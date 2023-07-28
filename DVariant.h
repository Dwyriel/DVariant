#ifndef DWYVARIANT_H
#define DWYVARIANT_H

#include <string>

class DVariant {
    enum class Type {
        String, FloatingPoint, Integer, Boolean
    };

    Type m_type;
    void *m_data;
    size_t m_size;

    void modifyData(void *from, size_t size, Type type);

public:
    using Type = Type;

    DVariant() noexcept;

    DVariant(std::string value) noexcept;

    DVariant(const char *value) noexcept;

    DVariant(double value) noexcept;

    DVariant(long long value) noexcept;

    DVariant(int value) noexcept;

    DVariant(bool value) noexcept;

    std::string AsString() noexcept;

    double AsDouble() noexcept;

    long long AsInteger() noexcept;

    bool AsBool() noexcept;

    Type GetType();

    DVariant &operator=(const char *value) noexcept;

    DVariant &operator=(const std::string &value) noexcept;

    DVariant &operator=(double value) noexcept;

    DVariant &operator=(long long value) noexcept;

    DVariant &operator=(int value) noexcept;

    DVariant &operator=(bool value) noexcept;
};

#endif //DWYVARIANT_H
