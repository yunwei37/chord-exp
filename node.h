#ifndef NODE_H
#define NODE_H

#include <stdint.h>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <tuple>

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
	explicit FingerTable(uint8_t nodeId);
	// Default constructor for Node initialization
	FingerTable() : nodeId_(0) {}
	void set(int index, Node* node) { fingerTable_[index] = node; }
	Node* get(int index) const { return fingerTable_[index]; }
	// TODO: complete print function
	void prettyPrint() const;
	std::vector<std::tuple<int, uint16_t, uint16_t, uint8_t>> getFingerTableData() const;
private:
	uint8_t nodeId_;
	std::vector<Node*> fingerTable_;
};

class Node {
public:
	explicit Node(uint8_t id) : id_(id), fingerTable_(id) {}
	
	void join(Node* node);
	void leave();
	void insert(uint8_t key, uint8_t value = 0);
	uint8_t find(uint8_t key);
	void remove(uint8_t key);
	
	Node* findSuccessor(uint8_t id);
	Node* findPredecessor(uint8_t id);
	Node* closestPrecedingFinger(uint8_t id);
	
	uint8_t getId() const { return id_; }
	Node* getSuccessor() const;
	Node* getPredecessor() const;
	void setPredecessor(Node* pred);
	const std::map<uint8_t, uint8_t>& getLocalKeys() const { return localKeys_; }
	std::vector<std::tuple<int, uint16_t, uint16_t, uint8_t>> getFingerTableData() const {
		return fingerTable_.getFingerTableData();
	}

private:
	uint8_t id_;
	Node* predecessor_ = nullptr;
	FingerTable fingerTable_;
	std::map<uint8_t, uint8_t> localKeys_;
	
	void updateOthers();
	void updateFingerTable(Node* s, int i);
	void transferKeys();
	bool isResponsibleForKey(uint8_t key) const {
		if (predecessor_->getId() >= id_) {
			return key > predecessor_->getId() || key <= id_;
		}
		return key > predecessor_->getId() && key <= id_;
	}
};

#endif
