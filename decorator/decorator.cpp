#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/*
 * Component
 * defines an interface for objects that can have responsibilities
 * added to them dynamically
 */
class Component {
   public:
    virtual ~Component() = default;
    virtual std::string operation() const = 0;
    // ...
};

/*
 * Concrete Component
 * defines an object to which additional responsibilities
 * can be attached
 */
class ConcreteComponent final : public Component {
   public:
    std::string operation() const override { return "ConcreteComponent"; }
    // ...
};

/*
 * Decorator
 * maintains a reference to a Component object and defines an interface
 * that conforms to Component's interface
 */
class Decorator : public Component {
   public:
    Decorator(const std::shared_ptr<Component>& component)
        : component(component) {}

    std::string operation() const override { return component->operation(); }
    // ...

   protected:
    std::shared_ptr<Component> component;
};

/*
 * Concrete Decorators
 * add responsibilities to the component (can extend the state
 * of the component)
 */
class ConcreteDecoratorA final : public Decorator {
   public:
    ConcreteDecoratorA(const std::shared_ptr<Component>& component)
        : Decorator(component) {}

    std::string operation() const override {
        std::string parentResult = Decorator::operation();
        std::string decoratedResult =
            "ConcreteDecoratorA ( " + parentResult + " )";
        return decoratedResult;
    }
};

class ConcreteDecoratorB final : public Decorator {
   public:
    ConcreteDecoratorB(const std::shared_ptr<Component>& component)
        : Decorator(component) {}

    std::string operation() const override {
        std::string parentResult = Decorator::operation();
        std::string decoratedResult =
            "ConcreteDecoratorB [ " + parentResult + " ]";
        return decoratedResult;
    }
};

int main() {
    std::shared_ptr<Component> component =
        std::make_shared<ConcreteComponent>();
    std::shared_ptr<Component> decorator1 =
        std::make_shared<ConcreteDecoratorA>(component);
    std::shared_ptr<Component> decorator2 =
        std::make_shared<ConcreteDecoratorB>(decorator1);

    std::cout << decorator2->operation() << "\n";
}
