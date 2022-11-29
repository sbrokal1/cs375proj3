OBJS	= main.o
SOURCE	= main.cpp
HEADER	= 
OUT	= proj3
CC	 = g++
FLAGS	 = -g3 -c -Wall
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

proj3: clean all

main.o: src/main.cpp
	$(CC) $(FLAGS) src/main.cpp 

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT) $(ARGS)

debug: $(OUT)
	valgrind $(OUT)

valgrind: $(OUT)
	valgrind $(OUT)

valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)