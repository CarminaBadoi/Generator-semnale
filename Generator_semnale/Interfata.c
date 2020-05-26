#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Interfata.h"




// -----------------------     DECLARARE VARIABILE   --------------------------- 

	static int panelHandle; 
	static int OldWidth ,NewWidth;   // latimea panelului  (old si new)
	static int state_sine_button=0,state_square_button=0,state_triangle_button=0;  // starea butoanelor formelor de unda (neapasate)
	
	double T;    // perioada semnalului
	double A;    // amplitudinea
	double t0;   // intarzierea/avansul(defazajul/faza)
	
	double tk;   // momentul actual de timp
	double tk_1; // momentul anterior de timp
	
	double xk;   // esantion al semnalului sinusoidal initial la momentul actual de timp
	double yk;   // esantion al semnalului sinusoidal defazat la momentul actual de timp  
	
	double xk_1; // esantion al semnalului initial la momentul anterior de timp  
	double yk_1; // esantion al semnalului defazat la momentul anterior de timp  
	
	double Te;   // Perioada de esantionare
	double pi;   // constanta pi
	
	double xk1,xk2,xk3;       // esantioane ale relatiilor recursive ale f.d.t la momentul actual de timp ( intrare semnalul propriu-zis)
	double xk1_1,xk2_1,xk3_1; // esantioane ale relatiilor recursive ale f.d.t la momentul anterior de timp (intrare semnalul propriu-zis)
	
	double C1,C2,C3;
	
	double yk1,yk2,yk3;       // esantioane ale relatiilor recursive ale f.d.t la momentul actual de timp ( intrare semnalul defazat)
	double yk1_1,yk2_1,yk3_1; // esantioane ale relatiilor recursive ale f.d.t la momentul anterior de timp ( intrare semnalul defazat)

	double a; // panta semnalului
	double b; // pozitia semnalului pe ordonata
	
	
	int raspuns_la_semnal_initial,raspuns_la_semnal_defazat; // variabile in care stocam plotarile
	
	int sinusoidal=0,step=0,rampa=0;  //  parametrii butoanelor sine,step si ramp
	
	
#include "Functii.h"	



int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					   LPSTR lpszCmdLine, int nCmdShow)
{
	if (InitCVIRTE (hInstance, 0, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Interfata.uir", PANEL)) < 0)
		return -1;
	
	GetPanelAttribute(panelHandle,ATTR_WIDTH,&NewWidth); 
	
	
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}





//--------------------------- START BUTTON ------------------------------- 

int CVICALLBACK Start_aplicatie (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			 
			
			//Setare perioada de esantionare initiala
			
			
				GetCtrlVal (panelHandle, PANEL_NUMERICDIAL, &Te);
				
			 
		 	//Setare parametrii semnale 
				
				tk_1=0; 	//moment de esantionare anterior
				xk_1=0; 	//Valoare semnal la momentul de esantionare anterior 
				yk_1=0;		//Valoare semnal la momentul de esantionare anterior, semnal avansat//intarziat
			
				pi=Pi();
				
				C1 = Te/(15+Te);
				C2 = Te/(2+Te);
				C3 = Te/(0.1+Te);
			
				xk1_1=0;   //f.d.t la momentul de esantionare anterior (prima parte : 15s+1)    , semnal propriu-zis 
				xk2_1=0;   //f.d.t la momentul de esantionare anterior (a doua parte : 2s+1)    , semnal propriu-zis
				xk3_1=0;   //f.d.t la momentul de esantionare anterior (a treia parte : 0.1s+1) , semnal propriu-zis
				
				yk1_1=0;   //f.d.t la momentul de esantionare anterior (prima parte : 15s+1)  , semnal avansat//intarziat
				yk2_1=0;   //f.d.t la momentul de esantionare anterior (prima parte : 2s+1)	  , semnal avansat//intarziat
				yk3_1=0;   //f.d.t la momentul de esantionare anterior (prima parte : 0.1s+1) , semnal avansat//intarziat
			 																				  
			// Pornim timer-ul	
				SetCtrlAttribute (panelHandle,PANEL_TIMER, ATTR_ENABLED,1); 
				
			



			break;
	}
	return 0;
}



 //------------------ SETARE PERIOADA ESANTIONARE(Te)  --------------------------

int CVICALLBACK Setare_Perioada_Esantionare (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			//citire perioada esantionare
				GetCtrlVal (panelHandle, PANEL_NUMERICDIAL, &Te); 
				
			//setare perioada esantionare timer (cu acel Te)
				SetCtrlAttribute (panelHandle,PANEL_TIMER, ATTR_INTERVAL,Te);
		
				
				
			

			break;
	}
	return 0;
}




  

//--------------------------- ESANTIONARE -------------------------------------

int CVICALLBACK esantionare (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			 			
			
			  if(sinusoidal==1) {
				  
			  
				
		
				 
				//--------------  CITIRE DATE ------------------
		
				//citire amplitudine 
				 
				   	GetCtrlVal (panelHandle, PANEL_NUMERICDIAL_2, &A);
		
				//citire perioada semnal
				
				   	GetCtrlVal (panelHandle, PANEL_NUMERICDIAL_3, &T);
		
				//citire  intarziere/avans (t0)
				
				   	GetCtrlVal (panelHandle, PANEL_NUMERICDIAL_4, &t0);
			
		
				//--------------  GENERARE SEMNAL ------------------		
					
					
				//generare semnal sinusoidal
				
					xk=A*sin( ((2*pi)/T)*tk );  
					
				//generare semnal sinusoidal intarziat/avansat cu intervalul de timp t0
						
				  	yk=A*sin( ((2*pi)/T)*tk+((2*pi)/T)*t0 );
						
				// implementare functie de transfer avand ca intrare semnalul propiru-zis
						
					xk1 = xk1_1 + C1 * (xk - xk1_1 );
					xk2 = xk2_1 + C2 * (xk1 - xk2_1 );
					xk3 = xk3_1 + C3 * (xk2 - xk3_1 );
				
				// implementare functie de transfer avand ca intrare semnalul defazat
						
					yk1 = yk1_1 + C1 * (yk - yk1_1 );
					yk2 = yk2_1 + C2 * (yk1 - yk2_1 );
					yk3 = yk3_1 + C3 * (yk2 - yk3_1 );			
	  
			
					
				//--------------  PLOTTING ------------------		
					
					//prelucrare graph
					   
					   SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_ENABLE_ZOOM_AND_PAN, 1);
					   SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_ZOOM_STYLE, VAL_ZOOM_TO_RECT);
				
				 	
			
					//afisare raspuns f.d.t la semnal sinusoidal 
					
					   raspuns_la_semnal_initial =	PlotLine (panelHandle, PANEL_GRAPH, tk_1, xk3_1, tk, xk3, VAL_GREEN);
						
					///afisare raspuns f.d.t la semnal sinusoidal defazat (cu t0)      	
					
					   raspuns_la_semnal_defazat =	PlotLine (panelHandle, PANEL_GRAPH_2, tk_1, yk3_1, tk, yk3, VAL_YELLOW);
			
				
			
					//reactualizare timp
					
					   tk_1=tk; 
					   tk=tk+Te;
						
					//generare esantioane noi  
						
					   xk3_1=xk3;
				       yk3_1=yk3;
					
					   		
			
					 
					 
			  }
			  
			  else if (step == 1) {
				  
			  
			  
			  		 //--------------  CITIRE DATE ------------------
					 
		
					//citire amplitudine 
				 
					   	GetCtrlVal (panelHandle, PANEL_NUMERICDIAL_2, &A);
						
					//citire t0
						
						GetCtrlVal (panelHandle, PANEL_NUMERICDIAL_4, &t0);
					
						
					
			   //--------------  GENERARE SEMNAL ------------------
						
				   // generam un semnal treapta propriu zis 
				
						xk = A;
					    
								
				   
				   // implementare functie de transfer avand ca intrare semnalul propiru-zis
						
						xk1 = xk1_1 + C1 * (xk - xk1_1 );
						xk2 = xk2_1 + C2 * (xk1 - xk2_1 );
						xk3 = xk3_1 + C3 * (xk2 - xk3_1 );
						
				  
			
					
			//--------------  PLOTTING ------------------		
					
				//prelucrare graph
					  
					   SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_ENABLE_ZOOM_AND_PAN, 1);
					   SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_ZOOM_STYLE, VAL_ZOOM_TO_RECT);
				
				 	
			
				//afisare semnal treapta
					
				       raspuns_la_semnal_initial =	PlotLine (panelHandle, PANEL_GRAPH,tk_1 ,xk_1 , tk, xk, VAL_CYAN);
						
				///afisare raspuns f.d.t la semnal treapta      	
					
					   raspuns_la_semnal_defazat =	PlotLine (panelHandle, PANEL_GRAPH_2, tk_1, xk3_1, tk, xk3, VAL_MAGENTA);
			
				
			
				//reactualizare timp
					
					   tk_1=tk; 
					   tk=tk+Te;
						
				//generare esantioane noi 
					   
						xk_1 = xk;
						xk3_1=xk3;
						
						
					        
			
			
			  }
				 
			else if(rampa == 1) {
			
					//--------------  CITIRE DATE ------------------
					 
		
					//citire panta semnal 
					 
				 	   
					  	GetCtrlVal (panelHandle, PANEL_NUMERICKNOB, &a);
						
					//citire pozitia semnalului pe ordonata	
						
						GetCtrlVal (panelHandle, PANEL_NUMERICKNOB_2, &b);
					
					//citire t0
						
						GetCtrlVal (panelHandle, PANEL_NUMERICDIAL_4, &t0);	
					
						
						
			   //--------------  GENERARE SEMNAL ------------------
						
				   // generam un semnal rampa propriu zis 
				
						xk = a * tk + b;
						
				   // generam un semnal rampa defazat
						
						yk = a *(tk+t0) + b;

				
				   // implementare functie de transfer avand ca intrare semnalul propiru-zis
						
						xk1 = xk1_1 + C1 * (xk - xk1_1 );
						xk2 = xk2_1 + C2 * (xk1 - xk2_1 );
						xk3 = xk3_1 + C3 * (xk2 - xk3_1 );
						
				  // implementare functie de transfer avand ca intrare semnalul defazat
						
						yk1 = yk1_1 + C1 * (yk - yk1_1 );
						yk2 = yk2_1 + C2 * (yk1 - yk2_1 );
						yk3 = yk3_1 + C3 * (yk2 - yk3_1 );			
			  
			
					
			//--------------  PLOTTING ------------------		
					
				//prelucrare graph
					  
					   SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_ENABLE_ZOOM_AND_PAN, 1);
					   SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_ZOOM_STYLE, VAL_ZOOM_TO_RECT);
					  
				 	
			
				//afisare raspuns f.d.t la semnal rampa 
					
					raspuns_la_semnal_initial =	PlotLine (panelHandle, PANEL_GRAPH, tk_1, xk3_1, tk, xk3, VAL_BLUE);
						
				///afisare raspuns f.d.t la semnal rampa defazat (cu t0)      	
					
					raspuns_la_semnal_defazat =	PlotLine (panelHandle, PANEL_GRAPH_2, tk_1, yk3_1, tk, yk3, VAL_RED);
			
				
			
				//reactualizare timp
					
							tk_1=tk; 
							tk=tk+Te;
						
				//generare esantioane noi  
						
							xk_1 = xk;
							xk1_1 = xk1;
							xk2_1= xk2;
							xk3_1=xk3;
							
							yk_1 = yk;
							yk1_1 = yk1;
							yk2_1= yk2;
							yk3_1=yk3;
							
						
			
				
			}	
			
						
			 
			
					
				   

			break;
	}
	return 0;
}



 









