Here is a detailed README file for the chat server program implemented in C:

---

# Chat Server

## Overview

This program implements a simple chat server that allows two clients to communicate with each other. The server listens for incoming connections from clients, receives messages from one client, and forwards them to the other client. The server uses the `select` function to handle multiple clients without using multi-threading.

## Features

- Accepts connections from two clients.
- Forwards messages from one client to the other.
- Handles client disconnections gracefully.
- Uses the `select` function to monitor multiple file descriptors for readability.

## Requirements

- GCC (GNU Compiler Collection)
- POSIX-compliant operating system (e.g., Linux)

## Files

- `server.c`: The main server program.
- `explanation.txt`: Explanation of the implementation.
- `README.md`: This file.

## How to Compile

To compile the server program, use the following command:

```sh
gcc -o server server.c
```

This command compiles `server.c` and produces an executable named `server`.

## How to Run

To run the server program, use the following command:

```sh
./server
```

The server will start listening for incoming connections on port 8080.

## How to Test

### Setting Up the Environment

1. **Start the Server**

   First, start the server by running the compiled executable:

   ```sh
   ./server
   ```

   The server will start listening on port 8080 and will print messages indicating its status.

2. **Connect Clients**

   Use a tool like `telnet` or `nc` (netcat) to connect clients to the server. In two separate terminal windows, run:

   ```sh
   telnet localhost 8080
   ```

   or

   ```sh
   nc localhost 8080
   ```

### Interacting with the Server

Once both clients are connected, they can start sending messages to each other. Type a message in one client terminal and it will be forwarded to the other client terminal.

### Example Interaction

1. **Client A:**

   ```sh
   Hi
   ```

2. **Client B:**

   ```sh
   Hello
   ```

3. **Client A:**

   ```sh
   Long time
   ```

4. **Client B:**

   ```sh
   Long time indeed
   ```

Messages sent by one client will be displayed in the other client's terminal.

## Program Flow

1. **Initialization:**

   - Initialize client sockets to 0 (indicating no clients connected).
   - Create the server socket.
   - Set socket options to allow reuse of the address and port.
   - Bind the server socket to the specified port.
   - Start listening for incoming connections.

2. **Main Loop:**

   - Clear and set file descriptors.
   - Use `select` to wait for activity on any file descriptor.
   - Handle new connections.
   - Handle I/O operations on client sockets.

## Error Handling

- The program checks for errors at each step (e.g., socket creation, binding, listening).
- If an error occurs, the program prints an error message and exits.

## Notes

- The server supports a maximum of two clients.
- The program uses the `select` function to handle multiple clients without using multi-threading.

## Conclusion

This chat server program demonstrates basic socket programming and the use of the `select` function to handle multiple client connections. It is a simple and effective way to enable communication between two clients.

---

This README file provides an overview of the program, how to compile and run it, how to test it, and a detailed explanation of its functionality.