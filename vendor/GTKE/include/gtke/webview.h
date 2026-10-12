#if !defined(__GTKE_WEBVIEW_H__)
# define __GTKE_WEBVIEW_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtke/common.h>

# include <webkit2/webkit2.h>
# include <gtke/button.h>
# include <gtke/widget.h>

typedef WebKitCookieManager      GtkECookieManager;
typedef WebKitSettings           GtkEWebSettings;
typedef WebKitUserContentManager GtkEWebContentManager;
typedef WebKitUserScript         GtkEWebUserScript;
typedef WebKitWebContext         GtkEWebContext;
typedef WebKitWebView            GtkEWebView;

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

typedef struct GtkEWebContentManagerInjector
{
  uint32_t            index;
  GtkEWebUserScript** script;
} GtkEWebContentManagerInjector;

GtkEWebContentManager*         gtke_webcontentmanager_new(void);
GtkEWebContentManager*         gtke_webcontentmanager_get(GtkEWidget* webview);
GtkEWebContentManagerInjector* gtke_webcontentmanager_injector_new(void);
void                           gtke_webcontentmanager_injector_destroy(GtkEWebContentManagerInjector* content_injector);
void                           gtke_webcontentmanager_inject(GtkEWebContentManager* manager, GtkEWebContentManagerInjector* content_injector);
GtkEWebUserScript**            gtke_webuserscript_new(GtkEWebContentManagerInjector* content_injector, const char* script_path, const char* const* allowed_uri_list, const char* const* filtered_uri_list);
GtkEWebContext*                gtke_webcontext_new(void);
# if defined(__GTKE_WEBVIEW_USE_COOKIES__)
GtkECookieManager*             gtke_webcontext_get_cookies(GtkEWebContext* context);
void                           gtke_cookies_set_storage(GtkECookieManager* cookies, const char* path, GtkECookieStorage method);
void                           gtke_hook_cookies(GtkEWidget* webview, GtkEWebLoadEvent event, void* data);
# endif
GtkEWebSettings*               gtke_websettings_new(void);
GtkEWebSettings*               gtke_websettings_get(GtkEWidget* webview);
void                           gtke_websettings_set(GtkEWebSettings* settings, GtkEWidget* webview);
# if defined(__GTKE_WEBVIEW_USE_COOKIES__)
GtkEWidget*                    gtke_webview_new(const char* cookies_path);
# else
GtkEWidget*                    gtke_webview_new(void);
# endif
bool                           gtke_webview_get_visible(GtkEWidget* web_view);
bool                           gtke_webview_can_go_back(GtkEWidget* web_view);
bool                           gtke_webview_can_go_forward(GtkEWidget* web_view);
bool                           gtke_webview_is_loading(GtkEWidget* web_view);
const char*                    gtke_webview_get_title(GtkEWidget* web_view);
const char*                    gtke_webview_get_uri(GtkEWidget* web_view);
void                           gtke_webview_control(GtkEWidget* web_view, GtkEWebViewMode mode);
void                           gtke_webview_load_html(GtkEWidget* web_view, const char* file, const char* uri);
void                           gtke_webview_load_uri(GtkEWidget* web_view, const char* uri);
void                           gtke_webview_search(GtkEWidget* web_view, char* url);
void                           gtke_webview_go_back(GtkEWidget* web_view);
void                           gtke_webview_go_forward(GtkEWidget* web_view);
void                           gtke_webview_stop_loading(GtkEWidget* web_view);
void                           gtke_webview_reload(GtkEWidget* web_view, GtkEButton* button);

# if defined(__GTKE_USE_CLASS__)
typedef struct GtkEWidgetWebViewClass
{
#   if defined(__GTKE_WEBVIEW_USE_COOKIES__)
  GtkEWidget*   (*Create)(const char*);
#   else
  GtkEWidget*   (*Create)(void);
#   endif
  bool          (*Visible)(GtkEWidget*);
  bool          (*Loading)(GtkEWidget*);
  const char*   (*GetTitle)(GtkEWidget*);
  const char*   (*GetURI)(GtkEWidget*);
  void          (*Control)(GtkEWidget*, GtkEWebViewMode);
  void          (*LoadHTML)(GtkEWidget*, const char*, const char*);
  void          (*LoadURI)(GtkEWidget*, const char*);
  void          (*Search)(GtkEWidget*, char*);
  void          (*BackHistory)(GtkEWidget*);
  void          (*ForwardHistory)(GtkEWidget*);
  void          (*Stop)(GtkEWidget*);
  void          (*Reload)(GtkEWidget*, GtkEButton*);
} GtkEWidgetWebViewClass;

static GtkEWidgetWebViewClass WebView =
{
  gtke_webview_new,
  gtke_webview_get_visible,
  gtke_webview_is_loading,
  gtke_webview_get_title,
  gtke_webview_get_uri,
  gtke_webview_control,
  gtke_webview_load_html,
  gtke_webview_load_uri,
  gtke_webview_search,
  gtke_webview_go_back,
  gtke_webview_go_forward,
  gtke_webview_stop_loading,
  gtke_webview_reload
};
# endif

# if defined(__cplusplus)
}
# endif
#endif

