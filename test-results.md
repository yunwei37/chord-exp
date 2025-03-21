# The test result

```bash
$ make run
g++ -std=c++11 -Wall -Wextra -c node.cpp -o node.o
g++ -std=c++11 -Wall -Wextra -c fingertable.cpp -o fingertable.o
g++ -std=c++11 -Wall -Wextra -c test_chord.cpp -o test_chord.o
g++ -std=c++11 -Wall -Wextra -o chord_test node.o fingertable.o test_chord.o
./chord_test
=== Chord DHT Test Case ===
Setting up Chord network with m = 8

=== Creating Nodes ===
Created nodes with ids: 0, 30, 65, 110, 160, 230

=== Joining Nodes to Network ===
Node n0 (id:0) joined the network as the first node
Node n1 (id:30) joined the network
Node n2 (id:65) joined the network
Node n3 (id:110) joined the network
Node n4 (id:160) joined the network
Node n5 (id:230) joined the network

=== Print Finger Tables of All Nodes ===
------------ Node Id:0 -------------
Successor: 30  Predecessor: 230
FingerTables:
| k = 1 (1,2)               succ.: 30 |
| k = 2 (2,4)               succ.: 30 |
| k = 3 (4,8)               succ.: 30 |
| k = 4 (8,16)              succ.: 30 |
| k = 5 (16,32)              succ.: 30 |
| k = 6 (32,64)              succ.: 65 |
| k = 7 (64,128)             succ.: 65 |
| k = 8 (128,0)               succ.: 160 |

------------ Node Id:30 -------------
Successor: 65  Predecessor: 0
FingerTables:
| k = 1 (31,32)              succ.: 65 |
| k = 2 (32,34)              succ.: 65 |
| k = 3 (34,38)              succ.: 65 |
| k = 4 (38,46)              succ.: 65 |
| k = 5 (46,62)              succ.: 65 |
| k = 6 (62,94)              succ.: 65 |
| k = 7 (94,158)             succ.: 110 |
| k = 8 (158,30)              succ.: 160 |

------------ Node Id:65 -------------
Successor: 110  Predecessor: 30
FingerTables:
| k = 1 (66,67)              succ.: 110 |
| k = 2 (67,69)              succ.: 110 |
| k = 3 (69,73)              succ.: 110 |
| k = 4 (73,81)              succ.: 110 |
| k = 5 (81,97)              succ.: 110 |
| k = 6 (97,129)             succ.: 110 |
| k = 7 (129,193)             succ.: 160 |
| k = 8 (193,65)              succ.: 230 |

------------ Node Id:110 -------------
Successor: 160  Predecessor: 65
FingerTables:
| k = 1 (111,112)             succ.: 160 |
| k = 2 (112,114)             succ.: 160 |
| k = 3 (114,118)             succ.: 160 |
| k = 4 (118,126)             succ.: 160 |
| k = 5 (126,142)             succ.: 160 |
| k = 6 (142,174)             succ.: 160 |
| k = 7 (174,238)             succ.: 230 |
| k = 8 (238,110)             succ.: 0 |

------------ Node Id:160 -------------
Successor: 230  Predecessor: 110
FingerTables:
| k = 1 (161,162)             succ.: 230 |
| k = 2 (162,164)             succ.: 230 |
| k = 3 (164,168)             succ.: 230 |
| k = 4 (168,176)             succ.: 230 |
| k = 5 (176,192)             succ.: 230 |
| k = 6 (192,224)             succ.: 230 |
| k = 7 (224,32)              succ.: 230 |
| k = 8 (32,160)             succ.: 65 |

------------ Node Id:230 -------------
Successor: 0  Predecessor: 160
FingerTables:
| k = 1 (231,232)             succ.: 0 |
| k = 2 (232,234)             succ.: 0 |
| k = 3 (234,238)             succ.: 0 |
| k = 4 (238,246)             succ.: 0 |
| k = 5 (246,6)               succ.: 0 |
| k = 6 (6,38)              succ.: 30 |
| k = 7 (38,102)             succ.: 65 |
| k = 8 (102,230)             succ.: 110 |


=== Inserting Keys ===

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
Look-up result of key 3 from node 0 with path [0,30] value is 3
Look-up result of key 200 from node 0 with path [0,230] value is None
Look-up result of key 123 from node 0 with path [0,160] value is None
Look-up result of key 45 from node 0 with path [0,65] value is 3
Look-up result of key 99 from node 0 with path [0,110] value is None
Look-up result of key 60 from node 0 with path [0,65] value is 10
Look-up result of key 50 from node 0 with path [0,65] value is 8
Look-up result of key 100 from node 0 with path [0,110] value is 5
Look-up result of key 101 from node 0 with path [0,110] value is 4
Look-up result of key 102 from node 0 with path [0,110] value is 6
Look-up result of key 240 from node 0 with path [0] value is 8
Look-up result of key 250 from node 0 with path [0] value is 10

=== Looking Up Keys from Node n2 (id:65) ===
Look-up result of key 3 from node 65 with path [65,30] value is 3
Look-up result of key 200 from node 65 with path [65,230] value is None
Look-up result of key 123 from node 65 with path [65,160] value is None
Look-up result of key 45 from node 65 with path [65] value is 3
Look-up result of key 99 from node 65 with path [65,110] value is None
Look-up result of key 60 from node 65 with path [65] value is 10
Look-up result of key 50 from node 65 with path [65] value is 8
Look-up result of key 100 from node 65 with path [65,110] value is 5
Look-up result of key 101 from node 65 with path [65,110] value is 4
Look-up result of key 102 from node 65 with path [65,110] value is 6
Look-up result of key 240 from node 65 with path [65,0] value is 8
Look-up result of key 250 from node 65 with path [65,0] value is 10

=== Adding New Node n6 (id:100) ===
Node n6 (id:100) joined the network
------------ Node Id:100 -------------
Successor: 110  Predecessor: 65
FingerTables:
| k = 1 (101,102)             succ.: 110 |
| k = 2 (102,104)             succ.: 110 |
| k = 3 (104,108)             succ.: 110 |
| k = 4 (108,116)             succ.: 110 |
| k = 5 (116,132)             succ.: 160 |
| k = 6 (132,164)             succ.: 160 |
| k = 7 (164,228)             succ.: 230 |
| k = 8 (228,100)             succ.: 230 |


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
Look-up result of key 3 from node 100 with path [100,30] value is 3
Look-up result of key 200 from node 100 with path [100,230] value is None
Look-up result of key 123 from node 100 with path [100,160] value is None
Look-up result of key 45 from node 100 with path [100,65] value is 3
Look-up result of key 99 from node 100 with path [100] value is None
Look-up result of key 60 from node 100 with path [100,65] value is 10
Look-up result of key 50 from node 100 with path [100,65] value is 8
Look-up result of key 100 from node 100 with path [100] value is 5
Look-up result of key 101 from node 100 with path [100,110] value is 4
Look-up result of key 102 from node 100 with path [100,110] value is 6
Look-up result of key 240 from node 100 with path [100,0] value is 8
Look-up result of key 250 from node 100 with path [100,0] value is 10

=== Testing Node Leave - Node n2 (id:65) ===
Node 65 is leaving the network
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


=== Print Finger Tables of All Nodes after leaving ===
------------ Node Id:0 -------------
Successor: 30  Predecessor: 230
FingerTables:
| k = 1 (1,2)               succ.: 30 |
| k = 2 (2,4)               succ.: 30 |
| k = 3 (4,8)               succ.: 30 |
| k = 4 (8,16)              succ.: 30 |
| k = 5 (16,32)              succ.: 30 |
| k = 6 (32,64)              succ.: 65 |
| k = 7 (64,128)             succ.: 100 |
| k = 8 (128,0)               succ.: 160 |

------------ Node Id:30 -------------
Successor: 100  Predecessor: 0
FingerTables:
| k = 1 (31,32)              succ.: 100 |
| k = 2 (32,34)              succ.: 100 |
| k = 3 (34,38)              succ.: 100 |
| k = 4 (38,46)              succ.: 100 |
| k = 5 (46,62)              succ.: 100 |
| k = 6 (62,94)              succ.: 100 |
| k = 7 (94,158)             succ.: 100 |
| k = 8 (158,30)              succ.: 160 |

------------ Node Id:110 -------------
Successor: 160  Predecessor: 100
FingerTables:
| k = 1 (111,112)             succ.: 160 |
| k = 2 (112,114)             succ.: 160 |
| k = 3 (114,118)             succ.: 160 |
| k = 4 (118,126)             succ.: 160 |
| k = 5 (126,142)             succ.: 160 |
| k = 6 (142,174)             succ.: 160 |
| k = 7 (174,238)             succ.: 230 |
| k = 8 (238,110)             succ.: 0 |

------------ Node Id:160 -------------
Successor: 230  Predecessor: 110
FingerTables:
| k = 1 (161,162)             succ.: 230 |
| k = 2 (162,164)             succ.: 230 |
| k = 3 (164,168)             succ.: 230 |
| k = 4 (168,176)             succ.: 230 |
| k = 5 (176,192)             succ.: 230 |
| k = 6 (192,224)             succ.: 230 |
| k = 7 (224,32)              succ.: 230 |
| k = 8 (32,160)             succ.: 100 |

------------ Node Id:230 -------------
Successor: 0  Predecessor: 160
FingerTables:
| k = 1 (231,232)             succ.: 0 |
| k = 2 (232,234)             succ.: 0 |
| k = 3 (234,238)             succ.: 0 |
| k = 4 (238,246)             succ.: 0 |
| k = 5 (246,6)               succ.: 0 |
| k = 6 (6,38)              succ.: 30 |
| k = 7 (38,102)             succ.: 65 |
| k = 8 (102,230)             succ.: 110 |

------------ Node Id:100 -------------
Successor: 110  Predecessor: 30
FingerTables:
| k = 1 (101,102)             succ.: 110 |
| k = 2 (102,104)             succ.: 110 |
| k = 3 (104,108)             succ.: 110 |
| k = 4 (108,116)             succ.: 110 |
| k = 5 (116,132)             succ.: 160 |
| k = 6 (132,164)             succ.: 160 |
| k = 7 (164,228)             succ.: 230 |
| k = 8 (228,100)             succ.: 230 |

```
