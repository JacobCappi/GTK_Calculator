#include <gtk/gtk.h>

//gcc `pkg-config --cflags gtk+-3.0` -o example-0 example-0.c `pkg-config --libs gtk+-3.0`

static void activateWindow(GtkApplication* app, gpointer user_data);
static void helloWorld(GtkApplication* app, gpointer data);

int main(int argc, char **argv){

    GtkApplication *app;
    int status;

    // unsure what the arguments mean
    // app_new(gchar *app id, flags) <- init()
    app = gtk_application_new("jacob.cappi.org", G_APPLICATION_FLAGS_NONE);
    
    // define g_signal_connect(instance, detailed_signal, c_handler, data)
    // g_signal_connect makes no sense to me
    g_signal_connect(app, "activate", G_CALLBACK(activateWindow), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;    
}




static void helloWorld(GtkApplication* app, gpointer data){
    g_print("Hello World\n");
}

static void activateWindow(GtkApplication* app, gpointer user_data){
    GtkWidget *window;
    GtkWidget *button, *button_box;

    // gtk_application_window_new
    window = gtk_application_window_new(app);
    // (?) unsure if signal is called "window" or if just string
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 200,200);

// -- added later
    // button box new (orientation)
    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL); 
    // (?), GTK Container doesn't make much sense
    gtk_container_add(GTK_CONTAINER(window), button_box);

    // button declaration, button with label ('char *')
    button = gtk_button_new_with_label("+");
    g_signal_connect(button, "clicked", G_CALLBACK(helloWorld), NULL);
    // g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(button_box), button);

// -- End
    gtk_widget_show_all(window);
}
