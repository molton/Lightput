#ifndef DELETEVERIFY_H
#define DELETEVERIFY_H

//(*Headers(DeleteVerify)
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class DeleteVerify: public wxDialog
{
	public:

		DeleteVerify(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DeleteVerify();

		//(*Declarations(DeleteVerify)
		wxStaticText* StaticText2;
		wxButton* Button1;
		wxStaticText* StaticText1;
		wxButton* Button2;
		//*)

	protected:

		//(*Identifiers(DeleteVerify)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT2;
		//*)

	private:

		//(*Handlers(DeleteVerify)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
