#!/bin/bash

N=0
while true ; do
	N=$((N+1))
	# Lanza exploit
	python3 exploit.py | ./vuln1
	if [ $? -eq 0 ]; then
		echo "Success on try #$N"
		break
	fi
	echo "Failed on try #$N"
done
