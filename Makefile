CC = gcc
CFLAGS = -Wall -Werror `pkg-config --cflags gobject-2.0 gtk+-2.0 gthread-2.0`
LDFLAGS = -g -O0 `pkg-config --libs gobject-2.0 gtk+-2.0 gthread-2.0` 
OBJECTS = $(SOURCES:.c=.o)
BUILD = teuthida 
SOURCES = main.c \
	  t-canvas.c \
	  teuthida-main.c

all: $(SOURCES) $(BUILD)

$(BUILD): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

install:
	cp $(BUILD) /usr/bin/

clean:
	rm -rf *.o
	rm -rf $(BUILD)
	
