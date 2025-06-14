#include <string.h>
#include <gtk/gtk.h>

#include "webview.h"

FB_SDK_WebViewReference* web_view_reference = NULL;

/* =========================================================================== */

FB_SDK_WebViewReference*
fb_sdk_webview_get_reference(void)
{
  return web_view_reference;
}

void
fb_sdk_webview_set_reference(FB_SDK_WebViewReference* webview)
{
  web_view_reference = webview;
}

void
control_web_view_reference(WebViewReferenceMode mode)
{
  if (web_view_reference != NULL)
  {
    switch (mode)
    {
      case HIDE_WEBVIEWREFERENCE: gtk_widget_hide(GTK_WIDGET(web_view_reference)); break;
      case SHOW_WEBVIEWREFERENCE: gtk_widget_show(GTK_WIDGET(web_view_reference)); break;
    }
  }
}

unsigned char
fb_sdk_webview_get_view(void)
{
  return gtk_widget_get_visible(GTK_WIDGET(web_view_reference));
}

/* --------------------------------------------------------------------------- */

void
fb_sdk_webview_search_url(char* url)
{
  if ((strncmp(url, "http://", 7) != 0) & (strncmp(url, "https://", 8) != 0))
  {
    unsigned char website = 0, ip = 0;
    unsigned short i = 0, urllen = strlen(url)+1;
    for (i=0; i<urllen; i++)
    {
      switch (url[i])
      {
        case '.': website = 1; break;
        case ':': ip = 1; website = 0; break;
        default: break;
      }
    }

    if (ip == 0)
    {
      char buffer[1024] = {0};
      if (website == 1)
      { strcpy(buffer, "https://"); }
      else
      { strcpy(buffer, "https://html.duckduckgo.com/html/?q="); }
      strcat(buffer, url);
      strcpy(url, buffer);
    }
  }

  webkit_web_view_load_uri(web_view_reference, url);
}

/* --------------------------------------------------------------------------- */

void
fb_sdk_webview_go_back_on_history(void)
{
  if (webkit_web_view_can_go_back(web_view_reference) == 1)
  { webkit_web_view_go_back(web_view_reference); }
}

void
fb_sdk_webview_go_forward_on_history(void)
{
  if (webkit_web_view_can_go_forward(web_view_reference) == 1)
  { webkit_web_view_go_forward(web_view_reference); }
}

void
fb_sdk_webview_reload_page(void)
{
  webkit_web_view_reload(web_view_reference);
}
