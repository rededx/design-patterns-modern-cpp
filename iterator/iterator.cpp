#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class Iterator;
template <typename T>
class ConcreteAggregate;
template <typename T>
class ForwardIterator;
template <typename T>
class BackwardIterator;

/*
 * Aggregate
 * defines an interface for aggregates and it decouples your
 * client from the implementation of your collection of objects
 */
template <typename T>
class Aggregate {
   public:
    virtual ~Aggregate() = default;
    virtual Iterator<T>* createForwardIterator() = 0;
    virtual Iterator<T>* createBackwardIterator() = 0;
};

/*
 * Concrete Aggregate
 * has a collection of objects and implements the method
 * that returns an Iterator for its collection
 *
 */
template <typename T>
class ConcreteAggregate : public Aggregate<T> {
   public:
    Iterator<T>* createForwardIterator() override {
        return new class ForwardIterator<T>(this);
    }

    Iterator<T>* createBackwardIterator() override {
        return new class BackwardIterator<T>(this);
    }

    void add(const T& content) { vector.push_back(content); }
    int size() const { return static_cast<int>(vector.size()); }
    T& get(int index) { return vector[index]; }
    const T& get(int index) const { return vector[index]; }

   private:
    std::vector<T> vector;
};

/*
 * Iterator
 * provides the interface that all iterators must implement and
 * a set of methods for traversing over elements
 */
template <typename T>
class Iterator {
   public:
    virtual ~Iterator() = default;
    virtual void reset() = 0;
    virtual const T& getCurrent() const = 0;
    virtual bool hasNext() = 0;
};

/*
 * Concrete Iterators 
 * implements the interface and is responsible for managing
 * the current position of the iterator
 */
template <typename T>
class ForwardIterator : public Iterator<T> {
   public:
    ForwardIterator(const ConcreteAggregate<T>* agg)
        : aggregate(agg), pos(-1) {}

    void reset() override { pos = -1; }
    const T& getCurrent() const override { return aggregate->get(pos); }
    bool hasNext() override {
        bool erg = false;
        if (pos < aggregate->size() - 1) {
            pos++;
            erg = true;
        }
        return erg;
    }

   private:
    const ConcreteAggregate<T>* aggregate;
    int pos;
};

template <typename T>
class BackwardIterator : public Iterator<T> {
   public:
    BackwardIterator(const ConcreteAggregate<T>* agg)
        : aggregate(agg), pos(agg->size()) {}

    void reset() override { pos = aggregate->size(); }
    const T& getCurrent() const override { return aggregate->get(pos); }
    bool hasNext() override {
        bool erg = false;
        if (pos > 0) {
            pos--;
            erg = true;
        }
        return erg;
    }

   private:
    const ConcreteAggregate<T>* aggregate;
    int pos;
};

int main() {
    ConcreteAggregate<int> intContainer;

    for (size_t i = 0; i < 10; i++) intContainer.add(i);

    Iterator<int>* intIterator1 = intContainer.createForwardIterator();
    Iterator<int>* intIterator2 = intContainer.createBackwardIterator();

    while (intIterator1->hasNext()) std::cout << intIterator1->getCurrent();
    std::cout << "\n";
    while (intIterator2->hasNext()) std::cout << intIterator2->getCurrent();

    delete intIterator1;
    delete intIterator2;
}
