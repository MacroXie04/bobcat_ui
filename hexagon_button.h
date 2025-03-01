#ifndef BOBCAT_UI_HEXAGON_BUTTON
#define BOBCAT_UI_HEXAGON_BUTTON

#include "bobcat_ui.h"
#include <FL/Enumerations.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Light_Button.H>
#include <FL/fl_draw.H>
#include <cmath>

#include <FL/Fl_Button.H>

#include <string>
#include <functional>


namespace bobcat {

/**
 * @class HexagonButton
 * @brief A custom button class that draws a hexagon shape and handles various events.

// HexagonButton class inheriting from Fl_Button
class HexagonButton: public Fl_Button{
    std::string caption; // Caption of the hexagon button

    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onClickCb;
    std::function<void(bobcat::Widget *)> onEnterCb;
    std::function<void(bobcat::Widget *)> onLeaveCb;

    // Initialize the callback functions to nullptr
    void init(){
        onClickCb = nullptr;
        onEnterCb = nullptr;
        onLeaveCb = nullptr;
    }

    // Handle events for the hexagon button
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

    // Draw the hexagon shape
    void draw_hexagon(int x, int y, int w, int h) {
        fl_color(Fl_Button::color());
        fl_begin_polygon();
        for (int i = 0; i < 6; ++i) {
            double angle = M_PI / 3 * i;
            int px = x + w / 2 + (w / 2) * cos(angle);
            int py = y + h / 2 + (h / 2) * sin(angle);
            fl_vertex(px, py);
        }
        fl_end_polygon();

        // Draw the border
        fl_color(Fl_Button::labelcolor());
        fl_begin_line();
        for (int i = 0; i <= 6; ++i) {
            double angle = M_PI / 3 * i;
            int px = x + w / 2 + (w / 2) * cos(angle);
            int py = y + h / 2 + (h / 2) * sin(angle);
            fl_vertex(px, py);
        }
        fl_end_line();
    }

public:
    // Constructor to initialize the hexagon button with position, size, and caption
    HexagonButton(int x, int y, int w, int h, std::string caption = ""): Fl_Button(x, y, w, h, caption.c_str()) {
        init();
        this->caption = caption;
        Fl_Button::copy_label(caption.c_str());
    }

    // Override the draw method to draw the hexagon button
    void draw() override {
        draw_hexagon(x(), y(), w(), h());

        // Draw the label
        fl_font(Fl_Button::labelfont(), 28);
        align(Fl_Button::align());
        fl_draw(label().c_str(), x() + (w() / 2) - 9, y() + (h() / 2) + 9);
    }

    // Get the label of the hexagon button
    std::string label() const {
        return caption;
    }

    // Set the label of the hexagon button
    void label(std::string s){
        Fl_Button::copy_label(s.c_str());
        caption = s;
    }

    // Set the onClick callback function
    void onClick(std::function<void(bobcat::Widget *)> cb){
        onClickCb = cb;
        callback([](bobcat::Widget* sender, void* self){
            HexagonButton* butt = (HexagonButton*) self;
            butt->onClickCb(butt);
        }, this);
    }

    // Set the onEnter callback function
    void onEnter(std::function<void(bobcat::Widget *)> cb){
        onEnterCb = cb;
    }

    // Set the onLeave callback function
    void onLeave(std::function<void(bobcat::Widget *)> cb){
        onLeaveCb = cb;
    }

    // Set the alignment of the hexagon button
    void align(Fl_Align alignment){
        Fl_Button::align(alignment);
        parent()->redraw();
    }

    // Get the label size of the hexagon button
    Fl_Fontsize labelsize() {
        return Fl_Button::labelsize();
    }

    // Set the label size of the hexagon button
    void labelsize(Fl_Fontsize pix) {
        Fl_Button::labelsize(pix);
        parent()->redraw();
    }

    // Get the label color of the hexagon button
    Fl_Color labelcolor() {
        return Fl_Button::labelcolor();
    }

    // Set the label color of the hexagon button
    void labelcolor(Fl_Color color) {
        Fl_Button::labelcolor(color);
        parent()->redraw();
    }

    // Get the label font of the hexagon button
    Fl_Font labelfont() {
        return Fl_Button::labelfont();
    }

    // Set the label font of the hexagon button
    void labelfont(Fl_Font f) {
        Fl_Button::labelfont(f);
        parent()->redraw();
    }

    // Set the focus to the hexagon button
    void take_focus() {
        Fl_Button::take_focus();
    }

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif