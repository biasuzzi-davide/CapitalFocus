#ifndef OPENINGFRAMES_H
#define OPENINGFRAMES_H

#include <QTime>

struct openingFrames {
    QTime opening;
    QTime closing;
    bool closed;

    openingFrames() : closed(true) {}

    openingFrames(const QTime& open, const QTime& close)
        : opening(open), closing(close), closed(false) {}
};

#endif // OPENINGFRAMES_H
