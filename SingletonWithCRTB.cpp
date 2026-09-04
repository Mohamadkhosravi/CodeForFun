#include <iostream>
#include <cstdint>

// ---- CRTP Singleton base ----
// Any class that inherits from Singleton<T> automatically becomes
// a singleton, with no need to rewrite the boilerplate every time.
template <typename T>
class Singleton {
public:
    static T& Instance() {
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
};

// ---- Shared interface for CAN message managers ----
class CanManagement {
public:
    virtual ~CanManagement() = default;
    virtual uint32_t getID() const = 0;
    virtual uint32_t getDLC() const = 0;
    virtual uint32_t getPeriod() const = 0;
};

// ---- AC unit, singleton via CRTP ----
class CAN_ACManagement : public CanManagement, public Singleton<CAN_ACManagement> {
    friend class Singleton<CAN_ACManagement>;

public:
    uint32_t getID() const override { return current_id; }
    uint32_t getDLC() const override { return dlc; }
    uint32_t getPeriod() const override { return period; }

private:
    CAN_ACManagement() : current_id(0x1B6), dlc(8), period(100) {}

    uint32_t current_id;
    uint32_t dlc;
    uint32_t period;
};

// ---- BCM unit, singleton via CRTP ----
class CAN_BCMManagement : public CanManagement, public Singleton<CAN_BCMManagement> {
    friend class Singleton<CAN_BCMManagement>;

public:
    uint32_t getID() const override { return current_id; }
    uint32_t getDLC() const override { return dlc; }
    uint32_t getPeriod() const override { return period; }

private:
    CAN_BCMManagement() : current_id(0x7DF), dlc(8), period(50) {}

    uint32_t current_id;
    uint32_t dlc;
    uint32_t period;
};

// ---- Demo ----
int main() {
    CAN_ACManagement& ac = CAN_ACManagement::Instance();
    CAN_BCMManagement& bcm = CAN_BCMManagement::Instance();

    std::cout << "AC  -> ID: 0x" << std::hex << ac.getID()
              << " DLC: " << std::dec << ac.getDLC()
              << " Period: " << ac.getPeriod() << "ms\n";

    std::cout << "BCM -> ID: 0x" << std::hex << bcm.getID()
              << " DLC: " << std::dec << bcm.getDLC()
              << " Period: " << bcm.getPeriod() << "ms\n";

    // Proving it's really a singleton: same instance every time.
    std::cout << "Same AC instance? "
              << (&ac == &CAN_ACManagement::Instance() ? "yes" : "no") << "\n";

    return 0;
}
