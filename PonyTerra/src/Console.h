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
/*
enum class ECVarType
{
    FLOAT,
    INT,
    STRING
};

template<typename _type>
class CCVar
{
public:
    CCVar();
    CCVar(ECVarType type, _type defaultValue);
    CCVar(ECVarType type, _type defaultValue, _type minValue, _type maxValue);

    ECVarType type;
    _type value;
    _type minValue;
    _type maxValue;
};

template<typename _type>
inline CCVar<_type>::CCVar()
{
    this->type = ECVarType::INT;
}

template<>
inline CCVar<int>::CCVar()
{
    this->type = ECVarType::INT;
}

template<>
inline CCVar<float>::CCVar()
{
    this->type = ECVarType::FLOAT;
}

template<>
inline CCVar<std::string>::CCVar()
{
    this->type = ECVarType::STRING;
}

template<typename _type>
inline CCVar<_type>::CCVar(_type defaultValue) : CCVar()
{
    value = defaultValue;
}

template<typename _type>
inline CCVar<_type>::CCVar(_type defaultValue, _type minValue, _type maxValue) : CCVar(defaultValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}*/

class CConsole
{
public:
    CConsole();
    ~CConsole();

    void Initialize();

    void Clear();

    bool IsInitialized() const;

    void ToggleFocus();
    bool HasFocus();

    bool Exec(const std::string &cmd);
    void Print(const std::string &msg);

    void Update(float dtTime);
    void Draw();

    void RegisterCommand(const std::string &name, consoleCmd_t cmd);

private:
    bool isInitialized;
    bool hasFocus;
    char textBuffer[CONSOLE_BUFFER_H][CONSOLE_BUFFER_W];
    std::string prompt;
    std::vector<std::string> promptBuffer;
    unsigned int promptBufferIndex;

    typedef std::map<std::string, consoleCmd_t> cmdMap_t;
    cmdMap_t cmdMap;

    unsigned int GetTextBufferLatestIndex();
    void MoveTextUp();
};

extern CConsole console;

#endif