#ifndef BLINKSEQUENCER_H
#define BLINKSEQUENCER_H

//(*Headers(BlinkSequencer)
#include <wx/stopwatch.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/radiobut.h>
#include <wx/slider.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/timer.h>
#include <wx/listbox.h>
//*)



class BlinkSequencer: public wxDialog
{
	public:

		BlinkSequencer(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~BlinkSequencer();

		//(*Declarations(BlinkSequencer)
		wxStaticText* StaticText24;
		wxStaticText* StaticText22;
		wxCheckBox* CheckBox13;
		wxRadioButton* RadioButton1;
		wxStaticText* StaticText21;
		wxStaticText* StaticText13;
		wxStaticText* StaticText14;
		wxStaticText* StaticText15;
		wxSlider* Slider4;
		wxListBox* ListBox1;
		wxSlider* Slider3;
		wxChoice* Choice3;
		wxStaticText* StaticText32;
		wxStaticText* StaticText17;
		wxStaticText* StaticText28;
		wxSlider* Slider8;
		wxCheckBox* CheckBox10;
		wxButton* Button4;
		wxButton* Button1;
		wxCheckBox* CheckBox1;
		wxCheckBox* CheckBox6;
		wxButton* Button2;
		wxButton* Button3;
		wxCheckBox* CheckBox12;
		wxChoice* Choice2;
		wxStaticText* StaticText20;
		wxStaticText* StaticText18;
		wxStaticText* StaticText1;
		wxCheckBox* CheckBox16;
		wxStaticText* StaticText10;
		wxStaticText* StaticText16;
		wxTimer Timer1;
		wxStaticBox* StaticBox2;
		wxButton* Button8;
		wxSlider* Slider5;
		wxStaticText* StaticText3;
		wxSlider* Slider11;
		wxStaticText* StaticText23;
		wxSlider* Slider9;
		wxCheckBox* CheckBox8;
		wxCheckBox* CheckBox4;
		wxChoice* Choice1;
		wxRadioButton* RadioButton2;
		wxButton* Button5;
		wxCheckBox* CheckBox2;
		wxStaticText* StaticText8;
		wxStaticText* StaticText12;
		wxCheckBox* CheckBox7;
		wxButton* Button9;
		wxStaticBox* StaticBox1;
		wxStaticText* StaticText7;
		wxCheckBox* CheckBox15;
		wxStaticBox* StaticBox3;
		wxSlider* Slider7;
		wxTextCtrl* TextCtrl1;
		wxStaticText* StaticText4;
		wxSlider* Slider2;
		wxStaticText* StaticText5;
		wxStaticText* StaticText30;
		wxStaticText* StaticText2;
		wxSlider* Slider10;
		wxStopWatch StopWatch1;
		wxStaticText* StaticText27;
		wxCheckBox* CheckBox17;
		wxCheckBox* CheckBox3;
		wxStaticBox* StaticBox4;
		wxCheckBox* CheckBox9;
		wxStaticText* StaticText26;
		wxCheckBox* CheckBox14;
		wxStaticText* StaticText6;
		wxSlider* Slider1;
		wxStaticBox* StaticBox5;
		wxStaticText* StaticText19;
		wxButton* Button7;
		wxCheckBox* CheckBox11;
		wxStaticText* StaticText29;
		wxSlider* Slider12;
		wxSlider* Slider6;
		wxStaticText* StaticText9;
		wxButton* Button6;
		wxStaticText* StaticText31;
		wxStaticText* StaticText11;
		wxStaticText* StaticText25;
		wxCheckBox* CheckBox5;
		//*)
        void savenewprofile(void);
        void updateprofile(void);
        void updatechannels(void);
        void beatcounter(void);
        void updatelabels(void);
        void bscalculateincrements(void);
        void updatestartbeatbox(void);

	protected:
		//(*Identifiers(BlinkSequencer)
		static const long ID_STATICBOX1;
		static const long ID_STATICBOX4;
		static const long ID_STATICBOX3;
		static const long ID_STATICBOX2;
		static const long ID_CHOICE1;
		static const long ID_SLIDER1;
		static const long ID_SLIDER2;
		static const long ID_SLIDER3;
		static const long ID_SLIDER4;
		static const long ID_SLIDER5;
		static const long ID_SLIDER6;
		static const long ID_SLIDER7;
		static const long ID_SLIDER8;
		static const long ID_SLIDER9;
		static const long ID_SLIDER10;
		static const long ID_SLIDER11;
		static const long ID_SLIDER12;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_CHOICE3;
		static const long ID_LISTBOX1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT13;
		static const long ID_BUTTON5;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT14;
		static const long ID_BUTTON6;
		static const long ID_BUTTON7;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT20;
		static const long ID_STATICTEXT21;
		static const long ID_STATICTEXT22;
		static const long ID_STATICTEXT23;
		static const long ID_STATICTEXT24;
		static const long ID_STATICTEXT25;
		static const long ID_STATICTEXT26;
		static const long ID_STATICTEXT27;
		static const long ID_STATICTEXT28;
		static const long ID_STATICTEXT29;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT30;
		static const long ID_BUTTON2;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_STATICTEXT31;
		static const long ID_CHECKBOX1;
		static const long ID_BUTTON9;
		static const long ID_STATICTEXT15;
		static const long ID_CHOICE2;
		static const long ID_STATICTEXT18;
		static const long ID_STATICTEXT32;
		static const long ID_BUTTON8;
		static const long ID_STATICBOX5;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_CHECKBOX9;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX11;
		static const long ID_CHECKBOX12;
		static const long ID_CHECKBOX13;
		static const long ID_CHECKBOX14;
		static const long ID_CHECKBOX15;
		static const long ID_CHECKBOX16;
		static const long ID_CHECKBOX17;
		static const long ID_TIMER1;
		//*)

	private:

		//(*Handlers(BlinkSequencer)
		void OnChoice1Select(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnChoice2Select(wxCommandEvent& event);
		void changebeat(void);
		void loadprofiles(void);
		void OnButton5Click(wxCommandEvent& event);
		void OnCheckBox1Click(wxCommandEvent& event);
		void OnChoice3Select(wxCommandEvent& event);
		void OnSlider1CmdScroll(wxScrollEvent& event);
		void OnSlider2CmdScroll(wxScrollEvent& event);
		void OnSlider3CmdScroll(wxScrollEvent& event);
		void OnSlider4CmdScroll(wxScrollEvent& event);
		void OnSlider5CmdScroll(wxScrollEvent& event);
		void OnSlider6CmdScroll(wxScrollEvent& event);
		void OnSlider7CmdScroll(wxScrollEvent& event);
		void OnSlider8CmdScroll(wxScrollEvent& event);
		void OnSlider9CmdScroll(wxScrollEvent& event);
		void OnSlider10CmdScroll(wxScrollEvent& event);
		void OnSlider11CmdScroll(wxScrollEvent& event);
		void OnSlider12CmdScroll(wxScrollEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnKillFocus(wxFocusEvent& event);
		void OnListBox1Select(wxCommandEvent& event);
		void OnTimer1Trigger(wxTimerEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnButton6Click(wxCommandEvent& event);
		void OnButton7Click(wxCommandEvent& event);
		void OnButton1Click1(wxCommandEvent& event);
		void OnRadioButton1Select(wxCommandEvent& event);
		void OnRadioButton2Select(wxCommandEvent& event);
		void OnButton8Click(wxCommandEvent& event);
		void OnCheckBox1Click1(wxCommandEvent& event);
		void OnChoice2Select1(wxCommandEvent& event);
		void OnButton3Click(wxCommandEvent& event);
		void OnButton4Click(wxCommandEvent& event);
		void OnButton9Click(wxCommandEvent& event);
		void OnSlider1CmdScroll1(wxScrollEvent& event);
		void OnTextCtrl1TextEnter(wxCommandEvent& event);
		void OnButton8Click1(wxCommandEvent& event);
		void OnButton8Click2(wxCommandEvent& event);
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
		void OnCheckBox17Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};




#endif
