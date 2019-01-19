CC = gcc

CFLAGS = -Wall\
	-DUNIT_TEST\
	-I../inc/
CUNIT = -lcunit

vpath %.c ../src

SRC := ring.c unittest.c

OBJ := $(SRC:.c=.o)

unittest: $(OBJ)
	$(CC) -o unittest $(OBJ) $(CFLAGS) $(CUNIT)

clean:
	rm -f *.o unittest 
