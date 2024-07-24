# Multi-Threaded Microwave Oven Simulation

## Overview

This program simulates the functionality of a microwave oven using multiple threads. Each thread handles a specific function of the oven, such as opening and closing the door, rotating the plate, controlling the light, and running the timer. The program ensures that the oven operates correctly by using synchronization mechanisms.

## Features

- **Open/Close the Oven**: Simulate opening and closing the oven door.
- **Start/Stop the Oven**: Start and stop the oven with a timer.
- **Plate Rotation**: Rotate the plate when the oven is running.
- **Light Control**: Control the light inside the oven.
- **Timer**: Countdown timer from 60 to 0 seconds.

## Files

- `microwave_oven.c`: The main program file.
- `explanation.txt`: Explanation of the program's functionality.

## Requirements

- A Linux-based system.
- GCC (GNU Compiler Collection).

## Installation

1. **Install GCC**:
   ```
   sudo apt-get update
   sudo apt-get install gcc
   ```

## Usage

### Step 1: Compile the Program

Compile the C program using GCC:
```
gcc -o microwave_oven microwave_oven.c -pthread
```

### Step 2: Run the Program

Run the compiled program:
```
./microwave_oven
```

### Step 3: Enter Commands

The program will prompt you to enter commands to control the microwave oven. The available commands are:
- `0`: Close the oven
- `1`: Open the oven
- `2`: Start the oven
- `3`: Stop the oven
- `4`: Rotate the plate
- `5`: Stop the plate
- `6`: Turn on the light
- `7`: Turn off the light

Enter the corresponding command number to simulate the action.

### Step 4: Stopping the Program

The program runs indefinitely to allow continuous simulation. To stop the program, you can use `Ctrl+C`.

## Detailed Explanation of the Program

### Opening and Closing the Oven

- **Open the Oven (`1`)**:
  - The `open_oven` thread sets the oven state to open and stops the oven from running.
  - The oven stops rotating the plate, turns off the light, and stops the timer when opened.
  
- **Close the Oven (`0`)**:
  - The `close_oven` thread sets the oven state to closed.
  
### Starting and Stopping the Oven

- **Start the Oven (`2`)**:
  - The `start_oven` thread starts the oven if it is closed.
  - It sets the oven state to running, starts rotating the plate, turns on the light, and starts the timer.
  
- **Stop the Oven (`3`)**:
  - The `stop_oven` thread stops the oven.
  - It stops the plate rotation, turns off the light, and resets the timer.

### Plate Rotation

- **Rotate the Plate (`4`)**:
  - The `rotate_plate` thread keeps the plate rotating when the oven is running.
  
- **Stop the Plate (`5`)**:
  - The `stop_plate` thread stops the plate from rotating.

### Light Control

- **Turn on the Light (`6`)**:
  - The `start_light` thread keeps the light on when the oven is running.
  
- **Turn off the Light (`7`)**:
  - The `stop_light` thread turns off the light.

### Timer

- **Timer**:
  - The `start_timer` thread starts the timer from 60 seconds to 0 seconds when the oven is running.
  - The timer decrements every second and the oven stops when the timer reaches 0.

### Synchronization

- **Synchronization**:
  - Mutexes and condition variables are used to ensure that the oven runs correctly only when it is closed and the start button is pressed. The threads wait and signal each other using these synchronization mechanisms.

## Troubleshooting

- **Compilation Errors**: Ensure GCC is installed and properly configured. If you encounter compilation errors, check the syntax and dependencies in `microwave_oven.c`.
- **Unexpected Behavior**: If the oven does not behave as expected, ensure you are entering valid command numbers and that the threads are running correctly.

## Conclusion

This program provides a simulation of a microwave oven using multi-threading in C. By following the instructions in this README, you should be able to compile, run, and interact with the microwave oven simulation successfully.