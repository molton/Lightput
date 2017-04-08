#ifndef BSPROFILEOVERWRITE_H
#define BSPROFILEOVERWRITE_H

//(*Headers(bsProfileOverwrite)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class bsProfileOverwrite: public wxDialog
{
	public:

		bsProfileOverwrite(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~bsProfileOverwrite();

		//(*Declarations(bsProfileOverwrite)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(bsProfileOverwrite)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(bsProfileOverwrite)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnButton2Click1(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
