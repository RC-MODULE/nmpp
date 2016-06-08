#ifndef PRIFILER_INCLUDED
#define PRIFILER_INCLUDED

//! Определяет макс размер строки имени функции в поле S_ProfilerData.funcname
//#include "profiler_def.h"
#include "string.h"
#include "time.h"
#include <stdio.h>
//#define MAX_FUNCNAME_LENGTH 64
#define MAX_FUNCNAME_LENGTH 16

/*! \page intro Введение 
	
	
Данная библиотека предназначения для профилирования проектов, разработанных под архитектуру процессоров семейства NeuroMatrix. 
Подключив к проекту можно получить статистику по кол-ву вызовов функций и времени их исполнения в процессорных тактах.
Результат можно вывести в табличном виде, в xml-формате, а также при необходимости непосредственно получить доступ к структурам профилирования в памяти. 
Библиотека поддерживает работу с платами МЦ5101, МЦ5103, МЦ6901, MB7707
*/

/*! \page Principle Принцип работы профайлера 

\par Инициализация
		Для работы профайлера сначала определяется список функций подлежащих профилированию.  \n
		Этот список наполняется пользователем с помощью специальных макросов с именами необходимых функций в теле функции <_profiler_list>. 
		
		
\code 
		#include "profiler_def.h"
		import from profiler.mlb;

		begin ".text_profiler"
		PROFILER_LIB(MAX_FUNCNAME_LENGTH);

		<_profiler_list>
			...
			PROFILE_FUNC(_myfunc,"myfunc");
			PROFILE_FUNC(_sin,"sin");
			PROFILE_FUNC(_cos,"cos");
			PROFILE_FUNC(_bool._.8.8fullBuffer.1.2,"fullBuffer");
			...
		<_profiler_last>
		return;

		end ".text_profiler";
\endcode

\par 
		При запуске программы производится инициализация профайлера путем вызова функции _profiler_list . 
		Каждый макрос  PROFILE_FUNC() по списку производит подмену кода в начале соответствующей функции и вставляет переход на собственный код с замером времени.
		Каждый макрос содержит структуру данных  S_ProfilerData в полях  которой накапливается информация о количестве вызовов и суммарном затраченном времени работы функции. 
		
\par Вывод результатов
  По окончанию работы программы результаты профилирования формируются в виде связного списка структур S_ProfilerData , который  можно вывести через stdout  (если работает printf) либо в табличном виде, либо в xml-формате с помощью макросов 
  PROFILER_PRINT() и PROFILER_PRINT2XML(). \n
  Также доступ к данным профлирования можно получить в виде связного списка непосредественно из памяти где они хранятся. \n
  Помимо результатов профилирования функций также можно замерять время на участках кода с помощью таймеров C_Stopwatch. Все объявленные таймеры аналогично объединяются в список и также могут быть отображены с помощью макросов
  STOPWATCH_PRINT() и STOPWATCH_PRINT2XML(). \n
  
*/


/*! \page manual Руководство по использованию
	
	
 \par 1. Создание профилировочного файла 
   \li Создать файл , например с именем - proflist.asm.\n
   \li Задать в макросе MAX_FUNCNAME_LENGTH (proiler_def.h) размер строки, содержащей название функции для вывода на экран. Чем больше размер строки, тем больший общий объем памяти будет зарезервирован под список. минимальный размер 8.
   Если имя функции больше размера MAX_FUNCNAME_LENGTH , то при выводе оно будет обрезано. На работу самого профайлера величина MAX_FUNCNAME_LENGTH не влияет.\n
   \li подключить макробиблиотеку profiler_06.mlb (для процессоров NM6405,NM6406) либо profiler_soc.mlb (для системы на кристалле - микросхемы К1879ХК1Я ) \n
   \li объявить секцию ".text_profiler". \n
    \e Примечание. Cекцию .text_profiler для большой точности замера времени рекомендуется располагать в быстрой внутренней памяти. Следует учесть, что при этом эта память извне может быть недоступна. 
	В таком случае для удобства спрофилированный список функций можно скопировать в разделяемую память с помощью функции profiler_list2table().\n
   \li между метками <_profiler_list> и <_profiler_last> перечислить имена профилируемых функций окруженных в макрос PROFILE_FUNC() \n
    \e Примечание. для некоторых системных функций с особым соглашением о вызове таких как: FAdd Mul32 FMul IDiv32 UDiv32 FDiv IMod32 UMod32 LShift32 RShift32 ARShift32 ConvI64toF ConvU64toF
необходимо использовать макрос PROFILE_NONSTD_FUNC()\n
    \e Примечание. Имена профилируемых функций можно взять из map-файла , предварительно скомпилировав программу с пустым списком функций. \n
    \e Примечание. По умолчанию линкер создает map-файл с обрезанными длинными С++ именами функций. Чтобы имена оставались  полными линкеру необходимо задать ключ -full_names \n
	 
	 
	Пример кода profiler.asm:

\code 
const MAX_FUNCNAME_LEN=MAX_FUNCNAME_LENGTH;
import from profiler.mlb;
//import from profiler_soc.mlb; // use profiler_soc.mlb for mc6901 board
begin ".text_profiler"
global _profiler_list:label;
global _profiler_last:label;
<_profiler_list>
	// place here macros with function name for each function you wish to profile like:
	// PROFILE_FUNC(_myfunc,"_myfunc");
	
	PROFILE_FUNC(_mysin,"mysin");
	PROFILE_FUNC(_mycos,"mycos");
	
<_profiler_last>
return;
end ".text_profiler";
\endcode 

\e Примечание. Профилировочный файл можно сгенерировать автоматически по имеющемуся map-файлу. 
Генерация осуществляется запуском \htmlonly <A HREF="http://www.activestate.com/activetcl/downloads">  TCL </A>    \endhtmlonly скрипта generate_proflist.tcl из папки scripts , где в качестве параметра необоходимо  указать имя map-файла . 
например:
\verbatim 
tclsh generate_proflist.tcl main.map
\endverbatim
В результате работы скрипта будет сгенерирован файл proflist_generated.asm. 
После чего лишние макросы можно просто удалить из файла и переименовать его в profile.asm. \n
Следует учесть, что скрипт generate_proflist.tcl  не отличает меток на данные и функции и в параметры макросов могут попасть метки на данные.
В этом случае линкер выдаст ошибку наподобие : 
\verbatim 
"DEBUG\DEQUANTIZER.ELF": ERROR LNK415: Symbol "_unsigned._int._const._.8.8Qs.5.7" has different types in different files.
\endverbatim
Соответствующие макросы надо просто удалить 


 
\par 2. Модификация сборочного файла 
  - подключите библиотеку profiler06.lib , profiler05.lib или profiler_soc.lib \n
  - подключите библиотеку nm_io.lib если вывод результатов профилирования осуществляется на stdout  \n
  - добавьте соответствующие пути lib и include библиотеки профайлера \n
  - добавьте сборку профилировочного файла proflist.asm \n
  - укажите ключ -fullnames в параметрах линкера 
  
например:
\verbatim 
nmcc main.cpp -6405 -g          -o.\Release\main.elf     -I..\..\profiler\libprofiler\include -I%NEURO%\include
nmcc proflist.asm -Sc -g -6405  -o.\Release\proflist.elf -I..\..\profiler\libprofiler\include -I%NEURO%\include
linker  -full_names -cmc5101brd.cfg -m -d0 -heap=11000 -o.\example.abs .\Release\main.elf  .\Release\proflist.elf nm_io.lib mc5103lib.lib libc05.lib profiler06.lib cppnew05.lib -l%PROFILER%\lib  -l%NEURO%\lib
\endverbatim


 \par 3. Модификация конфигурационного файла 
 Необходимо модифицировать конфиг файл, чтобы обеспечить работу printf  и расположить секцию .text_profile по возможности во внутренней (быстрой памяти), 
 где будут накапливаться результаты профилирования. \n
 например :
 \verbatim
MEMORY
{
	local0:  at 0x00000200, len = 0x00007E00;
	global0: at 0x80000000, len = 0x00008000;
	local1:  at 0x10004000, len = 0x00FFC000;
	global1: at 0xA0000000, len = 0x01000000;
}
SEGMENTS
{
	...
	usercode 	: in local0;
	shared		: in local1;
}

SECTIONS
{
	...
	.rpc_services 		: in shared;		// необходимо для printf
	.rpc_services.bss 	: in shared;		// необходимо для printf
	.text_profile 		: in usercode;

}
\endverbatim	
	
	
	
 \par 4. Запуск  профайлера 
 В основном файле с функцией main() подключить заголовочный файл profiler.h и запустить инициализацию профайлера с нужного места с помощью функции profiler_init().


 \code 
#include "profiler.h"

extern "C"{
	int mysin(){
		...
	}
	void mycos(){
		...
	}
};


int main()
{
	...
	PROFILER_PRINT();
	...
	return 1;
}
 \endcode
	
	
 \par 5. Вывод результатов на экран или в файл

	Вывод на экран  (через stdout) результатов профилирования осуществляется макросами :
	PROFILER_PRINT() - вывод в табличном виде \n
	PROFILER_PRINT2XML() осуществляет вывод в формате xml \n \n
	
	Для вывода необходимо чтобы работала функция printf для данной платы. \n
	Работа этой функции обеспечивается подключением библиотеки nm_io.lib.  \n
	\e Примечание. Библиотека nm_io.lib должна идти первой в списке подключаемых библиотек.
	

	Пример запуска и вывода таблицы статистики на экран: \n
	\verbatim 
	mc5103run example.abs 
	\endverbatim 

	Пример запуска и перенаправления данных в board_stdout.txt : \n
	\verbatim 
	mc5103run example.abs -p 
	\endverbatim 

	
 \par 6. Непосредственный доступ к результатам профилирования 
   Если printf не работает, доступ к данным профлирования можно получить непосредственно из памяти где они хранятся.  \n\n
   
  \b Вариант \b 1. - поэлементный доступ через связный спиcок. \n
  Профилированные данные хранятся в виде связного списка структур S_ProfilerData.
  
  Доступ к первому элементу можно получить с помощью вызова функции profiler_head():
  \code 
  S_ProfilerData* profile_item=profiler_head(); 
  \endcode 
  
  Доступ к следующей структуре по списку - осуществляется через поле  S_ProfilerData::next . \n
  \e Примечание. Список должен располагаться в разделяемой памяти
  
  \b Вариант \b 2. - доступ через таблицу . \n
  Сформированные профилированные данные изначально хранятся в виде связного списка, который не всегда удобно  поэлементно считывать с host-машины. Кроме того 
  секцию .text_profiler может располагать в недоступной извне  внутренней памяти. В этих целях рекомендуется использоваться функцию копирования списка структур S_ProfilerData во внешнюю разделяемую память с помощью функции profiler_list2table(). 
  Скопированные данные по прежнему сохранят структуру связного списка , но при этом будут располагаться линейно в виде одномерного массива. Этот массив можно прочитать 
  с host-машины за раз и вывести на экран с помощью специальных функций:
  
  \e nm-код:
  \code
	...
	int count=profiler_count(profiler_head());  // вычисляем кол-во профилированных функций в списке
	S_ProfilerData* tbl=(S_ProfilerData*)malloc1(count*sizeof(S_ProfilerData)); // выделяем область под таблицу в разделяемой памяти
	if (tbl==0) return -1;
	profiler_list2table(profiler_head(),tbl);   // копируем данные по функциям в таблицу в разделяемой памяти
	ncl_hostSync((int)tbl);                     // передаем адрес таблицы
	ncl_hostSync((int)profiler_count(tbl));     // передаем размер таблицы
	...
  \endcode
  
  \e pc-код:
  \code 
	...
	int addr, count;
	PL_Sync(access,123,&addr);                      // читаем адрес первой структуры S_ProfilerData в разделяемой памяти
	PL_Sync(access,123,&count);                     // читаем размер таблицы

	S_ProfilerData* head=new S_ProfilerData[count]; // выделяем память под таблицу
	PL_ReadMemBlock(access, (PL_Word*) head, addr, count*sizeof(S_ProfilerData)/4);	// копируем таблицу
	
	profiler_table2list(head,count);                // обновляем связи в таблице
	profiler_char8bit(head);                        // преобразцем строку в 8-битную char строку
	profiler_print(head);                           // печатаем таблицу профилированных функций
	...
  \endcode
  
  
  
 \par Примечание 1 :  
в папке scripts прилагается xsl преобразование -profile.xsl , позволяющее отобразить содержимое xml-файла в браузере в отсортированном табличном виде . 
Файл profile.xsl при этом должен находится рядом с файлом profile.xml.

 \par Примечание 2 :
Названия функций хранятся в массиве типа int поля S_ProfilerData::funcname. Для корректного отображения строки на host-машине необходимо пользоваться функциями преобразования к типу char: profiler_char8bit() или функцией членом класса S_ProfilerData::funcname2char().

 \par Примечание 3 :
При компиляции с ключом оптимизации -O1 или -O2 некоторые функы могут подставиться как inline функции и в этом случае их профилирование не произойдет.
	
*/


extern "C"{
//!  Структура хранения результатов профилирования для одной функции 
/*!
 Из данных структур создается связный список по профилируемым функциям. Указатель на первую стурктуру возращает функция profiler_head() 
*/
	void profiler_start();
	void profiler_stop();
	void profiler_reset();
	void profiler_dummy();
	
	
	struct S_ProfilerData {
		S_ProfilerData* next;				///< указатель на следующую структуру 
		unsigned	funcaddr;				///< адрес функции
		unsigned	calls;					///< кол-во вызовов 
		unsigned	summary;				///< суммарное накопленное время (в тактах)
		unsigned	funcname[MAX_FUNCNAME_LENGTH];///< имя функции для отображения в статистике (может не свпадать с реальным именем)
		unsigned	stopwatch;				///< последний замер времени (значение таймер t1)
	};
	
	
	//! Функция копирует связный список структур профилирования в непрерывный линейный массив и связывает в новый список. Вызов данной функции необходим для удобства чтения данных с host - машины в виде массива а также чтобы скопировать данные в разделяемую память.
	//! \param src_head указатель на первую структуру в исходном списке.
	//! \param dst_table указатель на первую структуру в результирующем списке.
	//! \return возвращает указатель на последний элемент в резельтирующем списке.
	inline S_ProfilerData* profiler_replace(const S_ProfilerData* src_head,S_ProfilerData* dst_table){
		S_ProfilerData* last;
		while (src_head){
			memcpy(dst_table,src_head,sizeof(S_ProfilerData));
			last=dst_table;
			src_head=src_head->next;
			dst_table->next=dst_table+1;
			dst_table=dst_table->next;
		}
		last->next=0;
		return last;
	}

	//! Функция вычисляет кол-во записей в списке начиная с head
	//! \param head указатель на первую структуру в списке.
	//! \return кол-во записей в списке начиная с head
	inline int profiler_count(S_ProfilerData* head){
		int i=0;
		while (head->next){
			head=head->next;
			i++;
		}
		return i;
	}

//! \}
	



};
#endif 
