#include "node.h"
#include <iostream>
#include <vector>
#include <string>

// Function to print details of all nodes in the network
void printNetworkDetails(const std::vector<Node*>& nodes) {
    std::cout << "\n=== Network Details ===" << std::endl;
    for (const auto& node : nodes) {
        std::cout << "------------- Node id:" << (int)node->getId() << " --------------" << std::endl;
        std::cout << "Keys: {";
        bool first = true;
        for (const auto& pair : node->getLocalKeys()) {
            if (!first) std::cout << ", ";
            first = false;
            std::cout << (int)pair.first << ": ";
            if (pair.second == 0) {
                std::cout << "None";
            } else {
                std::cout << (int)pair.second;
            }
        }
        std::cout << "}" << std::endl << std::endl;
    }
}

int main() {
    std::cout << "=== Chord DHT Test Case ===" << std::endl;
    std::cout << "Setting up Chord network with m = " << BITLENGTH << std::endl;
    
    // Step 1: Create nodes with given identifiers
    std::cout << "\n=== Creating Nodes ===" << std::endl;
    Node* n0 = new Node(0);
    Node* n1 = new Node(30);
    Node* n2 = new Node(65);
    Node* n3 = new Node(110);
    Node* n4 = new Node(160);
    Node* n5 = new Node(230);
    
    std::vector<Node*> nodes = {n0, n1, n2, n3, n4, n5};
    
    std::cout << "Created nodes with ids: 0, 30, 65, 110, 160, 230" << std::endl;
    
    // Step 2: Joining nodes to form the network
    std::cout << "\n=== Joining Nodes to Network ===" << std::endl;
    n0->join(nullptr);   // First node creates the network
    std::cout << "\nNode n0 (id:0) joined the network as the first node" << std::endl;
    
    n1->join(n0);
    std::cout << "\nNode n1 (id:30) joined the network" << std::endl;
    
    n2->join(n1);
    std::cout << "\nNode n2 (id:65) joined the network" << std::endl;
    
    n3->join(n2);
    std::cout << "\nNode n3 (id:110) joined the network" << std::endl;
    
    n4->join(n3);
    std::cout << "\nNode n4 (id:160) joined the network" << std::endl;
    
    n5->join(n4);
    std::cout << "\nNode n5 (id:230) joined the network" << std::endl;
    
    // Step 3: Insert keys
    std::cout << "\n=== Inserting Keys ===" << std::endl;
    n0->insert(3, 3);
    n1->insert(200);
    n2->insert(123);
    n3->insert(45, 3);
    n4->insert(99);
    n2->insert(60, 10);
    n0->insert(50, 8);
    n3->insert(100, 5);
    n3->insert(101, 4);
    n3->insert(102, 6);
    n5->insert(240, 8);
    n5->insert(250, 10);
    
    // Print the keys stored in each node
    printNetworkDetails(nodes);
    
    // Step 4: Look up keys
    std::cout << "\n=== Looking Up Keys from Node n0 (id:0) ===" << std::endl;
    n0->find(3);
    n0->find(200);
    n0->find(123);
    n0->find(45);
    n0->find(99);
    n0->find(60);
    n0->find(50);
    n0->find(100);
    n0->find(101);
    n0->find(102);
    n0->find(240);
    n0->find(250);
    
    std::cout << "\n=== Looking Up Keys from Node n2 (id:65) ===" << std::endl;
    n2->find(3);
    n2->find(200);
    n2->find(123);
    n2->find(45);
    n2->find(99);
    n2->find(60);
    n2->find(50);
    n2->find(100);
    n2->find(101);
    n2->find(102);
    n2->find(240);
    n2->find(250);
    
    // Step 5: Add a new node and show key migration
    std::cout << "\n=== Adding New Node n6 (id:100) ===" << std::endl;
    Node* n6 = new Node(100);
    n6->join(n5);
    nodes.push_back(n6);
    
    // Print the updated network details
    printNetworkDetails(nodes);
    
    // Step 6: Look up keys from the new node
    std::cout << "\n=== Looking Up Keys from New Node n6 (id:100) ===" << std::endl;
    n6->find(3);
    n6->find(200);
    n6->find(123);
    n6->find(45);
    n6->find(99);
    n6->find(60);
    n6->find(50);
    n6->find(100);
    n6->find(101);
    n6->find(102);
    n6->find(240);
    n6->find(250);
    
    // Step 7: Test node leave (optional)
    std::cout << "\n=== Testing Node Leave - Node n2 (id:65) ===" << std::endl;
    n2->leave();
    
    // Remove n2 from nodes vector
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (*it == n2) {
            nodes.erase(it);
            break;
        }
    }
    
    // Print the updated network details
    printNetworkDetails(nodes);
    
    // Clean up
    delete n0;
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;
    
    return 0;
} 