**MULTIPROCESSING**

Ability of the system to have more than one processors within the system. Multiprocessing is possible because the processors share the:
* computer bus
* clock
* memory
* peripheral devices

so basically a dual core processor can do 2 process at a time and a octa-core processor can do 8 process at a time

**MULTITHREADING**

It is a process in which we can allow different code segments to run concurrently within the context of the process. Formally,it is the ablity of a process to be used by many users at the single time and also manage different requests by the user

for ex: using VLC media player we can use one thread to open VLC player another to run songs another thread to add music

for ex : web server client architecture , here many request by clients are handled by the server using threads

multithreading increases the responsiveness of the system also it reduces the cost as we don't need to manage separate process for each users

**POST**

Power On Self Test. It is used to initialize the hardware devices of the computer.

In order to boot the system BIOS is used (now UEFI)

POST -> BIOS CHECK -> CMOS RAM ->CPU ->HARDWARE DEVICE ->SECONDARY STORAGE DEVICE

The POST first checks the bios and then tests the CMOS RAM. If there is no problem with this then POST continues to check the CPU, hardware devices such as the Video Card, the secondary storage devices such as the Hard Drive, Floppy Drives, Zip Drive or CD/DVD Drives. If some errors found then an error message is displayed on the screen or a number of beeps are heard. These beeps are known as POST beep codes.

Limitations of BIOS

* can root upto 2TB device
* runs in 16 bit processor mode

The complete process of loading with BIOS

BIOS -> goes of POST -> check for MBR ->retrieve the BOOT-LOADER ->loads the system in RAM -> finally loads the OS

**MBR**

Master Boot Record. It is a program which runs when the computer is turning ON to find the OS.
