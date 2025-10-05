#include "widgets.h"

/* =========================================================================== */

static void
on_window_signal(void)
{
  gtk_main_quit();
}

/* =========================================================================== */

/* CORE */

FBWidget*
_WC_Window_Create(const char* w_icon_path, const char* title, size_t scale_x, size_t scale_y)
{
  FBWidgetsContainerClass Container = fb_widgets_get_container_class();
  FBWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  FBIcon* icon = gdk_pixbuf_new_from_file(w_icon_path, NULL);

  gtk_window_set_title(GTK_WINDOW(window), title);
  gtk_window_set_default_size(GTK_WINDOW(window), scale_x, scale_y);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_icon(GTK_WINDOW(window), icon);
  Container.SetBorderWidth(window, 0);

  g_signal_connect(window, "destroy", G_CALLBACK(on_window_signal), NULL);
  g_object_unref(icon);

  return window;
}

