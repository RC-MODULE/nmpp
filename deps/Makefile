ROOT = ..

-include proxy.mk
-include $(ROOT)/global.mk

OS_WGET  = wget -nc --no-check-certificate --content-disposition 
OS_UNZIP = unzip -u -o -q 
   
#http_proxy ?=http://username:password@proxy:80/

download: dev-pack-master.zip

install-nmc: dev-pack-master
	$(MAKE) -C dev-pack-master install-nmc

install-arm: 
	$(MAKE) -C dev-pack-master install-arm 

standalone: dev-pack
	
dev-pack-master: dev-pack-master.zip	
	$(OS_UNZIP) dev-pack-master.zip	

dev-pack-master.zip:
	$(OS_WGET)  https://github.com/RC-MODULE/dev-pack/archive/master.zip
	
clean:
	-$(OS_RM) *.zip *.exe *.tgz *.tar *.gz
	-$(OS_RD) dev-pack-master
	
#libeasynmc:
#	$(MAKE) -C dev-pack libeasynmc 
	