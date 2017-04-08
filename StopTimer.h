#ifndef STOPTIMER_H
#define STOPTIMER_H

//(*Headers(StopTimer)
#include <wx/stopwatch.h>
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class StopTimer: public wxDialog
{
	public:

		StopTimer(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~StopTimer();

		//(*Declarations(StopTimer)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		wxStopWatch StopWatch1;
		//*)

	protected:

		//(*Identifiers(StopTimer)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(StopTimer)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
