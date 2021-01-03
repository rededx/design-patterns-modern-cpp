#include <iostream>
#include <memory>
#include <string>

class AbstractObject {
   public:
    virtual std::string operation() const = 0;
};

class RealObject : public AbstractObject {
   public:
    std::string operation() const override {
        return std::string("computed something");
    }
};

class NullObject : public AbstractObject {
   public:
    std::string operation() const override { return std::string(""); }
};

void doSomething(const AbstractObject& obj) {
    std::cout << obj.operation() << "\n";
}

int main() {
    RealObject realObject;
    doSomething(realObject);

    NullObject nullObject;
    doSomething(nullObject);
}