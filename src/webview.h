#ifndef WEBVIEW_HEADER
#define WEBVIEW_HEADER

#include <webkit2/webkit2.h>
typedef WebKitWebView FB_SDK_WebViewReference;

typedef enum FB_SDK_WebViewReferenceMode
{
  HIDE_WEBVIEWREFERENCE = 0,
  SHOW_WEBVIEWREFERENCE = 1
} WebViewReferenceMode;

FB_SDK_WebViewReference* fb_sdk_webview_create_new(void);
FB_SDK_WebViewReference* fb_sdk_webview_get_reference(void);
void fb_sdk_webview_set_reference(FB_SDK_WebViewReference* webview);
void control_web_view_reference(WebViewReferenceMode mode);
unsigned char fb_sdk_webview_get_view(void);

void fb_sdk_webview_search_url(char* url);

void fb_sdk_webview_go_back_on_history(void);
void fb_sdk_webview_go_forward_on_history(void);

void fb_sdk_webview_reload_page(void);

#endif

