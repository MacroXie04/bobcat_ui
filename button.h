#ifndef BOBCAT_UI_BUTTON
#define BOBCAT_UI_BUTTON

#include "bobcat_ui.h"

#include <FL/Fl_Button.H>

#include <string>
#include <functional>


namespace bobcat {

class Button: public Fl_Button{
    std::string caption;

    std::function<void(bobcat::Widget *)> onClickCb;
    std::function<void(bobcat::Widget *)> onEnterCb;
    std::function<void(bobcat::Widget *)> onLeaveCb;

    void init(){
        onClickCb = nullptr;
        onEnterCb = nullptr;
        onLeaveCb = nullptr;
    }

    int handle(int event) {
        int ret = Fl_Button::handle(event);

        if (event == FL_ENTER){
            if (onEnterCb) onEnterCb(this);
        }
        if (event == FL_LEAVE){
            if (onLeaveCb) onLeaveCb(this);
        }
        return ret;
    }

public:
    Button(int x, int y, int w, int h, std::string caption = ""): Fl_Button(x, y, w, h, caption.c_str()) {
        init();
        this->caption = caption;
        Fl_Button::copy_label(caption.c_str());
    }

    std::string label() const {
        return caption;
    }

    void label(std::string s){
        Fl_Button::copy_label(s.c_str());
        caption = s;
    }

    void onClick(std::function<void(bobcat::Widget *)> cb){
        onClickCb = cb;
        callback([](bobcat::Widget* sender, void* self){
            Button* butt = (Button*) self;
            butt->onClickCb(butt);
        }, this);
    }

    void onEnter(std::function<void(bobcat::Widget *)> cb){
        onEnterCb = cb;
    }

    void onLeave(std::function<void(bobcat::Widget *)> cb){
        onLeaveCb = cb;
    }

    void align(Fl_Align alignment){
        Fl_Button::align(alignment);
        parent()->redraw();
    }

    Fl_Fontsize labelsize() {
        return Fl_Button::labelsize();
    }

    void labelsize(Fl_Fontsize pix) {
        Fl_Button::labelsize(pix);
        parent()->redraw();
    }

    Fl_Color labelcolor() {
        return Fl_Button::labelcolor();
    }

    void labelcolor(Fl_Color color) {
        Fl_Button::labelcolor(color);
        parent()->redraw();
    }

    Fl_Font labelfont() {
        return Fl_Button::labelfont();
    }

    void labelfont(Fl_Font f) {
        Fl_Button::labelfont(f);
        parent()->redraw();
    }

    void take_focus() {
        Fl_Button::take_focus();
    }

    friend struct ::AppTest;
};

}

#endif