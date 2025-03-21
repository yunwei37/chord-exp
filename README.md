# Chord DHT Implementation

This is an implementation of the Chord Distributed Hash Table (DHT) protocol as described in the paper ["Chord: A Scalable Peer-to-peer Lookup Service for Internet Applications"](http://nms.lcs.mit.edu/papers/chord.pdf) by Stoica et al.

## Overview

The implementation provides a simulation of a Chord DHT with the following features:

- Node join operation and finger table construction
- Key insertion, lookup, and removal
- Node leave operation and key migration
- Tracking of lookup paths

The DHT uses 8-bit identifiers for both nodes and keys, with the identifier space ranging from 0 to 255.

## Implementation Details

The implementation consists of two main classes:

1. `FingerTable`: Manages the finger table for each node in the Chord ring.
2. `Node`: Represents a node in the Chord DHT, maintaining its finger table, successor, predecessor, and local keys.

Key operations implemented:
- `join()`: Allows a node to join the Chord network
- `find()`: Lookup a key in the DHT
- `insert()`: Insert a key-value pair into the DHT
- `remove()`: Remove a key from the DHT
- `leave()`: Remove a node from the DHT

## Building and Running

### Prerequisites

- C++11 compatible compiler (g++ recommended)
- Make

### Compilation

To compile the project, simply run:

```bash
make
```

This will generate an executable called `chord_dht`.

### Running

To run the chord implementation with the test cases:

```bash
make run
```

or directly:

```bash
./chord_dht
```

### Cleaning

To clean the build files:

```bash
make clean
```

## Test Cases

The test file `test.cpp` demonstrates the functionality of the implementation with test cases closely following the sample test cases provided in the project specification. It includes:

1. Creating a Chord ring with six nodes with specific IDs
2. Inserting keys into the DHT through different nodes
3. Looking up keys from different nodes in the ring
4. Adding a new node and observing key migration
5. Handling node departure and finger table updates

## Limitations

- The implementation is a simulation and doesn't include networking functionality.
- The DHT uses 8-bit identifiers for simplicity, limiting the identifier space to 256 values.
- Concurrent joins/leaves are not supported.

## References

- I. Stoica, R. Morris, D. Karger, M. F. Kaashoek, and H. Balakrishnan, "Chord: A Scalable Peer-to-peer Lookup Service for Internet Applications," ACM SIGCOMM, 2001.