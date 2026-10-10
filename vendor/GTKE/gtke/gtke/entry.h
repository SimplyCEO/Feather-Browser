#if !defined(__GTKE_ENTRY_H__)
#define __GTKE_ENTRY_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <gtke/gtke.h>

#include <gtke/types/entry.h>

static GtkEWidget*
gtke_entry_new(const char* label)
{
  GtkEWidget* entry = gtk_entry_new();

  if (entry != NULL)
  { gtk_entry_set_text(GTK_ENTRY(entry), label); }

  return entry;
}

static const char*
gtke_entry_get_text(GtkEWidget* entry)
{
  return gtk_entry_get_text(GTK_ENTRY(entry));
}

static void
gtke_entry_set_text(GtkEWidget* entry, const char* label)
{
  gtk_entry_set_text(GTK_ENTRY(entry), label);
}

#if defined(__GTKE_USE_CLASS__)
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
#endif

#if defined(__cplusplus)
}
#endif
#endif
