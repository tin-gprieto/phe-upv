SHELL := /bin/bash
CC = gcc -std=c99 -m32
FLAGS = -fno-pie -no-pie -fno-stack-protector -g
EXE ?= srv


all: payload


deactivate_aslr:
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

activate_aslr:
	echo 2 | sudo tee /proc/sys/kernel/randomize_va_space

check_aslr:
	cat /proc/sys/kernel/randomize_va_space

compile:
	$(CC) $(FLAGS) -o $(EXE) $(EXE).c

addr:
	ltrace ./$(EXE)

check:
	checksec --file=$(EXE)

dep:
	ldd $(EXE) | grep libc
	
read:
	readelf -W -l $(EXE) | grep GNU_STACK

exploit:
	python3 exploit_2.py | ./vuln1
	
srv_exploit:
	python3 srv_exploit_2.py

