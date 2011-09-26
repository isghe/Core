#ifndef UI_SCROLL_BAR_H
#define UI_SCROLL_BAR_H

#include "element.h"

class UIScrollLayout;

class UIScrollBar: public UIElement {
protected:
    std::vector<TextureResource*> bartex;
public:
    bool inverted;
    bool horizontal;
    float bar_width;
    float bar_min;
    float bar_step;
    float bar_percent;
    float bar_offset;
    float bar_visual_offset;
    bool  flip_sides;

    bool dragging;
    vec2 drag_start;
   

    vec2 bar_rect;

    UIScrollBar(UIScrollLayout* parent, bool horizontal = false);
    ~UIScrollBar();

    int getType() { return UI_SCROLL_BAR; };

    void idle();
    void setSelected(bool selected);
    void drag(const vec2& pos);
    void scroll(bool up);

    void flipSides(bool flip_sides);
    
    UIElement* elementAt(const vec2& pos);
        
    void reset();
    
    void updateRect();
    void updatePos();
    void drawContent();
};

#endif
