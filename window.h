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

/**
 * @class Window
 * @brief A class representing a window in the bobcat UI framework, inheriting from Fl_Double_Window.
 */
class Window : public Fl_Double_Window {
    /**
     * @brief Callback function for the show event.
     */
    std::function<void(bobcat::Widget *)> onShowCb;

    /**
     * @brief Callback function for the hide event.
     */
    std::function<void(bobcat::Widget *)> onHideCb;

    /**
     * @brief Callback function for the click event.
     */
    std::function<void(bobcat::Widget *)> onClickCb;

    /**
     * @brief Callback function for the will hide event.
     */
    std::function<void(bobcat::Widget *)> willHideCb;

    /**
     * @brief Caption of the window.
     */
    std::string caption;

    /**
     * @brief Icon data for the window.
     */
    Fl_PNG_Image *icon_data;

    /**
     * @brief Initialize the callback functions to nullptr and set the icon.
     */
    void init();

public:
    /**
     * @brief Constructor to initialize the window with width, height, and title.
     * @param w Width of the window.
     * @param h Height of the window.
     * @param title Title of the window (optional).
     */
    Window(int w, int h, std::string title = "");

    /**
     * @brief Constructor to initialize the window with position, width, height, and title.
     * @param x X position of the window.
     * @param y Y position of the window.
     * @param w Width of the window.
     * @param h Height of the window.
     * @param title Title of the window (optional).
     */
    Window(int x, int y, int w, int h, std::string title = "");

    /**
     * @brief Handle events for the window.
     * @param event The event to handle.
     * @return int The result of the event handling.
     */
    int handle(int event);

    /**
     * @brief Set the onShow callback function.
     * @param cb The callback function to set.
     */
    void onShow(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the onHide callback function.
     * @param cb The callback function to set.
     */
    void onHide(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the willHide callback function.
     * @param cb The callback function to set.
     */
    void willHide(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Set the onClick callback function.
     * @param cb The callback function to set.
     */
    void onClick(std::function<void(bobcat::Widget *)> cb);

    /**
     * @brief Get the label of the window.
     * @return std::string The label of the window.
     */
    std::string label() const;

    /**
     * @brief Set the label of the window.
     * @param s The new label to set.
     */
    void label(std::string s);

    /**
     * @brief Show the window.
     */
    void show();

    /**
     * @brief Destructor to delete the icon data.
     */
    ~Window();

    /**
     * @brief Friend declaration for AppTest struct.
     */
    friend struct ::AppTest;
};

}
