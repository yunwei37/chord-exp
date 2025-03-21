#include "node.h"
#include <iostream>
#include <string>
#include <vector>

void printDivider() {
    std::cout << "=========================================" << std::endl;
}

int main() {
    std::cout << "Chord DHT Implementation Test" << std::endl;
    printDivider();
    
    std::cout << "1. Creating nodes with specific IDs" << std::endl;
    // Create nodes
    Node n0(0);
    Node n1(30);
    Node n2(65);
    Node n3(110);
    Node n4(160);
    Node n5(230);
    
    printDivider();
    std::cout << "2. Building the Chord ring" << std::endl;
    
    // Join the first node (creates the network)
    std::cout << "\nNode 0 (id: 0) joins the network:" << std::endl;
    n0.join(nullptr);
    
    // Join the other nodes
    std::cout << "\nNode 1 (id: 30) joins the network:" << std::endl;
    n1.join(&n0);
    
    std::cout << "\nNode 2 (id: 65) joins the network:" << std::endl;
    n2.join(&n1);
    
    std::cout << "\nNode 3 (id: 110) joins the network:" << std::endl;
    n3.join(&n2);
    
    std::cout << "\nNode 4 (id: 160) joins the network:" << std::endl;
    n4.join(&n3);
    
    std::cout << "\nNode 5 (id: 230) joins the network:" << std::endl;
    n5.join(&n4);
    
    printDivider();
    std::cout << "3. Inserting keys into the DHT" << std::endl;
    
    n0.insert(3, 3);
    n1.insert(200);
    n2.insert(123);
    n3.insert(45, 3);
    n4.insert(99);
    n2.insert(60, 10);
    n0.insert(50, 8);
    n3.insert(100, 5);
    n3.insert(101, 4);
    n3.insert(102, 6);
    n5.insert(240, 8);
    n5.insert(250, 10);
    
    printDivider();
    std::cout << "4. Key distribution across nodes:" << std::endl;
    
    n0.printKeys();
    n1.printKeys();
    n2.printKeys();
    n3.printKeys();
    n4.printKeys();
    n5.printKeys();
    
    printDivider();
    std::cout << "5. Looking up keys from node 0:" << std::endl;
    
    n0.find(3);
    n0.find(200);
    n0.find(123);
    n0.find(45);
    n0.find(99);
    n0.find(60);
    n0.find(50);
    n0.find(100);
    n0.find(101);
    n0.find(102);
    n0.find(240);
    n0.find(250);
    
    printDivider();
    std::cout << "6. Looking up keys from node 2 (id: 65):" << std::endl;
    
    n2.find(3);
    n2.find(200);
    n2.find(123);
    n2.find(45);
    n2.find(99);
    n2.find(60);
    n2.find(50);
    
    printDivider();
    std::cout << "7. Adding a new node and observing key migration" << std::endl;
    
    // Create a new node with ID 100
    Node n6(100);
    std::cout << "\nNode 6 (id: 100) joins the network:" << std::endl;
    n6.join(&n0);
    
    printDivider();
    std::cout << "8. Updated key distribution across nodes:" << std::endl;
    
    n0.printKeys();
    n1.printKeys();
    n2.printKeys();
    n6.printKeys(); // New node
    n3.printKeys();
    n4.printKeys();
    n5.printKeys();
    
    printDivider();
    std::cout << "9. Looking up keys from node 6 (id: 100):" << std::endl;
    
    n6.find(3);
    n6.find(200);
    n6.find(123);
    n6.find(45);
    n6.find(99);
    n6.find(60);
    n6.find(50);
    
    printDivider();
    std::cout << "10. Testing node departure - Node 2 (id: 65) leaves the network" << std::endl;
    
    n2.leave();
    
    printDivider();
    std::cout << "11. Updated finger tables after node departure:" << std::endl;
    
    n0.printNodeInfo();
    n1.printNodeInfo();
    n6.printNodeInfo();
    n3.printNodeInfo();
    n4.printNodeInfo();
    n5.printNodeInfo();
    
    printDivider();
    std::cout << "12. Final key distribution after node departure:" << std::endl;
    
    n0.printKeys();
    n1.printKeys();
    n6.printKeys();
    n3.printKeys();
    n4.printKeys();
    n5.printKeys();
    
    return 0;
} 