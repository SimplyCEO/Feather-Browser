#ifndef BROWSER_HEADER
#define BROWSER_HEADER

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <libsoup/soup.h>

typedef struct Browser
{
  struct BrowserData
  {
    WebKitCookieManager* cookie;
    char url[2048];
  } data;
  struct WindowUI
  {
    GtkWidget* def;
    GdkPixbuf* icon;
    struct WindowWidgetUI
    {
      GtkWidget* vbox;
      GtkWidget* hbox;
      GtkWidget* back;
      GtkWidget* forward;
      GtkWidget* reload;
      GtkWidget* url;
      GtkWidget* search;
      struct WindowWidgetWebUI
      { WebKitWebView* view; } web;
    } widget;
  } window;
} Browser;

typedef struct BrowserDirectory
{
  char def[1024];
  struct BrowserAssetsDirectory
  {
    char def[1024];
    char icon[1024];
    char cookies[1024];
  } assets;
} BrowserDirectory;

extern Browser          browser;
extern BrowserDirectory root;

void setup_browser(int argc, char** argv);
void run_browser(void);
void free_resources(void);

#endif

