#include <iostream>

class Notifier {
public:
  virtual ~Notifier() {}
  virtual void send(const std::string& message) const = 0;
};

class NotifierDecorator : public Notifier {
protected:
  Notifier* mNotifier;

public:
  NotifierDecorator(Notifier* notifier = nullptr) : mNotifier(notifier) {}

  void send(const std::string& message) const override {
    if (this->mNotifier != nullptr) {
      this->mNotifier->send(message);
    }
  }
};

class EmailNotifier : public NotifierDecorator {
public:
  EmailNotifier(Notifier* notifier = nullptr) : NotifierDecorator(notifier) {}

  void send(const std::string& message) const override {
    std::cout << "Sending e-mail notification with message: " << message << std::endl;
    NotifierDecorator::send(message);
  }
};

class SMSNotifier : public NotifierDecorator {
public:
  SMSNotifier(Notifier* notifier = nullptr) : NotifierDecorator(notifier) {}

  void send(const std::string& message) const override {
    std::cout << "Sending SMS notification with message: " << message << std::endl;
    NotifierDecorator::send(message);
  }
};

class SlackNotifier : public NotifierDecorator {
public:
  SlackNotifier(Notifier* notifier = nullptr) : NotifierDecorator(notifier) {}

  void send(const std::string& message) const override {
    std::cout << "Sending Slack notification with message: " << message << std::endl;
    NotifierDecorator::send(message);
  }
};


int main() {
  Notifier* notifier = new EmailNotifier();
  notifier->send("Discount ready for you");
  std::cout << std::endl;

  notifier = new SMSNotifier(notifier);
  notifier->send("Discount ready for you 2");
  std::cout << std::endl;

  notifier = new SlackNotifier(notifier);
  notifier->send("Discount ready for you 3");
  std::cout << std::endl << std::endl;

  delete notifier;
  notifier = nullptr; // safer

  // I can start from which decorator i prefer:
  Notifier* notifier2 = new SMSNotifier(); // Dangerous, if I pass a deleted pointer an infinity loop will start.
  notifier2->send("Discount ready for you 4");
  std::cout << std::endl;

  notifier2 = new EmailNotifier(notifier2);
  notifier2->send("Discount ready for you 5");
  std::cout << std::endl;

  return 0;
}
