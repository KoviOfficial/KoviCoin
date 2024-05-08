#pragma once
#include <iostream>
#include "picosha2.h"

class Transaction {
public:
    std::string from;
    std::string to;
    int amount;

    Transaction(const std::string& from, const std::string& to, int amount) :
        from(from), to(to), amount(amount)
    {}

//    std::string calculateHash() {
//        std::string hash;
//        picosha2::hash256_hex_string(from + to + std::to_string(amount), hash);
//    }
//
//    void sign() {
//        // sign transaction
//    }
};