#ifndef WIDGET_HEADER
#define WIDGET_HEADER

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#include "common.h"

typedef GtkButton FBButton;
typedef GtkEntry FBEntry;
typedef GdkPixbuf FBIcon;
typedef WebKitWebView FBWebView;
typedef GtkWidget FBWidget;

typedef struct FBWidgetsBoxClass FBWidgetsBoxClass;
typedef struct FBWidgetsButtonClass FBWidgetsButtonClass;
typedef struct FBWidgetsContainerClass FBWidgetsContainerClass;
typedef struct FBWidgetsEntryClass FBWidgetsEntryClass;
typedef struct FBWidgetsWebViewClass FBWidgetsWebViewClass;
typedef struct FBWidgetsWindowClass FBWidgetsWindowClass;
typedef struct FBWidgetsClass FBWidgetsClass;

typedef enum FBOrientation FBOrientation;
typedef enum FBWebViewMode FBWebViewMode;

enum FBOrientation
{
  BOX_ORIENTATION_HORIZONTAL,
  BOX_ORIENTATION_VERTICAL
};

enum FBWebViewMode
{
  WEBVIEW_HIDE,
  WEBVIEW_SHOW
};

/* BOX */
FBWidget*   _WC_Box_Create(FBOrientation orientation, int32_t padding);
void        _WC_Box_Move(FBWidget* box, FBWidget* slave, int32_t position);
void        _WC_Box_PositionStart(FBWidget* box, FBWidget* slave, bool expand, bool fill, uint32_t padding);
void        _WC_Box_PositionEnd(FBWidget* box, FBWidget* slave, bool expand, bool fill, uint32_t padding);

/* BUTTON */
FBWidget*   _WC_Button_Create(const char* label);
FBButton*   _WC_Button_GetMaster(void);
void        _WC_Button_SetMaster(FBWidget* button);
const char* _WC_Button_GetLabel(FBWidget* button);
void        _WC_Button_SetLabel(FBWidget* button, const char* label);

/* CONTAINER */
void        _WC_Container_Add(FBWidget* container, FBWidget* slave);
void        _WC_Container_Remove(FBWidget* container, FBWidget* slave);
int32_t     _WC_Container_GetBorderWidth(FBWidget* container);
void        _WC_Container_SetBorderWidth(FBWidget* container, int32_t width);

/* ENTRY */
FBWidget*   _WC_Entry_Create(const char* label);
FBEntry*    _WC_Entry_GetMaster(void);
void        _WC_Entry_SetMaster(FBWidget* entry);
const char* _WC_Entry_GetLabel(FBWidget* entry);
void        _WC_Entry_SetLabel(FBWidget* entry, const char* label);

/* WEBVIEW */
FBWebView*  _WC_WebView_Create(void);
FBWebView*  _WC_WebView_GetMaster(void);
void        _WC_WebView_SetMaster(FBWebView* web_view);
bool        _WC_WebView_Visible(FBWebView* web_view);
bool        _WC_WebView_CanGoBack(FBWebView* web_view);
bool        _WC_WebView_CanGoForward(FBWebView* web_view);
bool        _WC_WebView_Loading(FBWebView* web_view);
const char* _WC_WebView_GetTitle(FBWebView* web_view);
const char* _WC_WebView_GetURI(FBWebView* web_view);
void        _WC_WebView_Control(FBWebView* web_view, FBWebViewMode mode);
void        _WC_WebView_LoadHTML(FBWebView* web_view, const char* file, const char* uri);
void        _WC_WebView_LoadURI(FBWebView* web_view, const char* uri);
void        _WC_WebView_Search(FBWebView* web_view, char* url);
void        _WC_WebView_BackHistory(FBWebView* web_view);
void        _WC_WebView_ForwardHistory(FBWebView* web_view);
void        _WC_WebView_Stop(FBWebView* web_view);
void        _WC_WebView_Reload(FBWebView* web_view, FBButton* button);

/* WINDOW */
FBWidget*   _WC_Window_Create(const char* w_icon_path, const char* title, size_t scale_x, size_t scale_y);

struct FBWidgetsBoxClass
{
  FBWidget*   (*Create)(FBOrientation, int32_t);
  void        (*Move)(FBWidget*, FBWidget*, int32_t);
  void        (*PositionStart)(FBWidget*, FBWidget*, bool, bool, uint32_t);
  void        (*PositionEnd)(FBWidget*, FBWidget*, bool, bool, uint32_t);
};

struct FBWidgetsButtonClass
{
  FBWidget*   (*Create)(const char*);
  FBButton*   (*GetMaster)(void);
  void        (*SetMaster)(FBWidget*);
  const char* (*GetLabel)(FBWidget*);
  void        (*SetLabel)(FBWidget*, const char*);
};

struct FBWidgetsContainerClass
{
  void        (*Add)(FBWidget*, FBWidget*);
  void        (*Remove)(FBWidget*, FBWidget*);
  int32_t     (*GetBorderWidth)(FBWidget*);
  void        (*SetBorderWidth)(FBWidget*, int32_t);
};

struct FBWidgetsEntryClass
{
  FBWidget*   (*Create)(const char*);
  FBEntry*    (*GetMaster)(void);
  void        (*SetMaster)(FBWidget*);
  const char* (*GetLabel)(FBWidget*);
  void        (*SetLabel)(FBWidget*, const char*);
};

struct FBWidgetsWebViewClass
{
  FBWebView*  (*Create)(void);
  FBWebView*  (*GetMaster)(void);
  void        (*SetMaster)(FBWebView*);
  bool        (*Visible)(FBWebView*);
  bool        (*CanGoBack)(FBWebView*);
  bool        (*CanGoForward)(FBWebView*);
  bool        (*Loading)(FBWebView*);
  const char* (*GetTitle)(FBWebView*);
  const char* (*GetURI)(FBWebView*);
  void        (*Control)(FBWebView*, FBWebViewMode);
  void        (*LoadHTML)(FBWebView*, const char*, const char*);
  void        (*LoadURI)(FBWebView*, const char*);
  void        (*Search)(FBWebView*, char*);
  void        (*BackHistory)(FBWebView*);
  void        (*ForwardHistory)(FBWebView*);
  void        (*Stop)(FBWebView*);
  void        (*Reload)(FBWebView*, FBButton*);
};

struct FBWidgetsWindowClass
{
  FBWidget*   (*Create)(const char*, const char*, size_t, size_t);
};

struct FBWidgetsClass
{
  void (*Destroy)(FBWidget*);
};

const FBWidgetsClass          fb_widgets_get(void);
const FBWidgetsBoxClass       fb_widgets_get_box_class(void);
const FBWidgetsButtonClass    fb_widgets_get_button_class(void);
const FBWidgetsContainerClass fb_widgets_get_container_class(void);
const FBWidgetsEntryClass     fb_widgets_get_entry_class(void);
const FBWidgetsWebViewClass   fb_widgets_get_web_view_class(void);
const FBWidgetsWindowClass    fb_widgets_get_window_class(void);

#endif

