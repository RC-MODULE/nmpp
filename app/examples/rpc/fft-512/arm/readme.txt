1. Build arm and nmc projects by 'make' from current (./arm ) folder
2. Upload binaries (./arm/rpc-demo and  ./nmc/rpc-demo.abs) to ./root at MB7707 by 'make upload'
3. Connect to MB7707 by PUTTY through SSH 192.168.20.9 port 22 [admin@12345678]
4. Change attribute 'chmod +x ./rpc-demo'
5. Execute './rpc-demo'

If start is successfull  output should  be like that :

root@shade:~# ./rpc-demo
START-0.1.2 a21bb1b79a42372469cdfa530c650b36f974f0c6 @2a4da6ea4758 built on 28/04/16
Attaching .easynmc_stdin io buffer size 128 words @ 0x167a0
Attaching .easynmc_stdout io buffer size 128 words @ 0x169b0
START-1
NMC: Aura RPC demo
START-2
1970.01.07-00:03:20 - [INFO]  ARM: Call nmppsCmpNe_8s8um -ok
1970.01.07-00:03:20 - [INFO]  ARM: Call nmppsCmpNe_16s8um -ok
1970.01.07-00:03:20 - [INFO]  ARM: Call nmppsCmpNe_32s8um -ok
1970.01.07-00:03:20 - [INFO]  ARM: Call nmppsCmpNe_64s8um -ok
1970.01.07-00:03:20 - [INFO]  ARM: Call nmppsCmpLt_16s8um -ok
1970.01.07-00:03:20 - [INFO]  ARM: Call nmppsCmpLt_32s8um -ok
1970.01.07-00:03:20 - [INFO]  ARM: Call nmppsSum_8s -ok
1970.01.07-00:03:20 - [INFO]  ARM: Call nmppsSum_8s -ok
