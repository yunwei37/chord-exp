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

### Result

```sh
$ ./chord_test
=== Chord DHT Test Case ===
Setting up Chord network with m = 8

=== Creating Nodes ===
Created nodes with ids: 0, 30, 65, 110, 160, 230

=== Joining Nodes to Network ===
------------ Node Id:0 -------------
Successor: 0  Predecessor: 0
FingerTables:
| k = 1 (1,2)         succ.: 0 |
| k = 2 (2,4)         succ.: 0 |
| k = 3 (4,8)         succ.: 0 |
| k = 4 (8,16)        succ.: 0 |
| k = 5 (16,32)        succ.: 0 |
| k = 6 (32,64)        succ.: 0 |
| k = 7 (64,128)       succ.: 0 |
| k = 8 (128,0)         succ.: 0 |

Node n0 (id:0) joined the network as the first node
Node 30 is joining through node 0
------------ Node Id:30 -------------
Successor: 0  Predecessor: 0
FingerTables:
| k = 1 (31,32)        succ.: 0 |
| k = 2 (32,34)        succ.: 0 |
| k = 3 (34,38)        succ.: 0 |
| k = 4 (38,46)        succ.: 0 |
| k = 5 (46,62)        succ.: 0 |
| k = 6 (62,94)        succ.: 0 |
| k = 7 (94,158)       succ.: 0 |
| k = 8 (158,30)        succ.: 0 |

Node n1 (id:30) joined the network
Node 65 is joining through node 30
------------ Node Id:65 -------------
Successor: 0  Predecessor: 30
FingerTables:
| k = 1 (66,67)        succ.: 0 |
| k = 2 (67,69)        succ.: 0 |
| k = 3 (69,73)        succ.: 0 |
| k = 4 (73,81)        succ.: 0 |
| k = 5 (81,97)        succ.: 0 |
| k = 6 (97,129)       succ.: 0 |
| k = 7 (129,193)       succ.: 0 |
| k = 8 (193,65)        succ.: 0 |

Node n2 (id:65) joined the network
Node 110 is joining through node 65
------------ Node Id:110 -------------
Successor: 0  Predecessor: 65
FingerTables:
| k = 1 (111,112)       succ.: 0 |
| k = 2 (112,114)       succ.: 0 |
| k = 3 (114,118)       succ.: 0 |
| k = 4 (118,126)       succ.: 0 |
| k = 5 (126,142)       succ.: 0 |
| k = 6 (142,174)       succ.: 0 |
| k = 7 (174,238)       succ.: 0 |
| k = 8 (238,110)       succ.: 0 |

Node n3 (id:110) joined the network
Node 160 is joining through node 110
------------ Node Id:160 -------------
Successor: 0  Predecessor: 110
FingerTables:
| k = 1 (161,162)       succ.: 0 |
| k = 2 (162,164)       succ.: 0 |
| k = 3 (164,168)       succ.: 0 |
| k = 4 (168,176)       succ.: 0 |
| k = 5 (176,192)       succ.: 0 |
| k = 6 (192,224)       succ.: 0 |
| k = 7 (224,32)        succ.: 0 |
| k = 8 (32,160)       succ.: 65 |

Node n4 (id:160) joined the network
Node 230 is joining through node 160
------------ Node Id:230 -------------
Successor: 0  Predecessor: 160
FingerTables:
| k = 1 (231,232)       succ.: 0 |
| k = 2 (232,234)       succ.: 0 |
| k = 3 (234,238)       succ.: 0 |
| k = 4 (238,246)       succ.: 0 |
| k = 5 (246,6)         succ.: 0 |
| k = 6 (6,38)        succ.: 30 |
| k = 7 (38,102)       succ.: 65 |
| k = 8 (102,230)       succ.: 110 |

Node n5 (id:230) joined the network

=== Inserting Keys ===
Key 3 with value 3 inserted at node 30
Key 200 with value 0 inserted at node 230
Key 123 with value 0 inserted at node 160
Key 45 with value 3 inserted at node 65
Key 99 with value 0 inserted at node 110
Key 60 with value 10 inserted at node 65
Key 50 with value 8 inserted at node 65
Key 100 with value 5 inserted at node 110
Key 101 with value 4 inserted at node 110
Key 102 with value 6 inserted at node 110
Key 240 with value 8 inserted at node 0
Key 250 with value 10 inserted at node 0

=== Network Details ===
------------- Node id:0 --------------
Keys: {240: 8, 250: 10}

------------- Node id:30 --------------
Keys: {3: 3}

------------- Node id:65 --------------
Keys: {45: 3, 50: 8, 60: 10}

------------- Node id:110 --------------
Keys: {99: None, 100: 5, 101: 4, 102: 6}

------------- Node id:160 --------------
Keys: {123: None}

------------- Node id:230 --------------
Keys: {200: None}


=== Looking Up Keys from Node n0 (id:0) ===
Look-up result of key 3 from node 30 with path [30] value is 3
Look-up result of key 3 from node 0 with path [0,30] value is 3
Look-up result of key 200 from node 230 with path [230] value is 0
Look-up result of key 200 from node 0 with path [0,230] value is 0
Look-up result of key 123 from node 160 with path [160] value is 0
Look-up result of key 123 from node 0 with path [0,160] value is 0
Look-up result of key 45 from node 65 with path [65] value is 3
Look-up result of key 45 from node 0 with path [0,65] value is 3
Look-up result of key 99 from node 110 with path [110] value is 0
Look-up result of key 99 from node 0 with path [0,110] value is 0
Look-up result of key 60 from node 65 with path [65] value is 10
Look-up result of key 60 from node 0 with path [0,65] value is 10
Look-up result of key 50 from node 65 with path [65] value is 8
Look-up result of key 50 from node 0 with path [0,65] value is 8
Look-up result of key 100 from node 110 with path [110] value is 5
Look-up result of key 100 from node 0 with path [0,110] value is 5
Look-up result of key 101 from node 110 with path [110] value is 4
Look-up result of key 101 from node 0 with path [0,110] value is 4
Look-up result of key 102 from node 110 with path [110] value is 6
Look-up result of key 102 from node 0 with path [0,110] value is 6
Look-up result of key 240 from node 0 with path [0] value is 8
Look-up result of key 250 from node 0 with path [0] value is 10

=== Looking Up Keys from Node n2 (id:65) ===
Look-up result of key 3 from node 30 with path [30] value is 3
Look-up result of key 3 from node 65 with path [65,30] value is 3
Look-up result of key 200 from node 230 with path [230] value is 0
Look-up result of key 200 from node 65 with path [65,230] value is 0
Look-up result of key 123 from node 160 with path [160] value is 0
Look-up result of key 123 from node 65 with path [65,160] value is 0
Look-up result of key 45 from node 65 with path [65] value is 3
Look-up result of key 99 from node 110 with path [110] value is 0
Look-up result of key 99 from node 65 with path [65,110] value is 0
Look-up result of key 60 from node 65 with path [65] value is 10
Look-up result of key 50 from node 65 with path [65] value is 8
Look-up result of key 100 from node 110 with path [110] value is 5
Look-up result of key 100 from node 65 with path [65,110] value is 5
Look-up result of key 101 from node 110 with path [110] value is 4
Look-up result of key 101 from node 65 with path [65,110] value is 4
Look-up result of key 102 from node 110 with path [110] value is 6
Look-up result of key 102 from node 65 with path [65,110] value is 6
Look-up result of key 240 from node 0 with path [0] value is 8
Look-up result of key 240 from node 65 with path [65,0] value is 8
Look-up result of key 250 from node 0 with path [0] value is 10
Look-up result of key 250 from node 65 with path [65,0] value is 10

=== Adding New Node n6 (id:100) ===
Node 100 is joining through node 230
Key 99 moved from node 110 to node 100
Key 100 moved from node 110 to node 100
Key 99 removed from node 110
Key 100 removed from node 110
------------ Node Id:100 -------------
Successor: 110  Predecessor: 65
FingerTables:
| k = 1 (101,102)       succ.: 110 |
| k = 2 (102,104)       succ.: 110 |
| k = 3 (104,108)       succ.: 110 |
| k = 4 (108,116)       succ.: 110 |
| k = 5 (116,132)       succ.: 160 |
| k = 6 (132,164)       succ.: 160 |
| k = 7 (164,228)       succ.: 230 |
| k = 8 (228,100)       succ.: 230 |

=== Network Details ===
------------- Node id:0 --------------
Keys: {240: 8, 250: 10}

------------- Node id:30 --------------
Keys: {3: 3}

------------- Node id:65 --------------
Keys: {45: 3, 50: 8, 60: 10}

------------- Node id:110 --------------
Keys: {101: 4, 102: 6}

------------- Node id:160 --------------
Keys: {123: None}

------------- Node id:230 --------------
Keys: {200: None}

------------- Node id:100 --------------
Keys: {99: None, 100: 5}


=== Looking Up Keys from New Node n6 (id:100) ===
Look-up result of key 3 from node 30 with path [30] value is 3
Look-up result of key 3 from node 100 with path [100,30] value is 3
Look-up result of key 200 from node 230 with path [230] value is 0
Look-up result of key 200 from node 100 with path [100,230] value is 0
Look-up result of key 123 from node 160 with path [160] value is 0
Look-up result of key 123 from node 100 with path [100,160] value is 0
Look-up result of key 45 from node 65 with path [65] value is 3
Look-up result of key 45 from node 100 with path [100,65] value is 3
Look-up result of key 99 from node 100 with path [100] value is 0
Look-up result of key 60 from node 65 with path [65] value is 10
Look-up result of key 60 from node 100 with path [100,65] value is 10
Look-up result of key 50 from node 65 with path [65] value is 8
Look-up result of key 50 from node 100 with path [100,65] value is 8
Look-up result of key 100 from node 100 with path [100] value is 5
Look-up result of key 101 from node 110 with path [110] value is 4
Look-up result of key 101 from node 100 with path [100,110] value is 4
Look-up result of key 102 from node 110 with path [110] value is 6
Look-up result of key 102 from node 100 with path [100,110] value is 6
Look-up result of key 240 from node 0 with path [0] value is 8
Look-up result of key 240 from node 100 with path [100,0] value is 8
Look-up result of key 250 from node 0 with path [0] value is 10
Look-up result of key 250 from node 100 with path [100,0] value is 10

=== Testing Node Leave - Node n2 (id:65) ===
Key 45 moved from node 65 to node 100
Key 50 moved from node 65 to node 100
Key 60 moved from node 65 to node 100
Node 65 has left the network

=== Network Details ===
------------- Node id:0 --------------
Keys: {240: 8, 250: 10}

------------- Node id:30 --------------
Keys: {3: 3}

------------- Node id:110 --------------
Keys: {101: 4, 102: 6}

------------- Node id:160 --------------
Keys: {123: None}

------------- Node id:230 --------------
Keys: {200: None}

------------- Node id:100 --------------
Keys: {45: 3, 50: 8, 60: 10, 99: None, 100: 5}
```

## Implementation Notes

- This implementation follows the Chord paper's protocol for finger tables and successor/predecessor pointers.
- The lookup procedure is implemented recursively, with each node passing the request to the next appropriate node.
- Each operation outputs its steps to provide clarity on how the Chord protocol operates.
- The network in this implementation is simulated in-memory, rather than using actual network communications.