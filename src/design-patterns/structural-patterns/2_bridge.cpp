#include <iostream>

// Used to extend a class in several orthogonal (independent) dimensions.


/**
 * The Implementation defines the interface for all implementation classes. It
 * doesn't have to match the Abstraction's interface. In fact, the two
 * interfaces can be entirely different. Typically the Implementation interface
 * provides only primitive operations, while the Abstraction defines higher-
 * level operations based on those primitives.
 */
// Implementation - IDevice
class IDevice { // Interface
public:
  virtual ~IDevice() {}

  virtual bool isEnabled() const = 0;
  virtual void enable() = 0;
  virtual void disable() = 0;

  virtual int getVolume() const = 0;
  virtual void setVolume(int percent) = 0;

  virtual int getChannel() const = 0;
  virtual void setChannel(int channel) = 0;

protected:
  bool powerOn = false;
  int volume = 20;
  int channel = 1;
};

/**
 * Each Concrete Implementation corresponds to a specific platform and
 * implements the Implementation interface using that platform's API.
 */
// Concrete Implementation - TV
class TV : public IDevice {
public:
  bool isEnabled() const override {
    return this->powerOn;
  }
  void enable() override {
    this->powerOn = true;
  };
  void disable() override {
    this->powerOn = false;
  }

  int getVolume() const override {
    return this->volume;
  }
  void setVolume(int percent) override {
    if (percent > 100) {
      this->volume = 100;
    } else if (percent < 0) {
      this->volume = 0;
    } else {
      this->volume = percent;
    }
  }

  virtual int getChannel() const override {
    return this->channel;
  };
  virtual void setChannel(int channel) override {
    this->channel = channel;
  };
};

/**
 * The Abstraction defines the interface for the "control" part of the two class
 * hierarchies. It maintains a reference to an object of the Implementation
 * hierarchy and delegates all of the real work to this object.
 */
// Abstraction - RemoteControl
class RemoteControl {
protected:
  IDevice* mDevice;

public:
  RemoteControl(IDevice* device) : mDevice(device) {}

  virtual ~RemoteControl() {}

  virtual void togglePower() {
    if (mDevice->isEnabled())
      mDevice->disable();
    else
      mDevice->enable();
  }
  virtual void volumeDown() {
    mDevice->setVolume(mDevice->getVolume() - 10);
  }
  virtual void volumeUp() {
    mDevice->setVolume(mDevice->getVolume() + 10);
  }
  virtual void channelDown() {
    mDevice->setChannel(mDevice->getChannel() - 1);
  }
  virtual void channelUp() {
    mDevice->setChannel(mDevice->getChannel() + 1);
  }
};

class AdvancedRemoteControl : public RemoteControl {
public:
  void mute() {
    mDevice->setVolume(0);
  }
};

std::ostream& operator<<(std::ostream& out, const TV& tv) {
  out << "Window(" << &tv << ") - Status: " << (tv.isEnabled() ? "ON" : "OFF") << std::endl;
  out << "Channel: " << tv.getChannel() << std::endl;
  out << "Volume: " << tv.getVolume() << std::endl;
  return out;
}

int main() {
  TV* tv = new TV();
  RemoteControl* remote = new RemoteControl(tv);
  remote->togglePower();

  std::cout << *tv;

  return 0;
}
