#include <iostream>
#include <memory>

class Colleague;

/*
 * Mediator
 * defines an interface for communicating with Colleague objects
 */
class Mediator {
   public:
    virtual ~Mediator() = default;
    virtual void notify(std::shared_ptr<Colleague> sender) const = 0;
};

/*
 * Colleague classes
 * each colleague communicates with its mediator whenever
 * it would have otherwise communicated with another colleague
 */
class Colleague {
   public:
    Colleague() = default;
    Colleague(std::shared_ptr<Mediator> mediator) : mediator(mediator) {}

    void setMediator(std::shared_ptr<Mediator> mediator) {
        this->mediator = mediator;
    }

   protected:
    std::weak_ptr<Mediator> mediator;
};

class ConcreteColleagueA
    : public Colleague,
      public std::enable_shared_from_this<ConcreteColleagueA> {
   public:
    void doA() {
        std::cout << "Component 1 does A.\n";
        std::shared_ptr<Mediator> sp = mediator.lock();
        sp->notify(shared_from_this());
    }

    void doX() { std::cout << "Component 1 does X.\n"; }
};

class ConcreteColleagueB
    : public Colleague,
      public std::enable_shared_from_this<ConcreteColleagueB> {
   public:
    void doB() {
        std::cout << "Component 2 does A.\n";
        std::shared_ptr<Mediator> sp = mediator.lock();
        sp->notify(shared_from_this());
    }

    void doY() { std::cout << "Component 2 does Y.\n"; }

    void doZ() { std::cout << "Component 2 does Z.\n"; }
};

/*
 * Concrete Mediator
 * implements cooperative behavior by coordinating Colleague objects
 * and knows its colleagues
 */
class ConcreteMediator : public Mediator,
                         public std::enable_shared_from_this<ConcreteMediator> {
   public:
    ConcreteMediator(std::shared_ptr<ConcreteColleagueA> cA,
                     std::shared_ptr<ConcreteColleagueB> cB)
        : componentA(cA), componentB(cB) {}

    ~ConcreteMediator() = default;

    void setConcreteColleagueA() {
        componentA->setMediator(shared_from_this());
    }

    void setConcreteColleagueB() {
        componentB->setMediator(shared_from_this());
    }

    void setConcreteColleagues() {
        componentA->setMediator(shared_from_this());
        componentB->setMediator(shared_from_this());
    }

    void notify(std::shared_ptr<Colleague> sender) const override {
        if (sender == componentA) {
            std::cout
                << "Mediator reacts on Component A and triggers following "
                   "operations: \n";
            componentA->doX();
            componentB->doY();
        }

        if (sender == componentB) {
            std::cout
                << "Mediator reacts on Component B and triggers following "
                   "operations: \n";
            componentA->doX();
            componentB->doY();
            componentB->doZ();
        }
    }

   private:
    std::shared_ptr<ConcreteColleagueA> componentA;
    std::shared_ptr<ConcreteColleagueB> componentB;
};

int main() {
    auto cA = std::make_shared<ConcreteColleagueA>();
    auto cB = std::make_shared<ConcreteColleagueB>();

    auto mediator = std::make_shared<ConcreteMediator>(cA, cB);
    mediator->setConcreteColleagues();

    cA->doA();
    cB->doB();
}