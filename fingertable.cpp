#include "node.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <tuple>

FingerTable::FingerTable(uint8_t nodeId): nodeId_(nodeId) {
	// According to Chord paper, the finger table starts from index=1
	fingerTable_.resize(BITLENGTH + 1);
}

// Get finger table data as a vector of tuples (k, start, end, successor_id)
std::vector<std::tuple<int, uint16_t, uint16_t, uint8_t>> FingerTable::getFingerTableData() const {
    std::vector<std::tuple<int, uint16_t, uint16_t, uint8_t>> data;
    
    for (int k = 1; k <= BITLENGTH; k++) {
        // Calculate interval start: (n + 2^(k-1)) mod 2^m
        uint16_t start = (nodeId_ + (1 << (k-1))) & ((1 << BITLENGTH) - 1);
        
        // Calculate interval end: (n + 2^k) mod 2^m
        uint16_t end = (nodeId_ + (1 << k)) & ((1 << BITLENGTH) - 1);
        
        // Get successor ID
        uint8_t succ_id = fingerTable_[k] != nullptr ? fingerTable_[k]->getId() : 0;
        
        data.push_back(std::make_tuple(k, start, end, succ_id));
    }
    
    return data;
}

void FingerTable::prettyPrint() const {
    std::cout << "FingerTables:" << std::endl;
    
    for (int k = 1; k <= BITLENGTH; k++) {
        // Calculate interval start: (n + 2^(k-1)) mod 2^m
        uint16_t start = (nodeId_ + (1 << (k-1))) & ((1 << BITLENGTH) - 1);
        
        // Calculate interval end: (n + 2^k) mod 2^m
        uint16_t end = (nodeId_ + (1 << k)) & ((1 << BITLENGTH) - 1);
        
        std::cout << "| k = " << k << " (" << start << "," << end << ")";
        
        // Add padding
        std::cout << std::string(10 - std::to_string(end).length(), ' ');
        
        // Print successor ID
        if (fingerTable_[k] != nullptr) {
            std::cout << "succ.: " << (int)fingerTable_[k]->getId() << " |" << std::endl;
        } else {
            std::cout << "succ.: NULL |" << std::endl;
        }
    }
} 