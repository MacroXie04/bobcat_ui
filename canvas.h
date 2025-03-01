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
/**
 * @class Canvas_
 * @brief A class representing a canvas that inherits from Fl_Gl_Window.
 * 
 * This class provides a canvas with various callback functions for handling events such as showing, hiding, mouse down, mouse up, and dragging.
 */
class Canvas_ : public Fl_Gl_Window {
    // Callback functions for various events
    std::function<void(bobcat::Widget *)> onShowCb; ///< Callback function for the show event.
    std::function<void(bobcat::Widget *)> onHideCb; ///< Callback function for the hide event.
    std::function<void(bobcat::Widget *)> willHideCb; ///< Callback function for the will hide event.
    std::function<void(bobcat::Widget *, float, float)> onMouseDownCb; ///< Callback function for the mouse down event.
    std::function<void(bobcat::Widget *, float, float)> onDragCb; ///< Callback function for the drag event.
    std::function<void(bobcat::Widget *, float, float)> onMouseUpCb; ///< Callback function for the mouse up event.

    std::string caption; ///< Caption of the canvas.

    // Initialize the callback functions to nullptr
    /**
     * @brief Initializes the callback functions to nullptr.
     */
    void init();

public:
    // Constructor to initialize the canvas with width, height, and title
    /**
     * @brief Constructs a Canvas_ object with the specified width, height, and title.
     * 
     * @param w Width of the canvas.
     * @param h Height of the canvas.
     * @param title Title of the canvas (default is an empty string).
     */
    Canvas_(int w, int h, std::string title = "");

    // Constructor to initialize the canvas with position, width, height, and title
    /**
     * @brief Constructs a Canvas_ object with the specified position, width, height, and title.
     * 
     * @param x X-coordinate of the canvas.
     * @param y Y-coordinate of the canvas.
     * @param w Width of the canvas.
     * @param h Height of the canvas.
     * @param title Title of the canvas (default is an empty string).
     */
    Canvas_(int x, int y, int w, int h, std::string title = "");

    // Pure virtual function to render the canvas
    /**
     * @brief Pure virtual function to render the canvas.
     */
    virtual void render() = 0;

    // Handle events for the canvas
    /**
     * @brief Handles events for the canvas.
     * 
     * @param event The event to handle.
     * @return int The result of the event handling.
     */
    int handle(int event) override;

    // Draw the canvas
    /**
     * @brief Draws the canvas.
     */
    void draw() override;

    // Set the onShow callback function
    /**
     * @brief Sets the onShow callback function.
     * 
     * @param cb The callback function to set.
     */
    void onShow(std::function<void(bobcat::Widget *)> cb);

    // Set the onHide callback function
    /**
     * @brief Sets the onHide callback function.
     * 
     * @param cb The callback function to set.
     */
    void onHide(std::function<void(bobcat::Widget *)> cb);

    // Set the willHide callback function
    /**
     * @brief Sets the willHide callback function.
     * 
     * @param cb The callback function to set.
     */
    void willHide(std::function<void(bobcat::Widget *)> cb);

    // Set the onDrag callback function
    /**
     * @brief Sets the onDrag callback function.
     * 
     * @param cb The callback function to set.
     */
    void onDrag(std::function<void(bobcat::Widget *, float, float)> cb);

    // Set the onMouseDown callback function
    /**
     * @brief Sets the onMouseDown callback function.
     * 
     * @param cb The callback function to set.
     */
    void onMouseDown(std::function<void(bobcat::Widget *, float, float)> cb);

    // Set the onMouseUp callback function
    /**
     * @brief Sets the onMouseUp callback function.
     * 
     * @param cb The callback function to set.
     */
    void onMouseUp(std::function<void(bobcat::Widget *, float, float)> cb);

    // Get the label of the canvas
    /**
     * @brief Gets the label of the canvas.
     * 
     * @return std::string The label of the canvas.
     */
    std::string label() const;

    // Set the label of the canvas
    /**
     * @brief Sets the label of the canvas.
     * 
     * @param s The label to set.
     */
    void label(std::string s);

    // Show the canvas
    /**
     * @brief Shows the canvas.
     */
    void show() override;

    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}
