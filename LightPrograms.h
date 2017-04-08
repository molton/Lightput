#ifndef LIGHTPROGRAMS_H
#define LIGHTPROGRAMS_H

//(*Headers(LightPrograms)
#include <wx/dialog.h>
#include <wx/button.h>
//*)

class LightPrograms: public wxDialog
{
	public:

		LightPrograms(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~LightPrograms();

		//(*Declarations(LightPrograms)
		wxButton* LightScriptsButton;
		wxButton* ActualVSXuButton;
		wxButton* VSXuButton;
		wxButton* CloseButton;
		wxButton* LightSequencerButton;
		wxButton* LightAlarmClockButton;
		wxButton* MidiButton;
		wxButton* H24TimerButton;
		//*)

	protected:

		//(*Identifiers(LightPrograms)
		static const long ID_BUTTON1;
		static const long ID_BUTTON4;
		static const long ID_BUTTON2;
		static const long ID_BUTTON5;
		static const long ID_BUTTON7;
		static const long ID_BUTTON3;
		static const long ID_BUTTON8;
		static const long ID_BUTTON6;
		//*)

	private:

		//(*Handlers(LightPrograms)
		void OnButton1Click(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnButton4Click(wxCommandEvent& event);
		void OnButton8Click(wxCommandEvent& event);
		void OnButton5Click(wxCommandEvent& event);
		void OnButton3Click(wxCommandEvent& event);
		void OnButtonnotyetnamedClick(wxCommandEvent& event);
		void OnMidiButtonClick(wxCommandEvent& event);
		void OnMidiButtonClick1(wxCommandEvent& event);
		void OnMouseEnter(wxMouseEvent& event);
		//void OnTimer1Trigger(wxTimerEvent& event);
		void OnActualVSXuButtonClick(wxCommandEvent& event);
		//*)

        void EnableButtons(void);
        void DisableButtons(void);

		DECLARE_EVENT_TABLE()
};

#endif
