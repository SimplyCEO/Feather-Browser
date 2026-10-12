#if !defined(__GTKE_CORE_H__)
# define __GTKE_CORE_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtk/gtk.h>

void gtke_setup(void);
void gtke_loop(void);
void gtke_free_object(void* object);

# if defined(__cplusplus)
}
# endif
#endif

