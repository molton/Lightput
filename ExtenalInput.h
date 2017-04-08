#ifndef EXTENALINPUT_H
#define EXTENALINPUT_H

//(*Headers(ExtenalInput)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/timer.h>
//*)

class ExtenalInput: public wxDialog
{
	public:

		ExtenalInput(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ExtenalInput();

		//(*Declarations(ExtenalInput)
		wxButton* CloseButton;
		wxStaticBox* StaticBox1;
		wxStaticText* StaticText2;
		wxTimer EItimer;
		//*)

	protected:

		//(*Identifiers(ExtenalInput)
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON2;
		static const long ID_TIMER1;
		//*)

	private:

		//(*Handlers(ExtenalInput)
		void OnButton1Click(wxCommandEvent& event);
		void OnEItimerTrigger(wxTimerEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
