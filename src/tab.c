#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#include <stdio.h>
#include <string.h>

#include "cookie.h"
#include "browser.h"
#include "tab.h"

void* web_view_reference = NULL;

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


/* --------------------------------------------------------------------------- */

static void
on_url_change(GtkWidget* widget, gpointer data)
{
  update_tab_id(data);

  if (gtk_widget_get_visible(GTK_WIDGET(web_view_reference)))
  { strcpy(tab[ID].url, gtk_entry_get_text(GTK_ENTRY(widget))); }
}

static void
on_url_update(WebKitWebView* web, GParamSpec* pspec, gpointer data)
{
  update_tab_id(data);

  if (gtk_widget_get_visible(GTK_WIDGET(web_view_reference)))
  {
    strcpy(tab[ID].url, webkit_web_view_get_uri(web_view_reference));
    gtk_entry_set_text(GTK_ENTRY(FB.widget.url), tab[ID].url);
  }
}

static void
on_url_search(GtkWidget* widget, gpointer data)
{
  update_tab_id(data);

  if ((strncmp(tab[ID].url, "http://", 7) != 0) & (strncmp(tab[ID].url, "https://", 8) != 0))
  {
    unsigned char website = 0, ip = 0;
    unsigned short i = 0, urllen = strlen(tab[ID].url)+1;
    for (i=0; i<urllen; i++)
    {
      switch (tab[ID].url[i])
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
      { strcpy(buffer, "https://duckduckgo.com/?q="); }
      strcat(buffer, tab[ID].url);
      strcpy(tab[ID].url, buffer);
    }
  }

  webkit_web_view_load_uri(web_view_reference, tab[ID].url);
}

static void
on_search_click(GtkButton* button, gpointer data)
{
  update_tab_id(data);

  if (gtk_widget_get_visible(GTK_WIDGET(web_view_reference)))
  { on_url_search(NULL, data); }
}

/* --------------------------------------------------------------------------- */

static void
on_url_history_back(GtkButton* button, gpointer data)
{
  update_tab_id(data);

  if (webkit_web_view_can_go_back(web_view_reference))
  { webkit_web_view_go_back(web_view_reference); }
}

static void
on_url_history_forward(GtkButton* button, gpointer data)
{
  update_tab_id(data);

  if (webkit_web_view_can_go_forward(web_view_reference))
  { webkit_web_view_go_forward(web_view_reference); }
}

static void
on_url_reload(GtkButton* button, gpointer data)
{
  update_tab_id(data);

  webkit_web_view_reload(web_view_reference);
}

/* --------------------------------------------------------------------------- */

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

  gtk_button_set_label(GTK_BUTTON(tab[ID].button), tab[ID].title);
}

static void
on_tab_click(GtkButton* button, gpointer data)
{
  control_web_view_reference(0);

  update_tab_id(data);
  set_tab_url(tab[ID].url);
  web_view_reference = tab[ID].web;

  control_web_view_reference(1);
}

static void
update_tab_title(WebKitWebView* web, GParamSpec* pspec, gpointer data)
{
  update_tab_id(data);

  set_tab_title(webkit_web_view_get_title(web_view_reference));
}

/* =========================================================================== */

BrowserTabID
fb_sdk_create_new_tab(GtkWidget* container)
{
  control_web_view_reference(0);

  BrowserTabID ID = tab[tab_count].ID = tab_count;

  sprintf(tab[ID].title, "New tab");

  tab[ID].button = gtk_button_new_with_label(tab[ID].title);
  gtk_box_pack_start(GTK_BOX(container), tab[ID].button, FALSE, FALSE, 3);
  gtk_box_reorder_child(GTK_BOX(container), tab[ID].button, TabPosition-1);
  TabPosition++;

  web_view_reference = tab[ID].web = WEBKIT_WEB_VIEW(webkit_web_view_new());
  gtk_box_pack_start(GTK_BOX(FB.box.main), GTK_WIDGET(web_view_reference), TRUE, TRUE, 0);
  strcpy(tab[ID].url, "https://simplyceo.github.io/main_page");

  g_signal_connect(tab[ID].button,        "clicked",        G_CALLBACK(on_tab_click),           GINT_TO_POINTER(ID));

  g_signal_connect(web_view_reference,    "load-changed",   G_CALLBACK(on_cookie_handle),       GINT_TO_POINTER(ID));
  g_signal_connect(web_view_reference,    "notify::uri",    G_CALLBACK(on_url_update),          GINT_TO_POINTER(ID));
  g_signal_connect(web_view_reference,    "notify::title",  G_CALLBACK(update_tab_title),       GINT_TO_POINTER(ID));

  g_signal_connect(FB.widget.url,         "changed",        G_CALLBACK(on_url_change),          GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.url,         "activate",       G_CALLBACK(on_url_search),          GINT_TO_POINTER(ID));

  g_signal_connect(FB.widget.back,        "clicked",        G_CALLBACK(on_url_history_back),    GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.forward,     "clicked",        G_CALLBACK(on_url_history_forward), GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.reload,      "clicked",        G_CALLBACK(on_url_reload),          GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.search,      "clicked",        G_CALLBACK(on_search_click),        GINT_TO_POINTER(ID));

  on_url_search(NULL, GINT_TO_POINTER(ID));
  on_cookie_handle(web_view_reference, (WebKitLoadEvent)WEBKIT_LOAD_FINISHED, GINT_TO_POINTER(ID));
  control_web_view_reference(1);

  tab_count++;

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

