#ifndef EXECS_DWYVARIANT_H
#define EXECS_DWYVARIANT_H

#include <string>

class DVariant {
    enum class Type {
        String, Double, LongLong, Integer
    };

    std::string valueAsString;
    Type type;

public:
    DVariant() noexcept;

    explicit DVariant(std::string value) noexcept;

    explicit DVariant(double value) noexcept;

    explicit DVariant(long long value) noexcept;

    explicit DVariant(int value) noexcept;

    explicit DVariant(bool value) noexcept;

    const std::string &GetString() noexcept;

    double GetDouble() noexcept;

    long long GetInteger() noexcept;

    bool GetBool() noexcept;

    DVariant &operator=(std::string value) noexcept;

    DVariant &operator=(double value) noexcept;

    DVariant &operator=(long long value) noexcept;

    DVariant &operator=(int value) noexcept;
};

#endif //EXECS_DWYVARIANT_H
