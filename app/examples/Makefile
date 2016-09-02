ROOT = ../..
####################################################
#
# Recursive make in subfulders
#
# RC Module 2015
#
#
####################################################


include $(ROOT)/global.mk
-include $(ROOT)/dirs.mk

# prevents call of embedded 'find.exe' in Windows and GNU make becomes callable
PATH:= $(subst $(SystemRoot),,$(PATH))	

# get list of all sub-foldfers
SUB_DIRS=$(subst /,,$(wildcard */))
$(info DIRS=$(SUB_DIRS))
# get list of all sub-foldfers with makefile inside
SUB_MAKEFILES=$(wildcard */Makefile)
$(info MAKEFILES=$(SUB_MAKEFILES))

# for each sub-folder try to start Makefile with (build/test/run/clean targets) 
build test run clean: 
	echo ***** build *************
	$(foreach mk,$(SUB_MAKEFILES), $(MAKE) -C $(dir $(mk)) $(MAKECMDGOALS) 	$(newline))
	
# for each sub-folder try to create Makefile
configure: $(addsuffix /Makefile,$(SUB_DIRS))
	echo ***** configure **********
	$(foreach dir,$(SUB_DIRS), $(MAKE) -C ./$(dir) $(MAKECMDGOALS) 			$(newline))
	
#recursive delete all sub-makefiles
kill: 
	$(foreach mk,$(SUB_MAKEFILES), $(MAKE) -C $(dir $(mk)) kill				$(newline))
	$(foreach mk,$(SUB_MAKEFILES), -rm   $(mk) 								$(newline))
	
	
	
define configure_makefile
$(1)/Makefile:
	-$(ROOT)\deps\gnuwin32\bin\find $(1)/*.cpp && echo ROOT=../$(ROOT)| cat - "$(ROOT)/app/templates/sometest/Makefile" > $(1)/Makefile
	-$(ROOT)\deps\gnuwin32\bin\find $(1)/*.cpp || echo ROOT=../$(ROOT)| cat - "$(ROOT)/app/templates/Makefile" > $(1)/Makefile
endef
	
$(foreach dir,$(SUB_DIRS), $(eval $(call configure_makefile,$(dir))) )	


define newline


endef	
