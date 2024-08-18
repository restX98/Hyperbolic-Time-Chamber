#include <iostream>

// The Abstract Factory pattern is used to create a family of related object
// (in this case the family is the UI component of a program e.g. button, checkbox ecc),
// with more variant of it (in this case different theme e.g. dark or light).

// Abstract Product - Button
class Button {
public:
  virtual void click() = 0;
  virtual ~Button() {}
};

// Abstract Product - Label
class Checkbox {
public:
  virtual void check() = 0;
  virtual ~Checkbox() {}
};

// Concrete Product - Button Light Theme
class LightButton : public Button {
public:
  void click() override {
    std::cout << "Light button clicked" << std::endl;
  }
};

// Concrete Product - Button Dark Theme
class DarkButton : public Button {
public:
  void click() override {
    std::cout << "Dark button clicked" << std::endl;
  }
};

// Concrete Product - Checkbox Light Theme
class LightCheckbox : public Checkbox {
public:
  void check() override {
    std::cout << "Light button checked" << std::endl;
  }
};

// Concrete Product - Checkbox Dark Theme
class DarkCheckbox : public Checkbox {
public:
  void check() override {
    std::cout << "Dark button checked" << std::endl;
  }
};

// Abstract Factory - GUI Factory
class GUIFactory {
public:
  virtual Button* createButton() = 0;
  virtual Checkbox* createCheckbox() = 0;
  virtual ~GUIFactory() {}
};

// Concrete Factory - Light GUI Factory
class LightGUIFactory : public GUIFactory {
public:
  Button* createButton() override {
    return new LightButton();
  }

  Checkbox* createCheckbox() override {
    return new LightCheckbox();
  }
};

// Concrete Factory - Dark GUI Factory
class DarkGUIFactory : public GUIFactory {
public:
  Button* createButton() override {
    return new DarkButton();
  }

  Checkbox* createCheckbox() override {
    return new DarkCheckbox();
  }
};

int main() {

  char chose;
  std::cout << "Choose the theme of the UI (d=dark/l=light): ";
  std::cin >> chose;

  GUIFactory* factory = nullptr;
  switch (chose) {
  case 'l':
    factory = new LightGUIFactory();
    break;
  case 'd':
    factory = new DarkGUIFactory();
    break;
  default:
    factory = new LightGUIFactory();
    break;
  }

  Button* btn = factory->createButton();
  Checkbox* cbx = factory->createCheckbox();

  btn->click();
  cbx->check();

  delete btn;
  delete cbx;
  delete factory;

  return 0;
}
