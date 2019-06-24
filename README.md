## Basic_Kernel : A Basic Attempt to Make A Kernel

This is my first ever attempt at making a basic kernel. So far I successfully made a bootloader, linker, and got a hello world to work. 

![As Demonstrated Here](images/hello.png).

This runs in QEMU. 

### How to build:

Clone the source, and make sure you have all of the build tools required (gcc, gas, make, grub-mkrescue). Then go to source and run `make package`. 

This will generate an ISO file. While I run it in QEMU with `qemu-system-x86_64 -cdrom /path/to/ISO`, you should be able to run it on other emulators as well.
