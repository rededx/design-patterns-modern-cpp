#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

/*
 * Strategy
 * declares an interface common to all supported algorithms
 */
class Strategy {
   public:
    virtual ~Strategy() = default;
    virtual std::string doAlgorithm(
        const std::vector<std::string>& data) const = 0;
    virtual std::string getName() const = 0;
};

/*
 * Context
 * maintains a reference to a Strategy object
 */
class Context {
   public:
    Context(std::unique_ptr<Strategy> strategy)
        : strategy(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<Strategy> strategy) {
        this->strategy = std::move(strategy);
    }

    void doSomeBusinesLogic() const {
        std::vector<std::string> someStrings{"A", "B", "C", "B", "D"};

        std::string result = strategy->doAlgorithm(someStrings);
        std::cout << "Context: " << result << "\n";
    }

   private:
    std::unique_ptr<Strategy> strategy;
};

/*
 * Concrete Strategies
 * implement the algorithm using the Strategy interface
 */
class ConcreteStrategyA : public Strategy {
   public:
    std::string getName() const override { return "Normal Sorting"; }

    std::string doAlgorithm(
        const std::vector<std::string>& data) const override {
        std::string result;

        std::for_each(
            std::begin(data), std::end(data),
            [&result](const std::string& letter) { result += letter; });

        std::sort(std::begin(result), std::end(result));

        return result;
    }
};

class ConcreteStrategyB : public Strategy {
   public:
    std::string getName() const override { return "Reverse Sorting"; }

    std::string doAlgorithm(
        const std::vector<std::string>& data) const override {
        std::string result;

        std::for_each(
            std::begin(data), std::end(data),
            [&result](const std::string& letter) { result += letter; });

        std::sort(std::begin(result), std::end(result));
        std::reverse(std::begin(result), std::end(result));

        return result;
    }
};

int main() {
    Context context(std::make_unique<ConcreteStrategyA>());
    context.doSomeBusinesLogic();

    context.setStrategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinesLogic();
}
