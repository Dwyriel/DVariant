#include "DVariant.h"

DVariant::DVariant() noexcept: type(Type::String) {}

DVariant::DVariant(std::string value) noexcept: valueAsString(std::move(value)), type(Type::String) {}

DVariant::DVariant(const char *value) noexcept: valueAsString(value), type(Type::String) {}

DVariant::DVariant(double value) noexcept: valueAsString(std::move(std::to_string(value))), type(Type::Double) {}

DVariant::DVariant(long long value) noexcept: valueAsString(std::move(std::to_string(value))), type(Type::Integer) {}

DVariant::DVariant(int value) noexcept: valueAsString(std::move(std::to_string(value))), type(Type::Integer) {}

DVariant::DVariant(bool value) noexcept: valueAsString(std::move(std::to_string(value))), type(Type::Boolean) {}

std::string &DVariant::AsString() noexcept {
    return valueAsString;
}

double DVariant::AsDouble() noexcept {
    return strtod(valueAsString.c_str(), nullptr);
}

long long DVariant::AsInteger() noexcept {
    return strtoll(valueAsString.c_str(), nullptr, 10);
}

bool DVariant::AsBool() noexcept {
    return strtol(valueAsString.c_str(), nullptr, 10);
}

DVariant::Type DVariant::GetType() {
    return type;
}

DVariant &DVariant::operator=(std::string value) noexcept {
    valueAsString = std::move(value);
    type = Type::String;
    return *this;
}

DVariant &DVariant::operator=(const char *value) noexcept {
    valueAsString = value;
    type = Type::String;
    return *this;
}

DVariant &DVariant::operator=(double value) noexcept {
    valueAsString = std::move(std::to_string(value));
    type = Type::Double;
    return *this;
}

DVariant &DVariant::operator=(long long value) noexcept {
    valueAsString = std::move(std::to_string(value));
    type = Type::Integer;
    return *this;
}

DVariant &DVariant::operator=(int value) noexcept {
    valueAsString = std::move(std::to_string(value));
    type = Type::Integer;
    return *this;
}

DVariant &DVariant::operator=(bool value) noexcept {
    valueAsString = std::move(std::to_string(value));
    type = Type::Boolean;
    return *this;
}
