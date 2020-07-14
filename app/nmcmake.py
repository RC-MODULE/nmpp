#!/usr/bin/env python

import sys
import os
import time
import json
import shutil
import os.path
import subprocess
import logging


# Таймер
def timer(func):
    def wrapper():
        t = time.time()
        func()
        print('%.4f seconds' % float(time.time() - t))
    return wrapper


# Функция на проверку обязательных папок
def include_dir(directory_path_arr, data_from_json):
    for i in data_from_json:
        if i in directory_path_arr:  # Если найдена директория, которую необходимо включить
            return False
    return True


# Функция на исключения папок
def exclude_dir(directory_path_arr, data_from_json):
    for i in data_from_json:
        if i in directory_path_arr:  # Если найдена директория, которую необходимо исключить
            return True
    return False


# Функция на изменения настроек, связанные
def change_settings(data_json_change, path):
    with open(os.path.join(path, 'local.json'), 'r') as f:
        data = json.loads(f.read())
    for key, value in data.items():
        if data[key] != []:
            data_json_change[key] = value


# Функция на копирование файлов и папок
def copytree(src, dst, symlinks=False, ignore=None):
    if not os.path.exists(dst):
        os.makedirs(dst)
    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isdir(s):
            copytree(s, d, symlinks, ignore)
        else:
            if not os.path.exists(d) or os.stat(s).st_mtime \
                   - os.stat(d).st_mtime > 1:
                shutil.copy2(s, d)


# Наследование настроек от global.json к найденному local.json
def inheritance(directory, json_settings):
    global_json_directory = directory
    list_of_files = []
    data = dict()
    while True:
        if 'global.json' in list_of_files:
            path_to_file = 'global.json'
            break
        else:
            os.chdir(os.path.dirname(global_json_directory))
            global_json_directory = os.getcwd()
            list_of_files = os.listdir(global_json_directory)
    with open(path_to_file, 'r') as f:  # Открытие файла с расширением .json
        data = json.loads(f.read())
    for key in data.keys():
        if key not in json_settings:  # Проверка на остуствие какого-либо поля в local.json
            json_settings[key] = data[key]
        elif json_settings[key] == []:  # Проверка на пустое значения поля в local.json
            json_settings[key] = data[key]
    return os.getcwd()


# Добавление переменной ROOT в Makefile
def add_ROOT(directory_path, settings, path_to_global):
    os.chdir(os.path.join(path_to_global, settings['root_dir']))
    root_path = os.getcwd()  # Путь до корня
    os.chdir(directory_path)
    dirs = os.listdir(directory_path)
    for directory in dirs:
        local_flag = os.path.abspath(f'{directory}')  # Флаг для сохранения директории
        if not os.path.isdir(local_flag):  # Проверка, есть ли в списке элементов файлы (не директории)
            continue
        os.chdir(local_flag)  # Заходим в папку с Makefile
        depth = list()
        # Создание относительного пути к корню
        for x in range(os.getcwd().count(os.path.sep, len(root_path))):
            depth.append('..')
        data = '/'.join(depth)
        if 'Makefile' in os.listdir(local_flag):
            os.chdir(local_flag)
            with open('Makefile', 'r+') as f:
                lines = f.readlines()
                if lines[0] != f'ROOT = {data}\n':
                    f.seek(0)
                    f.write(f'ROOT = {data}\n')
                    for line in lines:
                        f.write(line)
                else:
                    print('ROOT has already defined')
        os.chdir(directory_path)
    print(directory_path)


'''
Метод конфигурации, копируют все конфигурации(взятые из json-файла)
в дочерние папки, относительно той папки, откуда был вызван метод.
'''


@timer
def configure():
    is_local = False
    folder = []
    settings = dict()
    init_directory = os.getcwd()
    directory = os.getcwd()
    inner_files = os.listdir(directory)
    while True:  # Поиск до первого local.json или до global.json
        if 'global.json' in inner_files:
            path = 'global.json'
            path_to_global = directory
            print('global JSON founded')
            break
        elif 'local.json' in inner_files:
            path = 'local.json'
            print('local JSON founded')
            is_local = True
            break
        else:
            print('JSON-file NOT FOUND!')
            os.chdir(os.path.dirname(directory))  # Смена директории на родительскую(т.е. идем наверх)
            directory = os.getcwd()
            inner_files = os.listdir(directory)
    json_directory = directory  # Необходим флаг для хранения пути до начального json-файла
    new_local_json_flag = json_directory  # Флаг для хранения пути нижележащего json-файла(если такие будут)
    with open(path, 'r') as f:  # Открытие файла с расширением .json
        data = json.loads(f.read())
    for key, value in data.items():
        settings[key] = value
    if is_local:  # Флаг, который указывает на то, что мы встретили первым local.json
        path_to_global = inheritance(json_directory, settings)
        for key, value in settings.items():
            data[key] = value
    directory = init_directory
    # Проход по дереву дочерних элементов, относительно папки, откуда вызван метод
    for i in os.walk(directory):
        folder.append(i)
    if 'main.cpp' not in folder[0][2]:
        folder.pop(0)
    for i in folder:
        if new_local_json_flag not in i[0]:  # Сохранение настроек начального json-файла
            for key, value in settings.items():
                data[key] = value
            new_local_json_flag = json_directory  # Сохранение флага относительно начального json-файла
        if data['include_dirs'] == []:  # Если нет специальных папок
            if 'local.json' in i[2]:  # Поиск нижележащего local.json
                change_settings(data, i[0])  # Изменение .json настроек
                new_local_json_flag = i[0]  # Сохранение флага относительно директории, в которой найден local.json
            if exclude_dir(i[0].split('\\'), data['exclude_dirs']):
                continue
            if 'main.cpp' in i[2]:  # Конечная ветвь
                # Переход в папку templates
                os.chdir(path_to_global)
                os.chdir(data['template_dir'])
                for cfg in data['targets']:
                    try:
                        os.mkdir(os.path.join(i[0], data['target_index'] + cfg))  # Создание папки make..
                    except FileExistsError:
                        # Необходимо для исключения ошибки, если папка уже существует
                        shutil.rmtree(os.path.join(i[0], data['target_index'] + cfg))  # Удаление папки make.. и её содержимого
                        os.mkdir(os.path.join(i[0], data['target_index'] + cfg))
                    copytree(os.path.join(os.getcwd(), data['target_index'] + cfg), os.path.join(i[0], data['target_index'] + cfg))
                add_ROOT(i[0], settings, path_to_global)
        else:
            if 'local.json' in i[2]:
                change_settings(data, i[0])
                new_local_json_flag = i[0]
            if include_dir(i[0].split('\\'), data['include_dirs']):
                continue
            if exclude_dir(i[0].split('\\'), data['exclude_dirs']):
                continue
            if 'main.cpp' in i[2]:
                os.chdir(path_to_global)
                os.chdir(data['template_dir'])
                for cfg in data['targets']:
                    try:
                        os.mkdir(os.path.join(i[0], data['target_index'] + cfg))  # Создание папки make..
                    except FileExistsError:
                        shutil.rmtree(os.path.join(i[0], data['target_index'] + cfg))  # Удаление папки make.. и её содержимого
                        os.mkdir(os.path.join(i[0], data['target_index'] + cfg))
                    copytree(os.path.join(os.getcwd(), data['target_index'] + cfg), os.path.join(i[0], data['target_index'] + cfg))
                add_ROOT(i[0], settings, path_to_global)
    print('\nAll files were configured')


'''
Метод удаления, удаляют все скопированные конфигурации
(папки из templates) в дочерних папках.
'''


@timer
def kill():
    folders = []
    for i in os.walk(os.getcwd()):  # Проход по древу дочерних элементов папки, из которой вызван метод
        folders.append(i)
    if 'main.cpp' not in folders[0][2]:
        folders.pop(0)
    for folder in folders:
        if 'main.cpp' in folder[2]:
            if folder[1] == []:
                continue
            else:
                for element in folder[1]:
                    shutil.rmtree(os.path.join(folder[0], element))  # Удаление папки и всего внутреннего контента
            print(folder[0])
    print('\nAll configures were deleted')


@timer
def test():
    pass


def run_external_app(args):
    is_local = False
    folder = []
    settings = dict()
    init_directory = os.getcwd()
    directory = os.getcwd()
    inner_files = os.listdir(directory)
    while True:  # Поиск до первого local.json или до global.json
        if 'global.json' in inner_files:
            path = 'global.json'
            path_to_global = directory
            print('global JSON founded')
            break
        elif 'local.json' in inner_files:
            path = 'local.json'
            print('local JSON founded')
            is_local = True
            break
        else:
            print('JSON-file NOT FOUND!')
            os.chdir(os.path.dirname(directory))  # Смена директории на родительскую(т.е. идем наверх)
            directory = os.getcwd()
            inner_files = os.listdir(directory)
    json_directory = directory  # Необходим флаг для хранения пути до начального json-файла
    new_local_json_flag = json_directory  # Флаг для хранения пути нижележащего json-файла(если такие будут)
    with open(path, 'r') as f:  # Открытие файла с расширением .json
        data = json.loads(f.read())
    for key, value in data.items():
        settings[key] = value
    if is_local:  # Флаг, который указывает на то, что мы встретили первым local.json
        path_to_global = inheritance(json_directory, settings)
        for key, value in settings.items():
            data[key] = value
    if args[0] == '-log':  # Проверка на выбор .log-файла для записи (по умолчанию make.log)
        log_path = os.path.join(path_to_global, args[1])
        cmd = args[2:]
    else:
        log_path = os.path.join(path_to_global, data['log'])
        cmd = args
    logging.basicConfig(format=u'%(filename)s[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level=logging.DEBUG, filename=u'{log}'.format(log=log_path))
    directory = init_directory
    # Проход по дереву дочерних элементов, относительно папки, откуда вызван метод
    for i in os.walk(directory):
        folder.append(i)
    if 'main.cpp' not in folder[0][2]:
        folder.pop(0)
    for i in folder:
        if new_local_json_flag not in i[0]:  # Сохранение настроек начального json-файла
            for key, value in settings.items():
                data[key] = value
            new_local_json_flag = json_directory  # Сохранение флага относительно начального json-файла
        if data['include_dirs'] == []:  # Если нет специальных папок
            if 'local.json' in i[2]:  # Поиск нижележащего local.json
                change_settings(data, i[0])  # Изменение .json настроек
                new_local_json_flag = i[0]  # Сохранение флага относительно директории, в которой найден local.json
            if exclude_dir(i[0].split('\\'), data['exclude_dirs']):
                continue
            if 'main.cpp' in i[2]:  # Конечная ветвь
                if i[1] == []:
                    print('Files were not confgiured!')
                else:
                    for test in i[1]:
                        os.chdir(os.path.join(i[0], test))
                        if 'Makefile' in os.listdir(os.getcwd()):
                            result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
                            print(result.stdout.encode('cp1251').decode('cp866'), result.stderr.encode('cp1251').decode('cp866'))
                            if result.returncode == 2:  # Появление ошибки и сохранение информацию о нем (расположение, текст ошибки)
                                logging.error(u'\ndirectory : {folder}\ntext : {error}'.format(folder=os.getcwd(), error=result.stderr.encode('cp1251').decode('cp866')))  # Запись в лог
                            print('---------------------------')
        else:
            if 'local.json' in i[2]:
                change_settings(data, i[0])
                new_local_json_flag = i[0]
            if include_dir(i[0].split('\\'), data['include_dirs']):
                continue
            if exclude_dir(i[0].split('\\'), data['exclude_dirs']):
                continue
            if 'main.cpp' in i[2]:
                if i[1] == []:
                    print('Files were not confgiured!')
                else:
                    for test in i[1]:
                        os.chdir(os.path.join(i[0], test))
                        if 'Makefile' in os.listdir(os.getcwd()):
                            result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
                            print(result.stdout.encode('cp1251').decode('cp866'), result.stderr.encode('cp1251').decode('cp866'))
                            if result.returncode == 2:  # Появление ошибки и сохранение информацию о нем (расположение, текст ошибки)
                                logging.error(u'\ndirectory : {folder}\ntext : {error}'.format(folder=os.getcwd(), error=result.stderr.encode('cp1251').decode('cp866')))  # Запись в лог
                            print('---------------------------')
    if len(cmd) > 0:
        print(f'\n{" ".join(cmd)} process is done\n')


if __name__ == "__main__":
    try:
        # входящая команда
        args = sys.argv
        op = args[1]
        if op == 'configure':
            configure()
        elif op == 'kill':
            kill()
        elif op == 'test':
            print('test')
        else:
            run_external_app(args[1:])
    except IndexError:
        print('''Write one of the nmcmake.py operations below:
    1)configure
    2)kill
    3)test
    or run external app e.g:'python nmcmake.py make.exe ...' ''')
        exit()
