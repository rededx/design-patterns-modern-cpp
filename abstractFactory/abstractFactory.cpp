#include <iostream>
#include <memory>

/*
 * Product A
 * products implement the same interface so that the classes can refer
 * to the interface not the concrete product
 */
class AbstractProductA {
   public:
    virtual ~AbstractProductA() = default;

    virtual std::string getName() const = 0;
    // ...
};

/*
 * ConcreteProductAX and ConcreteProductAY
 * define objects to be created by concrete factory
 */
class ConcreteProductAX : public AbstractProductA {
   public:
    std::string getName() const override { return "AX"; }
    // ...
};

class ConcreteProductAY : public AbstractProductA {
   public:
    std::string getName() const override { return "AY"; }
    // ...
};

/*
 * Product B
 * same as Product A, Product B declares interface for concrete products
 * where each can produce an entire set of products
 */
class AbstractProductB {
   public:
    virtual ~AbstractProductB() = default;

    virtual std::string getName() const = 0;
};

/*
 * ConcreteProductBX and ConcreteProductBY
 * same as previous concrete product classes
 */
class ConcreteProductBX : public AbstractProductB {
   public:
    std::string getName() const override { return "BX"; }
    // ...
};

class ConcreteProductBY : public AbstractProductB {
   public:
    std::string getName() const override { return "BY"; }
    // ...
};

/*
 * Abstract Factory
 * provides an abstract interface for creating a family of products
 */
class AbstractFactory {
   public:
    virtual ~AbstractFactory() = default;

    virtual std::shared_ptr<AbstractProductA> createProductA() const = 0;
    virtual std::shared_ptr<AbstractProductB> createProductB() const = 0;
};

/*
 * Concrete Factory X and Y
 * each concrete factory create a family of products and client uses
 * one of these factories so it never has to instantiate a product object
 */
class ConcreteFactoryX : public AbstractFactory {
   public:
    std::shared_ptr<AbstractProductA> createProductA() const override {
        return std::make_shared<ConcreteProductAX>();
    }
    std::shared_ptr<AbstractProductB> createProductB() const override {
        return std::make_shared<ConcreteProductBX>();
    }
    // ...
};

class ConcreteFactoryY : public AbstractFactory {
   public:
    std::shared_ptr<AbstractProductA> createProductA() const override {
        return std::make_shared<ConcreteProductAY>();
    }
    std::shared_ptr<AbstractProductB> createProductB() const override {
        return std::make_shared<ConcreteProductBY>();
    }
    // ...
};

int main() {
    auto factoryX = std::make_shared<ConcreteFactoryX>();
    auto factoryY = std::make_shared<ConcreteFactoryY>();

    std::shared_ptr<AbstractProductA> p1 = factoryX->createProductA();
    std::cout << "Product: " << p1->getName() << "\n";

    std::shared_ptr<AbstractProductB> p2 = factoryY->createProductB();
    std::cout << "Product: " << p2->getName() << "\n";
}