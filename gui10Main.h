/***************************************************************
 * Name:      gui10Main.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2012-09-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef GUI10MAIN_H
#define GUI10MAIN_H

#include "ftd2xx.h"
#include "FTDI_interface.h"

//(*Headers(gui10Frame)
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/slider.h>
#include <wx/statbox.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/timer.h>
#include <wx/listbox.h>
//*)
#include <wx/timer.h>

//#include <iostream>
//#include <cstdlib>
//#include <vector>


class gui10Frame: public wxFrame
{
    public:

        gui10Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~gui10Frame();


   private:
        //(*Handlers(gui10Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnButton1Click1(wxCommandEvent& event);
        void OnButton4Click(wxCommandEvent& event);
        void OnChoice2Select(wxCommandEvent& event);
        void OnSlider1CmdScroll1(wxScrollEvent& event);
        void OnSlider1CmdScroll(wxScrollEvent& event);
        void OnSlider2CmdScroll(wxScrollEvent& event);
        void OnSlider3CmdScroll(wxScrollEvent& event);
        void OnSlider4CmdScroll(wxScrollEvent& event);
        void OnListBox1Select(wxCommandEvent& event);
        void OnMENUITEM1(wxCommandEvent& event);
        void DMXconnect(void);
        void loadoptions(void);
        void loadprofile(void);
        void updateprofile(void);
        void updatesliders(void);
        void saveprofile(void);
        void DMXSend_initialize(void);
        void setoutputchannels(void);
        void calculateincrements(void);
        void updateprofileinterval(void);
        void LightProgramStart(void);
        void LightProgramStop(void);
        void saveoptions(void);
        void OnButton6Click(wxCommandEvent& event);
        void OnButton2Click1(wxCommandEvent& event);
        void OnButton5Click(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnSlider6CmdScroll(wxScrollEvent& event);
        void OnSlider5CmdScroll(wxScrollEvent& event);
        void OnSlider7CmdScroll(wxScrollEvent& event);
        void OnSlider8CmdScroll(wxScrollEvent& event);
        void OnSlider9CmdScroll(wxScrollEvent& event);
        void OnSlider10CmdScroll(wxScrollEvent& event);
        void OnSlider11CmdScroll(wxScrollEvent& event);
        void OnSlider12CmdScroll(wxScrollEvent& event);
        void OnSlider13CmdScroll(wxScrollEvent& event);
        void OnSlider14CmdScroll(wxScrollEvent& event);
        void OnSlider15CmdScroll(wxScrollEvent& event);
        void OnSlider16CmdScroll(wxScrollEvent& event);
        void OnButton7Click(wxCommandEvent& event);
        void OnButton8Click(wxCommandEvent& event);
        void OnButton1Click2(wxCommandEvent& event);
        void OnButton11Click(wxCommandEvent& event);
        void OnButton11Click1(wxCommandEvent& event);
        void OnButton2Click2(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnMenuItem4Selected(wxCommandEvent& event);
        void OnButton12Click(wxCommandEvent& event);
        void OnButton12Click1(wxCommandEvent& event);
        void OnButton12Click2(wxCommandEvent& event);
        void OnHelp(wxCommandEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnSetFocus(wxFocusEvent& event);
        void OnResize(wxSizeEvent& event);
        void OnMouseEnter(wxMouseEvent& event);
        void OnMouseEnter1(wxMouseEvent& event);
        //*)
        void InitializeLightputEngine(void);
        void RunLightProgramOnStartup(void);

        //(*Identifiers(gui10Frame)
        static const long ID_STATICBOX1;
        static const long ID_LISTBOX1;
        static const long ID_BUTTON4;
        static const long ID_BUTTON8;
        static const long ID_BUTTON7;
        static const long ID_BUTTON2;
        static const long ID_BUTTON6;
        static const long ID_BUTTON1;
        static const long ID_BUTTON9;
        static const long ID_BUTTON11;
        static const long ID_BUTTON3;
        static const long ID_BUTTON12;
        static const long ID_BUTTON5;
        static const long ID_SLIDER1;
        static const long ID_SLIDER2;
        static const long ID_SLIDER3;
        static const long ID_SLIDER4;
        static const long ID_SLIDER5;
        static const long ID_SLIDER6;
        static const long ID_SLIDER7;
        static const long ID_SLIDER8;
        static const long ID_SLIDER9;
        static const long ID_SLIDER10;
        static const long ID_SLIDER11;
        static const long ID_SLIDER12;
        static const long ID_SLIDER13;
        static const long ID_SLIDER14;
        static const long ID_SLIDER15;
        static const long ID_SLIDER16;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT10;
        static const long ID_STATICTEXT12;
        static const long ID_STATICTEXT17;
        static const long ID_STATICTEXT18;
        static const long ID_STATICTEXT22;
        static const long ID_STATICTEXT21;
        static const long ID_STATICTEXT20;
        static const long ID_STATICTEXT19;
        static const long ID_STATICTEXT16;
        static const long ID_STATICTEXT15;
        static const long ID_STATICTEXT14;
        static const long ID_STATICTEXT13;
        static const long ID_STATICTEXT11;
        static const long ID_STATICTEXT23;
        static const long ID_STATICTEXT24;
        static const long ID_STATICTEXT25;
        static const long ID_STATICTEXT26;
        static const long ID_STATICTEXT27;
        static const long ID_STATICTEXT28;
        static const long ID_STATICTEXT29;
        static const long ID_STATICTEXT30;
        static const long ID_STATICTEXT31;
        static const long ID_STATICTEXT32;
        static const long ID_STATICTEXT33;
        static const long ID_STATICTEXT34;
        static const long ID_STATICTEXT35;
        static const long ID_STATICTEXT36;
        static const long ID_MENUITEM2;
        static const long ID_MENUITEM1;
        static const long idMenuQuit;
        static const long idMenuHelp;
        static const long idMenuAbout;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(gui10Frame)
        wxStaticText* StaticText24;
        wxStaticText* StaticText22;
        wxStaticText* StaticText21;
        wxStaticText* StaticText13;
        wxStaticText* StaticText14;
        wxStaticText* StaticText15;
        wxStaticText* StaticText35;
        wxSlider* Slider4;
        wxListBox* ListBox1;
        wxSlider* Slider3;
        wxStaticText* StaticText32;
        wxStaticText* StaticText17;
        wxStaticText* StaticText28;
        wxSlider* Slider8;
        wxButton* Button4;
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxSlider* Slider15;
        wxButton* Button12;
        wxStaticText* StaticText20;
        wxStaticText* StaticText18;
        wxStaticText* StaticText1;
        wxStaticText* StaticText10;
        wxStaticText* StaticText16;
        wxTimer Timer1;
        wxSlider* Slider5;
        wxButton* Button8;
        wxStaticText* StaticText3;
        wxSlider* Slider11;
        wxSlider* Slider13;
        wxStaticText* StaticText23;
        wxSlider* Slider9;
        wxMenuItem* MenuItem3;
        wxButton* Button5;
        wxStaticText* StaticText8;
        wxStaticText* StaticText34;
        wxStaticText* StaticText12;
        wxSlider* Slider16;
        wxButton* Button9;
        wxStaticBox* StaticBox1;
        wxStaticText* StaticText7;
        wxSlider* Slider7;
        wxStaticText* StaticText4;
        wxSlider* Slider2;
        wxStaticText* StaticText5;
        wxSlider* Slider14;
        wxStaticText* StaticText36;
        wxStaticText* StaticText30;
        wxStaticText* StaticText2;
        wxSlider* Slider10;
        wxStaticText* StaticText27;
        wxMenuItem* MenuItem4;
        wxStaticText* StaticText26;
        wxStaticText* StaticText6;
        wxSlider* Slider1;
        wxButton* Button11;
        wxStaticText* StaticText19;
        wxButton* Button7;
        wxStaticText* StaticText29;
        wxSlider* Slider12;
        wxSlider* Slider6;
        wxStaticText* StaticText9;
        wxStaticText* StaticText33;
        wxButton* Button6;
        wxStaticText* StaticText31;
        wxStaticText* StaticText11;
        wxStaticText* StaticText25;
        //*)

        DECLARE_EVENT_TABLE()
};
/*
class DMXtimer : public wxTimer
{

        public:

		void Notify(void);
        DMXtimer* Timer1;

};
*/

#endif // GUI10MAIN_H
