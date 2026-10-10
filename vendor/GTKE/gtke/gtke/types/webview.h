#if !defined(__GTKE_WEBVIEW_TYPES_H__)
#define __GTKE_WEBVIEW_TYPES_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <webkit2/webkit2.h>

typedef WebKitCookieManager GtkECookieManager;
typedef WebKitSettings      GtkEWebSettings;
typedef WebKitWebContext    GtkEWebContext;
typedef WebKitWebView       GtkEWebView;

typedef enum GtkECookieStorage
{
  GTKE_COOKIES_STORAGE_DATA = 0,
  GTKE_COOKIES_STORAGE_SQL
} GtkECookieStorage;

typedef enum GtkEWebLoadEvent
{
  GTKE_WEB_LOAD_START = 0,
  GTKE_WEB_LOAD_REDIRECT,
  GTKE_WEB_LOAD_COMMIT,
  GTKE_WEB_LOAD_FINISH
} GtkEWebLoadEvent;

typedef enum GtkEWebViewMode
{
  GTKE_WEBVIEW_HIDE = 0,
  GTKE_WEBVIEW_SHOW = 1
} GtkEWebViewMode;

#if defined(__cplusplus)
}
#endif
#endif
