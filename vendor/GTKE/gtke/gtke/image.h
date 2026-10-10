#if !defined(__GTKE_IMAGE_H__)
#define __GTKE_IMAGE_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <gtke/gtke.h>

#include <gtke/types/image.h>

/* Image */

static GtkEWidget*
gtke_image_new_from_image_data(GtkEImageData* image_data)
{
  return (GtkEWidget*)(gtk_image_new_from_pixbuf(image_data));
}

static GtkEWidget*
gtke_image_new_from_file(const char* path)
{
  return (GtkEWidget*)(gtk_image_new_from_file(path));
}

/* ImageData */

static GtkEImageData*
gtke_image_data_new_from_file(const char* path)
{
  return (GtkEImageData*)(gdk_pixbuf_new_from_file(path, NULL));
}

static void
gtke_image_data_rescale(GtkEImageData** src_data, int32_t width, int32_t height)
{
  if ((src_data == NULL) || (*src_data == NULL))
  { return; }

  GtkEImageData* dest_data = gdk_pixbuf_scale_simple(*src_data, width, height, GDK_INTERP_BILINEAR);

  gtke_free_object(*src_data);
  *src_data = dest_data;
}

#if defined(__GTKE_USE_CLASS__)
typedef struct GtkEWidgetImageClass
{
  struct GtkEWidgetImageDataStructure { GtkEWidget* (*Create)(GtkEImageData*); } ImageData;
  struct GtkEWidgetImageFileStructure { GtkEWidget* (*Create)(const char*); } File;
} GtkEWidgetImageClass;

typedef struct GtkEWidgetImageDataClass
{
  struct GtkEWidgetImageDataFileStructure { GtkEImageData* (*Create)(const char*); } File;
  void (*Rescale)(GtkEImageData**, int32_t, int32_t);
} GtkEWidgetImageDataClass;

static GtkEWidgetImageClass Image =
{
  { gtke_image_new_from_image_data },
  { gtke_image_new_from_file }
};

static GtkEWidgetImageDataClass ImageData =
{
  { gtke_image_data_new_from_file },
  gtke_image_data_rescale
};
#endif

#if defined(__cplusplus)
}
#endif
#endif
