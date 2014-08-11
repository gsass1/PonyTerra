#include "Console.h"
#include "ICommon.h"
#include "IResourceManager.h"
#include "IGraphics.h"
#include "IInput.h"
#include "StringUtils.h"
#include <string.h>
#include <sstream>
#include <iterator>
#include "Game.h"
#include "Level.h"

CONSOLE_COMMAND(loadlevel)
{
    if(args.size() != 2) {
        console.Print("Usage: loadlevel <filename>");
        return 1;
    }

    game_local.LoadLevel(args[1]);
    return 0;
}

CONSOLE_COMMAND(savelevel)
{
    if(!level.IsLoaded()) {
        console.Print("Level must be loaded!");
        return 1;
    }

    game_local.SaveLevel(levelFilename);
    return 0;
}

CONSOLE_COMMAND(savelevelandexit)
{
   if(!level.IsLoaded()) {
        console.Print("Level must be loaded!");
        return 1;
    }

    game_local.SaveLevelAndExit(levelFilename);
    return 0;
}

CONSOLE_COMMAND(genlevel)
{
    if(args.size() != 4) {
        console.Print("Usage: genlevel <name> <width> <height>");
        return 1;
    }

    levelFilename = args[1];
    int levelWidth = atoi(args[2].c_str());
    int levelHeight = atoi(args[3].c_str());

    if(levelWidth == 0 || levelHeight == 0) {
        console.Print("Invalid size!");
        return 1;
    }

    game_local.BeginLevelGenProccess(levelWidth, levelHeight);
    return 0;
}

CONSOLE_COMMAND(exitlevel)
{
    game_local.UnloadLevel();
    return 0;
}

CONSOLE_COMMAND(say)
{
    if(args.size() != 2) {
        console.Print("Usage: say <msg>");
        return 1;
    }
    console.Print(args[1]);
    return 0;
}

CONSOLE_COMMAND(clear)
{
    console.Clear();
    return 0;
}

CONSOLE_COMMAND(exit)
{
    common->Quit();
    return 0;
}

CConsole console;

CConsole::CConsole()
{
    Clear();

    RegisterCommand("clear", Cmd_clear);
    RegisterCommand("say", Cmd_say);
    RegisterCommand("exit", Cmd_exit);
    RegisterCommand("genlevel", Cmd_genlevel);
    RegisterCommand("exitlevel", Cmd_exitlevel);
    RegisterCommand("savelevel", Cmd_savelevel);
    RegisterCommand("savelevelandexit", Cmd_savelevelandexit);
    RegisterCommand("loadlevel", Cmd_loadlevel);
}

CConsole::~CConsole()
{
}

void CConsole::Clear()
{
    promptBufferIndex = 0;
    for(unsigned int i = 0; i < CONSOLE_BUFFER_H; i++) {
       textBuffer[i][0] = '\0';
    }
}

void CConsole::ToggleFocus()
{
    hasFocus = !hasFocus;
}

bool CConsole::HasFocus()
{
    return hasFocus;
}

bool CConsole::Exec(const std::string &cmd)
{
    if(cmd.size() == 0) {
        return false;
    }

    Print(cmd);

    // No idea but splits the string by whitespaces
    // Copied from here http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
    std::istringstream iss(cmd);
    cmdArgs_t args
    {
        std::istream_iterator< std::string >
        {
            iss
        },
        std::istream_iterator< std::string >
        {
        }
    };

    cmdMap_t::iterator itr = cmdMap.find(args[0]);
    if(itr != cmdMap.end()) {
        return (*itr->second)(args) == 0;
    } else {
        Print("Could not find that command.");
        return false;
    }
}

void CConsole::Print(const std::string &msg)
{
    int index = GetTextBufferLatestIndex();
    if(index == CONSOLE_BUFFER_H - 1) {
        MoveTextUp();
    }
    strncpy(textBuffer[index], msg.c_str(), CONSOLE_BUFFER_W);
}

void CConsole::Update(float dtTime)
{
    if(!hasFocus) {
        return;
    }

    for(unsigned int i = (unsigned int)NSKey::NSK_0; i < (unsigned int)NSKey::NSK_z + 1; i++) {
        if(input->KeyPressed((NSKey)i, true)) {
            if(isprint((int)i)) {
                prompt += (char)i;
            }
        }
    }

    if(input->KeyPressed(NSKey::NSK_UP, true)) {
        if(promptBuffer.size() != 0 && promptBufferIndex != 0) {
            promptBufferIndex--;
            prompt = "";
            prompt = promptBuffer[promptBufferIndex];
        }
    } else if(input->KeyPressed(NSKey::NSK_DOWN, true)) {
        if(promptBufferIndex != promptBuffer.size() - 1) {
            promptBufferIndex++;
            prompt = "";
            prompt = promptBuffer[promptBufferIndex];
        }
    }

    if(input->KeyPressed(NSKey::NSK_RETURN, true)) {
        if(Exec(prompt)) {
            promptBuffer.push_back(prompt);
            promptBufferIndex++;
        }
        prompt = "";
    }

    if(input->KeyPressed(NSKey::NSK_SPACE, true)) {
        prompt += " ";
    }

    if(input->KeyPressed(NSKey::NSK_BACKSPACE, true)) {
        if(prompt.size() != 0) {
            prompt.erase(prompt.size() - 1);
        }
    }
}

void CConsole::Draw()
{
    if(!hasFocus) {
        return;
    }

    graphics->DrawRect(CRect(CVector2f(0.0f, graphics->GetSize().y - (float)((GetTextBufferLatestIndex() + 1) * CONSOLE_TEXT_SPACING)), CONSOLE_BUFFER_W * CONSOLE_TEXT_SPACING, (CONSOLE_BUFFER_H - 1) * CONSOLE_TEXT_SPACING), CColor(0, 0, 255, 128));
    for(unsigned int i = 0; i < GetTextBufferLatestIndex(); i++) {
        if(textBuffer[i][0] == '\0') {
            continue;
        }
        graphics->DrawText(resMgr->GetFont("data/res/font/sys.fnt"), CVector2f(0.0f, (graphics->GetSize().y - (float)i * (float)CONSOLE_TEXT_SPACING) - (float)CONSOLE_TEXT_SPACING), CColor::white, textBuffer[i]);
    }
    graphics->DrawText(resMgr->GetFont("data/res/font/sys.fnt"), CVector2f(0.0f, (graphics->GetSize().y - (float)GetTextBufferLatestIndex() * (float)CONSOLE_TEXT_SPACING) - (float)CONSOLE_TEXT_SPACING), CColor::white, StrUtl::FormatString(">%s", prompt.c_str()).c_str());
}

unsigned int CConsole::GetTextBufferLatestIndex()
{
    for(unsigned int i = 0; i < CONSOLE_BUFFER_H; i++) {
        if(textBuffer[i][0] == '\0') {
            return i;
        }
    }
    return CONSOLE_BUFFER_H - 1;
}

void CConsole::MoveTextUp()
{
    char newBuffer[CONSOLE_BUFFER_W][CONSOLE_BUFFER_H];
    for(unsigned int i = 1; i < CONSOLE_BUFFER_H; i++) {
        strncpy(newBuffer[i - 1], textBuffer[i], CONSOLE_BUFFER_W);
    }

    for(unsigned int i = 0; i < CONSOLE_BUFFER_H; i++) {
        strncpy(textBuffer[i], newBuffer[i], CONSOLE_BUFFER_W);
    }
}

void CConsole::RegisterCommand(const std::string &name, consoleCmd_t cmd)
{
    cmdMap.insert(std::pair<std::string, consoleCmd_t>(name, cmd));
}