#include "widgets.h"

FBWidgetsClass          Widget;
FBWidgetsBoxClass       Box;
FBWidgetsButtonClass    Button;
FBWidgetsContainerClass Container;
FBWidgetsEntryClass     Entry;
FBWidgetsWebViewClass   WebView;
FBWidgetsWindowClass    Window;

void
setup_all_widgets(void)
{
  Widget.Destroy = gtk_widget_destroy;
  Box.Create = _WC_Box_Create;
  Box.Move = _WC_Box_Move;
  Box.PositionStart = _WC_Box_PositionStart;
  Box.PositionEnd = _WC_Box_PositionEnd;
  Button.Create = _WC_Button_Create;
  Button.GetMaster = _WC_Button_GetMaster;
  Button.SetMaster = _WC_Button_SetMaster;
  Button.GetLabel = _WC_Button_GetLabel;
  Button.SetLabel = _WC_Button_SetLabel;
  Container.Add = _WC_Container_Add;
  Container.Remove = _WC_Container_Remove;
  Container.GetBorderWidth = _WC_Container_GetBorderWidth;
  Container.SetBorderWidth = _WC_Container_SetBorderWidth;
  Entry.Create = _WC_Entry_Create;
  Entry.GetMaster = _WC_Entry_GetMaster;
  Entry.SetMaster = _WC_Entry_SetMaster;
  Entry.GetLabel = _WC_Entry_GetLabel;
  Entry.SetLabel = _WC_Entry_SetLabel;
  WebView.Create = _WC_WebView_Create;
  WebView.GetMaster = _WC_WebView_GetMaster;
  WebView.SetMaster = _WC_WebView_SetMaster;
  WebView.Visible = _WC_WebView_Visible;
  WebView.CanGoBack = _WC_WebView_CanGoBack;
  WebView.CanGoForward = _WC_WebView_CanGoForward;
  WebView.Loading = _WC_WebView_Loading;
  WebView.GetTitle = _WC_WebView_GetTitle;
  WebView.GetURI = _WC_WebView_GetURI;
  WebView.Control = _WC_WebView_Control;
  WebView.LoadHTML = _WC_WebView_LoadHTML;
  WebView.LoadURI = _WC_WebView_LoadURI;
  WebView.Search = _WC_WebView_Search;
  WebView.BackHistory = _WC_WebView_BackHistory;
  WebView.ForwardHistory = _WC_WebView_ForwardHistory;
  WebView.Stop = _WC_WebView_Stop;
  WebView.Reload = _WC_WebView_Reload;
  Window.Create = _WC_Window_Create;
}

