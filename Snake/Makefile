GCC=gcc
SRC=main.c
FLAG=-o
TAR=build/Snake

all: create_build
	$(GCC) $(SRC) $(FLAG) $(TAR)

create_build: clean
	mkdir build

clean:
	rm build -rf