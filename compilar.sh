find -name "*.c" > names.txt
msg=""
msg=$(gcc @names.txt 2>&1 -lm -o saida)

if [ "$msg" != "" ];
then
 echo $msg> log.txt
 gedit log.txt
fi
