EXE ?= canary

echosrv:
	gcc -m32 -fstack-protector -g echosrv.c -o echosrv

vuln_ssp:
	gcc -std=c99 -m32 -fstack-protector -g vuln_ssp.c -o vuln_ssp

compile_show_spp_64:
	gcc show_canary_64.c -o show_canary_64

compile_show_sin_spp_32:
	gcc -m32 -fno-stack-protector show_canary_32.c -o show_no_canary_32

compile_show_spp_32:
	gcc -m32 show_canary_32.c -o show_canary_32

compile_no_spp:
	gcc -std=c99 -m32 -fno-stack-protector crash.c -o nocanary

compile_spp:
	gcc -std=c99 -m32 -fstack-protector crash.c -o canary

exec:	
	python3 -c 'print("a" * 40)' | ./$(EXE)
	
check:
	checksec --file=$(EXE)
