#if !defined(__GTKE_BUTTON_H__)
#define __GTKE_BUTTON_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <gtke/gtke.h>

#include <gtke/types/button.h>

static const char*
gtke_button_get_label(GtkEWidget* button)
{
  return gtk_button_get_label(GTK_BUTTON(button));
}

static void
gtke_button_set_label(GtkEWidget* button, const char* label)
{
  gtk_button_set_label(GTK_BUTTON(button), label);
}

static GtkEWidget*
gtke_button_new(const char* label)
{
  GtkEWidget* button = gtk_button_new();

  if (label != NULL)
  { gtke_button_set_label(button, label); }

  return button;
}

static GtkEWidget*
gtke_check_button_new(const char* label)
{
  GtkEWidget* checkmark = gtk_check_button_new();

  if (label != NULL)
  { gtke_button_set_label(checkmark, label); }

  return checkmark;
}

static int32_t
gtke_toggle_button_get_active(GtkEWidget* checkmark)
{
  return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkmark));
}

static void
gtke_toggle_button_set_active(GtkEWidget* checkmark, int32_t index)
{
  return gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkmark), index);
}

#if defined(__GTKE_USE_CLASS__)
typedef struct GtkEWidgetButtonClass
{
  const char*   (*GetLabel)(GtkEWidget*);
  void          (*SetLabel)(GtkEWidget*, const char*);
  GtkEWidget*   (*Create)(const char*);
  struct GtkEWidgetButtonCheckMarkClass
  {
    GtkEWidget* (*Create)(const char*);
    int32_t     (*GetDefault)(GtkEWidget*);
    void        (*SetDefault)(GtkEWidget*, int32_t);
  } CheckMark;
} GtkEWidgetButtonClass;

static GtkEWidgetButtonClass Button =
{
  gtke_button_get_label,
  gtke_button_set_label,
  gtke_button_new,
  {
    gtke_check_button_new,
    gtke_toggle_button_get_active,
    gtke_toggle_button_set_active
  }
};
#endif

#if defined(__cplusplus)
}
#endif
#endif
