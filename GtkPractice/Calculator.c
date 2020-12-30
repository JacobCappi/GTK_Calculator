#include <gtk/gtk.h>

#define GUINT_TO_POINTER(u) ((gpointer) (gulong) (u))
// Using 11 chars as my calculater can store up to 11 digits:
// most likely due to binary and leading bit and whatnot, but
// don't know how to do that yet.

// global b/c I couldn't figure out how to safely pass an updating
// local screen 
static GtkWidget *screen; 
static char num1[12], num2[12]; 

// Global counter var for num1 & num2 for %2,
// num1 and num2 are the registers on calcs
static int counter;

// Declarations
static void activateWindow(GtkApplication *app, gpointer user_data);
static void addNumberToBuffer(GtkButton *num, unsigned int data);

int main(int argc, char *argv[]){

    GtkApplication *app;
    int status;

    app = gtk_application_new("jacob.cappi.org", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activateWindow), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

static void activateWindow(GtkApplication *app, gpointer user_data){

// -------------- Gtk pointers to Buttons and Screen
    GtkWidget *window, *grid;

    GtkWidget *zero, *one, *two, *three, *four, *five, *six, *seven, *eight, *nine, *dot;
    GtkWidget *equals, *div, *mult, *add, *sub;

    GtkWidget *power, *eClear, *clear;
// -------------- END Gtk pointers to Buttons and Screen


// -------------- Windows and Grid init: Attaching Grid to Window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    // I use a tiling windows manager, so this size is just a guess;
    gtk_window_set_default_size(GTK_WINDOW(window), 200,200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

// -------------- END


// -------------- BUTTONS and GRID attatchments
    // Not sure if there is a better way because this way sucks...
    // but, here is a manual creation of all the Calc buttons
    screen = gtk_label_new(" ");
    *num1 = '\0';
    *num2 = '\0';

    zero = gtk_button_new_with_label("0");
    one = gtk_button_new_with_label("1");
    two  = gtk_button_new_with_label("2");
    three  = gtk_button_new_with_label("3");
    four  = gtk_button_new_with_label("4");
    five = gtk_button_new_with_label("5");
    six = gtk_button_new_with_label("6");
    seven = gtk_button_new_with_label("7");
    eight = gtk_button_new_with_label("8");
    nine = gtk_button_new_with_label("9");
    dot = gtk_button_new_with_label(".");
    equals = gtk_button_new_with_label("=");

    div = gtk_button_new_with_label("/");
    mult = gtk_button_new_with_label("*");
    sub= gtk_button_new_with_label("-");
    add = gtk_button_new_with_label("+");
    power = gtk_button_new_with_label("^");

    eClear = gtk_button_new_with_label("ec");
    clear = gtk_button_new_with_label("c");

    gtk_grid_attach(GTK_GRID(grid), screen, 0, 0, 5, 1);
    gtk_grid_attach(GTK_GRID(grid), equals, 2, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), dot, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), zero, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), one, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), two, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), three, 2, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), four, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), five, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), six, 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), seven, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), eight, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), nine, 2, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), div, 3, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), mult, 3, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), sub, 3, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), add, 3, 4, 1, 2);
    gtk_grid_attach(GTK_GRID(grid), power, 2, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), eClear, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), clear, 0, 1, 1, 1);

    // Number mappings to callbacks, needed pointer cast as it expects gpointer;
    // Don't think I need to delete, as not calling anything to heap ~_~
    g_signal_connect(zero, "clicked", G_CALLBACK(addNumberToBuffer), GUINT_TO_POINTER(0));
    g_signal_connect(one, "clicked", G_CALLBACK(addNumberToBuffer), GUINT_TO_POINTER(1));    
    g_signal_connect(two, "clicked", G_CALLBACK(addNumberToBuffer), GUINT_TO_POINTER(2));    
    g_signal_connect(three, "clicked", G_CALLBACK(addNumberToBuffer), GUINT_TO_POINTER(3));    
    g_signal_connect(four, "clicked", G_CALLBACK(addNumberToBuffer), GUINT_TO_POINTER(4));    
    g_signal_connect(five, "clicked", G_CALLBACK(addNumberToBuffer), GUINT_TO_POINTER(5));    
    g_signal_connect(six, "clicked", G_CALLBACK(addNumberToBuffer), GUINT_TO_POINTER(6));    
    g_signal_connect(seven, "clicked", G_CALLBACK(addNumberToBuffer), GUINT_TO_POINTER(7));    
    g_signal_connect(eight, "clicked", G_CALLBACK(addNumberToBuffer), GUINT_TO_POINTER(8));    
    g_signal_connect(nine, "clicked", G_CALLBACK(addNumberToBuffer), GUINT_TO_POINTER(9));    
   
// -------------- END BUTTONS and GRID attatchments



    gtk_widget_show_all(window);
}


static void addNumberToBuffer(GtkButton *num, unsigned int data){
    unsigned int tmpCounter = 0;
    while(num1[tmpCounter] != '\0'){
        tmpCounter++;
    }
    if(*(num1+tmpCounter)=='\0' && tmpCounter<12){
        *(num1+tmpCounter+1) = *(num1+tmpCounter);
        *(num1+tmpCounter) = data + '0'; 
    }
    //Janky Code with buffer manip and stuff (~_~!)
    const char *format = "<span style=\"100\">\%s</span>";
    char *markup = g_markup_printf_escaped (format, num1);
    gtk_label_set_markup(GTK_LABEL (screen), markup); 
    g_free (markup);

}
