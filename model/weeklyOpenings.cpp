#include "weeklyOpenings.h"
#include "weekday.h"
void weeklyOpenings::setOpening(Weekday day, const QTime& open, const QTime& close){
    schedule[day]= openingFrames(open,close);
}

void weeklyOpenings::setClosed(Weekday day){
    schedule[day] = openingFrames();
}

openingFrames weeklyOpenings::getOpening(Weekday day) const{
    return schedule.value(day, openingFrames());
}

bool weeklyOpenings::opensBefore(Weekday day, const QTime& time) const{
    if (!schedule.contains(day)) return false;
    return !schedule[day].closed && schedule[day].opening<time;
}

bool weeklyOpenings::isOpenAt(Weekday day, const QTime& time) const{
    if(!schedule.contains(day)) return false;
    return !schedule[day].closed && (schedule[day].opening<=time && schedule[day].closing>=time);
}

QString weeklyOpenings::getOpeningFrameString(Weekday day) const{
    if(!schedule.contains(day) || schedule[day].closed) return "Closed";
    else return QString("%1 - %2").arg(schedule[day].opening.toString("hh:mm"), schedule[day].closing.toString("hh:mm"));
}

const QMap<Weekday, openingFrames>& weeklyOpenings::getSchedule() const {
    return schedule;
}

weeklyOpenings::weeklyOpenings(const weeklyOpenings& other)
    : schedule(other.schedule) {}
weeklyOpenings::weeklyOpenings() = default;

QString weeklyOpenings::weekdayToString(const Weekday day) {
    switch (day) {
    case Weekday::Monday:    return "Monday";
    case Weekday::Tuesday:   return "Tuesday";
    case Weekday::Wednesday: return "Wednesday";
    case Weekday::Thursday:  return "Thursday";
    case Weekday::Friday:    return "Friday";
    case Weekday::Saturday:  return "Saturday";
    case Weekday::Sunday:    return "Sunday";
    }

    return "ERROR"; // fallback
}

Weekday weeklyOpenings::weekdayFromString(const QString& dayStr) {
    if (dayStr == "Monday") return Weekday::Monday;
    else if (dayStr == "Tuesday") return Weekday::Tuesday;
    else if (dayStr == "Wednesday") return Weekday::Wednesday;
    else if (dayStr == "Thursday") return Weekday::Thursday;
    else if (dayStr == "Friday") return Weekday::Friday;
    else if (dayStr == "Saturday") return Weekday::Saturday;
    else if (dayStr == "Sunday") return Weekday::Sunday;

    // fallback
    qWarning() << "weekdayFromString: error:" << dayStr;
    return Weekday::Monday;
}
