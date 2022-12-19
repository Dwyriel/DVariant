#ifndef EXECS_DWYVARIANT_H
#define EXECS_DWYVARIANT_H

#include <string>

class DVariant{
    std::string valueAsString;

public:
    DVariant();
    explicit DVariant(std::string value);
    explicit DVariant(double value);
    explicit DVariant(long long value);
    explicit DVariant(bool value);

    std::string GetString();
    double GetDouble();
    long long GetInteger();
    bool GetBool();

    DVariant& operator=(std::string value);
    DVariant& operator=(double value);
    DVariant& operator=(long long value);
    DVariant& operator=(bool value);
};

#endif //EXECS_DWYVARIANT_H
