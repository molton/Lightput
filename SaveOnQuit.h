#ifndef SAVEONQUIT_H
#define SAVEONQUIT_H

//(*Headers(SaveOnQuit)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class SaveOnQuit: public wxDialog
{
	public:

		SaveOnQuit(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SaveOnQuit();

		//(*Declarations(SaveOnQuit)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(SaveOnQuit)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(SaveOnQuit)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
