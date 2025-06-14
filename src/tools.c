#include <stdio.h>
#include <stdlib.h>

/* =========================================================================== */

char*
load_html_file(const char* path)
{
  FILE* stream = fopen(path, "r");
  if (stream == NULL)
  { return NULL; }

  fseek(stream, 0, SEEK_END);
  long streamsize = ftell(stream);
  rewind(stream);

  char* contents = (char*)malloc(streamsize+1);
  fread(contents, streamsize, 1, stream);
  contents[streamsize] = '\0';

  fclose(stream);
  return contents;
}

