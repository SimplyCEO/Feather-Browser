#ifndef TAB_HEADER
#define TAB_HEADER

typedef unsigned char BrowserTabID;

typedef struct BrowserTab
{
  BrowserTabID    ID;
  WebKitWebView*  web;
  struct BrowsetTabContainer
  {
    GtkWidget*    button;
  } box;
  struct BrowserTabButton
  {
    GtkWidget*    tab;
    GtkWidget*    close;
  } button;
  char            title[24];
  char            url[2048];
  unsigned char   garbage;
} BrowserTab;

BrowserTabID fb_sdk_create_new_tab(GtkWidget* container);
BrowserTab  fb_sdk_get_tab(BrowserTabID ID);

extern BrowserTab tab[16];

#endif

