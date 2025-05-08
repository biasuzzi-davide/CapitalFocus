#ifndef WEEKDAY_H
#define WEEKDAY_H
#include <Qt>
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
inline Qt::DayOfWeek toQt(Weekday d) {
    // Qt::Monday == 1, noi abbiamo Monday==0, ecc.
    return static_cast<Qt::DayOfWeek>(static_cast<int>(d) + 1);
}
inline Weekday fromQt(Qt::DayOfWeek d) {
    return static_cast<Weekday>(static_cast<int>(d) - 1);
}
#endif // WEEKDAY_H

