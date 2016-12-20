ROOT=../../..
####################################################
#
# Recursive make in subfulders
#
# RC Module 2015
#
#
####################################################
# USAGE:
# > make configure 
#  - recursive generates Makefiles for all tests for different platforms defined in $(PLATFORMS) list
#
# > make test TARGET1=mc5103 TARGET2=vs80
# - recursive build and run all test from current folder 
# - each test compares exitcode of programs runned on  $(TARGET1) and $(TARGET2) platforms 
# - if exitcodes are identical - test is passed
#
# make test 
# - recursive build and run all tests from current folder with default $(TARGET1) and $(TARGET2) defined in global.mk 


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
	$(foreach dir,$(WORK_DIRS), $(MAKE) -C ./$(dir) $(MAKECMDGOALS) 			$(newline))
	
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
