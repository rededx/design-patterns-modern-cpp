#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

/*
 * Product
 * the final object that will be created using Builder
 */
class Product {
   public:
    void addPart(std::string part) { parts.push_back(part); }

    std::string operator()() const {
        std::ostringstream oss;

        for (auto i : parts)
            if (i == parts.back())
                oss << i;
            else
                oss << i << " ";
        oss << "\n";

        return oss.str();
    }
    // ...

   private:
    std::vector<std::string> parts;
};

/*
 * Builder
 * abstract interface for creating products
 */
class Builder {
   public:
    virtual ~Builder() = default;

    virtual void buildPartA() const = 0;
    virtual void buildPartB() const = 0;
    virtual void buildPartC() const = 0;
    //...
};

/*
 * Concrete Builder X and Y
 * create real products and stores them in the composite structure
 */
class ConcreteBuilderX : public Builder {
   public:
    ConcreteBuilderX() { this->reset(); }

    void reset() { product = std::make_unique<Product>(); }
    void buildPartA() const override { product->addPart("AX"); }
    void buildPartB() const override { product->addPart("BX"); }
    void buildPartC() const override { product->addPart("CX"); }

    /**
     * Concrete Builders are supposed to provide their own methods for
     * retrieving results. That's because various types of builders may create
     * entirely different products that don't follow the same interface.
     * Therefore, such methods cannot be declared in the base Builder interface
     * (at least in a statically typed programming language).
     */
    std::unique_ptr<Product> getProduct() {
        std::unique_ptr<Product> result = std::move(product);
        this->reset();
        return std::move(result);
    }
    //...

   private:
    std::unique_ptr<Product> product;
};

class ConcreteBuilderY : public Builder {
   public:
    ConcreteBuilderY() { this->reset(); }

    void reset() { product = std::make_unique<Product>(); }
    void buildPartA() const override { product->addPart("AY"); }
    void buildPartB() const override { product->addPart("BY"); }
    void buildPartC() const override { product->addPart("CY"); }

    /**
     * Concrete Builders are supposed to provide their own methods for
     * retrieving results. That's because various types of builders may create
     * entirely different products that don't follow the same interface.
     * Therefore, such methods cannot be declared in the base Builder interface
     * (at least in a statically typed programming language).
     */
    std::unique_ptr<Product> getProduct() {
        std::unique_ptr<Product> result = std::move(product);
        this->reset();
        return std::move(result);
    }
    //...

   private:
    std::unique_ptr<Product> product;
};

/*
 * Director
 * responsible for managing the correct sequence of object creation
 */
class Director {
   public:
    void setBuilder(std::shared_ptr<Builder> builder) {
        this->builder = builder;
    }

    void constructA() { builder->buildPartA(); }
    void constructAll() {
        builder->buildPartA();
        builder->buildPartB();
        builder->buildPartC();
    }

    std::shared_ptr<ConcreteBuilderX> getConcreteBuilderX() {
        return std::static_pointer_cast<ConcreteBuilderX>(builder);
    }
    std::shared_ptr<ConcreteBuilderY> getConcreteBuilderY() {
        return std::static_pointer_cast<ConcreteBuilderY>(builder);
    }
    // ...

   private:
    std::shared_ptr<Builder> builder;
};

int main() {
    Director director;
    std::shared_ptr<Builder> builder = std::make_shared<ConcreteBuilderX>();

    director.setBuilder(builder);
    director.constructA();

    std::unique_ptr<Product> product1 =
        std::static_pointer_cast<ConcreteBuilderX>(builder)->getProduct();
    std::cout << "1st product parts: " << (*product1)();

    builder = std::make_shared<ConcreteBuilderY>();
    director.setBuilder(builder);
    director.constructAll();

    std::unique_ptr<Product> product2 = std::static_pointer_cast<ConcreteBuilderY>(builder)->getProduct();
    std::cout << "2nd product parts: " << (*product2)();
}