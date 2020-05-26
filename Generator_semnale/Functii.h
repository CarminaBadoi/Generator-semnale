// ---------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
									
									//FUNCTII BUTOANE (REFRESH,QUIT,PAUSE,SPLITTERS)

// ---------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------- 


 
//--------------------------- REFRESH BUTTON ---------------------------------

int CVICALLBACK Refresh_graph (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			
			//stergere grafice desenate pe obiectele GRAPH
				
					DeleteGraphPlot (panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW );
					DeleteGraphPlot (panelHandle, PANEL_GRAPH_2, -1, VAL_IMMEDIATE_DRAW );
				    
			
			//Reinitializare timp de afisare
					tk_1=0;
					tk=Te;
			
			
			

			break;
	}
	return 0;
}



//--------------------------- SPLITTERS ----------------------------------


int CVICALLBACK OnPanel (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{  
	
	
	switch (event)
	{
		case EVENT_PANEL_SIZING: 
				
			
				// Splitter Vertical - Redimensionare fereastra 
				
				GetPanelAttribute(panelHandle,ATTR_WIDTH,&NewWidth);
				OperateSplitter (panelHandle, PANEL_V_SPLITTER, NewWidth-OldWidth);
				OldWidth-NewWidth;
				
			
		

			break;
		
	}
	return 0;
}



//--------------------------- PAUSE BUTTON ----------------------------------


int CVICALLBACK Pause_aplicatie (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			//oprim timer-ul
			
				SetCtrlAttribute (panelHandle,PANEL_TIMER, ATTR_ENABLED,0);
				
			// Asteapta 1.5 sec
				Delay(1.5);
				
			//pornim timer-ul	
				SetCtrlAttribute (panelHandle,PANEL_TIMER, ATTR_ENABLED,1);

			break;
	}
	return 0;
}

//--------------------------- QUIT BUTTON ----------------------------------

int CVICALLBACK Quit_aplicatie (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);  // Quit 
			break;
	}
	return 0;
}









// ---------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
									
									//FUNCTII BUTOANE (SINE,STEP RAMP)

// ---------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------





//----------------------------- STEP BUTTON ---------------------------------- 


int CVICALLBACK status_square_wave (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			
					step = 1;
			
				// Dezactivare anumite butoane 
			
					 SetCtrlAttribute (panelHandle,PANEL_PICTUREBUTTON,ATTR_DIMMED,1);
					 SetCtrlAttribute (panelHandle,PANEL_PICTUREBUTTON_3,ATTR_DIMMED,1);
					 SetCtrlAttribute (panelHandle,PANEL_NUMERICKNOB,ATTR_DIMMED,1);
					 SetCtrlAttribute (panelHandle,PANEL_NUMERICKNOB_2,ATTR_DIMMED,1);
					 SetCtrlAttribute (panelHandle,PANEL_NUMERICDIAL_3,ATTR_DIMMED,1);
					// SetCtrlAttribute (panelHandle,PANEL_NUMERICDIAL_2,ATTR_DIMMED,1); 
			
					
					
					

			break;
	}
	return 0;
}

//--------------------------- RAMP BUTTON ---------------------------------- 

int CVICALLBACK status_triangle_wave (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			
					rampa = 1;
			
				// Dezactivare anumite butoane 
			
				     SetCtrlAttribute (panelHandle,PANEL_PICTUREBUTTON,ATTR_DIMMED,1);
					 SetCtrlAttribute (panelHandle,PANEL_PICTUREBUTTON_2,ATTR_DIMMED,1);
					 SetCtrlAttribute (panelHandle,PANEL_NUMERICDIAL_3,ATTR_DIMMED,1);
					 SetCtrlAttribute (panelHandle,PANEL_NUMERICDIAL_2,ATTR_DIMMED,1);
					 
				
			break;
	}
	return 0;
}

//--------------------------- SINE BUTTON ----------------------------------

int CVICALLBACK status_sine_button (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			
				   sinusoidal = 1;
				   
				 SetCtrlAttribute (panelHandle,PANEL_PICTUREBUTTON_2,ATTR_DIMMED,1);
				 SetCtrlAttribute (panelHandle,PANEL_PICTUREBUTTON_3,ATTR_DIMMED,1);
				 SetCtrlAttribute (panelHandle,PANEL_NUMERICKNOB,ATTR_DIMMED,1);
				 SetCtrlAttribute (panelHandle,PANEL_NUMERICKNOB_2,ATTR_DIMMED,1);

	 			break;
	}
	return 0;
}




