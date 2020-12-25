#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

/*
 * Memento
 * stores internal state of the Originator object and protects
 * against access by objects other than the originator
 */
class Memento {
   public:
    virtual ~Memento() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDate() const = 0;
    virtual std::string getState() const = 0;
};

class ConcreteMemento : public Memento {
   public:
    ConcreteMemento(std::string state) : state(state) {
        date = currentTimeToString();
    }

    ~ConcreteMemento() = default;

    std::string getState() const override { return state; }

    std::string getName() const override {
        return date + "/ (" + state.substr(0, 9) + " ...)";
    }

    std::string getDate() const override { return date; }

   private:
    std::string currentTimeToString() {
        char str[32];
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        return std::ctime(&now_c);
    }

    std::string state;
    std::string date;
};

/*
 * Originator
 * creates a memento containing a snapshot of its current internal
 * state and uses the memento to restore its internal state
 */
class Originator {
   public:
    Originator(std::string state) : state(state) {}

    void doSomething() {
        std::cout << "Originator: I'm doing something important!\n";
        state = generateRandomString(30);
        std::cout << "Originator: state has changed to: " << state << "\n";
    }

    std::shared_ptr<Memento> save() {
        return std::make_shared<ConcreteMemento>(state);
    }

    void restore(std::shared_ptr<Memento> memento) {
        state = memento->getState();
        std::cout << "Originator: state has changed to: " << state << "\n";
    }

   private:
    std::string generateRandomString(int length = 10) {
        const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        int stringLength = sizeof(alphanum) - 1;

        std::string randomString;
        for (int i = 0; i < length; i++) {
            randomString += alphanum[std::rand() % stringLength];
        }

        return randomString;
    }

    std::string state;
};

/*
 * CareTaker
 * is responsible for the memento's safe keeping
 */
class CareTaker {
   public:
    CareTaker(std::shared_ptr<Originator> originator)
        : originator(originator) {}

    void backup() {
        std::cout << "CareTaker: saving orininator's state...\n";
        mementos.push_back(originator->save());
    }

    void undo() {
        if (!mementos.size()) return;

        std::shared_ptr<Memento> memento = mementos.back();
        mementos.pop_back();
        std::cout << "CareTaker: restoring state to: " << memento->getName()
                  << "\n";

        try {
            originator->restore(memento);
        } catch (...) {
            undo();
        }
    }

    void showHistory() const {
        std::cout << "CareTaker: here's the list of mementos:\n";
        for (std::shared_ptr<Memento> memento : mementos)
            std::cout << memento->getName() << "\n";
    }

   private:
    std::vector<std::shared_ptr<Memento>> mementos;
    std::shared_ptr<Originator> originator;
};

int main() {
    std::shared_ptr<Originator> originator = std::make_shared<Originator>(
        "I'm the original state of this Originator");
    auto careTaker = std::make_shared<CareTaker>(originator);

    careTaker->backup();
    originator->doSomething();
    careTaker->backup();
    originator->doSomething();
    careTaker->backup();
    originator->doSomething();

    std::cout << "\n";
    careTaker->showHistory();

    std::cout << "\n";
    careTaker->undo();
    std::cout << "\n";
    careTaker->showHistory();
}