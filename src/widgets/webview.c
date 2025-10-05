#include <stdio.h>

#include "widgets.h"
#include "cookie.h"
#include "browser.h"

FBWebView* web_view_master = NULL;

/* =========================================================================== */

static FBWebView*
WebViewReference(FBWebView* web_view)
{
  return (FBWebView*)((web_view == NULL) ? web_view_master : web_view);
}

/* =========================================================================== */

/* CORE */

FBWebView*
_WC_WebView_Create(void)
{
  return (FBWebView*)(WEBKIT_WEB_VIEW(webkit_web_view_new()));
}

FBWebView*
_WC_WebView_GetMaster(void)
{
  return web_view_master;
}

void
_WC_WebView_SetMaster(FBWebView* web_view)
{
  web_view_master = web_view;
}

/* API */

bool
_WC_WebView_Visible(FBWebView* web_view)
{
  return gtk_widget_get_visible(GTK_WIDGET(WebViewReference(web_view)));
}

bool
_WC_WebView_CanGoBack(FBWebView* web_view)
{
  return webkit_web_view_can_go_back(WebViewReference(web_view));
}

bool
_WC_WebView_CanGoForward(FBWebView* web_view)
{
  return webkit_web_view_can_go_forward(WebViewReference(web_view));
}

bool
_WC_WebView_Loading(FBWebView* web_view)
{
  return webkit_web_view_is_loading(WebViewReference(web_view));
}

const char*
_WC_WebView_GetTitle(FBWebView* web_view)
{
  return webkit_web_view_get_title(WebViewReference(web_view));
}

const char*
_WC_WebView_GetURI(FBWebView* web_view)
{
  return webkit_web_view_get_uri(WebViewReference(web_view));
}

void
_WC_WebView_Control(FBWebView* web_view, FBWebViewMode mode)
{
  FBWebView* ref_web_view = WebViewReference(web_view);

  if (ref_web_view == NULL)
  { return; }

  switch (mode)
  {
    case WEBVIEW_HIDE: gtk_widget_hide(GTK_WIDGET(ref_web_view)); break;
    case WEBVIEW_SHOW: gtk_widget_show(GTK_WIDGET(ref_web_view)); break;
  }
}

void
_WC_WebView_LoadHTML(FBWebView* web_view, const char* file, const char* uri)
{
  webkit_web_view_load_html(WebViewReference(web_view), file, uri);
}

void
_WC_WebView_LoadURI(FBWebView* web_view, const char* uri)
{
  webkit_web_view_load_uri(WebViewReference(web_view), uri);
}

void
_WC_WebView_Search(FBWebView* web_view, char* url)
{
  if ((strncmp(url, "http://", 7) != 0) & (strncmp(url, "https://", 8) != 0))
  {
    bool website = false,
         ip      = false;
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

  _WC_WebView_LoadURI(web_view, url);
}

void
_WC_WebView_BackHistory(FBWebView* web_view)
{
  webkit_web_view_go_back(WebViewReference(web_view));
}

void
_WC_WebView_ForwardHistory(FBWebView* web_view)
{
  webkit_web_view_go_forward(WebViewReference(web_view));
}

void
_WC_WebView_Stop(FBWebView* web_view)
{
  FBWebView* ref_web_view = WebViewReference(web_view);
  if (_WC_WebView_Loading(ref_web_view) == true)
  { webkit_web_view_stop_loading(ref_web_view); }
}

void
_WC_WebView_Reload(FBWebView* web_view, FBButton* button)
{
  FBWidgetsButtonClass Button = fb_widgets_get_button_class();
  FBWebView* ref_web_view = WebViewReference(web_view);

  if (Button.GetLabel(GTK_WIDGET(button)) != NULL)
  { webkit_web_view_reload(ref_web_view); return; }

  _WC_WebView_Stop(ref_web_view);
  Button.SetLabel(GTK_WIDGET(button), "↑↓");
}

