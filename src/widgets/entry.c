#include "widgets.h"

FBEntry* entry_master = NULL;

/* =========================================================================== */

static FBEntry*
EntryReference(FBEntry* entry)
{
  return (FBEntry*)((entry == NULL) ? entry_master : entry);
}

/* =========================================================================== */

/* CORE */

FBWidget*
_WC_Entry_Create(const char* label)
{
  FBWidget* entry = gtk_entry_new();

  if (entry != NULL)
  { gtk_entry_set_placeholder_text(GTK_ENTRY(entry), label); }

  return entry;
}

FBEntry*
_WC_Entry_GetMaster(void)
{
  return entry_master;
}

void
_WC_Entry_SetMaster(FBWidget* entry)
{
  entry_master = GTK_ENTRY(entry);
}

/* API */

const char*
_WC_Entry_GetLabel(FBWidget* entry)
{
  return gtk_entry_get_text(EntryReference(GTK_ENTRY(entry)));
}

void
_WC_Entry_SetLabel(FBWidget* entry, const char* label)
{
  gtk_entry_set_text(EntryReference(GTK_ENTRY(entry)), label);
}

