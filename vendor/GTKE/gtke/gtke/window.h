#if !defined(__GTKE_WINDOW_H__)
#define __GTKE_WINDOW_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <gtke/gtke.h>

#include <gtke/types/window.h>
#include <gtke/container.h>
#include <gtke/image.h>

static void
on_window_signal(void)
{
  gtk_main_quit();
}

static void
gtke_window_set_title(GtkEWidget* window, const char* title)
{
  gtk_window_set_title(GTK_WINDOW(window), title);
}

static void
gtke_window_set_icon(GtkEWidget* window, GtkEImageData* icon)
{
  gtk_window_set_icon(GTK_WINDOW(window), icon);
}

static void
gtke_window_set_default_size(GtkEWidget* window, size_t x, size_t y)
{
  gtk_window_set_default_size(GTK_WINDOW(window), x, y);
}

#if (GTK_MAJOR_VERSION > 2)
static void
gtke_window_set_position(GtkEWidget* window, GtkWindowPosition position)
{
  gtk_window_set_position(GTK_WINDOW(window), position);
}
#endif

static GtkEWidget*
gtke_window_new(const char* w_icon_path, const char* title, size_t scale_x, size_t scale_y)
{
  GtkEWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtke_window_set_title(window, title);
  gtke_window_set_default_size(window, scale_x, scale_y);
#if (GTK_MAJOR_VERSION > 2)
  gtke_window_set_position(window, GTK_WIN_POS_CENTER);
#endif
  gtke_container_set_border_width(window, 0);

  g_signal_connect(window, "destroy", G_CALLBACK(on_window_signal), NULL);

  if (w_icon_path != NULL)
  {
    GtkEImageData* icon = gtke_image_data_new_from_file(w_icon_path);
    gtke_window_set_icon(window, icon);
    gtke_free_object(icon);
  }

  return window;
}

static void
gtke_window_add(GtkEWidget* window, GtkEWidget* container)
{
  gtke_widget_dettach(container);
  gtk_container_add(GTK_CONTAINER(window), container);
  gtke_widget_update(window);
}

static void
gtke_window_remove(GtkEWidget* window, GtkEWidget* container)
{
  gtk_container_remove(GTK_CONTAINER(window), container);
}

#if defined(__GTKE_USE_CLASS__)
typedef struct GtkEWidgetWindowClass
{
  GtkEWidget* (*Create)(const char*, const char*, size_t, size_t);
  void        (*Add)(GtkEWidget*, GtkEWidget*);
  void        (*Remove)(GtkEWidget*, GtkEWidget*);
  void        (*Size)(GtkEWidget*, size_t, size_t);
  struct GtkEWidgetWindowBorderStructure
  {
    void      (*Title)(GtkEWidget*, const char*);
    void      (*Icon)(GtkEWidget*, GtkEImageData*);
  } Border;
#if (GTK_MAJOR_VERSION > 2)
  void        (*Position)(GtkEWidget*, GtkWindowPosition);
#endif
} GtkEWidgetWindowClass;

static GtkEWidgetWindowClass Window =
{
  gtke_window_new,
  gtke_window_add,
  gtke_window_remove,
  gtke_window_set_default_size,
  {
    gtke_window_set_title,
    gtke_window_set_icon
  }
#if (GTK_MAJOR_VERSION > 2)
  ,gtke_window_set_position
#endif
};
#endif

#if defined(__cplusplus)
}
#endif
#endif
