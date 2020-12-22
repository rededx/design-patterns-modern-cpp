#include <future>
#include <iostream>
#include <mutex>

/*
 * Meyers Singleton
 * has private static variable to hold one instance of the class
 * and method which gives us a way to instantiate the class
 */
class Singleton {
   public:
    Singleton(Singleton const &) = delete;
    Singleton &operator=(Singleton const &) = delete;

    static Singleton &getInstance(const std::string &value) {
        static Singleton instance{value};
        return instance;
    }

    std::string getValue() const { return value; }

   protected:
    Singleton() = default;
    Singleton(const std::string value) : value(value) {}
    ~Singleton() = default;

   protected:
    std::string value;
    // ...
};

int main() {
    Singleton &singleton1 = Singleton::getInstance("foo");
    Singleton &singleton2 = Singleton::getInstance("bar");

    std::cout << singleton1.getValue() << "\n";
    std::cout << singleton2.getValue() << "\n";

    auto foo = []() {
        Singleton &singleton = Singleton::getInstance("foo");
        std::cout << singleton.getValue() << "\n";
    };

    auto bar = []() {
        Singleton &singleton = Singleton::getInstance("bar");
        std::cout << singleton.getValue() << "\n";
    };

    std::async(std::launch::async, foo);
    std::async(std::launch::async, foo);
    std::async(std::launch::async, bar);
    std::async(std::launch::async, bar);
}