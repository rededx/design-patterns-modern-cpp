#include <iostream>
#include <memory>
#include <string>

/*
 * Subsystems
 * implement more complex subsystem functionality
 * and have no knowledge of the facade
 */
class SubsystemA {
   public:
    std::string suboperation() { return "SubsystemA"; }
    // ...
};

class SubsystemB {
   public:
    std::string suboperation() { return "SubsystemB"; }
    // ...
};

class SubsystemC {
   public:
    std::string suboperation() { return "SubsystemC"; }
    // ...
};

/*
 * Facade
 * delegates client requests to appropriate subsystem object
 * and unified interface that is easier to use
 */
class Facade {
   public:
    Facade() {
        subsystemA = std::make_shared<SubsystemA>();
        subsystemB = std::make_shared<SubsystemB>();
        subsystemC = std::make_shared<SubsystemC>();
    }

    ~Facade() = default;

    std::string operation1() {
        return subsystemA->suboperation() + " " + subsystemB->suboperation();
    }

    std::string operation2() { return subsystemC->suboperation(); }

   private:
    std::shared_ptr<SubsystemA> subsystemA;
    std::shared_ptr<SubsystemB> subsystemB;
    std::shared_ptr<SubsystemC> subsystemC;
};

int main() {
    Facade facade;

    std::cout << facade.operation1() << "\n";
    std::cout << facade.operation2() << "\n";
}