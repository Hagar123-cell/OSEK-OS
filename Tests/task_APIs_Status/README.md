# Compile and run the test as follows: 

Open task_APIs_Status directory and run the following command to compile the test
```
riscv32-unknown-elf-gcc -I../../ -I./  -g -ffreestanding -O0 -Wl,--gc-sections     -nostartfiles -nostdlib -nodefaultlibs -Wl,-T,../../Linker_and_Startup/riscv32-virt.ld ../../Linker_and_Startup/crt0.s Task_API_Errors.c ../../Os.c Os_PBcfg.c ../../riscv_context_switching.S ../../scheduler.c ../../task_management.c
```

Start the RISC-V virtual machine and listen for GDB connections on port 1234 . 

```
qemu-system-riscv32 -machine virt -m 128M -gdb tcp::1234 -S -bios none -kernel a.out
```

In another terminal launch the RISC-V GDB (GNU Debugger) and connect it to a remote target, in this case, a QEMU instance running a RISC-V virtual machine

```
riscv32-unknown-elf-gdb a.out -ex "target remote :1234"`
```

run the follwing commands in debug Session:

```
b* Task1+36   
c
p *&act[0]@8  
p *&ter[0]@2  
p *&chain[0]@5
p *&sched[0]@2
```
