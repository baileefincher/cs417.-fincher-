#pragma once
enum class ErrorLevel { SEVERE, ERROR, WARNING, INFO };

struct ErrorContext {
    ErrorLevel errlevel;
    const char* logmsg;

    ErrorContext(ErrorLevel errlevel, const char* logmsg) : errlevel(errlevel), logmsg(logmsg) {
    }
};

extern void SDAOSlogger(struct ErrorContext& logcontext);