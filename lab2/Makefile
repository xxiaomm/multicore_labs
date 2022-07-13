GCC_BIN=gcc
GCC_STD=c99

.PHONY: clean

all: genprime

genprime: genprime.c
	$(GCC_BIN) -g -fopenmp -Wall -o genprime -std=$(GCC_STD) genprime.c -lm
