ROOT=../../../../..
#########################################################################
#                                                                       #
# This Makefile recursivly allows to :                                  #
# configurate,build,run or test given tests or examples                 #
# from currect folder                                                   #
#                                                                       #
# S.Mushkaev  (RC)Module 2015                                           #
#                                                                       #
#                                                                       #
#########################################################################
# USAGE:
#
# /> make configure PLATFORMS="mc5103 emu6405 mc12101"
#  Recursively generates Makefiles for all tests/axamples for mc5103,emu6405,mc12101 platforms 
#
# /> make configure 
#  Recursively generates Makefiles for all tests/axamples for default platform list defined by $(PLATFORMS) in global.mk
#
# /> make 
#  Recursivly makes(builds) all Makefiles  from current folder 
#
# /> make run PLATFORMS="mc5103 emu6405"
#  Recursivly runs all tests/examples from current folder on mc5103 board and emulator
#
# /> make run 
#  Recursivly runs all tests/examples from current folder on all platforms from $(PLATFORMS) list defined in global.mk 
#
# /> make test TARGET1=mc5103 TARGET2=vs80
#  Recursivly builds and runs all tests from current folder  
#  Then two exitcodes fo $(TARGET1) and $(TARGET2) platforms are compared
#  if exitcodes are identical - test is passed
#
# /> make test 
#  Recursively builds and runs all tests from current folder with default $(TARGET1) and $(TARGET2) defined in global.mk 
#
# /> make clean 
#  Recursive cleanup (Remove all builds)
#
# /> make kill
#  Recursive clean with Makefile removal 




include $(ROOT)/global.mk
# get list of all sub-foldfers
WORK_DIRS=$(subst /,,$(wildcard */))

# override all sub-foldfers by custom list in local.mk
-include local.mk
WORK_DIRS := $(filter-out $(SKIP_DIRS),$(WORK_DIRS))

# for each sub-folder try to start Makefile with (build/test/run/clean targets) 
#.default 
test run clean: 
	@echo ***** build *************
	$(foreach dir,$(WORK_DIRS), $(MAKE) -C $(dir) $(MAKECMDGOALS) 	$(newline))
	
# for each sub-folder try to create Makefile
configure: $(addsuffix /Makefile,$(WORK_DIRS))
	@echo ***** configure **********
	$(foreach dir,$(WORK_DIRS), $(MAKE) -C ./$(dir) $(MAKECMDGOALS) $(newline))
	
#recursive delete all sub-makefiles
kill: 
	$(foreach mak,$(wildcard */Makefile), $(MAKE) -C $(dir $(mak)) kill				$(newline))
	$(foreach mak,$(wildcard */Makefile), -rm   $(mak) 								$(newline))
	
	
define configure_makefile
$(1)/Makefile:
	-$(OS_FIND) $(1)/*.cpp && echo ROOT=../$(ROOT)| $(OS_CAT) - "$(ROOT)/app/templates/sometest/Makefile" > $(1)/Makefile
	-$(OS_FIND) $(1)/*.cpp || echo ROOT=../$(ROOT)| $(OS_CAT) - "$(ROOT)/app/templates/Makefile" > $(1)/Makefile
endef
	
$(foreach dir,$(WORK_DIRS), $(eval $(call configure_makefile,$(dir))) )	


define newline


endef	
