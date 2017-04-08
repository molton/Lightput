#ifndef VSXUAUDIOVISUALIZER_H
#define VSXUAUDIOVISUALIZER_H

//(*Headers(VSXuAudioVisualizer)
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/timer.h>
#include <wx/statbmp.h>
//*)

#include <GL/glew.h>

#include <wx/glcanvas.h>

#include <vsx_manager.h>


class VSXuAudioVisualizer: public wxDialog
{
	public:

		VSXuAudioVisualizer(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~VSXuAudioVisualizer();

		//(*Declarations(VSXuAudioVisualizer)
		wxStaticText* StaticText24;
		wxStaticText* StaticText22;
		wxButton* NextButton;
		wxButton* PreviousButton;
		wxCheckBox* CheckBox13;
		wxStaticText* StaticText21;
		wxStaticText* StaticText13;
		wxStaticText* StaticText14;
		wxStaticText* StaticText15;
		wxSlider* Slider4;
		wxSlider* Slider3;
		wxChoice* Choice3;
		wxStaticText* StaticText17;
		wxSlider* Slider8;
		wxCheckBox* CheckBox10;
		wxCheckBox* CheckBox1;
		wxCheckBox* CheckBox6;
		wxCheckBox* CheckBox12;
		wxSlider* Slider15;
		wxChoice* Choice2;
		wxStaticText* StaticText20;
		wxStaticText* StaticText18;
		wxStaticText* StaticText1;
		wxCheckBox* CheckBox16;
		wxStaticText* StaticText10;
		wxStaticText* StaticText16;
		wxTimer Timer1;
		wxButton* StartButton;
		wxSlider* Slider5;
		wxChoice* Choice4;
		wxStaticText* StaticText3;
		wxSlider* Slider11;
		wxSlider* Slider13;
		wxStaticText* StaticText23;
		wxSlider* Slider9;
		wxCheckBox* CheckBox8;
		wxCheckBox* CheckBox4;
		wxChoice* Choice5;
		wxChoice* Choice1;
		wxCheckBox* CheckBox2;
		wxStaticText* StaticText8;
		wxStaticText* StaticText12;
		wxCheckBox* CheckBox7;
		wxSlider* Slider16;
		wxStaticText* StaticText7;
		wxCheckBox* CheckBox15;
		wxButton* FullScreenButton;
		wxSlider* Slider7;
		wxStaticText* StaticText4;
		wxSlider* Slider2;
		wxStaticText* StaticText5;
		wxSlider* Slider14;
		wxSlider* Slider10;
		wxStaticText* StaticText2;
		wxStaticBitmap* StaticBitmap1;
		wxCheckBox* CheckBox3;
		wxStaticText* StaticText26;
		wxCheckBox* CheckBox9;
		wxCheckBox* CheckBox14;
		wxStaticText* StaticText6;
		wxSlider* Slider1;
		wxStaticText* StaticText19;
		wxCheckBox* CheckBox11;
		wxButton* RandomButton;
		wxSlider* Slider12;
		wxSlider* Slider6;
		wxStaticText* StaticText9;
		wxStaticText* StaticText11;
		wxStaticText* StaticText25;
		wxCheckBox* CheckBox5;
		//*)

	protected:

		//(*Identifiers(VSXuAudioVisualizer)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT2;
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
		static const long ID_SLIDER13;
		static const long ID_SLIDER14;
		static const long ID_SLIDER15;
		static const long ID_SLIDER16;
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
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_STATICTEXT19;
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT20;
		static const long ID_STATICTEXT21;
		static const long ID_STATICTEXT22;
		static const long ID_STATICTEXT23;
		static const long ID_CHOICE2;
		static const long ID_CHOICE3;
		static const long ID_CHOICE4;
		static const long ID_STATICTEXT24;
		static const long ID_CHOICE5;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_STATICBITMAP1;
		static const long ID_CHECKBOX1;
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
		static const long ID_STATICTEXT25;
		static const long ID_STATICTEXT26;
		static const long ID_TIMER1;
		//*)

	private:

        void VSXuStartButtonHandler(void);
        void VSXuStopButtonHandler(void);

        void LoadData(void);
        void SaveData(void);

		//(*Handlers(VSXuAudioVisualizer)
		void OnStartButtonClick(wxCommandEvent& event);
		void OnTestButtonClick(wxCommandEvent& event);
		void OnPreviousButtonClick(wxCommandEvent& event);
		void OnNextButtonClick(wxCommandEvent& event);
		void OnStopButtonClick(wxCommandEvent& event);
		void OnTimer1Trigger(wxTimerEvent& event);
		void OnChoice1Select(wxCommandEvent& event);
		void OnChoice5Select(wxCommandEvent& event);
		void OnTestButtonClick1(wxCommandEvent& event);
		void OnSlider17CmdScroll(wxScrollEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnChoice5Select1(wxCommandEvent& event);
		void OnRandomButtonClick(wxCommandEvent& event);
		void OnTestButtonClick2(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnChoice5Select2(wxCommandEvent& event);
		void OnLeftDClick(wxMouseEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnSetFocus(wxFocusEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};



class VSXuRenderer:  public wxGLCanvas
{

public:


    vsx_manager_abs *m_manager;

    VSXuRenderer(wxGLCanvas *parent);
   //this causes vtable error ~VSXuRenderer();

    bool m_isRunning, m_doResize, m_isActive;
    int m_width,m_height;
    float m_soundData[512];
    int m_previousError;

    //void PaintIt(wxPaintEvent& event);
    void run();
    void drawSplashScreen();
    bool processErrors();


    void deactivate(){ m_isActive = false; }
    void activate(){ m_isActive = true; }
    void stop(){ m_isRunning = false;}

    void nextVisual(){ if(m_manager)m_manager->next_visual(); }
    void prevVisual(){ if(m_manager)m_manager->prev_visual(); }

    bool getRandomizerStatus(){
      if(m_manager)
        return m_manager->get_randomizer_status();
      return false;
    }
    void setRandomizer(bool value){ if(m_manager)m_manager->set_randomizer(value); }

    float getFXLevel(){
      if(m_manager)
        return m_manager->get_fx_level();
      return -1;
    }
    void increaseFXLevel(){ if(m_manager)m_manager->inc_fx_level(); }
    void decreaseFXLevel(){ if(m_manager)m_manager->dec_fx_level(); }

    float getSpeed(){
      if(m_manager)
        return m_manager->get_speed();
      return -1;
    }
    void increaseSpeed(){ if(m_manager)m_manager->inc_speed();}
    void decreaseSpeed(){ if(m_manager)m_manager->dec_speed();}

    wxArrayString getVisuals();

    void resize(int w, int h);
    void injectSound(float soundData[]);




protected:


private:


        //DECLARE_EVENT_TABLE()
};

class VSXuTimer : public wxTimer
{

    protected:

    void Notify();


};


#endif
