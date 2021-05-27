#include "test_button_box.h"
#include "glibmm/ustring.h"
#include "gtkmm/enums.h"
#include "gtkmm/messagedialog.h"
#include "gtkmm/object.h"
#include "sigc++/functors/mem_fun.h"
#include <iostream>

TestButtonBox::TestButtonBox(const Glib::ustring& title, gint spacing) : 
    Gtk::Frame(title), button1("Test") {

    bbptr_bbox = nullptr;
    set_border_width(5);

    bbptr_bbox = Gtk::make_managed<Gtk::ButtonBox>(Gtk::ORIENTATION_VERTICAL);
    
    bbptr_bbox->set_border_width(5);

    add(*bbptr_bbox);

    bbptr_bbox->set_layout(Gtk::BUTTONBOX_START);
    bbptr_bbox->set_spacing(spacing);

    bbptr_bbox->add(button1);
}

void TestButtonBox::addButton(Gtk::Button button) {
    if ( bbptr_bbox ) {
        bbptr_bbox->add(button);
    }

}
        
