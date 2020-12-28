CFLAGS = -Wall -Werror
TARGET = skip
OBJECTFILES = skip.o main.o
CFILES = skip.c main.c

all: $(TARGET)

$(TARGET): $(OBJECTFILES)
	gcc $(CFLAGS) -g -o $(TARGET) $(OBJECTFILES)

debug: 
	gcc $(CFLAGS) -g $(CFILES)

clean:
	rm $(TARGET) $(OBJECTFILES)

run:
	./$(TARGET)

runMem:
	valgrind ./$(TARGET)

zip:
	@zip -r Operacoes.zip *.c *.h Makefile
	