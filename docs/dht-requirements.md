# CSE250A Project A: Implementation of DHT

In this project, you will work on one of the most cited implementations of a Distributed Hash Table (DHT): [Chord](http://nms.lcs.mit.edu/papers/chord.pdf). This topic was covered in the lecture.

## Project Overview

The main task is to implement different functions of a node class. A skeleton of the program will be provided (written in C++; apologies for non-C++ users). Your job is to implement some interfaces of the class, and your program will be tested against a set of member function calls.

- **Keys and Node Identifiers:**  
  For ease of grading, keys and node identifiers are 8-bit. Hash functions (like SHA-1 in the Chord paper) are omitted for this reason.

## Node Join Operation

When a node joins the DHT network, it needs to build its own finger table for routing purposes. To bootstrap this process, the joining node is provided with another node already in the Chord network (via an external mechanism). The following member function should be implemented, and some keys should be migrated to the new node when it joins:

```cpp
void Node::join(Node* node);
```

> *Note:* The Chord paper presents optimization techniques to initialize the finger table. Implementing one of them is optional. Also, multiple simultaneous joins are not considered in this project.

## Node Leave Operation

When a node leaves the DHT network, the keys it maintained should be migrated to another node. Since the Chord paper does not detail the leave procedure, implementing the following function is optional:

```cpp
void Node::leave();
```

This function should locate the node to which the keys should be migrated and notify other nodes to update their finger tables.

## Key Operations

Each node in Chord maintains part of the distributed hash table. If a node does not have the queried key locally, it must query the key from the Chord network. Additionally, nodes must support inserting and removing keys. The following functions are crucial:

```cpp
uint8_t Node::find(uint8_t key);
```

- For `find()`, the sequence of nodes involved in the lookup should be printed to the screen.

```cpp
void Node::insert(uint8_t key, uint8_t value);
void Node::remove(uint8_t key);
```

> Upon executing `join()` and `leave()`, the most updated finger tables should be printed.

## Example

Below is an example of how the member functions might be used:

```cpp
int main() { 
    Node n0(5);    // node_id == 5 
    Node n1(63);   // node_id == 63 
    n0.join(nullptr);  // the first node joins the Chord network 
    n0.insert(3, 3);   // insert key = 3 
    n1.join(&n0);      // the second node joins the Chord network 
    n1.insert(5);      // insert key = 5 
    n0.find(5);        // key query 
}
```

## TIPS

Chord uses Remote Procedure Call (RPC) to perform key lookups, either iteratively or recursively. In a simulation setting, RPC can be mimicked easily. For example:

```cpp
int remoteLookup(uint8_t key, Node* remoteNode) { 
    return remoteNode->localLookup(key); 
}
```

It can even be implemented recursively:

```cpp
int remoteLookup(uint8_t key, Node* remoteNode) { 
    return remoteNode->remoteLookup(key, anotherRemoteNode); 
}
```

## Grading Rubrics

1. **Build and Print Finger Table:**  
   Build the finger table correctly and print it when a new node joins. (40 pts)

2. **Key Migration:**  
   Correct keys are moved when a new node joins the DHT network. Print the keys that are migrated. (20 pts)

3. **Key Lookup:**  
   Correctly lookup keys and print the sequence of nodes involved in this process. (40 pts)

4. **[Optional] Node Leave:**  
   Implement `Node::leave()` correctly. (20 pts)

5. **[Optional] Simulate Space Shuffle:**  
   Correctly simulate Space Shuffle as described in the [TPDS16 paper](https://users.soe.ucsc.edu/~qian/papers/TPDS16.pdf). (40 pts)

## Contact

If you have any questions or encounter any bugs, please contact TA Yi Liu at [yliu634@ucsc.edu](mailto:yliu634@ucsc.edu).

[TPDS16 Paper](https://users.soe.ucsc.edu/~qian/papers/TPDS16.pdf)
