CC = gcc
CCFLAGS = -W -Wall

INCLUDES_PATH = Includes
SOURCES_PATH = Sources

BINARY = Tic_Tac_Toe
SOURCES = $(SOURCES_PATH)/Grid.c $(SOURCES_PATH)/Interface.c $(SOURCES_PATH)/Main.c

release: CCFLAGS += -O3
release: all

debug: CCFLAGS += -DDEBUG -g
debug: all

all:
	$(CC) $(CCFLAGS) $(SOURCES) -I$(INCLUDES_PATH) -o $(BINARY)

clean:
	rm -f $(BINARY)