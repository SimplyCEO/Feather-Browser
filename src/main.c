#include "widgets.h"
#include "browser.h"

int
main(int argc, char** argv)
{
  setup_all_widgets();

  setup_browser(argc, argv);
  run_browser();
  free_resources();

  return 0;
}

