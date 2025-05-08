#ifndef DEBUGCONFIG_H
#define DEBUGCONFIG_H

#include <QDebug>

// Variabile globale di configurazione
extern bool DEBUG_MODE;

// Macro per stampa condizionata
#define DEBUG_LOG(x) \
do { if (DEBUG_MODE) qDebug() << x; } while (0)

    // Funzioni per modificare e leggere il flag
    namespace DebugConfig {
    void setEnabled(bool enabled);
    bool isEnabled();
}

#endif // DEBUGCONFIG_H
