# Operating Systems Assignment 3: Memory Management

## Introduction

This assignment focuses on implementing a shared memory system in xv6 and utilizing it to create a userspace cryptographic service. The project is divided into two main tasks:

1. Implementing memory sharing
2. Creating a userspace cryptographic service

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
   git clone <repository-url>
   ```
5. Open the cloned repository in Visual Studio Code.
6. Install the "Remote - Containers" extension in VS Code if you haven't already.
7. When prompted, reopen the project in a container, or use the command palette (F1) and select "Remote-Containers: Reopen in Container".
8. VS Code will build the Docker container with all necessary dependencies for xv6 development.
9. Once the container is ready, you can start working on the assignment tasks.

Now you're all set to begin working on the assignment!


## Task 1: Memory Sharing

Implement the following kernel functions:

1. `uint64 map_shared_pages(struct proc* src_proc, struct proc* dst_proc, uint64 src_va, uint64 size)`
2. `uint64 unmap_shared_pages(struct proc* p, uint64 addr, uint64 size)`

Expose these functions to userspace by adding system calls:

- `sys_map_shared_pages()`
- `sys_unmap_shared_pages()`

Modify `uvmunmap()` to handle shared memory correctly.

Test your implementation with two userspace programs:

1. `shmem_test1.c`
2. `shmem_test2.c`

## Task 2: Userspace Cryptographic Service

Implement a cryptographic server in `crypto_srv.c` that processes encryption and decryption requests using shared memory.

Key components:

1. Use the provided system call `crypto_op()` to request cryptographic operations.
2. Implement the server to use `take_shared_memory_request()` and `remove_shared_memory_request()`.
3. Process requests using XOR operation for both encryption and decryption.
4. Use the provided request format for communication between client and server.
5. Implement proper error checking and state management.

## Submission Instructions

1. Ensure your code compiles without errors and warnings.
2. Comment your code and explain your choices where necessary.
3. Submit a single copy of xv6 with all tasks included, ready to compile with `make qemu`.
4. Run `make clean` before submission.
5. Submit as a single .tar.gz or .zip file (no .rar files).
6. Submission is allowed only in pairs and via Moodle.

## Files to Submit

1. Modified kernel code implementing the shared memory system
2. `shmem_test1.c` and `shmem_test2.c`
3. Implementation of the cryptographic server in `crypto_srv.c`

## Notes

- The assignment includes theoretical questions that are not for submission but may be discussed during grading sessions.
- Use git to maintain a working version of your code as you progress.
- If you need help, contact the teaching assistants during office hours.

Good luck with your assignment!
