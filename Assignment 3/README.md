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

Now you're all set to begin working on the assignment!


## Task 1: Memory Sharing

In this task we implemented the following kernel functions:

1. `uint64 map_shared_pages(struct proc* src_proc, struct proc* dst_proc, uint64 src_va, uint64 size)`
   - Purpose: This function maps physical pages from one process (source) to another process (destination). It enables different processes to share the same physical memory, facilitating inter-process communication and efficient data sharing.

2. `uint64 unmap_shared_pages(struct proc* p, uint64 addr, uint64 size)`
   - Purpose: This function removes the shared memory mapping from a process. It's essential for cleaning up shared resources when they're no longer needed, preventing memory leaks and maintaining proper isolation between processes.

These functions can be called from userspace by the system calls:

- `sys_map_shared_pages()`
- `sys_unmap_shared_pages()`

To keep xv6-os Modify `uvmunmap()` to handle shared memory correctly.

2 Test files with two userspace programs:

1. `shmem_test1.c`
   - Purpose: This test program demonstrates basic shared memory functionality between a parent and child process.
   - What it does:
     1. The parent process allocates memory and writes the string "Hello child" to it.
     2. The parent then forks a child process and shares this memory with the child.
     3. The child process reads and prints the shared string.
     4. The parent waits for the child to finish before exiting.
     5. This test verifies that shared memory is properly mapped and accessible in both processes.
     6. It also checks that the kernel properly cleans up the shared memory when processes exit without explicitly unmapping.

2. `shmem_test2.c`
   - Purpose: This test program showcases more advanced shared memory operations, including unmapping shared memory and verifying correct process address space management.
   - What it does:
     1. The parent process creates a shared memory mapping with a child process.
     2. The child process writes the string "Hello daddy" to the shared memory.
     3. The parent process reads and prints this string from the shared memory.
     4. The child process then unmaps the shared memory.
     5. The test verifies that `malloc()` in the child process works correctly after unmapping.
     6. It prints the size of the child process at various stages: before mapping, after mapping, after unmapping, and after a `malloc()` call.
     7. This test ensures that shared memory can be properly unmapped and that the process address space is correctly managed throughout these operations.

Both tests are designed to run sequentially without rebooting the system, demonstrating that your implementation leaves the system in a valid state after each test.

These test programs help verify the correct implementation of the shared memory system, including mapping, unmapping, process isolation, and proper cleanup of resources.

## Task 2: Userspace Cryptographic Service

Implement a cryptographic server in `crypto_srv.c` that processes encryption and decryption requests using shared memory.

Key components:

1. Use the provided system call `crypto_op()` to request cryptographic operations.
2. Implement the server to use `take_shared_memory_request()` and `remove_shared_memory_request()`.
3. Process requests using XOR operation for both encryption and decryption.
4. Use the provided request format for communication between client and server.
5. Implement proper error checking and state management.

Cryptographic Server Flow:
1. A process builds a crypto_os struct with type, state, key size and datat size.
2. The process calls the system call `crypto_op()` with the crypto_os struct and its size.
3. The system call adds this to the Server queue in the Kernel.
4. The Server reads the request from the kernel, uses `sys_map_shared_pages()` to access the process memory.
5. The Server decrypt the message.
6. The server changes the flag in the process memory according to sucess or failure.
7. The server calls `sys_unmap_shared_pages()`.
8. The process waits for the flag to be changed.
9. The processcontinues according to its new state.
   
![image](https://github.com/user-attachments/assets/a955c84d-f0d9-4242-a9ff-46c4ab14c7c6)
