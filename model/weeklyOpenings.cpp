#include "weeklyOpenings.h"
#include "weekday.h"
void weeklyOpenings::setOpening(Weekday day, const QTime& open, const QTime& close){
    if(open>=close)
        throw std::invalid_argument("open>=close"); //Lancia eccezione per orari non validi
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

    return "ERROR"; // fallback di errore grave
}

QString weeklyOpenings::toQStringMultiline() const {
    QStringList result;

    QList<Weekday> days = {
        Weekday::Monday, Weekday::Tuesday, Weekday::Wednesday,
        Weekday::Thursday, Weekday::Friday, Weekday::Saturday, Weekday::Sunday
    };

    for (const Weekday& day : days) {
        QString dayStr = weekdayToString(day).left(3); // es. "Mon"
        const openingFrames& frame = schedule.value(day, openingFrames());

        if (frame.closed) {
            result << QString("%1: Closed").arg(dayStr);
        } else if (frame.opening == QTime(0, 0) && frame.closing == QTime(23, 59)) {
            result << QString("%1: Always open").arg(dayStr);
        } else {
            result << QString("%1: from %2 to %3")
            .arg(dayStr)
                .arg(frame.opening.toString("HH:mm"))
                .arg(frame.closing.toString("HH:mm"));
        }
    }

    return result.join("\n");
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
bool weeklyOpenings::isClosed(Weekday day) const
{
    return getOpening(day).closed;
}

bool weeklyOpenings::isAlwaysOpen(Weekday day) const
{
    const auto f = getOpening(day);
    // considera “sempre aperto” se 00:00-23:59 e non è marcato closed
    return !f.closed && f.opening == QTime(0,0) && f.closing == QTime(23,59);
}

QTime weeklyOpenings::openTime(Weekday day) const
{
    return getOpening(day).opening;
}

QTime weeklyOpenings::closeTime(Weekday day) const
{
    return getOpening(day).closing;
}
