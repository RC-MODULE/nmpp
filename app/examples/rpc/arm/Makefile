
.SUFFIXES:
ROOT 		= ../../../..
include 	$(ROOT)/global.mk
TARGET  	=  rpc-demo
CC_FLAGS 	= \
	-marm -march=armv4t -mfloat-abi=hard \
	--sysroot=$(ROOTFS) \
	-D_GNU_SOURCE \
	-I$(ROOTFS)/usr/include/arm-linux-gnueabihf/aura-0.1.2/ \
	-I$(ROOTFS)/usr/include/ \
	-I$(ROOTFS)/usr/include/arm-linux-gnueabihf/ \
	-I$(NMPP)/include 

LD_FLAGS = \
	-marm -march=armv4t -mfloat-abi=hard \
	-Wl,--sysroot=$(ROOTFS) \
	-Wl,-unresolved-symbols=ignore-in-shared-libs \
	-Wl,-L$(ROOTFS)/lib \
	-Wl,-L$(ROOTFS)/lib/arm-linux-gnueabihf \
	-Wl,-L$(ROOTFS)/usr/lib/arm-linux-gnueabihf \
	-Wl,-L$(NMPP)/lib 

#VPATH    = $(AURA) $(AURA)/nmc-utils
ALL_C    = ./main-arm.c 
OBJECTS_C= $(notdir $(patsubst %.c,%.o,$(ALL_C)))


all: $(TARGET) ../nmc/rpc-demo.abs

lib: 
	$(MAKE) -C $(ROOT)/make/nmpp-arm-rpc

upload: ./$(TARGET) ../nmc/rpc-demo.abs
	$(OS_SCP) -pw 12345678 ../nmc/rpc-demo.abs root@192.168.20.9: 
	$(OS_SCP) -pw 12345678 ./$(TARGET) root@192.168.20.9: 

%.o: %.c 
	$(ARM_CC) $(CC_FLAGS) -c $(<) -o$(@) $(INC_DIRS) 

$(TARGET): $(OBJECTS_C) $(ROOT)/lib/libnmpp-arm-rpc.a
	$(ARM_CC) -o $(@)  $(LD_FLAGS) $(OBJECTS_C) -laura -lnmpp-arm-rpc

../nmc/rpc-demo.abs:
	$(MAKE) -C ../nmc

clean:
	-$(OS_RM) *.o $(TARGET)
	$(MAKE) -C ../nmc clean

#	make -cd nmc-utils && make clean

#rpc-demo uses VFP register arguments, main-arm.o does not

	
