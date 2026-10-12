#if !defined(__GTKE_WINDOW_H__)
# define __GTKE_WINDOW_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtke/common.h>

# include <gtke/container.h>
# include <gtke/image.h>
# include <gtke/widget.h>
# include <gtke/window.h>

typedef int32_t WindowPosition[2];

typedef struct WindowSettings
{
  WindowPosition position;
  const char*    title;
  const char*    icon;
} WindowSettings;

void        on_window_signal(void);
void        gtke_window_set_title(GtkEWidget* window, const char* title);
void        gtke_window_set_icon(GtkEWidget* window, GtkEImageData* icon);
void        gtke_window_set_default_size(GtkEWidget* window, size_t x, size_t y);
void        gtke_window_set_position(GtkEWidget* window, GtkWindowPosition position);
GtkEWidget* gtke_window_new(const char* w_icon_path, const char* title, size_t scale_x, size_t scale_y);
void        gtke_window_add(GtkEWidget* window, GtkEWidget* container);
void        gtke_window_remove(GtkEWidget* window, GtkEWidget* container);

# if defined(__GTKE_USE_CLASS__)
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
#   if (GTK_MAJOR_VERSION > 2)
  void        (*Position)(GtkEWidget*, GtkWindowPosition);
#   endif
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
#   if (GTK_MAJOR_VERSION > 2)
  , gtke_window_set_position
#   endif
};
# endif

# if defined(__cplusplus)
}
# endif
#endif

