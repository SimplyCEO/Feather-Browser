#include "widgets.h"

FBButton* button_master = NULL;

/* =========================================================================== */

static FBButton*
ButtonReference(FBButton* button)
{
  return (FBButton*)((button == NULL) ? button_master : button);
}

/* =========================================================================== */

/* CORE */

FBWidget*
_WC_Button_Create(const char* label)
{
  FBWidget* button = gtk_button_new();

  if (label != NULL)
  { gtk_button_set_label(GTK_BUTTON(button), label); }

  return button;
}

FBButton*
_WC_Button_GetMaster(void)
{
  return button_master;
}

void
_WC_Button_SetMaster(FBWidget* button)
{
  button_master = GTK_BUTTON(button);
}

/* API */

const char*
_WC_Button_GetLabel(FBWidget* button)
{
  return gtk_button_get_label(ButtonReference(GTK_BUTTON(button)));
}

void
_WC_Button_SetLabel(FBWidget* button, const char* label)
{
  gtk_button_set_label(ButtonReference(GTK_BUTTON(button)), label);
}

