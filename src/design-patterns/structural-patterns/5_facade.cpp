#include <iostream>


/**
 * The Subsystem can accept requests either from the facade or client directly.
 * In any case, to the Subsystem, the Facade is yet another client, and it's not
 * a part of the Subsystem.
 */
class Engine {
public:
  void start() const {
    std::cout << "Engine started" << std::endl;
  }
  void stop() const {
    std::cout << "Engine stopped" << std::endl;
  }
};

/**
 * Some facades can work with multiple subsystems at the same time.
 */
class Lights {
public:
  void turnOn() const {
    std::cout << "Lights on" << std::endl;
  }
  void turnOff() const {
    std::cout << "Lights off" << std::endl;
  }
};

/**
 * The Facade class provides a simple interface to the complex logic of one or
 * several subsystems. The Facade delegates the client requests to the
 * appropriate objects within the subsystem. The Facade is also responsible for
 * managing their lifecycle. All of this shields the client from the undesired
 * complexity of the subsystem.
 */
class Car {
protected:
  Engine* mEngine;
  Lights* mLights;
  /**
   * Depending on your application's needs, you can provide the Facade with
   * existing subsystem objects or force the Facade to create them on its own.
   */
public:
 /**
  * In this case we will delegate the memory ownership to Facade Class
  */
  Car(
    Engine* engine = nullptr,
    Lights* lights = nullptr) {
    this->mEngine = engine ? : new Engine;
    this->mLights = lights ? : new Lights;
  }
  ~Car() {
    delete mEngine;
    delete mLights;
  }
  /**
   * The Facade's methods are convenient shortcuts to the sophisticated
   * functionality of the subsystems. However, clients get only to a fraction of
   * a subsystem's capabilities.
   */
  void startCar() {
    std::cout << "Starting Car:\n";
    this->mEngine->start();
    this->mLights->turnOn();
  }

  void stopCar() {
    std::cout << "Stopping Car:\n";
    this->mLights->turnOff();
    this->mEngine->stop();
  }
};

/**
 * The client code works with complex subsystems through a simple interface
 * provided by the Facade. When a facade manages the lifecycle of the subsystem,
 * the client might not even know about the existence of the subsystem. This
 * approach lets you keep the complexity under control.
 * The client code may have some of the subsystem's objects already created. In
 * this case, it might be worthwhile to initialize the Facade with these objects
 * instead of letting the Facade create new instances.
 */

int main() {
  Engine* engine = new Engine;
  Lights* lights = new Lights;
  Car* car = new Car(engine, lights);

  car->startCar();
  car->stopCar();

  delete car;

  return 0;
}
