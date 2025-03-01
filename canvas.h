#ifndef BOBCAT_UI_CANVAS
#define BOBCAT_UI_CANVAS

#include "bobcat_ui.h"
#include <FL/Enumerations.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_PNG_Image.H>
#include <GL/gl.h>
#include <string>
#include <functional>

namespace bobcat {

// Canvas class inheriting from Fl_Gl_Window
class Canvas_ : public Fl_Gl_Window {
    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onShowCb;
    std::function<void(bobcat::Widget *)> onHideCb;
    std::function<void(bobcat::Widget *)> willHideCb;
    std::function<void(bobcat::Widget *, float, float)> onMouseDownCb;
    std::function<void(bobcat::Widget *, float, float)> onDragCb;
    std::function<void(bobcat::Widget *, float, float)> onMouseUpCb;

    std::string caption; // Caption of the canvas

    // Initialize the callback functions to nullptr
    void init() {
        onShowCb = nullptr;
        onHideCb = nullptr;
        willHideCb = nullptr;
        onDragCb = nullptr;
        onMouseDownCb = nullptr;
        onDragCb = nullptr;
        onMouseUpCb = nullptr;
    }

public:
    // Constructor to initialize the canvas with width, height, and title
    Canvas_(int w, int h, std::string title = "") : Fl_Gl_Window(w, h, title.c_str()) {
        init(); 
        caption = title; 
        Fl_Gl_Window::copy_label(title.c_str());
    }

    // Constructor to initialize the canvas with position, width, height, and title
    Canvas_(int x, int y, int w, int h, std::string title = "") : Fl_Gl_Window(x, y, w, h, title.c_str()) {
        init(); 
        caption = title;
        Fl_Gl_Window::copy_label(title.c_str());
    }

    // Pure virtual function to render the canvas
    virtual void render() = 0;

    // Handle events for the canvas
    int handle(int event) override {
        // printf("Event was %s - %d\n", fl_eventnames[event], event);
        int ret = Fl_Gl_Window::handle(event);

        if (event == FL_SHOW) {
            if (onShowCb) onShowCb(this);
        }
        if (event == FL_HIDE) {
            if (onHideCb) onHideCb(this);
        }

        for (int i = 0; i < children(); i++) {
            if (Fl::event_inside(child(i))) {
                return 0;
            }
        }

        // if (event == FL_PUSH){
        //     Fl::focus(this);
        // }

        float x = (2.0f * (Fl::event_x() / float(w()))) - 1.0f;
        float y = 1.0f - (2.0f * (Fl::event_y() / float(h())));

        if (x >= -1.0 && x <= 1.0 && y >= -1.0 && y <= 1.0) {
            if (event == FL_RELEASE) {
                if (onMouseUpCb) onMouseUpCb(this, x, y);
            }
            if (event == FL_PUSH) {
                if (onMouseDownCb) onMouseDownCb(this, x, y);
                return 1;
            }
            if (event == FL_DRAG) {
                if (onDragCb) onDragCb(this, x, y);
            }
        }

        return ret;
    }

    // Draw the canvas
    void draw() override {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_POINT_SMOOTH);
        glPointSize(7.0f);
        glColor3f(0.0f, 0.0f, 0.0f);

        render();

        swap_buffers();
    }

    // Set the onShow callback function
    void onShow(std::function<void(bobcat::Widget *)> cb) {
        onShowCb = cb;
    }

    // Set the onHide callback function
    void onHide(std::function<void(bobcat::Widget *)> cb) {
        onHideCb = cb;
    }

    // Set the willHide callback function
    void willHide(std::function<void(bobcat::Widget *)> cb) {
        willHideCb = cb;
        callback([](bobcat::Widget * sender, void *self) {
            Canvas_ *win = (Canvas_ *)self;
            win->willHideCb(win);
        }, this);   
    }

    // Set the onDrag callback function
    void onDrag(std::function<void(bobcat::Widget *, float, float)> cb) {
        onDragCb = cb;
    }

    // Set the onMouseDown callback function
    void onMouseDown(std::function<void(bobcat::Widget *, float, float)> cb) {
        onMouseDownCb = cb;
    }

    // Set the onMouseUp callback function
    void onMouseUp(std::function<void(bobcat::Widget *, float, float)> cb) {
        onMouseUpCb = cb;
    }

    // Get the label of the canvas
    std::string label() const {
        return caption;
    }

    // Set the label of the canvas
    void label(std::string s) {
        Fl_Gl_Window::copy_label(s.c_str());
        caption = s;
    }

    // Show the canvas
    void show() override {
        Fl_Gl_Window::show();
        wait_for_expose();          // Supposedly makes show() synchronous
        Fl::flush();                // Make sure to draw what needs to be drawn
    }

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif