CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O3 -s
LFLAGS = -lconio -static-libgcc
INCLUDE = -IC:\libs\mingw\include
LIBS = -LC:\libs\mingw\lib 
OBJS = ai.o board.o draw.o game.o input.o random.o timer.o main.o
EXEC = tictactoe.exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $+ -o $@ $(LIBS) $(LFLAGS)
	strip -s -x $(EXEC)
	echo "Built: $(EXEC)"

%.o: %.c
	$(CC) -c $(INCLUDE) $(LIBS) $<

ai.o: ai.h ai.c
board.o: board.h board.c
draw.o: draw.h draw.c
game.o: game.h game.c
input.o: input.h input.c
random.o: random.h random.c
timer.o: timer.h timer.c
main.o: main.c

clean:
		del *.o

.PHONY: clean
