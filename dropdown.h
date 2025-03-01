#ifndef BOBCAT_UI_DROPDOWN
#define BOBCAT_UI_DROPDOWN

#include "bobcat_ui.h"

#include <FL/Enumerations.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Widget.H>

#include <string>
#include <functional>

// #include <FL/names.h>

/**
 * @file dropdown.h
 * @namespace bobcat
 * @class Dropdown
 * @brief A custom dropdown class inheriting from Fl_Choice with additional functionalities.
 *
 * This class provides a dropdown widget with additional callback functionalities for various events.
 */

/**
 * @brief Constructor to initialize the dropdown with position, size, and caption.
 * @param x The x-coordinate of the dropdown.
 * @param y The y-coordinate of the dropdown.
 * @param w The width of the dropdown.
 * @param h The height of the dropdown.
 * @param caption The caption of the dropdown (default is an empty string).
 */

/**
 * @brief Get the label of the dropdown.
 * @return The label of the dropdown as a std::string.
 */

/**
 * @brief Set the label of the dropdown.
 * @param s The new label for the dropdown.
 */

/**
 * @brief Get the text of the selected item.
 * @return The text of the selected item as a std::string.
 */

/**
 * @brief Add an item to the dropdown.
 * @param item The item to be added to the dropdown.
 * @return The index of the added item.
 */

/**
 * @brief Set the selected item by index.
 * @param index The index of the item to be selected.
 */

/**
 * @brief Set the selected item by text.
 * @param s The text of the item to be selected.
 */

/**
 * @brief Get the index of the selected item.
 * @return The index of the selected item.
 */

/**
 * @brief Remove an item by index.
 * @param i The index of the item to be removed.
 */

/**
 * @brief Remove an item by text.
 * @param s The text of the item to be removed.
 */

/**
 * @brief Set the onEnter callback function.
 * @param cb The callback function to be called when the mouse enters the dropdown.
 */

/**
 * @brief Set the onLeave callback function.
 * @param cb The callback function to be called when the mouse leaves the dropdown.
 */

/**
 * @brief Set the onChange callback function.
 * @param cb The callback function to be called when the selected item changes.
 */

/**
 * @brief Set the alignment of the dropdown.
 * @param alignment The alignment to be set for the dropdown.
 */

/**
 * @brief Get the label size of the dropdown.
 * @return The label size of the dropdown.
 */

/**
 * @brief Set the label size of the dropdown.
 * @param pix The new label size for the dropdown.
 */

/**
 * @brief Get the label color of the dropdown.
 * @return The label color of the dropdown.
 */

/**
 * @brief Set the label color of the dropdown.
 * @param color The new label color for the dropdown.
 */

/**
 * @brief Get the label font of the dropdown.
 * @return The label font of the dropdown.
 */

/**
 * @brief Set the label font of the dropdown.
 * @param f The new label font for the dropdown.
 */

/**
 * @brief Set the focus to the dropdown.
 */
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