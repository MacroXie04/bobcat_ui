#ifndef BOBCAT_UI_DROPDOWN
#define BOBCAT_UI_DROPDOWN

#include "bobcat_ui.h"

#include <FL/Enumerations.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Widget.H>

#include <string>
#include <functional>

// #include <FL/names.h>

namespace bobcat {

// Dropdown class inheriting from Fl_Choice
class Dropdown: public Fl_Choice {
    std::string caption; // Caption of the dropdown

    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onEnterCb;
    std::function<void(bobcat::Widget *)> onLeaveCb;
    std::function<void(bobcat::Widget *)> onChangeCb;

    // Initialize the callback functions to nullptr
    void init() {
        onEnterCb = nullptr;
        onLeaveCb = nullptr;
        onChangeCb = nullptr;
    }

    // Handle events for the dropdown
    int handle(int event) {
        // if (event == 8 || event == 9)
        // printf("Event was %s (%d) - %s\n", fl_eventnames[event], event, value());
        int ret = Fl_Choice::handle(event);
        if (event == FL_ENTER) {
            if (onEnterCb) onEnterCb(this);
        }

        if (event == FL_LEAVE) {
            if (onLeaveCb) onLeaveCb(this);
        }

        return ret;
    }

public:
    // Constructor to initialize the dropdown with position, size, and caption
    Dropdown(int x, int y, int w, int h, std::string caption = ""): Fl_Choice(x, y, w, h, caption.c_str()) {
        init();
        align(FL_ALIGN_TOP_LEFT);
        this->caption = caption;
        Fl_Choice::copy_label(caption.c_str());
    }

    // Get the label of the dropdown
    std::string label() const {
        return caption;
    }

    // Set the label of the dropdown
    void label(std::string s) {
        Fl_Choice::copy_label(s.c_str());
        caption = s;
    }

    // Get the text of the selected item
    std::string text() const {
        std::string temp = Fl_Choice::text();
        return temp;
    }

    // Add an item to the dropdown
    int add(std::string item) {
        int index = Fl_Choice::add(item.c_str());
        if (index == 0) Fl_Choice::value(0);
        return index;
    }

    // Set the selected item by index
    void value(int index) {
        Fl_Choice::value(index);
        if (onChangeCb) onChangeCb(this);
    }

    // Set the selected item by text
    void text(std::string s) {
        int i = Fl_Choice::find_index(s.c_str());
        Fl_Choice::value(i);
        if (onChangeCb) onChangeCb(this);
    }

    // Get the index of the selected item
    int value() {
        return Fl_Choice::value();
    }

    // Remove an item by index
    void remove(int i) {
        Fl_Choice::remove(i);
    }

    // Remove an item by text
    void remove(std::string s) {
        int i = Fl_Choice::find_index(s.c_str());
        if (i != -1) {
            Fl_Choice::remove(i);
        }
    }

    // Set the onEnter callback function
    void onEnter(std::function<void(bobcat::Widget *)> cb) {
        onEnterCb = cb;
    }

    // Set the onLeave callback function
    void onLeave(std::function<void(bobcat::Widget *)> cb) {
        onLeaveCb = cb;
    }

    // Set the onChange callback function
    void onChange(std::function<void(bobcat::Widget *)> cb) {
        onChangeCb = cb;
        when(FL_WHEN_CHANGED);
        callback([](bobcat::Widget* sender, void* self) {
            Dropdown *dd = (Dropdown*) self;
            dd->onChangeCb(dd);
        }, this);
    }

    // Set the alignment of the dropdown
    void align(Fl_Align alignment) {
        Fl_Choice::align(alignment);
        parent()->redraw();
    }

    // Get the label size of the dropdown
    Fl_Fontsize labelsize() {
        return Fl_Choice::labelsize();
    }

    // Set the label size of the dropdown
    void labelsize(Fl_Fontsize pix) {
        Fl_Choice::labelsize(pix);
        parent()->redraw();
    }

    // Get the label color of the dropdown
    Fl_Color labelcolor() {
        return Fl_Choice::labelcolor();
    }

    // Set the label color of the dropdown
    void labelcolor(Fl_Color color) {
        Fl_Choice::labelcolor(color);
        parent()->redraw();
    }

    // Get the label font of the dropdown
    Fl_Font labelfont() {
        return Fl_Choice::labelfont();
    }

    // Set the label font of the dropdown
    void labelfont(Fl_Font f) {
        Fl_Choice::labelfont(f);
        parent()->redraw();
    }

    // Set the focus to the dropdown
    void take_focus() {
        Fl_Choice::take_focus();
    }

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif