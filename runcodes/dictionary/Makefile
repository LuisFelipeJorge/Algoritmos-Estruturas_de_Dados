CFLAGS = -Wall -Werror
TARGET = dictionary
OBJECTFILES = dictionary.o main.o
CFILES = dictionary.c main.c

all: $(TARGET)

$(TARGET): $(OBJECTFILES)
	gcc $(CFLAGS) -g -o $(TARGET) $(OBJECTFILES)

debug:
	gcc $(CFLAGS) -g $(CFILES)

clean:
	rm $(TARGET) $(OBJECTFILES)

run:
	./$(TARGET) < tests/1.in
	./$(TARGET) < tests/2.in
	./$(TARGET) < tests/3.in
	./$(TARGET) < tests/4.in
	./$(TARGET) < tests/5.in

runMem:
	valgrind ./$(TARGET) < tests/1.in
	valgrind ./$(TARGET) < tests/2.in
	valgrind ./$(TARGET) < tests/3.in
	valgrind ./$(TARGET) < tests/4.in
	valgrind ./$(TARGET) < tests/5.in

zip:
	@zip -r Operacoes.zip *.c *.h Makefile
	