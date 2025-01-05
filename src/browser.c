#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "browser.h"
#include "cookie.h"

Browser FB = {0};
BrowserDirectory ROOT = {0};

unsigned char isFirstLaunch = 1;

/* =========================================================================== */

static void
setup_directory(void)
{
  const char* home = getenv("HOME");
  struct stat s = {0};

  strcpy(ROOT.def, home);
  strcat(ROOT.def, "/.local/share/feather_browser");
  if (stat(ROOT.def, &s) == -1)
  {
    mkdir(ROOT.def, 0700);
  }

  strcpy(ROOT.assets.def, ROOT.def);
  strcat(ROOT.assets.def, "/assets");
  if (stat(ROOT.assets.def, &s) == -1)
  {
    mkdir(ROOT.assets.def, 0700);
  }

  strcpy(ROOT.assets.cookies, ROOT.assets.def);
  strcat(ROOT.assets.cookies, "/cookies.dat");

  strcpy(ROOT.assets.icon, ROOT.assets.def);
  strcat(ROOT.assets.icon, "/icon.png");
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
  strcpy(FB.data.url, gtk_entry_get_text(GTK_ENTRY(widget)));
}

static void
on_url_update(WebKitWebView* web, GParamSpec* pspec, gpointer data)
{
  strcpy(FB.data.url, webkit_web_view_get_uri(web));
  gtk_entry_set_text(GTK_ENTRY(FB.widget.url), FB.data.url);
}

static void
on_url_fetch(GtkWidget* widget, gpointer web)
{
  if (strncmp(FB.data.url, "https://", 8) != 0)
  {
    char buffer[1024] = {0};
    strcpy(buffer, "https://");
    strcat(buffer, FB.data.url);
    strcpy(FB.data.url, buffer);
  }

  webkit_web_view_load_uri(web, FB.data.url);
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

  FB.window.def = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(FB.window.def), "Feather Browser");
  gtk_window_set_default_size(GTK_WINDOW(FB.window.def), 800, 600);
  gtk_window_set_position(GTK_WINDOW(FB.window.def), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(FB.window.def), 0);
  g_signal_connect(FB.window.def, "destroy", G_CALLBACK(on_window_terminate), NULL);

  FB.window.icon = gdk_pixbuf_new_from_file(ROOT.assets.icon, NULL);
  gtk_window_set_icon(GTK_WINDOW(FB.window.def), FB.window.icon);

  FB.widget.vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(FB.window.def), FB.widget.vbox);

  FB.widget.hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(FB.widget.vbox), FB.widget.hbox, FALSE, FALSE, 3);

  FB.widget.back = gtk_button_new_with_label("<");
  gtk_box_pack_start(GTK_BOX(FB.widget.hbox), GTK_WIDGET(FB.widget.back), FALSE, FALSE, 1);

  FB.widget.forward = gtk_button_new_with_label(">");
  gtk_box_pack_start(GTK_BOX(FB.widget.hbox), GTK_WIDGET(FB.widget.forward), FALSE, FALSE, 1);

  FB.widget.reload = gtk_button_new_with_label("↑↓");
  gtk_box_pack_start(GTK_BOX(FB.widget.hbox), GTK_WIDGET(FB.widget.reload), FALSE, FALSE, 1);

  FB.widget.url = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(FB.widget.url), "Type the URL link here...");
  g_signal_connect(FB.widget.url, "changed", G_CALLBACK(on_url_change), NULL);
  gtk_entry_set_text(GTK_ENTRY(FB.widget.url), FB.data.url);
  gtk_box_pack_start(GTK_BOX(FB.widget.hbox), FB.widget.url, TRUE, TRUE, 1);

  FB.widget.search = gtk_button_new_with_label("→");
  gtk_box_pack_end(GTK_BOX(FB.widget.hbox), GTK_WIDGET(FB.widget.search), FALSE, FALSE, 1);

  FB.widget.web = WEBKIT_WEB_VIEW(webkit_web_view_new());
  gtk_box_pack_end(GTK_BOX(FB.widget.vbox), GTK_WIDGET(FB.widget.web), TRUE, TRUE, 0);
  g_signal_connect(FB.widget.web, "load-changed", G_CALLBACK(on_cookie_handle), NULL);
  g_signal_connect(FB.widget.web, "notify::uri", G_CALLBACK(on_url_update), NULL);
  g_signal_connect(FB.widget.url, "activate", G_CALLBACK(on_url_fetch), FB.widget.web);
  g_signal_connect(FB.widget.back, "clicked", G_CALLBACK(on_url_history_back), FB.widget.web);
  g_signal_connect(FB.widget.forward, "clicked", G_CALLBACK(on_url_history_forward), FB.widget.web);
  g_signal_connect(FB.widget.reload, "clicked", G_CALLBACK(on_url_reload), FB.widget.web);
  g_signal_connect(FB.widget.search, "clicked", G_CALLBACK(on_fetch_click), FB.widget.web);

  if (isFirstLaunch == 1)
  {
    strcpy(FB.data.url, "https://www.duckduckgo.com");
    on_url_fetch(NULL, FB.widget.web);
    isFirstLaunch = 0;
  }

  gtk_widget_show_all(FB.window.def);
}

void
run_browser(void)
{
  gtk_main();
}

void
free_resources(void)
{
  g_object_unref(FB.window.def);
  g_object_unref(FB.window.icon);
}

