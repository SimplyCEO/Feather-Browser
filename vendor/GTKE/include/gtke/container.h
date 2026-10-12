#if !defined(__GTKE_CONTAINER_H__)
# define __GTKE_CONTAINER_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtke/common.h>

# include <gtke/box.h>
# include <gtke/widget.h>

typedef enum GtkEPosition
{
  GTKE_CONTAINER_START = 0,
  GTKE_CONTAINER_END = 1
} GtkEPosition;

GtkEWidget* gtke_container_new(GtkEOrientation orientation, int32_t padding);
void        gtke_container_add(GtkEPosition position, GtkEWidget* container, GtkEWidget* worker, bool expand, bool fill, int32_t padding);
void        gtke_container_remove(GtkEWidget* worker);
void        gtke_container_move(GtkEWidget* container, GtkEWidget* worker, int32_t index);
int32_t     gtke_container_get_border_width(GtkEWidget* container);
void        gtke_container_set_border_width(GtkEWidget* container, int32_t width);

# if defined(__GTKE_USE_CLASS__)

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
# endif

# if defined(__cplusplus)
}
# endif
#endif

