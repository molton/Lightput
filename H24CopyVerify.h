#ifndef H24COPYVERIFY_H
#define H24COPYVERIFY_H

//(*Headers(H24CopyVerify)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class H24CopyVerify: public wxDialog
{
	public:

		H24CopyVerify(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~H24CopyVerify();

		//(*Declarations(H24CopyVerify)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(H24CopyVerify)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(H24CopyVerify)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
