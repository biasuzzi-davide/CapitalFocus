#ifndef OPENINGFRAMES_H
#define OPENINGFRAMES_H

#include <QTime>
#include <QString>

// Struttura per gli orari di apertura/chiusura
struct openingFrames {
    QTime opening; // Ora apertura
    QTime closing; // Ora chiusura
    bool closed = false; // È chiuso tutto il giorno
    bool alwaysOpen = false; // È sempre aperto

    // Costruttore
    openingFrames();
    // Costruttore con orari specifici
    openingFrames(const QTime&, const QTime&);

    // Copy constructor e assignment operator di default
    openingFrames(const openingFrames&) = default;
    openingFrames& operator=(const openingFrames&) = default;

    // Getter
    QString getStartAsString() const;
    QString getEndAsString() const;
};

#endif // OPENINGFRAMES_H
