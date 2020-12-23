#include <iostream>
#include <memory>

/*
 * Implementor
 * defines the interface for implementation classes
 */
class Implementor {
   public:
    virtual ~Implementor() = default;

    virtual std::string operationImpl() const = 0;
    // ...
};

/*
 * Concrete Implementors
 * implement the Implementor interface and define concrete implementations
 */
class ConcreteImplA : public Implementor {
   public:
    std::string operationImpl() const override { return "ConcreteImplA"; }
    // ...
};

class ConcreteImplB : public Implementor {
   public:
    std::string operationImpl() const override { return "ConcreteImplB"; }
    // ...
};

/*
 * Abstraction
 * defines the abstraction's interface
 */
class Abstraction {
   public:
    Abstraction(std::shared_ptr<Implementor> implementor)
        : implementor(implementor) {}

    virtual ~Abstraction() = default;

    virtual std::string operation() const = 0;
    // ...

   protected:
    std::shared_ptr<Implementor> implementor;
};

/*
 * RefinedAbstraction
 * extends the interface defined by Abstraction
 */
class RefinedAbstraction : public Abstraction {
   public:
    RefinedAbstraction(std::shared_ptr<Implementor> implementor)
        : Abstraction(implementor) {}

    std::string operation() const override {
        return "RefinedAbstraction: refined operation with " +
               implementor->operationImpl();
    }
    // ...
};

int main() {
    std::shared_ptr<Implementor> implementor =
        std::make_shared<ConcreteImplA>();
    std::shared_ptr<Abstraction> abstraction =
        std::make_shared<RefinedAbstraction>(implementor);

    std::cout << abstraction->operation();
}