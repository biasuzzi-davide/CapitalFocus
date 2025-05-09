#ifndef OPENINGFRAMES_H
#define OPENINGFRAMES_H

#include <QTime>

struct openingFrames {
    QTime opening;
    QTime closing;
    bool closed    = false;
    bool alwaysOpen= false;

    openingFrames();
    openingFrames(const QTime&, const QTime&);
    QString getStartAsString() const;
    QString getEndAsString() const;
    openingFrames(const openingFrames&) = default;
    openingFrames& operator=(const openingFrames&) = default;
};

#endif // OPENINGFRAMES_H
