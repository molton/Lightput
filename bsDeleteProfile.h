#ifndef BSDELETEPROFILE_H
#define BSDELETEPROFILE_H

//(*Headers(bsDeleteProfile)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class bsDeleteProfile: public wxDialog
{
	public:

		bsDeleteProfile(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~bsDeleteProfile();

		//(*Declarations(bsDeleteProfile)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(bsDeleteProfile)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(bsDeleteProfile)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
