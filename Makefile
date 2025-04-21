SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = main
CFLAGS = -Wall -Wextra

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
