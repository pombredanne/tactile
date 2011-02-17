CFLAGS += -O2 -Wall
LDFLAGS += -s

tactile: tactile.o

clean:
	rm -f tactile tactile.o
