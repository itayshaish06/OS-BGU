# Operating Systems Assignment 2: Synchronization and Interprocess Communication

## Introduction

This assignment focuses on implementing a cooperative multi-process coroutine system in the xv6 kernel.
The assignment will use process synchronization and the sleep and wakeup mechanisms provided by the xv6 kernel.

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
