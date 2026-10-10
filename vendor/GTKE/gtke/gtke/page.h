#if !defined(__GTKE_PAGE_H__)
#define __GTKE_PAGE_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <gtke/gtke.h>

static uint8_t index_count = 0;

static uint8_t
gtke_page_index_count(void)
{
  return index_count;
}

static GtkEWidget*
gtke_page_new(void)
{
  return (GtkEWidget*)(gtk_notebook_new());
}

static int32_t
gtke_page_append(GtkEWidget* page, GtkEWidget* title, GtkEWidget* container)
{
  gtke_widget_update(title);
  gtke_widget_update(container);
  ++index_count;

  return gtk_notebook_append_page(GTK_NOTEBOOK(page), container, title);
}

static void
gtke_page_remove(GtkEWidget* page, int32_t index)
{
  --index_count;
  gtk_notebook_remove_page(GTK_NOTEBOOK(page), index);
}

static void
gtke_page_move_backwards(GtkEWidget* page)
{
  gtk_notebook_prev_page(GTK_NOTEBOOK(page));
}

static void
gtke_page_move_forward(GtkEWidget* page)
{
  gtk_notebook_next_page(GTK_NOTEBOOK(page));
}

static void
gtke_page_move_worker(GtkEWidget* page, GtkEWidget* worker, int32_t index)
{
  gtk_notebook_reorder_child(GTK_NOTEBOOK(page), worker, index);
}

static int32_t
gtke_page_get_current_index(GtkEWidget* page)
{
  return (int32_t)gtk_notebook_get_current_page(GTK_NOTEBOOK(page));
}

static GtkEWidget*
gtke_page_get_worker_from_index(GtkEWidget* page, int32_t index)
{
  return (GtkEWidget*)gtk_notebook_get_nth_page(GTK_NOTEBOOK(page), index);
}

#if defined(__GTKE_USE_CLASS__)
typedef struct GtkEWidgetPageClass
{
  GtkEWidget*   (*Create)(void);
  int32_t       (*Add)(GtkEWidget*, GtkEWidget*, GtkEWidget*);
  void          (*Remove)(GtkEWidget*, int32_t);
  struct GtkEWidgetPageMoveStructure
  {
    void        (*Backwards)(GtkEWidget*);
    void        (*Forward)(GtkEWidget*);
    void        (*Worker)(GtkEWidget*, GtkEWidget*, int32_t);
  } Move;
  struct GtkEWidgetPageGetStructure
  {
    int32_t     (*CurrentIndex)(GtkEWidget*);
    GtkEWidget* (*WorkerFromIndex)(GtkEWidget*, int32_t);
  } Get;
} GtkEWidgetPageClass;

static GtkEWidgetPageClass Page =
{
  gtke_page_new,
  gtke_page_append,
  gtke_page_remove,
  {
    gtke_page_move_backwards,
    gtke_page_move_forward,
    gtke_page_move_worker
  },
  {
    gtke_page_get_current_index,
    gtke_page_get_worker_from_index
  }
};
#endif

#if defined(__cplusplus)
}
#endif
#endif
