# Compiler & Flags
CC = gcc
CFLAGS = -Wall -std=c99 -pthread -g

# Zielprogramme
TARGET = new_wc
TEST_TARGET = test_wc

# Quellcode-Dateien für das Hauptprogramm
SRC = src/main.c src/wc_functions.c
OBJ = $(SRC:.c=.o)

# Testdateien
TEST_SRC = tests/test_args.c tests/test_wc_functions.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_FLAGS = -lcriterion

# Standardziel: `new_wc` kompilieren
all: $(TARGET)

# Hauptprogramm kompilieren
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Objektdateien kompilieren
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Unit Tests kompilieren
$(TEST_TARGET): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(OBJ) $(TEST_OBJ) $(TEST_FLAGS)

# Tests ausführen
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean-Befehl: Löscht alle kompilierten Dateien
clean:
	rm -f $(OBJ) $(TARGET) $(TEST_TARGET) $(TEST_OBJ)
