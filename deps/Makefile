ROOT = ..
#-include $(ROOT)/environment.mk
-include $(ROOT)/global.mk
#http_proxy ?=http://username:password@proxy:80/


#$(eval OUT=$(shell wget ))
#ifeq ($(OUT),)
#$(info -------------------------------------------------------------------)
#$(error ERROR: wget not found. Install setup wget from http://gnuwin32.sourceforge.net/URLages/wget.htm to sobel-steps/gnuwin32/ or to another folder accessible by PATH )
#endif
#
#
#$(eval OUT=$(shell unzip ))
#ifeq ($(OUT),)
#$(info -------------------------------------------------------------------)
#$(error ERROR: unzip not found. Install setup unzip from http://gnuwin32.sourceforge.net/URLages/unzip.htm to sobel-steps/gnuwin32/ or to another folder accessible by PATH )
#endif

all: download install

ifeq ($(OS),Windows_NT)
 # RCM Module production packages 
  SDK_MC5103_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mc5103_distrib_v_01_01_with_printf_non_official.zip
  SDK_MB7707_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mb7707_distrib_v_01_02_x32.zip
  SDK_MC7601_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mc7601_distrib_non_official.zip
  NMSDK_URL      = http://www.module.ru/mb7707/toolchains-neuromatrix/nmsdk_2016-04-19_non_official.zip
  NM_IO_URL      = http://www.module.ru/mb7707/NeuroMatrix/nm_io.zip
  VSHELL32_URL   = http://www.module.ru/mb7707/NeuroMatrix/VSHELL32.ZIP
  VSHELL32_DIST  = http://www.module.ru/mb7707/NeuroMatrix/VSHELL32_1.0.0.26.exe
 # 3rd party production packages 
  COREUTILS_URL	 = http://sourceforge.net/projects/gnuwin32/files/coreutils/5.3.0/coreutils-5.3.0-bin.zip
  COREDEPS_URL	 = http://sourceforge.net/projects/gnuwin32/files/coreutils/5.3.0/coreutils-5.3.0-dep.zip
  FIND_URL       = https://sourceforge.net/projects/gnuwin32/files/findutils/4.2.20-2/findutils-4.2.20-2-bin.zip
  CECHO_URL 	 = https://github.com/elisherer/cecho/archive/master.zip
  PUTTY_URL      = http://tartarus.org/~simon/putty-snapshots/x86/putty.zip
  # PUTTY's homepage http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html
  
  URLS = \
	  $(SDK_MC5103_URL) \
	  $(SDK_MB7707_URL) \
	  $(SDK_MC7601_URL) \
	  $(NMSDK_URL)      \
	  $(NM_IO_URL)      \
	  $(VSHELL32_URL)   \
	  $(VSHELL32_DIST)  \
	  $(COREUTILS_URL)	 \
	  $(COREDEPS_URL)	 \
	  $(FIND_URL)       \
	  $(CECHO_URL) 	 \
	  $(PUTTY_URL)      
  
  DOWNLOADS = $(notdir $(URLS))

install: nmsdk nm_io mc5103sdk mb7707sdk mc7601sdk vshell32 gnuwin32 putty cecho

else
  SDK_MC5103_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mc5103_distrib_v_01_01.tar.gz
  SDK_MB7707_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mb7707_distrib_v_01_00.tar.gz
  NMSDK_URL      = http://www.module.ru/mb7707/toolchains-neuromatrix/nmsdk.tar.gz
  NM_IO_URL      = http://www.module.ru/mb7707/NeuroMatrix/nm_io.zip
  
  URLS = \
	  $(SDK_MC5103_URL) \
	  $(SDK_MB7707_URL) \
	  $(NMSDK_URL)      \
	  $(NM_IO_URL)      
	  
  DOWNLOADS = $(notdir $(URLS))

install: nmsdk nm_io mc5103sdk mb7707sdk  

endif

#------------------------- package downloading of depended URLs --------------------

download: $(DOWNLOADS)

$(DOWNLOADS): 
	$(OS_WGET) $(URLS)
	
#------------------------- package installation  --------------------

mc5103sdk: $(notdir $(SDK_MC5103_URL))
	-mkdir $(@)
	$(OS_TAR) $(<) $(OS_TODIR) $(@)
	
mb7707sdk: $(notdir $(SDK_MB7707_URL))
	-mkdir $(@)
	$(OS_TAR) $(<) $(OS_TODIR) $(@) 

mc7601sdk: $(notdir $(SDK_MC7601_URL))
	-mkdir $(@)
	$(OS_TAR) $(<) $(OS_TODIR) $(@) 

nmsdk: $(notdir $(NMSDK_URL))
	-mkdir $(@)
	$(OS_TAR) $(<) $(OS_TODIR) $(@)

vshell32: $(notdir $(VSHELL32_URL))
	$(OS_UNZIP) $(<) 

nm_io: $(notdir $(NM_IO_URL))
	$(OS_UNZIP) $(<)
	
gnuwin32: $(notdir $(COREUTILS_URL)) $(notdir $(COREDEPS_URL))
	-mkdir gnuwin32
	$(OS_TAR) $(notdir $(COREUTILS_URL)) $(OS_TODIR) gnuwin32
	$(OS_TAR) $(notdir $(COREDEPS_URL))  $(OS_TODIR) gnuwin32
	$(OS_TAR) $(notdir $(FIND_URL))      $(OS_TODIR) gnuwin32

putty: $(notdir $(PUTTY_URL))
	-mkdir gnuwin32
	$(OS_TAR) $(notdir $(PUTTY_URL)) $(OS_TODIR) gnuwin32\bin
	
cecho: $(notdir $(CECHO_URL))
	-mkdir gnuwin32
	$(OS_TAR) $(notdir $(CECHO_URL)) $(OS_TODIR) gnuwin32
	copy .\gnuwin32\cecho-master\cecho\bin\Release\cecho.exe .\gnuwin32\bin
	

	

#------------------------------------------------------------------------------------	
clean:
	-$(OS_RM) *.zip *.exe
	-$(OS_RD) mb7707sdk mc5103sdk mc7601sdk nmsdk vshell32 gnuwin32 nm_io
	