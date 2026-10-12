#if !defined(__GTKE_IMAGE_H__)
# define __GTKE_IMAGE_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtke/common.h>

# include <gdk/gdk.h>
# include <gtke/widget.h>

typedef GtkImage  GtkEImage;
typedef GdkPixbuf GtkEImageData;

GtkEWidget*    gtke_image_new_from_image_data(GtkEImageData* image_data);
GtkEWidget*    gtke_image_new_from_file(const char* path);
GtkEImageData* gtke_image_data_new_from_file(const char* path);
void           gtke_image_data_rescale(GtkEImageData** src_data, int32_t width, int32_t height);

# if defined(__GTKE_USE_CLASS__)
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
# endif

# if defined(__cplusplus)
}
# endif
#endif

