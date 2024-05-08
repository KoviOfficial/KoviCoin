#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "picosha2.h"
#include "block.h"


//the chain of block
class chain {
public:
    std::vector<Block> blocks;
    int difficulty;
    std::vector<Transaction> transactionsPool;
    int minerReward;

chain()
    :difficulty(5),
     minerReward(50),
     transactionsPool(),
     blocks() { // initialize the blocks

    Transaction preTransaction("Genesis Transaction", "Genesis Transaction", 0);
    // 创建创世区块的临时对象
    Block genesisBlock({preTransaction}, "0");
    //genesisBlock.hash = genesisBlock.mine(difficulty); // 计算创世区块的哈希
    picosha2::hash256_hex_string(genesisBlock.calculateHash(), genesisBlock.hash);
    // 将创世区块添加到blocks向量中
    blocks.push_back(std::move(genesisBlock)); // 使用std::move避免不必要的复制
}


    int getLatestBLock() {
        return blocks.size() - 1;
    }

    //add transaction to the transactionsPool
    void addTransaction(Transaction transaction) {
        transactionsPool.push_back(transaction);
    }


    void mineTransactionPool(const std::string& minerRewardAddress) {
        //send the reward to the miner
        //minerRewardAddress: the account of the miner.
        Transaction minerRewardTransaction("", minerRewardAddress, minerReward);
        transactionsPool.push_back(minerRewardTransaction);
//        //create a temporary list to store transactions that will be included in the new block
//        std::vector<Transaction> selectedTransactions;

        //mining
        Block newBlock(transactionsPool, blocks[getLatestBLock()].hash);
        newBlock.mine(difficulty);
        //add the block to the chain
        //clear the transaction pool
        blocks.push_back(newBlock);
        transactionsPool.clear();
    }

    //check the chain is valid or not
    bool verifyChain() {
        if(blocks.size() == 1) {
            return true;
        }
        //start verifying from the second block to the last block
        for(int i = 1;i < blocks.size();i++) {
            if(blocks[i].hash != blocks[i].calculateHash()) {
                std::cout<<"数据篡改！"<<std::endl;
                return false;
            }
            if(blocks[i].previousHash != blocks[i - 1].hash) {
                std::cout<<"前后区块链接断裂！"<<std::endl;
                return false;
            }
        }
        return true;
    }
};
