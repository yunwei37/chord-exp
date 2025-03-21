# Chord DHT Implementation

This is an implementation of the Chord Distributed Hash Table (DHT) as described in the paper by I. Stoica, et al., "Chord: A Scalable Peer-to-peer Lookup Service for Internet Applications", ACM SIGCOMM, 2001.

## Overview

Chord is a protocol and algorithm for a peer-to-peer distributed hash table. A distributed hash table stores key-value pairs by assigning keys to different nodes; a node will store the values for all the keys for which it is responsible. Chord specifies how keys are assigned to nodes, and how a node can discover the value for a given key by first locating the node responsible for that key.

This implementation uses an 8-bit identifier space, meaning that both keys and node IDs are in the range [0, 255].

## Project Structure

- `node.h`: Header file defining the Node and FingerTable classes
- `node.cpp`: Implementation of the Node class methods
- `fingertable.cpp`: Implementation of the FingerTable class methods
- `test_chord.cpp`: Test file that demonstrates the Chord DHT functionality
- `Makefile`: For compiling and running the project

## Features

1. **Node Join**: Allows nodes to join the Chord ring
2. **Key Insertion**: Supports inserting key-value pairs into the DHT
3. **Key Lookup**: Lookup keys in the DHT with path tracing
4. **Key Removal**: Remove keys from the DHT
5. **Node Leave**: Node can leave the Chord ring (optional)

## Building and Running

To build the project, simply run:

```bash
make
```

To run the tests:

```bash
make run
```

Alternatively, you can execute the binary directly:

```bash
./chord_test
```

To clean the build files:

```bash
make clean
```

## Sample Test Case

The test case in `test_chord.cpp` demonstrates:

1. Creating a Chord ring with 6 nodes
2. Inserting keys into the DHT
3. Looking up keys from different nodes
4. Adding a new node and observing key migration
5. Testing the node leave operation

## Implementation Notes

- This implementation follows the Chord paper's protocol for finger tables and successor/predecessor pointers.
- The lookup procedure is implemented recursively, with each node passing the request to the next appropriate node.
- Each operation outputs its steps to provide clarity on how the Chord protocol operates.
- The network in this implementation is simulated in-memory, rather than using actual network communications.