#include <gtk/gtk.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "widgets.h"
#include "tools.h"
#include "browser.h"
#include "cookie.h"
#include "tab.h"

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
update_tab_url(char* url, FBWidget* entry)
{
  if (WebView.Visible(SELF) == true)
  { strcpy(url, Entry.GetLabel(entry)); }
}

/* --------------------------------------------------------------------------- */

static void
on_url_change(FBWidget* widget, gpointer data)
{
  update_tab_id(data);

  update_tab_url(tab[ID].url, widget);
}

static void
on_url_update(FBWebView* web_view, GParamSpec* pspec, gpointer data)
{
  update_tab_id(data);

  if (WebView.Visible(web_view) == true)
  { Entry.SetLabel(FB.widget.url, WebView.GetURI(web_view)); }

  update_tab_url(tab[ID].url, FB.widget.url);
}

static void
on_url_search(FBWidget* widget, gpointer data)
{
  update_tab_id(data);

  WebView.Search(SELF, tab[ID].url);
}

static void
on_search_click(FBButton* button, gpointer data)
{
  update_tab_id(data);

  if (WebView.Visible(SELF) == true)
  { on_url_search(NULL, data); }
}

/* --------------------------------------------------------------------------- */

static void
on_url_history_back(FBButton* button, gpointer data)
{
  if (WebView.CanGoBack(SELF) == true)
  { WebView.BackHistory(SELF); }
}

static void
on_url_history_forward(FBButton* button, gpointer data)
{
  if (WebView.CanGoForward(SELF) == true)
  { WebView.ForwardHistory(SELF); }
}

static void
on_url_load(FBWebView* web_view, WebKitLoadEvent event, gpointer data)
{
  char* button_label = NULL;

  switch (event)
  {
    case WEBKIT_LOAD_STARTED: button_label = "X"; break;
    case WEBKIT_LOAD_FINISHED: button_label = "↑↓"; break;
    default: break;
  }

  Button.SetLabel(FB.widget.reload, button_label);
}

static void
on_url_reload(FBButton* button, gpointer data)
{
  WebView.Reload(SELF, button);
}

/* --------------------------------------------------------------------------- */

static void
set_tab_url(const char* url)
{
  if (url != NULL)
  {
    Entry.SetLabel(FB.widget.url, url);
    return;
  }

  Entry.SetLabel(FB.widget.url, WebView.GetURI(SELF));
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

  Button.SetLabel(tab[ID].button.tab, tab[ID].title);
}

static void
on_tab_click(FBButton* button, gpointer data)
{
  update_tab_id(data);

  WebView.Control(SELF, (FBWebViewMode)WEBVIEW_HIDE);

  WebView.SetMaster(tab[ID].web);
  set_tab_url(NULL);

  WebView.Control(SELF, (FBWebViewMode)WEBVIEW_SHOW);
}

static void
on_tab_close(FBButton* button, gpointer data)
{
  update_tab_id(data);

  if (tab[ID].web == WebView.GetMaster())
  {
    WebView.Control(SELF, (FBWebViewMode)WEBVIEW_HIDE);
    WebView.SetMaster(NULL);
  }

  tab[ID].ID = 0;
  memset(tab[ID].title, '\0', sizeof(tab[ID].title));
  memset(tab[ID].url, '\0', sizeof(tab[ID].url));

  Widget.Destroy(GTK_WIDGET(tab[ID].web));
  Widget.Destroy(tab[ID].button.close);
  Widget.Destroy(tab[ID].button.tab);
  Widget.Destroy(tab[ID].box.button);
  TabPosition--;

  tab[ID].garbage = true;

  if (WebView.GetMaster() == NULL)
  {
    ID++;
    if (tab[ID].ID == 0)
    {
      int i = tab_count; for (; i>=0; i--)
      {
        if (tab[i].garbage == false)
        { ID = tab[i].ID; }
      }
    }

    if (ID < tab_count)
    {
      set_tab_url(tab[ID].url);
      WebView.SetMaster(tab[ID].web);

      WebView.Control(SELF, (FBWebViewMode)WEBVIEW_SHOW);
    }
  }
}

static void
update_tab_title(FBWebView* web_view, GParamSpec* pspec, gpointer data)
{
  update_tab_id(data);

  set_tab_title(WebView.GetTitle(web_view));
}

/* =========================================================================== */

BrowserTabID
fb_sdk_create_new_tab(FBWidget* container)
{
  WebView.Control(SELF, (FBWebViewMode)WEBVIEW_HIDE);

  BrowserTabID ID = tab[tab_count].ID = tab_count;

  bool countTabIncrease = true;
  if (ID > 0)
  {
    BrowserTabID i = 0; for (; i<=tab_count; i++)
    {
      if (tab[i].garbage == true)
      { ID = i; tab[i].ID = i; tab[i].garbage = false; countTabIncrease = false; break; }
    }
  }

  sprintf(tab[ID].title, "New tab");

  tab[ID].box.button = Box.Create((FBOrientation)BOX_ORIENTATION_HORIZONTAL, 0);
  tab[ID].button.tab = Button.Create(tab[ID].title);
  tab[ID].button.close = Button.Create("X");
  tab[ID].web = WebView.Create();

  Box.PositionStart(container, tab[ID].box.button, FALSE, FALSE, 3);
  Box.PositionStart(tab[ID].box.button, tab[ID].button.tab, FALSE, FALSE, 0);
  Box.PositionStart(tab[ID].box.button, tab[ID].button.close, FALSE, FALSE, 0);
  Box.PositionStart(FB.box.web, GTK_WIDGET(tab[ID].web), TRUE, TRUE, 0);
  Box.Move(container, tab[ID].box.button, TabPosition-1);
  TabPosition++;

  /* TODO: Fix `on_tab_click` bug where it is needed to double select a tab in order to switch. */
  g_signal_connect(tab[ID].button.tab,    "clicked",        G_CALLBACK(on_tab_click),           GINT_TO_POINTER(tab[ID].ID));
  g_signal_connect(tab[ID].button.tab,    "clicked",        G_CALLBACK(on_tab_click),           GINT_TO_POINTER(tab[ID].ID));
  g_signal_connect(tab[ID].button.close,  "clicked",        G_CALLBACK(on_tab_close),           GINT_TO_POINTER(tab[ID].ID));

  g_signal_connect(tab[ID].web,           "load-changed",   G_CALLBACK(on_url_load),            GINT_TO_POINTER(tab[ID].ID));
  g_signal_connect(tab[ID].web,           "load-changed",   G_CALLBACK(on_cookie_handle),       NULL);
  g_signal_connect(tab[ID].web,           "notify::uri",    G_CALLBACK(on_url_update),          GINT_TO_POINTER(tab[ID].ID));
  g_signal_connect(tab[ID].web,           "notify::title",  G_CALLBACK(update_tab_title),       GINT_TO_POINTER(tab[ID].ID));

  g_signal_connect(FB.widget.url,         "changed",        G_CALLBACK(on_url_change),          GINT_TO_POINTER(tab[ID].ID));
  g_signal_connect(FB.widget.url,         "activate",       G_CALLBACK(on_url_search),          GINT_TO_POINTER(tab[ID].ID));

  g_signal_connect(FB.widget.back,        "clicked",        G_CALLBACK(on_url_history_back),    GINT_TO_POINTER(tab[ID].ID));
  g_signal_connect(FB.widget.forward,     "clicked",        G_CALLBACK(on_url_history_forward), GINT_TO_POINTER(tab[ID].ID));
  g_signal_connect(FB.widget.reload,      "clicked",        G_CALLBACK(on_url_reload),          GINT_TO_POINTER(tab[ID].ID));
  g_signal_connect(FB.widget.search,      "clicked",        G_CALLBACK(on_search_click),        GINT_TO_POINTER(tab[ID].ID));

  on_cookie_handle(tab[ID].web, (WebKitLoadEvent)WEBKIT_LOAD_FINISHED, NULL);
  WebView.SetMaster(tab[ID].web);

  char *html_file = load_html_file(ROOT.assets.launcher);
  if (html_file == NULL)
  {
    strcpy(tab[ID].url, "https://html.duckduckgo.com/html/");
    set_tab_url(tab[ID].url);
    on_url_search(NULL, GINT_TO_POINTER(ID));
  }
  else
  {
    WebView.LoadHTML(tab[ID].web, html_file, NULL);
    free(html_file);
  }

  if (countTabIncrease == true)
  {
    tab_count++;
  }

  WebView.Control(SELF, (FBWebViewMode)WEBVIEW_SHOW);

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

