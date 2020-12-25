#include <array>
#include <iostream>
#include <memory>
#include <string>

class Request {
   public:
    explicit Request(int type, const std::string& param)
        : type(type), param(param) {}

    int getType() const { return type; }
    std::string getParam() const { return param; }
    // ...

   private:
    int type;
    std::string param;
};

/*
 * Handler
 * defines an interface for handling requests and
 * optionally implements the successor link
 */
class Handler {
   public:
    Handler() : successor(nullptr) {}
    virtual ~Handler() = default;

    virtual void handleRequest(const Request&) = 0;
    void setSuccessor(std::shared_ptr<Handler> successor) {
        this->successor = successor;
    }
    // ...

   protected:
    std::shared_ptr<Handler> successor;
};

/*
 * Concrete Handlers
 * handle requests they are responsible for
 */
class ConcreteHandlerA : public Handler {
   public:
    void handleRequest(const Request& request) override {
        if (request.getType() >= 0 && request.getType() < 10)
            std::cout << "ConcreteHandlerA: " << request.getParam() << "\n";
        else if (successor)
            successor->handleRequest(request);
    }
    // ...
};

class ConcreteHandlerB : public Handler {
   public:
    void handleRequest(const Request& request) override {
        if (request.getType() >= 10 && request.getType() < 20)
            std::cout << "ConcreteHandlerB: " << request.getParam() << "\n";
        else if (successor)
            successor->handleRequest(request);
    }
    // ...
};

int main() {
    std::shared_ptr<Handler> handler1 = std::make_shared<ConcreteHandlerA>();
    std::shared_ptr<Handler> handler2 = std::make_shared<ConcreteHandlerB>();

    handler1->setSuccessor(handler2);

    std::array<Request, 3> requests = {
        Request{17, std::string("Req. No. 7")},
        Request{21, std::string("Req. No. 21")},
        Request{18, std::string("Req. No. 18")},
    };

    for (auto request : requests) handler1->handleRequest(request);
}
