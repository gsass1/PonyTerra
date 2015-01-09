#ifndef GUI_H
#define GUI_H

class IGUI {
public:
    virtual         ~IGUI() {}

    virtual void    Initialize() = 0;
    virtual void    Dispose() = 0;

    virtual void    OnResize() = 0;

    virtual void    Update(float dt) = 0;
    virtual void    Draw() = 0;
};

#endif