CC=gcc
CFILES=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(CFILES))
TARGET=course

all: clean $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
	@rm -rf ./*.o

%.o:%.c
	$(CC) $< -c -o $@

.PHONY:clean
clean:
	@rm -rf $(TARGET)
