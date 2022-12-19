#include "DVariant.h"

DVariant::DVariant() noexcept: type(Type::String) {}

DVariant::DVariant(std::string value) noexcept: valueAsString(std::move(value)), type{Type::String} {
}

DVariant::DVariant(double value) noexcept: valueAsString(std::move(std::to_string(value))), type{Type::Double} {
}

DVariant::DVariant(long long value) noexcept: valueAsString(std::move(std::to_string(value))), type{Type::LongLong} {
}

DVariant::DVariant(int value) noexcept: valueAsString(std::move(std::to_string(value))), type{Type::Integer} {
}

DVariant::DVariant(bool value) noexcept: valueAsString(std::move(std::to_string(value))), type{Type::Integer} {
}

const std::string &DVariant::GetString() noexcept {
    return valueAsString;
}

double DVariant::GetDouble() noexcept {
    if (type == Type::String)
        return 0;
    return std::stod(valueAsString);
}

long long DVariant::GetInteger() noexcept {
    if (type == Type::String)
        return 0;
    return std::stoll(valueAsString);
}

bool DVariant::GetBool() noexcept {
    return GetInteger();
}

DVariant &DVariant::operator=(std::string value) noexcept {
    valueAsString = std::move(value);
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
    type = Type::LongLong;
    return *this;
}

DVariant &DVariant::operator=(int value) noexcept {
    valueAsString = std::move(std::to_string(value));
    type = Type::Integer;
    return *this;
}
