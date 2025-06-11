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
  } data;
  struct BrowserWindow
  {
    GtkWidget* def;
    GdkPixbuf* icon;
  } window;
  struct BrowserContainer
  {
    GtkWidget* main;
    GtkWidget* tool;
    GtkWidget* tab;
    GtkWidget* web;
  } box;
  struct BrowserWidget
  {
    GtkWidget* back;
    GtkWidget* forward;
    GtkWidget* reload;
    GtkWidget* url;
    GtkWidget* search;
  } widget;
} Browser;

typedef struct BrowserDirectory
{
  char def[1024];
  struct BrowserAssetsDirectory
  {
    char def[1024];
    char cookies[1024];
    char icon[1024];
    char launcher[1024];
  } assets;
} BrowserDirectory;

extern Browser          FB;
extern BrowserDirectory HOME;
extern BrowserDirectory ROOT;

void setup_browser(int argc, char** argv);
void run_browser(void);
void free_resources(void);

#endif

