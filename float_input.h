#ifndef BOBCAT_UI_FLOAT_INPUT
#define BOBCAT_UI_FLOAT_INPUT

#include "bobcat_ui.h"

#include <FL/Enumerations.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Input_.H>
#include <FL/Fl_Widget.H>

#include <string>
#include <functional>

// #include <FL/names.h>

namespace bobcat {

// FloatInput class inheriting from Fl_Input
class FloatInput: public Fl_Input{
    std::string caption; // Caption of the float input

    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onClickCb;
    std::function<void(bobcat::Widget *)> onEnterCb;
    std::function<void(bobcat::Widget *)> onLeaveCb;
    std::function<void(bobcat::Widget *)> onChangeCb;

    // Initialize the callback functions to nullptr
    void init(){
        onClickCb = nullptr;
        onEnterCb = nullptr;
        onLeaveCb = nullptr;
        onChangeCb = nullptr;
    }

    // Handle events for the float input
    int handle(int event) {
        // if (event == 8 || event == 9)
        // printf("Event was %s (%d) - %s\n", fl_eventnames[event], event, value());
        int ret = Fl_Input::handle(event);
        if (event == FL_ENTER){
            if (onEnterCb) onEnterCb(this);
        }

        if (event == FL_LEAVE){
            if (onLeaveCb) onLeaveCb(this);
        }

        if (event == FL_RELEASE){
            if (Fl::event_inside(this)){
                if (Fl::focus() == this){
                    if (onClickCb) onClickCb(this);
                }
            }
        }

        return ret;
    }

public:
    // Constructor to initialize the float input with position, size, and caption
    FloatInput(int x, int y, int w, int h, std::string caption = ""): Fl_Input(x, y, w, h, caption.c_str()) {
        init();
        align(FL_ALIGN_TOP_LEFT);
        this->caption = caption;
        Fl_Input::copy_label(caption.c_str());
        input_type(FL_FLOAT_INPUT);
    }

    // Get the label of the float input
    std::string label() const {
        return caption;
    }

    // Set the label of the float input
    void label(std::string s){
        Fl_Input::copy_label(s.c_str());
        caption = s;
    }

    // Get the value of the float input as a float
    float value() const {
        float temp = std::stof(Fl_Input::value());
        return temp;
    }

    // Check if the float input is empty
    bool empty() {
        std::string value = Fl_Input::value();
        if (value.empty()) return true;
        return false;
    }

    // Clear the value of the float input
    void clear(){
        Fl_Input::value("");
        if (onChangeCb) onChangeCb(this);
    }

    // Set the value of the float input
    void value(float v){
        Fl_Input::value(std::to_string(v).c_str());
        if (onChangeCb) onChangeCb(this);
    }

    // Set the onClick callback function
    void onClick(std::function<void(bobcat::Widget *)> cb){
        onClickCb = cb;
    }

    // Set the onEnter callback function
    void onEnter(std::function<void(bobcat::Widget *)> cb){
        onEnterCb = cb;
    }

    // Set the onLeave callback function
    void onLeave(std::function<void(bobcat::Widget *)> cb){
        onLeaveCb = cb;
    }

    // Set the onChange callback function
    void onChange(std::function<void(bobcat::Widget *)> cb){
        onChangeCb = cb;
        when(FL_WHEN_CHANGED);
        callback([](bobcat::Widget* sender, void* self){
            FloatInput *in = (FloatInput*) self;
            in->onChangeCb(in);
        }, this);
    }

    // Set the alignment of the float input
    void align(Fl_Align alignment){
        Fl_Input::align(alignment);
        parent()->redraw();
    }

    // Get the label size of the float input
    Fl_Fontsize labelsize() {
        return Fl_Input::labelsize();
    }

    // Set the label size of the float input
    void labelsize(Fl_Fontsize pix) {
        Fl_Input::labelsize(pix);
        parent()->redraw();
    }

    // Get the label color of the float input
    Fl_Color labelcolor() {
        return Fl_Input::labelcolor();
    }

    // Set the label color of the float input
    void labelcolor(Fl_Color color) {
        Fl_Input::labelcolor(color);
        parent()->redraw();
    }

    // Get the label font of the float input
    Fl_Font labelfont() {
        return Fl_Input::labelfont();
    }

    // Set the label font of the float input
    void labelfont(Fl_Font f) {
        Fl_Input::labelfont(f);
        parent()->redraw();
    }

    // Set the focus to the float input
    void take_focus() {
         Fl_Input::take_focus();
    }

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif