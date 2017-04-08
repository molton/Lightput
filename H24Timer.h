#ifndef H24TIMER_H
#define H24TIMER_H

//(*Headers(H24Timer)
#include <wx/stopwatch.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/slider.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/timer.h>
#include <wx/listbox.h>
//*)

class H24Timer: public wxDialog
{
	public:

		H24Timer(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~H24Timer();

		//(*Declarations(H24Timer)
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
		wxTimer H24Timer1;
		wxButton* Button1;
		wxCheckBox* CheckBox1;
		wxButton* Button2;
		wxButton* Button3;
		wxSlider* Slider15;
		wxStaticText* StaticText20;
		wxStaticText* StaticText18;
		wxStaticText* StaticText1;
		wxStaticText* StaticText10;
		wxStaticText* StaticText16;
		wxStaticBox* StaticBox2;
		wxButton* Button8;
		wxSlider* Slider5;
		wxStaticText* StaticText3;
		wxSlider* Slider11;
		wxSlider* Slider13;
		wxStaticText* StaticText23;
		wxSlider* Slider9;
		wxChoice* Choice1;
		wxButton* Button5;
		wxStaticText* StaticText8;
		wxStaticText* StaticText34;
		wxStaticText* StaticText12;
		wxButton* Button9;
		wxSlider* Slider16;
		wxStaticBox* StaticBox1;
		wxStaticText* StaticText7;
		wxStaticBox* StaticBox3;
		wxSlider* Slider7;
		wxStaticText* StaticText4;
		wxSlider* Slider2;
		wxStaticText* StaticText5;
		wxSlider* Slider14;
		wxStaticText* StaticText36;
		wxStaticText* StaticText30;
		wxStaticText* StaticText2;
		wxSlider* Slider10;
		wxStopWatch StopWatch1;
		wxStaticText* StaticText27;
		wxStaticText* StaticText26;
		wxStaticText* StaticText6;
		wxSlider* Slider1;
		wxButton* Button7;
		wxStaticText* StaticText19;
		wxListBox* ListBox2;
		wxStaticText* StaticText29;
		wxSlider* Slider12;
		wxSlider* Slider6;
		wxStaticText* StaticText9;
		wxButton* Button6;
		wxStaticText* StaticText33;
		wxStaticText* StaticText31;
		wxStaticText* StaticText11;
		wxStaticText* StaticText25;
		//*)

	protected:

		//(*Identifiers(H24Timer)
		static const long ID_STATICBOX1;
		static const long ID_LISTBOX1;
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
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT20;
		static const long ID_STATICTEXT21;
		static const long ID_STATICTEXT22;
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
		static const long ID_STATICBOX2;
		static const long ID_BUTTON1;
		static const long ID_CHECKBOX1;
		static const long ID_STATICBOX3;
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT33;
		static const long ID_LISTBOX2;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_STATICTEXT34;
		static const long ID_STATICTEXT35;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_STATICTEXT36;
		static const long ID_BUTTON9;
		static const long ID_H24TIMER1;
		//*)

	private:

		//(*Handlers(H24Timer)
		void OnChoice1Select(wxCommandEvent& event);
		void h24_loadprofiles(void);
		void h24_updatelabels(void);
		void h24_calculatetransition(void);
		void saveprofiles(void);
		void stop_timer(void);
		void OnSlider1CmdScroll(wxScrollEvent& event);
		void OnSlider2CmdScroll(wxScrollEvent& event);
		void OnSlider3CmdScroll(wxScrollEvent& event);
		void OnSlider4CmdScroll(wxScrollEvent& event);
		void OnSlider5CmdScroll(wxScrollEvent& event);
		void OnSlider6CmdScroll(wxScrollEvent& event);
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
		void OnListBox1Select(wxCommandEvent& event);
		void OnCheckBox1Click(wxCommandEvent& event);
		void OnH24Timer1Trigger(wxTimerEvent& event);
		void OnButton5Click(wxCommandEvent& event);
		void OnListBox2Select(wxCommandEvent& event);
		void OnButton6Click(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnButton4Click(wxCommandEvent& event);
		void OnButton3Click(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnButton7Click(wxCommandEvent& event);
		void OnButton8Click(wxCommandEvent& event);
		void OnKillFocus(wxFocusEvent& event);
		void OnResize(wxSizeEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		void OnMouseLeave(wxMouseEvent& event);
		void OnResize1(wxSizeEvent& event);
		void OnEraseBackground1(wxEraseEvent& event);
		void OnKillFocus1(wxFocusEvent& event);
		void OnMouseLeave1(wxMouseEvent& event);
		void OnSetFocus(wxFocusEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnButton9Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
