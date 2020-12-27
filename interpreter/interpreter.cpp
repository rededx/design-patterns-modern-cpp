#include <iostream>
#include <map>
#include <memory>

/*
 * Context
 * contains information that's global to the interpreter
 */
class Context {
   public:
    void set(const std::string& var, const bool value) {
        vars.insert(std::pair<std::string, bool>(var, value));
    }

    bool get(const std::string& exp) { return vars[exp]; }

   private:
    std::map<std::string, bool> vars;
};

/*
 * Abstract Expression
 * declares an abstract Interpret operation that is common to all nodes
 * in the abstract syntax tree
 */
class AbstractExpression {
   public:
    virtual ~AbstractExpression() = default;
    virtual bool interpretet(const std::shared_ptr<Context>) { return false; }
};

/*
 * Terminal Expression
 * implements an Interpret operation associated with terminal symbols
 * in the grammar (an instance is required for every terminal symbol
 * in a sentence)
 */
class TerminalExpression : public AbstractExpression {
   public:
    TerminalExpression(const std::string& val) : value(val) {}

    bool interpretet(const std::shared_ptr<Context> context) override {
        return context->get(value);
    }

   private:
    std::string value;
};

/*
 * Nonterminal Expression
 * implements an Interpret operation for nonterminal symbols
 * in the grammar (one such class is required for every rule in the grammar)
 */
class NonterminalExpression : public AbstractExpression {
   public:
    NonterminalExpression(std::shared_ptr<AbstractExpression> left,
                          std::shared_ptr<AbstractExpression> right)
        : lop(left), rop(right) {}

    bool interpretet(const std::shared_ptr<Context> context) override {
        return lop->interpretet(context) && rop->interpretet(context);
    }

   private:
    std::shared_ptr<AbstractExpression> lop;
    std::shared_ptr<AbstractExpression> rop;
};

int main() {
    std::shared_ptr<AbstractExpression> a =
        std::make_shared<TerminalExpression>("A");
    std::shared_ptr<AbstractExpression> b =
        std::make_shared<TerminalExpression>("B");
    std::shared_ptr<AbstractExpression> exp =
        std::make_shared<NonterminalExpression>(a, b);

    auto context = std::make_shared<Context>();
    context->set("A", true);
    context->set("B", false);

    std::cout << context->get("A") << " AND " << context->get("B");
    std::cout << " = " << exp->interpretet(context) << "\n";
}