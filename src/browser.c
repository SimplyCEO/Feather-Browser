#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "browser.h"
#include "cookie.h"

Browser browser = {0};
BrowserDirectory root = {0};

unsigned char isFirstLaunch = 1;

/* =========================================================================== */

static void
setup_directory(void)
{
  const char* home = getenv("HOME");
  struct stat s = {0};

  strcpy(root.def, home);
  strcat(root.def, "/.local/share/feather_browser");
  if (stat(root.def, &s) == -1)
  {
    mkdir(root.def, 0700);
  }

  strcpy(root.assets.def, root.def);
  strcat(root.assets.def, "/assets");
  if (stat(root.assets.def, &s) == -1)
  {
    mkdir(root.assets.def, 0700);
  }

  strcpy(root.assets.cookies, root.assets.def);
  strcat(root.assets.cookies, "/cookies.dat");

  strcpy(root.assets.icon, root.assets.def);
  strcat(root.assets.icon, "/icon.png");
}

/* =========================================================================== */

static void
on_window_terminate(void)
{
  gtk_main_quit();
}

/* --------------------------------------------------------------------------- */

static void
on_url_change(GtkWidget* widget, gpointer data)
{
  strcpy(browser.data.url, gtk_entry_get_text(GTK_ENTRY(widget)));
}

static void
on_url_update(WebKitWebView* web, GParamSpec* pspec, gpointer data)
{
  strcpy(browser.data.url, webkit_web_view_get_uri(web));
  gtk_entry_set_text(GTK_ENTRY(browser.window.widget.url), browser.data.url);
}

static void
on_url_fetch(GtkWidget* widget, gpointer web)
{
  if (strncmp(browser.data.url, "https://", 8) != 0)
  {
    char buffer[1024] = {0};
    strcpy(buffer, "https://");
    strcat(buffer, browser.data.url);
    strcpy(browser.data.url, buffer);
  }

  webkit_web_view_load_uri(web, browser.data.url);
}

static void
on_fetch_click(GtkButton* button, gpointer web)
{
  on_url_fetch(NULL, web);
}

/* --------------------------------------------------------------------------- */

static void
on_url_history_back(GtkButton* button, gpointer web)
{
  if (webkit_web_view_can_go_back(web))
  {
    webkit_web_view_go_back(web);
  }
}

static void
on_url_history_forward(GtkButton* button, gpointer web)
{
  if (webkit_web_view_can_go_forward(web))
  {
    webkit_web_view_go_forward(web);
  }
}

static void
on_url_reload(GtkButton* button, gpointer web)
{
  webkit_web_view_reload(web);
}

/* =========================================================================== */

void
setup_browser(int argc, char** argv)
{
  gtk_init(&argc, &argv);

  setup_directory();

  browser.window.def = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(browser.window.def), "Feather Browser");
  gtk_window_set_default_size(GTK_WINDOW(browser.window.def), 800, 600);
  gtk_window_set_position(GTK_WINDOW(browser.window.def), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(browser.window.def), 0);
  g_signal_connect(browser.window.def, "destroy", G_CALLBACK(on_window_terminate), NULL);

  browser.window.icon = gdk_pixbuf_new_from_file(root.assets.icon, NULL);
  gtk_window_set_icon(GTK_WINDOW(browser.window.def), browser.window.icon);

  browser.window.widget.vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(browser.window.def), browser.window.widget.vbox);

  browser.window.widget.hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(browser.window.widget.vbox), browser.window.widget.hbox, FALSE, FALSE, 3);

  browser.window.widget.back = gtk_button_new_with_label("<");
  gtk_box_pack_start(GTK_BOX(browser.window.widget.hbox), GTK_WIDGET(browser.window.widget.back), FALSE, FALSE, 1);

  browser.window.widget.forward = gtk_button_new_with_label(">");
  gtk_box_pack_start(GTK_BOX(browser.window.widget.hbox), GTK_WIDGET(browser.window.widget.forward), FALSE, FALSE, 1);

  browser.window.widget.reload = gtk_button_new_with_label("↑↓");
  gtk_box_pack_start(GTK_BOX(browser.window.widget.hbox), GTK_WIDGET(browser.window.widget.reload), FALSE, FALSE, 1);

  browser.window.widget.url = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(browser.window.widget.url), "Type the URL link here...");
  g_signal_connect(browser.window.widget.url, "changed", G_CALLBACK(on_url_change), NULL);
  gtk_entry_set_text(GTK_ENTRY(browser.window.widget.url), browser.data.url);
  gtk_box_pack_start(GTK_BOX(browser.window.widget.hbox), browser.window.widget.url, TRUE, TRUE, 1);

  browser.window.widget.search = gtk_button_new_with_label("→");
  gtk_box_pack_end(GTK_BOX(browser.window.widget.hbox), GTK_WIDGET(browser.window.widget.search), FALSE, FALSE, 1);

  browser.window.widget.web.view = WEBKIT_WEB_VIEW(webkit_web_view_new());
  gtk_box_pack_end(GTK_BOX(browser.window.widget.vbox), GTK_WIDGET(browser.window.widget.web.view), TRUE, TRUE, 0);
  g_signal_connect(browser.window.widget.web.view, "load-changed", G_CALLBACK(on_cookie_handle), NULL);
  g_signal_connect(browser.window.widget.web.view, "notify::uri", G_CALLBACK(on_url_update), NULL);
  g_signal_connect(browser.window.widget.url, "activate", G_CALLBACK(on_url_fetch), browser.window.widget.web.view);
  g_signal_connect(browser.window.widget.back, "clicked", G_CALLBACK(on_url_history_back), browser.window.widget.web.view);
  g_signal_connect(browser.window.widget.forward, "clicked", G_CALLBACK(on_url_history_forward), browser.window.widget.web.view);
  g_signal_connect(browser.window.widget.reload, "clicked", G_CALLBACK(on_url_reload), browser.window.widget.web.view);
  g_signal_connect(browser.window.widget.search, "clicked", G_CALLBACK(on_fetch_click), browser.window.widget.web.view);

  if (isFirstLaunch == 1)
  {
    strcpy(browser.data.url, "https://www.duckduckgo.com");
    on_url_fetch(NULL, browser.window.widget.web.view);
    isFirstLaunch = 0;
  }

  gtk_widget_show_all(browser.window.def);
}

void
run_browser(void)
{
  gtk_main();
}

void
free_resources(void)
{
  g_object_unref(browser.window.def);
  g_object_unref(browser.window.icon);
}

