#include <iostream>
#include <sstream>

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
      std::cout << "hash:\t\t" << hash << "\nprevious hash:\t" << previousHash << "\ntransaction:\t" << transaction->toString() << "\ntimestamp:\t" << std::string(ctime(&timestamp)) << std::endl;
    }

  private:
    size_t previousHash;
    size_t hash;
    time_t timestamp;
    Transaction* transaction;

    size_t calcHash() {
      std::stringstream ss;
      ss << previousHash << timestamp << transaction->toString();
      return std::hash<std::string>{}(ss.str());
    }
};

int main(void) {
  Transaction t1("A", "B", 100);
  Block b1(0, &t1);
  b1.printInfo();
  return 0;
}