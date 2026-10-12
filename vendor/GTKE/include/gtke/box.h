#if !defined(__GTKE_BOX_H__)
# define __GTKE_BOX_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtke/common.h>

# include <gtke/transform.h>
# include <gtke/widget.h>

GtkEWidget* gtke_box_new(GtkEOrientation orientation, int32_t padding);
void        gtke_box_reorder_child(GtkEWidget* box, GtkEWidget* worker, int32_t position);
void        gtke_box_pack_start(GtkEWidget* box, GtkEWidget* worker, bool expand, bool fill, uint32_t padding);
void        gtke_box_pack_end(GtkEWidget* box, GtkEWidget* worker, bool expand, bool fill, uint32_t padding);

#if defined(__cplusplus)
}
#endif
#endif
