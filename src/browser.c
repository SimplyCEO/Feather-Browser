#define __GTKE_USE_CLASS__

#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "browser.h"

#include "tab.h"

Browser feather = {0};

/* =========================================================================== */

static void
setup_directory(void)
{
  const char* home = getenv("HOME");
  struct stat s = {0};

  strcpy(feather.path.root.master, "/usr/share/feather-browser");
  strcpy(feather.path.user.master, home);
  strcat(feather.path.user.master, "/.local/share/feather-browser");

  strcpy(feather.path.root.assets, feather.path.root.master);
  strcpy(feather.path.root.icon, feather.path.root.assets);
  strcpy(feather.path.root.launcher, feather.path.root.assets);
  strcpy(feather.path.user.assets, feather.path.user.master);
  strcpy(feather.path.user.cookies, feather.path.user.assets);

  strcat(feather.path.root.assets, "/assets");
  strcat(feather.path.user.assets, "/assets");
  strcat(feather.path.root.icon, "/icon.png");
  strcat(feather.path.root.launcher, "/launcher/index.html");
  strcat(feather.path.user.cookies, "/cookies.dat");

  if (stat(feather.path.user.master, &s) == -1) { mkdir(feather.path.user.master, 0700); }
  if (stat(feather.path.user.assets, &s) == -1) { mkdir(feather.path.user.assets, 0700); }
}

/* =========================================================================== */

void
setup_browser(int argc, char** argv)
{
  gtk_init(&argc, &argv);

  setup_directory();

  /* Browser master layout */

  feather.window           = Window.Create(feather.path.root.icon, "Feather Browser", 640, 480);
  feather.container.master = Container.Create(GTKE_ORIENTATION_VERTICAL, 0);

  /* Organised layout */

  feather.container.tool   = Container.Create(GTKE_ORIENTATION_HORIZONTAL, 0);
  feather.container.tab    = Container.Create(GTKE_ORIENTATION_HORIZONTAL, 0);
  feather.container.web    = Container.Create(GTKE_ORIENTATION_HORIZONTAL, 0);

 /* Buttons / Entries / WebView */

  feather.widget.back      = Button.Create("<");
  feather.widget.forward   = Button.Create(">");
  feather.widget.reload    = Button.Create("↑↓");
  feather.widget.url       = Entry.Create("Type the URL link here...");
  feather.widget.search    = Button.Create("→");
  feather.widget.tab       = Page.Create();
  GtkEWidget* newtab       = Text.Create("+");
  GtkEWidget* container    = Container.Create(GTKE_ORIENTATION_HORIZONTAL, 0);
  Page.Add(feather.widget.tab, newtab, container);

  g_signal_connect(feather.widget.url,      "changed",      G_CALLBACK(fb_sdk_on_url_change),           NULL);
  g_signal_connect(feather.widget.url,      "activate",     G_CALLBACK(fb_sdk_on_url_search),           NULL);
  g_signal_connect(feather.widget.back,     "clicked",      G_CALLBACK(fb_sdk_on_url_history_back),     NULL);
  g_signal_connect(feather.widget.forward,  "clicked",      G_CALLBACK(fb_sdk_on_url_history_forward),  NULL);
  g_signal_connect(feather.widget.reload,   "clicked",      G_CALLBACK(fb_sdk_on_url_reload),           NULL);
  g_signal_connect(feather.widget.search,   "clicked",      G_CALLBACK(fb_sdk_on_search_click),         NULL);
  g_signal_connect(feather.widget.tab,      "switch-page",  G_CALLBACK(fb_sdk_page_switch),             NULL);

  Container.Add(GTKE_CONTAINER_START, feather.container.tool, feather.widget.back,    false,  false,  1);
  Container.Add(GTKE_CONTAINER_START, feather.container.tool, feather.widget.forward, false,  false,  1);
  Container.Add(GTKE_CONTAINER_START, feather.container.tool, feather.widget.reload,  false,  false,  1);
  Container.Add(GTKE_CONTAINER_START, feather.container.tool, feather.widget.url,     true,   true,   1);
  Container.Add(GTKE_CONTAINER_END,   feather.container.tool, feather.widget.search,  false,  false,  1);
  Container.Add(GTKE_CONTAINER_START, feather.container.tab,  feather.widget.tab,     true,   true,   1);

  fb_sdk_create_new_tab(container, NULL);

  Container.Add(GTKE_CONTAINER_START, feather.container.master, feather.container.tool, false,  false,  3);
  Container.Add(GTKE_CONTAINER_END,   feather.container.master, feather.container.tab,  true,   true,   3);

  Window.Add(feather.window, feather.container.master);
}

void
run_browser(void)
{
  gtke_loop();
}

void
free_resources(void)
{
  fb_sdk_free_tab();
}

