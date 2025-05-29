#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#include <stdio.h>
#include <string.h>

#include "cookie.h"
#include "browser.h"
#include "tab.h"

WebKitWebView* tmp_web_view = NULL;

BrowserTab tab[16] = {0};
BrowserTabID ID = 0;
BrowserTabID tab_count = 0;

/* =========================================================================== */

static void
update_tab_id(gpointer data)
{
  ID = GPOINTER_TO_INT(data);
}

static void
hide_tmp_web_view(void)
{
  if (tmp_web_view != NULL)
  { gtk_widget_hide(GTK_WIDGET(tmp_web_view)); }
}


/* --------------------------------------------------------------------------- */

static void
on_url_change(GtkWidget* widget, gpointer data)
{
  update_tab_id(data);

  if (gtk_widget_get_visible(GTK_WIDGET(tab[ID].web)))
  { strcpy(tab[ID].url, gtk_entry_get_text(GTK_ENTRY(widget))); }
}

static void
on_url_update(WebKitWebView* web, GParamSpec* pspec, gpointer data)
{
  update_tab_id(data);

  if (gtk_widget_get_visible(GTK_WIDGET(tab[ID].web)))
  {
    strcpy(tab[ID].url, webkit_web_view_get_uri(tab[ID].web));
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

  webkit_web_view_load_uri(tab[ID].web, tab[ID].url);
}

static void
on_search_click(GtkButton* button, gpointer data)
{
  update_tab_id(data);

  if (gtk_widget_get_visible(GTK_WIDGET(tab[ID].web)))
  { on_url_search(NULL, tab[ID].web); }
}

/* --------------------------------------------------------------------------- */

static void
on_url_history_back(GtkButton* button, gpointer data)
{
  update_tab_id(data);

  if (webkit_web_view_can_go_back(tab[ID].web))
  { webkit_web_view_go_back(tab[ID].web); }
}

static void
on_url_history_forward(GtkButton* button, gpointer data)
{
  update_tab_id(data);

  if (webkit_web_view_can_go_forward(tab[ID].web))
  { webkit_web_view_go_forward(tab[ID].web); }
}

static void
on_url_reload(GtkButton* button, gpointer data)
{
  update_tab_id(data);

  webkit_web_view_reload(tab[ID].web);
}

/* --------------------------------------------------------------------------- */

static void
set_tab_url(const char* url)
{
  gtk_entry_set_text(GTK_ENTRY(FB.widget.url), tab[ID].url);
}

static void
on_tab_click(GtkButton* button, gpointer data)
{
  update_tab_id(data);

  set_tab_url(tab[ID].url);

  hide_tmp_web_view();

  gtk_widget_show(GTK_WIDGET(tab[ID].web));
  tmp_web_view = tab[ID].web;
}

/* =========================================================================== */

BrowserTabID
fb_sdk_create_new_tab(GtkWidget* container)
{
  hide_tmp_web_view();

  BrowserTabID ID = tab[tab_count].ID = tab_count;

  sprintf(tab[ID].title, "New tab %d", ID+1);

  tab[ID].button = gtk_button_new_with_label(tab[ID].title);
  gtk_box_pack_start(GTK_BOX(container), tab[ID].button, FALSE, FALSE, 3);

  tab[ID].web = WEBKIT_WEB_VIEW(webkit_web_view_new());
  gtk_box_pack_start(GTK_BOX(FB.box.main), GTK_WIDGET(tab[ID].web), TRUE, TRUE, 0);
  strcpy(tab[ID].url, "https://simplyceo.github.io/main_page");

  g_signal_connect(tab[ID].button,        "clicked",      G_CALLBACK(on_tab_click),           GINT_TO_POINTER(ID));

  g_signal_connect(tab[ID].web,           "load-changed", G_CALLBACK(on_cookie_handle),       GINT_TO_POINTER(ID));
  g_signal_connect(tab[ID].web,           "notify::uri",  G_CALLBACK(on_url_update),          GINT_TO_POINTER(ID));

  g_signal_connect(FB.widget.url,         "changed",      G_CALLBACK(on_url_change),          GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.url,         "activate",     G_CALLBACK(on_url_search),          GINT_TO_POINTER(ID));

  g_signal_connect(FB.widget.back,        "clicked",      G_CALLBACK(on_url_history_back),    GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.forward,     "clicked",      G_CALLBACK(on_url_history_forward), GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.reload,      "clicked",      G_CALLBACK(on_url_reload),          GINT_TO_POINTER(ID));
  g_signal_connect(FB.widget.search,      "clicked",      G_CALLBACK(on_search_click),        GINT_TO_POINTER(ID));

  on_url_search(NULL, GINT_TO_POINTER(ID));
  on_cookie_handle(tab[ID].web, (WebKitLoadEvent)WEBKIT_LOAD_FINISHED, GINT_TO_POINTER(ID));
  tmp_web_view = tab[ID].web;

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

