ROOT = ..

-include $(ROOT)/proxy.mk
-include $(ROOT)/global.mk

OS_WGET  = wget -nc --no-check-certificate --content-disposition 
OS_UNZIP = unzip -u -o -q 
   
$(info $(http_proxy))   
#http_proxy ?=http://username:password@proxy:80/

download: dev-kit-master.zip

install: install-nmc

install-nmc: dev-kit-master
	$(MAKE) -C dev-kit-master nmsdk boards nm_io NOPROXY=$(NOPROXY)

install-arm: 
	$(MAKE) -C dev-kit-master install-arm NOPROXY=$(NOPROXY)

standalone: dev-kit
	
dev-kit-master: dev-kit-master.zip	
	$(OS_UNZIP) dev-kit-master.zip	

dev-kit-master.zip:
	$(OS_WGET)  https://github.com/RC-MODULE/dev-kit/archive/master.zip
	
clean:
	-$(OS_RM) *.zip *.exe *.tgz *.tar *.gz
	-$(OS_RD) dev-kit-master
	
#libeasynmc:
#	$(MAKE) -C dev-kit libeasynmc 
	