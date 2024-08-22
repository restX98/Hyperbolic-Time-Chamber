#include <iostream>
#include <memory>

class Window {
public:
  virtual ~Window() = default;
  void run() {
    std::cout << "Window started" << std::endl;
  }

  int getHeight() const {
    return this->mHeight;
  }

  int getWidth() const {
    return this->mWidth;
  }

  std::string getTitle() const {
    return this->mTitle;
  }

  std::string getCamera() const {
    return this->mCamera;
  }

private:
  friend class Window3DBuilder;

  int mHeight;
  int mWidth;
  std::string mTitle;
  std::string mCamera;

  Window(std::string name) : mTitle(name) {}
};

class WindowBuilder {
public:
  virtual ~WindowBuilder() = default;

  virtual std::unique_ptr<Window> build() = 0;

  virtual WindowBuilder& height(const int& height) = 0;
  virtual WindowBuilder& width(const int& width) = 0;
  virtual WindowBuilder& camera(const std::string& camera) = 0;
};

class Window3DBuilder : public WindowBuilder {
public:

  Window3DBuilder(std::string name) : mWindow(new Window(name)) {}

  std::unique_ptr<Window> build() override {
    return std::move(this->mWindow);
  }

  WindowBuilder& height(const int& height) {
    this->mWindow->mHeight = height;
    return *this;
  }

  WindowBuilder& width(const int& width) {
    this->mWindow->mWidth = width;
    return *this;
  }

  WindowBuilder& camera(const std::string& camera) {
    this->mWindow->mCamera = camera;
    return *this;
  }

private:
  std::unique_ptr<Window> mWindow;
};

std::ostream& operator<<(std::ostream& out, const Window& window) {
  out << "Window(" << &window << ") - " << window.getTitle() << std::endl;
  out << "Size:\t" << window.getWidth() << "x" << window.getHeight() << std::endl;
  out << "Camera:\t" << window.getCamera() << std::endl;
  return out;
}

int main() {

  std::unique_ptr<Window> w = Window3DBuilder("My Window")
    .width(600)
    .height(300)
    .camera("Perspective")
    .build();

  std::cout << *w << std::endl;
  w->run();

  return 0;
}
