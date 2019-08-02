CC=g++
FLAG=-o
TAR=Snake
OBJS=main.o print.o snake.o

Snake: create_build $(OBJS)
	$(CC) -g $(OBJS) $(FLAG) $(TAR)

main.o: main.cpp
	$(CC) -c -g main.cpp

print.o: ../common/view/print.c
	$(CC) -c -g ../common/view/print.c

snake.o: snake.cpp
	$(CC) -c -g snake.cpp

create_build:
	rm build -rf
	mkdir build

clean:
	rm build -rf
	rm -f $(OBJS)
	rm -f $(TAR)