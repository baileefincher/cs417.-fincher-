#include "ErrorContext.h"
#include <iostream>
#include "logger.h"
#include "loggerfactory.h"
using namespace std;

int main() {
    SDAOSLogger* logger = getLogger();
    ErrorContext ctx(ErrorLevel::SEVERE, "hello");
    logger->logInfo("test info msg");
    logger->logError("test error message");
    logger->logWarning("test warning msg");
    logger->logSevere("test severe msg");
}