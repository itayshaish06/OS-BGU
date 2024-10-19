# Operating Systems - Assignment 1

**Course:** BGU Operating Systems

**Semester:** Spring 2024  

## Overview

This assignment is part of the Operating Systems course at Ben-Gurion University and focuses on system calls, scheduling, and process management using the xv6 teaching OS.

## Getting Started

To run this project, you'll need the following prerequisites:

1. Windows Subsystem for Linux 2 (WSL2)
2. Visual Studio Code
3. Docker for Windows

Follow these steps to set up your environment:

1. Ensure WSL2 is installed and properly configured on your Windows system.
2. Install Visual Studio Code if you haven't already.
3. Install Docker for Windows and configure it to use WSL2 backend.
4. Clone this repository to your local machine:
   ```
   git clone https://github.com/itayshaish06/OS-BGU.git
   ```
5. Open the cloned repository in Visual Studio Code.
6. Install the "Remote - Containers" extension in VS Code if you haven't already.
7. When prompted, reopen the project in a container, or use the command palette (F1) and select "Remote-Containers: Reopen in Container".
8. VS Code will build the Docker container with all necessary dependencies for xv6 development.
9. Once the container is ready, you can start working on the assignment tasks.
10. to run the xv6-os:
 ```
   make qemu
 ```
11. to stop the xv6-os click `ctrl+A` and after that click `X` on keyboard.

## Tasks

### Task 0: Compiling and Running xv6
- Download the xv6 source code.
- Compile the OS using `make`.
- Run xv6 in QEMU by using the command `make qemu`.

### Task 1: Hello World
- Create a simple user space program in xv6 that prints "Hello World xv6" to the screen.
- Modify the Makefile to include this new program.

### Task 2: Kernel Space and System Calls
- Implement a new system call `memsize()` that returns the memory size of the running process.
- Write a test program `memsize_test.c` to check the process memory before and after allocation.

### Task 3: Goodbye World
- Modify the `exit()` system call to accept and store an exit message.
- Modify `wait()` to retrieve the message and display it in the shell.
- Create a user program `goodbye.c` that calls `exit()` with the message "Goodbye World xv6."

### Task 4: Scheduling and CPU Affinity
- Understand the existing scheduling policy in xv6.
- Implement CPU affinity using an affinity mask to restrict processes to run on specific CPUs.
- Modify the scheduler to respect CPU affinity settings.

### Task 5: Load Balancing
- Implement load balancing to prevent processes from running on the same CPU for two consecutive time slices.
- Add an effective affinity mask to the Process Control Block (PCB).

## Resources
- [xv6 Source Code](https://github.com/BGU-CS-OS/xv6-riscv.git)
- [MIT 6.828 - xv6 Overview](https://pdos.csail.mit.edu/6.828/2022/overview.html)
- [xv6 Book (RISC-V Version)](https://pdos.csail.mit.edu/6.828/2022/xv6/book-riscv-rev3.pdf)
