#ifndef SAVEFIRST_H
#define SAVEFIRST_H

//(*Headers(SaveFirst)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class SaveFirst: public wxDialog
{
	public:

		SaveFirst(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SaveFirst();

		//(*Declarations(SaveFirst)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxStaticText* StaticText2;
		//*)

	protected:

		//(*Identifiers(SaveFirst)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT4;
		//*)

	private:

		//(*Handlers(SaveFirst)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
