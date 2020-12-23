#include <iostream>
#include <map>
#include <memory>

/*
 * Flyweight
 * declares an interface through which flyweights can receive
 * and act on extrinsic state
 */
class Flyweight {
   public:
    virtual ~Flyweight() = default;
    virtual void operation() const = 0;
    // ...
};

/*
 * UnsharedConcreteFlyweight
 * not all subclasses need to be shared
 */
class UnsharedConcreteFlyweight : public Flyweight {
   public:
    UnsharedConcreteFlyweight(const int state) : state(state) {}

    ~UnsharedConcreteFlyweight() = default;

    void operation() const override {
        std::cout << "Unshared Flyweight with state " << state << "\n";
    }
    // ...

   private:
    int state;
};

/*
 * ConcreteFlyweight
 * implements the Flyweight interface and adds storage
 * for intrinsic state
 */
class ConcreteFlyweight : public Flyweight {
   public:
    ConcreteFlyweight(const int state) : state(state) {}

    ~ConcreteFlyweight() = default;

    void operation() const override {
        std::cout << "Concrete Flyweight with state " << state << "\n";
    }
    // ...

   private:
    int state;
};

/*
 * FlyweightFactory
 * creates and manages flyweight objects and ensures
 * that flyweights are shared properly
 */
class FlyweightFactory {
   public:
    std::shared_ptr<Flyweight> getFlyweight(const int key) {
        if (flyweights.find(key) == flyweights.end()) {
            std::shared_ptr<Flyweight> flyweight =
                std::make_shared<ConcreteFlyweight>(key);
            flyweights.insert(
                std::pair<int, std::shared_ptr<Flyweight>>(key, flyweight));
            return flyweight;
        }
        return flyweights.at(key);
    }

    void listFlyweights() const {
        size_t count = flyweights.size();
        std::cout << "FlyweightFactory: " << count << " flyweights:\n";

        for (std::pair<int, std::shared_ptr<Flyweight>> pair : flyweights) {
            std::cout << pair.first << "\n";
        }
    }
    // ...

   private:
    std::map<int, std::shared_ptr<Flyweight>> flyweights;
};

int main() {
    std::shared_ptr<FlyweightFactory> factory =
        std::make_shared<FlyweightFactory>();

    factory->getFlyweight(1)->operation();
    factory->getFlyweight(2)->operation();
    factory->getFlyweight(2)->operation();

    factory->listFlyweights();
}
