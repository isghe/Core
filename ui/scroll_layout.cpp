#include "scroll_layout.h"

UIScrollLayout::UIScrollLayout(const vec2& scroll_rect, bool horizontal) : scroll_rect(scroll_rect), UILayout(horizontal) {

    vertical_scrollbar   = new UIScrollBar(this, false);
    horizontal_scrollbar = new UIScrollBar(this, true);
    expanded_rect = vec2(0.0f);
    fill = true;
}

UIScrollLayout::~UIScrollLayout() {
    delete vertical_scrollbar;
    delete horizontal_scrollbar;
}

vec2 UIScrollLayout::getRect() {
    return glm::min(scroll_rect,rect)+expanded_rect;
}

vec2 UIScrollLayout::getScrollRect() {
    return scroll_rect+expanded_rect;
}

vec2 UIScrollLayout::getInnerRect() {
    return rect;
}

void UIScrollLayout::expandRect(const vec2& expand) {
    expanded_rect = expand;    
}

void UIScrollLayout::resetRect() {
    expanded_rect = vec2(0.0f);    
}

void UIScrollLayout::update(float dt) {

    UILayout::update(dt);

    //rect = scroll_rect;//glm::min( scroll_rect, rect );

    vertical_scrollbar->update(dt);
    horizontal_scrollbar->update(dt);
}

void UIScrollLayout::updatePos(const vec2& pos) {

    UILayout::updatePos(pos);

    vertical_scrollbar->updatePos();
    horizontal_scrollbar->updatePos();
}

void UIScrollLayout::scroll(bool up) {
    vertical_scrollbar->scroll(up);
}

UIElement* UIScrollLayout::elementAt(const vec2& pos) {

    if(vertical_scrollbar->elementAt(pos))   return vertical_scrollbar;
    if(horizontal_scrollbar->elementAt(pos)) return horizontal_scrollbar;

    if(!UIElement::elementAt(pos)) return 0;

    //apply scroll offset to position
    
    vec2 scrolled_pos = vec2(horizontal_scrollbar->bar_offset * rect.x, vertical_scrollbar->bar_offset * rect.y) + pos;

    UIElement* found = 0;

    foreach(UIElement* e, elements) {
        if((found = e->elementAt(scrolled_pos)) != 0) return found;
    }

    return this;
}

void UIScrollLayout::draw() {

    glEnable(GL_SCISSOR_TEST);

    vec2 scroll_offset = vec2(horizontal_scrollbar->bar_offset * -rect.x, vertical_scrollbar->bar_offset * -rect.y);

    glPushMatrix();
        glTranslatef(scroll_offset.x, scroll_offset.y, 0.0f);
    
        glScissor(pos.x, display.height-(pos.y+scroll_rect.y+expanded_rect.y), scroll_rect.x+expanded_rect.x, scroll_rect.y+expanded_rect.y);

        UILayout::draw();

        glDisable(GL_SCISSOR_TEST);
    glPopMatrix();
    
    vertical_scrollbar->draw();
    horizontal_scrollbar->draw();
}
