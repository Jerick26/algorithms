IDIR =.
CC = clang++ 
CFLAGS = -I$(IDIR) -std=c++11 -stdlib=libc++ -g -Wno-c++98-compat

ODIR = obj
#LDIR =../lib

#LIBS=-lm  // include match library

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
