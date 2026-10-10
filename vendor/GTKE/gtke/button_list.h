#if !defined(__GTKE_BUTTON_LIST_H__)
#define __GTKE_BUTTON_LIST_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <gtke/gtke.h>

static GtkEWidget*
gtke_button_list_new(void)
{
  return (GtkEWidget*)(gtk_combo_box_text_new());
}

static void
gtke_button_list_add(GtkEWidget* list, const char* label)
{
  return gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(list), label);
}

static void
gtke_button_list_remove(GtkEWidget* list, int32_t index)
{
  gtk_combo_box_text_remove(GTK_COMBO_BOX_TEXT(list), index);
}

static int32_t
gtke_button_list_get_active(GtkEWidget* list)
{
  return gtk_combo_box_get_active(GTK_COMBO_BOX(list));
}

static void
gtke_button_list_set_active(GtkEWidget* list, int32_t index)
{
  gtk_combo_box_set_active(GTK_COMBO_BOX(list), index);
}

#if defined(__GTKE_USE_CLASS__)
typedef struct GtkEWidgetListClass
{
  GtkEWidget*  (*Create)(void);
  void         (*Add)(GtkEWidget*, const char*);
  void         (*Remove)(GtkEWidget*, int32_t);
  int32_t      (*GetDefault)(GtkEWidget*);
  void         (*SetDefault)(GtkEWidget*, int32_t);
} GtkEWidgetListClass;

static GtkEWidgetListClass List =
{
  gtke_button_list_new,
  gtke_button_list_add,
  gtke_button_list_remove,
  gtke_button_list_get_active,
  gtke_button_list_set_active
};
#endif

#if defined(__cplusplus)
}
#endif
#endif
