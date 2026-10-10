#if !defined(__GTKE_H__)
#define __GTKE_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#if (__STDC_VERSION__ < 199901L)
#define false 0
#define true 1
typedef unsigned char    bool;
typedef signed   char    int8_t;
typedef signed   short   int16_t;
typedef signed   int     int32_t;
typedef unsigned char    uint8_t;
typedef unsigned short   uint16_t;
typedef unsigned int     uint32_t;
#else
#include <stdbool.h>
#include <stdint.h>
#endif

#include <gtk/gtk.h>
#include <gtke/types/window.h>

typedef enum GtkEOrientation
{
  GTKE_ORIENTATION_HORIZONTAL = 0,
  GTKE_ORIENTATION_VERTICAL = 1
} GtkEOrientation;

typedef GtkWidget GtkEWidget;

typedef struct GtkESettings
{
  WindowSettings window;
} GtkESettings;

static void
gtke_setup(void)
{
  gtk_init(NULL, NULL);
}

static void
gtke_loop(void)
{
  gtk_main();
}

static void
gtke_widget_dettach(GtkEWidget* worker)
{
  GtkEWidget* container = gtk_widget_get_parent(worker);

  if (container != NULL)
  { gtk_container_remove(GTK_CONTAINER(container), worker); }
}

static void
gtke_widget_update(GtkEWidget* widget)
{
  gtk_widget_show_all(widget);
}

static GtkESettings gtke_settings;

static GtkESettings*
gtke_settings_get(void)
{
  return &gtke_settings;
}

static void
gtke_settings_set(GtkESettings* settings)
{
  gtke_settings.window.position[0] = settings->window.position[0];
  gtke_settings.window.position[1] = settings->window.position[1];
  gtke_settings.window.title = settings->window.title;
  gtke_settings.window.icon = settings->window.icon;
}

static void
gtke_free_object(void* object)
{
  if (object == NULL)
  { return; }
  g_object_unref(G_OBJECT(object));
}

#if defined(__cplusplus)
}
#endif
#endif
