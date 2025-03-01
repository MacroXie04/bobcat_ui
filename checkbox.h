#ifndef BOBCAT_UI_CHECKBOX
#define BOBCAT_UI_CHECKBOX

#include "bobcat_ui.h"
#include <FL/Fl_Check_Button.H>
#include <string>
#include <functional>

namespace bobcat {

/**
 * @class Checkbox
 * @brief A custom checkbox widget inheriting from Fl_Check_Button.
 * 
 * This class provides a checkbox widget with additional callback functionalities
 * for various events such as click, enter, leave, and change.
 */
class Checkbox: public Fl_Check_Button {
    std::string caption; ///< Caption of the checkbox

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
     * @brief Handle events for the checkbox.
     * 
     * @param event The event to handle.
     * @return int The result of the event handling.
     */
    int handle(int event);

public:
    /**
     * @brief Constructor to initialize the checkbox with position, size, and caption.
     * 
     * @param x The x position of the checkbox.
     * @param y The y position of the checkbox.
     * @param w The width of the checkbox.
     * @param h The height of the checkbox.
     * @param caption The caption of the checkbox.
     */
    Checkbox(int x, int y, int w, int h, std::string caption = "");

    /**
     * @brief Get the label of the checkbox.
     * 
     * @return std::string The label of the checkbox.
     */
    std::string label() const;

    /**
     * @brief Set the label of the checkbox.
     * 
     * @param s The new label of the checkbox.
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
     * @brief Check if the checkbox is checked.
     * 
     * @return bool True if the checkbox is checked, false otherwise.
     */
    bool checked() const;

    /**
     * @brief Check the checkbox.
     */
    void check();

    /**
     * @brief Uncheck the checkbox.
     */
    void uncheck();

    /**
     * @brief Set the onChange callback function.
     * 
     * @param cb The callback function to be called on change event.
     */
    void onChange(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the alignment of the checkbox.
     * 
     * @param alignment The alignment to set.
     */
    void align(Fl_Align alignment);

    /**
     * @brief Get the label size of the checkbox.
     * 
     * @return Fl_Fontsize The label size of the checkbox.
     */
    Fl_Fontsize labelsize();

    /**
     * @brief Set the label size of the checkbox.
     * 
     * @param pix The new label size in pixels.
     */
    void labelsize(Fl_Fontsize pix);

    /**
     * @brief Get the label color of the checkbox.
     * 
     * @return Fl_Color The label color of the checkbox.
     */
    Fl_Color labelcolor();

    /**
     * @brief Set the label color of the checkbox.
     * 
     * @param color The new label color.
     */
    void labelcolor(Fl_Color color);

    /**
     * @brief Get the label font of the checkbox.
     * 
     * @return Fl_Font The label font of the checkbox.
     */
    Fl_Font labelfont();

    /**
     * @brief Set the label font of the checkbox.
     * 
     * @param f The new label font.
     */
    void labelfont(Fl_Font f);

    /**
     * @brief Set the focus to the checkbox.
     */
    void take_focus();

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif