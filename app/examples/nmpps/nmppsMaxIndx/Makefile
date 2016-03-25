ROOT=../../../..
include $(ROOT)/setenv.mk
# TEST-MAKEFILE
# This Makefile is for testing purpose
# It builds and runs two applications built from common cpp-source but for different platforms and compares their exit codes
# It also generates makefile for given platform using $(TEMPLATES)\make_$(platform) template
# USAGE:
# make                    : generates projects and builds apps for all (from $(PLATFORMS)) platforms
# make mc5103             : generates project and builds test app for mc5103 or any other from $(PLATFORMS)
# make test-win32-mc5103  : run applications under win32 and mc5103 platforms or any pair from $(PLATFORMS) and compare thier exit codes
# make clean              : clean up in all make_$(PLATFORMS)
# make delete             : delete all make_$(PLATFORMS) folder
#
# Used global variables: TOP_LEVEL,TEMPLATES,PLATFORMS should be exported from parent Makefile or set manualy in global.mk (for local usage)
# TOP_LEVEL :points to root directory of NMPP   
# TEMPLATES :points to automake template folder 
# PLATFORMS :set of available platforms: win32 mc5103 mb7707 emu ...

ifeq ($(wildcard config.mk),config.mk)
include config.mk
endif

PATH := $(ROOT)\deps\gnuwin32\bin

#all: $(addsuffix /Makefile,$(addprefix make_,$(PLATFORMS))) $(addprefix build_,$(PLATFORMS))
#	$(foreach platform,$(PLATFORMS), -$(MAKE) -C./make_$(platform) 					$(newline))
all: configure
	$(foreach platform,$(PLATFORMS), -$(MAKE) -C./make_$(platform) 					$(newline))

configure: $(addsuffix /Makefile,$(addprefix make_,$(PLATFORMS))) 
	
clean:
	$(foreach platform,$(PLATFORMS), -$(MAKE) -C./make_$(platform) clean 			$(newline))


run:	all
	$(foreach platform,$(PLATFORMS), -$(MAKE) -C./make_$(platform) run 				$(newline))

kill: 
	-rm -f -r make_* 
	

test: make_$(TARGET1)/Makefile make_$(TARGET2)/Makefile
	$(MAKE) -C./make_$(TARGET1) run 
	$(MAKE) -C./make_$(TARGET2) run
	diff make_$(TARGET1)/.exitcode make_$(TARGET2)/.exitcode
	

########### Produces automake rule for all platforms like ############################
# 
# mc5103: make_mc5103
# make_mc5103:
#   mkdir make_mc5103
#	cp $(TEMPLATES)/make_mc5103/*.* ./make_mc5103
#
# build_mc5103:
#	$(MAKE) -C./make_mc5103 
#
define automake_platform
$(1):make_$(1)/Makefile

make_$(1)/Makefile: make_$(1)
	echo ROOT=../$(ROOT)| cat - $(ROOT)/app/templates/sometest/make_$(1)/Makefile > make_$(1)/Makefile
	-cp $(ROOT)/app/templates/sometest/make_$(1)/*.cfg make_$(1)
	

make_$(1): 
	mkdir make_$(1)

endef	
#build_$(1):	
#	$$(MAKE) -C./make_$(1)


$(foreach platform, $(PLATFORMS),$(eval $(call automake_platform,$(platform))))
#######################################################################################

define newline


endef
