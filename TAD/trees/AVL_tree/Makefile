CFLAGS = -Wall -Werror
TARGET = avl
OBJECTFILES = avl.o main.o

all: $(TARGET)

$(TARGET): $(OBJECTFILES)
	gcc $(CFLAGS) -o $(TARGET) $(OBJECTFILES)

clean:
	rm $(TARGET) $(OBJECTFILES)

debug:
	gcc $(CFLAGS) -g $(CFILES)

run:
	./$(TARGET)

runMem:
	valgrind ./$(TARGET)

zip:
	@zip -r Operacoes.zip *.c *.h Makefile
	