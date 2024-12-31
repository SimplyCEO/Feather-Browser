#include "browser.h"
  
int
main(int argc, char** argv)
{
  setup_browser(argc, argv);
  run_browser();
  free_resources();

  return 0;
}

