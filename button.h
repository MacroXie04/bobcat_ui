#ifndef BOBCAT_UI_BUTTON
#define BOBCAT_UI_BUTTON

#include "bobcat_ui.h"
#include <FL/Fl_Button.H>
#include <string>
#include <functional>

namespace bobcat {

/**
 * @class Button
 * @brief A custom button class inheriting from Fl_Button.
 * 
 * This class provides additional functionality for handling button events
 * such as click, enter, and leave. It also allows setting and getting various
 * button properties like label, alignment, label size, label color, and label font.
 */
class Button: public Fl_Button {
    std::string caption; ///< Caption of the button

    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onClickCb; ///< Callback for click event
    std::function<void(bobcat::Widget *)> onEnterCb; ///< Callback for enter event
    std::function<void(bobcat::Widget *)> onLeaveCb; ///< Callback for leave event

    /**
     * @brief Initialize the callback functions to nullptr.
     */
    void init();

    /**
     * @brief Handle events for the button.
     * 
     * @param event The event to handle.
     * @return int The result of the event handling.
     */
    int handle(int event);

public:
    /**
     * @brief Constructor to initialize the button with position, size, and caption.
     * 
     * @param x The x-coordinate of the button.
     * @param y The y-coordinate of the button.
     * @param w The width of the button.
     * @param h The height of the button.
     * @param caption The caption of the button (default is an empty string).
     */
    Button(int x, int y, int w, int h, std::string caption = "");

    /**
     * @brief Get the label of the button.
     * 
     * @return std::string The label of the button.
     */
    std::string label() const;

    /**
     * @brief Set the label of the button.
     * 
     * @param s The new label of the button.
     */
    void label(std::string s);

    /**
     * @brief Set the onClick callback function.
     * 
     * @param cb The callback function to be called on click event.
     */
    void onClick(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the onEnter callback function.
     * 
     * @param cb The callback function to be called on enter event.
     */
    void onEnter(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the onLeave callback function.
     * 
     * @param cb The callback function to be called on leave event.
     */
    void onLeave(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the alignment of the button.
     * 
     * @param alignment The alignment to set.
     */
    void align(Fl_Align alignment);

    /**
     * @brief Get the label size of the button.
     * 
     * @return Fl_Fontsize The label size of the button.
     */
    Fl_Fontsize labelsize();

    /**
     * @brief Set the label size of the button.
     * 
     * @param pix The new label size in pixels.
     */
    void labelsize(Fl_Fontsize pix);

    /**
     * @brief Get the label color of the button.
     * 
     * @return Fl_Color The label color of the button.
     */
    Fl_Color labelcolor();

    /**
     * @brief Set the label color of the button.
     * 
     * @param color The new label color.
     */
    void labelcolor(Fl_Color color);

    /**
     * @brief Get the label font of the button.
     * 
     * @return Fl_Font The label font of the button.
     */
    Fl_Font labelfont();

    /**
     * @brief Set the label font of the button.
     * 
     * @param f The new label font.
     */
    void labelfont(Fl_Font f);

    /**
     * @brief Set the focus to the button.
     */
    void take_focus();

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif