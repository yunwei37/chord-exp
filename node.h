#ifndef NODE_H
#define NODE_H

#include <stdint.h>
#include <map>
#include <set>
#include <vector>
#include <iostream>

#define BITLENGTH 8

//forward declaration
class Node;

//The following code is just for reference. You can define your own finger table class.
//Since the index uniquely determines the interval, only the successor needs to be maintained.  
class FingerTable{
public:
	/**
	 * @param nodeId: the id of node hosting the finger table.
	 */
	FingerTable(uint8_t nodeId);
	// Default constructor for Node initialization
	FingerTable() : nodeId_(0) {}
	void set(size_t index, Node* successor){
		fingerTable_[index] = successor;
	}
	Node* get(size_t index) const {
		return fingerTable_[index];
	}
	// TODO: complete print function
	void prettyPrint() const;
private:
	uint8_t nodeId_;
	mutable std::vector<Node*> fingerTable_;
};

class Node {
public:
	Node(uint8_t id): id_(id), fingerTable_(id) {}
	//TODO: implement node join function
	/**
	 * @param node: the first node to contact with to initialize join process. If this is the first node to join the Chord network, the parameter is NULL.
	 */
	void join(Node* node);
	//TODO: implement DHT lookup
	uint8_t find(uint8_t key);
	//TODO: implement DHT key insertion
	void insert(uint8_t key, uint8_t value = 0);
	//TODO: implement DHT key deletion
	void remove(uint8_t key);
    // For leave operation (optional)
    void leave();
    
    // Additional utility functions
    Node* findSuccessor(uint8_t id);
    Node* findPredecessor(uint8_t id);
    Node* closestPrecedingFinger(uint8_t id);
    void updateOthers();
    void updateFingerTable(Node* s, int i);
    void transferKeys();
    
    // Getters for testing
    uint8_t getId() const { return id_; }
    Node* getSuccessor() const;
    Node* getPredecessor() const;
    const std::map<uint8_t, uint8_t>& getLocalKeys() const { return localKeys_; }
    const FingerTable& getFingerTable() const { return fingerTable_; }
    
    // Setters for internal use
    void setPredecessor(Node* pred);
    
private:
	uint8_t id_;
	FingerTable fingerTable_;
	std::map<uint8_t, uint8_t> localKeys_;
    Node* predecessor_ = nullptr;  // Predecessor node
};

#endif
