GCC_BIN=gcc
GCC_STD=c99

.PHONY: clean

all:  random-num xm2074seq xm2074ver1 xm2074ver2

random-num: random-num.c
	$(GCC_BIN) -Wall -o random-num -std=$(GCC_STD) random-num.c

xm2074seq: xm2074seq.c
	$(GCC_BIN) -Wall -o xm2074seq -std=$(GCC_STD) xm2074seq.c

xm2074ver1: xm2074ver1.c
	$(GCC_BIN) -fopenmp -Wall -o xm2074ver1 -std=$(GCC_STD) xm2074ver1.c

xm2074ver2: xm2074ver2.c
	$(GCC_BIN) -fopenmp -Wall -o xm2074ver2 -std=$(GCC_STD) xm2074ver2.c -lm

#clean:
#	rm -f random-num seq ver1 ver2
