#include "DVariant.h"

DVariant::DVariant() noexcept {}

DVariant::DVariant(std::string value) noexcept: valueAsString(std::move(value)) {}

DVariant::DVariant(const char *value) noexcept: valueAsString(value) {}

DVariant::DVariant(double value) noexcept: valueAsString(std::move(std::to_string(value))) {}

DVariant::DVariant(long long value) noexcept: valueAsString(std::move(std::to_string(value))) {}

DVariant::DVariant(int value) noexcept: valueAsString(std::move(std::to_string(value))) {}

std::string &DVariant::GetString() noexcept {
    return valueAsString;
}

double DVariant::GetDouble() noexcept {
    return strtod(valueAsString.c_str(), nullptr);
}

long long DVariant::GetInteger() noexcept {
    return strtoll(valueAsString.c_str(), nullptr, 10);
}

bool DVariant::GetBool() noexcept {
    return strtol(valueAsString.c_str(), nullptr, 10);
}

DVariant &DVariant::operator=(std::string value) noexcept {
    valueAsString = std::move(value);
    return *this;
}

DVariant &DVariant::operator=(const char *value) noexcept {
    valueAsString = value;
    return *this;
}

DVariant &DVariant::operator=(double value) noexcept {
    valueAsString = std::move(std::to_string(value));
    return *this;
}

DVariant &DVariant::operator=(long long value) noexcept {
    valueAsString = std::move(std::to_string(value));
    return *this;
}

DVariant &DVariant::operator=(int value) noexcept {
    valueAsString = std::move(std::to_string(value));
    return *this;
}
