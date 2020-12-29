ifndef OS_RM
 	OS_RM    =rm -f -r
  	OS_RD    =rm -d -r -f
endif

kill: clean
	-$(OS_RM) *.vcproj *.sln *.vcxproj *.db $(TARGET_LIB)

clean:
	-$(OS_RM) Release/*.o 
	-$(OS_RM) Debug/*.o 
	-$(OS_RM) $(TARGET) $(TARGET)_qemu *.abs *.elf *.ncb *.map *.elf *.suo *.user *.filters *.db *.make  *.opendb .objects nmc4vars_win.mk
	-$(OS_RD) Debug Release bin obj .vs
	
#	$(MAKE) del_files
#	$(MAKE) del_folders
	
#del_files:
#	-$(OS_RM) Release/*.o 
#	-$(OS_RM) *.abs *.elf *.ncb *.map *.elf *.suo *.user *.filters *.db *.make  .*  *.opendb  nmc4vars_win.mk
	
#del_folders:
#	-$(OS_RD) Debug Release bin obj .vs
	