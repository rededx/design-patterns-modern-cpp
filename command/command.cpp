#include <iostream>
#include <memory>

/*
 * Receiver
 * knows how to perform the operations associated
 * with carrying out a request
 */
class Receiver {
   public:
    void action(std::string message) {
        std::cout << "Action called with message " << message << "\n";
    }
    // ...
};

/*
 * Command
 * declares an interface for all commands
 */
class Command {
   public:
    Command(std::shared_ptr<Receiver> receiver) : receiver(receiver) {}
    virtual ~Command() = default;
    virtual void execute() const = 0;

   protected:
    std::shared_ptr<Receiver> receiver;
};

/*
 * Concrete Command
 * implements execute by invoking the corresponding
 * operation(s) on Receiver
 */
class ConcreteCommand : public Command {
   public:
    ConcreteCommand(std::shared_ptr<Receiver> receiver) : Command(receiver) {}

    void setData(std::string data) { this->data = data; }

    void execute() const override { receiver->action(data); }

   private:
    std::string data;
};

/*
 * Invoker
 * asks the command to carry out the request
 */
class Invoker {
   public:
    void setCommand(std::shared_ptr<Command> command) {
        this->command = command;
    }

    void executeCommand() { command->execute(); }

   private:
    std::shared_ptr<Command> command;
};

int main() {
    std::shared_ptr<Invoker> invoker = std::make_shared<Invoker>();
    std::shared_ptr<Receiver> receiver = std::make_shared<Receiver>();
    std::shared_ptr<ConcreteCommand> command =
        std::make_shared<ConcreteCommand>(receiver);

    command->setData("Hello world!");
    invoker->setCommand(command);
    invoker->executeCommand();
}
