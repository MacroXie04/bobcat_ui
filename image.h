#ifndef BOBCAT_UI_IMAGE
#define BOBCAT_UI_IMAGE

#include "textbox.h"
#include <FL/Fl_PNG_Image.H>
#include <string>
#include <iostream>

namespace bobcat {

// Image class inheriting from TextBox
class Image : public TextBox {
    Fl_PNG_Image *original; // Original image
    Fl_PNG_Image *img; // Current image
    std::string fname; // Filename of the image

public:
    // Constructor to initialize the image with position, size, filename, and title
    Image(int x, int y, int w, int h, std::string filename, std::string title = "" ) : TextBox(x, y, w, h, title.c_str()) {
        align(FL_ALIGN_CENTER);
        fname = filename;
        original = new Fl_PNG_Image(filename.c_str());

        img = (Fl_PNG_Image*)original->copy();

        Fl_Image *temp;
        if (img->w() > img->h()) {
            temp = img->copy(Fl_Box::w(), Fl_Box::h() * img->h() / img->w());
        } else {
            temp = img->copy(Fl_Box::w() * img->w() / img->h(), Fl_Box::h());
        }
        delete img;
        img = (Fl_PNG_Image *)temp;

        image(img);

        Fl_Box::align(FL_ALIGN_IMAGE_MASK);
    }

    // Increase the size of the image
    void increase(int amount = 10) {
        hide();
        w(w() + amount);
        h(h() + amount);

        delete img;
        img = (Fl_PNG_Image*)original->copy();

        Fl_Image *temp;
        if (img->w() > img->h()) {
            temp = img->copy(Fl_Box::w(), Fl_Box::h() * img->h() / img->w());
        } else {
            temp = img->copy(Fl_Box::w() * img->w() / img->h(), Fl_Box::h());
        }
        delete img;
        img = (Fl_PNG_Image *)temp;
        image(img);
        show();
    }

    // Decrease the size of the image
    void decrease(int amount = 10) {
        hide();
        w(w() - amount);
        h(h() - amount);

        delete img;
        img = new Fl_PNG_Image(fname.c_str());

        Fl_Image *temp;
        if (img->w() > img->h()) {
            temp = img->copy(Fl_Box::w(), Fl_Box::h() * img->h() / img->w());
        } else {
            temp = img->copy(Fl_Box::w() * img->w() / img->h(), Fl_Box::h());
        }
        delete img;
        img = (Fl_PNG_Image *)temp;
        image(img);
        show();
    }

    // Move the image to the left
    void moveLeft(int amount = 10) {
        hide();
        x(x() - amount);
        show();
    }

    // Move the image to the right
    void moveRight(int amount = 10) {
        hide();
        x(x() + amount);
        show();
    }

    // Set a new image
    void setImage(std::string filename) {
        delete original;
        fname = filename;
        original = new Fl_PNG_Image(filename.c_str());
        img = (Fl_PNG_Image*)original->copy();

        Fl_Image *temp;
        if (img->w() > img->h()) {
            temp = img->copy(Fl_Box::w(), Fl_Box::h() * img->h() / img->w());
        } else {
            temp = img->copy(Fl_Box::w() * img->w() / img->h(), Fl_Box::h());
        }
        delete img;
        img = (Fl_PNG_Image *)temp;
        hide();
        image(img);
        redraw();
        show();
    }

    // Set the alignment of the image
    void align(Fl_Align alignment) {
        Fl_Box::align(alignment);
        parent()->redraw();
    }

    // Get the label size of the image
    Fl_Fontsize labelsize() {
        return Fl_Box::labelsize();
    }

    // Set the label size of the image
    void labelsize(Fl_Fontsize pix) {
        Fl_Box::labelsize(pix);
        parent()->redraw();
    }

    // Get the label color of the image
    Fl_Color labelcolor() {
        return Fl_Box::labelcolor();
    }

    // Set the label color of the image
    void labelcolor(Fl_Color color) {
        Fl_Box::labelcolor(color);
        parent()->redraw();
    }

    // Get the label font of the image
    Fl_Font labelfont() {
        return Fl_Box::labelfont();
    }

    // Set the label font of the image
    void labelfont(Fl_Font f) {
        Fl_Box::labelfont(f);
        parent()->redraw();
    }
    
    // Friend declaration for AppTest struct
    friend struct ::AppTest;
};

}

#endif