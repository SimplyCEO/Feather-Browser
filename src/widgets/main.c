#include "widgets.h"

const FBWidgetsClass
fb_widgets_get(void)
{
  return (FBWidgetsClass){ gtk_widget_destroy };
}

const FBWidgetsBoxClass
fb_widgets_get_box_class(void)
{
  return (FBWidgetsBoxClass)
  {
    _WC_Box_Create,
    _WC_Box_Move,
    _WC_Box_PositionStart,
    _WC_Box_PositionEnd
  };
}

const FBWidgetsButtonClass
fb_widgets_get_button_class(void)
{
  return (FBWidgetsButtonClass)
  {
    _WC_Button_Create,
    _WC_Button_GetMaster,
    _WC_Button_SetMaster,
    _WC_Button_GetLabel,
    _WC_Button_SetLabel
  };
}

const FBWidgetsContainerClass
fb_widgets_get_container_class(void)
{
  return (FBWidgetsContainerClass)
  {
    _WC_Container_Add,
    _WC_Container_Remove,
    _WC_Container_GetBorderWidth,
    _WC_Container_SetBorderWidth
  };
}

const FBWidgetsEntryClass
fb_widgets_get_entry_class(void)
{
  return (FBWidgetsEntryClass)
  {
    _WC_Entry_Create,
    _WC_Entry_GetMaster,
    _WC_Entry_SetMaster,
    _WC_Entry_GetLabel,
    _WC_Entry_SetLabel
  };
}

const FBWidgetsWebViewClass
fb_widgets_get_web_view_class(void)
{
  return (FBWidgetsWebViewClass)
  {
    _WC_WebView_Create,
    _WC_WebView_GetMaster,
    _WC_WebView_SetMaster,
    _WC_WebView_Visible,
    _WC_WebView_CanGoBack,
    _WC_WebView_CanGoForward,
    _WC_WebView_Loading,
    _WC_WebView_GetTitle,
    _WC_WebView_GetURI,
    _WC_WebView_Control,
    _WC_WebView_LoadHTML,
    _WC_WebView_LoadURI,
    _WC_WebView_Search,
    _WC_WebView_BackHistory,
    _WC_WebView_ForwardHistory,
    _WC_WebView_Stop,
    _WC_WebView_Reload
  };
}

const FBWidgetsWindowClass
fb_widgets_get_window_class(void)
{
  return (FBWidgetsWindowClass)
  {
    _WC_Window_Create
  };
}

