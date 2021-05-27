#pragma once

#include "gtkmm/buttonbox.h"
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>

class TestButtonBox : public Gtk::Frame {

    public:
        TestButtonBox(const Glib::ustring& title, gint spacing);

        void addButton(Gtk::Button);

    protected:
        Gtk::ButtonBox *bbptr_bbox;
        Gtk::Button button1;

};
