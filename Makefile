# SRCS = $(wildcard *.c)
# OBJS = $(SRCS:.c=.o)
# TARGET = main
# CFLAGS = -Wall -Wextra

# $(TARGET): $(OBJS)
	# $(CC) $(OBJS) -o $(TARGET)

# %.o: %.c
	# $(CC) $(CFLAGS) -c $< -o $@

# .PHONY: clean run

# run: $(TARGET)
	# ./$(TARGET)

# clean:
	# rm -f $(OBJS) $(TARGET)
	#
run:
	clang main.c chunk.c debug.c memory.c value.c vm.c -o main;
	./main
