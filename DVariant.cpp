#include "DVariant.h"
#include <cstring>

const size_t defaultSize = 9;

DVariant::DVariant() noexcept: m_type(Type::String) {
    m_size = defaultSize;
    m_data = calloc(m_size, 1);
}

DVariant::DVariant(const char *value) noexcept: m_type(Type::String) {
    m_size = strlen(value) + 1;
    m_data = malloc(m_size);
    memcpy(m_data, value, m_size);
}

DVariant::DVariant(const std::string &value) noexcept: m_type(Type::String) {
    m_size = value.size() + 1;
    m_data = malloc(m_size);
    memcpy(m_data, value.c_str(), m_size);
}

DVariant::DVariant(double value) noexcept: m_type(Type::FloatingPoint) {
    m_size = defaultSize;
    m_data = calloc(m_size, 1);
    memcpy(m_data, &value, sizeof(value));
}

DVariant::DVariant(long long int value) noexcept: m_type(Type::Integer) {
    m_size = defaultSize;
    m_data = calloc(m_size, 1);
    memcpy(m_data, &value, sizeof(value));
}

DVariant::DVariant(int value) noexcept: m_type(Type::Integer) {
    m_size = defaultSize;
    m_data = calloc(m_size, 1);
    memcpy(m_data, &value, sizeof(value));
}

DVariant::DVariant(bool value) noexcept: m_type(Type::Boolean) {
    m_size = defaultSize;
    m_data = calloc(m_size, 1);
    memcpy(m_data, &value, sizeof(value));
}

DVariant::~DVariant() {
    free(m_data);
}

void DVariant::modifyData(const void *from, size_t size, DVariant::Type type) {
    memset(m_data, 0, defaultSize);
    memcpy(m_data, from, size);
    m_type = type;
}

std::string DVariant::AsString() const noexcept {
    std::string str = (const char *) m_data;
    return str;
}

double DVariant::AsDouble() const noexcept {
    return *((double *) m_data);
}

long long DVariant::AsInteger() const noexcept {
    return *((long long *) m_data);
}

bool DVariant::AsBool() const noexcept {
    return *((bool *) m_data);
}

DVariant::Type DVariant::GetType() const {
    return m_type;
}

DVariant &DVariant::operator=(const char *value) noexcept {
    size_t strSize = strlen(value) + 1;
    if (strSize > m_size) {
        m_data = realloc(m_data, strSize);
        m_size = strSize;
    }
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
