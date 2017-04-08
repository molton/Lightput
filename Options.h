#ifndef OPTIONS_H
#define OPTIONS_H

//(*Headers(Options)
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/radiobut.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
//*)

class Options: public wxDialog
{
	public:

		Options(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~Options();

		//(*Declarations(Options)
		wxRadioButton* RadioButton1;
		wxStaticBox* StaticBox8;
		wxStaticBox* StaticBox7;
		wxChoice* Choice3;
		wxButton* Button1;
		wxCheckBox* CheckBox1;
		wxCheckBox* CheckBox6;
		wxButton* Button2;
		wxChoice* Choice2;
		wxStaticText* StaticText1;
		wxStaticBox* StaticBox2;
		wxStaticText* StaticText3;
		wxCheckBox* CheckBox4;
		wxChoice* Choice1;
		wxRadioButton* RadioButton2;
		wxCheckBox* CheckBox2;
		wxCheckBox* CheckBox7;
		wxStaticBox* StaticBox1;
		wxStaticBox* StaticBox3;
		wxChoice* TransitionChoice;
		wxTextCtrl* TextCtrl1;
		wxStaticText* StaticText2;
		wxCheckBox* CheckBox3;
		wxStaticBox* StaticBox4;
		wxStaticBox* StaticBox5;
		wxStaticBox* StaticBox6;
		wxCheckBox* CheckBox5;
		//*)

	protected:

		//(*Identifiers(Options)
		static const long ID_STATICBOX2;
		static const long ID_STATICBOX1;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICBOX4;
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICBOX3;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_STATICBOX5;
		static const long ID_CHOICE2;
		static const long ID_STATICTEXT3;
		static const long ID_CHECKBOX3;
		static const long ID_STATICBOX6;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_STATICBOX7;
		static const long ID_CHOICE3;
		static const long ID_STATICBOX8;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_CHOICE4;
		static const long ID_STATICTEXT1;
		//*)

	private:

		//(*Handlers(Options)
		void OnButton2Click(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnRadioButton1Select(wxCommandEvent& event);
		void OnCheckBox2Click(wxCommandEvent& event);
		void OnCheckBox1Click(wxCommandEvent& event);
		void OnChoice2Select(wxCommandEvent& event);
		void OnCheckBox3Click(wxCommandEvent& event);
		void OnCheckBox4Click(wxCommandEvent& event);
		void OnCheckBox5Click(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnChoice1Select(wxCommandEvent& event);
		void OnCheckBox6Click(wxCommandEvent& event);
		void OnCheckBox7Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
