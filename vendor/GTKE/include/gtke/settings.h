#if !defined(__GTKE_SETTINGS_H__)
# define __GTKE_SETTINGS_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtke/window.h>

typedef struct GtkESettings
{
  WindowSettings window;
} GtkESettings;

GtkESettings* gtke_settings_get(void);
void          gtke_settings_set(GtkESettings* settings);

# if defined(__cplusplus)
}
# endif
#endif

