### README

# Performance Monitoring Program

## Overview

This program monitors the CPU and Memory usage of your system and logs the data to a file (`usage_log.txt`) every 2 seconds. It also captures the system calls made during this process and writes them to `syscalls.txt` using the `strace` tool.

## Files

- `performance_monitor.c`: The main C program file.
- `explanation.txt`: An explanation of how the program works.
- `syscalls.txt`: File to store system calls captured using `strace` (created during execution).
- `usage_log.txt`: File to store the logged CPU and Memory usage data (created during execution).

## Features

- **CPU Monitoring**: Calculates CPU usage percentage.
- **Memory Monitoring**: Calculates Memory usage percentage.
- **Logging**: Logs usage percentages along with timestamps to a file.
- **System Call Tracing**: Captures system calls like open, close, write, and read.

## Requirements

- A Linux-based system.
- GCC (GNU Compiler Collection) installed.
- `strace` tool installed.

## Installation

1. **Install GCC**: If GCC is not installed on your system, install it using:
   ```
   sudo apt-get update
   sudo apt-get install gcc
   ```

2. **Install strace**: If `strace` is not installed, install it using:
   ```
   sudo apt-get install strace
   ```

## Usage

### Step 1: Compile the Program

Compile the C program using GCC:
```
gcc -o performance_monitor performance_monitor.c
```

### Step 2: Run the Program

Run the compiled program:
```
./performance_monitor
```
This will start monitoring the CPU and Memory usage and log the data to `usage_log.txt`.

### Step 3: Capture System Calls

To capture the system calls made by the program, use `strace`:
```
strace -o syscalls.txt ./performance_monitor
```
This will run the program and simultaneously record the system calls in `syscalls.txt`.

### Stopping the Program

The program runs indefinitely, logging data every 2 seconds. To stop the program, use `Ctrl+C`.

## File Descriptions

### `performance_monitor.c`
The main program file that includes:
- Function to log CPU and Memory usage.
- Function to write logs to a file every 2 seconds.
- Main function that initializes logging and runs the logging loop.

### `explanation.txt`
A file explaining the program's functionality:
- How CPU and Memory usage is calculated.
- How the program logs the data.
- Instructions on using `strace` to capture system calls.

### `usage_log.txt`
A file created by the program to store the logged CPU and Memory usage data in the following format:
```
hh:mm:ss CPU: xx.xx%, Memory: xx.xx%
```
Where `hh:mm:ss` is the timestamp, `xx.xx` is the CPU usage percentage, and `xx.xx` is the Memory usage percentage.

### `syscalls.txt`
A file created by `strace` to store the system calls made by the program. This file includes calls like open, close, write, and read.

## Notes

- Ensure you have the necessary permissions to read from `/proc` and write to the log files.
- The program runs in an infinite loop, logging data every 2 seconds. Ensure you manually stop the program using `Ctrl+C`.
- To view the logs, open `usage_log.txt` with any text editor:
  ```
  cat usage_log.txt
  ```
- To view the captured system calls, open `syscalls.txt` with any text editor:
  ```
  cat syscalls.txt
  ```

## Troubleshooting

- **Permission Issues**: If you encounter permission issues while accessing `/proc` or writing to files, try running the program with elevated privileges using `sudo`:
  ```
  sudo ./performance_monitor
  ```

- **Compilation Errors**: Ensure GCC is installed and properly configured. If you encounter compilation errors, check the syntax and dependencies in `performance_monitor.c`.

- **Missing strace**: If `strace` is not installed, install it using the package manager (e.g., `sudo apt-get install strace`).

## Conclusion

This program provides a simple yet effective way to monitor system performance by logging CPU and Memory usage. It also demonstrates how to capture system calls, which can be useful for debugging and understanding program behavior. By following the instructions in this README, you should be able to compile, run, and analyze the performance monitoring program successfully.