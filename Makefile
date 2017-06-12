all:
	gcc -o matrix.o -c matrix.c
	gcc -o patternrec.o -c patternrec.c
	gcc -o pattern matrix.o patternrec.o pattern.c -lm
