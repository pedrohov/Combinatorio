names=""
names=$(find -name "*.c" >&1)
msg=""
msg=$(gcc $names 2>&1 -lm -o saida)

if [ "$msg" != "" ];
then
 echo $msg
 read line
fi
