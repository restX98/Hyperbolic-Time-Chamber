#include <iostream>
#include <memory>

class Window {

public:
  class Impl {
  private:
    int mHeight;
    int mWidth;
    std::string mTitle;
    std::string mCamera;

    friend class Window;

  public:
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
  };

  Window() : mImpl(new Impl()) {}

  std::unique_ptr<Impl> build() {
    return std::move(mImpl);
  }

  Window& height(const int& height) {
    this->mImpl->mHeight = height;
    return *this;
  }

  Window& width(const int& width) {
    this->mImpl->mWidth = width;
    return *this;
  }

  Window& title(const std::string& title) {
    this->mImpl->mTitle = title;
    return *this;
  }

  Window& camera(const std::string& camera) {
    this->mImpl->mCamera = camera;
    return *this;
  }

private:
  std::unique_ptr<Impl> mImpl;

};

std::ostream& operator<<(std::ostream& out, const Window::Impl& window) {
  out << "Window(" << &window << ") - " << window.getTitle() << std::endl;
  out << "Size:\t" << window.getWidth() << "x" << window.getHeight() << std::endl;
  out << "Camera:\t" << window.getCamera() << std::endl;
  return out;
}

int main() {

  std::unique_ptr<Window::Impl> w = Window().width(600)
    .height(300)
    .title("My Window")
    .camera("Perspective")
    .build();

  std::cout << *w << std::endl;

  return 0;
}
