#ifndef LSSAVEDIALOG_H
#define LSSAVEDIALOG_H

//(*Headers(lsSaveDialog)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class lsSaveDialog: public wxDialog
{
	public:

		lsSaveDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~lsSaveDialog();

		//(*Declarations(lsSaveDialog)
		wxButton* SaveButton_sd;
		wxStaticText* StaticText_A2;
		wxTextCtrl* TextCtrlFileName;
		wxButton* CancelButton_sd;
		wxStaticText* StaticText_A1;
		//*)

	protected:

		//(*Identifiers(lsSaveDialog)
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(lsSaveDialog)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
