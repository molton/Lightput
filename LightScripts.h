#ifndef LIGHTSCRIPTS_H
#define LIGHTSCRIPTS_H

//(*Headers(LightScripts)
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/radiobut.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

class LightScripts: public wxDialog
{
	public:

		LightScripts(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~LightScripts();

		//(*Declarations(LightScripts)
		wxStaticText* StaticText24;
		wxStaticText* StaticText22;
		wxButton* CopyButton;
		wxButton* NextButton;
		wxTextCtrl* TextCtrl3;
		wxButton* PreviousButton;
		wxButton* PauseButton;
		wxTextCtrl* TextCtrl10;
		wxButton* GoButton;
		wxCheckBox* CheckBox13;
		wxRadioButton* RadioButton1;
		wxStaticText* StaticText21;
		wxStaticText* StaticText13;
		wxStaticText* StaticText14;
		wxStaticText* StaticText15;
		wxStaticText* StaticText17;
		wxTextCtrl* TextCtrl9;
		wxButton* SaveButton;
		wxCheckBox* CheckBox10;
		wxCheckBox* CheckBox1;
		wxCheckBox* CheckBox6;
		wxButton* NewScriptButton;
		wxCheckBox* CheckBox12;
		wxTextCtrl* TextCtrl18;
		wxStaticText* StaticText20;
		wxStaticText* StaticText18;
		wxStaticText* StaticText1;
		wxCheckBox* CheckBox16;
		wxStaticText* StaticText10;
		wxStaticText* StaticText16;
		wxButton* DeleteButton;
		wxStaticBox* StaticBox2;
		wxTextCtrl* TextCtrl5;
		wxStaticText* StaticText3;
		wxStaticText* StaticText23;
		wxCheckBox* CheckBox8;
		wxStaticLine* StaticLine1;
		wxCheckBox* CheckBox4;
		wxTextCtrl* TextCtrl12;
		wxRadioButton* RadioButton2;
		wxButton* HideButton;
		wxCheckBox* CheckBox2;
		wxStaticText* StaticText8;
		wxStaticText* StaticText12;
		wxCheckBox* CheckBox7;
		wxTextCtrl* TextCtrl16;
		wxTextCtrl* TextCtrl6;
		wxStaticBox* StaticBox1;
		wxStaticText* StaticText7;
		wxCheckBox* CheckBox15;
		wxButton* LoadButton;
		wxStaticBox* StaticBox3;
		wxTextCtrl* TextCtrl1;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxButton* StartStopButton;
		wxStaticText* StaticText2;
		wxCheckBox* CheckBox17;
		wxStaticBox* StaticBox4;
		wxCheckBox* CheckBox3;
		wxCheckBox* CheckBox9;
		wxCheckBox* CheckBox14;
		wxTextCtrl* TextCtrl11;
		wxStaticText* StaticText6;
		wxStaticBox* StaticBox5;
		wxTextCtrl* TextCtrl15;
		wxTextCtrl* TextCtrl8;
		wxStaticText* StaticText19;
		wxCheckBox* CheckBox11;
		wxTextCtrl* TextCtrl7;
		wxStaticText* StaticText9;
		wxTextCtrl* TextCtrl4;
		wxTextCtrl* TextCtrl2;
		wxButton* Button6;
		wxTextCtrl* TextCtrl13;
		wxTimer LightScriptTimer;
		wxStaticBox* StaticBox6;
		wxStaticText* StaticText11;
		wxCheckBox* CheckBox5;
		wxTextCtrl* TextCtrl17;
		wxTextCtrl* TextCtrl14;
		//*)

	protected:

		//(*Identifiers(LightScripts)
		static const long ID_STATICBOX1;
		static const long ID_STATICBOX2;
		static const long ID_STATICTEXT1;
		static const long ID_CHECKBOX1;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_TEXTCTRL3;
		static const long ID_TEXTCTRL4;
		static const long ID_TEXTCTRL5;
		static const long ID_TEXTCTRL6;
		static const long ID_TEXTCTRL7;
		static const long ID_TEXTCTRL8;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRL9;
		static const long ID_CHECKBOX9;
		static const long ID_STATICLINE1;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_TEXTCTRL10;
		static const long ID_TEXTCTRL11;
		static const long ID_TEXTCTRL12;
		static const long ID_TEXTCTRL13;
		static const long ID_TEXTCTRL14;
		static const long ID_TEXTCTRL15;
		static const long ID_TEXTCTRL16;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX11;
		static const long ID_CHECKBOX12;
		static const long ID_CHECKBOX13;
		static const long ID_CHECKBOX14;
		static const long ID_CHECKBOX15;
		static const long ID_CHECKBOX16;
		static const long ID_STATICBOX3;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT20;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT21;
		static const long ID_TEXTCTRL17;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_BUTTON7;
		static const long ID_STATICBOX4;
		static const long ID_BUTTON8;
		static const long ID_BUTTON9;
		static const long ID_CHECKBOX17;
		static const long ID_STATICBOX5;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_STATICBOX6;
		static const long ID_TEXTCTRL18;
		static const long ID_STATICTEXT22;
		static const long ID_BUTTON10;
		static const long ID_BUTTON11;
		static const long ID_STATICTEXT23;
		static const long ID_STATICTEXT24;
		static const long ID_BUTTON12;
		static const long ID_TIMER1;
		//*)

	private:

		//(*Handlers(LightScripts)
		void OnButton6Click(wxCommandEvent& event);
		void OnSaveButtonClick(wxCommandEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnTextCtrl2Text(wxCommandEvent& event);
		void OnTextCtrl3Text(wxCommandEvent& event);
		void OnTextCtrl4Text(wxCommandEvent& event);
		void OnTextCtrl5Text(wxCommandEvent& event);
		void OnTextCtrl6Text(wxCommandEvent& event);
		void OnTextCtrl7Text(wxCommandEvent& event);
		void OnTextCtrl8Text(wxCommandEvent& event);
		void OnTextCtrl9Text(wxCommandEvent& event);
		void OnTextCtrl10Text(wxCommandEvent& event);
		void OnTextCtrl11Text(wxCommandEvent& event);
		void OnTextCtrl12Text(wxCommandEvent& event);
		void OnTextCtrl13Text(wxCommandEvent& event);
		void OnTextCtrl14Text(wxCommandEvent& event);
		void OnTextCtrl15Text(wxCommandEvent& event);
		void OnTextCtrl16Text(wxCommandEvent& event);
		void OnCheckBox1Click(wxCommandEvent& event);
		void OnCheckBox2Click(wxCommandEvent& event);
		void OnCheckBox3Click(wxCommandEvent& event);
		void OnCheckBox4Click(wxCommandEvent& event);
		void OnCheckBox5Click(wxCommandEvent& event);
		void OnCheckBox6Click(wxCommandEvent& event);
		void OnCheckBox7Click(wxCommandEvent& event);
		void OnCheckBox8Click(wxCommandEvent& event);
		void OnCheckBox9Click(wxCommandEvent& event);
		void OnCheckBox10Click(wxCommandEvent& event);
		void OnCheckBox11Click(wxCommandEvent& event);
		void OnCheckBox12Click(wxCommandEvent& event);
		void OnCheckBox13Click(wxCommandEvent& event);
		void OnCheckBox14Click(wxCommandEvent& event);
		void OnCheckBox15Click(wxCommandEvent& event);
		void OnCheckBox16Click(wxCommandEvent& event);
		void OnTextCtrl18Text(wxCommandEvent& event);
		void OnPreviousButtonClick(wxCommandEvent& event);
		void OnNextButtonClick(wxCommandEvent& event);
		void OnGoButtonClick(wxCommandEvent& event);
		void OnStartStopButtonClick(wxCommandEvent& event);
		void OnLightScriptTimerTrigger(wxTimerEvent& event);
		void OnPauseButtonClick(wxCommandEvent& event);
		void OnLoadButtonClick(wxCommandEvent& event);
		void OnDeleteButtonClick(wxCommandEvent& event);
		void OnCopyButtonClick(wxCommandEvent& event);
		void OnCheckBox17Click(wxCommandEvent& event);
		void OnRadioButton2Select(wxCommandEvent& event);
		void OnRadioButton1Select(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnNewScriptButtonClick(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnButton1Click1(wxCommandEvent& event);
		void OnHideButtonClick(wxCommandEvent& event);
		//*)

        void BlankStep(void);
        void LoadStep(void);
        void UpdateStepCounter(void);
        void CommitCurrentLine(void);
        void LoadCurrentLine(void);
        void CalculateIncrements(void);
        void StartSettings(void);
        void StopSettings(void);
        void SaveScript(void);

		DECLARE_EVENT_TABLE()
};

#endif
