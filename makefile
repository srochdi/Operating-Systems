CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
TARGET = cpu_scheduler
SRC = cpu_scheduler.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run