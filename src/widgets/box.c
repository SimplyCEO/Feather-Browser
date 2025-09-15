#include "widgets.h"

FBWidget*
_WC_Box_Create(FBOrientation orientation, int32_t padding)
{
  return (FBWidget*)(gtk_box_new((GtkOrientation)orientation, padding));
}

void
_WC_Box_Move(FBWidget* box, FBWidget* slave, int32_t position)
{
  gtk_box_reorder_child(GTK_BOX(box), slave, position);
}

void
_WC_Box_PositionStart(FBWidget* box, FBWidget* slave, bool expand, bool fill, uint32_t padding)
{
  gtk_box_pack_start(GTK_BOX(box), slave, expand, fill, padding);
}

void
_WC_Box_PositionEnd(FBWidget* box, FBWidget* slave, bool expand, bool fill, uint32_t padding)
{
  gtk_box_pack_end(GTK_BOX(box), slave, expand, fill, padding);
}

