#ifndef BOBCAT_UI_TEXTBOX
#define BOBCAT_UI_TEXTBOX

#include "bobcat_ui.h"
#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <string>
#include <functional>

namespace bobcat {

// TextBox class inheriting from Fl_Box
class TextBox: public Fl_Box {
    std::string caption; // Caption of the text box

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

    // Handle events for the text box
    int handle(int event) {
        if (event == FL_ENTER) {
            if (onEnterCb) onEnterCb(this);
        }
        if (event == FL_LEAVE) {
            if (onLeaveCb) onLeaveCb(this);
        }

        if (event == FL_PUSH) {
            Fl::focus(this);
            return 1;
        }

        if (event == FL_RELEASE) {
            if (Fl::event_inside(this)) {
                if (Fl::focus() == this) {
                    if (onClickCb) onClickCb(this);
                }
            }
        }

        return Fl_Box::handle(event);
    }

public:
    // Constructor to initialize the text box with position, size, and caption
    TextBox(int x, int y, int w, int h, std::string caption = ""): Fl_Box(x, y, w, h, caption.c_str()) {
        init();
        Fl_Box::align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
        this->caption = caption;
        Fl_Box::copy_label(caption.c_str());
    }

    // Get the label of the text box
    std::string label() const {
        return caption;
    }

    // Set the label of the text box
    void label(std::string s) {
        Fl_Box::copy_label(s.c_str());
        caption = s;
    }

    // Set the onClick callback function
    void onClick(std::function<void(bobcat::Widget *)> cb) {
        onClickCb = cb;
    }

    // Set the onEnter callback function
    void onEnter(std::function<void(bobcat::Widget *)> cb) {
        onEnterCb = cb;
    }

    // Set the onLeave callback function
    void onLeave(std::function<void(bobcat::Widget *)> cb) {
        onLeaveCb = cb;
    }

    // Set the alignment of the text box
    void align(Fl_Align alignment) {
        Fl_Box::align(FL_ALIGN_INSIDE | alignment);
        redraw_label();
    }

    // Get the label size of the text box
    Fl_Fontsize labelsize() {
        return Fl_Box::labelsize();
    }

    // Set the label size of the text box
    void labelsize(Fl_Fontsize pix) {
        Fl_Box::labelsize(pix);
        redraw_label();
    }

    // Get the label color of the text box
    Fl_Color labelcolor() {
        return Fl_Box::labelcolor();
    }

    // Set the label color of the text box
    void labelcolor(Fl_Color color) {
        Fl_Box::labelcolor(color);
        redraw_label();
    }

    // Get the label font of the text box
    Fl_Font labelfont() {
        return Fl_Box::labelfont();
    }

    // Set the label font of the text box
    void labelfont(Fl_Font f) {
        Fl_Box::labelfont(f);
        redraw_label();
    }

    // Set the focus to the text box
    void take_focus() {
        Fl_Box::take_focus();
    }

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif