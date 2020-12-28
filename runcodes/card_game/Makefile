CFLAGS = -Wall -Werror
TARGET = card_game
OBJECTFILES = card_game.o main.o

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
	./$(TARGET) < tests/6.in

runMem:
	valgrind ./$(TARGET) < tests/1.in
	valgrind ./$(TARGET) < tests/2.in
	valgrind ./$(TARGET) < tests/3.in
	valgrind ./$(TARGET) < tests/4.in
	valgrind ./$(TARGET) < tests/5.in
	valgrind ./$(TARGET) < tests/6.in

zip:
	@zip -r Operacoes.zip *.c *.h Makefile
	