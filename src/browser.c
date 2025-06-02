#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "browser.h"
#include "cookie.h"
#include "tab.h"

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
on_new_tab(GtkButton* button, GtkWidget* container)
{
  fb_sdk_create_new_tab(container);

  gtk_widget_show_all(FB.window.def);
}

/* =========================================================================== */

void
setup_browser(int argc, char** argv)
{
  gtk_init(&argc, &argv);

  setup_directory();

  /* Browser main layout */

  FB.window.def = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(FB.window.def), "Feather Browser");
  gtk_window_set_default_size(GTK_WINDOW(FB.window.def), 800, 600);
  gtk_window_set_position(GTK_WINDOW(FB.window.def), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(FB.window.def), 0);
  g_signal_connect(FB.window.def, "destroy", G_CALLBACK(on_window_terminate), NULL);

  FB.window.icon = gdk_pixbuf_new_from_file(ROOT.assets.icon, NULL);
  gtk_window_set_icon(GTK_WINDOW(FB.window.def), FB.window.icon);

  FB.box.main = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(FB.window.def), FB.box.main);

  /* Organised layout */

  FB.box.tool = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(FB.box.main), FB.box.tool, FALSE, FALSE, 3);

  FB.box.tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(FB.box.main), FB.box.tab, FALSE, FALSE, 3);

  FB.box.web = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end(GTK_BOX(FB.box.main), FB.box.web, FALSE, FALSE, 0);

  /* Buttons / Entries / WebView */

  FB.widget.back = gtk_button_new_with_label("<");
  gtk_box_pack_start(GTK_BOX(FB.box.tool), GTK_WIDGET(FB.widget.back), FALSE, FALSE, 1);

  FB.widget.forward = gtk_button_new_with_label(">");
  gtk_box_pack_start(GTK_BOX(FB.box.tool), GTK_WIDGET(FB.widget.forward), FALSE, FALSE, 1);

  FB.widget.reload = gtk_button_new_with_label("↑↓");
  gtk_box_pack_start(GTK_BOX(FB.box.tool), GTK_WIDGET(FB.widget.reload), FALSE, FALSE, 1);

  FB.widget.url = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(FB.widget.url), "Type the URL link here...");
  gtk_box_pack_start(GTK_BOX(FB.box.tool), FB.widget.url, TRUE, TRUE, 1);

  FB.widget.search = gtk_button_new_with_label("→");
  gtk_box_pack_end(GTK_BOX(FB.box.tool), GTK_WIDGET(FB.widget.search), FALSE, FALSE, 1);

  GtkWidget* newtab = gtk_button_new_with_label("+");
  gtk_box_pack_start(GTK_BOX(FB.box.tab), newtab, FALSE, FALSE, 3);
  g_signal_connect(newtab, "clicked", G_CALLBACK(on_new_tab), FB.box.tab);

  fb_sdk_create_new_tab(FB.box.tab);

  /* Render application */

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

