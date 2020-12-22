#include <iostream>
#include <memory>
#include <string>

/*
 * Product
 * products implement the same interface so that the classes can refer
 * to the interface not the concrete product
 */
class Product {
   public:
    virtual ~Product() = default;

    virtual std::string getName() const = 0;
    // ...
};

/*
 * Concrete Products A and B
 * define products to be created
 */
class ConcreteProductA : public Product {
   public:
    std::string getName() const override { return "ConcreteProductA"; }
    // ...
};

class ConcreteProductB : public Product {
   public:
    std::string getName() const override { return "ConcreteProductB"; }
};

/*
 * Creator
 * declares the factory method that is supposed to return an
 * object of a Product class.
 */
class Creator {
   public:
    virtual ~Creator() = default;

    virtual std::shared_ptr<Product> factoryMethod() const = 0;
};

/*
 * Concrete Creators A and B
 * implements factory method that is responsible for creating
 * concrete products ie. it is classes that has
 * the knowledge of how to create the products
 */
class ConcreteCreatorA : public Creator {
   public:
    std::shared_ptr<Product> factoryMethod() const override {
        std::shared_ptr<Product> product = std::make_shared<ConcreteProductA>();
        return product;
    }
};

class ConcreteCreatorB : public Creator {
   public:
    std::shared_ptr<Product> factoryMethod() const override {
        std::shared_ptr<Product> product = std::make_shared<ConcreteProductB>();
        return product;
    }
};

/*
 * Alternative realization factoryMethod
 */
namespace alternative {
enum class Type { ConcreteProductA = 1, ConcreteProductB };

class Creator {
   public:
    virtual ~Creator() = default;

    virtual std::shared_ptr<Product> factoryMethod(Type type) const = 0;
};

class ConcreteCreator : public Creator {
   public:
    std::shared_ptr<Product> factoryMethod(Type type) const override {
        switch (type) {
            case Type::ConcreteProductA:
                return std::make_shared<ConcreteProductA>();
            case Type::ConcreteProductB:
                return std::make_shared<ConcreteProductB>();
            default:
                throw std::runtime_error("Invalid type");
        }
    }
};
}  // namespace alternative

int main() {
    std::shared_ptr<Creator> creator = std::make_shared<ConcreteCreatorA>();
    std::shared_ptr<Product> product = creator->factoryMethod();
    std::cout << "Product type: " << product->getName() << "\n";

    creator = std::make_shared<ConcreteCreatorB>();
    product = creator->factoryMethod();
    std::cout << "Product type: " << product->getName() << "\n";

    std::shared_ptr<alternative::Creator> aCreator =
        std::make_shared<alternative::ConcreteCreator>();
    try {
        product = aCreator->factoryMethod(alternative::Type::ConcreteProductA);
    } catch (std::exception const& e) {
        std::cout << "error: " << e.what() << "\n";
    }
    std::cout << "Product type: " << product->getName() << "\n";
}