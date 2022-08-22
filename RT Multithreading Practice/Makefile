CFLAGS= -Wall
CC=gcc
TARGET=RTTest
PI=monteCarloPi

all: $(TARGET) $(PI)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

$(PI): $(PI).c
	$(CC) $(CFLAGS) -o $(PI) $(PI).c
	./$(PI)

clean:
	$(RM) $(TARGET) $(TARGET).o
	$(RM) $(PI) $(PI).o
    