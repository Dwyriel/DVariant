#ifndef DVARIANT_H
#define DVARIANT_H

#include <string>

class DVariant {
    enum class Type : u_int8_t {
        Object, String, FloatingPoint, Integer, Boolean
    };

    Type m_type;
    void *m_data;
    size_t m_size;

    void modifyData(const void *from, size_t size, DVariant::Type type);

public:
    using Type = Type;

    DVariant() noexcept;

    DVariant(void *value, size_t size) noexcept;

    DVariant(const char *value) noexcept;

    DVariant(const std::string &value) noexcept;

    DVariant(double value) noexcept;

    DVariant(int64_t value) noexcept;

    DVariant(int32_t value) noexcept;

    DVariant(bool value) noexcept;

    DVariant(const DVariant &dVariant) noexcept;

    DVariant(DVariant &&dVariant) noexcept;

    ~DVariant();

    void CustomObject(void *value, size_t size) noexcept;

    void *AsCustom() const noexcept;

    const char *AsCString() const noexcept;

    std::string AsString() const noexcept;

    double AsDouble() const noexcept;

    int64_t AsInteger() const noexcept;

    bool AsBool() const noexcept;

    Type GetType() const;

    DVariant &operator=(const char *value) noexcept;

    DVariant &operator=(const std::string &value) noexcept;

    DVariant &operator=(double value) noexcept;

    DVariant &operator=(int64_t value) noexcept;

    DVariant &operator=(int32_t value) noexcept;

    DVariant &operator=(bool value) noexcept;

    DVariant &operator=(const DVariant &dVariant) noexcept;

    DVariant &operator=(DVariant &&dVariant) noexcept;
};

#endif //DVARIANT_H
