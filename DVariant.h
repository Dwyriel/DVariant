#ifndef DVARIANT_H
#define DVARIANT_H

#include <string>

class DVariant {
    enum class Type {
        String, FloatingPoint, Integer, Boolean
    };

    Type m_type;
    void *m_data;
    size_t m_size;

    void modifyData(const void *from, size_t size, DVariant::Type type);

public:
    using Type = Type;

    DVariant() noexcept;

    DVariant(const char *value) noexcept;

    DVariant(const std::string &value) noexcept;

    DVariant(double value) noexcept;

    DVariant(long long value) noexcept;

    DVariant(int value) noexcept;

    DVariant(bool value) noexcept;

    DVariant(const DVariant &dVariant);

    ~DVariant();

    std::string AsString() const noexcept;

    double AsDouble() const noexcept;

    long long AsInteger() const noexcept;

    bool AsBool() const noexcept;

    Type GetType() const;

    DVariant &operator=(const char *value) noexcept;

    DVariant &operator=(const std::string &value) noexcept;

    DVariant &operator=(double value) noexcept;

    DVariant &operator=(long long value) noexcept;

    DVariant &operator=(int value) noexcept;

    DVariant &operator=(bool value) noexcept;
};

#endif //DVARIANT_H
