#ifndef LSOVERWRITESCRIPT_H
#define LSOVERWRITESCRIPT_H

//(*Headers(lsOverwriteScript)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class lsOverwriteScript: public wxDialog
{
	public:

		lsOverwriteScript(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~lsOverwriteScript();

		//(*Declarations(lsOverwriteScript)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		//*)

	protected:

		//(*Identifiers(lsOverwriteScript)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(lsOverwriteScript)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
