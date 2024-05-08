#include <iostream>
#include <cstring>
#include <chrono>
#include <vector>
#include "block.h"
#include "chain.h"
#include "transaction.h"
#include "picosha2.h"


int main() {
    chain KoviCoin;
    Transaction transaction1("lmk","wyc",10);
    KoviCoin.addTransaction(transaction1);
    Transaction transaction2("wyc","lmk",100);
    KoviCoin.addTransaction(transaction2);
    KoviCoin.mineTransactionPool("lmk");
    KoviCoin.mineTransactionPool("ino");
    std::cout<<KoviCoin.blocks.size()<<std::endl;
    std::cout<<KoviCoin.blocks[1].timestamp<<std::endl;
    std::cout<<KoviCoin.blocks[2].timestamp<<std::endl;

    std::cout<<KoviCoin.blocks[1].transactions[2].from<<std::endl;
    std::cout<<KoviCoin.blocks[1].transactions[2].to<<std::endl;
    std::cout<<KoviCoin.blocks[1].transactions[2].amount<<std::endl;

    std::cout<<KoviCoin.blocks[2].transactions[0].from<<std::endl;
    std::cout<<KoviCoin.blocks[2].transactions[0].to<<std::endl;
    std::cout<<KoviCoin.blocks[2].transactions[0].amount<<std::endl;

    return 0;
}
