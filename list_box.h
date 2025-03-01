#ifndef BOBCAT_UI_LIST_BOX
#define BOBCAT_UI_LIST_BOX

#include "bobcat_ui.h"
#include <FL/Enumerations.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Widget.H>
#include <functional>
#include <string>
#include <iostream>

namespace bobcat {

// ListBox class inheriting from Fl_Hold_Browser
class ListBox : public Fl_Hold_Browser {
    std::string caption; // Caption of the list box

    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onChangeCb;
    std::function<void(bobcat::Widget *)> onClickCb;
    std::function<void(bobcat::Widget *)> onEnterCb;
    std::function<void(bobcat::Widget *)> onLeaveCb;

    // Initialize the callback functions to nullptr
    void init() {
        onClickCb = nullptr;
        onEnterCb = nullptr;
        onLeaveCb = nullptr;
        onChangeCb = nullptr;
    }

    // Handle events for the list box
    int handle(int event) {
        int ret = Fl_Hold_Browser::handle(event);
        if (event == FL_ENTER) {
            if (onEnterCb) onEnterCb(this);
        }

        if (event == FL_LEAVE) {
            if (onLeaveCb) onLeaveCb(this);
        }

        return ret;
    }

public:
    // Constructor to initialize the list box with position, size, and title
    ListBox(int x, int y, int w, int h, std::string title = "") : Fl_Hold_Browser(x, y, w, h, title.c_str()) {
        init();
        align(FL_ALIGN_TOP_LEFT);
        Fl_Hold_Browser::copy_label(title.c_str());
    }

    // Get the label of the list box
    std::string label() const {
        return caption;
    }

    // Set the label of the list box
    void label(std::string s) {
        Fl_Hold_Browser::copy_label(s.c_str());
        caption = s;
    }

    // Get the selected item text
    std::string getSelected() const {
        std::string result = "";
        void *item = selection();
        if (item != nullptr) {
            result = item_text(item);
        }
        return result;
    }

    // Get the item text at a specific index
    std::string get(int index) {
        return item_text(item_at(index + 1));
    }

    // Remove the selected item
    void removeSelected() {
        void *item = selection();
        if (item != nullptr) {
            for (int i = 1; i <= size(); i++) {
                if (item_at(i) == item) {
                    Fl_Hold_Browser::remove(i);
                    break;
                }
            }
            if (onChangeCb) onChangeCb(this);
        }
    }

    // Add an item to the list box
    void add(std::string text) {
        Fl_Hold_Browser::add(text.c_str());
        if (onChangeCb) onChangeCb(this);
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

    // Set the onClick callback function
    void onClick(std::function<void(bobcat::Widget *)> cb) {
        onClickCb = cb;
        callback([](bobcat::Widget* sender, void* self) {
            ListBox* butt = (ListBox*) self;
            butt->onClickCb(butt);
        }, this);
    }

    // Set the alignment of the list box
    void align(Fl_Align alignment) {
        Fl_Hold_Browser::align(alignment);
        parent()->redraw();
    }

    // Get the label size of the list box
    Fl_Fontsize labelsize() {
        return Fl_Hold_Browser::labelsize();
    }

    // Set the label size of the list box
    void labelsize(Fl_Fontsize pix) {
        Fl_Hold_Browser::labelsize(pix);
        parent()->redraw();
    }

    // Get the label color of the list box
    Fl_Color labelcolor() {
        return Fl_Hold_Browser::labelcolor();
    }

    // Set the label color of the list box
    void labelcolor(Fl_Color color) {
        Fl_Hold_Browser::labelcolor(color);
        parent()->redraw();
    }

    // Get the label font of the list box
    Fl_Font labelfont() {
        return Fl_Hold_Browser::labelfont();
    }

    // Set the label font of the list box
    void labelfont(Fl_Font f) {
        Fl_Hold_Browser::labelfont(f);
        parent()->redraw();
    }

    // Set the focus to the list box
    void take_focus() {
        Fl_Hold_Browser::take_focus();
    }

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif