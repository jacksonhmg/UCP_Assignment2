CC = gcc -g
CFLAGS = -Wall -pedantic -ansi
OBJ = main.o setup.o gameloop.o terminal.o checkers.o random.o
EXEC = escape

ifdef BORDERLESS
CFLAGS += -D BORDERLESS
DEBUG : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c setup.h random.h
	$(CC) $(CFLAGS) -c main.c

setup.o : setup.c setup.h macros.h gameloop.h checkers.h
	$(CC) $(CFLAGS) -c setup.c

gameloop.o : gameloop.c gameloop.h checkers.h random.h
	$(CC) $(CFLAGS) -c gameloop.c

terminal.o : terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

checkers.o : checkers.c checkers.h
	$(CC) $(CFLAGS) -c checkers.c

random.o : random.c random.h
	$(CC) $(CFLAGS) -c random.c

clean:
	rm -f $(EXEC) $(OBJ)