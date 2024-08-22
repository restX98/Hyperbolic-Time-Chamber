#include <iostream>

class Window {
private:
  int mHeight;
  int mWidth;
  std::string mTitle;
  std::string mCamera;

  Window() = default;

public:
  static Window create() {
    return Window();
  }

  Window& height(const int& height) {
    this->mHeight = height;
    return *this;
  }
  int getHeight() const {
    return this->mHeight;
  }

  Window& width(const int& width) {
    this->mWidth = width;
    return *this;
  }
  int getWidth() const {
    return this->mWidth;
  }

  Window& title(const std::string& title) {
    this->mTitle = title;
    return *this;
  }
  std::string getTitle() const {
    return this->mTitle;
  }

  Window& camera(const std::string& camera) {
    this->mCamera = camera;
    return *this;
  }
  std::string getCamera() const {
    return this->mCamera;
  }
};

std::ostream& operator<<(std::ostream& out, const Window& window) {
  out << "Window(" << &window << ") - " << window.getTitle() << std::endl;
  out << "Size:\t" << window.getWidth() << "x" << window.getHeight() << std::endl;
  out << "Camera:\t" << window.getCamera() << std::endl;
  return out;
}

int main() {

  Window w = Window::create();

  w.width(600)
    .height(300)
    .title("My Window")
    .camera("Perspective");

  std::cout << w << std::endl;

  return 0;
}
