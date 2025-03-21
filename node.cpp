#include "node.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>

// Helper function to check if key is in the range (start, end]
bool inRange(uint8_t key, uint8_t start, uint8_t end) {
    if (start == end) return true;
    if (start < end) return (key > start && key <= end);
    return (key > start || key <= end); // Wrapping around the circle
}

// Helper function to check if key is in the range [start, end)
bool inRangeInclusive(uint8_t key, uint8_t start, uint8_t end) {
    if (start == end) return true;
    if (start < end) return (key >= start && key < end);
    return (key >= start || key < end); // Wrapping around the circle
}

// Print the finger table
void FingerTable::prettyPrint() {
    std::cout << "FingerTables:" << std::endl;
    for (size_t k = 1; k <= BITLENGTH; k++) {
        uint8_t start = (nodeId_ + static_cast<uint8_t>(pow(2, k-1))) % static_cast<uint8_t>(pow(2, BITLENGTH));
        uint8_t end = (nodeId_ + static_cast<uint8_t>(pow(2, k))) % static_cast<uint8_t>(pow(2, BITLENGTH));
        std::cout << "| k = " << k << " (" << (int)start << "," << (int)end << ")";
        std::cout << "\tsucc.: " << (fingerTable_[k] ? (int)fingerTable_[k]->getId() : -1) << " |" << std::endl;
    }
}

// Add getId method to get node id
uint8_t Node::getId() const {
    return id_;
}

// Get successor node
Node* Node::getSuccessor() const {
    return successor_;
}

// Get predecessor node
Node* Node::getPredecessor() const {
    return predecessor_;
}

// Set successor node
void Node::setSuccessor(Node* succ) {
    successor_ = succ;
}

// Set predecessor node
void Node::setPredecessor(Node* pred) {
    predecessor_ = pred;
}

// Print node information
void Node::printNodeInfo() const {
    std::cout << "------------ Node Id:" << (int)id_ << " -------------" << std::endl;
    std::cout << "Successor: " << (successor_ ? (int)successor_->getId() : -1);
    std::cout << "  Predecessor: " << (predecessor_ ? (int)predecessor_->getId() : -1) << std::endl;
    fingerTable_.prettyPrint();
    std::cout << std::endl;
}

// Print node keys
void Node::printKeys() const {
    std::cout << "------------- Node id:" << (int)id_ << " --------------" << std::endl;
    std::cout << "{";
    bool first = true;
    for (auto const& pair : localKeys_) {
        if (!first) std::cout << ", ";
        first = false;
        std::cout << (int)pair.first << ": " << (pair.second == 0 ? "None" : std::to_string(pair.second));
    }
    std::cout << "}" << std::endl << std::endl;
}

// Find the closest predecessor of id
Node* Node::findClosestPrecedingNode(uint8_t key) {
    for (int i = BITLENGTH; i >= 1; i--) {
        if (fingerTable_.get(i) && inRange(fingerTable_.get(i)->getId(), id_, key)) {
            return fingerTable_.get(i);
        }
    }
    return this;
}

// Find the successor of id
Node* Node::findSuccessor(uint8_t key) {
    // If key is in (n, successor], return successor
    if (inRange(key, id_, successor_->getId())) {
        return successor_;
    }
    // Otherwise, find the closest preceding node and ask it to find successor
    Node* n0 = findClosestPrecedingNode(key);
    if (n0 == this) {
        return successor_;
    }
    return n0->findSuccessor(key);
}

// Initialize finger table using a node in the network
void Node::initFingerTable(Node* node) {
    if (node == nullptr) {
        // First node in the network
        successor_ = this;
        predecessor_ = this;
        for (int i = 1; i <= BITLENGTH; i++) {
            fingerTable_.set(i, this);
        }
    } else {
        // Find successor using existing node
        uint8_t start = (id_ + 1) % 256;
        successor_ = node->findSuccessor(start);
        predecessor_ = successor_->getPredecessor();
        successor_->setPredecessor(this);
        
        // Initialize finger table
        fingerTable_.set(1, successor_);
        
        // Fill the rest of the finger table
        for (int i = 1; i < BITLENGTH; i++) {
            uint8_t start = (id_ + static_cast<uint8_t>(pow(2, i))) % 256;
            
            if (inRange(start, id_, fingerTable_.get(i)->getId())) {
                fingerTable_.set(i + 1, fingerTable_.get(i));
            } else {
                fingerTable_.set(i + 1, node->findSuccessor(start));
            }
        }
    }
}

// Update others' finger tables when this node joins
void Node::updateOthers() {
    // For each finger i, find the node p whose ith finger might be this node
    for (int i = 1; i <= BITLENGTH; i++) {
        // Find last node whose ith finger might be this node
        uint8_t p = (id_ - static_cast<uint8_t>(pow(2, i-1)) + 256) % 256; // +256 to handle underflow
        
        // Find the predecessor of p
        Node* pred = findSuccessor(p);
        if (pred != this) { // Don't update self
            pred->updateFingerTable(this, i);
        }
    }
}

// Update finger table with new node s at index i
void Node::updateFingerTable(Node* s, int i) {
    uint8_t start = (id_ + static_cast<uint8_t>(pow(2, i-1))) % 256;
    
    // If s is in range (n, finger[i]), update finger[i] = s
    if (inRange(s->getId(), id_, fingerTable_.get(i)->getId())) {
        fingerTable_.set(i, s);
        
        // Propagate the update
        Node* p = predecessor_;
        if (p != s) { // Avoid infinite loop
            p->updateFingerTable(s, i);
        }
    }
}

// Node join function
void Node::join(Node* node) {
    // Initialize finger table
    initFingerTable(node);
    
    // Update others' finger tables
    if (node != nullptr) {
        updateOthers();
        
        // Migrate keys
        std::vector<uint8_t> keysToMigrate;
        for (auto const& pair : successor_->getLocalKeys()) {
            if (inRange(pair.first, predecessor_->getId(), id_)) {
                keysToMigrate.push_back(pair.first);
                localKeys_[pair.first] = pair.second;
            }
        }
        
        // Remove migrated keys from successor
        for (uint8_t key : keysToMigrate) {
            successor_->removeLocal(key);
        }
        
        if (!keysToMigrate.empty()) {
            std::cout << "Keys migrated to node " << (int)id_ << ": ";
            for (size_t i = 0; i < keysToMigrate.size(); i++) {
                if (i > 0) std::cout << ", ";
                std::cout << (int)keysToMigrate[i];
            }
            std::cout << std::endl;
        }
    }
    
    // Print finger table
    printNodeInfo();
}

// Find key, return its value
uint8_t Node::find(uint8_t key) {
    std::vector<int> path;
    path.push_back(id_);
    
    return findWithPath(key, path);
}

// Find key with path tracking
uint8_t Node::findWithPath(uint8_t key, std::vector<int>& path) {
    // Check if key is in local keys
    if (localKeys_.find(key) != localKeys_.end()) {
        // Print the path
        std::cout << "Look-up result of key " << (int)key << " from node " << (int)path[0] 
                  << " with path [";
        for (size_t i = 0; i < path.size(); i++) {
            if (i > 0) std::cout << ",";
            std::cout << path[i];
        }
        std::cout << "] value is " << (localKeys_[key] == 0 ? "None" : std::to_string(localKeys_[key])) << std::endl;
        
        return localKeys_[key];
    }
    
    // Find the node responsible for the key
    Node* responsibleNode = findSuccessor(key);
    
    // If it's this node, key doesn't exist
    if (responsibleNode == this) {
        std::cout << "Look-up result of key " << (int)key << " from node " << (int)path[0] 
                  << " with path [";
        for (size_t i = 0; i < path.size(); i++) {
            if (i > 0) std::cout << ",";
            std::cout << path[i];
        }
        std::cout << "] value is None" << std::endl;
        return 0;
    }
    
    // Add node to path and forward the query
    path.push_back(responsibleNode->getId());
    return responsibleNode->findWithPath(key, path);
}

// Insert key with optional value
void Node::insert(uint8_t key, uint8_t value) {
    // Find the node responsible for the key
    Node* responsibleNode = findSuccessor(key);
    
    // Insert the key-value pair
    responsibleNode->localKeys_[key] = value;
}

// Insert key without value (value = 0)
void Node::insert(uint8_t key) {
    insert(key, 0);
}

// Remove key from local storage
void Node::removeLocal(uint8_t key) {
    localKeys_.erase(key);
}

// Remove key from DHT
void Node::remove(uint8_t key) {
    // Find the node responsible for the key
    Node* responsibleNode = findSuccessor(key);
    
    // Remove the key
    responsibleNode->removeLocal(key);
}

// Leave the network
void Node::leave() {
    if (successor_ == this) {
        // Only node in the network
        return;
    }
    
    // Transfer keys to successor
    for (auto const& pair : localKeys_) {
        successor_->localKeys_[pair.first] = pair.second;
    }
    
    // Update predecessor of successor
    successor_->setPredecessor(predecessor_);
    
    // Update successor of predecessor
    predecessor_->setSuccessor(successor_);
    
    // Update finger tables of other nodes
    for (int i = 1; i <= BITLENGTH; i++) {
        // Find nodes that have this node in their finger table
        uint8_t p = (id_ - static_cast<uint8_t>(pow(2, i-1)) + 256) % 256;
        Node* pred = findSuccessor(p);
        
        if (pred != this) {
            pred->fixFingerTableOnLeave(this);
        }
    }
    
    std::cout << "Node " << (int)id_ << " has left the network." << std::endl;
}

// Fix finger table when a node leaves
void Node::fixFingerTableOnLeave(Node* leavingNode) {
    for (int i = 1; i <= BITLENGTH; i++) {
        if (fingerTable_.get(i) == leavingNode) {
            fingerTable_.set(i, leavingNode->getSuccessor());
        }
    }
}

// Get local keys map
const std::map<uint8_t, uint8_t>& Node::getLocalKeys() const {
    return localKeys_;
}

// Get finger table
FingerTable& Node::getFingerTable() {
    return fingerTable_;
} 