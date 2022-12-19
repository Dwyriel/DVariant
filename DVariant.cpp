#include "DVariant.h"

DVariant::DVariant() {}

DVariant::DVariant(std::string value) : valueAsString(std::move(value)) {}

DVariant::DVariant(double value) : valueAsString(std::move(std::to_string(value))){}

DVariant::DVariant(long long value) : valueAsString(std::move(std::to_string(value))){}

DVariant::DVariant(bool value) : valueAsString(std::move(std::to_string(value))){}

std::string DVariant::GetString() {
    return valueAsString;
}

double DVariant::GetDouble() {
    return std::stod(valueAsString);
}

long long DVariant::GetInteger() {
    return std::stoll(valueAsString);
}

bool DVariant::GetBool() {
    return std::stoi(valueAsString);
}

DVariant& DVariant::operator=(std::string value) {
    valueAsString = std::move(value);
    return *this;
}

DVariant& DVariant::operator=(double value) {
    valueAsString = std::move(std::to_string(value));
    return *this;
}

DVariant& DVariant::operator=(long long value) {
    valueAsString = std::move(std::to_string(value));
    return *this;
}

DVariant& DVariant::operator=(bool value) {
    valueAsString = std::move(std::to_string(value));
    return *this;
}
