SHELL := /bin/bash
CC = gcc -std=c99 -m32
FLAGS = -fno-pie -no-pie -fno-stack-protector -g
EXE ?= srv


all: payload


compile:
	$(CC) $(FLAGS) -o $(EXE) $(EXE).c

addr:
	ltrace ./$(EXE)

srv_compile:
	$(CC) $(FLAGS) -o srv srv.c

deactivate_aslr:
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

activate_aslr:
	echo 2 | sudo tee /proc/sys/kernel/randomize_va_space

check_aslr:
	cat /proc/sys/kernel/randomize_va_space

check:
	checksec --file=$(EXE)

dep:
	ldd $(EXE) | grep libc
	
read:
	readelf -W -l $(EXE) | grep GNU_STACK

exploit:
	python3 exploit.py | ./vuln1
	
srv_exploit:
	python3 srv_exploit.py

