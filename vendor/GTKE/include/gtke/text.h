#if !defined(__GTKE_TEXT_H__)
# define __GTKE_TEXT_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtke/common.h>

# include <gtke/widget.h>

GtkEWidget* gtke_text_new(const char* label);
void        gtke_text_rename(GtkEWidget* text, const char* label);

# if defined(__GTKE_USE_CLASS__)
typedef struct GtkEWidgetTextClass
{
  GtkEWidget*  (*Create)(const char*);
  void         (*Rename)(GtkEWidget*, const char*);
} GtkEWidgetTextClass;

static GtkEWidgetTextClass Text =
{
  gtke_text_new,
  gtke_text_rename
};
# endif

# if defined(__cplusplus)
}
# endif
#endif

