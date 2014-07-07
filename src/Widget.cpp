#include "IInput.h"
#include "Widget.h"

CWidget::CWidget(CVector2f pos, int width, int height) {
	this->pos = pos;
	this->width = width;
	this->height = height;

	isMouseHovered = false;
	isClicked = false;
}

void CWidget::Update(float dtTime) {
	CMouseState mouseState = input->GetMouseState();

	CRect mouseRect = mouseState.GetRect();
	CRect thisRect = GetRect();

	isMouseHovered = thisRect.Collides(mouseRect);

	isClicked = isMouseHovered && (input->GetMouseStateDelta().buttonMask & EMouseButton_LEFT);
}

bool CWidget::IsMouseHovered() const {
	return isMouseHovered;
}

bool CWidget::IsClicked() const {
	return isClicked;
}