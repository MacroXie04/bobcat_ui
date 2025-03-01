#ifndef BOBCAT_UI_CHECKBOX
#define BOBCAT_UI_CHECKBOX

#include "bobcat_ui.h"
#include <FL/Fl_Check_Button.H>
#include <string>
#include <functional>

namespace bobcat {

// Checkbox class inheriting from Fl_Check_Button
class Checkbox: public Fl_Check_Button {
    std::string caption; // Caption of the checkbox

    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onClickCb;
    std::function<void(bobcat::Widget *)> onEnterCb;
    std::function<void(bobcat::Widget *)> onLeaveCb;
    std::function<void(bobcat::Widget *)> onChangeCb;

    // Initialize the callback functions to nullptr
    void init() {
        onClickCb = nullptr;
        onEnterCb = nullptr;
        onLeaveCb = nullptr;
        onChangeCb = nullptr;
    }

    // Handle events for the checkbox
    int handle(int event) {
        int ret = Fl_Check_Button::handle(event);

        if (event == FL_ENTER) {
            if (onEnterCb) onEnterCb(this);
        }
        if (event == FL_LEAVE) {
            if (onLeaveCb) onLeaveCb(this);
        }
        return ret;
    }

public:
    // Constructor to initialize the checkbox with position, size, and caption
    Checkbox(int x, int y, int w, int h, std::string caption = ""): Fl_Check_Button(x, y, w, h, caption.c_str()) {
        init();
        this->caption = caption;
        Fl_Check_Button::copy_label(caption.c_str());
    }

    // Get the label of the checkbox
    std::string label() const {
        return caption;
    }

    // Set the label of the checkbox
    void label(std::string s) {
        Fl_Check_Button::copy_label(s.c_str());
        caption = s;
    }

    // Set the onClick callback function
    void onClick(std::function<void(bobcat::Widget *)> cb) {
        onClickCb = cb;
        callback([](bobcat::Widget* sender, void* self) {
            Checkbox* butt = (Checkbox*) self;
            butt->onClickCb(butt);
        }, this);
    }

    // Set the onEnter callback function
    void onEnter(std::function<void(bobcat::Widget *)> cb) {
        onEnterCb = cb;
    }

    // Set the onLeave callback function
    void onLeave(std::function<void(bobcat::Widget *)> cb) {
        onLeaveCb = cb;
    }

    // Check if the checkbox is checked
    bool checked() const {
        return value() == 1;
    }

    // Check the checkbox
    void check() {
        set();
        if (onChangeCb) onChangeCb(this);
    }
    
    // Uncheck the checkbox
    void uncheck() {
        clear();
        if (onChangeCb) onChangeCb(this);
    }

    // Set the onChange callback function
    void onChange(std::function<void(bobcat::Widget *)> cb) {
        onChangeCb = cb;
        when(FL_WHEN_CHANGED);
        callback([](bobcat::Widget* sender, void* self) {
            Checkbox *in = (Checkbox*) self;
            in->onChangeCb(in);
        }, this);
    }

    // Set the alignment of the checkbox
    void align(Fl_Align alignment) {
        Fl_Check_Button::align(alignment);
        parent()->redraw();
    }

    // Get the label size of the checkbox
    Fl_Fontsize labelsize() {
        return Fl_Check_Button::labelsize();
    }

    // Set the label size of the checkbox
    void labelsize(Fl_Fontsize pix) {
        Fl_Check_Button::labelsize(pix);
        parent()->redraw();
    }

    // Get the label color of the checkbox
    Fl_Color labelcolor() {
        return Fl_Check_Button::labelcolor();
    }

    // Set the label color of the checkbox
    void labelcolor(Fl_Color color) {
        Fl_Check_Button::labelcolor(color);
        parent()->redraw();
    }

    // Get the label font of the checkbox
    Fl_Font labelfont() {
        return Fl_Check_Button::labelfont();
    }

    // Set the label font of the checkbox
    void labelfont(Fl_Font f) {
        Fl_Check_Button::labelfont(f);
        parent()->redraw();
    }

    // Set the focus to the checkbox
    void take_focus() {
        Fl_Check_Button::take_focus();
    }

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif