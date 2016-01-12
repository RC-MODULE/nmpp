
.SUFFIXES:
ROOT = ../../../..
include $(ROOT)/setenv.mk


INC_DIRS+= -I$(NMPP)/include
INC_DIRS+= -I$(AURA)/include -I$(AURA)/nmc-utils/include
INC_DIRS+= -DLIBEASYNMC_VERSION=\"0.1.1\"
#INC_DIRS+= -I/home/mushkaev/matlab/linux-3.10.x/include/uapi
#INC_DIRS+= -I/home/mushkaev/matlab/linux-3.10.x/drivers/staging/android/uapi
#INC_DIRS+= -I/include/uapi
#INC_DIRS+= -I/drivers/staging/android/uapi
INC_DIRS+= -I./include  -I./include/linux

TARGET  =  rpc-demo

CC_FLAGS = -g -Wall -fPIC $(INC_DIRS) -pg
LD_FLAGS+=-rdynamic -g  -lelf -L$(ROOT)/lib -lnmpp-arm-rpc -pg

#-L$(NMPP)/lib
#INC_DIRS+= -I$(NMPP)/include
#SRC_DIRS = . ./aura 
#ALL_C    = $(wildcard $(addsuffix /*.c,$(SRC_DIRS)))

VPATH    = $(AURA) $(AURA)/nmc-utils




ALL_C   = ./main-arm.c 
ALL_C   += ./test.c 
ALL_C   += $(AURA)/aura.c 
ALL_C   += $(AURA)/buffer.c 
ALL_C   += $(AURA)/buffer-dummy.c 
ALL_C   += $(AURA)/eventloop.c 
ALL_C   += $(AURA)/eventsys-epoll.c 
ALL_C   += $(AURA)/export.c 
ALL_C   += $(AURA)/ion.c 
ALL_C   += $(AURA)/panic.c 
ALL_C   += $(AURA)/queue.c 
ALL_C   += $(AURA)/retparse.c 
ALL_C   += $(AURA)/serdes.c 
ALL_C   += $(AURA)/slog.c 
ALL_C   += $(AURA)/transport.c 
ALL_C   += $(AURA)/transport-dummy.c 
ALL_C   += $(AURA)/transport-nmc.c 
ALL_C   += $(AURA)/utils.c 
ALL_C   += $(AURA)/utils-linux.c 
ALL_C   += $(AURA)/nmc-utils/easynmc-core.c
ALL_C   += $(AURA)/nmc-utils/easynmc-filters.c


OBJECTS_C= $(notdir $(patsubst %.c,%.o,$(ALL_C)))



all : rpc $(TARGET)
	$(MAKE) -C ../nmc

rpc:
	$(MAKE) -C $(ROOT)/make/nmpp-arm-rpc
	
upload:
	scp ../nmc/rpc-demo.abs root@192.168.20.9:
	scp ./$(TARGET) root@192.168.20.9:


%.o: %.c 
	$(ARM_CC) $(CC_FLAGS) -c $(<) -o$(@) $(INC_DIRS) 


$(TARGET): $(OBJECTS_C) $(ROOT)/lib/libnmpp-arm-rpc.a
	$(ARM_CC) -o $(@) $(OBJECTS_C) $(LD_FLAGS)


clean:
	-$(OS_RM) *.o $(TARGET)
	-cd nmc-utils && make clean

#	$(MAKE) -C ../nmc clean

	
