#if !defined(__GTKE_WEBVIEW_H__)
#define __GTKE_WEBVIEW_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <gtke/gtke.h>

#include <gtke/types/webview.h>
#include <gtke/button.h>

/* WebContext */

static GtkEWebContext*
gtke_webcontext_new(void)
{
  return webkit_web_context_new();
}

#if defined(__GTKE_WEBVIEW_USE_COOKIES__)
static GtkECookieManager*
gtke_webcontext_get_cookies(GtkEWebContext* context)
{
  return webkit_web_context_get_cookie_manager(context);
}

static void
gtke_cookies_set_storage(GtkECookieManager* cookies, const char* path, GtkECookieStorage method)
{
  webkit_cookie_manager_set_persistent_storage(cookies, path, (WebKitCookiePersistentStorage)method);
}

static GtkECookieManager* cookies = NULL;

static void
gtke_hook_cookies(GtkEWidget* webview, GtkEWebLoadEvent event, void* data)
{
  if (event == GTKE_WEB_LOAD_FINISH)
  {
    cookies = gtke_webcontext_get_cookies(webkit_web_view_get_context(WEBKIT_WEB_VIEW(webview)));

    if (data == NULL) { data = "cookies.dat"; }

    gtke_cookies_set_storage(cookies, data, GTKE_COOKIES_STORAGE_DATA);
  }
}
#endif

/* WebSettings */

static GtkEWebSettings*
gtke_websettings_new(void)
{
  GtkEWebSettings* settings = webkit_settings_new();

#if 0
  webkit_settings_set_enable_frame_flattening(settings, false);
  webkit_settings_set_enable_hyperlink_auditing(settings, false);
  webkit_settings_set_enable_java(settings, false);
  webkit_settings_set_enable_offline_web_application_cache(settings, false);
  webkit_settings_set_enable_plugins(settings, false);
  webkit_settings_set_enable_xss_auditor(settings, false);
  webkit_settings_set_load_icons_ignoring_image_load_setting(settings, false);
  webkit_settings_set_enable_private_browsing(settings, false);
  webkit_settings_set_enable_dns_prefetching(settings, false);
  webkit_settings_set_enable_accelerated_2d_canvas(settings, false);
  webkit_settings_set_default_font_family(settings, NULL);
  webkit_settings_set_monospace_font_family(settings, NULL);
  webkit_settings_set_serif_font_family(settings, NULL);
  webkit_settings_set_sans_serif_font_family(settings, NULL);
  webkit_settings_set_cursive_font_family(settings, NULL);
  webkit_settings_set_fantasy_font_family(settings, NULL);
  webkit_settings_set_pictograph_font_family(settings, NULL);
  webkit_settings_set_default_charset(settings, NULL);
  webkit_settings_set_user_agent(settings, NULL);
  webkit_settings_set_user_agent_with_application_details(settings, NULL, NULL);
#endif

  webkit_settings_set_auto_load_images(settings, true);
  webkit_settings_set_enable_html5_database(settings, false);
  webkit_settings_set_enable_html5_local_storage(settings, false);
  webkit_settings_set_enable_javascript(settings, true);
  webkit_settings_set_javascript_can_open_windows_automatically(settings, false);
  webkit_settings_set_default_font_size(settings, 12);
  webkit_settings_set_default_monospace_font_size(settings, 12);
  webkit_settings_set_minimum_font_size(settings, 12);
  webkit_settings_set_enable_developer_extras(settings, false);
  webkit_settings_set_enable_resizable_text_areas(settings, false);
  webkit_settings_set_enable_tabs_to_links(settings, false);
  webkit_settings_set_enable_caret_browsing(settings, false);
  webkit_settings_set_enable_fullscreen(settings, false);
  webkit_settings_set_print_backgrounds(settings, false);
  webkit_settings_set_enable_webaudio(settings, false);
  webkit_settings_set_enable_webgl(settings, false);
  webkit_settings_set_allow_modal_dialogs(settings, false);
  webkit_settings_set_zoom_text_only(settings, false);
  webkit_settings_set_javascript_can_access_clipboard(settings, false);
  webkit_settings_set_media_playback_requires_user_gesture(settings, false);
  webkit_settings_set_media_playback_allows_inline(settings, false);
  webkit_settings_set_draw_compositing_indicators(settings, false);
  webkit_settings_set_enable_site_specific_quirks(settings, false);
  webkit_settings_set_enable_page_cache(settings, false);
  webkit_settings_set_enable_smooth_scrolling(settings, false);
  webkit_settings_set_enable_write_console_messages_to_stdout(settings, false);
  webkit_settings_set_enable_media_stream(settings, false);
  webkit_settings_set_enable_spatial_navigation(settings, false);
  webkit_settings_set_enable_mediasource(settings, false);

  return settings;
}

/* WebView */

static GtkEWidget*
gtke_webview_new(
#if defined(__GTKE_WEBVIEW_USE_COOKIES__)
  const char* cookies_path
#else
  void
#endif
)
{
  GtkEWebContext* context = webkit_web_context_new();
  GtkEWidget* webview = webkit_web_view_new_with_context(context);
  GtkEWebSettings* settings = gtke_websettings_new();

  webkit_web_view_set_settings(WEBKIT_WEB_VIEW(webview), settings);

#if defined(__GTKE_WEBVIEW_USE_COOKIES__)
  gtke_hook_cookies(webview, GTKE_WEB_LOAD_FINISH, cookies_path);
  g_signal_connect(webview, "load-changed", G_CALLBACK(gtke_hook_cookies), cookies_path);
#endif

  return webview;
}

static bool
gtke_webview_get_visible(GtkEWidget* web_view)
{
  return gtk_widget_get_visible(web_view);
}

static bool
gtke_webview_can_go_back(GtkEWidget* web_view)
{
  return webkit_web_view_can_go_back(WEBKIT_WEB_VIEW(web_view));
}

static bool
gtke_webview_can_go_forward(GtkEWidget* web_view)
{
  return webkit_web_view_can_go_forward(WEBKIT_WEB_VIEW(web_view));
}

static bool
gtke_webview_is_loading(GtkEWidget* web_view)
{
  return webkit_web_view_is_loading(WEBKIT_WEB_VIEW(web_view));
}

static const char*
gtke_webview_get_title(GtkEWidget* web_view)
{
  return webkit_web_view_get_title(WEBKIT_WEB_VIEW(web_view));
}

static const char*
gtke_webview_get_uri(GtkEWidget* web_view)
{
  return webkit_web_view_get_uri(WEBKIT_WEB_VIEW(web_view));
}

static void
gtke_webview_control(GtkEWidget* web_view, GtkEWebViewMode mode)
{
  switch (mode)
  {
    case GTKE_WEBVIEW_SHOW: gtk_widget_show(web_view); break;
    case GTKE_WEBVIEW_HIDE: gtk_widget_hide(web_view); break;
  }
}

static void
gtke_webview_load_html(GtkEWidget* web_view, const char* file, const char* uri)
{
  webkit_web_view_load_html(WEBKIT_WEB_VIEW(web_view), file, uri);
}

static void
gtke_webview_load_uri(GtkEWidget* web_view, const char* uri)
{
  webkit_web_view_load_uri(WEBKIT_WEB_VIEW(web_view), uri);
}

static void
gtke_webview_search(GtkEWidget* web_view, char* url)
{
  if ((strncmp(url, "http://", 7) != 0) & (strncmp(url, "https://", 8) != 0))
  {
    bool website = false;
    bool ip      = false;
    uint16_t url_len = strlen(url)+1;

    /* XXX.XXX.XXX = WEBSITE / X.X.X.X:XXXXX = IP */
    uint16_t i = 0; for (; i<url_len; i++)
    {
      switch (url[i])
      {
        case '.': website = true; break;
        case ':': ip = true; website = false; break;
        default: break;
      }
    }

    if (ip == false)
    {
      char buffer[1024] = {0};

      sprintf(buffer, "%s://%s", "http", url);
      if (website == false)
      { sprintf(buffer, "%s://%s/?q=%s", "https", "html.duckduckgo.com/html", url); }

      sprintf(url, "%s", buffer);
    }
  }

  gtke_webview_load_uri(web_view, url);
}

static void
gtke_webview_go_back(GtkEWidget* web_view)
{
  if (gtke_webview_can_go_back(web_view) == true)
  { webkit_web_view_go_back(WEBKIT_WEB_VIEW(web_view)); }
}

static void
gtke_webview_go_forward(GtkEWidget* web_view)
{
  if (gtke_webview_can_go_forward(web_view) == true)
  { webkit_web_view_go_forward(WEBKIT_WEB_VIEW(web_view)); }
}

static void
gtke_webview_stop_loading(GtkEWidget* web_view)
{
  if (gtke_webview_is_loading(web_view) == true)
  { webkit_web_view_stop_loading(WEBKIT_WEB_VIEW(web_view)); }
}

static void
gtke_webview_reload(GtkEWidget* web_view, GtkEButton* button)
{
  if (gtke_button_get_label(GTK_WIDGET(button)) != NULL)
  { webkit_web_view_reload(WEBKIT_WEB_VIEW(web_view)); return; }

  gtke_webview_stop_loading(web_view);
  gtke_button_set_label(GTK_WIDGET(button), "@");
}

#if defined(__GTKE_USE_CLASS__)
typedef struct GtkEWidgetWebViewClass
{
#if defined(__GTKE_WEBVIEW_USE_COOKIES__)
  GtkEWidget*   (*Create)(const char*);
#else
  GtkEWidget*   (*Create)(void);
#endif
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
#endif

#if defined(__cplusplus)
}
#endif
#endif
