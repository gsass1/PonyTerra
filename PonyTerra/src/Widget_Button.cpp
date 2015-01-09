#include "Color.h"
#include "IFont.h"
#include "IGraphics.h"
#include "IResourceManager.h"
#include "Widget_Button.h"

#include <string.h>

// We actually only use the size of the string,
// so just pass 0 to CWidget constructor.
CWidget_Button::CWidget_Button(const char *text, CVector2f pos) 
    : CWidget(pos, 0, 0) {
    strcpy(this->text, text);
    font = NULL;
}

CWidget_Button::~CWidget_Button() {
}

void CWidget_Button::Initialize() {
    font = resMgr->GetFont("data/res/font/menu.fnt");
}

void CWidget_Button::Update(float dtTime) {
    CWidget::Update(dtTime);
}

void CWidget_Button::Draw() {
    CColor color = isMouseHovered ? CColor(255, 255, 255) : CColor(128, 128, 128);
    graphics->DrawText(font, pos, color, text, true);
}

CRect CWidget_Button::GetRect() const {
    CVector2f rectSize = font->GetTextSize(text);

    CRect rect(pos, (int)rectSize.x, (int)rectSize.y);
    rect.pos -= rectSize / 2.0f;
    return rect;
}
