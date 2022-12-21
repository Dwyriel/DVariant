#ifndef DWYVARIANT_H
#define DWYVARIANT_H

#include <string>

class DVariant {
    std::string valueAsString;

public:
    DVariant() noexcept;

    DVariant(std::string value) noexcept;

    DVariant(const char *value) noexcept;

    DVariant(double value) noexcept;

    DVariant(long long value) noexcept;

    DVariant(int value) noexcept;

    std::string &GetString() noexcept;

    double GetDouble() noexcept;

    long long GetInteger() noexcept;

    bool GetBool() noexcept;

    DVariant &operator=(std::string value) noexcept;

    DVariant &operator=(const char *value) noexcept;

    DVariant &operator=(double value) noexcept;

    DVariant &operator=(long long value) noexcept;

    DVariant &operator=(int value) noexcept;
};

#endif //DWYVARIANT_H
