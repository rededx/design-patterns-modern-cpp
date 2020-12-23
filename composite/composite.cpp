#include <iostream>
#include <memory>
#include <vector>

/*
 * Component
 * defines an interface for all objects in the composition
 * both the composite and the leaf nodes
 */
class Component {
   public:
    Component() : parent(nullptr) {}
    virtual ~Component() = default;
    void setParent(std::shared_ptr<Component> parent) { this->parent = parent; }
    std::shared_ptr<Component> getParent() const { return parent; }
    virtual void add(std::shared_ptr<Component> component) {}
    virtual void remove(std::shared_ptr<Component> component) {}
    virtual bool isComposite() const { return false; }
    virtual std::string operation() const = 0;

   protected:
    std::shared_ptr<Component> parent;
};

/*
 * Leaf
 * defines the behavior for the elements in the composition,
 * it has no children
 */
class Leaf : public Component {
   public:
    std::string operation() const override { return "Leaf"; }
};

/*
 * Composite
 * defines behavior of the components having children
 * and store child components
 */
class Composite : public Component,
                  public std::enable_shared_from_this<Composite> {
   public:
    virtual ~Composite() { children.clear(); }
    void add(std::shared_ptr<Component> component) {
        std::weak_ptr<Component> wComp = component;
        children.push_back(wComp);
        component->setParent(shared_from_this());
    }
    void remove(std::shared_ptr<Component> component) {
        auto i = children.begin();
        while (i != children.end()) {
            std::shared_ptr<Component> comp = i->lock();

            if (comp == component)
                i = children.erase(i);
            else
                ++i;
        }
    }

    bool isComposite() const override { return true; }
    std::string operation() const override {
        std::string result;
        for (int i = 0; i < children.size(); ++i) {
            std::weak_ptr<Component> wComp = children[i];
            std::shared_ptr<Component> comp = wComp.lock();

            if (i == children.size() - 1)
                result += comp->operation();
            else
                result += comp->operation() + "+";
        }
        return "Branch(" + result + ")";
    }

   protected:
    std::vector<std::weak_ptr<Component>> children;
};

int main() {
    std::shared_ptr<Component> simple = std::make_shared<Leaf>();
    std::cout << "Result: " << simple->operation() << "\n";

    std::shared_ptr<Component> tree = std::make_shared<Composite>();
    std::shared_ptr<Component> branch1 = std::make_shared<Composite>();
    std::shared_ptr<Component> leaf_1 = std::make_shared<Leaf>();
    std::shared_ptr<Component> leaf_2 = std::make_shared<Leaf>();
    std::shared_ptr<Component> leaf_3 = std::make_shared<Leaf>();
    std::shared_ptr<Component> leaf_4 = std::make_shared<Leaf>();

    branch1->add(leaf_1);
    branch1->add(leaf_2);
    std::shared_ptr<Component> branch2 = std::make_shared<Composite>();

    branch2->add(leaf_3);
    tree->add(branch1);
    tree->add(branch2);
    std::cout << "Result: " << tree->operation() << "\n";

    if (tree->isComposite()) tree->add(simple);
    std::cout << "Result: " << tree->operation() << "\n";

    tree->remove(simple);
    tree->remove(branch2);
    std::cout << "Result: " << tree->operation() << "\n";
}
