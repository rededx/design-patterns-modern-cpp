#include <array>
#include <iostream>
#include <memory>
#include <string>

class Element;
class ConcreteElementA;
class ConcreteElementB;

/*
 * Visitor
 * declares a Visit operation for each class of ConcreteElement
 * in the object structure
 */
class Visitor {
   public:
    virtual ~Visitor() = default;
    virtual void visit(
        const std::shared_ptr<const class ConcreteElementA> element) const = 0;
    virtual void visit(
        const std::shared_ptr<const class ConcreteElementB> element) const = 0;
};

/*
 * Element
 * defines an accept operation that takes a visitor as an argument
 */
class Element {
   public:
    virtual ~Element() = default;
    virtual void accept(std::shared_ptr<Visitor> visitor) const = 0;
};

/*
 * Concrete Elements
 * implement an accept operation that takes a visitor as an argument
 */
class ConcreteElementA : public Element,
                         public std::enable_shared_from_this<ConcreteElementA> {
   public:
    virtual void accept(std::shared_ptr<Visitor> visitor) const override {
        visitor->visit(shared_from_this());
    }

    std::string exclusiveMethod() const { return "A"; }
};

class ConcreteElementB : public Element,
                         public std::enable_shared_from_this<ConcreteElementB> {
   public:
    virtual void accept(std::shared_ptr<Visitor> visitor) const override {
        visitor->visit(shared_from_this());
    }

    std::string specialMethod() const { return "B"; }
};

/*
 * Concrete Visitors
 * implement each operation declared by Visitor, which implement
 * a fragment of the algorithm defined for the corresponding class
 * of object in the structure
 */
class ConcreteVisitorX : public Visitor {
   public:
    virtual void visit(const std::shared_ptr<const class ConcreteElementA>
                           element) const override {
        std::cout << element->exclusiveMethod() << " + ConcreteVisitorX\n";
    }

    virtual void visit(const std::shared_ptr<const class ConcreteElementB>
                           element) const override {
        std::cout << element->specialMethod() << " + ConcreteVisitorX\n";
    }
};

class ConcreteVisitorY : public Visitor {
   public:
    virtual void visit(const std::shared_ptr<const class ConcreteElementA>
                           element) const override {
        std::cout << element->exclusiveMethod() << " + ConcreteVisitorY\n";
    }

    virtual void visit(const std::shared_ptr<const class ConcreteElementB>
                           element) const override {
        std::cout << element->specialMethod() << " + ConcreteVisitorY\n";
    }
};

int main() {
    std::array<std::shared_ptr<Element>, 2> elements = {
        std::make_shared<ConcreteElementA>(),
        std::make_shared<ConcreteElementB>()};

    std::shared_ptr<Visitor> visitor = std::make_shared<ConcreteVisitorX>();

    for (std::shared_ptr<Element> element : elements) {
        element->accept(visitor);
    }

    visitor = std::make_shared<ConcreteVisitorY>();

    for (std::shared_ptr<Element> element : elements) {
        element->accept(visitor);
    }
}