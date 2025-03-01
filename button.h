#ifndef BOBCAT_UI_BUTTON
#define BOBCAT_UI_BUTTON

#include "bobcat_ui.h"
#include <FL/Fl_Button.H>
#include <string>
#include <functional>

namespace bobcat {

// Button class inheriting from Fl_Button
class Button: public Fl_Button {
    std::string caption; // Caption of the button

    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onClickCb;
    std::function<void(bobcat::Widget *)> onEnterCb;
    std::function<void(bobcat::Widget *)> onLeaveCb;

    // Initialize the callback functions to nullptr
    void init() {
        onClickCb = nullptr;
        onEnterCb = nullptr;
        onLeaveCb = nullptr;
    }

    // Handle events for the button
    int handle(int event) {
        int ret = Fl_Button::handle(event);

        if (event == FL_ENTER) {
            if (onEnterCb) onEnterCb(this);
        }
        if (event == FL_LEAVE) {
            if (onLeaveCb) onLeaveCb(this);
        }
        return ret;
    }

public:
    // Constructor to initialize the button with position, size, and caption
    Button(int x, int y, int w, int h, std::string caption = ""): Fl_Button(x, y, w, h, caption.c_str()) {
        init();
        this->caption = caption;
        Fl_Button::copy_label(caption.c_str());
    }

    // Get the label of the button
    std::string label() const {
        return caption;
    }

    // Set the label of the button
    void label(std::string s) {
        Fl_Button::copy_label(s.c_str());
        caption = s;
    }

    // Set the onClick callback function
    void onClick(std::function<void(bobcat::Widget *)> cb) {
        onClickCb = cb;
        callback([](bobcat::Widget* sender, void* self) {
            Button* butt = (Button*) self;
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

    // Set the alignment of the button
    void align(Fl_Align alignment) {
        Fl_Button::align(alignment);
        parent()->redraw();
    }

    // Get the label size of the button
    Fl_Fontsize labelsize() {
        return Fl_Button::labelsize();
    }

    // Set the label size of the button
    void labelsize(Fl_Fontsize pix) {
        Fl_Button::labelsize(pix);
        parent()->redraw();
    }

    // Get the label color of the button
    Fl_Color labelcolor() {
        return Fl_Button::labelcolor();
    }

    // Set the label color of the button
    void labelcolor(Fl_Color color) {
        Fl_Button::labelcolor(color);
        parent()->redraw();
    }

    // Get the label font of the button
    Fl_Font labelfont() {
        return Fl_Button::labelfont();
    }

    // Set the label font of the button
    void labelfont(Fl_Font f) {
        Fl_Button::labelfont(f);
        parent()->redraw();
    }

    // Set the focus to the button
    void take_focus() {
        Fl_Button::take_focus();
    }

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif