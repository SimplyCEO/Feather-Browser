#if !defined(__GTKE_ENTRY_H__)
# define __GTKE_ENTRY_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtke/common.h>

# include <gtke/widget.h>

typedef GtkEntry GtkEEntry;

GtkEWidget* gtke_entry_new(const char* label);
const char* gtke_entry_get_text(GtkEWidget* entry);
void        gtke_entry_set_text(GtkEWidget* entry, const char* label);

# if defined(__GTKE_USE_CLASS__)
typedef struct GtkEWidgetEntryClass
{
  GtkEWidget*  (*Create)(const char*);
  const char*  (*GetLabel)(GtkEWidget*);
  void         (*SetLabel)(GtkEWidget*, const char*);
} GtkEWidgetEntryClass;

static GtkEWidgetEntryClass Entry =
{
  gtke_entry_new,
  gtke_entry_get_text,
  gtke_entry_set_text
};
# endif

# if defined(__cplusplus)
}
# endif
#endif

