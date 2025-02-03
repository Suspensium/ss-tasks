#pragma once

#include <any>
#include <variant>

class AnyType {
public:
    AnyType(const AnyType &other);

    AnyType(AnyType &&other) noexcept;

    void swap(AnyType &other) noexcept;

    AnyType(const int value) : intValue(value), currentType(Int) {
    }

    AnyType(const double value): doubleValue(value), currentType(Double) {
    }

    AnyType(const bool value) : boolValue(value), currentType(Bool) {
    }

    AnyType &operator=(int value);

    AnyType &operator=(double value);

    AnyType &operator=(bool value);

    [[nodiscard]] std::variant<int, double, bool> get() const;

    [[nodiscard]] int getInt() const;

    [[nodiscard]] double getDouble() const;

    [[nodiscard]] bool getBool() const;

    void reset();

private:
    union {
        int intValue = 0;
        double doubleValue;
        bool boolValue;
    };

    enum Type {
        None, Int, Double, Bool
    } currentType = None;
};

template<typename T>
concept fundamental = std::is_fundamental_v<T>;

class VariadicType {
public:
    VariadicType(const VariadicType &other);

    VariadicType(VariadicType &&other) noexcept;

    void swap(VariadicType &other) noexcept;

    template<fundamental T>
    VariadicType(T value) : variantValue(value) {
    }

    template<fundamental T>
    VariadicType &operator=(T value) {
        variantValue = value;
        return *this;
    }

    template<fundamental T>
    [[nodiscard]] T get() const {
        return std::get<T>(variantValue);
    }

    [[nodiscard]] std::any get() const {
        return std::visit([](const auto &value) -> std::any {
            return value;
        }, variantValue);
    }

    void reset();

private:
    std::variant<std::monostate, bool, char, int, long, long long, float, double, long double> variantValue;
};

void run_task2_union();

void run_task2_variadic();
