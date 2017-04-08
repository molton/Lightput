#ifndef H24DELETEPROFILE_H
#define H24DELETEPROFILE_H

//(*Headers(H24DeleteProfile)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class H24DeleteProfile: public wxDialog
{
	public:

		H24DeleteProfile(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~H24DeleteProfile();

		//(*Declarations(H24DeleteProfile)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(H24DeleteProfile)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(H24DeleteProfile)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
