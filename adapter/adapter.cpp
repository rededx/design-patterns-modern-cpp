#include <iostream>
#include <memory>

/*
 * Target
 * defines specific interface that Client uses
 */
class Target {
   public:
    virtual ~Target() = default;

    virtual void request() = 0;
    // ...
};

/*
 * Adaptee
 * all requests get delegated to the Adaptee which defines
 * an existing interface that needs adapting
 */
class Adaptee {
   public:
    void specificRequest() {
        std::cout << "specific request"
                  << "\n";
    }
    // ... 
};

/*
 * Adapter
 * implements the Target interface and lets the Adaptee respond
 * to request on a Target by extending both classes
 * ie adapts the interface of Adaptee to the Target interface
 *
 * Alternatively, you can use composition or passing an adaptable object through
 * a method parameter.
 */
class Adapter : public Target, private Adaptee {
   public:
    virtual void request() { specificRequest(); }
    // ...
};

int main() {
    std::unique_ptr<Target> t = std::make_unique<Adapter>();
    t->request();
}