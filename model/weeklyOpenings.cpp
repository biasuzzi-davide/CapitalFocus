#include "weeklyOpenings.h"
#include <QDebug>

// Costruttore di default
weeklyOpenings::weeklyOpenings() = default;

// Costruttore di copia
weeklyOpenings::weeklyOpenings(const weeklyOpenings& other)
    : schedule(other.schedule) {}

// Imposta orario per un giorno
void weeklyOpenings::setOpening(Weekday day, const QTime& open, const QTime& close){
    schedule[day]= openingFrames(open,close);
}

// Imposta un giorno come chiuso
void weeklyOpenings::setClosed(Weekday day){
    schedule[day] = openingFrames(); // openingFrames() di default imposta closed = true
}

// Imposta un giorno come sempre aperto
void weeklyOpenings::setAlwaysOpen(Weekday d) {
    auto &f = schedule[d];
    f.closed = false; // Non è chiuso
    f.alwaysOpen = true; // È sempre aperto
}

// Controlla se è chiuso in un giorno
bool weeklyOpenings::isClosed(Weekday day) const {
    return schedule.value(day).closed;
}

// Controlla se è sempre aperto in un giorno
bool weeklyOpenings::isAlwaysOpen(Weekday day) const {
    return schedule.value(day).alwaysOpen;
}

// Controlla se apre prima di un'ora in un giorno
bool weeklyOpenings::opensBefore(Weekday day, const QTime& time) const{
    if (!schedule.contains(day) || schedule.value(day).closed) return false;
    return schedule.value(day).opening < time;
}

// Controlla se è aperto a una certa ora in un giorno
bool weeklyOpenings::isOpenAt(Weekday day, const QTime& time) const{
    if(!schedule.contains(day)) return false;
    const openingFrames& f = schedule.value(day);
    return !f.closed && (f.opening <= time && f.closing >= time);
}

// Formatta gli orari di un giorno come stringa
QString weeklyOpenings::getOpeningFrameString(Weekday day) const {
    const openingFrames f = schedule.value(day);
    if (f.closed)
        return QStringLiteral("Closed");
    if (f.alwaysOpen)
        return QStringLiteral("Always open");
    return QString("%1 - %2")
        .arg(f.opening.toString("HH:mm"))
        .arg(f.closing.toString("HH:mm"));
}

// Formatta tutti gli orari come stringa multilinea
QString weeklyOpenings::toQStringMultiline() const {
    static const QList<Weekday> giorni = {
        Weekday::Monday, Weekday::Tuesday, Weekday::Wednesday,
        Weekday::Thursday, Weekday::Friday, Weekday::Saturday,
        Weekday::Sunday
    };
    QStringList righe;
    for (Weekday d : giorni) {
        QString nome = weekdayToString(d);
        righe << QString("%1: %2")
                     .arg(nome.left(3),
                          getOpeningFrameString(d));
    }
    return righe.join('\n');
}

// Converte da Weekday a stringa
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
    return "ERROR"; // Dovrebbe non succedere mai con Weekday
}

// Converte da stringa a Weekday
Weekday weeklyOpenings::weekdayFromString(const QString& dayStr) {
    if (dayStr == "Monday") return Weekday::Monday;
    else if (dayStr == "Tuesday") return Weekday::Tuesday;
    else if (dayStr == "Wednesday") return Weekday::Wednesday;
    else if (dayStr == "Thursday") return Weekday::Thursday;
    else if (dayStr == "Friday") return Weekday::Friday;
    else if (dayStr == "Saturday") return Weekday::Saturday;
    else if (dayStr == "Sunday") return Weekday::Sunday;

    // Fallback in caso di stringa non valida
    qWarning() << "weekdayFromString: error:" << dayStr;
    return Weekday::Monday; // Ritorna Monday come default in caso di errore
}

// Ritorna la fascia oraria giorno per giorno se esiste, altrimenti chiuso
openingFrames weeklyOpenings::getOpening(Weekday day) const{
    return schedule.value(day, openingFrames());
}

// Ritorna l'ora di apertura per un giorno
QTime weeklyOpenings::openTime(Weekday day) const
{
    return getOpening(day).opening;
}

// Ritorna l'ora di chiusura per un giorno
QTime weeklyOpenings::closeTime(Weekday day) const
{
    return getOpening(day).closing;
}

// Ritorna l'intera schedule
const QMap<Weekday, openingFrames>& weeklyOpenings::getSchedule() const {
    return schedule;
}
