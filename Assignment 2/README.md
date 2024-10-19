# Operating Systems Assignment 2: Synchronization and Interprocess Communication

## Introduction

This assignment focuses on implementing a cooperative multi-process coroutine system in the xv6 kernel.
The assignment will use process synchronization and the sleep and wakeup mechanisms provided by the xv6 kernel.

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

### Task 1: Kernel Channels

Implement a new synchronization system in xv6 called a channel. This system will allow processes to send information between each other, with processes sleeping when no data is available or when no space is available to store new data.

#### Required System Calls:

1. `int channel_create(void)`
2. `int channel_put(int cd, int data)`
3. `int channel_take(int cd, int* data)`
4. `int channel_destroy(int cd)`

### Task 2: Prime Numbers

Using the channel mechanism implemented in Task 1, create a program that finds and prints prime numbers. The program should consist of several processes:

- A generator to produce numbers
- Multiple checkers to determine if numbers are prime
- A printer to output the results
  
![image](https://github.com/user-attachments/assets/d3b0ca30-7ca9-42ea-9aaf-49e92be71cec)
