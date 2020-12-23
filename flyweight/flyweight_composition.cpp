#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class SharedState {
   public:
    SharedState(const std::string& brand, const std::string& model,
                const std::string& color)
        : brand(brand), model(model), color(color) {}

    friend std::ostream& operator<<(std::ostream& os, const SharedState& ss);

    // private:
    std::string brand;
    std::string model;
    std::string color;
};

std::ostream& operator<<(std::ostream& os, const SharedState& ss) {
    return os << "[ " << ss.brand << ", " << ss.model << ", " << ss.color
              << " ]";
}

class UniqueState {
   public:
    UniqueState(const std::string& owner, const std::string& plates)
        : owner(owner), plates(plates) {}

    friend std::ostream& operator<<(std::ostream& os, const UniqueState& us);

   private:
    std::string owner;
    std::string plates;
};

std::ostream& operator<<(std::ostream& os, const UniqueState& us) {
    return os << "[ " << us.owner << ", " << us.plates << " ]";
}

/*
 * Flyweight
 * declares an interface through which flyweights can receive
 * and act on extrinsic state
 */
class Flyweight {
   public:
    Flyweight(const SharedState& state) {
        repeatingState = std::make_shared<SharedState>(state);
    }
    ~Flyweight() = default;

    std::shared_ptr<SharedState> getSharedState() const {
        return repeatingState;
    }

    void operation(const UniqueState& uniqueState) const {
        std::cout << "Flyweight: Displaying shared (" << *repeatingState
                  << ") and unique (" << uniqueState << ") state.\n";
    }

   private:
    std::shared_ptr<SharedState> repeatingState;
};

/*
 * FlyweightFactory
 * creates and manages flyweight objects and ensures
 * that flyweights are shared properly
 */
class FlyweightFactory {
   public:
    FlyweightFactory(std::initializer_list<SharedState> shareStates) {
        for (const SharedState& state : shareStates) {
            std::string key = getKey(state);
            std::shared_ptr<Flyweight> flyweight =
                std::make_shared<Flyweight>(state);
            std::pair<std::string, std::shared_ptr<Flyweight>> pair =
                std::make_pair<>(key, flyweight);
            flyweights.insert(pair);
        }
    }

    std::shared_ptr<Flyweight> getFlywight(const SharedState& sharedState) {
        std::string key = getKey(sharedState);
        if (flyweights.find(key) == flyweights.end()) {
            std::shared_ptr<Flyweight> flyweight =
                std::make_shared<Flyweight>(sharedState);
            std::pair<std::string, std::shared_ptr<Flyweight>> pair =
                std::make_pair<>(key, flyweight);
            flyweights.insert(pair);
        }

        return flyweights.at(key);
    }

    void listFlyweights() const {
        size_t count = flyweights.size();
        std::cout << "FlyweightFactory: " << count << " flyweights:\n";

        for (std::pair<std::string, std::shared_ptr<Flyweight>> pair :
             flyweights) {
            std::cout << pair.first << "\n";
        }
    }

   private:
    std::string getKey(const SharedState& ss) const {
        return ss.brand + "_" + ss.model + "_" + ss.color;
    }

    std::unordered_map<std::string, std::shared_ptr<Flyweight>> flyweights;
};

int main() {
    FlyweightFactory factory{{"Chevrolet", "Camaro2018", "pink"},
                             {"MercedesBenz", "C300", "black"},
                             {"MercedesBenz", "C500", "red"},
                             {"BMW", "M5", "red"},
                             {"BMW", "X6", "white"}};

    factory.listFlyweights();
    std::cout << "\n";

    std::shared_ptr<Flyweight> flyweight =
        factory.getFlywight({"BMW", "X1", "red"});

    flyweight->operation({"7d8sf", "rededx"});
    std::cout << "\n";
    
    factory.listFlyweights();
}