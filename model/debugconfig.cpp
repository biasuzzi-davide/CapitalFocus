#include "debugconfig.h"

bool DEBUG_MODE = false;

void DebugConfig::setEnabled(bool enabled) {
    DEBUG_MODE = enabled;
}

bool DebugConfig::isEnabled() {
    return DEBUG_MODE;
}
