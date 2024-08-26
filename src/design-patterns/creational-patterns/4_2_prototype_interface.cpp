#include <iostream>

template <typename T>
class Prototype {
  virtual T* clone() const = 0; // Clone method for creating copies.
};

class Shape : virtual public Prototype<Shape> {
public:
  virtual void draw() const = 0;   // Draw method for rendering the shape.
  virtual ~Shape() {}              // Virtual destructor for proper cleanup.
};

class Circle : public Shape {
private:
  double radius;

public:
  Circle(double r) : radius(r) {}

  Shape* clone() const override {
    return new Circle(*this); // Default copy constructor
  }

  void draw() const override {
    std::cout << "Drawing a circle with radius " << radius << std::endl;
  }
};



class Rectangle : public Shape {
private:
  double width;
  double height;

public:
  Rectangle(double w, double h) : width(w), height(h) {}

  Shape* clone() const override {
    return new Rectangle(*this); // Default copy constructor
  }

  void draw() const override {
    std::cout << "Drawing a rectangle with width " << width << " and height " << height << std::endl;
  }
};

int main() {

  Circle circlePrototype(5.0);
  Rectangle rectanglePrototype(4.0, 6.0);

  circlePrototype.draw();
  rectanglePrototype.draw();
  std::cout << &circlePrototype << std::endl;
  std::cout << &rectanglePrototype << std::endl;

  Shape* shape1 = circlePrototype.clone();
  Shape* shape2 = rectanglePrototype.clone();

  shape1->draw();
  shape2->draw();
  std::cout << shape1 << std::endl;
  std::cout << shape2 << std::endl;

  return 0;
}
