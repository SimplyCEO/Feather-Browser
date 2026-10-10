#ifndef TAB_HEADER
#define TAB_HEADER

#include <gtke/page.h>
#include <gtke/webview.h>

typedef int BrowserTabSize;

typedef enum BrowserTabActivity
{
  BROWSER_TAB_INACTIVE = 0,
  BROWSER_TAB_ACTIVE,
  BROWSER_TAB_GARBAGE
} BrowserTabActivity;

typedef struct BrowserTab
{
  BrowserTabSize      index;
  BrowserTabActivity  active;
  struct BrowsetTabContainer
  {
    GtkEWidget* button;
    GtkEWidget* webview;
    char        title[32];
    char        url[2048];
  } container;
  struct BrowserTabWidget
  {
    GtkEWidget* title;
    GtkEWidget* close;
    GtkEWidget* webview;
  } widget;
} BrowserTab;

void    fb_sdk_on_url_change(GtkEWidget* widget, void* data);
void    fb_sdk_on_url_search(GtkEWidget* widget, void* data);
void    fb_sdk_on_search_click(GtkEButton* button, void* data);
void    fb_sdk_on_url_history_back(GtkEButton* button, void* data);
void    fb_sdk_on_url_history_forward(GtkEButton* button, void* data);
void    fb_sdk_on_url_reload(GtkEButton* button, void* data);
int32_t fb_sdk_create_new_tab(GtkEWidget* widget, void* data);
void    fb_sdk_page_switch(GtkNotebook* page, GtkEWidget* worker, int32_t index, void* data);
void    fb_sdk_free_tab(void);

extern BrowserTab** tab;

#endif

