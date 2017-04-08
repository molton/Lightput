#ifndef LSLOADDIALOG_H
#define LSLOADDIALOG_H

//(*Headers(lsLoadDialog)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
//*)

class lsLoadDialog: public wxDialog
{
	public:

		lsLoadDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~lsLoadDialog();

		//(*Declarations(lsLoadDialog)
		wxListBox* ListBox1;
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(lsLoadDialog)
		static const long ID_LISTBOX1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT1;
		//*)

	private:

		//(*Handlers(lsLoadDialog)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
