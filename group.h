#ifndef BOBCAT_UI_GROUP
#define BOBCAT_UI_GROUP

#include "bobcat_ui.h"
#include <FL/Enumerations.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_PNG_Image.H>
#include <GL/gl.h>
#include <string>
#include <functional>

namespace bobcat {

/**
 * @class Group
 * @brief A class representing a group of widgets, inheriting from Fl_Group.
 * 
 * The Group class provides functionality to manage a group of widgets with 
 * additional callback functions for various events such as change, enter, and leave.
 */
class Group : public Fl_Group {
private:
    std::string caption; // Caption of the group

    // Initialize the callback functions to nullptr
    void init() {
        onChangeCb = nullptr;
        onEnterCb = nullptr;
        onLeaveCb = nullptr;
    }

protected:
    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onChangeCb;
    std::function<void(bobcat::Widget *)> onEnterCb;
    std::function<void(bobcat::Widget *)> onLeaveCb;

public:
    // Constructor to initialize the group with position, size, and title
    Group(int x, int y, int w, int h, std::string title = "") : Fl_Group(x, y, w, h, title.c_str()) { 
        init();
        caption = title;
        Fl_Widget::copy_label(caption.c_str());
    }

    // Set the onChange callback function
    void onChange(std::function<void(bobcat::Widget *)> cb) {
        onChangeCb = cb;
    }

    // Set the onEnter callback function
    void onEnter(std::function<void(bobcat::Widget *)> cb) {
        onEnterCb = cb;
    }

    // Set the onLeave callback function
    void onLeave(std::function<void(bobcat::Widget *)> cb) {
        onLeaveCb = cb;
    }

    // Get the label of the group
    std::string label() const {
        return caption;
    }

    // Set the label of the group
    void label(std::string s) {
        Fl_Widget::copy_label(s.c_str());
        caption = s;
    }

    // void show() override {
    //     Fl_Group::show();
    //     // wait_for_expose();          // Supposedly makes show() synchronous
    //     Fl::flush();                // Make sure to draw what needs to be drawn
    // }

    friend struct ::AppTest;
};

}

#endif