#pragma once
#include "logger.h"

class LoggerImpl : public SDAOSLogger {
public:
    LoggerImpl() {
    }

    void logSevere(std::string msg) {
        ErrorContext ctx(ErrorLevel::SEVERE, msg.c_str());
        log(ctx);
    }

    void logError(std::string msg) {
        ErrorContext ctx(ErrorLevel::ERROR, msg.c_str());
        log(ctx);
    }

    void logWarning(std::string msg) {
        ErrorContext ctx(ErrorLevel::WARNING, msg.c_str());
        log(ctx);
    }

    void logInfo(std::string msg) {
        ErrorContext ctx(ErrorLevel::INFO, msg.c_str());
        log(ctx);
    }

    void log(ErrorContext& context) {
        std::cout << "Severity = ";
        switch (context.errlevel) {
        case ErrorLevel::SEVERE:
            std::cout << "SEVERE";
            break;

        case ErrorLevel::ERROR:
            std::cout << "ERROR";
            break;

        case ErrorLevel::WARNING:
            std::cout << "WARNING";
            break;

        case ErrorLevel::INFO:
            std::cout << "INFO";
            break;
        }

        std::cout << ", msg = " << context.logmsg << std::endl;
    }

};