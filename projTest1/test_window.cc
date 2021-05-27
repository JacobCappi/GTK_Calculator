#include "test_window.h"
#include "gtkmm/enums.h"
#include "gtkmm/object.h"
#include "test_button_box.h"
#include "glibmm/ustring.h"
#include "gtkmm/messagedialog.h"
#include "sigc++/functors/mem_fun.h"
#include <iostream>

TestWindow::TestWindow() :
  m_Vbox(Gtk::ORIENTATION_HORIZONTAL),
  m_Frame_Main("Test") {

    set_title("Default");
    set_border_width(20);

    m_Frame_Main.set_border_width(5);

    add(m_Frame_Main);
    m_Frame_Main.add(m_Vbox);

    TestButtonBox *tbbptr_col1 = Gtk::make_managed<TestButtonBox>("Test Window", 30);

    Gtk::Button button1("Hello");
    tbbptr_col1->add(button1);

    m_Vbox.pack_start(*tbbptr_col1, Gtk::PACK_EXPAND_WIDGET);


    show_all_children();
}

TestWindow::~TestWindow(){
}

void TestWindow::on_button_clicked(){

}
