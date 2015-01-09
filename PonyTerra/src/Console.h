#ifndef CONSOLE_H
#define CONSOLE_H

#include <map>
#include <string>
#include <vector>

#define CONSOLE_BUFFER_W 256
#define CONSOLE_BUFFER_H 64
#define CONSOLE_TEXT_SPACING 10
#define CONSOLE_PROMPT_BUFFER_SIZE 1024

#define CONSOLE_COMMAND(X) static int Cmd_##X(cmdArgs_t args)

typedef std::vector<std::string> cmdArgs_t;
typedef int(*consoleCmd_t)(cmdArgs_t);

class CConsole
{
public:
				CConsole();
				~CConsole();

    void		Initialize();

    void		Clear();

    bool		IsInitialized() const;

    void		ToggleFocus();
    bool		HasFocus();

    bool		Exec(const std::string &cmd);
    void		Print(const std::string &msg);

    void		Update(float dtTime);
    void		Draw();

    void		RegisterCommand(const std::string &name, consoleCmd_t cmd);

private:
    bool					isInitialized;
    bool					hasFocus;
    char					textBuffer[CONSOLE_BUFFER_H][CONSOLE_BUFFER_W];
    std::string				prompt;
    std::vector<std::string> promptBuffer;
    unsigned int			promptBufferIndex;

    typedef std::map<std::string, consoleCmd_t> cmdMap_t;
    cmdMap_t				cmdMap;

    unsigned int			GetTextBufferLatestIndex();
    void					MoveTextUp();
};

extern CConsole console;

#endif
