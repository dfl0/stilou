CC=gcc
CFLAGS=-Wall -Wextra

BINS=demo
OBJS=demo.o
LIBS=-lSDL2

all: $(BINS)

demo: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.c stilou.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINS) $(OBJS)
