CC=g++
CFLAGS=-I.
DEPS = data.h solver.h
OBJ = main.o data.o solver.o

%.o: %.c $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

exact_cover: $(OBJ)
	$(CC) -o exact_cover.so $^ $(CFLAGS)

.PHONY : clean

clean :
	rm -f exact_cover *.o *.d
	rm -f exact_cover.so
