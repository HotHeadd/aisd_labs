TARGET = dops
CC = gcc

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
CFLAGS = -g -lm -lreadline

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm *.o $(TARGET)
	rm vgcore*
