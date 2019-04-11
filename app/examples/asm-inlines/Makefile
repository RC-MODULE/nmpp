ROOT=../../..
####################################################
#
# Recursive make in subfulders
#
# RC Module 2015
#
#
####################################################

include $(ROOT)/global.mk
# get list of all sub-foldfers
WORK_DIRS=$(subst /,,$(wildcard */))
ifeq ($(wildcard config.mk),config.mk)
include config.mk
endif
WORK_DIRS := $(filter-out $(SKIP_DIRS),$(WORK_DIRS))

# for each sub-folder try to start Makefile with (build/test/run/clean targets) 
build test run clean: 
	echo ***** build *************
	$(foreach dir,$(WORK_DIRS), $(MAKE) -C $(dir) $(MAKECMDGOALS) 	$(newline))
	
# for each sub-folder try to create Makefile
configure: $(addsuffix /Makefile,$(WORK_DIRS))
	echo ***** configure **********
	$(foreach dir,$(WORK_DIRS), $(MAKE) -C ./$(dir) $(MAKECMDGOALS) 			$(newline))
	
#recursive delete all sub-makefiles
kill: 
	$(foreach mak,$(wildcard */Makefile), $(MAKE) -C $(dir $(mak)) kill				$(newline))
	$(foreach mak,$(wildcard */Makefile), -rm   $(mak) 								$(newline))
	
	
define configure_makefile
$(1)/Makefile:
	-find $(1)/*.cpp && echo ROOT=../$(ROOT)| cat - "$(ROOT)/app/templates/sometest/Makefile" > $(1)/Makefile
	-find $(1)/*.cpp || echo ROOT=../$(ROOT)| cat - "$(ROOT)/app/templates/Makefile" > $(1)/Makefile
endef
	
$(foreach dir,$(WORK_DIRS), $(eval $(call configure_makefile,$(dir))) )	


define newline


endef	
