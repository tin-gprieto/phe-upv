#!/bin/bash

FILE=log.out

echo "--------------" >> $FILE

N=0
while true ; do
	
	N=$((N+1))
	
	EXPLOIT=$(python3 exploit.py | ./vuln1 2>&1)

	if echo "$EXPLOIT" | grep -q "exploit.py" ; then
		echo "Success on try #$N :"
		echo "$EXPLOIT"
		echo "Success on try #$N :" >> $FILE
		echo "$EXPLOIT" >> $FILE
		break
	else
		echo "Failed on try #$N"
		echo "Failed on try #$N"  >> $FILE
	fi
done
