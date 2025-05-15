#include "openingFrames.h"

// Costruttore di default che imposta chiuso
openingFrames::openingFrames() : closed(true) {};

// Costruttore con orari specifici
openingFrames::openingFrames(const QTime& open, const QTime& close)
    : opening(open), closing(close), closed(false) {};

// Ritorna l'ora di apertura come stringa
QString openingFrames::getStartAsString() const {
    return opening.toString("HH:mm");
}

// Ritorna l'ora di chiusura come stringa
QString openingFrames::getEndAsString() const {
    return closing.toString("HH:mm");
}
