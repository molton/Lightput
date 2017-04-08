#ifndef LSSAVECHANGESDIALOG_H
#define LSSAVECHANGESDIALOG_H

//(*Headers(lsSaveChangesDialog)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class lsSaveChangesDialog: public wxDialog
{
	public:

		lsSaveChangesDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~lsSaveChangesDialog();

		//(*Declarations(lsSaveChangesDialog)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(lsSaveChangesDialog)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(lsSaveChangesDialog)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
