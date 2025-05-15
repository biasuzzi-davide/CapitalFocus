#ifndef DEBUGCONFIG_H
#define DEBUGCONFIG_H

#include <QDebug> // Per qDebug()

// Flag globale per il debug
extern bool DEBUG_MODE;

// Macro per stampare messaggi solo in modalità debug
#define DEBUG_LOG(x) \
do { if (DEBUG_MODE) qDebug() << x; } while (0)

    // Namespace per gestire il flag di debug
    namespace DebugConfig {
    // Attiva/disattiva il debug
    void setEnabled(bool enabled);
    // Controlla se il debug è attivo
    bool isEnabled();
}

#endif // DEBUGCONFIG_H
