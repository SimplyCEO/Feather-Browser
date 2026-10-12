#if !defined(__GTKE_WIDGET_H__)
# define __GTKE_WIDGET_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtk/gtk.h>

typedef GtkWidget GtkEWidget;

void gtke_widget_dettach(GtkEWidget* worker);
void gtke_widget_update(GtkEWidget* widget);

# if defined(__cplusplus)
}
# endif
#endif

