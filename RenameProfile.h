#ifndef RENAMEPROFILE_H
#define RENAMEPROFILE_H

//(*Headers(RenameProfile)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class RenameProfile: public wxDialog
{
	public:

		RenameProfile(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~RenameProfile();

		//(*Declarations(RenameProfile)
		wxButton* Button1;
		wxStaticText* StaticText1;
		wxButton* Button2;
		wxTextCtrl* TextCtrl1;
		//*)

	protected:

		//(*Identifiers(RenameProfile)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(RenameProfile)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnButton2Click1(wxCommandEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnButton1Click1(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
