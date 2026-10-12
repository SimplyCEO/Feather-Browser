#if !defined(__GTKE_PAGE_H__)
# define __GTKE_PAGE_H__

# if defined(__cplusplus)
extern "C"
{
# endif

# include <gtke/common.h>

# include <gtke/widget.h>

int32_t     gtke_page_index_count(GtkEWidget* page);
GtkEWidget* gtke_page_new(void);
int32_t     gtke_page_append(GtkEWidget* page, GtkEWidget* title, GtkEWidget* container);
void        gtke_page_remove(GtkEWidget* page, int32_t index);
void        gtke_page_move_backwards(GtkEWidget* page);
void        gtke_page_move_forward(GtkEWidget* page);
void        gtke_page_move_worker(GtkEWidget* page, GtkEWidget* worker, int32_t index);
int32_t     gtke_page_get_current_index(GtkEWidget* page);
GtkEWidget* gtke_page_get_worker_from_index(GtkEWidget* page, int32_t index);

# if defined(__GTKE_USE_CLASS__)
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
    int32_t     (*Index)(GtkEWidget*);
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
    gtke_page_index_count,
    gtke_page_get_current_index,
    gtke_page_get_worker_from_index
  }
};
# endif

# if defined(__cplusplus)
}
# endif
#endif

