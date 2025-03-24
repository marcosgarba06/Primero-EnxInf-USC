CC= gcc -Wall

LIBS=

HEADER_FILES_DIR = .

INCLUDES = -I$(HEADER_FILES_DIR)

OUTPUT = main

LIB_HEADERS = $(HEADER_FILES_DIR)operaciones.h

SRCS = main.c gcd.c sqrt.c

OBJS = $(SRCS:.c=.o)

$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIBS)

%.o: %.c $(LIB_HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)

cleanall: clean
	rm -f $(OUTPUT)

clean:
	rm -f *.o *~