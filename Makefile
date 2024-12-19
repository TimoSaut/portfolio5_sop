CC = ggc
CFLAGS = -wall -std=c99

TARGET = new_wc

SRC = src/main.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(OBJ): ($SRC)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(TARGET)