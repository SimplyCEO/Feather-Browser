#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "widgets.h"

#include "browser.h"
#include "cookie.h"
#include "tab.h"

Browser FB = {0};
BrowserDirectory HOME = {0};
BrowserDirectory ROOT = {0};

/* =========================================================================== */

static void
setup_directory(void)
{
  const char* home = getenv("HOME");
  struct stat s = {0};

  strcpy(ROOT.def, "/usr/share/feather-browser");
  sprintf(ROOT.assets.def, "%s/assets", ROOT.def);

  sprintf(HOME.def, "%s/.local/share/feather-browser", home);
  sprintf(HOME.assets.def, "%s/assets", HOME.def);

  if (stat(HOME.def, &s) == -1)
  { mkdir(HOME.def, 0700); }
  if (stat(HOME.assets.def, &s) == -1)
  { mkdir(HOME.assets.def, 0700); }

  sprintf(ROOT.assets.icon, "%s/icon.png", ROOT.assets.def);
  sprintf(ROOT.assets.launcher, "%s/launcher/index.html", ROOT.assets.def);

  sprintf(HOME.assets.cookies, "%s/cookies.dat", HOME.assets.def);
}

/* =========================================================================== */

static void
on_new_tab(FBButton* button, FBWidget* container)
{
  fb_sdk_create_new_tab(container);

  gtk_widget_show_all(FB.box.tab);
}

/* =========================================================================== */

void
setup_browser(int argc, char** argv)
{
  gtk_init(&argc, &argv);

  setup_directory();

  FBWidgetsBoxClass       Box       = fb_widgets_get_box_class();
  FBWidgetsButtonClass    Button    = fb_widgets_get_button_class();
  FBWidgetsContainerClass Container = fb_widgets_get_container_class();
  FBWidgetsEntryClass     Entry     = fb_widgets_get_entry_class();
  FBWidgetsWindowClass    Window    = fb_widgets_get_window_class();

  /* Browser main layout */

  FB.window = Window.Create(ROOT.assets.icon, "Feather Browser", 800, 600);
  FB.box.main = Box.Create((FBOrientation)BOX_ORIENTATION_VERTICAL, 0);
  Container.Add(FB.window, FB.box.main);

  /* Organised layout */

  FB.box.tool = Box.Create((FBOrientation)BOX_ORIENTATION_HORIZONTAL, 0);
  FB.box.tab = Box.Create((FBOrientation)BOX_ORIENTATION_HORIZONTAL, 0);
  FB.box.web = Box.Create((FBOrientation)BOX_ORIENTATION_HORIZONTAL, 0);

  Box.PositionStart(FB.box.main, FB.box.tool, FALSE, FALSE, 3);
  Box.PositionStart(FB.box.main, FB.box.tab, FALSE, FALSE, 3);
  Box.PositionEnd(FB.box.main, FB.box.web, TRUE, TRUE, 0);

  /* Buttons / Entries / WebView */

  FB.widget.back = Button.Create("<");
  FB.widget.forward = Button.Create(">");
  FB.widget.reload = Button.Create("↑↓");
  FB.widget.url = Entry.Create("Type the URL link here...");
  FB.widget.search = Button.Create("→");
  FBWidget* newtab = Button.Create("+");

  Box.PositionStart(FB.box.tool, FB.widget.back, FALSE, FALSE, 1);
  Box.PositionStart(FB.box.tool, FB.widget.forward, FALSE, FALSE, 1);
  Box.PositionStart(FB.box.tool, FB.widget.reload, FALSE, FALSE, 1);
  Box.PositionStart(FB.box.tool, FB.widget.url, TRUE, TRUE, 1);
  Box.PositionEnd(FB.box.tool, FB.widget.search, FALSE, FALSE, 1);
  Box.PositionStart(FB.box.tab, newtab, FALSE, FALSE, 3);
  g_signal_connect(newtab, "clicked", G_CALLBACK(on_new_tab), FB.box.tab);

  fb_sdk_create_new_tab(FB.box.tab);

  /* Render application */
  
  gtk_widget_show_all(FB.window);
}

void
run_browser(void)
{
  gtk_main();
}

void
free_resources(void)
{
  g_object_unref(FB.window);
}

