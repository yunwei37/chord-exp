#include "node.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Helper function to check if id is in range (start, end) on the Chord ring
bool inRange(uint8_t id, uint8_t start, uint8_t end) {
    if (start < end) {
        return (id > start && id <= end);
    } else {  // Wrapping around the circle
        return (id > start || id <= end);
    }
}

// Join node to the Chord network
void Node::join(Node* node) {
    if (node == nullptr) {
        // This is the first node in the network
        for (int i = 1; i <= BITLENGTH; i++) {
            fingerTable_.set(i, this);  // All fingers point to itself
        }
        predecessor_ = this;  // Set predecessor to itself
        std::cout << "------------ Node Id:" << (int)id_ << " -------------" << std::endl;
        std::cout << "Successor: " << (int)getSuccessor()->getId() << "  Predecessor: " << (int)getPredecessor()->getId() << std::endl;
        fingerTable_.prettyPrint();
    } else {
        // Join the network using node as an entry point
        
        // Initialize finger table
        fingerTable_.set(1, node->findSuccessor(id_ + 1));  // First finger
        
        std::cout << "Node " << (int)id_ << " is joining through node " << (int)node->getId() << std::endl;
        
        // Initialize predecessor
        predecessor_ = getSuccessor()->getPredecessor();
        getSuccessor()->setPredecessor(this);
        
        // Fill the rest of the finger table
        for (int i = 1; i < BITLENGTH; i++) {
            uint8_t next_finger_id = (id_ + (1 << i)) & ((1 << BITLENGTH) - 1);
            
            if (inRange(next_finger_id, id_, fingerTable_.get(i)->getId())) {
                // If next finger id is in the range, reuse the current finger
                fingerTable_.set(i + 1, fingerTable_.get(i));
            } else {
                // Otherwise, find the correct successor
                fingerTable_.set(i + 1, node->findSuccessor(next_finger_id));
            }
        }
        
        // Update all nodes whose finger tables should refer to this node
        updateOthers();
        
        // Transfer keys that this node is now responsible for
        transferKeys();
        
        // Print finger table
        std::cout << "------------ Node Id:" << (int)id_ << " -------------" << std::endl;
        std::cout << "Successor: " << (int)getSuccessor()->getId() << "  Predecessor: " << (int)getPredecessor()->getId() << std::endl;
        fingerTable_.prettyPrint();
    }
}

// Find the successor node of an identifier
Node* Node::findSuccessor(uint8_t id) {
    Node* n = findPredecessor(id);
    return n->getSuccessor();
}

// Find the predecessor node of an identifier
Node* Node::findPredecessor(uint8_t id) {
    Node* n = this;
    while (!inRange(id, n->getId(), n->getSuccessor()->getId())) {
        n = n->closestPrecedingFinger(id);
    }
    return n;
}

// Find the closest finger preceding id
Node* Node::closestPrecedingFinger(uint8_t id) {
    for (int i = BITLENGTH; i >= 1; i--) {
        Node* finger = fingerTable_.get(i);
        if (finger != nullptr && inRange(finger->getId(), id_, id)) {
            return finger;
        }
    }
    return this;
}

// Get the successor of the node
Node* Node::getSuccessor() const {
    return fingerTable_.get(1);
}

// Get the predecessor of the node
Node* Node::getPredecessor() const {
    return predecessor_;
}

// Set the predecessor of the node
void Node::setPredecessor(Node* pred) {
    predecessor_ = pred;
}

// Update all nodes whose finger tables should now point to this node
void Node::updateOthers() {
    for (int i = 1; i <= BITLENGTH; i++) {
        // Find the last node p whose i-th finger might be this node
        uint8_t p_id = (id_ - (1 << (i-1)) + (1 << BITLENGTH)) & ((1 << BITLENGTH) - 1);
        Node* p = findPredecessor(p_id);
        
        // Update p's finger table
        p->updateFingerTable(this, i);
    }
}

// Update finger table with node s at index i
void Node::updateFingerTable(Node* s, int i) {
    uint8_t s_id = s->getId();
    uint8_t start = (id_ + (1 << (i-1))) & ((1 << BITLENGTH) - 1);
    
    // If s is in the range of the i-th finger
    if (fingerTable_.get(i) == nullptr || 
        inRange(s_id, start, fingerTable_.get(i)->getId())) {
        fingerTable_.set(i, s);
        
        // Propagate the update
        Node* p = predecessor_;
        if (p != this) {  // Not the only node
            p->updateFingerTable(s, i);
        }
    }
}

// Transfer keys that belong to this node
void Node::transferKeys() {
    if (predecessor_ == this) {
        return;  // No keys to transfer if only one node
    }
    
    Node* successor = getSuccessor();
    std::vector<uint8_t> keysToTransfer;
    
    // Check which keys in successor should be moved to this node
    for (const auto& pair : successor->getLocalKeys()) {
        uint8_t key = pair.first;
        if (inRange(key, predecessor_->getId(), id_)) {
            keysToTransfer.push_back(key);
            // Insert into this node
            localKeys_[key] = pair.second;
            std::cout << "Key " << (int)key << " moved from node " << (int)successor->getId() 
                      << " to node " << (int)id_ << std::endl;
        }
    }
    
    // Remove transferred keys from successor
    for (uint8_t key : keysToTransfer) {
        successor->remove(key);
    }
}

// Lookup a key in the DHT
uint8_t Node::find(uint8_t key) {
    std::vector<int> path;
    path.push_back(id_);  // Start with this node
    
    // If the key is stored locally
    if (localKeys_.find(key) != localKeys_.end()) {
        // Print the path and return the value
        std::cout << "Look-up result of key " << (int)key << " from node " << (int)id_
                  << " with path [";
        for (size_t i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i < path.size() - 1) std::cout << ",";
        }
        std::cout << "] value is " << (int)localKeys_[key] << std::endl;
        
        return localKeys_[key];
    }
    
    // Key not stored locally, find the responsible node
    Node* nextNode = findSuccessor(key);
    
    // If the next node is this node, key doesn't exist
    if (nextNode == this) {
        std::cout << "Look-up result of key " << (int)key << " from node " << (int)id_
                  << " with path [" << (int)id_ << "] key not found" << std::endl;
        return 0;  // Key not found
    }
    
    // Add the next node to the path and continue the lookup
    path.push_back(nextNode->getId());
    
    // Get the value from the next node
    uint8_t value = nextNode->find(key);
    
    // Print the path and result
    std::cout << "Look-up result of key " << (int)key << " from node " << (int)id_
              << " with path [";
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1) std::cout << ",";
    }
    std::cout << "] value is " << (int)value << std::endl;
    
    return value;
}

// Insert a key-value pair into the DHT
void Node::insert(uint8_t key, uint8_t value) {
    // Find the node responsible for the key
    Node* responsibleNode = findSuccessor(key);
    
    // Insert the key-value pair into the responsible node
    responsibleNode->localKeys_[key] = value;
    std::cout << "Key " << (int)key << " with value " << (int)value 
              << " inserted at node " << (int)responsibleNode->getId() << std::endl;
}

// Remove a key from the DHT
void Node::remove(uint8_t key) {
    // Check if the key is stored locally
    auto it = localKeys_.find(key);
    if (it != localKeys_.end()) {
        // Remove the key
        localKeys_.erase(it);
        std::cout << "Key " << (int)key << " removed from node " << (int)id_ << std::endl;
        return;
    }
    
    // If not stored locally, find the responsible node
    Node* responsibleNode = findSuccessor(key);
    
    // Remove the key from the responsible node
    if (responsibleNode != this) {
        responsibleNode->remove(key);
    } else {
        std::cout << "Key " << (int)key << " not found in the DHT" << std::endl;
    }
}

// Leave the Chord network (optional)
void Node::leave() {
    if (predecessor_ == this && getSuccessor() == this) {
        std::cout << "Node " << (int)id_ << " is the only node in the network" << std::endl;
        return;
    }
    
    // Notify successor and predecessor
    getSuccessor()->setPredecessor(predecessor_);
    predecessor_->fingerTable_.set(1, getSuccessor());
    
    // Transfer keys to successor
    for (const auto& pair : localKeys_) {
        getSuccessor()->localKeys_[pair.first] = pair.second;
        std::cout << "Key " << (int)pair.first << " moved from node " << (int)id_ 
                  << " to node " << (int)getSuccessor()->getId() << std::endl;
    }
    
    // Update finger tables of other nodes
    for (int i = 1; i <= BITLENGTH; i++) {
        // Find nodes that might have this node in their finger table
        uint8_t p_id = (id_ - (1 << (i-1)) + (1 << BITLENGTH)) & ((1 << BITLENGTH) - 1);
        Node* p = findPredecessor(p_id);
        
        // Update the finger table entry if it points to this node
        if (p->fingerTable_.get(i) == this) {
            p->fingerTable_.set(i, getSuccessor());
        }
    }
    
    std::cout << "Node " << (int)id_ << " has left the network" << std::endl;
    
    // Clear local data
    localKeys_.clear();
    predecessor_ = nullptr;
    for (int i = 1; i <= BITLENGTH; i++) {
        fingerTable_.set(i, nullptr);
    }
} 