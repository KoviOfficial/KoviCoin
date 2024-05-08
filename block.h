#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "picosha2.h"
#include "transaction.h"

class Block {
public:
    std::vector<Transaction> transactions; //The data stored in this block
    std::string previousHash; //The hash of the previous block
    std::string hash; //The hash of this block
    long long timestamp; //create time of this block
    int nonce;

    Block(const std::vector<Transaction>& transactions, const std::string& previousHash) :
        transactions(transactions), previousHash(previousHash) {
        nonce = 1;
        hash = calculateHash();
        timestamp = getTimestamp();
    }

    long long getTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto timestamp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        return timestamp_ms;
    }

    //calculate hash of this block.
    std::string calculateHash() {
        std::string data;
        for(auto & transaction : transactions) {
            data += transaction.from + transaction.to + std::to_string(transaction.amount);
        }
        std::string target = data+previousHash+std::to_string(nonce)+std::to_string(timestamp);
        std::string ret;
        picosha2::hash256_hex_string(target, ret);
        return ret;
    }

    std::string getAnswer(int difficulty) {
        std::string answer = "";
        for(int i = 0;i < difficulty;i++) {
            answer += "0";
        }
        return answer;
    }

    std::string mine(int difficulty) {
        std::string target = getAnswer(difficulty);
        std::string ret;
        std::cout<<"开始挖矿！"<<std::endl;
        auto start = std::chrono::system_clock::now();
        while(ret.substr(0, difficulty) != getAnswer(difficulty)) {
            ret = calculateHash();
            nonce++;
        }
        nonce--;
        auto end = std::chrono::system_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout<<"挖矿结束！"<<std::endl;
        std::cout<<"耗时："<<duration_ms.count()<<"ms"<<std::endl;
        std::cout<<"nonce: "<<nonce<<std::endl;
        std::cout<<"hash: "<<ret<<std::endl;
        return ret;
    }
};