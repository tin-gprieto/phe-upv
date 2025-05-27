.section .text
.global _start

_start:
	xor %eax , %eax  ;eax=0
	push %eax ; push 0
	push $0x68732f2f ; push "// sh "
	push $0x6e69622f ; push "/ bin "
	mov %esp , %ebx ; ebx -> "/ bin // sh "
	push %eax ; push 0
	push %ebx ; push ebx
	mov %esp , %ecx ; ecx -> {"/ bin // sh " , 0}
	mov $0xb , %al  ; execve =11
	int $0x80 ; syscall
