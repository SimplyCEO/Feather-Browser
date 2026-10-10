#if !defined(__GTKE_BOX_H__)
#define __GTKE_BOX_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <gtke/gtke.h>

static GtkEWidget*
gtke_box_new(GtkEOrientation orientation, int32_t padding)
{
  GtkEWidget* widget = NULL;

#if (GTK_MAJOR_VERSION > 2)
  widget = gtk_box_new((GtkOrientation)orientation, padding);
#else
  switch (orientation)
  {
    case GTKE_ORIENTATION_HORIZONTAL: widget = gtk_hbox_new(false, padding); break;
    case GTKE_ORIENTATION_VERTICAL: widget = gtk_vbox_new(false, padding); break;
    default: return NULL;
  }
#endif

  return widget;
}

static void
gtke_box_reorder_child(GtkEWidget* box, GtkEWidget* worker, int32_t position)
{
  gtk_box_reorder_child(GTK_BOX(box), worker, position);
}

static void
gtke_box_pack_start(GtkEWidget* box, GtkEWidget* worker, bool expand, bool fill, uint32_t padding)
{
  gtk_box_pack_start(GTK_BOX(box), worker, expand, fill, padding);
}

static void
gtke_box_pack_end(GtkEWidget* box, GtkEWidget* worker, bool expand, bool fill, uint32_t padding)
{
  gtk_box_pack_end(GTK_BOX(box), worker, expand, fill, padding);
}

#if defined(__cplusplus)
}
#endif
#endif
