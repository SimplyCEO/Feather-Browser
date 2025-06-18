#include "browser.h"
#include "tab.h"

#if defined(DEBUG)
  static void
  on_cookie_request(GObject* source, GAsyncResult* result, gpointer data)
  {
    FB.data.cookie = WEBKIT_COOKIE_MANAGER(source);

    GList *cookies = webkit_cookie_manager_get_cookies_finish(FB.data.cookie, result, NULL);
    GList *list = NULL;

    for (list=cookies; list!=NULL; list=g_list_next(list))
    {
      SoupCookie* cookie = (SoupCookie*)(list->data);
      g_print("Cookie: %s=%s\n", soup_cookie_get_name(cookie), soup_cookie_get_value(cookie));
      soup_cookie_free(cookie);
    }
    g_list_free(cookies);
  }
#endif

void
on_cookie_handle(WebKitWebView* web, WebKitLoadEvent event, gpointer data)
{
  BrowserTabID ID = GPOINTER_TO_INT(data);
  BrowserTab tab = fb_sdk_get_tab(ID);

  if (event == WEBKIT_LOAD_FINISHED)
  {
    FB.data.cookie = webkit_web_context_get_cookie_manager(webkit_web_view_get_context(tab.web));

    webkit_cookie_manager_set_persistent_storage
    (
      FB.data.cookie,
      HOME.assets.cookies,
      WEBKIT_COOKIE_PERSISTENT_STORAGE_TEXT
    );

    #if defined(DEBUG)
      webkit_cookie_manager_get_cookies
      (
        FB.data.cookie,
        FB.data.url,
        NULL,
        on_cookie_request,
        NULL
      );
    #endif
  }
}

