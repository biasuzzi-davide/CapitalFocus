#include "weeklyOpenings.h"
#include "weekday.h"
void weeklyOpenings::setOpening(Weekday day, const QTime& open, const QTime& close){
    schedule[day]= openingFrames(open,close);
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
