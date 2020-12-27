#include <iostream>
#include <memory>

/*
 * AbstractClass
 * implements a template method defining the skeleton of an algorithm
 */
class AbstractClass {
   public:
    virtual ~AbstractClass() = default;

    void templateMethod() const {
        primitiveOperation1();
        primitiveOperation2();
        primitiveOperation3();
    }

   protected:
    virtual void primitiveOperation1() const = 0;
    virtual void primitiveOperation2() const = 0;
    virtual void primitiveOperation3() const {
        std::cout << "Base primitive operation 3\n";
    }
};

/*
 * Concrete Class
 * implements the primitive operations to carry out specific steps
 * of the algorithm, there may be many Concrete classes, each implementing
 * the full set of the required operation
 */
class ConcreteClassA : public AbstractClass {
   public:
    void primitiveOperation1() const override {
        std::cout << "Primitive operation 1\n";
    }

    void primitiveOperation2() const override {
        std::cout << "Primitive operation 2\n";
    }

    void primitiveOperation3() const override {
        std::cout << "Primitive operation 3\n";
    }
};

class ConcreteClassB : public AbstractClass {
   public:
    void primitiveOperation1() const override {
        std::cout << "Primitive operation 1\n";
    }

    void primitiveOperation2() const override {
        std::cout << "Primitive operation 2\n";
    }
};

int main() {
    std::shared_ptr<AbstractClass> concreteClass =
        std::make_shared<ConcreteClassA>();
    concreteClass->templateMethod();

    concreteClass = std::make_shared<ConcreteClassB>();
    concreteClass->templateMethod();
}