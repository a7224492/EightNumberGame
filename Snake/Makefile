GCC=gcc
FLAG=-o
TAR=Snake
OBJS=main.o print.o

Snake: create_build $(OBJS)
	$(GCC) $(OBJS) $(FLAG) $(TAR)

main.o: main.c print.o ../common/print.h
	$(GCC) -c main.c

print.o: ../common/print.c ../common/print.h
	$(GCC) -c ../common/print.c

create_build:
	rm build -rf
	mkdir build

clean:
	rm build -rf
	rm $(OBJS)