#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

enum class Type { PROTOTYPE_A = 0, PROTOTYPE_B };

/*
 * Prototype
 * declares an interface for cloning itself
 */
class Prototype {
   public:
    virtual ~Prototype() = default;

    virtual std::shared_ptr<Prototype> clone() const = 0;
    virtual std::string type() const = 0;
    // ...
};

/*
 * Concrete Prototype A and B
 * implement an operation for cloning itself
 */
class ConcretePrototypeA : public Prototype {
   public:
    std::shared_ptr<Prototype> clone() const override {
        return std::make_shared<ConcretePrototypeA>(*this);
    }

    std::string type() const override { return "ConcretePrototypeA"; }
    // ...
};

class ConcretePrototypeB : public Prototype {
   public:
    std::shared_ptr<Prototype> clone() const override {
        return std::make_shared<ConcretePrototypeB>(*this);
    }

    std::string type() const override { return "ConcretePrototypeB"; }
    // ...
};

/*
 * Client
 * creates a new object by asking a prototype to clone itself
 */
class Client {
   public:
    void init() {
        prototypes[Type::PROTOTYPE_A] = std::make_shared<ConcretePrototypeA>();
        prototypes[Type::PROTOTYPE_B] = std::make_shared<ConcretePrototypeB>();
    }

    std::shared_ptr<Prototype> make(Type type) {
        return prototypes[type]->clone();
    }
    // ...

   private:
    std::unordered_map<Type, std::shared_ptr<Prototype>>
        prototypes;
};

int main(){
    Client client;
    client.init();

    std::shared_ptr<Prototype> prototype = client.make(Type::PROTOTYPE_A);
    std::cout << "Prototype: " << prototype->type() << "\n";

    prototype = client.make(Type::PROTOTYPE_B);
    std::cout << "Prototype: " << prototype->type() << "\n";
}