#include <iostream>

// Product Class - Computer
// Could be more than one product class and may not always follow the same interface.
class Computer {
private:
  std::string cpu;
  std::string memory;
  std::string storage;

public:
  void setCPU(const std::string& cpu) {
    this->cpu = cpu;
  }
  std::string getCPU() const {
    return this->cpu;
  }

  void setMemory(const std::string& memory) {
    this->memory = memory;
  }
  std::string getMemory() const {
    return this->memory;
  }

  void setStorage(const std::string& storage) {
    this->storage = storage;
  }
  std::string getStorage() const {
    return this->storage;
  }
};

std::ostream& operator<<(std::ostream& out, const Computer& computer) {
  out << "Computer: " << &computer << std::endl;
  out << "CPU:      " << computer.getCPU() << std::endl;
  out << "Memory:   " << computer.getMemory() << std::endl;
  out << "Storage:  " << computer.getStorage() << std::endl;
  return out;
}

class ComputerBuilder {
public:
  virtual void buildCPU() = 0;
  virtual void buildMemory() = 0;
  virtual void buildStorage() = 0;
  virtual ~ComputerBuilder() {}
};

class DesktopComputerBuilder : public ComputerBuilder {
private:
  Computer* computer;

public:
  DesktopComputerBuilder() {
    this->reset();
  }
  ~DesktopComputerBuilder() {
    delete this->computer;
  }

  void reset() {
    this->computer = new Computer();
  }

  void buildCPU() {
    this->computer->setCPU("Intel i7");
  }

  void buildMemory() {
    this->computer->setMemory("16GB");
  }

  void buildStorage() {
    this->computer->setStorage("1024GB");
  }

  /**
   * Concrete Builders are supposed to provide their own methods for
   * retrieving results. That's because various types of builders may create
   * entirely different products that don't follow the same interface.
   *
   * Usually, after returning the end result to the client, a builder instance
   * is expected to be ready to start producing another product. That's why
   * it's a usual practice to call the reset method at the end of the
   * `getProduct` method body. However, this behavior is not mandatory, and
   * you can make your builders wait for an explicit reset call from the
   * client code before disposing of the previous result.
   * In this way, once you call the getProduct method, the user of this
   * function is responsable to release this memory.
   * Here could be a better option to use smart pointers to avoid
   * memory leaks [TO STUDY: Smart pointer]
   */

  Computer* getComputer() {
    Computer* c = this->computer;
    this->reset();
    return c;
  }
};

// Director - ComputerAssembler
// The Director is only responsible for executing the building steps in a
// particular sequence. It is helpful when producing products according to a
// specific order or configuration. Strictly speaking, the Director class is
// optional, since the client can control builders directly.
class ComputerAssembler {
private:
  ComputerBuilder* builder;

public:
  ComputerAssembler(ComputerBuilder* builder) {
    this->builder = builder;
  }

  void setBuilder(ComputerBuilder* builder) {
    this->builder = builder;
  }

  void buildComputer() {
    this->builder->buildCPU();
    this->builder->buildMemory();
    this->builder->buildStorage();
  }
};

int main() {
  DesktopComputerBuilder dcb;
  ComputerAssembler assembler(&dcb);

  assembler.buildComputer();
  Computer* c = dcb.getComputer();

  std::cout << *c;

  return 0;
}
