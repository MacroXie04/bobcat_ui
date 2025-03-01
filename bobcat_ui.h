#ifndef BOBCAT_UI_CORE
#define BOBCAT_UI_CORE

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Tooltip.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_draw.H>
#include <cstddef>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <unistd.h>

// Macro to bind a function to the onShow event of a widget
#define ON_SHOW(WIDGET, FUNCTION) {                                             \
    auto f = std::bind(&FUNCTION, this, std::placeholders::_1);                 \
    WIDGET->onShow(f);                                                          \
}                                                                               \

// Macro to bind a function to the onHide event of a widget
#define ON_HIDE(WIDGET, FUNCTION) {                                             \
    auto f = std::bind(&FUNCTION, this, std::placeholders::_1);                 \
    WIDGET->onHide(f);                                                          \
}                                                                               \

// Macro to bind a function to the willHide event of a widget
#define WILL_HIDE(WIDGET, FUNCTION) {                                           \
    auto f = std::bind(&FUNCTION, this, std::placeholders::_1);                 \
    WIDGET->willHide(f);                                                        \
}                                                                               \

// Macro to bind a function to the onClick event of a widget
#define ON_CLICK(WIDGET, FUNCTION) {                                            \
    auto f = std::bind(&FUNCTION, this, std::placeholders::_1);                 \
    WIDGET->onClick(f);                                                         \
}                                                                               \

// Macro to bind a function to the onEnter event of a widget
#define ON_ENTER(WIDGET, FUNCTION) {                                            \
    auto f = std::bind(&FUNCTION, this, std::placeholders::_1);                 \
    WIDGET->onEnter(f);                                                         \
}                                                                               \

// Macro to bind a function to the onLeave event of a widget
#define ON_LEAVE(WIDGET, FUNCTION) {                                            \
    auto f = std::bind(&FUNCTION, this, std::placeholders::_1);                 \
    WIDGET->onLeave(f);                                                         \
}                                                                               \

// Macro to bind a function to the onChange event of a widget
#define ON_CHANGE(WIDGET, FUNCTION) {                                           \
    auto f = std::bind(&FUNCTION, this, std::placeholders::_1);                 \
    WIDGET->onChange(f);                                                        \
}                                                                               \

// Macro to bind a function to the onDrag event of a widget
#define ON_DRAG(WIDGET, FUNCTION) {                                                                                            \
    auto f = std::bind(&FUNCTION, this, std::placeholders::_1, std::placeholders::_2,  std::placeholders::_3);                 \
    WIDGET->onDrag(f);                                                                                                         \
}                                                                                                                              \

// Macro to bind a function to the onMouseDown event of a widget
#define ON_MOUSE_DOWN(WIDGET, FUNCTION) {                                                                                      \
    auto f = std::bind(&FUNCTION, this, std::placeholders::_1, std::placeholders::_2,  std::placeholders::_3);                 \
    WIDGET->onMouseDown(f);                                                                                                    \
}                                                                                                                              \

// Macro to bind a function to the onMouseUp event of a widget
#define ON_MOUSE_UP(WIDGET, FUNCTION) {                                                                                        \
    auto f = std::bind(&FUNCTION, this, std::placeholders::_1, std::placeholders::_2,  std::placeholders::_3);                 \
    WIDGET->onMouseUp(f);                                                                                                      \
}                                                                                                                              \

// Every Bobcat-UI Component should have this forward declaration
struct AppTest;

namespace bobcat {

    // Enum for theme types
    enum THEME {LIGHT, DARK};

    // Current theme, default is LIGHT
    static THEME currentTheme = LIGHT;

    // Typedef for Fl_Widget
    typedef Fl_Widget Widget;

    // Function to set the theme of the application
    inline void theme(THEME newTheme = LIGHT){
        Fl::visible_focus(0);
        Fl::scheme("gtk+");

        if (newTheme == DARK){
            Fl::background(0x53, 0x53, 0x53);
            Fl::background2(0x3A, 0x3A, 0x3A);
            Fl::foreground(0xFF, 0xFF, 0xFF);
            Fl::set_color(FL_INACTIVE_COLOR, 0x26, 0x26, 0x26);
            Fl::set_color(FL_SELECTION_COLOR, 0xD6, 0xD6, 0xD6);
            Fl_Tooltip::color(fl_rgb_color(0xFF, 0xFF, 0xCC));
            Fl_Tooltip::textcolor(fl_rgb_color(0x00, 0x00, 0x00));
        }
        else if (newTheme == LIGHT){
            Fl::background(0xCE, 0xCE, 0xCE);
            Fl::background2(0xFC, 0xFC, 0xFC);
            Fl::foreground(0x3C, 0x3C, 0x3C);
            Fl::set_color(FL_INACTIVE_COLOR, 0x55, 0x55, 0x55);
            Fl::set_color(FL_SELECTION_COLOR, 32768);
            Fl_Tooltip::color(fl_rgb_color(0x0A, 0x0A, 0x0A));
            Fl_Tooltip::textcolor(fl_rgb_color(0xFF, 0xFF, 0xFF));
            currentTheme = LIGHT;
        }
        
        currentTheme = newTheme;
    
        Fl::reload_scheme();
    }

    // Application class
    class Application_ {
    public:

        // Constructor to set the theme
        Application_() {
            theme();
        }

        // Function to run the application
        int run() const {
            std::cout << "Bobcat UI Application Running..." << std::endl;
            return Fl::run();
        }
    };

    // Function to update color using RGB values (double)
    inline void updateColorRGB(double &r, double &g, double &b){
        Fl::check();
        usleep(10000);
        double rr = r, gg = g, bb = b;
        int result = fl_color_chooser("Select color", rr, gg, bb);
        if (result){
            r = rr;
            g = gg;
            b = bb;
        }
    }
    
    // Function to update color using RGB values (int)
    inline void updateColorRGB(int &r, int &g, int &b){
        Fl::check();
        usleep(10000);
        uchar rr = r, gg = g, bb = b;
        int result = fl_color_chooser("Select color", rr, gg, bb);
        if (result){
            r = rr;
            g = gg;
            b = bb;
        }
    }

    // Function to get text input from the user
    inline std::string textInput(
        std::string prompt, 
        std::string placeholder = "",
        std::string title = "Text Input"
    ){
        std::string result = "";
        fl_message_title(title.c_str());
        const char * temp = fl_input(prompt.c_str(), placeholder.c_str(), 0);
        if (temp != nullptr) result = temp;
        return result;
    }

    // Function to get password input from the user
    inline std::string passwordInput(
        std::string prompt, 
        std::string title = "Password Input"
    ){
        std::string result = "";
        fl_message_title(title.c_str());
        const char * temp = fl_password(prompt.c_str(), "", 0);
        if (temp != nullptr) result = temp;
        return result;
    }

    // Function to wrap text to a specified line length
    inline std::string wordWrap(const std::string& text, unsigned int lineLength) {
        std::stringstream initial(text);
        std::string wrappedText, word, line;
        std::vector<std::string> lines;
        std::string temp;
        while(getline(initial, temp)){
            lines.push_back(temp);
        }
        
        for (size_t i = 0; i < lines.size(); i++){
            std::stringstream ss(lines[i]);
            while (ss >> word) {
                if (line.empty() || line.length() + word.length() + 1 <= lineLength) {
                    line += (line.empty() ? "" : " ") + word;
                } else {
                    wrappedText += line + '\n';
                    line = word;
                }
            }

            if (!line.empty()) {
                wrappedText += line;
            }

            if (i < lines.size()-1){
                wrappedText += "\n";
                line = "";
            }
            
        }

        return wrappedText;
    }

    // Function to show a message to the user
    inline void showMessage(
        std::string message, 
        std::string title = "Message"
    ) {
        Fl::check();
        usleep(10000);
        message = wordWrap(message, 55);
        fl_message_title(title.c_str());
        fl_message(message.c_str(), 0);
    }

    // Function to show a confirmation dialog to the user
    inline int confirm (
        std::string message, 
        std::string positiveBtn = "Yes", 
        std::string negativeBtn = "No", 
        std::string title       = "Confirm"
    ) {
        Fl::check();
        usleep(10000);
        fl_message_title(title.c_str());
        int result = fl_choice_n(
            message.c_str(), 
            negativeBtn.c_str(),
            positiveBtn.c_str(), 
            0,
            0
        );

        return result;
    }
    
    // Function to round a float to a specified precision
    inline std::string roundFloat(float number, int precision = 2) {
        std::stringstream ss;
        ss << std::fixed;
        ss.precision(precision);
        ss << number;
        return ss.str();
    }

}

#endif