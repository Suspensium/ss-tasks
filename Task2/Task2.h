#pragma once

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

class VariadicType {
public:
    VariadicType(const VariadicType &other);

    VariadicType(VariadicType &&other) noexcept;

    void swap(VariadicType &other) noexcept;

    VariadicType(const int val) : value(val) {
    }

    VariadicType(const double val): value(val) {
    }

    VariadicType(const bool val) : value(val) {
    }

    VariadicType &operator=(int val);

    VariadicType &operator=(double val);

    VariadicType &operator=(bool val);

    [[nodiscard]] std::variant<std::monostate, int, double, bool> get() const;

    [[nodiscard]] int getInt() const;

    [[nodiscard]] double getDouble() const;

    [[nodiscard]] bool getBool() const;

    void reset();

private:
    std::variant<std::monostate, int, double, bool> value;
};

void run_task2_union();

void run_task2_variadic();
