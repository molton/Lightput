#ifndef ADDNEWPROFILE_H
#define ADDNEWPROFILE_H

//(Headers(AddNewProfile)
#include <wx/dialog.h>
//*
#include <wx/textctrl.h>
#include <wx/frame.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/msgdlg.h>




class AddNewProfile: public wxDialog
{
	public:

		AddNewProfile(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AddNewProfile();

		//(*Declarations(AddNewProfile)
		wxButton* Button1;
		wxStaticText* StaticText1;
		wxButton* Button2;
		wxTextCtrl* TextCtrl1;
		//*)

	protected:

		//(*Identifiers(AddNewProfile)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(AddNewProfile)
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
