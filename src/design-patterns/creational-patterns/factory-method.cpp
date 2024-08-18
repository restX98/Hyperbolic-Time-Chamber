#include <iostream>

// The Factory method is used to create various kind of product (object) derived
// from the same classes and this allow this objects to be used by the
// same client code.

// Abstract product:
class Shape {
public:
    virtual void draw() = 0; // Pure (=0) virtual function
    virtual ~Shape() {}
};

// Concrete Product - Circle
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a circle" << std::endl;
    }
};

// Concrete Product - Square
class Square : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a square" << std::endl;
    }
};

// Abstract creatore class
class ShapeFactory {
public:
    virtual Shape* createShape() = 0;
    virtual ~ShapeFactory() {}
};

// Concrete creatore class - Circle
class CircleFactory : public ShapeFactory {
public:
    Shape* createShape() {
        return new Circle();
    }
};

// Concrete creatore class - Square
class SquareFactory : public ShapeFactory {
public:
    Shape* createShape() {
        return new Square();
    }
};

void drawShape(Shape* shape) {
    shape->draw();
}

int main() {
    CircleFactory circleFactory;
    SquareFactory squareFactory;

    Shape* circle = circleFactory.createShape();
    Shape* square = squareFactory.createShape();

    drawShape(circle);
    drawShape(square);
    circle->draw();
    square->draw();

    char chose;
    std::cout << "Choose the shape that you wanna create (c=circle/s=square):" << std::endl;
    std::cin >> chose;

    ShapeFactory* factory = nullptr;
    switch (chose) {
    case 'c':
        factory = new CircleFactory();
        break;
    case 's':
        factory = new SquareFactory();
        break;
    default:
        factory = new CircleFactory();
        break;
    }

    Shape* choosenShape = factory->createShape();
    drawShape(choosenShape);

    delete circle;
    delete square;
    delete factory;

    return 0;
}
