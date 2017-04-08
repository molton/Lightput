#ifndef PROFILEOVERWRITE_H
#define PROFILEOVERWRITE_H

//(*Headers(ProfileOverwrite)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class ProfileOverwrite: public wxDialog
{
	public:

		ProfileOverwrite(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ProfileOverwrite();

		//(*Declarations(ProfileOverwrite)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		//*)

	protected:

		//(*Identifiers(ProfileOverwrite)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(ProfileOverwrite)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
