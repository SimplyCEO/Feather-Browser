#define __GTKE_WEBVIEW_USE_COOKIES__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tab.h"

#include "tools.h"
#include "browser.h"

BrowserTab**   tab     = NULL;
BrowserTab*    tab_ptr = NULL;
BrowserTabSize tab_max = 0;

/* =========================================================================== */

static BrowserTab*
browser_tab_init(BrowserTabSize index)
{
  BrowserTab* object = NULL;

  if (index < 0)
  {
    object = (BrowserTab*)malloc(sizeof(BrowserTab));

    object->container.title[0] = 0;
    object->container.url[0] = 0;

    object->widget.webview = NULL;
    object->container.button = NULL;
    object->container.webview = NULL;
    object->widget.title = NULL;
    object->widget.close = NULL;

    return object;
  }

  BrowserTabSize i = 0;
  for (; tab[i] != NULL; ++i) {}
  --i;

  if (index > i)
  {
    index = i;
  }

  object = tab[index];

  strcpy(object->container.title, "New Tab");
  strcpy(object->container.url, "http://html.duckduckgo.com/html/");

  if (object->active != BROWSER_TAB_ACTIVE)
  {
    object->widget.webview     = gtke_webview_new(feather.path.user.cookies);
    object->container.button   = gtke_container_new(GTKE_ORIENTATION_HORIZONTAL, 0);
    object->container.webview  = gtke_container_new(GTKE_ORIENTATION_VERTICAL, 0);
    object->widget.title       = gtke_text_new(object->container.title);
    object->widget.close       = gtke_button_new("x");

    gtke_container_add(GTKE_CONTAINER_START, object->container.button,   object->widget.title,    false,  false,  0);
    gtke_container_add(GTKE_CONTAINER_START, object->container.button,   object->widget.close,    false,  false,  3);
    gtke_container_add(GTKE_CONTAINER_START, object->container.webview,  object->widget.webview,  true,   true,   0);
  }

  object->active = BROWSER_TAB_ACTIVE;

  return object;
}

static BrowserTabSize
browser_tab_alloc(void)
{
  if (tab != NULL)
  {
    BrowserTabSize i = 0;
    BrowserTabSize size = 0;

    for (; ((tab[i] != NULL) && (tab[i]->active != BROWSER_TAB_GARBAGE)); ++i)
    {
      switch (tab[i]->active)
      {
        case BROWSER_TAB_ACTIVE: break;
        case BROWSER_TAB_GARBAGE: return i;
        default: tab[i]->active = BROWSER_TAB_INACTIVE; break;
      }
    }

    size = i + 2;

    BrowserTab** tab_realloc = (BrowserTab**)realloc(tab, size*sizeof(*tab));
    if (tab_realloc == NULL)
    { return i-1; }
    tab = tab_realloc;

    for (; i < size - 1; ++i)
    {
      tab[i] = browser_tab_init(-1);
    }
    tab[i] = NULL;

    return i-1;
  }

  tab = (BrowserTab**)malloc(2*sizeof(BrowserTab*));
  tab[0] = browser_tab_init(-1);
  tab[1] = NULL;

  return 0;
}

static void
browser_tab_free(BrowserTabSize index)
{
  if (index < 0)
  {
    BrowserTabSize i = 0;

    for (; tab[i] != NULL; ++i)
    {
      free((void*)tab[i]);
      tab[i] = NULL;
    }
    free((void*)tab);
    tab = NULL;

    return;
  }

  BrowserTabSize i = 0;
  for (; tab[i] != NULL; ++i) {}
  --i;

  if (index > i)
  {
    index = i;
  }

  BrowserTab* ptr = tab[index];

  ptr->active = BROWSER_TAB_GARBAGE;

  if (index == 0)
  {
    if (tab_max == 1)
    {
      gtk_main_quit();
      return;
    }

    gtke_page_move_forward(feather.widget.tab);
    gtke_page_remove(feather.widget.tab, index);
    return;
  }

  if (index == gtke_page_get_current_index(feather.widget.tab))
  { gtke_page_move_backwards(feather.widget.tab); }

  gtke_page_remove(feather.widget.tab, index);
}

/* =========================================================================== */

static void
update_tab_url(GtkEWidget* entry, char* url)
{
  strcpy(url, gtke_entry_get_text(entry));

  gtke_widget_update(entry);
}

/* --------------------------------------------------------------------------- */

static void
on_url_update(GtkEWebView* webview, GParamSpec* pspec, void* data)
{
  if (webview == NULL) { return; }

  BrowserTabSize index = GPOINTER_TO_INT(data);

  if (gtke_webview_get_visible(GTK_WIDGET(webview)) == true)
  { gtke_entry_set_text(feather.widget.url, gtke_webview_get_uri(GTK_WIDGET(webview))); }

  update_tab_url(feather.widget.url, tab[index]->container.url);
}

static void
on_url_load(GtkEWebView* webview, WebKitLoadEvent event, void* data)
{
  if (webview == NULL) { return; }

  /* Temporary fix for new tab button */
  if (gtke_page_get_current_index(feather.widget.tab) == gtke_page_index_count(feather.widget.tab)) { gtke_page_move_backwards(feather.widget.tab); }

  char* button_label = NULL;

  switch (event)
  {
    case WEBKIT_LOAD_STARTED: button_label = "X"; break;
    case WEBKIT_LOAD_FINISHED: button_label = "↑↓"; break;
    default: break;
  }

  gtke_button_set_label(feather.widget.reload, button_label);
}

/* --------------------------------------------------------------------------- */

static void
set_tab_url(BrowserTab* object, const char* url)
{
  if (url == NULL)
  {
    gtke_entry_set_text(feather.widget.url, gtke_webview_get_uri(object->widget.webview));
    return;
  }

  gtke_entry_set_text(feather.widget.url, url);
}

static void
set_tab_title(BrowserTab* object, const char* title)
{
  if (title == NULL) { return; }

  uint8_t i = 0;

  memset(object->container.title, ' ', 30);
  object->container.title[31] = '\0';
  strncpy(object->container.title, title, 30);

  switch (strlen(title))
  {
    case 0 ... 27: break;
    default:
    {
      if (object->container.title[27] == ' ') { break; }
      for (i=0; i<=2; i++) { object->container.title[28+i] = '.'; }
    } break;
  }

  gtke_text_rename(object->widget.title, object->container.title);
}

static void
on_tab_click(GtkEButton* button, void* data)
{
  BrowserTabSize index = GPOINTER_TO_INT(data);

  set_tab_url(tab[index], NULL);
}

static void
on_tab_close(GtkEButton* button, void* data)
{
  if (button == NULL) { return; }

  browser_tab_free(GPOINTER_TO_INT(data));
}

static void
update_tab_title(GtkEWebView* webview, GParamSpec* pspec, void* data)
{
  if (webview == NULL) { return; }

  BrowserTabSize index = GPOINTER_TO_INT(data);

  set_tab_title(tab[index], gtke_webview_get_title(GTK_WIDGET(webview)));
}

/* =========================================================================== */

void
fb_sdk_on_url_change(GtkEWidget* widget, void* data)
{
  BrowserTabSize index = gtke_page_get_current_index(feather.widget.tab);
  if (index == tab_max) { --index; gtke_page_move_backwards(feather.widget.tab); }

  update_tab_url(widget, tab[index]->container.url);
}

void
fb_sdk_on_url_search(GtkEWidget* widget, void* data)
{
  if (data != NULL) { gtke_webview_search(widget, data); return; }

  BrowserTabSize index = gtke_page_get_current_index(feather.widget.tab);
  if (index == tab_max) { --index; gtke_page_move_backwards(feather.widget.tab); }

  gtke_webview_search(tab[index]->widget.webview, tab[index]->container.url);
}

void
fb_sdk_on_search_click(GtkEButton* button, void* data)
{
  BrowserTabSize index = gtke_page_get_current_index(feather.widget.tab);
  if (index == tab_max) { --index; gtke_page_move_backwards(feather.widget.tab); }

  fb_sdk_on_url_search(tab[index]->widget.webview, NULL);
}

void
fb_sdk_on_url_history_back(GtkEButton* button, void* data)
{
  BrowserTabSize index = gtke_page_get_current_index(feather.widget.tab);
  if (index == tab_max) { --index; gtke_page_move_backwards(feather.widget.tab); }

  gtke_webview_go_back(tab[index]->widget.webview);
}

void
fb_sdk_on_url_history_forward(GtkEButton* button, void* data)
{
  BrowserTabSize index = gtke_page_get_current_index(feather.widget.tab);
  if (index == tab_max) { --index; gtke_page_move_backwards(feather.widget.tab); }

  gtke_webview_go_forward(tab[index]->widget.webview);
}

void
fb_sdk_on_url_reload(GtkEButton* button, void* data)
{
  BrowserTabSize index = gtke_page_get_current_index(feather.widget.tab);
  if (index == tab_max) { --index; gtke_page_move_backwards(feather.widget.tab); }

  gtke_webview_reload(tab[index]->widget.webview, button);
}

/* =========================================================================== */

int32_t
fb_sdk_create_new_tab(GtkEWidget* widget, void* data)
{
  tab_max = gtke_page_index_count(feather.widget.tab);
  BrowserTabSize object_index = browser_tab_alloc();
  BrowserTab* object = tab[object_index];

  object = browser_tab_init(object_index);
  object->index = tab_max - 1;

  tab_ptr = object;

  GtkEWebView* webview = WEBKIT_WEB_VIEW(object->widget.webview);
  g_signal_connect(webview, "load-changed",   G_CALLBACK(on_url_load),      GINT_TO_POINTER(object->index));
  g_signal_connect(webview, "notify::uri",    G_CALLBACK(on_url_update),    GINT_TO_POINTER(object->index));
  g_signal_connect(webview, "notify::title",  G_CALLBACK(update_tab_title), GINT_TO_POINTER(object->index));
  set_tab_url(object, object->container.url);
  fb_sdk_on_url_search(object->widget.webview, object->container.url);

  g_signal_connect(object->widget.close, "clicked", G_CALLBACK(on_tab_close), GINT_TO_POINTER(object->index));

  gtke_page_append(feather.widget.tab, object->container.button, object->container.webview);
  gtke_page_move_worker(feather.widget.tab, object->container.webview, object->index);
  gtke_page_move_backwards(feather.widget.tab);

  gtke_widget_update(feather.widget.tab);

  return 0;
}

void
fb_sdk_page_switch(GtkNotebook* page, GtkEWidget* worker, int32_t index, void* data)
{
  BrowserTabSize i = 0;
  BrowserTab** ptr = tab;

  for (; *ptr != NULL; ptr++)
  {
    if ((*ptr)->active == BROWSER_TAB_ACTIVE)
    { (*ptr)->index = i++; }
  }

  if (index < gtke_page_index_count(feather.widget.tab) - 1)
  {
    set_tab_url(tab[index], NULL);
    return;
  }

  fb_sdk_create_new_tab(worker, GINT_TO_POINTER(index));
}

void
fb_sdk_free_tab(void)
{
  browser_tab_free(-1);
}

