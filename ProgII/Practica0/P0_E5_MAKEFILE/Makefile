CC= gcc -Wall

LIBS=

HEADER_FILES_DIR = .

INCLUDES = -I $(HEADER_FILES_DIR)

OUTPUT = main

SRCS = main.c

OBJS = $(SRCS:.c=.o)

$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIBS)

cleanall: clean
	rm -f $(OUTPUT)

clean:
	rm -f *.o *~