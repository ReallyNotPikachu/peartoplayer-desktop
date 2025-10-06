CC = gcc
# add all the files
files := ./src/*.c
files += ./src/menus/*.c
objects := $(wildcard *.o)
CFLAGS := -O0 -ggdb -std=c17
LIBRARIES := -lm -lraylib

# by the way TODO add stuff like bolt and propeller

# I still have no idea how to use a makefile lol
test:
	sccache $(CC) $(files) $(CFLAGS) -o main $(LIBRARIES)
	./main
clean:
	rm *.o