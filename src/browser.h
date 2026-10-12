#ifndef BROWSER_HEADER
#define BROWSER_HEADER

#include <libsoup/soup.h>

#include "gtke.h"

typedef struct BrowserAssetsDirectory
{
  char master[1024];
  char assets[1024];
  char cookies[1024];
  char icon[1024];
  char launcher[1024];
} BrowserAssetsDirectory;

typedef struct Browser
{
  struct BrowserDirectory
  {
    BrowserAssetsDirectory root;
    BrowserAssetsDirectory user;
  } path;

  struct BrowserData { GtkECookieManager* cookie; } data;

  GtkEWidget* window;
  struct BrowserContainer
  {
    GtkEWidget* master;
    GtkEWidget* tool;
    GtkEWidget* tab;
    GtkEWidget* web;
  } container;
  struct BrowserWidget
  {
    GtkEWidget* back;
    GtkEWidget* forward;
    GtkEWidget* reload;
    GtkEWidget* url;
    GtkEWidget* search;
    GtkEWidget* tab;
  } widget;
} Browser;

extern Browser feather;

void setup_browser(int argc, char** argv);
void run_browser(void);
void free_resources(void);

#endif

