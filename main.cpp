#include <gtk/gtk.h>
#include <iostream>

void helloworld(GtkWidget *widget, gpointer *data) {
  g_print("hello world this test be funky\n");
}

void hellooo() {
  std::cout << "test!\n";
}

void destroy(GtkWidget *widget, gpointer *data) {
  gtk_main_quit();
}


int main(int argc, char *argv[]) {

  gtk_init(&argc, &argv);
//  GtkBuilder* gtk_builder_new_from_file (
//    const char* buidfile.xml
//  );
  GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);;
  gtk_container_set_border_width(GTK_CONTAINER (window), 10);

  GtkWidget *button = gtk_button_new_with_label("hello world");
  g_signal_connect(G_OBJECT (button), "clicked", G_CALLBACK(helloworld), NULL);
  
  GtkWidget *secondButton = gtk_button_new_with_label("second button!!!");
  g_signal_connect(G_OBJECT (secondButton), "clicked", G_CALLBACK(hellooo), NULL);
  
  GtkWidget *horizontalBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_style_context_add_class(gtk_widget_get_style_context(horizontalBox), "boxed");

  GtkWidget *label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), "<b>this</b> is some <i>crazy</i> ass text");
  gtk_container_add(GTK_CONTAINER(window), horizontalBox);
  gtk_box_set_homogeneous(GTK_BOX(horizontalBox), FALSE);
  gtk_widget_set_valign(button, GTK_ALIGN_START);
  gtk_widget_set_valign(secondButton, GTK_ALIGN_START);
  gtk_box_pack_start(GTK_BOX(horizontalBox), button, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(horizontalBox), secondButton, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(horizontalBox), label, false, false, 5);
  
  //Load css!
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "style.css", NULL);
  gtk_style_context_add_provider_for_screen(
    gdk_screen_get_default(),
    GTK_STYLE_PROVIDER(provider),
    GTK_STYLE_PROVIDER_PRIORITY_USER
  );
  g_object_unref(provider);

  g_signal_connect(G_OBJECT (window), "destroy", G_CALLBACK (destroy), NULL);
  
  gtk_widget_show_all(window);

  gtk_main();
  
  return 0;
}
