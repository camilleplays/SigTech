CC = gcc

CFLAGS =

# Utility routines
UTIL_OBJS += taus.o fixed_point.o rangen_double.o

#

all: fft fft2

OBJ = $(UTIL_OBJS)
$(OBJ) : %.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

fft.o: fft.c
	$(CC)  -c fft.c -o fft.o $(CFLAGS)

fft2.o: fft2.c
	$(CC)  -c fft2.c -o fft2.o $(CFLAGS)

fft: $(OBJ) fft.o
	$(CC)  $(OBJ) fft.o -o fft -lm

fft2: $(OBJ) fft2.o
	$(CC)  $(OBJ) fft2.o -o fft2 -lm

clean:
	rm -f *.o
