#include <gtk/gtk.h>

#include <stdio.h>
#include <string.h>

#include "cookie.h"
#include "browser.h"
#include "tab.h"
#include "tools.h"
#include "webview.h"

BrowserTab tab[16] = {0};
BrowserTabID ID = 0, TabPosition = 1;
BrowserTabID tab_count = 0;

/* =========================================================================== */

static void
update_tab_id(gpointer data)
{
  ID = GPOINTER_TO_INT(data);
}

static void
update_tab_url(char* url, GtkWidget* entry)
{
  if (fb_sdk_webview_get_view() == 1)
  { strcpy(url, gtk_entry_get_text(GTK_ENTRY(entry))); }
}

/* --------------------------------------------------------------------------- */

static void
on_url_change(GtkWidget* widget, gpointer data)
{
  update_tab_id(data);

  update_tab_url(tab[ID].url, widget);
}

static void
on_url_update(WebKitWebView* web, GParamSpec* pspec, gpointer data)
{
  update_tab_id(data);

  if (fb_sdk_webview_get_view() == 1)
  { gtk_entry_set_text(GTK_ENTRY(FB.widget.url), webkit_web_view_get_uri(fb_sdk_webview_get_reference())); }

  update_tab_url(tab[ID].url, FB.widget.url);
}

static void
on_url_search(GtkWidget* widget, gpointer data)
{
  update_tab_id(data);

  fb_sdk_webview_search_url(tab[ID].url);
}

static void
on_search_click(GtkButton* button, gpointer data)
{
  update_tab_id(data);

  if (fb_sdk_webview_get_view() == 1)
  { on_url_search(NULL, data); }
}

/* --------------------------------------------------------------------------- */

static void
on_url_history_back(GtkButton* button, gpointer data)
{
  fb_sdk_webview_go_back_on_history();
}

static void
on_url_history_forward(GtkButton* button, gpointer data)
{
  fb_sdk_webview_go_forward_on_history();
}

static void
on_url_reload(GtkButton* button, gpointer data)
{
  fb_sdk_webview_reload_page();
}

/* --------------------------------------------------------------------------- */

static void
close_tab(void)
{
  FB_SDK_WebViewReference* web_view_reference = fb_sdk_webview_get_reference();
  if (tab[ID].web == web_view_reference)
  {
    control_web_view_reference(0);
    fb_sdk_webview_set_reference(NULL);
  }

  tab[ID].ID = 0;
  memset(tab[ID].title, '\0', sizeof(tab[ID].title));
  memset(tab[ID].url, '\0', sizeof(tab[ID].url));

  gtk_widget_destroy(GTK_WIDGET(tab[ID].web));
  gtk_widget_destroy(tab[ID].button.close);
  gtk_widget_destroy(tab[ID].button.tab);
  gtk_widget_destroy(tab[ID].box.button);
  TabPosition--;

  tab[ID].garbage = 1;
}

static void
set_tab_url(const char* url)
{
  gtk_entry_set_text(GTK_ENTRY(FB.widget.url), url);
}

static void
set_tab_title(const char* title)
{
  if (title == NULL) { return; }
  int titlelen = strlen(title);
  if (titlelen < 1) { return; }

  strncpy(tab[ID].title, title, 23);
  tab[ID].title[23] = '\0';
  switch (titlelen)
  {
    case 0 ... 23: break;
    default:
    {
      char c = 0;
      if ((tab[ID].title[20] != '.') &&
          (tab[ID].title[21] != '.') &&
          (tab[ID].title[22] != '.'))
      { c = '.'; }

      tab[ID].title[20] = c;
      tab[ID].title[21] = c;
      tab[ID].title[22] = c;
    } break;
  }

  gtk_button_set_label(GTK_BUTTON(tab[ID].button.tab), tab[ID].title);
}

static void
on_tab_click(GtkButton* button, gpointer data)
{
  control_web_view_reference(0);

  update_tab_id(data);
  set_tab_url(tab[ID].url);
  fb_sdk_webview_set_reference(tab[ID].web);

  control_web_view_reference(1);
}

static void
on_tab_close(GtkButton* button, gpointer data)
{
  update_tab_id(data);
  close_tab();

  FB_SDK_WebViewReference* web_view_reference = fb_sdk_webview_get_reference();
  if (web_view_reference == NULL)
  {
    ID++;
    if (tab[ID].ID == 0)
    {
      char i = 0;
      for (i=tab_count; i>=0; i--)
      {
        if (tab[i].garbage == 0)
        { ID = tab[i].ID; }
      }
    }

    if (ID < tab_count)
    {
      set_tab_url(tab[ID].url);
      fb_sdk_webview_set_reference(tab[ID].web);

      control_web_view_reference(1);
    }
  }
}

static void
update_tab_title(WebKitWebView* web, GParamSpec* pspec, gpointer data)
{
  update_tab_id(data);

  FB_SDK_WebViewReference* web_view_reference = fb_sdk_webview_get_reference();
  set_tab_title(webkit_web_view_get_title(web_view_reference));
}

/* =========================================================================== */

BrowserTabID
fb_sdk_create_new_tab(GtkWidget* container)
{
  control_web_view_reference(0);

  BrowserTabID ID = tab[tab_count].ID = tab_count;

  unsigned char countTabIncrease = 1;
  if (ID > 0)
  {
    BrowserTabID i = 0;
    for (i=0; i<=tab_count; i++)
    {
      if (tab[i].garbage == 1)
      { ID = i; tab[ID].ID = ID; tab[ID].garbage = 0; countTabIncrease = 0; break; }
    }
  }

  sprintf(tab[ID].title, "New tab");

  tab[ID].box.button = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(container), tab[ID].box.button, FALSE, FALSE, 3);

  tab[ID].button.tab = gtk_button_new_with_label(tab[ID].title);
  gtk_box_pack_start(GTK_BOX(tab[ID].box.button), tab[ID].button.tab, FALSE, FALSE, 0);

  tab[ID].button.close = gtk_button_new_with_label("X");
  gtk_box_pack_start(GTK_BOX(tab[ID].box.button), tab[ID].button.close, FALSE, FALSE, 0);

  gtk_box_reorder_child(GTK_BOX(container), tab[ID].box.button, TabPosition-1);
  TabPosition++;

  FB_SDK_WebViewReference* web_view_reference = fb_sdk_webview_get_reference();
  web_view_reference = tab[ID].web = WEBKIT_WEB_VIEW(webkit_web_view_new());
  gtk_box_pack_start(GTK_BOX(FB.box.main), GTK_WIDGET(web_view_reference), TRUE, TRUE, 0);
  fb_sdk_webview_set_reference(web_view_reference);

  g_signal_connect(tab[ID].button.tab,    "clicked",        G_CALLBACK(on_tab_click),           GINT_TO_POINTER(ID));
  g_signal_connect(tab[ID].button.close,  "clicked",        G_CALLBACK(on_tab_close),           GINT_TO_POINTER(ID));

  g_signal_connect(web_view_reference,    "load-changed",   G_CALLBACK(on_cookie_handle),       GINT_TO_POINTER(ID));
  g_signal_connect(web_view_reference,    "notify::uri",    G_CALLBACK(on_url_update),          GINT_TO_POINTER(ID));
  g_signal_connect(web_view_reference,    "notify::title",  G_CALLBACK(update_tab_title),       GINT_TO_POINTER(ID));

  g_signal_connect(FB.widget.url,         "changed",        G_CALLBACK(on_url_change),          GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.url,         "activate",       G_CALLBACK(on_url_search),          GINT_TO_POINTER(ID));

  g_signal_connect(FB.widget.back,        "clicked",        G_CALLBACK(on_url_history_back),    GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.forward,     "clicked",        G_CALLBACK(on_url_history_forward), GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.reload,      "clicked",        G_CALLBACK(on_url_reload),          GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.search,      "clicked",        G_CALLBACK(on_search_click),        GINT_TO_POINTER(ID));

  char *html_file = load_html_file(ROOT.assets.launcher);
  if (html_file == NULL)
  {
    strcpy(tab[ID].url, "https://html.duckduckgo.com/html/");
    set_tab_url(tab[ID].url);
    on_url_search(NULL, GINT_TO_POINTER(ID));
  }
  else
  {
    webkit_web_view_load_html(web_view_reference, html_file, NULL);
    free(html_file);
  }
  on_cookie_handle(web_view_reference, (WebKitLoadEvent)WEBKIT_LOAD_FINISHED, GINT_TO_POINTER(ID));
  control_web_view_reference(1);

  if (countTabIncrease == 1)
  {
    tab_count++;
  }

  return ID;
}

BrowserTab
fb_sdk_get_tab(BrowserTabID ID)
{
  return tab[ID];
}

/*
TODO: Dynamic tabs.

void
fb_sdk_free_tab(BrowserTab* tab)
{
  BrowserTabID i = 0;
  for (i=0; i<tab_count; i++)
  {
    g_object_unref(tab[i].web);
  }
  free(tab);
}
*/

