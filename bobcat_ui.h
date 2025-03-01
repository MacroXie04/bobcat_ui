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

    /**
     * @brief Sets the theme of the application.
     * 
     * @param newTheme The new theme to set. Default is LIGHT.
     */
    inline void theme(THEME newTheme = LIGHT);

    // Application class
    class Application_ {
    public:
        /**
         * @brief Constructor to set the theme.
         */
        Application_();

        /**
         * @brief Runs the application.
         * 
         * @return int The exit status of the application.
         */
        int run() const;
    };

    /**
     * @brief Updates the color using RGB values (double).
     * 
     * @param r Red component (double).
     * @param g Green component (double).
     * @param b Blue component (double).
     */
    inline void updateColorRGB(double &r, double &g, double &b);

    /**
     * @brief Updates the color using RGB values (int).
     * 
     * @param r Red component (int).
     * @param g Green component (int).
     * @param b Blue component (int).
     */
    inline void updateColorRGB(int &r, int &g, int &b);

    /**
     * @brief Gets text input from the user.
     * 
     * @param prompt The prompt message.
     * @param placeholder The placeholder text. Default is an empty string.
     * @param title The title of the input dialog. Default is "Text Input".
     * @return std::string The user input.
     */
    inline std::string textInput(
        std::string prompt, 
        std::string placeholder = "",
        std::string title = "Text Input"
    );

    /**
     * @brief Gets password input from the user.
     * 
     * @param prompt The prompt message.
     * @param title The title of the input dialog. Default is "Password Input".
     * @return std::string The user input.
     */
    inline std::string passwordInput(
        std::string prompt, 
        std::string title = "Password Input"
    );

    /**
     * @brief Wraps text to a specified line length.
     * 
     * @param text The text to wrap.
     * @param lineLength The maximum line length.
     * @return std::string The wrapped text.
     */
    inline std::string wordWrap(const std::string& text, unsigned int lineLength);

    /**
     * @brief Shows a message to the user.
     * 
     * @param message The message to show.
     * @param title The title of the message dialog. Default is "Message".
     */
    inline void showMessage(
        std::string message, 
        std::string title = "Message"
    );

    /**
     * @brief Shows a confirmation dialog to the user.
     * 
     * @param message The message to show.
     * @param positiveBtn The text for the positive button. Default is "Yes".
     * @param negativeBtn The text for the negative button. Default is "No".
     * @param title The title of the confirmation dialog. Default is "Confirm".
     * @return int The user's choice (0 for negative, 1 for positive).
     */
    inline int confirm (
        std::string message, 
        std::string positiveBtn = "Yes", 
        std::string negativeBtn = "No", 
        std::string title       = "Confirm"
    );

    /**
     * @brief Rounds a float to a specified precision.
     * 
     * @param number The number to round.
     * @param precision The number of decimal places. Default is 2.
     * @return std::string The rounded number as a string.
     */
    inline std::string roundFloat(float number, int precision = 2);

}
