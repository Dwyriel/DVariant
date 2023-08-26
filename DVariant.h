#ifndef DVARIANT_H
#define DVARIANT_H

#include <string>
#include <cstring>

class DVariant {
    enum class Type : u_int8_t {
        CObject, String, FloatingPoint, Integer, Boolean, Object
    };

    static const size_t defaultSize = 9;

    Type m_type;
    void *m_data;
    size_t m_size;

    void (*m_objDestructor)(void *) = nullptr;

    void (*m_objCopy)(void *, void *) = nullptr;


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

    template<class T>
    DVariant(const T &value) noexcept: m_type(Type::Object) {
        m_objDestructor = [](void *ptr) {
            ((T *) ptr)->~T();
        };
        m_objCopy = [](void *dest, void *origin) {
            new(dest) T(*((T *) origin));
        };
        auto size = sizeof(T);
        m_size = size > defaultSize ? size : defaultSize;
        m_data = malloc(m_size);
        new(m_data) T(value);
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
        if (m_type == Type::Object) {
            m_objDestructor = dVariant.m_objDestructor;
            m_objCopy = dVariant.m_objCopy;
            m_objCopy(m_data, dVariant.m_data);
        } else
            memcpy(m_data, dVariant.m_data, m_size);
    }

    DVariant(DVariant &&dVariant) noexcept {
        m_type = dVariant.m_type;
        m_size = dVariant.m_size;
        m_data = dVariant.m_data;
        m_objDestructor = dVariant.m_objDestructor;
        m_objCopy = dVariant.m_objCopy;
        dVariant.m_data = nullptr;
    }

    ~DVariant() {
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        free(m_data);
    }

    template<class T>
    void SetObject(const T &value) {
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        m_objDestructor = [](void *ptr) {
            ((T *) ptr)->~T();
        };
        m_objCopy = [](void *dest, void *origin) {
            new(dest) T(*((T *) origin));
        };
        auto size = sizeof(T);
        if (size > m_size) {
            m_data = realloc(m_data, size);
            m_size = size;
        }
        new(m_data) T(value);
        m_type = Type::Object;
    }

    /**
     * @warning only performs a shallow copy, do not use for complex objects.
     */
    void SetObject(void *value, size_t size) noexcept {
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        if (size > m_size) {
            m_data = realloc(m_data, size);
            m_size = size;
        }
        memcpy(m_data, value, size);
        m_type = Type::CObject;
    }

    template<class T>
    T AsObject() {
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

    template<class T>
    DVariant &operator=(const T &value) {
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        m_objDestructor = [](void *ptr) {
            ((T *) ptr)->~T();
        };
        m_objCopy = [](void *dest, void *origin) {
            new(dest) T(*((T *) origin));
        };
        auto size = sizeof(T);
        if (size > m_size) {
            m_data = realloc(m_data, size);
            m_size = size;
        }
        new(m_data) T(value);
        m_type = Type::Object;
        return *this;
    }

    DVariant &operator=(const char *value) noexcept {
        if (m_type == Type::Object)
            m_objDestructor(m_data);
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
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        operator=(value.c_str());
        return *this;
    }

    DVariant &operator=(double value) noexcept {
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        modifyData(&value, sizeof(value), Type::FloatingPoint);
        return *this;
    }

    DVariant &operator=(int64_t value) noexcept {
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        modifyData(&value, sizeof(value), Type::Integer);
        return *this;
    }

    DVariant &operator=(int32_t value) noexcept {
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        modifyData(&value, sizeof(value), Type::Integer);
        return *this;
    }

    DVariant &operator=(bool value) noexcept {
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        modifyData(&value, sizeof(value), Type::Boolean);
        return *this;
    }

    DVariant &operator=(const DVariant &dVariant) noexcept {
        if (this == &dVariant)
            return *this;
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        if (dVariant.m_size > m_size) {
            m_data = realloc(m_data, dVariant.m_size);
            m_size = dVariant.m_size;
        }
        if (dVariant.m_type == Type::Object) {
            m_objDestructor = dVariant.m_objDestructor;
            m_objCopy = dVariant.m_objCopy;
            m_objCopy(m_data, dVariant.m_data);
        } else
            memcpy(m_data, dVariant.m_data, dVariant.m_size);
        m_type = dVariant.m_type;
        return *this;
    }

    DVariant &operator=(DVariant &&dVariant) noexcept {
        if (m_type == Type::Object)
            m_objDestructor(m_data);
        free(m_data);
        m_type = dVariant.m_type;
        m_size = dVariant.m_size;
        m_data = dVariant.m_data;
        m_objDestructor = dVariant.m_objDestructor;
        m_objCopy = dVariant.m_objCopy;
        dVariant.m_data = nullptr;
        return *this;
    }
};

#endif //DVARIANT_H
