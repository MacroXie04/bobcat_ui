#ifndef BOBCAT_UI_MENU
#define BOBCAT_UI_MENU

#include "bobcat_ui.h"
#include <FL/Enumerations.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Widget.H>
#include <map>
#include <vector>
#include <functional>
#include <iostream>

namespace bobcat {

// MenuItem class inheriting from Fl_Widget
class MenuItem : public Fl_Widget {
    std::string caption; // Caption of the menu item
    std::function<void(bobcat::Widget *)> onClickCb; // Callback function for click event

public:
    // Constructor to initialize the menu item with a caption
    MenuItem(std::string caption) : Fl_Widget(0, 0, 0, 0, caption.c_str()) {
        onClickCb = nullptr;
        Fl_Widget::copy_label(caption.c_str());
        this->caption = caption;
    }

    // Set the onClick callback function
    void onClick(std::function<void(bobcat::Widget *)> cb) {
        onClickCb = cb;
    }

    // Get the label of the menu item
    std::string label() const {
        return caption;
    }

    // Set the label of the menu item
    void label(std::string s) {
        Fl_Widget::copy_label(s.c_str());
        caption = s;
    }

    // Override the draw method (empty implementation)
    void draw() {}

    // Friend declarations
    friend class Menu;
    friend struct ::AppTest;
};

// Menu class inheriting from Fl_Menu_Bar
class Menu : public Fl_Menu_Bar {
    std::map<int, MenuItem*> items; // Map to store menu items

    // Static handler function for menu item click events
    static void handler(Fl_Widget *sender, void *data) {
        Fl_Menu_Bar *bar = (Fl_Menu_Bar *)sender;
        int index = bar->value();

        Menu *self = (Menu *)data;
        MenuItem *curr = self->items[index];
        if (curr->onClickCb) curr->onClickCb(curr);
    }

    // Helper function to split a string by a delimiter
    std::vector<std::string> split(std::string s, char c = ' ') {
        const char *str = s.c_str();
        std::vector<std::string> result;

        do {
            const char *begin = str;

            while (*str != c && *str)
                str++;

            result.push_back(std::string(begin, str));
        } while (0 != *str++);

        return result;
    }

    // Helper function to add padding to a string
    std::string addPadding(std::string s) {
        std::vector<std::string> tokens = split(s, '/');
        std::string result = tokens[0] + "/";

        for (unsigned long i = 1; i < tokens.size(); i++) {
            result += tokens[i] + "            ";
            if (i < tokens.size() - 1) {
                result += "/";
            }
        }

        return result;
    }

public:
    // Constructor to initialize the menu
    Menu() : Fl_Menu_Bar(0, 0, 0, 0) {
        int pw = ((Fl_Widget *)parent())->w() + 4;
        box(FL_THIN_UP_BOX);
        resize(-2, 0, pw, 25);
    }

    // Add a menu item to the menu
    void addItem(MenuItem *item) {
        int pos = add(addPadding(item->label()).c_str(), 0, handler, this);
        items.insert(std::pair<int, MenuItem*>(pos, item));
    }

    // Add a menu item with a separator to the menu
    void addItemSep(MenuItem *item) {
        int pos = add(addPadding(item->label()).c_str(), 0, handler, this, FL_MENU_DIVIDER);
        items.insert(std::pair<int, MenuItem*>(pos, item));
    }

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif