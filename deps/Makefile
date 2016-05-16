ROOT = ..
#-include $(ROOT)/environment.mk
-include $(ROOT)/global.mk
#http_proxy ?=http://username:password@proxy:80/

standalone: dev-pack
		
dev-pack: master.zip	
	$(OS_UNPACK) master.zip
	$(OS_MV) dev-pack-master dev-pack
	$(MAKE) -C dev-pack 

master.zip: 
	$(OS_WGET)  https://github.com/RC-MODULE/dev-pack/archive/master.zip
	
	
libeasynmc:
	$(MAKE) -C dev-pack libeasynmc 
	