#include "global.h"
#include "Arduino.h"

void LogInfo(String message)
{
    LogInfo(message, false);
}
void LogInfo(String message, bool showInfoLabel)
{
    _GlobalInternal::_PrintLog(showInfoLabel ? "[INFO]" : new char, message);
}
void LogWarning(String message)
{
    _GlobalInternal::_PrintLog("[WARNING]", message);
}
void LogError(String message)
{
    _GlobalInternal::_ThrowLog("[ERROR]", message);
}
void LogException(String message)
{
    _GlobalInternal::_ThrowLog("[EXCEPTION]", message);
}

void _GlobalInternal::_PrintLog(String label, String message)
{
    printf("%s \n", _ParseLog(label, message));
}
void _GlobalInternal::_ThrowLog(String label, String message)
{
    throw _ParseLog(label, message);
}
const char *_GlobalInternal::_ParseLog(String label, String message)
{
    String log = "";
    // check if label/message are present
    bool hasLabel = label && label.length() > 0;
    bool hasMessage = message && message.length() > 0;
    // add label
    if (hasLabel)
    {
        // format label
        label.trim();
        if (!label.startsWith("["))
        {
            label = "[" + label;
        }
        if (!label.endsWith("]"))
        {
            label += "]";
        }
        // append label to log, check if message is present
        log += hasMessage ? label + " " : label;
    }
    // add message
    if (hasMessage)
    {
        log += message;
    }
    return hasLabel || hasMessage ? log.c_str() : new char;
}

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14
#define PIN_15 15
#define PIN_16 16