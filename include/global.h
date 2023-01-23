#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>

void LogInfo(String);
void LogInfo(String message, bool showInfoLabel);
void LogWarning(String message);
void LogError(String message);
void LogException(String message);

class _GlobalInternal
{
public:
    static void _PrintLog(String label, String message);
    static void _ThrowLog(String label, String message);
    static const char *_ParseLog(String label, String message);
};

#endif