#if !defined(__GTKE_CONTAINER_H__)
#define __GTKE_CONTAINER_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <gtke/gtke.h>

#include <gtke/types/container.h>
#include <gtke/box.h>

static GtkEWidget*
gtke_container_new(GtkEOrientation orientation, int32_t padding)
{
  return gtke_box_new(orientation, padding);
}

static void
gtke_container_add(GtkEPosition position, GtkEWidget* container, GtkEWidget* worker, bool expand, bool fill, int32_t padding)
{
  switch (position)
  {
    case GTKE_CONTAINER_START: gtke_box_pack_start(container, worker, expand, fill, padding); break;
    case GTKE_CONTAINER_END: gtke_box_pack_end(container, worker, expand, fill, padding); break;
    default: break;
  }
}

static void
gtke_container_remove(GtkEWidget* worker)
{
  gtk_widget_unparent(worker);
}

static void
gtke_container_move(GtkEWidget* container, GtkEWidget* worker, int32_t index)
{
  gtke_box_reorder_child(container, worker, index);
}

static int32_t
gtke_container_get_border_width(GtkEWidget* container)
{
  return (int32_t)(gtk_container_get_border_width(GTK_CONTAINER(container)));
}

static void
gtke_container_set_border_width(GtkEWidget* container, int32_t width)
{
  gtk_container_set_border_width(GTK_CONTAINER(container), width);
}

#if defined(__GTKE_USE_CLASS__)
#include <gtke/box.h>

typedef struct GtkEWidgetContainerClass
{
  GtkEWidget*  (*Create)(GtkEOrientation, int32_t);
  void         (*Add)(GtkEPosition, GtkEWidget*, GtkEWidget*, bool, bool, int32_t);
  void         (*Remove)(GtkEWidget*);
  void         (*Move)(GtkEWidget*, GtkEWidget*, int32_t);
  int32_t      (*GetBorderWidth)(GtkEWidget*);
  void         (*SetBorderWidth)(GtkEWidget*, int32_t);
} GtkEWidgetContainerClass;

static GtkEWidgetContainerClass Container =
{
  gtke_container_new,
  gtke_container_add,
  gtke_container_remove,
  gtke_container_move,
  gtke_container_get_border_width,
  gtke_container_set_border_width
};
#endif

#if defined(__cplusplus)
}
#endif
#endif
