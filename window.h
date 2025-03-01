#ifndef BOBCAT_UI_WINDOW
#define BOBCAT_UI_WINDOW

#include "bobcat_ui.h"

#include <FL/Enumerations.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_PNG_Image.H>

#include <string>
#include <functional>

// #include <FL/names.h>

namespace bobcat {

// Window class inheriting from Fl_Double_Window
class Window : public Fl_Double_Window {
    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onShowCb;
    std::function<void(bobcat::Widget *)> onHideCb;
    std::function<void(bobcat::Widget *)> onClickCb;
    std::function<void(bobcat::Widget *)> willHideCb;

    std::string caption; // Caption of the window

    Fl_PNG_Image *icon_data; // Icon data for the window

    // Initialize the callback functions to nullptr and set the icon
    void init(){
        onShowCb = nullptr;
        onHideCb = nullptr;
        onClickCb = nullptr;
        willHideCb = nullptr;
        icon_data = new Fl_PNG_Image("/usr/share/icons/big_m.png");

        icon(icon_data);
    }

public:
    // Constructor to initialize the window with width, height, and title
    Window(int w, int h, std::string title = "") : Fl_Double_Window(w, h, title.c_str()) { 
        init(); 
        caption = title; 
        Fl_Double_Window::copy_label(title.c_str());
    }

    // Constructor to initialize the window with position, width, height, and title
    Window(int x, int y, int w, int h, std::string title = "") : Fl_Double_Window(x, y, w, h, title.c_str()) { 
        init(); 
        caption = title;
        Fl_Double_Window::copy_label(title.c_str());
    }

    // Handle events for the window
    int handle(int event) {
        // printf("Event was %s - %d\n", fl_eventnames[event], event);
        int ret = Fl_Double_Window::handle(event);

        if (event == FL_SHOW){
            if (onShowCb) onShowCb(this);
        }
        if (event == FL_HIDE){
            if (onHideCb) onHideCb(this);
        }


        for (int i = 0; i < children(); i++){
            if (Fl::event_inside(child(i))){
                return 0;
            }
        }

        if (event == FL_PUSH){
            Fl::focus(this);
        }

        if (event == FL_RELEASE){
            if (Fl::focus() == this){
                if (onClickCb) onClickCb(this);
            }
        }

        return ret;
    }

    // Set the onShow callback function
    void onShow(std::function<void(bobcat::Widget *)> cb){
        onShowCb = cb;
    }

    // Set the onHide callback function
    void onHide(std::function<void(bobcat::Widget *)> cb){
        onHideCb = cb;
    }

    // Set the willHide callback function
    void willHide(std::function<void(bobcat::Widget *)> cb){
        willHideCb = cb;
        callback([](bobcat::Widget * sender, void *self){
            Window *win = (Window *)self;
            win->willHideCb(win);
        }, this);   
    }

    // Set the onClick callback function
    void onClick(std::function<void(bobcat::Widget *)> cb){
        onClickCb = cb;
    }

    // Get the label of the window
    std::string label() const {
        return caption;
    }

    // Set the label of the window
    void label(std::string s){
        Fl_Double_Window::copy_label(s.c_str());
        caption = s;
    }

    // Show the window
    void show(){
        Fl_Double_Window::show();
        wait_for_expose();          // Supposedly makes show() synchronous
        Fl::flush();                // Make sure to draw what needs to be drawn
    }

    // Destructor to delete the icon data
    ~Window(){
        delete icon_data;
    }

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};



}

#endif