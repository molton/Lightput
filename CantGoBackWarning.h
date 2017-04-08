#ifndef CANTGOBACKWARNING_H
#define CANTGOBACKWARNING_H

//(*Headers(CantGoBackWarning)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class CantGoBackWarning: public wxDialog
{
	public:

		CantGoBackWarning(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CantGoBackWarning();

		//(*Declarations(CantGoBackWarning)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(CantGoBackWarning)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(CantGoBackWarning)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
