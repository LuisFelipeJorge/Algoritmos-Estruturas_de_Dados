CFLAGS = -Wall -Werror
TARGET = backward
OBJECTFILES = backward.o main.o

all: $(TARGET)

$(TARGET): $(OBJECTFILES)
	gcc $(CFLAGS) -o $(TARGET) $(OBJECTFILES)

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

runTest:
	./$(TARGET) < tests/2.in

runTestMem:
	valgrind ./$(TARGET) < tests/1.in

zip:
	@zip -r Operacoes.zip *.c *.h Makefile
	