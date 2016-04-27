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
  NMC_UTILS_URL  = https://github.com/RC-MODULE/nmc-utils/archive/master.zip
  SYSROOT_URL    = http://www.module.ru/mb7707/random/matlab-dev/armhf-sdk-sysroot.tgz
  
 # 3rd party production packages 
  COREUTILS_URL	 = http://sourceforge.net/projects/gnuwin32/files/coreutils/5.3.0/coreutils-5.3.0-bin.zip
  COREDEPS_URL	 = http://sourceforge.net/projects/gnuwin32/files/coreutils/5.3.0/coreutils-5.3.0-dep.zip
  FIND_URL       = https://sourceforge.net/projects/gnuwin32/files/findutils/4.2.20-2/findutils-4.2.20-2-bin.zip
  CECHO_URL 	 = https://github.com/elisherer/cecho/archive/master.zip
  PUTTY_URL      = http://tartarus.org/~simon/putty-snapshots/x86/putty.zip
  # PUTTY's homepage http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html
  
  TAR_URL        = http://downloads.sourceforge.net/project/gnuwin32/tar/1.13-1/tar-1.13-1-bin.zip
  TARDEP_URL     = http://downloads.sourceforge.net/project/gnuwin32/tar/1.13-1/tar-1.13-1-dep.zip
  ZIP7_URL       = http://www.7-zip.org/a/7za920.zip

  SDK_ARM_URL    = https://launchpad.net/linaro-toolchain-binaries/trunk/2013.10/+download/gcc-linaro-arm-linux-gnueabihf-4.8-2013.10_win32.zip
  
  
  NMC_URLS = \
	  $(SDK_MC5103_URL) \
	  $(SDK_MB7707_URL) \
	  $(SDK_MC7601_URL) \
	  $(NMSDK_URL)      \
	  $(NM_IO_URL)      \
	  $(VSHELL32_URL)   \
	  $(VSHELL32_DIST)  
	  
  GNU_URLS =\
	  $(COREUTILS_URL)	 \
	  $(COREDEPS_URL)	 \
	  $(FIND_URL)       \
	  $(CECHO_URL) 	 
  
  ARM_URLS = \
	  $(SYSROOT_URL) \
	  $(NMC_UTILS_URL) \
	  $(PUTTY_URL)	  \
	  $(SDK_ARM_URL) 
	  
  ARC_URLS = \
      $(TAR_URL) \
      $(TARDEP_URL) \
      $(ZIP7_URL) 
      
	   
  
   
  

else
  SDK_MC5103_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mc5103_distrib_v_01_01.tar.gz
  SDK_MB7707_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mb7707_distrib_v_01_00.tar.gz
  NMSDK_URL      = http://www.module.ru/mb7707/toolchains-neuromatrix/nmsdk.tar.gz
  NM_IO_URL      = http://www.module.ru/mb7707/NeuroMatrix/nm_io.zip
  
  NMC_URLS = \
	  $(SDK_MC5103_URL) \
	  $(SDK_MB7707_URL) \
	  $(NMSDK_URL)      \
	  $(NM_IO_URL)      
	
endif
	
PACKAGES_NMC = $(notdir $(NMC_URLS))
PACKAGES_ARM = $(notdir $(ARM_URLS)) 
PACKAGES_GNU = $(notdir $(GNU_URLS))
PACKAGES_ARC = $(notdir $(ARC_URLS))

PACKAGES_GNU:= $(subst master.zip,cecho.zip,$(PACKAGES_GNU))
PACKAGES_ARM:= $(subst master.zip,nmc-utils.zip,$(PACKAGES_ARM))

install-nmc: nmsdk nm_io mc5103sdk mb7707sdk mc7601sdk vshell32 

install-arm: gnuwin32/bin/tar.exe gnuwin32/bin/putty.exe rootfs nmc-utils-master gcc-linaro-arm-linux-gnueabihf-4.8-2013.10_win32 

install-gnu: core-utils gnuwin32/bin/cecho.exe gnuwin32/bin/tar.exe

install-arc: gnuwin32/bin/tar.exe


#------------------------- package downloading of depended URLs --------------------

get-nmc: $(PACKAGES_NMC)

$(PACKAGES_NMC):
	$(OS_WGET) $(NMC_URLS)
	
#.....................................................
get-arm: 	$(PACKAGES_ARM)

$(PACKAGES_ARM): 
	$(OS_WGET) $(ARM_URLS)
	ren master.zip nmc-utils.zip	
	
#.....................................................
get-gnu: 	$(PACKAGES_GNU) $(PACKAGES_ARC)

$(PACKAGES_GNU): 
	$(OS_WGET) $(GNU_URLS) $(ARC_URLS)
	ren master.zip cecho.zip	

#.....................................................
get-arc: 	$(PACKAGES_ARC)

$(PACKAGES_ARC): 
	$(OS_WGET) $(ARC_URLS)

#------------------------- package installation  --------------------

mc5103sdk: $(notdir $(SDK_MC5103_URL))
	-mkdir $(@)
	$(OS_UNPACK) $(<) $(OS_TODIR) $(@)
	
mb7707sdk: $(notdir $(SDK_MB7707_URL))
	-mkdir $(@)
	$(OS_UNPACK) $(<) $(OS_TODIR) $(@) 

mc7601sdk: $(notdir $(SDK_MC7601_URL))
	-mkdir $(@)
	$(OS_UNPACK) $(<) $(OS_TODIR) $(@) 

nmsdk: $(notdir $(NMSDK_URL))
	-mkdir $(@)
	$(OS_UNPACK) $(<) $(OS_TODIR) $(@)

vshell32: $(notdir $(VSHELL32_URL))
	$(OS_UNPACK) $(<) 

nm_io: $(notdir $(NM_IO_URL))
	$(OS_UNPACK) $(<)
	
core-utils: $(notdir $(COREUTILS_URL)) gnuwin32
	$(OS_UNPACK) $(notdir $(COREUTILS_URL)) $(OS_TODIR) gnuwin32
	$(OS_UNPACK) $(notdir $(COREDEPS_URL))  $(OS_TODIR) gnuwin32
	$(OS_UNPACK) $(notdir $(FIND_URL))      $(OS_TODIR) gnuwin32

gnuwin32/bin/putty.exe: $(notdir $(PUTTY_URL)) gnuwin32
	$(OS_UNPACK) $(notdir $(PUTTY_URL)) $(OS_TODIR) gnuwin32\bin
	
gnuwin32/bin/cecho.exe: cecho.zip gnuwin32
	$(OS_UNPACK) cecho.zip $(OS_TODIR) gnuwin32
	copy .\gnuwin32\cecho-master\cecho\bin\Release\cecho.exe .\gnuwin32\bin

gnuwin32/bin/tar.exe: $(PACKAGES_ARC) gnuwin32\bin
	$(OS_UNPACK) $(notdir $(ZIP7_URL))   $(OS_TODIR) gnuwin32\bin
	$(OS_UNPACK) $(notdir $(TAR_URL))  	 $(OS_TODIR) gnuwin32
	$(OS_UNPACK) $(notdir $(TARDEP_URL)) $(OS_TODIR) gnuwin32

rootfs: $(notdir $(SYSROOT_URL))
	-mkdir rootfs
	$(GNUWIN32)/7za  e $(<)
	$(GNUWIN32)/tar  -vxf armhf-sdk-sysroot.tar -C rootfs
	
nmc-utils-master: nmc-utils.zip
	$(OS_UNPACK) nmc-utils.zip 
	
gcc-linaro-arm-linux-gnueabihf-4.8-2013.10_win32: $(nodir $(SDK_ARL_URL))
	$(GNUWIN32)/7za  e $(<)

gnuwin32\bin:
	-mkdir gnuwin32
	-mkdir gnuwin32\bin

gnuwin32:	
	-mkdir gnuwin32
#------------------------------------------------------------------------------------	
clean:
	-$(OS_RM) *.zip *.exe
	-$(OS_RD) mb7707sdk mc5103sdk mc7601sdk nmsdk vshell32 gnuwin32 nm_io
	