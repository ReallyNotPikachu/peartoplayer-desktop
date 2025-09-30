CC = gcc

# Note to self actually learn how to write a makefile

test:
# my code is SO BROKEN i have to compile it with march=x86-64??
# was it defaulting to march=native?? I dont think it was?? huh??
# im guessing if I compile it for 32 bit arm and then emulate it it'll run even faster?
# just tried march=native, and it worked?
	sccache $(CC) ./src/**.c -o main -lraylib -lm -O0 -march=native -ggdb -pipe
	./main