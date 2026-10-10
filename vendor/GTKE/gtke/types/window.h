#if !defined(__GTKE_WINDOW_TYPES_H__)
#define __GTKE_WINDOW_TYPES_H__

#if defined(__cplusplus)
extern "C"
{
#endif

typedef int32_t WindowPosition[2];

typedef struct WindowSettings
{
  WindowPosition position;
  const char*    title;
  const char*    icon;
} WindowSettings;

#if defined(__cplusplus)
}
#endif
#endif
