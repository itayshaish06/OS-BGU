# Operating Systems - Assignment 1

**Course:** Operating Systems (202.1.3031)  
**Semester:** Spring 2024  
**Instructors:** Ido Ben-Yair, Eldar Zrihen

## Overview

This assignment is part of the Operating Systems course at Ben-Gurion University and focuses on system calls, scheduling, and process management using the xv6 teaching OS. The tasks include compiling and running xv6, creating system calls, and modifying the scheduler to implement CPU affinity and load balancing.

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

## Submission
- Submit a `.tar.gz` or `.zip` file containing all modified files via Moodle.
- Ensure your code compiles without errors and includes comments explaining the key changes.
- Test all changes thoroughly before submission.

## Resources
- [xv6 Source Code](https://github.com/BGU-CS-OS/xv6-riscv.git)
- [MIT 6.828 - xv6 Overview](https://pdos.csail.mit.edu/6.828/2022/overview.html)
- [xv6 Book (RISC-V Version)](https://pdos.csail.mit.edu/6.828/2022/xv6/book-riscv-rev3.pdf)

## Notes
- Work in pairs and use version control (Git) to track your progress.
- Follow the instructions closely, and don’t hesitate to reach out for help during office hours.

Good luck and enjoy the assignment!
