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

/**
 * @class FloatInput
 * @brief A class representing a float input widget, inheriting from Fl_Input.
 */
class FloatInput: public Fl_Input {
    std::string caption; ///< Caption of the float input

    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onClickCb; ///< Callback for click event
    std::function<void(bobcat::Widget *)> onEnterCb; ///< Callback for enter event
    std::function<void(bobcat::Widget *)> onLeaveCb; ///< Callback for leave event
    std::function<void(bobcat::Widget *)> onChangeCb; ///< Callback for change event

    /**
     * @brief Initialize the callback functions to nullptr.
     */
    void init();

    /**
     * @brief Handle events for the float input.
     * @param event The event to handle.
     * @return int The result of the event handling.
     */
    int handle(int event);

public:
    /**
     * @brief Constructor to initialize the float input with position, size, and caption.
     * @param x The x position of the float input.
     * @param y The y position of the float input.
     * @param w The width of the float input.
     * @param h The height of the float input.
     * @param caption The caption of the float input.
     */
    FloatInput(int x, int y, int w, int h, std::string caption = "");

    /**
     * @brief Get the label of the float input.
     * @return std::string The label of the float input.
     */
    std::string label() const;

    /**
     * @brief Set the label of the float input.
     * @param s The new label of the float input.
     */
    void label(std::string s);

    /**
     * @brief Get the value of the float input as a float.
     * @return float The value of the float input.
     */
    float value() const;

    /**
     * @brief Check if the float input is empty.
     * @return bool True if the float input is empty, false otherwise.
     */
    bool empty();

    /**
     * @brief Clear the value of the float input.
     */
    void clear();

    /**
     * @brief Set the value of the float input.
     * @param v The new value of the float input.
     */
    void value(float v);

    /**
     * @brief Set the onClick callback function.
     * @param cb The callback function to set.
     */
    void onClick(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the onEnter callback function.
     * @param cb The callback function to set.
     */
    void onEnter(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the onLeave callback function.
     * @param cb The callback function to set.
     */
    void onLeave(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the onChange callback function.
     * @param cb The callback function to set.
     */
    void onChange(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the alignment of the float input.
     * @param alignment The alignment to set.
     */
    void align(Fl_Align alignment);

    /**
     * @brief Get the label size of the float input.
     * @return Fl_Fontsize The label size of the float input.
     */
    Fl_Fontsize labelsize();

    /**
     * @brief Set the label size of the float input.
     * @param pix The new label size of the float input.
     */
    void labelsize(Fl_Fontsize pix);

    /**
     * @brief Get the label color of the float input.
     * @return Fl_Color The label color of the float input.
     */
    Fl_Color labelcolor();

    /**
     * @brief Set the label color of the float input.
     * @param color The new label color of the float input.
     */
    void labelcolor(Fl_Color color);

    /**
     * @brief Get the label font of the float input.
     * @return Fl_Font The label font of the float input.
     */
    Fl_Font labelfont();

    /**
     * @brief Set the label font of the float input.
     * @param f The new label font of the float input.
     */
    void labelfont(Fl_Font f);

    /**
     * @brief Set the focus to the float input.
     */
    void take_focus();

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}
