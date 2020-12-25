#include <iostream>
#include <list>
#include <memory>
#include <string>

class Observer;

/*
 * Subject
 * knows its observers and provides an interface for attaching
 * and detaching observers
 */
class Subject {
   public:
    virtual ~Subject() = default;
    virtual void attach(std::shared_ptr<Observer>) = 0;
    virtual void detach(std::shared_ptr<Observer>) = 0;
    virtual void notify() = 0;
    // ...
};

/*
 * Observer
 * defines an updating interface for objects that should be notified
 * of changes in a subject
 */
class Observer {
   public:
    virtual ~Observer() = default;
    virtual void update(const std::string&) = 0;
    // ...
};

/*
 * Concrete Observer
 * stores state of interest to ConcreteObserver objects and
 * sends a notification to its observers when its state changes
 */
class ConcreteObserver : public Observer,
                         public std::enable_shared_from_this<ConcreteObserver> {
   public:
    ConcreteObserver(std::shared_ptr<Subject> subject) : subject(subject) {
        number = ++ConcreteObserver::staticNumber;
    }

    void update(const std::string& messageFromSubject) override {
        this->messageFromSubject = messageFromSubject;
        printInfo();
    }

    void removeMeFromTheList() {
        try {
            std::shared_ptr<Observer> me = shared_from_this();
            this->subject->detach(me);
        } catch (const std::exception& e) {
            std::cout << "exception: " << e.what() << "\n";
        }
    }

    void printInfo() {
        std::cout << "Observer \"" << this->number
                  << "\": a new message is available --> "
                  << this->messageFromSubject << "\n";
    }

   private:
    std::string messageFromSubject;
    std::shared_ptr<Subject> subject;
    static int staticNumber;
    int number;
};

int ConcreteObserver::staticNumber = 0;

/*
 * Concrete Subject
 * stores state that should stay consistent with the subject's
 */
class ConcreteSubject : public Subject {
   public:
    void attach(std::shared_ptr<Observer> observer) override {
        listObservers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) override {
        listObservers.remove(observer);
    }

    void notify() override {
        std::list<std::shared_ptr<Observer>>::iterator iterator =
            listObservers.begin();
        howManyObserver();
        while (iterator != listObservers.end()) {
            (*iterator)->update(message);
            ++iterator;
        }
    }

    void createMessage(std::string message = "<empty>") {
        this->message = message;
        notify();
    }

    void howManyObserver() {
        std::cout << "There are " << listObservers.size()
                  << " observer in the list\n";
    }

    void someBusinessLogic() {
        message = "changing this message";
        notify();
        std::cout << "I'm about to do some important things\n";
    }

   private:
    std::list<std::shared_ptr<Observer>> listObservers;
    std::string message;
};

int main() {
    auto subject = std::make_shared<ConcreteSubject>();

    auto observer1 = std::make_shared<ConcreteObserver>(subject);
    subject->attach(observer1);
    auto observer2 = std::make_shared<ConcreteObserver>(subject);
    subject->attach(observer2);
    auto observer3 = std::make_shared<ConcreteObserver>(subject);
    subject->attach(observer3);

    subject->createMessage("Hello world!");

    observer3->removeMeFromTheList();

    subject->createMessage("Hi!");
    subject->someBusinessLogic();
}                   