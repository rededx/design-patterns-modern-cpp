#include <iostream>
#include <memory>

/*
 * Subject
 * defines the common interface for RealSubject and Proxy
 * so that a Proxy can be used anywhere a RealSubject is expected
 */
class Subject {
   public:
    virtual ~Subject() = default;
    virtual void request() const = 0;
    // ...
};

/*
 * Real Subject
 * defines the real object that the proxy represents
 */
class RealSubject : public Subject {
   public:
    void request() const override { std::cout << "RealSubject request\n"; }
    // ...
};

/*
 * Proxy
 * maintains a reference that lets the proxy access the real subject
 */
class Proxy : public Subject {
   public:
    Proxy() { subsect = std::make_shared<RealSubject>(); }

    void request() const override { std::cout << "Proxy request\n"; }
    std::shared_ptr<RealSubject> getRealSubject() { return subsect; }

   private:
    std::shared_ptr<RealSubject> subsect;
};

int main() {
    std::unique_ptr<Proxy> proxy = std::make_unique<Proxy>();
    proxy->request();
    proxy->getRealSubject()->request();
}
