#include "debugconfig.h"

// Inizialmente il debug è disattivato
bool DEBUG_MODE = false;

// Attiva/disattiva il flag di debug
void DebugConfig::setEnabled(bool enabled) {
    DEBUG_MODE = enabled;
}

// Controlla lo stato del flag di debug
bool DebugConfig::isEnabled() {
    return DEBUG_MODE;
}
