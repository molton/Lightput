#ifndef ALARMCLOCK_H
#define ALARMCLOCK_H

//(*Headers(AlarmClock)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/slider.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/timer.h>
//*)

class AlarmClock: public wxDialog
{
	public:

		AlarmClock(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AlarmClock();

		//(*Declarations(AlarmClock)
		wxStaticText* StaticText13;
		wxChoice* Choice3;
		wxButton* Button4;
		wxButton* Button1;
		wxButton* Button2;
		wxButton* Button3;
		wxChoice* Choice2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText10;
		wxTimer Timer1;
		wxStaticBox* StaticBox2;
		wxChoice* Choice4;
		wxStaticText* StaticText3;
		wxChoice* Choice5;
		wxChoice* Choice1;
		wxStaticText* StaticText8;
		wxStaticText* StaticText12;
		wxChoice* Choice7;
		wxStaticBox* StaticBox1;
		wxStaticText* StaticText7;
		wxStaticText* StaticText4;
		wxSlider* Slider2;
		wxStaticText* StaticText5;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxSlider* Slider1;
		wxChoice* Choice6;
		wxStaticText* StaticText9;
		wxStaticText* StaticText11;
		//*)

	protected:

		//(*Identifiers(AlarmClock)
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_BUTTON1;
		static const long ID_CHOICE1;
		static const long ID_CHOICE2;
		static const long ID_CHOICE3;
		static const long ID_STATICTEXT5;
		static const long ID_STATICBOX2;
		static const long ID_CHOICE4;
		static const long ID_CHOICE5;
		static const long ID_SLIDER1;
		static const long ID_SLIDER2;
		static const long ID_CHOICE6;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_BUTTON2;
		static const long ID_CHOICE7;
		static const long ID_STATICTEXT13;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT8;
		static const long ID_BUTTON4;
		static const long ID_TIMER1;
		//*)

	private:

		//(*Handlers(AlarmClock)
		void OnChoice1Select(wxCommandEvent& event);
		void OnTimer1Trigger(wxTimerEvent& event);
		void OnChoice2Select(wxCommandEvent& event);
		void OnChoice7Select(wxCommandEvent& event);
		void OnButton3Click(wxCommandEvent& event);
		void OnButton3Click1(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnChoice6Select(wxCommandEvent& event);
		void alarm_calculateincrements(void);
		void snoozehandler (void);
		void alarm_loadprofiles(void);
		void alarm_saveprofiles(void);
		void OnClose(wxCloseEvent& event);
		void OnChoice4Select(wxCommandEvent& event);
		void OnSlider1CmdScroll(wxScrollEvent& event);
		void OnSlider2CmdScroll(wxScrollEvent& event);
		void OnChoice5Select(wxCommandEvent& event);
		void OnChoice7Select1(wxCommandEvent& event);
		void OnSlider2CmdScroll1(wxScrollEvent& event);
		void OnChoice3Select(wxCommandEvent& event);
		void OnButton4Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
