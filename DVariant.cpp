#include "DVariant.h"
#include <cstring>

DVariant::DVariant() noexcept: m_type(Type::String) {
    m_size = 9;
    m_data = calloc(m_size, 1);
}

void DVariant::modifyData(void *from, size_t size, DVariant::Type type) {
    memcpy(m_data, from, size);
    m_type = type;
}

std::string DVariant::AsString() noexcept {
    std::string str = (const char *) m_data;
    return str;
}

double DVariant::AsDouble() noexcept {
    return *((double *) m_data);
}

long long DVariant::AsInteger() noexcept {
    return *((long long *) m_data);
}

bool DVariant::AsBool() noexcept {
    return *((bool *) m_data);
}

DVariant::Type DVariant::GetType() {
    return m_type;
}

DVariant &DVariant::operator=(const char *value) noexcept {
    size_t strSize = strlen(value) + 1;
    if (strSize > m_size)
        m_data = realloc(m_data, strSize);
    memcpy(m_data, value, strSize);
    m_type = Type::String;
    return *this;
}

DVariant &DVariant::operator=(const std::string &value) noexcept {
    operator=(value.c_str());
    return *this;
}

DVariant &DVariant::operator=(double value) noexcept {
    modifyData(&value, sizeof(value), Type::FloatingPoint);
    return *this;
}

DVariant &DVariant::operator=(long long int value) noexcept {
    modifyData(&value, sizeof(value), Type::Integer);
    return *this;
}

DVariant &DVariant::operator=(int value) noexcept {
    modifyData(&value, sizeof(value), Type::Integer);
    return *this;
}

DVariant &DVariant::operator=(bool value) noexcept {
    modifyData(&value, sizeof(value), Type::Boolean);
    return *this;
}
