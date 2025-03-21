#include "node.h"
#include <iostream>
#include <iomanip>
#include <sstream>

FingerTable::FingerTable(uint8_t nodeId): nodeId_(nodeId) {
	// According to Chord paper, the finger table starts from index=1
	fingerTable_.resize(BITLENGTH + 1);
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