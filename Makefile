CC				= clang
CFLAGS		= -Wall -Wextra -pedantic -g
LDFLAGS		= -lm -lz -std=gnu99
OBJFILES	= emwa.o parser.o util.o
TARGET		= emwa-bin

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -rf $(OBJFILES) $(TARGET) *~

install:
	cp emwa-bin /usr/local/bin/emwa
