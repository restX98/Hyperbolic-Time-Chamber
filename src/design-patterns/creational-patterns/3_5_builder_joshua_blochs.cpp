#include <iostream>

class Window {
public:
  class Builder {
  public:
    Builder() : mWindow(new Window()) {}
    virtual ~Builder() = default;

    Window* build() {
      return this->mWindow;
    }

    Builder& title(const std::string& title) {
      this->mWindow->mTitle = title;
      return *this;
    }

    Builder& height(const int& height) {
      this->mWindow->mHeight = height;
      return *this;
    }

    Builder& width(const int& width) {
      this->mWindow->mWidth = width;
      return *this;
    }

    Builder& camera(const std::string& camera) {
      this->mWindow->mCamera = camera;
      return *this;
    }

  private:
    friend class Window;
    Window* mWindow;
  };

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
  int mHeight;
  int mWidth;
  std::string mTitle;
  std::string mCamera;

  Window() : mTitle() {}
};

std::ostream& operator<<(std::ostream& out, const Window& window) {
  out << "Window(" << &window << ") - " << window.getTitle() << std::endl;
  out << "Size:\t" << window.getWidth() << "x" << window.getHeight() << std::endl;
  out << "Camera:\t" << window.getCamera() << std::endl;
  return out;
}

int main() {
  Window* w = Window::Builder()
    .title("My Window")
    .width(600)
    .height(300)
    .camera("Perspective")
    .build();

  std::cout << *w << std::endl;
  w->run();

  Window::Builder windowBuilder = Window::Builder()
    .title("Multi Window Instance")
    .width(900)
    .height(600)
    .camera("Ortho");

  Window* w1 = windowBuilder.build();
  Window* w2 = windowBuilder.build();

  std::cout << *w1 << std::endl;
  std::cout << *w2 << std::endl;

}
