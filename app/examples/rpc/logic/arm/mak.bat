d:/SDK/arm-module-linux-gnueabi/bin/arm-module-linux-gnueabi-gcc -Id:/GIT/matlab/rootfs-debian-jessie/usr/include/arm-linux-gnueabi/aura-0.1.2/  -I d:/GIT/matlab/rootfs-debian-jessie/usr/include/easynmc-0.1.1 -I d:/GIT/matlab/rootfs-debian-jessie/usr/include/arm-linux-gnueabi -I d:/GIT/matlab/rootfs-debian-jessie/usr/include/arm-linux-gnueabi/aura-0.1.2 -c main-arm.c -o main-arm.o -I%NMPP%/include
rem d:/SDK/arm-module-linux-gnueabi/bin/arm-module-linux-gnueabi-gcc main-arm.o -o test -Wl,--whole-archive d:/GIT/matlab/rootfs-debian-jessie/usr/lib/arm-linux-gnueabi/libaura.a -Wl,--no-whole-archive d:/GIT/matlab/rootfs-debian-jessie/usr/lib/arm-linux-gnueabi/liblua5.2.a d:/GIT/matlab/rootfs-debian-jessie/usr/lib/arm-linux-gnueabi/libusb-1.0.a d:\GIT\matlab\rootfs-debian-jessie\usr\lib\libeasynmc.a -lm -lelf -lpthread -ldl -ludev -lnmpp-arm-rpc -L%NMPP%/lib 

d:/SDK/arm-module-linux-gnueabi/bin/arm-module-linux-gnueabi-gcc main-arm.o -o test -L d:/GIT/matlab/rootfs-debian-jessie/lib/arm-linux-gnueabi/ -L d:/GIT/matlab/rootfs-debian-jessie/usr/lib/ -L d:/GIT/matlab/rootfs-debian-jessie/usr/lib/arm-linux-gnueabi -l:libaura.so.1 -l:liblua5.2.so.0.0.0 -l:libusb-1.0.so.0.1.0 -l:libeasynmc.so.0.1.1 -lnmpp-arm-rpc -L%NMPP%/lib 

  