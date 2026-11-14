CC = gcc
TARGET = askem
OBJ = main.c
CLIBS = -Wall -w -lm

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CLIBS)

