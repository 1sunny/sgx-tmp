# Define compiler and flags
CC = gcc
CFLAGS = -Wall -g -O0

# Define source files and object files
SOURCES = alloc.c commonio.c fputsx.c gpasswd.c groupio.c groupmem.c gshadow.c memzero.c sgroupio.c list.c \
          fields.c basename.c sgetgrent.c get_gid.c salt.c encrypt.c print.c


OBJECTS = $(SOURCES:.c=.o)

# Define the executable file
EXECUTABLE = gpasswd

# Default target
all: $(EXECUTABLE)

# Link object files to create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lcrypt

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean up
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)