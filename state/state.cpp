#include <iostream>
#include <memory>

class Context;
class ConcreteStateB;
class ConcreteStateA;

/*
 * State
 * defines an interface for encapsulating the behavior associated
 * with a particular state of the Context
 */
class State {
   public:
    virtual ~State() = default;
    virtual void handle(Context& context) = 0;
};

/*
 * Context
 * defines the interface of interest to clients
 */
class Context {
   public:
    Context(std::shared_ptr<State> state) : state(state) {}
    void request() { state->handle(*this); }
    void setState(std::shared_ptr<State> state) {
        this->state = state;
        std::cout << "State: " << typeid(*state).name() << "\n";
    }

   private:
    std::shared_ptr<State> state;
};

/*
 * Concrete States
 * each subclass implements a behavior associated with a state
 * of the Context
 */
class ConcreteStateA : public State {
   public:
    void handle(Context& context) override;
};

class ConcreteStateB : public State {
   public:
    void handle(Context& context) override;
};

void ConcreteStateA::handle(Context& context) {
    std::shared_ptr<ConcreteStateB> newState =
        std::make_shared<ConcreteStateB>();
    context.setState(newState);
}

void ConcreteStateB::handle(Context& context) {
    std::shared_ptr<ConcreteStateA> newState =
        std::make_shared<ConcreteStateA>();
    context.setState(newState);
}

int main() {
    std::shared_ptr<State> initState = std::make_shared<ConcreteStateA>();
    Context context(initState);

    context.request();
    context.request();
    context.request();
    context.request();
    context.request();
}