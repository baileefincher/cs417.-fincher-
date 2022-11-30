#pragma once
#include "logger.h"
#include "loggerimpl.h"

SDAOSLogger* getLogger() {
    return new LoggerImpl();
}