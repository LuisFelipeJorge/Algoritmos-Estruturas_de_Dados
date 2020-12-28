CFLAGS = -Wall -Werror
TARGET = list
OBJECTFILES = list.o main.o

all: $(TARGET)

$(TARGET): $(OBJECTFILES)
	gcc $(CFLAGS) -o $(TARGET) $(OBJECTFILES) -lm

clean:
	rm $(TARGET) $(OBJECTFILES)

run:
	./$(TARGET)

runMem:
	valgrind ./$(TARGET)

zip:
	@zip -r Operacoes.zip *.c *.h Makefile
	