#ifndef MIDICONTROL_H
#define MIDICONTROL_H

//(*Headers(MidiControl)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
//*)


class MidiControl: public wxDialog
{
	public:

		MidiControl(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~MidiControl();


		//(*Declarations(MidiControl)
		wxStaticText* StaticText24;
		wxStaticText* StaticText22;
		wxStaticText* StaticText21;
		wxStaticText* StaticText14;
		wxStaticText* StaticText15;
		wxSlider* Slider4;
		wxStaticText* StaticText35;
		wxStaticText* StaticText37;
		wxButton* Midi_Button3;
		wxSlider* Slider3;
		wxButton* Midi_Button7;
		wxStaticText* StaticText32;
		wxStaticText* StaticText17;
		wxSlider* Slider8;
		wxStaticText* StaticText28;
		wxButton* Midi_Button9;
		wxButton* Midi_Button4;
		wxButton* Midi_Button14;
		wxButton* Midi_Button12;
		wxSlider* Slider15;
		wxStaticText* StaticText41;
		wxStaticText* StaticText20;
		wxStaticText* StaticText18;
		wxStaticText* StaticText1;
		wxStaticText* StaticText10;
		wxStaticText* StaticText16;
		wxButton* Midi_Button5;
		wxSlider* Slider5;
		wxButton* ClearButton;
		wxStaticText* StaticText3;
		wxSlider* Slider11;
		wxSlider* Slider13;
		wxButton* Midi_Button13;
		wxStaticText* StaticText23;
		wxSlider* Slider9;
		wxButton* Midi_Button6;
		wxStaticText* StaticText8;
		wxStaticText* StaticText34;
		wxStaticText* StaticText12;
		wxStaticText* StaticText38;
		wxSlider* Slider16;
		wxStaticText* StaticText7;
		wxButton* Midi_Button1;
		wxButton* Midi_Button16;
		wxStaticText* StaticText40;
		wxButton* Midi_Button15;
		wxSlider* Slider7;
		wxButton* Midi_Button8;
		wxStaticText* StaticText4;
		wxSlider* Slider2;
		wxStaticText* StaticText5;
		wxSlider* Slider14;
		wxSlider* Slider10;
		wxStaticText* StaticText30;
		wxStaticText* StaticText2;
		wxStaticText* StaticText27;
		wxStaticBitmap* StaticBitmap1;
		wxStaticText* StaticText39;
		wxStaticText* StaticText26;
		wxStaticText* StaticText6;
		wxSlider* Slider1;
		wxButton* Midi_Button2;
		wxButton* Midi_Button10;
		wxStaticText* StaticText19;
		wxStaticText* StaticText29;
		wxSlider* Slider12;
		wxSlider* Slider6;
		wxStaticText* StaticText9;
		wxStaticText* StaticText33;
		wxStaticText* StaticText31;
		wxStaticText* StaticText11;
		wxStaticText* StaticText25;
		wxButton* Midi_Button11;
		//*)

	protected:

		//(*Identifiers(MidiControl)
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
		static const long ID_BUTTON1;
		static const long ID_SLIDER1;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_STATICTEXT19;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_BUTTON9;
		static const long ID_BUTTON10;
		static const long ID_BUTTON11;
		static const long ID_BUTTON12;
		static const long ID_BUTTON13;
		static const long ID_BUTTON14;
		static const long ID_BUTTON15;
		static const long ID_BUTTON16;
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
		static const long ID_STATICTEXT30;
		static const long ID_STATICTEXT31;
		static const long ID_STATICTEXT32;
		static const long ID_STATICTEXT33;
		static const long ID_STATICTEXT34;
		static const long ID_STATICTEXT35;
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
		static const long ID_SLIDER13;
		static const long ID_SLIDER14;
		static const long ID_SLIDER15;
		static const long ID_SLIDER16;
		static const long ID_STATICTEXT37;
		static const long ID_STATICTEXT38;
		static const long ID_STATICBITMAP1;
		static const long ID_STATICTEXT39;
		static const long ID_STATICTEXT40;
		static const long ID_STATICTEXT41;
		static const long ID_BUTTON17;
		//*)
		static const long ID_MIDICONTROL;

	private:

        void OnMidiReceive(wxCommandEvent &event);


		//(*Handlers(MidiControl)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton1Click1(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnMidi_Button1Click(wxCommandEvent& event);
		void OnMidi_Button2Click(wxCommandEvent& event);
		void OnMidi_Button3Click(wxCommandEvent& event);
		void OnMidi_Button4Click(wxCommandEvent& event);
		void OnMidi_Button5Click(wxCommandEvent& event);
		void OnMidi_Button6Click(wxCommandEvent& event);
		void OnMidi_Button7Click(wxCommandEvent& event);
		void OnMidi_Button8Click(wxCommandEvent& event);
		void OnMidi_Button9Click(wxCommandEvent& event);
		void OnMidi_Button10Click(wxCommandEvent& event);
		void OnMidi_Button11Click(wxCommandEvent& event);
		void OnMidi_Button12Click(wxCommandEvent& event);
		void OnMidi_Button13Click(wxCommandEvent& event);
		void OnMidi_Button14Click(wxCommandEvent& event);
		void OnMidi_Button15Click(wxCommandEvent& event);
		void OnMidi_Button16Click(wxCommandEvent& event);
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
		void OnSlider13CmdScroll(wxScrollEvent& event);
		void OnSlider14CmdScroll(wxScrollEvent& event);
		void OnSlider15CmdScroll(wxScrollEvent& event);
		void OnSlider16CmdScroll(wxScrollEvent& event);
		void OnButton1Click2(wxCommandEvent& event);
		//*)
		void LoadData(void);
		void SaveData(void);

		DECLARE_EVENT_TABLE()
};

#endif

