#include <iostream>

class SomeClass {
   public:
    SomeClass() = default;

    SomeClass(int id) : id(id) {}

    ~SomeClass() = default;

    int getId() { return id; }

   private:
    int id;
};

template <typename T>
class RAII {
   public:
    explicit RAII(T* p) : p(p) {}
    ~RAII() { delete p; }

    T* operator->() { return p; }
    const T* operator->() const { return p; }
    T& operator&() { return *p; }
    const T* operator&() const { return *p; }

   private:
    T* p;
};

class ContainerRAII {
   public:
    ContainerRAII(SomeClass* p) : p(p) {}

   private:
    RAII<SomeClass> p;
};

void test_0() {
    { RAII<SomeClass> p(new SomeClass(0)); }

    std::cout << "0.done\n";
}

void test_1() {
    {
        RAII<SomeClass> p(new SomeClass(1));
        std::cout << "id: " << p->getId() << "\n";

        SomeClass& someClassRef = p.operator&();
        std::cout << "id: " << someClassRef.getId() << "\n";
    }

    std::cout << "1.done\n";
}

void test_2() {
    { ContainerRAII cp(new SomeClass(2)); }

    std::cout << "2.done\n";
}

int main() {
    test_0();
    test_1();
    test_2();
}