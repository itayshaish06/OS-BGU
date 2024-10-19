# OS-BGU
This repository contains 3 assignments given in the OS-BGU course during the 2024 Fall semester.

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
