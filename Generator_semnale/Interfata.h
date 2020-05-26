/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2020. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: OnPanel */
#define  PANEL_V_SPLITTER                 2       /* control type: splitter, callback function: (none) */
#define  PANEL_NUMERICDIAL_2              3       /* control type: scale, callback function: (none) */
#define  PANEL_NUMERICDIAL_3              4       /* control type: scale, callback function: (none) */
#define  PANEL_NUMERICDIAL_4              5       /* control type: scale, callback function: (none) */
#define  PANEL_COMMANDBUTTON_6            6       /* control type: command, callback function: Pause_aplicatie */
#define  PANEL_COMMANDBUTTON_3            7       /* control type: command, callback function: Start_aplicatie */
#define  PANEL_COMMANDBUTTON_7            8       /* control type: command, callback function: Refresh_graph */
#define  PANEL_COMMANDBUTTON_5            9       /* control type: command, callback function: Quit_aplicatie */
#define  PANEL_PICTUREBUTTON_3            10      /* control type: pictButton, callback function: status_triangle_wave */
#define  PANEL_PICTUREBUTTON_2            11      /* control type: pictButton, callback function: status_square_wave */
#define  PANEL_PICTUREBUTTON              12      /* control type: pictButton, callback function: status_sine_button */
#define  PANEL_GRAPH_2                    13      /* control type: graph, callback function: (none) */
#define  PANEL_GRAPH                      14      /* control type: graph, callback function: (none) */
#define  PANEL_NUMERICDIAL                15      /* control type: scale, callback function: Setare_Perioada_Esantionare */
#define  PANEL_NUMERICKNOB                16      /* control type: scale, callback function: (none) */
#define  PANEL_NUMERICKNOB_2              17      /* control type: scale, callback function: (none) */
#define  PANEL_DECORATION_3               18      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_2               19      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION                 20      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG                    21      /* control type: textMsg, callback function: (none) */
#define  PANEL_TIMER                      22      /* control type: timer, callback function: esantionare */
#define  PANEL_DECORATION_4               23      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_5               24      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_2                  25      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK esantionare(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pause_aplicatie(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit_aplicatie(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Refresh_graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Setare_Perioada_Esantionare(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Start_aplicatie(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK status_sine_button(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK status_square_wave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK status_triangle_wave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
