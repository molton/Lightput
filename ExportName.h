#ifndef EXPORTNAME_H
#define EXPORTNAME_H

//(*Headers(ExportName)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class ExportName: public wxDialog
{
	public:

		ExportName(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ExportName();

		//(*Declarations(ExportName)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxTextCtrl* TextCtrl1;
		wxStaticText* StaticText2;
		//*)

	protected:

		//(*Identifiers(ExportName)
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT3;
		//*)

	private:

		//(*Handlers(ExportName)
		void OnButton1Click(wxCommandEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
