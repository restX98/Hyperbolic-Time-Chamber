#include <iostream>

// Target - RoundPeg
class RoundPeg {
protected:
  RoundPeg() {}

public:
  RoundPeg(int radius) : radius(radius) {}
  virtual ~RoundPeg() = default;

  virtual int getRadius() const {
    return this->radius;
  }

private:
  int radius;
};

class RoundHole {
public:
  RoundHole(int radius) : radius(radius) {}

  bool fit(const RoundPeg& peg) const {
    return this->getRadius() >= peg.getRadius();
  }

  int getRadius() const {
    return this->radius;
  }

private:
  int radius;
};

// Adaptee - SquarePeg
class SquarePeg {
public:
  SquarePeg(int width) : width(width) {}

  int getWidth() const {
    return this->width;
  }

private:
  int width;
};

// Adapter - SquarePegAdapter
class SquarePegAdapter : public RoundPeg {
public:
  SquarePegAdapter(SquarePeg* peg) : RoundPeg(peg->getWidth()) {
    this->peg = peg;
  }

  int getRadius() const override {
    // The adapter pretends that it's a round peg with a
    // radius that could fit the square peg that the adapter
    // actually wraps.
    return peg->getWidth() / 2;
  }
private:
  SquarePeg* peg;
};


int main() {
  std::cout << "Client: I can work just fine with the Target objects:\n";

  RoundPeg* roundPeg = new RoundPeg(5);
  RoundHole* roundHole = new RoundHole(6);


  std::cout << "Default fit? " << roundHole->fit(*roundPeg);
  std::cout << "\n\n";

  SquarePeg* squarePeg = new SquarePeg(5);
  // std::cout << "Fit? " << roundHole->fit(*squarePeg); // Compile Error

  SquarePegAdapter* squarePegAdapter = new SquarePegAdapter(squarePeg);
  std::cout << "Adapter fit? " << roundHole->fit(*squarePegAdapter);
  std::cout << "\n\n";

  delete roundPeg;
  delete roundHole;
  delete squarePeg;
  delete squarePegAdapter;

  return 0;
}
