#include "openingFrames.h"

openingFrames::openingFrames() : closed(true) {};
openingFrames::openingFrames(const QTime& open, const QTime& close)
    : opening(open), closing(close), closed(false) {};
    // Questo converve in stringa gli orari per poi fare l'export
QString openingFrames::getStartAsString() const {
    return opening.toString("HH:mm");
}
    // Questo converve in stringa gli orari per poi fare l'export
QString openingFrames::getEndAsString() const {
    return closing.toString("HH:mm");
}
