#if !defined(__GTKE_BUTTON_H__)
# define __GTKE_BUTTON_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtke/common.h>

# include <gtke/widget.h>

typedef GtkButton GtkEButton;

const char* gtke_button_get_label(GtkEWidget* button);
void        gtke_button_set_label(GtkEWidget* button, const char* label);
GtkEWidget* gtke_button_new(const char* label);
GtkEWidget* gtke_check_button_new(const char* label);
int32_t     gtke_toggle_button_get_active(GtkEWidget* checkmark);
void        gtke_toggle_button_set_active(GtkEWidget* checkmark, int32_t index);

# if defined(__GTKE_USE_CLASS__)
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
# endif

# if defined(__cplusplus)
}
# endif
#endif

