#pragma once
#include "ErrorContext.h"
#include <iostream>
#include <string.h>

struct SDAOSLogger {

public:
    SDAOSLogger() {
    }

    virtual void logSevere(std::string msg) = 0;
    virtual void logError(std::string msg) = 0;
    virtual void logWarning(std::string msg) = 0;
    virtual void logInfo(std::string msg) = 0;

    virtual void log(ErrorContext& context) = 0;
};