CFLAGS = -Wall -Werror
TARGET = big
OBJECTFILES = big.o main.o

all: $(TARGET)

$(TARGET): $(OBJECTFILES)
	gcc $(CFLAGS) -o $(TARGET) $(OBJECTFILES)

clean:
	rm $(TARGET) $(OBJECTFILES)

run:
	./$(TARGET) < tests/1.in
	./$(TARGET) < tests/2.in
	
runMem:
	valgrind ./$(TARGET) < tests/1.in
	valgrind ./$(TARGET) < tests/2.in

runTest:
	./$(TARGET) < tests/1.in

runTestMem:
	valgrind ./$(TARGET) < tests/1.in

zip:
	@zip -r Operacoes.zip *.c *.h Makefile
	