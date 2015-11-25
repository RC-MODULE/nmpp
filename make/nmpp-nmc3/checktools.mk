TOOLS= rm $(CROSS_COMPILE)gcc find which nmcc mkdir mb7707run nm6405emurun mc5103run edcltool diff

#ifeq ($(OS),Windows_NT)
#  OS_WHICH= where
#  OS_RM   = del /Q
#  OS_RD   = rd /Q /S
#else
  OS_WHICH= which
  OS_RM   = rm -f -r
  OS_RD   = rm -f -r
#endif


define have_tool
$(eval OUT=$(shell $(OS_WHICH) $(1)))
ifneq ($(OUT),)
HAVE_$(1):=$(OUT)
endif
endef 


$(foreach tool,$(TOOLS),$(eval $(call have_tool,$(tool))))

all:
	rm -f -r .toolchecked.mk
	$(foreach tool,$(TOOLS),@echo HAVE_$(tool)=$(HAVE_$(tool)) >>.toolchecked.mk $(endline))
	$(foreach tool,$(TOOLS),@echo export HAVE_$(tool) >>.toolchecked.mk $(endline))

define endline


endef
	
	
	
	
