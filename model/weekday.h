#ifndef WEEKDAY_H
#define WEEKDAY_H

enum class Weekday {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

#include <functional> // per std::less, specializzo std::less per il mio tipo weekday ed evito ambiguità

namespace std {
template<>
struct less<Weekday> {
    bool operator()(const Weekday& a, const Weekday& b) const {
        return static_cast<int>(a) < static_cast<int>(b);
    }
};
}

#endif // WEEKDAY_H

