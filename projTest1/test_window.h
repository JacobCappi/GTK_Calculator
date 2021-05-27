#pragma once

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/frame.h>

// Using this webpage to learn basic syntax
//https://developer.gnome.org/gtkmm-tutorial/3.24/sec-multi-item-containers.html.en


class TestWindow : public Gtk::Window
{
    public:
        TestWindow();
        virtual ~TestWindow();

    protected:
        void on_button_clicked();

        Gtk::Frame m_Frame_Main; // Frame to hold the boxes
        Gtk::Box m_Vbox; // vertical box

};
