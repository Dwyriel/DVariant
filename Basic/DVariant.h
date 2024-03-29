#ifndef DVARIANTBASIC_H
#define DVARIANTBASIC_H

#include <string>
#include <cstring>

class DVariant {
    enum class Type : u_int8_t {
        CObject, String, FloatingPoint, Integer, Boolean
    };

    static const size_t defaultSize = 9;

    Type m_type;
    void *m_data;
    size_t m_size;

    inline void modifyData(const void *from, size_t size, DVariant::Type type) {
        memset(m_data, 0, defaultSize);
        memcpy(m_data, from, size);
        m_type = type;
    }

public:
    using Type = Type;

    DVariant() noexcept: m_type(Type::CObject) {
        m_size = defaultSize;
        m_data = calloc(m_size, 1);
    }

    /**
     * @warning only performs a shallow copy, do not use for complex objects.
     */
    DVariant(void *value, size_t size) noexcept: m_type(Type::CObject) {
        m_size = size > defaultSize ? size : defaultSize;
        m_data = malloc(m_size);
        memcpy(m_data, value, size);
    }

    DVariant(const char *value) noexcept: m_type(Type::String) {
        auto size = strlen(value) + 1;
        m_size = size > defaultSize ? size : defaultSize;
        m_data = calloc(m_size, 1);
        memcpy(m_data, value, m_size);
    }

    DVariant(const std::string &value) noexcept: m_type(Type::String) {
        auto size = value.size() + 1;
        m_size = size > defaultSize ? size : defaultSize;
        m_data = calloc(m_size, 1);
        memcpy(m_data, value.c_str(), size);
    }

    DVariant(double value) noexcept: m_type(Type::FloatingPoint) {
        m_size = defaultSize;
        m_data = calloc(m_size, 1);
        memcpy(m_data, &value, sizeof(value));
    }

    DVariant(int64_t value) noexcept: m_type(Type::Integer) {
        m_size = defaultSize;
        m_data = calloc(m_size, 1);
        memcpy(m_data, &value, sizeof(value));
    }

    DVariant(int32_t value) noexcept: m_type(Type::Integer) {
        m_size = defaultSize;
        m_data = calloc(m_size, 1);
        memcpy(m_data, &value, sizeof(value));
    }

    DVariant(bool value) noexcept: m_type(Type::Boolean) {
        m_size = defaultSize;
        m_data = calloc(m_size, 1);
        memcpy(m_data, &value, sizeof(value));
    }

    DVariant(const DVariant &dVariant) noexcept {
        m_type = dVariant.m_type;
        m_size = dVariant.m_size;
        m_data = malloc(m_size);
        memcpy(m_data, dVariant.m_data, m_size);
    }

    DVariant(DVariant &&dVariant) noexcept {
        m_type = dVariant.m_type;
        m_size = dVariant.m_size;
        m_data = dVariant.m_data;
        dVariant.m_data = nullptr;
    }

    ~DVariant() {
        free(m_data);
    }

    /**
     * @warning only performs a shallow copy, do not use for complex objects.
     */
    void SetObject(void *value, size_t size) noexcept {
        if (size > m_size) {
            m_data = realloc(m_data, size);
            m_size = size;
        }
        memcpy(m_data, value, size);
        m_type = Type::CObject;
    }

    template<class T>
    T &AsObject() {
        return *(T *) m_data;
    }

    void *AsCustom() const noexcept {
        return m_data;
    }

    const char *AsCString() const noexcept {
        return (char *) m_data;
    }

    std::string AsString() const noexcept {
        std::string str = (const char *) m_data;
        return str;
    }

    double AsDouble() const noexcept {
        return *((double *) m_data);
    }

    int64_t AsInteger() const noexcept {
        return *((int64_t *) m_data);
    }

    bool AsBool() const noexcept {
        return *((bool *) m_data);
    }

    Type GetType() const {
        return m_type;
    }

    DVariant &operator=(const char *value) noexcept {
        size_t strSize = strlen(value) + 1;
        if (strSize > m_size) {
            m_data = realloc(m_data, strSize);
            m_size = strSize;
        }
        memcpy(m_data, value, strSize);
        m_type = Type::String;
        return *this;
    }

    DVariant &operator=(const std::string &value) noexcept {
        operator=(value.c_str());
        return *this;
    }

    DVariant &operator=(double value) noexcept {
        modifyData(&value, sizeof(value), Type::FloatingPoint);
        return *this;
    }

    DVariant &operator=(int64_t value) noexcept {
        modifyData(&value, sizeof(value), Type::Integer);
        return *this;
    }

    DVariant &operator=(int32_t value) noexcept {
        modifyData(&value, sizeof(value), Type::Integer);
        return *this;
    }

    DVariant &operator=(bool value) noexcept {
        modifyData(&value, sizeof(value), Type::Boolean);
        return *this;
    }

    DVariant &operator=(const DVariant &dVariant) noexcept {
        if (this == &dVariant)
            return *this;
        if (dVariant.m_size > m_size) {
            m_data = realloc(m_data, dVariant.m_size);
            m_size = dVariant.m_size;
        }
        memcpy(m_data, dVariant.m_data, dVariant.m_size);
        m_type = dVariant.m_type;
        return *this;
    }

    DVariant &operator=(DVariant &&dVariant) noexcept {
        free(m_data);
        m_type = dVariant.m_type;
        m_size = dVariant.m_size;
        m_data = dVariant.m_data;
        dVariant.m_data = nullptr;
        return *this;
    }
};

#endif //DVARIANTBASIC_H
