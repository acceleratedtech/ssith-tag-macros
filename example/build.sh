#!/bin/bash
riscv64-linux-gnu-gcc -S -I.. -O2 example.c -o example.S
riscv64-linux-gnu-gcc -I.. -O2 example.c -o example
riscv64-linux-gnu-objdump -d example > example.dump
