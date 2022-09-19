#include <iostream>
#include <sstream>
#include <vector>

class Transaction {
 public:
  Transaction(std::string sender, std::string receiver, double amount) {
    this->sender = sender;
    this->receiver = receiver;
    this->amount = amount;
  }

  std::string toString() {
    return sender + " -> " + receiver + " : $" + std::to_string(amount);
  }

 private:
  std::string sender;
  std::string receiver;
  double amount;
};

class Block {
 public:
  Block(size_t previousHash, Transaction* transaction) {
    this->previousHash = previousHash;
    this->transaction = transaction;
    this->timestamp = time(nullptr);
    this->hash = calcHash();
  }

  void printInfo() {
    std::cout << "hash:\t\t" << hash << "\nprevious hash:\t" << previousHash
              << "\ntransaction:\t" << transaction->toString()
              << "\ntimestamp:\t" << std::string(ctime(&timestamp))
              << std::endl;
  }

  size_t calcHash() {
    std::stringstream ss;
    ss << previousHash << timestamp << transaction->toString();
    return std::hash<std::string>{}(ss.str());
  }

  size_t getHash() { return hash; }

  size_t getPreviousHash() { return previousHash; }

 private:
  size_t previousHash;
  size_t hash;
  time_t timestamp;
  Transaction* transaction;
};

class BlockChain {
 public:
  BlockChain() {
    Block* genesis = new Block(0, new Transaction("genesis", "genesis", 0));
    chain.push_back(genesis);
  }

  void addBlock(Transaction* transaction) {
    Block* block = new Block(chain.back()->getHash(), transaction);
    chain.push_back(block);
  }

  void addTransaction(Transaction* transaction) {
    pendings.push_back(transaction);
  }

  bool isValid() {
    for (size_t i = chain.size() - 1; i > 0; --i) {
      Block* curBlock = chain[i];
      Block* preBlock = chain[i - 1];

      if (curBlock->getHash() != curBlock->calcHash()) {
        return false;
      }

      if (curBlock->getPreviousHash() != preBlock->getHash()) {
        return false;
      }
    }

    return true;
  }

  void printInfo() {
    for (auto block : chain) {
      std::cout << "-----------------------------------------------------------"
                   "---------------"
                << std::endl;
      block->printInfo();
    }
  }

 private:
  std::vector<Block*> chain;
  std::vector<Transaction*> pendings;
};

int main(void) {
  BlockChain* bc = new BlockChain();
  bc->addBlock(new Transaction("hoge", "huga", 100));
  bc->addBlock(new Transaction("hoge", "huga", 5000));
  bc->printInfo();

  return 0;
}