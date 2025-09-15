#include "widgets.h"

void
_WC_Container_Add(FBWidget* container, FBWidget* slave)
{
  gtk_container_add(GTK_CONTAINER(container), slave);
}

void
_WC_Container_Remove(FBWidget* container, FBWidget* slave)
{
  gtk_container_remove(GTK_CONTAINER(container), slave);
}

int32_t
_WC_Container_GetBorderWidth(FBWidget* container)
{
  return (int32_t)(gtk_container_get_border_width(GTK_CONTAINER(container)));
}

void
_WC_Container_SetBorderWidth(FBWidget* container, int32_t width)
{
  gtk_container_set_border_width(GTK_CONTAINER(container), width);
}

