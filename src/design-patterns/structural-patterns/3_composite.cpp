#include <iostream>
#include <list>

/**
 * The base Component class declares common operations for both simple and
 * complex objects of a composition.
 */
// Component Interface - Graphic
class Graphic {
protected:
  Graphic* parent_;
  /**
   * Optionally, the base Component can declare an interface for setting and
   * accessing a parent of the component in a tree structure. It can also
   * provide some default implementation for these methods.
   */
public:
  virtual ~Graphic() {}

  void setParent(Graphic* parent) {
    this->parent_ = parent;
  }
  Graphic* getParent() const {
    return this->parent_;
  }
  /**
   * In some cases, it would be beneficial to define the child-management
   * operations right in the base Component class. This way, you won't need to
   * expose any concrete component classes to the client code, even during the
   * object tree assembly. The downside is that these methods will be empty for
   * the leaf-level components.
   */
  virtual void add(Graphic* component) {}
  virtual void remove(Graphic* component) {}
  /**
   * You can provide a method that lets the client code figure out whether a
   * component can bear children.
   */
  virtual bool isComposite() const {
    return false;
  }
  /**
   * The base Component may implement some default behavior or leave it to
   * concrete classes (by declaring the method containing the behavior as
   * "abstract").
   */
  virtual void move(int x, int y) = 0;
  virtual void draw() const = 0;
};

/**
 * The Leaf class represents the end objects of a composition. A leaf can't have
 * any children.
 *
 * Usually, it's the Leaf objects that do the actual work, whereas Composite
 * objects only delegate to their sub-components.
 */
// Leaf - Dot
class Dot : public Graphic {
protected:
  int x;
  int y;

public:
  Dot() : Dot(0, 0) {}
  Dot(int x, int y) : x(x), y(y) {}

  void move(int x, int y) override {
    this->x += x;
    this->y += y;
  }
  void draw() const override {
    std::cout << "Point(" << x << ", " << y << ")" << std::endl;
  }
};

// All component classes can extend other components.
class Circle : public Dot {
protected:
  float radius;

public:
  Circle() : Circle(0, 0, 1.0f) {}
  Circle(float radius) : Circle(0, 0, radius) {}
  Circle(int x, int y, float radius) : Dot(x, y), radius(radius) {}

  void draw() const override {
    std::cout << "Point(" << x << ", " << y << ")[R:" << radius << "]" << std::endl;
  }
};


/**
 * The Composite class represents the complex components that may have children.
 * Usually, the Composite objects delegate the actual work to their children and
 * then "sum-up" the result.
 */
class CompoundGraphic : public Graphic {
protected:
  std::list<Graphic*> children;

public:
 /**
  * A composite object can add or remove other components (both simple or
  * complex) to or from its child list.
  */
  void add(Graphic* graphic) override {
    this->children.push_back(graphic);
    graphic->setParent(this);
  }
  /**
   * Have in mind that this method removes the pointer to the list but doesn't
   * frees the
   *     memory, you should do it manually or better use smart pointers.
   */
  void remove(Graphic* graphic) override {
    children.remove(graphic);
    graphic->setParent(nullptr);
  }
  bool isComposite() const override {
    return true;
  }
  /**
   * The Composite executes its primary logic in a particular way. It traverses
   * recursively through all its children, collecting and summing their results.
   * Since the composite's children pass these calls to their children and so
   * forth, the whole object tree is traversed as a result.
   */
  void move(int x, int y) override {
    std::string result;
    for (Graphic* g : children) {
      g->move(x, y);
    }
  }

  void draw() const override {
    std::string result;
    for (const Graphic* g : children) {
      g->draw();
    }
  }
};

int main() {
  CompoundGraphic* group = new CompoundGraphic();

  Dot* d1 = new Dot(1, 1);
  Dot* d2 = new Dot(1, 4);
  Dot* d3 = new Dot(4, 4);
  Dot* d4 = new Dot(4, 1);
  Circle* c = new Circle(6, 6, 3);
  group->add(d1);
  group->add(d2);
  group->add(d3);
  group->add(d4);
  group->add(c);

  Dot* origin = new Dot();
  origin->move(10, 10);
  group->add(origin);

  group->move(2, 3);
  group->draw();

  group->remove(origin);
  group->draw();

  // We can also call the move and draw method of the leaf object.
  // To prevent this beavhior set the operations method as proteced.

  return 0;
}
