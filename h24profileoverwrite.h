#ifndef H24PROFILEOVERWRITE_H
#define H24PROFILEOVERWRITE_H

//(*Headers(h24profileoverwrite)
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class h24profileoverwrite: public wxDialog
{
	public:

		h24profileoverwrite(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~h24profileoverwrite();

		//(*Declarations(h24profileoverwrite)
		wxButton* Button1;
		wxStaticText* StaticText1;
		wxButton* Button2;
		//*)

	protected:

		//(*Identifiers(h24profileoverwrite)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(h24profileoverwrite)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
