#include <iostream>

/**
 * The base Component interface defines operations that can be altered by
 * decorators.
 */
// Component Interface - DataSource
class DataSource {
public:
  virtual ~DataSource() {}
  virtual void readData() const = 0;
  virtual void writeData() const = 0;
};

/**
 * Concrete Components provide default implementations of the operations. There
 * might be several variations of these classes.
 */
// Concrete Component - FileDataSource
class FileDataSource : public DataSource {
protected:
  std::string mFileName;
public:
  FileDataSource(const std::string& fileName) {
    mFileName = fileName;
  }

  void readData() const override {
    std::cout << "Reading: " << mFileName << std::endl;
  }
  void writeData() const override {
    std::cout << "Writing: " << mFileName << std::endl;
  }
};
/**
 * The base Decorator class follows the same interface as the other components.
 * The primary purpose of this class is to define the wrapping interface for all
 * concrete decorators. The default implementation of the wrapping code might
 * include a field for storing a wrapped component and the means to initialize
 * it.
 */
class DataSourceDecorator : public DataSource {
protected:
  DataSource* mDataSource; // wrappee

public:
  DataSourceDecorator(DataSource* dataSource) : mDataSource(dataSource) {}
  /**
   * The Decorator delegates all work to the wrapped component.
   */
  void readData() const override {
    this->mDataSource->readData();
  }
  void writeData() const override {
    this->mDataSource->writeData();
  }
};

/**
 * Concrete Decorators call the wrapped object and alter its result in some way.
 */
class EncryptionDecorator : public DataSourceDecorator {
  /**
   * Decorators may call parent implementation of the operation, instead of
   * calling the wrapped object directly. This approach simplifies extension of
   * decorator classes.
   */
public:
  EncryptionDecorator(DataSource* dataSource) : DataSourceDecorator(dataSource) {
  }
  void readData() const override {
    std::cout << "Decrypting data..." << std::endl;
    DataSourceDecorator::readData();
  }
  void writeData() const override {
    std::cout << "Encrypting data..." << std::endl;
    DataSourceDecorator::writeData();
  }
};
/**
 * Decorators can execute their behavior either before or after the call to a
 * wrapped object.
 */
class CompressionDecorator : public DataSourceDecorator {
public:
  CompressionDecorator(DataSource* dataSource) : DataSourceDecorator(dataSource) {
  }

  void readData() const override {
    std::cout << "Decompressing data..." << std::endl;
    DataSourceDecorator::readData();
  }
  void writeData() const override {
    std::cout << "Compressing data..." << std::endl;
    DataSourceDecorator::writeData();
  }
};

int main() {
  DataSource* file = new FileDataSource("myFile.txt");
  file->readData();
  std::cout << std::endl;
  file->writeData();
  std::cout << std::endl;

  file = new EncryptionDecorator(file);
  file->readData();
  std::cout << std::endl;
  file->writeData();
  std::cout << std::endl;

  file = new CompressionDecorator(file);
  file->readData();
  std::cout << std::endl;
  file->writeData();
  std::cout << std::endl;

  delete file;

  return 0;
}
