call "%VS80COMNTOOLS%..\..\vc\bin\vcvars32
nmcc nmpart.cpp -cnm1board.cfg nm1lib.lib -g
cl host.cpp "%NEURO%\libload\emuload.lib" -I"%NEURO%\libload" /MT
