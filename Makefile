# CC = gcc
# CFLAGS = -g -Wall -lpthread -lm
# TARGET = main
# SRCS = src/main
#
# all: $(TARGET)
#
# $(TARGET): src/main.c
# 	$(CC) $(CFLAGS) -o $(SRCS).c
#
# clean:
# 	$(RM) $(TARGET)

all:
	gcc -g -Wall -o main src/main.c -lm -lpthread
