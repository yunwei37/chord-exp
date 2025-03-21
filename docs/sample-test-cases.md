# Chord DHT Sample Test Case

This document uses a sample test case to show the grading steps for a Chord distributed hash table implementation (following [1] I. Stoica, et al., *Chord: A Scalable Peer-to-peer Lookup Service for Internet Applications*, ACM SIGCOMM, 2001). The code is written in Python. If you find any problems, please email Yi Liu (<yliu634@ucsc.edu>).

---

## 1. Add Nodes to the Network

Use the `join` function with `m = 8` to create an identifier circle containing six nodes:

**Figure 1: An identifier circle that contains six nodes**  

```
n5 (id:230)    n0 (id:0)    n1 (id:30)    n2 (id:65)    n3 (id:110)    n4 (id:160)

         (circle shape)

m = 8
```

Below is the sample Python setup:

```python
# Creating nodes with given identifiers
n0 = Node(0)
n1 = Node(30)
n2 = Node(65)
n3 = Node(110)
n4 = Node(160)
n5 = Node(230)

# Joining nodes to form the network
n0.join(None)   # First node creates the network
n1.join(n0)
n2.join(n1)
n3.join(n2)
n4.join(n3)
n5.join(n4)
```

---

## 2. Print Finger Tables of All Nodes (40 pts)

Once the nodes have joined, each node will have a successor, predecessor, and a finger table.

**Figure 2: Finger tables of six nodes**

<details>
<summary>Textual representation of the finger tables</summary>

```
------------ Node Id:0 -------------
Successor: 30  Predecessor: 230
FingerTables:
| k = 1 (1,2)      succ.: 30  |
| k = 2 (2,4)      succ.: 30  |
| k = 3 (4,8)      succ.: 30  |
| k = 4 (8,16)     succ.: 30  |
| k = 5 (16,32)    succ.: 30  |
| k = 6 (32,64)    succ.: 65  |
| k = 7 (64,128)   succ.: 110 |
| k = 8 (128,256)  succ.: 230 |

------------ Node Id:30 -------------
Successor: 65  Predecessor: 0
FingerTables:
| k = 1 (31,32)    succ.: 65  |
| k = 2 (32,34)    succ.: 65  |
| k = 3 (34,38)    succ.: 65  |
| k = 4 (38,46)    succ.: 65  |
| k = 5 (46,62)    succ.: 65  |
| k = 6 (62,94)    succ.: 110 |
| k = 7 (94,158)   succ.: 160 |
| k = 8 (158,286)  succ.: 230 |

------------ Node Id:65 -------------
Successor: 110 Predecessor: 30
FingerTables:
| k = 1 (66,67)    succ.: 110 |
| k = 2 (67,69)    succ.: 110 |
| k = 3 (69,73)    succ.: 110 |
| k = 4 (73,81)    succ.: 110 |
| k = 5 (81,97)    succ.: 110 |
| k = 6 (97,129)   succ.: 160 |
| k = 7 (129,193)  succ.: 230 |
| k = 8 (193,321)  succ.: 0   |

------------ Node Id:110 -------------
Successor: 160 Predecessor: 65
FingerTables:
| k = 1 (111,112)   succ.: 160 |
| k = 2 (112,114)   succ.: 160 |
| k = 3 (114,118)   succ.: 160 |
| k = 4 (118,126)   succ.: 160 |
| k = 5 (126,142)   succ.: 160 |
| k = 6 (142,174)   succ.: 230 |
| k = 7 (174,238)   succ.: 230 |
| k = 8 (238,366)   succ.: 0   |

------------ Node Id:160 -------------
Successor: 230 Predecessor: 110
FingerTables:
| k = 1 (161,162)   succ.: 230 |
| k = 2 (162,164)   succ.: 230 |
| k = 3 (164,168)   succ.: 230 |
| k = 4 (168,176)   succ.: 230 |
| k = 5 (176,192)   succ.: 230 |
| k = 6 (192,224)   succ.: 230 |
| k = 7 (224,288)   succ.: 0   |
| k = 8 (288,416)   succ.: 30  |

------------ Node Id:230 -------------
Successor: 0   Predecessor: 160
FingerTables:
| k = 1 (231,232)   succ.: 0   |
| k = 2 (232,234)   succ.: 0   |
| k = 3 (234,238)   succ.: 0   |
| k = 4 (238,246)   succ.: 0   |
| k = 5 (246,262)   succ.: 0   |
| k = 6 (262,294)   succ.: 0   |
| k = 7 (294,358)   succ.: 30  |
| k = 8 (358,486)   succ.: 65  |
```

</details>

---

## 3. Insert Keys and Add New Node Joins (20 pts)

### 3.1 Insert Keys

Insert several keys into the network using the `insert` function. Some keys may include an extra parameter (e.g., replication factor or other metadata):

```python
n0.insert(3, 3)
n1.insert(200)
n2.insert(123)
n3.insert(45, 3)
n4.insert(99)
n2.insert(60, 10)
n0.insert(50, 8)
n3.insert(100, 5)
n3.insert(101, 4)
n3.insert(102, 6)
n5.insert(240, 8)
n5.insert(250, 10)
```

### 3.2 Print Keys Stored in Each Node (10 pts)

After the insertions, print the keys stored in each node.

**Figure 3: Keys distribution on nodes**

<details>
<summary>Textual representation of the keys on each node</summary>

```
------------- Node id:0 --------------
{240: 8, 250: 10}

------------- Node id:30 -------------
{ }

------------- Node id:110 -------------
{99: None, 100: 5, 101: 4, 102: 6}

------------- Node id:230 -------------
{123: None}

------------- Node id:65 -------------
{ }

------------- Node id:160 -------------
{ }
```

</details>

### 3.3 Add a New Node and Migrate Keys (10 pts)

Introduce a new node `n6 (id:100)` into the network. This causes some keys to be migrated.

```python
n6 = Node(100)
n6.join(n5)  # or whichever node you choose to join with
```

**Figure 4: An updated circle after n6 joins**

```
n5 (id:230) -> n0 (id:0) -> n1 (id:30) -> n2 (id:65) -> n6 (id:100) -> n3 (id:110) -> n4 (id:160)
m = 8
```

You should then print which keys were migrated to `n6` upon joining.

---

## 4. Lookup Keys (40 pts)

Perform lookups for all inserted keys starting from three nodes (`n0`, `n2`, and `n6`). For each lookup, print both the result and the sequence of nodes involved in the lookup procedure.

**Figure 5: Lookup keys from three nodes**  
Below is a sample text log (the actual results may vary depending on your implementation):

<details>
<summary>Textual example of lookups and paths</summary>

```
---------------- node 0 ----------------
Look-up result of key 3   from node 0 with path [0,30]  value is 3
Look-up result of key 200 from node 0 with path [0,30]  value is None
Look-up result of key 123 from node 0 with path [0,30,65] value is 123
Look-up result of key 45  from node 0 with path [0,30]  value is 3
Look-up result of key 99  from node 0 with path [0,30,65,110] value is None
Look-up result of key 60  from node 0 with path [0,30,65] value is 10
Look-up result of key 50  from node 0 with path [0,30]  value is 8
...
(etc.)

---------------- node 2 (id:65) ----------------
Look-up result of key 3   from node 2 with path [65,30]  value is 3
Look-up result of key 200 from node 2 with path [65,30]  value is None
Look-up result of key 123 from node 2 with path [65]     value is 123
...
(etc.)

---------------- node 6 (id:100) ----------------
Look-up result of key 3   from node 6 with path [100,110,160,...]  value is ...
Look-up result of key 200 from node 6 with path [100,110,160,...]  value is ...
...
(etc.)
```

</details>

---

## 5. Leave (20 pts)

Let one node (e.g., `n2`) leave the network. Print the updated finger tables of `n0` and `n1`, and also show how the keys are redistributed among remaining nodes.

```python
# Node n2 leaves the network
n2.leave()

# Print updated finger tables and keys distribution
print("Updated finger table for n0:", n0.get_finger_table())
print("Updated finger table for n1:", n1.get_finger_table())
# Also print the keys stored in each remaining node.
```

**Figure 6: Updated finger table**  

<details>
<summary>Sample text after n2 leaves</summary>

```
------------ Node id:0 -------------
Successor: 30  Predecessor: 230
FingerTables:
| k = 1 (1,2)      succ.: 30  |
| k = 2 (2,4)      succ.: 30  |
| k = 3 (4,8)      succ.: 30  |
| k = 4 (8,16)     succ.: 30  |
| k = 5 (16,32)    succ.: 30  |
| k = 6 (32,64)    succ.: 30  |
| k = 7 (64,128)   succ.: 230 |
| k = 8 (128,256)  succ.: 230 |

------------ Node id:30 -------------
Successor: 0   Predecessor: 0
FingerTables:
| k = 1 (31,32)    succ.: 0   |
| k = 2 (32,34)    succ.: 0   |
| k = 3 (34,38)    succ.: 0   |
| k = 4 (38,46)    succ.: 0   |
| k = 5 (46,62)    succ.: 0   |
| k = 6 (62,94)    succ.: 0   |
| k = 7 (94,158)   succ.: 0   |
| k = 8 (158,286)  succ.: 0   |

# (And similarly for the other nodes still in the network)

# Updated keys distribution across remaining nodes
# ...
```

</details>
