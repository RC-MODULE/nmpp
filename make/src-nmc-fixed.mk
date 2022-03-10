DIRS+=$(ROOT)/src/fixed/image/Arithmetics 
DIRS+=$(ROOT)/src/fixed/image/Convert 
DIRS+=$(ROOT)/src/fixed/image/Filtration 
DIRS+=$(ROOT)/src/fixed/image/Floodfill 
DIRS+=$(ROOT)/src/fixed/image/Init 
DIRS+=$(ROOT)/src/fixed/image/Plessy 
DIRS+=$(ROOT)/src/fixed/image/Print 
DIRS+=$(ROOT)/src/fixed/image/Reodering 
DIRS+=$(ROOT)/src/fixed/image/Resample 
DIRS+=$(ROOT)/src/fixed/image/Select 
DIRS+=$(ROOT)/src/fixed/image/Support 

DIRS+=$(ROOT)/src/fixed/matrix/core 
DIRS+=$(ROOT)/src/fixed/matrix/init 
DIRS+=$(ROOT)/src/fixed/matrix/linear 
DIRS+=$(ROOT)/src/fixed/matrix/metric 

DIRS+=$(ROOT)/src/fixed/signal/arithmetic 
DIRS+=$(ROOT)/src/fixed/signal/conditional 
DIRS+=$(ROOT)/src/fixed/signal/conversion 
DIRS+=$(ROOT)/src/fixed/signal/core 
DIRS+=$(ROOT)/src/fixed/signal/correlation 
DIRS+=$(ROOT)/src/fixed/signal/filtering 
DIRS+=$(ROOT)/src/fixed/signal/init 
DIRS+=$(ROOT)/src/fixed/signal/logical 
DIRS+=$(ROOT)/src/fixed/signal/reordering 
DIRS+=$(ROOT)/src/fixed/signal/sampling 
DIRS+=$(ROOT)/src/fixed/signal/statistical 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/FFT0016 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/FFT0032 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/FFT0064 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/FFT0128 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/FFT0256 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/FFT0512 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/FFT2048 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/FFT4096 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/FFT8192 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/IFFT0256 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/IFFT0512 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/IFFT1024 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/IFFT2048 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/IFFT4096 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/IFFT8192 
DIRS+=$(ROOT)/src/fixed/signal/transform/fft/FFTFree 


















INC_DIRS         = -I../../include
INC_DIRS+= -I../../include/nmpps

SRC_DIRS         = 	 \
					$(ROOT)/src/nmplc/arithmetic/common \
					$(ROOT)/src/nmplc/fixpoint32/nm \
					$(ROOT)/src/nmplc/fixpoint64/nm \
					$(ROOT)/src/nmplc/init/common \
					$(ROOT)/src/nmplc/integer/nm \
					$(ROOT)/src/nmpli/Arithmetics/nm \
					$(ROOT)/src/image/Convert/common \
					$(ROOT)/src/image/Convert/nm \
					$(ROOT)/src/image/Filtration/common \
					$(ROOT)/src/image/Filtration/nm \
					$(ROOT)/src/image/Floodfill/common \
					$(ROOT)/src/image/Floodfill/nm \
					$(ROOT)/src/image/Init/common \
					$(ROOT)/src/image/Print/nm \
					$(ROOT)/src/image/Reodering/nm \
					$(ROOT)/src/image/Resample/common \
					$(ROOT)/src/image/Resample/nm \
					$(ROOT)/src/image/Select/nm \
					$(ROOT)/src/image/Select/common \
					$(ROOT)/src/image/Support/common \
					$(ROOT)/src/nmplm/Core/nm \
					$(ROOT)/src/matrix/Init/nm \
					$(ROOT)/src/matrix/Inverse/common \
					$(ROOT)/src/matrix/MatrixVector/nm \
					$(ROOT)/src/matrix/Support/common \
					$(ROOT)/src/matrix/Stat/common \
					$(ROOT)/src/nmpls/Correlation/nm \
					$(ROOT)/src/nmpls/Metric \
					$(ROOT)/src/signal/FFT/common \
					$(ROOT)/src/signal/FFT/FFT0016/nm \
					$(ROOT)/src/signal/FFT/FFT0016/common \
					$(ROOT)/src/signal/FFT/FFT0032/nm \
					$(ROOT)/src/signal/FFT/FFT0032/common \
					$(ROOT)/src/signal/FFT/FFT0064/nm \
					$(ROOT)/src/signal/FFT/FFT0064/common \
					$(ROOT)/src/signal/FFT/FFT0256/nm \
					$(ROOT)/src/signal/FFT/FFT0256/common \
					$(ROOT)/src/signal/FFT/FFT0512/nm \
					$(ROOT)/src/signal/FFT/FFT0512/common \
					$(ROOT)/src/signal/FFT/FFT1024/nm \
					$(ROOT)/src/signal/FFT/FFT1024/common \
					$(ROOT)/src/signal/FFT/FFT2048/nm \
					$(ROOT)/src/signal/FFT/FFT2048/common \
					$(ROOT)/src/signal/FFT/FFT4096/nm \
					$(ROOT)/src/signal/FFT/FFT8192/nm \
					$(ROOT)/src/signal/FFT/FFT8192/common \
					$(ROOT)/src/signal/FFT/IFFT0256/nm \
					$(ROOT)/src/signal/FFT/IFFT0512/nm \
					$(ROOT)/src/signal/FFT/IFFT1024/nm \
					$(ROOT)/src/signal/FFT/IFFT2048/common \
					$(ROOT)/src/signal/FFT/IFFT2048/nm \
					$(ROOT)/src/signal/FFT/IFFT4096/nm \
					$(ROOT)/src/signal/FFT/IFFT8192/nm \
					$(ROOT)/src/signal/FFT/IFFT8192/common \
					$(ROOT)/src/signal/FFT/FFTFree/common \
					$(ROOT)/src/signal/Filtration/nm \
					$(ROOT)/src/signal/Filtration/common \
					$(ROOT)/src/signal/Resample/common \
					$(ROOT)/src/signal/Resample/nm \
					$(ROOT)/src/nmplv/Arithmetics/common \
					$(ROOT)/src/nmplv/Arithmetics/nm \
					$(ROOT)/src/nmplv/Bitwise/nm \
					$(ROOT)/src/nmplv/Init/common \
					$(ROOT)/src/nmplv/Init/nm \
					$(ROOT)/src/nmplv/Select/common \
					$(ROOT)/src/nmplv/Select/nm \
					$(ROOT)/src/nmplv/Stat/common \
					$(ROOT)/src/nmplv/Stat/nm \
					$(ROOT)/src/nmplv/Support/nm \
					$(ROOT)/src/nmplv/Support/common \
					$(ROOT)/src/nmplv/Tables/nm \
					$(ROOT)/src/nmplv/Transform/common \
					$(ROOT)/src/nmplv/Transform/nm \
					$(ROOT)/src/nmvcore/nm  \
					$(ROOT)/src/nmplv/Init/nm-risc
					
					
#SRC_DIRS+= $(ROOT)/src/nmpps/arithmetic
#SRC_DIRS+= $(ROOT)/src/nmpps/atan
#SRC_DIRS+= $(ROOT)/src/nmpps/blackman
#SRC_DIRS+= $(ROOT)/src/nmpps/common
#SRC_DIRS+= $(ROOT)/src/nmpps/conversion
#SRC_DIRS+= $(ROOT)/src/nmpps/cos
#SRC_DIRS+= $(ROOT)/src/nmpps/div
#SRC_DIRS+= $(ROOT)/src/nmpps/exp
#SRC_DIRS+= $(ROOT)/src/nmpps/initialization
#SRC_DIRS+= $(ROOT)/src/nmpps/kaiser
#SRC_DIRS+= $(ROOT)/src/nmpps/norm
#SRC_DIRS+= $(ROOT)/src/nmpps/normalize
#SRC_DIRS+= $(ROOT)/src/nmpps/phase
#SRC_DIRS+= $(ROOT)/src/nmpps/random
#SRC_DIRS+= $(ROOT)/src/nmpps/shift
#SRC_DIRS+= $(ROOT)/src/nmpps/sort
#SRC_DIRS+= $(ROOT)/src/nmpps/sqrt
#SRC_DIRS+= $(ROOT)/src/nmpps/statistical
#SRC_DIRS+= $(ROOT)/src/nmpps/threshold
#SRC_DIRS+= $(ROOT)/src/nmpps/windowing
#SRC_DIRS+= $(ROOT)/src/nmpps/polar
#SRC_DIRS+= $(ROOT)/src/nmpps/powerspectr
#SRC_DIRS+= $(ROOT)/src/nmpps/winhamming
#SRC_DIRS+= $(ROOT)/src/nmpps/add
#SRC_DIRS+= $(ROOT)/src/nmpps/mul
#SRC_DIRS+= $(ROOT)/src/nmpps/sub
					