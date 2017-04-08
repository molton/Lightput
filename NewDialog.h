#ifndef NEWDIALOG_H
#define NEWDIALOG_H

//(*Headers(NewDialog)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
//*)

class NewDialog: public wxDialog
{
	public:

		NewDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NewDialog();

		//(*Declarations(NewDialog)
		wxListBox* ListBox1;
		wxButton* Button4;
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		wxButton* Button5;
		//*)

	protected:

		//(*Identifiers(NewDialog)
		static const long ID_LISTBOX1;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(NewDialog)
		void OnButton1Click(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnButton4Click(wxCommandEvent& event);
		void OnButton1Click1(wxCommandEvent& event);
		void OnButton5Click(wxCommandEvent& event);
		void OnListBox1Select(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
