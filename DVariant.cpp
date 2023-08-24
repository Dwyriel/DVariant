#include "DVariant.h"
#include <cstring>

const size_t defaultSize = 9;

DVariant::DVariant() noexcept: m_type(Type::String) {
    m_size = defaultSize;
    m_data = calloc(m_size, 1);
}

DVariant::DVariant(void *value, size_t size) noexcept: m_type(Type::Object) {
    m_size = size > defaultSize ? size : defaultSize;
    m_data = malloc(m_size);
    memcpy(m_data, value, size);
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

DVariant::DVariant(int64_t value) noexcept: m_type(Type::Integer) {
    m_size = defaultSize;
    m_data = calloc(m_size, 1);
    memcpy(m_data, &value, sizeof(value));
}

DVariant::DVariant(int32_t value) noexcept: m_type(Type::Integer) {
    m_size = defaultSize;
    m_data = calloc(m_size, 1);
    memcpy(m_data, &value, sizeof(value));
}

DVariant::DVariant(bool value) noexcept: m_type(Type::Boolean) {
    m_size = defaultSize;
    m_data = calloc(m_size, 1);
    memcpy(m_data, &value, sizeof(value));
}

DVariant::DVariant(const DVariant &dVariant) noexcept {
    m_type = dVariant.m_type;
    m_size = m_type == Type::String ? dVariant.m_size : defaultSize;
    m_data = malloc(m_size);
    memcpy(m_data, dVariant.m_data, m_size);//if not string/object, 9th byte should be set to 0 at this point per constructor/operator= behavior.
}

DVariant::DVariant(DVariant &&dVariant) noexcept {
    m_type = dVariant.m_type;
    m_size = dVariant.m_size;
    m_data = dVariant.m_data;
    dVariant.m_data = nullptr;
}

DVariant::~DVariant() {
    free(m_data);
}

inline void DVariant::modifyData(const void *from, size_t size, DVariant::Type type) {
    memset(m_data, 0, defaultSize);
    memcpy(m_data, from, size);
    m_type = type;
}

void DVariant::CustomObject(void *value, size_t size) noexcept {
    if (size > m_size) {
        m_data = realloc(m_data, size);
        m_size = size;
    }
    memcpy(m_data, value, size);
    m_type = Type::Object;
}

void *DVariant::AsCustom() const noexcept {
    return m_data;
}

const char *DVariant::AsCString() const noexcept {
    return (char *) m_data;
}

std::string DVariant::AsString() const noexcept {
    std::string str = (const char *) m_data;
    return str;
}

double DVariant::AsDouble() const noexcept {
    return *((double *) m_data);
}

int64_t DVariant::AsInteger() const noexcept {
    return *((int64_t *) m_data);
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

DVariant &DVariant::operator=(int64_t value) noexcept {
    modifyData(&value, sizeof(value), Type::Integer);
    return *this;
}

DVariant &DVariant::operator=(int32_t value) noexcept {
    modifyData(&value, sizeof(value), Type::Integer);
    return *this;
}

DVariant &DVariant::operator=(bool value) noexcept {
    modifyData(&value, sizeof(value), Type::Boolean);
    return *this;
}

DVariant &DVariant::operator=(const DVariant &dVariant) noexcept {
    if (this == &dVariant)
        return *this;
    if (dVariant.m_type == Type::String && dVariant.m_size > m_size) {
        m_data = realloc(m_data, dVariant.m_size);
        m_size = dVariant.m_size;
    }
    memcpy(m_data, dVariant.m_data, dVariant.m_size);//check copy constructor
    m_type = dVariant.m_type;
    return *this;
}

DVariant &DVariant::operator=(DVariant &&dVariant) noexcept {
    free(m_data);
    m_type = dVariant.m_type;
    m_size = dVariant.m_size;
    m_data = dVariant.m_data;
    dVariant.m_data = nullptr;
    return *this;
}
