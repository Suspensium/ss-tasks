#include "Task2.h"

#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <gtest/gtest-matchers.h>

// AnyType

AnyType::AnyType(const AnyType &other) {
    currentType = other.currentType;

    switch (currentType) {
        case Int:
            intValue = other.intValue;
            break;
        case Double:
            doubleValue = other.doubleValue;
            break;
        case Bool:
            boolValue = other.boolValue;
            break;
        case None:
            break;
    }
}

AnyType::AnyType(AnyType &&other) noexcept {
    currentType = other.currentType;

    switch (currentType) {
        case Int:
            intValue = other.intValue;
            break;
        case Double:
            doubleValue = other.doubleValue;
            break;
        case Bool:
            boolValue = other.boolValue;
            break;
        case None:
            break;
    }

    other.reset();
}

void AnyType::swap(AnyType &other) noexcept {
    const AnyType temp = *this;

    switch (other.currentType) {
        case Int:
            intValue = other.intValue;
            currentType = Int;
            break;
        case Double:
            doubleValue = other.doubleValue;
            currentType = Double;
            break;
        case Bool:
            boolValue = other.boolValue;
            currentType = Bool;
            break;
        case None:
            intValue = 0;
            currentType = None;
            break;
    }

    switch (temp.currentType) {
        case Int:
            other.intValue = temp.intValue;
            other.currentType = Int;
            break;
        case Double:
            other.doubleValue = temp.doubleValue;
            other.currentType = Double;
            break;
        case Bool:
            other.boolValue = temp.boolValue;
            other.currentType = Bool;
            break;
        case None:
            other.intValue = 0;
            other.currentType = None;
            break;
    }
}

AnyType &AnyType::operator=(int value) {
    intValue = value;
    currentType = Int;
    return *this;
}

AnyType &AnyType::operator=(double value) {
    doubleValue = value;
    currentType = Double;
    return *this;
}

AnyType &AnyType::operator=(bool value) {
    boolValue = value;
    currentType = Bool;
    return *this;
}

std::variant<int, double, bool> AnyType::get() const {
    switch (currentType) {
        case Int:
            return intValue;
        case Double:
            return doubleValue;
        case Bool:
            return boolValue;
        default:
            throw std::runtime_error("No value is set.");
    }
}

int AnyType::getInt() const {
    if (currentType == Int) {
        return intValue;
    }
    throw std::bad_cast();
}

double AnyType::getDouble() const {
    if (currentType == Double) {
        return doubleValue;
    }
    throw std::bad_cast();
}

bool AnyType::getBool() const {
    if (currentType == Bool) {
        return boolValue;
    }
    throw std::bad_cast();
}

void AnyType::reset() {
    intValue = 0;
    currentType = None;
}

// VariadicType

VariadicType::VariadicType(const VariadicType &other) {
    value = other.value;
}

VariadicType::VariadicType(VariadicType &&other) noexcept {
    value = other.value;
    other.reset();
}

void VariadicType::swap(VariadicType &other) noexcept {
    value.swap(other.value);
}

VariadicType &VariadicType::operator=(int val) {
    value = val;
    return *this;
}

VariadicType &VariadicType::operator=(double val) {
    value = val;
    return *this;
}

VariadicType &VariadicType::operator=(bool val) {
    value = val;
    return *this;
}

std::variant<std::monostate, int, double, bool> VariadicType::get() const {
    return value;
}

int VariadicType::getInt() const {
    return std::get<int>(value);
}

double VariadicType::getDouble() const {
    return std::get<double>(value);
}

bool VariadicType::getBool() const {
    return std::get<bool>(value);
}

void VariadicType::reset() {
    value = std::monostate{};
}

void run_task2_union() {
    auto visitor = [](const auto value) {
        std::cout << value;
    };

    try {
        AnyType anyType1 = 1;

        std::printf("anyType1 getInt(): %d\n", anyType1.getInt());

        anyType1 = 2.621515;
        std::printf("anyType1 getDouble(): %f\n", anyType1.getDouble());

        std::printf("anyType1 get(): ");
        std::visit(visitor, anyType1.get());
        std::printf("\n");

        AnyType anyType2 = anyType1;
        std::printf("anyType2 getDouble(): %f\n", anyType1.getDouble());

        anyType1 = 1567;
        anyType2 = true;

        anyType1.swap(anyType2);

        std::printf("anyType1 get(): ");
        std::visit(visitor, anyType1.get());
        std::printf("\n");
        std::printf("anyType2 get(): ");
        std::visit(visitor, anyType2.get());
        std::printf("\n");

        std::printf("anyType1 getInt(): %d\n", anyType1.getInt());
    } catch (std::bad_cast &e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

std::ostream &operator<<(std::ostream &os, const std::monostate &) {
    return os << "not set";
}

void run_task2_variadic() {
    auto visitor = [](const auto value) {
        std::cout << value;
    };

    try {
        VariadicType variadicType1 = 1;

        std::printf("variadicType1 getInt(): %d\n", variadicType1.getInt());

        variadicType1 = 2.621515;
        std::printf("variadicType1 getDouble(): %f\n", variadicType1.getDouble());

        std::printf("variadicType1 get(): ");
        std::visit(visitor, variadicType1.get());
        std::printf("\n");

        VariadicType variadicType2 = variadicType1;
        std::printf("variadicType2 getDouble(): %f\n", variadicType1.getDouble());

        variadicType1 = 1567;
        variadicType2 = true;

        variadicType1.swap(variadicType2);

        std::printf("variadicType1 get(): ");
        std::visit(visitor, variadicType1.get());
        std::printf("\n");
        std::printf("variadicType2 get(): ");
        std::visit(visitor, variadicType2.get());
        std::printf("\n");

        variadicType1.reset();
        std::printf("variadicType2 get(): ");
        std::visit(visitor, variadicType1.get());
        std::printf("\n");
        std::printf("variadicType1 getDouble(): %f\n", variadicType1.getDouble());
    } catch (const std::bad_variant_access &e) {
        std::cerr << e.what() << std::endl;
    }
}
