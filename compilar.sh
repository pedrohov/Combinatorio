find -name "*.c" > names.txt
gcc @names.txt 2> log.txt -o saida
