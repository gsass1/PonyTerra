#ifndef CONSOLE_H
#define CONSOLE_H

#include <map>
#include <string>
#include <vector>

#define CONSOLE_BUFFER_W 256
#define CONSOLE_BUFFER_H 64
#define CONSOLE_TEXT_SPACING 10
#define CONSOLE_PROMPT_BUFFER_SIZE 1024

#define CONSOLE_COMMAND(cmd) static int Cmd_##cmd##(cmdArgs_t args)

typedef std::vector<std::string> cmdArgs_t;
typedef int(*consoleCmd_t)(cmdArgs_t);

enum class CVarType
{
    FLOAT,
    INT,
    STRING
};

template<typename _type>
class CCVar
{
public:
    CCVar(CVarType type);
    CCVar(CVarType type, _type defaultValue);
    CCVar(CVarType type, _type defaultValue, _type minValue, _type maxValue);

    CVarType type;
    _type value;
    _type minValue;
    _type maxValue;
};

template<typename _type>
inline CCVar<_type>::CCVar(CVarType type)
{
    this->type = type;
}

template<typename _type>
inline CCVar<_type>::CCVar(CVarType type, _type defaultValue) : CCVar(type)
{
    value = defaultValue;
}

template<typename _type>
inline CCVar<_type>::CCVar(CVarType type, _type defaultValue, _type minValue, _type maxValue) : CCVar(type, defaultValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

class CConsole
{
public:
    CConsole();
    ~CConsole();

    void Clear();

    void ToggleFocus();
    bool HasFocus();

    void Exec(const std::string &cmd);
    void Print(const std::string &msg);

    void Update(float dtTime);
    void Draw();

    void RegisterCommand(const std::string &name, consoleCmd_t cmd);

private:
    bool hasFocus;
    char textBuffer[CONSOLE_BUFFER_W][CONSOLE_BUFFER_H];
    std::string prompt;
    std::string promptBuffer[CONSOLE_PROMPT_BUFFER_SIZE];

    typedef std::map<std::string, consoleCmd_t> cmdMap_t;
    cmdMap_t cmdMap;

    unsigned int GetTextBufferLatestIndex();
    void MoveTextUp();
};

extern CConsole console;

#endif