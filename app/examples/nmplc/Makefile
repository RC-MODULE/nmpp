####################################################
#
# Recursive make in subfulders
#
# RC Module 2015
#
#
####################################################

ROOT = ../../..
include $(ROOT)/setenv.mk

# 'dirs.mk' specifies list of dirs for recursive make in subfolders . 
# If 'dir.mk' doesn't exists then all subfolders will be used
ifeq ($(wildcard dirs.mk),)
DIRS=$(subst /,,$(wildcard */))
else 
include dirs.mk
endif

# prevents call of embedded 'find.exe' in Windows and GNU make becomes callable
PATH:= $(subst $(SystemRoot),,$(PATH))	

	
test configure run clean: $(addsuffix /Makefile,$(DIRS))
	$(foreach dir,$(DIRS), $(MAKE) -C ./$(dir) $(MAKECMDGOALS) 				$(newline))

kill: $(addsuffix /Makefile,$(DIRS))
	$(foreach dir,$(DIRS), $(MAKE) -C ./$(dir) kill			 				$(newline))
	$(foreach dir,$(DIRS), -rm   ./$(dir)/Makefile 	.toolchecked.mk			$(newline))
	
	
.DEFAULT: 
	$(foreach dir,$(DIRS), $(MAKE) -C ./$(dir) $(MAKECMDGOALS) 				$(newline))
	
define cp_makefile
$(1)/Makefile:
	-find $(1)/*.cpp && cp "$(TEMPLATES)/sometest/Makefile" $(1)
	-find $(1)/*.cpp || cp "$(TEMPLATES)/Makefile" $(1)
endef
	
$(foreach dir,$(DIRS), $(eval $(call cp_makefile,$(dir))) )	


define newline


endef	
