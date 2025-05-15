#ifndef WEEKDAY_H
#define WEEKDAY_H

#include <Qt>
#include <functional>

// Giorni della settimana
enum class Weekday {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

// Specializza std::less per Weekday
namespace std {
template<>
struct less<Weekday> {
    bool operator()(const Weekday& a, const Weekday& b) const {
        return static_cast<int>(a) < static_cast<int>(b);
    }
};
}

// Converte da Weekday nostro a Qt::DayOfWeek
inline Qt::DayOfWeek toQt(Weekday d) {
    return static_cast<Qt::DayOfWeek>(static_cast<int>(d) + 1);
}

// Converte da Qt::DayOfWeek a Weekday nostro
inline Weekday fromQt(Qt::DayOfWeek d) {
    return static_cast<Weekday>(static_cast<int>(d) - 1);
}

#endif // WEEKDAY_H
