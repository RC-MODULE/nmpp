
.SUFFIXES:
ROOT 		= ../../../../..
include 	$(ROOT)/global.mk

TARGET  	=  rpc-demo
CC_FLAGS 	= \
	-march=armv6 -mtune=arm1176jz-s -mfpu=vfp -mfloat-abi=hard -marm \
	--sysroot=$(ROOTFS) \
	-D_GNU_SOURCE \
	-I$(ARMTOOLCH)/arm-rcm-linux-gnueabihf/libc/usr/include/arm-linux-gnueabihf/aura-0.1.2 \
	-I$(ARMTOOLCH)/arm-rcm-linux-gnueabihf/libc/usr/include \
	-I$(ARMTOOLCH)/arm-rcm-linux-gnueabihf/libc/usr/include/arm-linux-gnueabihf \
    -I$(ROOT)/include \
    -I$(ROOT)/include/rpc


LD_FLAGS = \
	-march=armv6 -mtune=arm1176jz-s -mfpu=vfp -mfloat-abi=hard -marm \
	-Wl,--sysroot=$(ARMTOOLCH) \
	-Wl,-unresolved-symbols=ignore-in-shared-libs \
	-Wl,-L$(ARMTOOLCH)/lib \
	-Wl,-L$(ARMTOOLCH)/lib/arm-rcm-linux-gnueabihf \
	-Wl,-L$(ARMTOOLCH)/usr/lib/arm-rcm-linux-gnueabihf \
	-Wl,-L$(NMPP)/lib 

#VPATH    = $(AURA) $(AURA)/nmc-utils
ALL_C    = ./main-arm.c 
OBJECTS_C= $(notdir $(patsubst %.c,%.o,$(ALL_C)))


all: $(TARGET) nmc

nmc:
	$(MAKE) -C ../nmc
	
lib: 
	$(MAKE) -C $(ROOT)/make rpc


upload: ./$(TARGET) ../nmc/rpc-demo.abs
	pscp -pw 12345678 ../nmc/rpc-demo.abs root@192.168.20.9: 
	pscp -pw 12345678 ./$(TARGET) root@192.168.20.9: 

upload2: ./$(TARGET) ./arm-demo nmc
	pscp -pw 12345678 ../nmc/rpc-demo.abs root@192.168.20.9: 
	pscp -pw 12345678 ./$(TARGET) root@192.168.20.9: 
	pscp -pw 12345678 ./arm-demo  root@192.168.20.9: 
	
run: 
	putty -ssh 192.168.20.9 -l root -pw 12345678 -m run.putty -t
	
%.o: %.c 
	$(ARM_CC) $(CC_FLAGS) -c $(<) -o$(@) $(INC_DIRS) 

$(TARGET): $(OBJECTS_C) $(ROOT)/lib/libnmpp-arm-rpc.a
	$(ARM_CC) -o $(@)  $(LD_FLAGS) $(OBJECTS_C) -laura -lnmpp-arm-rpc -lnmpp-arm

arm-demo: $(OBJECTS_C) $(ROOT)/lib/libnmpp-arm-rpc.a
	$(ARM_CC) -o $(@)  $(LD_FLAGS) $(OBJECTS_C) -laura -lnmpp-arm

	
$(ROOT)/lib/libnmpp-arm-rpc.a:
		$(MAKE) -C $(ROOT)/make/nmpp-arm-rpc

clean:
	-$(OS_RM) *.o $(TARGET) arm-demo
	$(MAKE) -C ../nmc clean

#	make -cd nmc-utils && make clean

#rpc-demo uses VFP register arguments, main-arm.o does not

	
