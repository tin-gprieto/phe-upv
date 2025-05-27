#!/bin/bash

# Target binary (set to your binary path)
BINARY="./srv"

# Initialize min and max with extreme values
min_addr=0xffffffff
max_addr=0x0

# Loop 100 times
for i in $(seq 1 $1); do
    # Get the mapped libc address directly from ldd output
    addr_hex=$(ldd "$BINARY" | grep "libc.so.6" | grep -oP '0x[0-9a-f]+')
    
    # Convert to decimal for comparison
    addr=$((addr_hex))
    min=$((min_addr))
    max=$((max_addr))
    
    (( addr < min )) && min_addr=$addr_hex
    (( addr > max )) && max_addr=$addr_hex
done

# Print results
printf "Min libc base address: 0x%x\n" $min_addr
printf "Max libc base address: 0x%x\n" $max_addr

