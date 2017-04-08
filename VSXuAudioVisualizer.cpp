#include "VSXuAudioVisualizer.h"

//(*InternalHeaders(VSXuAudioVisualizer)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
#include <wx/bitmap.h>
#include <wx/image.h>
//*)
#include <wx/image.h>
#include <wx/frame.h>
#include <wx/msgdlg.h>
#include <wx/glcanvas.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/textfile.h>

//testing variables
float testlevelfloat;
int testlevel;
int ntest;
int threadtest;


//global pointer identifiers
wxFrame *vsxu_frame;
wxGLCanvas *vsxu_canvas;
VSXuRenderer *vsxu_renderer;
int *attributes = new int[1];
wxButton *LeaveFullScreenButton;
wxTimer *timer;


//VSXu output analyzing variables
GLubyte pixels[1920][1080][3];

//external global control variables
extern bool VSXuInitialize;
extern bool hasVSXurunonce;
extern bool isprofilemode;
extern bool isVSXumode;

//global control variables
int CheckIsRunning;
bool VSXuisstarted;
bool ispick_visual;
bool fullscreen;
int vsxu_width;
int vsxu_height;
bool calculatethistime;



unsigned short int VSXu_Red_Channel;
unsigned short int VSXu_Green_Channel;
unsigned short int VSXu_Blue_Channel;
unsigned short int VSXu_RGB_Channel;

unsigned long int VSXu_Red_Channel_add;
unsigned long int VSXu_Green_Channel_add;
unsigned long int VSXu_Blue_Channel_add;

//variables for VSXu audio visualization
extern unsigned short int Channel_1_VSXu;
extern unsigned short int Channel_2_VSXu;
extern unsigned short int Channel_3_VSXu;
extern unsigned short int Channel_4_VSXu;
extern unsigned short int Channel_5_VSXu;
extern unsigned short int Channel_6_VSXu;
extern unsigned short int Channel_7_VSXu;
extern unsigned short int Channel_8_VSXu;
extern unsigned short int Channel_9_VSXu;
extern unsigned short int Channel_10_VSXu;
extern unsigned short int Channel_11_VSXu;
extern unsigned short int Channel_12_VSXu;
extern unsigned short int Channel_13_VSXu;
extern unsigned short int Channel_14_VSXu;
extern unsigned short int Channel_15_VSXu;
extern unsigned short int Channel_16_VSXu;

extern unsigned short int VSXu_ProfileChannel_1;
extern unsigned short int VSXu_ProfileChannel_2;
extern unsigned short int VSXu_ProfileChannel_3;
extern unsigned short int VSXu_ProfileChannel_4;
extern unsigned short int VSXu_ProfileChannel_5;
extern unsigned short int VSXu_ProfileChannel_6;
extern unsigned short int VSXu_ProfileChannel_7;
extern unsigned short int VSXu_ProfileChannel_8;
extern unsigned short int VSXu_ProfileChannel_9;
extern unsigned short int VSXu_ProfileChannel_10;
extern unsigned short int VSXu_ProfileChannel_11;
extern unsigned short int VSXu_ProfileChannel_12;
extern unsigned short int VSXu_ProfileChannel_13;
extern unsigned short int VSXu_ProfileChannel_14;
extern unsigned short int VSXu_ProfileChannel_15;
extern unsigned short int VSXu_ProfileChannel_16;

//(*IdInit(VSXuAudioVisualizer)
const long VSXuAudioVisualizer::ID_STATICTEXT1 = wxNewId();
const long VSXuAudioVisualizer::ID_BUTTON1 = wxNewId();
const long VSXuAudioVisualizer::ID_BUTTON2 = wxNewId();
const long VSXuAudioVisualizer::ID_BUTTON3 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT2 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER1 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER2 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER3 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER4 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER5 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER6 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER7 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER8 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER9 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER10 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER11 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER12 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER13 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER14 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER15 = wxNewId();
const long VSXuAudioVisualizer::ID_SLIDER16 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT3 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT4 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT5 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT6 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT7 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT8 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT9 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT10 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT11 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT12 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT13 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT14 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT15 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT16 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT17 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT18 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT19 = wxNewId();
const long VSXuAudioVisualizer::ID_CHOICE1 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT20 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT21 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT22 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT23 = wxNewId();
const long VSXuAudioVisualizer::ID_CHOICE2 = wxNewId();
const long VSXuAudioVisualizer::ID_CHOICE3 = wxNewId();
const long VSXuAudioVisualizer::ID_CHOICE4 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT24 = wxNewId();
const long VSXuAudioVisualizer::ID_CHOICE5 = wxNewId();
const long VSXuAudioVisualizer::ID_BUTTON4 = wxNewId();
const long VSXuAudioVisualizer::ID_BUTTON5 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICBITMAP1 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX1 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX2 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX3 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX4 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX5 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX6 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX7 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX8 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX9 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX10 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX11 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX12 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX13 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX14 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX15 = wxNewId();
const long VSXuAudioVisualizer::ID_CHECKBOX16 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT25 = wxNewId();
const long VSXuAudioVisualizer::ID_STATICTEXT26 = wxNewId();
const long VSXuAudioVisualizer::ID_TIMER1 = wxNewId();
//*)

wxString   vsxufilename;

BEGIN_EVENT_TABLE(VSXuAudioVisualizer,wxDialog)
	//(*EventTable(VSXuAudioVisualizer)
	//*)
END_EVENT_TABLE()

//BEGIN_EVENT_TABLE(VSXuRenderer,wxGLCanvas)

//END_EVENT_TABLE()


VSXuAudioVisualizer::VSXuAudioVisualizer(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{

    attributes[0] = int(WX_GL_DOUBLEBUFFER);
    attributes[1] = WX_GL_RGBA;

    hasVSXurunonce = false;
    VSXuInitialize = true;
    fullscreen = false;

    vsxu_width = 640;//1366;
    vsxu_height = 480;//768;

    vsxufilename = wxT("./light_programs/vsxu.lightput");

	//(*Initialize(VSXuAudioVisualizer)
	Create(parent, wxID_ANY, _("Vovoid VSXu -> Lightput 0.2"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(573,552));
	SetFocus();
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("VSXu Audio Visualizer -> Lightput"), wxPoint(16,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(16,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	StartButton = new wxButton(this, ID_BUTTON1, _("Start VSXu"), wxPoint(168,504), wxSize(176,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont StartButtonFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StartButton->SetFont(StartButtonFont);
	NextButton = new wxButton(this, ID_BUTTON2, _("Next Visual"), wxPoint(304,456), wxSize(112,29), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	NextButton->Disable();
	wxFont NextButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	NextButton->SetFont(NextButtonFont);
	PreviousButton = new wxButton(this, ID_BUTTON3, _("Previous Visual"), wxPoint(168,456), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	PreviousButton->Disable();
	wxFont PreviousButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	PreviousButton->SetFont(PreviousButtonFont);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Select which channels change with the VSXu audio visuals before \nstarting.  Exempt channels stay on whatever the profile was set as\nand are exempt from this light program. Change the visuals with the \nnext and previous visual buttons.  Some visuals may not work\ncorrectly or well with Lightput. "), wxPoint(184,360), wxSize(352,26), 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	Slider1 = new wxSlider(this, ID_SLIDER1, 127, 0, 255, wxPoint(40,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER1"));
	Slider2 = new wxSlider(this, ID_SLIDER2, 127, 0, 255, wxPoint(72,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER2"));
	Slider3 = new wxSlider(this, ID_SLIDER3, 127, 0, 255, wxPoint(104,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER3"));
	Slider4 = new wxSlider(this, ID_SLIDER4, 127, 0, 255, wxPoint(136,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER4"));
	Slider5 = new wxSlider(this, ID_SLIDER5, 127, 0, 255, wxPoint(168,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER5"));
	Slider6 = new wxSlider(this, ID_SLIDER6, 127, 0, 255, wxPoint(200,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER6"));
	Slider7 = new wxSlider(this, ID_SLIDER7, 127, 0, 255, wxPoint(232,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER7"));
	Slider8 = new wxSlider(this, ID_SLIDER8, 127, 0, 255, wxPoint(264,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER8"));
	Slider9 = new wxSlider(this, ID_SLIDER9, 127, 0, 255, wxPoint(296,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER9"));
	Slider10 = new wxSlider(this, ID_SLIDER10, 127, 0, 255, wxPoint(328,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER10"));
	Slider11 = new wxSlider(this, ID_SLIDER11, 127, 0, 255, wxPoint(360,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER11"));
	Slider12 = new wxSlider(this, ID_SLIDER12, 127, 0, 255, wxPoint(392,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER12"));
	Slider13 = new wxSlider(this, ID_SLIDER13, 127, 0, 255, wxPoint(424,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER13"));
	Slider14 = new wxSlider(this, ID_SLIDER14, 127, 0, 255, wxPoint(456,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER14"));
	Slider15 = new wxSlider(this, ID_SLIDER15, 127, 0, 255, wxPoint(488,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER15"));
	Slider16 = new wxSlider(this, ID_SLIDER16, 127, 0, 255, wxPoint(520,80), wxSize(27,104), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER16"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Channel:"), wxPoint(16,48), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("1"), wxPoint(48,64), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	wxFont StaticText4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("2"), wxPoint(80,64), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	wxFont StaticText5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText5->SetFont(StaticText5Font);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("3"), wxPoint(112,64), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	wxFont StaticText6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText6->SetFont(StaticText6Font);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("4"), wxPoint(144,64), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	wxFont StaticText7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText7->SetFont(StaticText7Font);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("5"), wxPoint(176,64), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	wxFont StaticText8Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText8->SetFont(StaticText8Font);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("6"), wxPoint(208,64), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	wxFont StaticText9Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText9->SetFont(StaticText9Font);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("7"), wxPoint(240,64), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	wxFont StaticText10Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText10->SetFont(StaticText10Font);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("8"), wxPoint(272,64), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	wxFont StaticText11Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText11->SetFont(StaticText11Font);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("9"), wxPoint(304,64), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	wxFont StaticText12Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText12->SetFont(StaticText12Font);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("10"), wxPoint(336,64), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	wxFont StaticText13Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText13->SetFont(StaticText13Font);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("11"), wxPoint(368,64), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	wxFont StaticText14Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText14->SetFont(StaticText14Font);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("12"), wxPoint(400,64), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	wxFont StaticText15Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText15->SetFont(StaticText15Font);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("13"), wxPoint(432,64), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	wxFont StaticText16Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText16->SetFont(StaticText16Font);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("14"), wxPoint(464,64), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	wxFont StaticText17Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText17->SetFont(StaticText17Font);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("15"), wxPoint(496,64), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	wxFont StaticText18Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText18->SetFont(StaticText18Font);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("16"), wxPoint(528,64), wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	wxFont StaticText19Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText19->SetFont(StaticText19Font);
	Choice1 = new wxChoice(this, ID_CHOICE1, wxPoint(176,208), wxSize(112,29), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice1->Append(_("None"));
	Choice1->SetSelection( Choice1->Append(_("Channel 1")) );
	Choice1->Append(_("Channel 2"));
	Choice1->Append(_("Channel 3"));
	Choice1->Append(_("Channel 4"));
	Choice1->Append(_("Channel 5"));
	Choice1->Append(_("Channel 6"));
	Choice1->Append(_("Channel 7"));
	Choice1->Append(_("Channel 8"));
	Choice1->Append(_("Channel 9"));
	Choice1->Append(_("Channel 10"));
	Choice1->Append(_("Channel 11"));
	Choice1->Append(_("Channel 12"));
	Choice1->Append(_("Channel 13"));
	Choice1->Append(_("Channel 14"));
	Choice1->Append(_("Channel 15"));
	Choice1->Append(_("Channel 16"));
	wxFont Choice1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Choice1->SetFont(Choice1Font);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("VSXu Red -> Lighput"), wxPoint(56,216), wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	wxFont StaticText20Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText20->SetFont(StaticText20Font);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("VSXu Green -> Lighput"), wxPoint(40,256), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	wxFont StaticText21Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText21->SetFont(StaticText21Font);
	StaticText22 = new wxStaticText(this, ID_STATICTEXT22, _("VSXu Blue -> Lighput"), wxPoint(320,216), wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	wxFont StaticText22Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText22->SetFont(StaticText22Font);
	StaticText23 = new wxStaticText(this, ID_STATICTEXT23, _("VSXu RGB -> Lighput"), wxPoint(328,256), wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	wxFont StaticText23Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText23->SetFont(StaticText23Font);
	Choice2 = new wxChoice(this, ID_CHOICE2, wxPoint(176,248), wxSize(112,29), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	Choice2->Append(_("None"));
	Choice2->Append(_("Channel 1"));
	Choice2->SetSelection( Choice2->Append(_("Channel 2")) );
	Choice2->Append(_("Channel 3"));
	Choice2->Append(_("Channel 4"));
	Choice2->Append(_("Channel 5"));
	Choice2->Append(_("Channel 6"));
	Choice2->Append(_("Channel 7"));
	Choice2->Append(_("Channel 8"));
	Choice2->Append(_("Channel 9"));
	Choice2->Append(_("Channel 10"));
	Choice2->Append(_("Channel 11"));
	Choice2->Append(_("Channel 12"));
	Choice2->Append(_("Channel 13"));
	Choice2->Append(_("Channel 14"));
	Choice2->Append(_("Channel 15"));
	Choice2->Append(_("Channel 16"));
	wxFont Choice2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Choice2->SetFont(Choice2Font);
	Choice3 = new wxChoice(this, ID_CHOICE3, wxPoint(448,208), wxSize(112,29), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
	Choice3->Append(_("None"));
	Choice3->Append(_("Channel 1"));
	Choice3->Append(_("Channel 2"));
	Choice3->SetSelection( Choice3->Append(_("Channel 3")) );
	Choice3->Append(_("Channel 4"));
	Choice3->Append(_("Channel 5"));
	Choice3->Append(_("Channel 6"));
	Choice3->Append(_("Channel 7"));
	Choice3->Append(_("Channel 8"));
	Choice3->Append(_("Channel 9"));
	Choice3->Append(_("Channel 10"));
	Choice3->Append(_("Channel 11"));
	Choice3->Append(_("Channel 12"));
	Choice3->Append(_("Channel 13"));
	Choice3->Append(_("Channel 14"));
	Choice3->Append(_("Channel 15"));
	Choice3->Append(_("Channel 16"));
	wxFont Choice3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Choice3->SetFont(Choice3Font);
	Choice4 = new wxChoice(this, ID_CHOICE4, wxPoint(448,248), wxSize(112,29), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
	Choice4->SetSelection( Choice4->Append(_("None")) );
	Choice4->Append(_("Channel 1"));
	Choice4->Append(_("Channel 2"));
	Choice4->Append(_("Channel 3"));
	Choice4->Append(_("Channel 4"));
	Choice4->Append(_("Channel 5"));
	Choice4->Append(_("Channel 6"));
	Choice4->Append(_("Channel 7"));
	Choice4->Append(_("Channel 8"));
	Choice4->Append(_("Channel 9"));
	Choice4->Append(_("Channel 10"));
	Choice4->Append(_("Channel 11"));
	Choice4->Append(_("Channel 12"));
	Choice4->Append(_("Channel 13"));
	Choice4->Append(_("Channel 14"));
	Choice4->Append(_("Channel 15"));
	Choice4->Append(_("Channel 16"));
	wxFont Choice4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Choice4->SetFont(Choice4Font);
	StaticText24 = new wxStaticText(this, ID_STATICTEXT24, _("VSXu Color Bias (Lower number, brighter output)"), wxPoint(176,292), wxSize(80,13), 0, _T("ID_STATICTEXT24"));
	wxFont StaticText24Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText24->SetFont(StaticText24Font);
	Choice5 = new wxChoice(this, ID_CHOICE5, wxPoint(448,288), wxSize(112,24), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
	Choice5->Append(_("0"));
	Choice5->Append(_("1"));
	Choice5->Append(_("2"));
	Choice5->Append(_("3"));
	Choice5->Append(_("4"));
	Choice5->Append(_("5"));
	Choice5->Append(_("6"));
	Choice5->Append(_("7"));
	Choice5->Append(_("8"));
	Choice5->Append(_("9"));
	Choice5->Append(_("10"));
	Choice5->Append(_("11"));
	Choice5->Append(_("12"));
	Choice5->Append(_("13"));
	Choice5->Append(_("14"));
	Choice5->Append(_("15"));
	Choice5->Append(_("16"));
	Choice5->Append(_("17"));
	Choice5->Append(_("18"));
	Choice5->Append(_("19"));
	Choice5->SetSelection( Choice5->Append(_("20")) );
	Choice5->Append(_("21"));
	Choice5->Append(_("22"));
	Choice5->Append(_("23"));
	Choice5->Append(_("24"));
	Choice5->Append(_("25"));
	Choice5->Append(_("26"));
	Choice5->Append(_("27"));
	Choice5->Append(_("28"));
	Choice5->Append(_("29"));
	Choice5->Append(_("30"));
	Choice5->Append(_("31"));
	Choice5->Append(_("32"));
	Choice5->Append(_("33"));
	Choice5->Append(_("34"));
	Choice5->Append(_("35"));
	Choice5->Append(_("36"));
	Choice5->Append(_("37"));
	Choice5->Append(_("38"));
	Choice5->Append(_("39"));
	Choice5->Append(_("40"));
	Choice5->Append(_("41"));
	Choice5->Append(_("42"));
	Choice5->Append(_("43"));
	Choice5->Append(_("44"));
	Choice5->Append(_("45"));
	Choice5->Append(_("46"));
	Choice5->Append(_("47"));
	Choice5->Append(_("48"));
	Choice5->Append(_("49"));
	Choice5->Append(_("50"));
	Choice5->Append(_("51"));
	Choice5->Append(_("52"));
	Choice5->Append(_("53"));
	Choice5->Append(_("54"));
	Choice5->Append(_("55"));
	Choice5->Append(_("56"));
	Choice5->Append(_("57"));
	Choice5->Append(_("58"));
	Choice5->Append(_("59"));
	Choice5->Append(_("60"));
	Choice5->Append(_("61"));
	Choice5->Append(_("62"));
	Choice5->Append(_("63"));
	Choice5->Append(_("64"));
	Choice5->Append(_("65"));
	Choice5->Append(_("66"));
	Choice5->Append(_("67"));
	Choice5->Append(_("68"));
	Choice5->Append(_("69"));
	Choice5->Append(_("70"));
	Choice5->Append(_("71"));
	Choice5->Append(_("72"));
	Choice5->Append(_("73"));
	Choice5->Append(_("74"));
	Choice5->Append(_("75"));
	Choice5->Append(_("76"));
	Choice5->Append(_("77"));
	Choice5->Append(_("78"));
	Choice5->Append(_("79"));
	Choice5->Append(_("80"));
	Choice5->Append(_("81"));
	Choice5->Append(_("82"));
	Choice5->Append(_("83"));
	Choice5->Append(_("84"));
	Choice5->Append(_("85"));
	Choice5->Append(_("86"));
	Choice5->Append(_("87"));
	Choice5->Append(_("88"));
	Choice5->Append(_("89"));
	Choice5->Append(_("90"));
	Choice5->Append(_("91"));
	Choice5->Append(_("92"));
	Choice5->Append(_("93"));
	Choice5->Append(_("94"));
	Choice5->Append(_("95"));
	Choice5->Append(_("96"));
	Choice5->Append(_("97"));
	Choice5->Append(_("98"));
	Choice5->Append(_("99"));
	Choice5->Append(_("100"));
	wxFont Choice5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Choice5->SetFont(Choice5Font);
	RandomButton = new wxButton(this, ID_BUTTON4, _("Random Visual"), wxPoint(440,456), wxSize(112,29), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	RandomButton->Disable();
	wxFont RandomButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	RandomButton->SetFont(RandomButtonFont);
	FullScreenButton = new wxButton(this, ID_BUTTON5, _("Full Screen"), wxPoint(360,504), wxSize(192,29), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FullScreenButton->Disable();
	wxFont FullScreenButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	FullScreenButton->SetFont(FullScreenButtonFont);
	StaticBitmap1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxBitmap(wxImage(_T("graphics/vsxu.bmp"))), wxPoint(8,382), wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
	CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, wxEmptyString, wxPoint(44,184), wxSize(24,24), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox1->SetValue(false);
	CheckBox2 = new wxCheckBox(this, ID_CHECKBOX2, wxEmptyString, wxPoint(76,184), wxSize(24,24), 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBox2->SetValue(false);
	CheckBox3 = new wxCheckBox(this, ID_CHECKBOX3, wxEmptyString, wxPoint(108,184), wxSize(24,24), 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	CheckBox3->SetValue(false);
	CheckBox4 = new wxCheckBox(this, ID_CHECKBOX4, _("Label"), wxPoint(140,184), wxSize(24,24), 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	CheckBox4->SetValue(false);
	CheckBox5 = new wxCheckBox(this, ID_CHECKBOX5, wxEmptyString, wxPoint(170,184), wxSize(24,24), 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	CheckBox5->SetValue(false);
	CheckBox6 = new wxCheckBox(this, ID_CHECKBOX6, wxEmptyString, wxPoint(204,184), wxSize(24,24), 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	CheckBox6->SetValue(false);
	CheckBox7 = new wxCheckBox(this, ID_CHECKBOX7, wxEmptyString, wxPoint(236,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	CheckBox7->SetValue(false);
	CheckBox8 = new wxCheckBox(this, ID_CHECKBOX8, wxEmptyString, wxPoint(268,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	CheckBox8->SetValue(false);
	CheckBox9 = new wxCheckBox(this, ID_CHECKBOX9, wxEmptyString, wxPoint(300,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	CheckBox9->SetValue(false);
	CheckBox10 = new wxCheckBox(this, ID_CHECKBOX10, wxEmptyString, wxPoint(332,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	CheckBox10->SetValue(false);
	CheckBox11 = new wxCheckBox(this, ID_CHECKBOX11, wxEmptyString, wxPoint(364,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	CheckBox11->SetValue(false);
	CheckBox12 = new wxCheckBox(this, ID_CHECKBOX12, wxEmptyString, wxPoint(396,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	CheckBox12->SetValue(false);
	CheckBox13 = new wxCheckBox(this, ID_CHECKBOX13, wxEmptyString, wxPoint(428,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	CheckBox13->SetValue(false);
	CheckBox14 = new wxCheckBox(this, ID_CHECKBOX14, wxEmptyString, wxPoint(460,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	CheckBox14->SetValue(false);
	CheckBox15 = new wxCheckBox(this, ID_CHECKBOX15, wxEmptyString, wxPoint(492,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	CheckBox15->SetValue(false);
	CheckBox16 = new wxCheckBox(this, ID_CHECKBOX16, wxEmptyString, wxPoint(524,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
	CheckBox16->SetValue(false);
	StaticText25 = new wxStaticText(this, ID_STATICTEXT25, _("Exempt"), wxPoint(0,192), wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	wxFont StaticText25Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText25->SetFont(StaticText25Font);
	StaticText26 = new wxStaticText(this, ID_STATICTEXT26, _("notes: VSXu takes 20-30 seconds to load and Lightput and VSXu will not respond while VSXu is\nloading. Use Alt-tab to stop the visualizer after going into fullscreen mode.\nIf you have audio issues using Lightput->VSXu, try starting VSXu from within lightput before \nopening the audio application."), wxPoint(16,320), wxSize(544,64), 0, _T("ID_STATICTEXT26"));
	wxFont StaticText26Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText26->SetFont(StaticText26Font);
	Timer1.SetOwner(this, ID_TIMER1);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&VSXuAudioVisualizer::OnStartButtonClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&VSXuAudioVisualizer::OnNextButtonClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&VSXuAudioVisualizer::OnPreviousButtonClick);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&VSXuAudioVisualizer::OnChoice1Select);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&VSXuAudioVisualizer::OnRandomButtonClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&VSXuAudioVisualizer::OnButton1Click);
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&VSXuAudioVisualizer::OnTimer1Trigger);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&VSXuAudioVisualizer::OnClose);
	//*)

    LoadData();


    isprofilemode = false;
    VSXuisstarted = false;
}

VSXuAudioVisualizer::~VSXuAudioVisualizer()
{
	//(*Destroy(VSXuAudioVisualizer)
	//*)
}

void VSXuAudioVisualizer::VSXuStartButtonHandler(void)
{
    //gui stuff
    //StartButton->Enable(false);
    //TestButton->Enable(true);
    NextButton->Enable(true);
    PreviousButton->Enable(true);
    RandomButton->Enable(true);
    FullScreenButton->Enable(true);
    //ToggleRandomButton->Enable(true);
    //StartButton->Enable(false);
    StartButton->SetLabel(wxT("Stop VSXu"));
    Choice1->Enable(false);
    Choice2->Enable(false);
    Choice3->Enable(false);
    Choice4->Enable(false);
    Choice5->Enable(false);
    hasVSXurunonce = true;
}


void VSXuAudioVisualizer::VSXuStopButtonHandler(void)
{
    //gui stuff
    //StartButton->Enable(true);
    //TestButton->Enable(false);
    FullScreenButton->Enable(false);
    NextButton->Enable(false);
    RandomButton->Enable(false);
    PreviousButton->Enable(false);
   // ToggleRandomButton->Enable(false);
    StartButton->SetLabel(wxT("Start VSXu"));
    Choice1->Enable(true);
    Choice2->Enable(true);
    Choice3->Enable(true);
    Choice4->Enable(true);
    Choice5->Enable(true);
}

/** VSXuRenderer code */


VSXuRenderer::VSXuRenderer(wxGLCanvas* parent):
  wxGLCanvas(parent, wxID_ANY,  wxPoint(-100,-100), wxDefaultSize, 0, wxT("GLCanvas")),
  m_manager(0),
  m_isRunning(true),
  m_doResize(true),
  m_isActive(true),
  m_width(640),
  m_height(480),
  m_previousError(0)
{
  vsxu_canvas = parent;
}

wxArrayString VSXuRenderer::getVisuals()
{
    wxArrayString result;
    if(!m_manager)
      return result;


    std::vector<std::string> visuals = m_manager->get_visual_filenames();
    for(std::vector<std::string>::iterator it = visuals.begin(); it < visuals.end() ; it++){

        std::string stdconv = *it;
        wxString wxt_conv (stdconv.c_str(), wxConvUTF8);
        wxt_conv.replace(wxT(".vsx"),wxT(""),false);
        result.Add(wxt_conv);
    }
    return result;
}



void VSXuRenderer::resize(int w, int h)
{
    m_width = w;
    m_height = h;
    m_doResize = true;
}

void VSXuRenderer::injectSound(float soundData[])
{
  /*uncomment for manual sound injection
  for (int i = 0; i < 512; i++){
      //Making a local copy of the sound data for updating the sound data
      m_soundData[i] = soundData[i];
  }
  manager->set_sound_wave(m_soundData);
  */
}

void VSXuRenderer::drawSplashScreen()
{
    //QImage splash = QGLWidget::convertToGLFormat(QImage(":luna.png"));

    wxImage* splash = new wxImage( wxT("./luna.png") );

    int edge = m_width > m_height? m_height:m_width;
    //splash->GetAlpha();
    //splash->ConvertAlphaToMask();

    glEnable(GL_TEXTURE_2D);
    GLuint texture_splash;
    glGenTextures(1,&texture_splash);
    glBindTexture(GL_TEXTURE_2D, texture_splash);
    glTexImage2D(GL_TEXTURE_2D, 0, 3 , splash->GetWidth(), splash->GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,splash->GetData());

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport((m_width-edge)/2, (m_height-edge)/2, edge, edge);

    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-0.5,-0.5,0);
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2f(0.0, 0.0);
      glVertex2f(0.0,0.0);

      glTexCoord2f(0.0, 1.0);
      glVertex2f(0.0,1.0);

      glTexCoord2f(1.0, 0.0);
      glVertex2f(1.0,0.0);

      glTexCoord2f(1.0, 1.0);
      glVertex2f(1.0,1.0);

    glEnd();
    vsxu_canvas->SetCurrent();

   // m_widget->swapBuffers();
}

bool VSXuRenderer::processErrors()
{

    int error = glGetError();
    if(error){
	if(m_previousError != error){
	  m_previousError = error;
	  //qDebug()<<"Error :"<<error;
	  if(m_manager){}
	      //qDebug()<<"Visual :"<<m_manager->get_meta_visual_filename().c_str();
	  //qDebug()<<"Widget is valid?"<<m_widget->isValid();
	}
	return true;
    }
    m_previousError = 0;
    return false;
    //m_manager->toggle_randomizer();
    m_manager->set_randomizer(false);

}

void VSXuRenderer::run()
{
    //if (CheckIsRunning < 10) CheckIsRunning++;

    if (VSXuInitialize)
    {
        ispick_visual = true;
        vsxu_canvas->SetCurrent();
        //vsxu_canvas->wxBufferedDC(false);
        //vsxu_canvas->wxPaintDC(this);
       // wxPaintDC(this);


        glEnable(GL_BLEND);
        glEnable(GL_POLYGON_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // A nice splash screen till VSXu actually loads itself
        //drawSplashScreen();

        //processErrors();


        m_manager = manager_factory();

        m_manager->init(0,"pulseaudio");
        //for manual sound injection, use: manager->init( path.c_str() , "media_player");

        //m_manager->add_visual_path("/home/mike/visuals_player");

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        VSXuInitialize = false;

        m_manager->set_randomizer(false);
       // m_manager->toggle_randomizer(); used to have to be here, now it works like you'd expect it too!

        //Lightput control
        isVSXumode = true;


    }


    if (m_doResize){

        glViewport(0, 0, vsxu_width, vsxu_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // set origin to bottom left corner
        gluOrtho2D(0, vsxu_width, 0, vsxu_height);

        m_doResize = false;

    }

    if (m_manager) {

        glFinish();

        m_manager->render();

        vsxu_canvas->SwapBuffers();

        if (calculatethistime) {
            glReadPixels(0, 0, vsxu_width, vsxu_height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            calculatethistime = false;
        }
        else calculatethistime = true;

    }

    if (ispick_visual)
    {
        //27 is starzoomer on 0.4.1 setup
        vsxu_renderer->m_manager->pick_visual(27);
        ispick_visual = false;
    }


}



void VSXuTimer::Notify()
{
    vsxu_renderer->run();
}

void VSXuAudioVisualizer::OnStartButtonClick(wxCommandEvent& event)
{
    if (!VSXuisstarted)VSXuStartButtonHandler();
    else VSXuStopButtonHandler();



    if (VSXuInitialize) {
        vsxu_frame = new wxFrame((wxFrame *)NULL, 1,  wxT("Vovoid VSXu"), wxPoint(520,50), wxSize(vsxu_width,vsxu_height),wxSYSTEM_MENU | wxCAPTION );
        vsxu_canvas = new wxGLCanvas (vsxu_frame, wxID_ANY,  wxDefaultPosition, wxDefaultSize, 1, wxT("GLCanvas"),attributes);
        vsxu_renderer = new VSXuRenderer(vsxu_canvas);
        timer = new VSXuTimer();
    }
    if (!VSXuisstarted) {
         if (!vsxu_renderer->m_manager) {

         };

        Timer1.Start(90,false);

        VSXuisstarted = true;
        timer->Start(45,false);//30
        //this restarts vsxu if it was closed and reopened
        if (vsxu_renderer->m_manager) vsxu_renderer->m_manager->start();
        vsxu_frame->Show(true);
    }
    else
    {
        //vsxu_renderer->m_manager->stop();
        vsxu_renderer->m_manager->stop();
        vsxu_frame->Show(false);
        //vsxu_frame->ShowFullscreen(TRUE);

        //timer->Stop();
        Timer1.Stop();
        //vsxu_renderer->deactivate();
        VSXuisstarted = false;
    }

}

void VSXuAudioVisualizer::OnRandomButtonClick(wxCommandEvent& event)
{
    vsxu_renderer->m_manager->pick_random_visual();
}


void VSXuAudioVisualizer::OnPreviousButtonClick(wxCommandEvent& event)
{
    vsxu_renderer->m_manager->prev_visual();
}

void VSXuAudioVisualizer::OnNextButtonClick(wxCommandEvent& event)
{
    vsxu_renderer->m_manager->next_visual();
}

void VSXuAudioVisualizer::OnStopButtonClick(wxCommandEvent& event)
{
    vsxu_renderer->m_manager->stop();
    vsxu_renderer->deactivate();
    //vsxu_renderer->Destroy();
    //vsxu_canvas->Destroy();
    //vsxu_frame->Destroy();
    vsxu_frame->Show(false);
    VSXuStopButtonHandler();
}

void VSXuAudioVisualizer::OnTimer1Trigger(wxTimerEvent& event)
{
    float divisor;
    int Red_divide_count = 1;
    int Green_divide_count = 1;
    int Blue_divide_count = 1;
    int RGB_divide_count = 0;
    //int Red_on;
    //int Red_off;
    int total_pixels;
    unsigned int countX;
    unsigned int countY;
    int bias;

    VSXu_Red_Channel_add = 0;
    VSXu_Green_Channel_add = 0;
    VSXu_Blue_Channel_add = 0;

//    VSXu_Red_Channel_off_add = 0;
  //  VSXu_Green_Channel_off_add = 0;
   // VSXu_Blue_Channel_off_add = 0;

    bias = Choice5->GetSelection();

/*old style detection
//this code here gets the average of all the pixels, excluding blank or biased out pixels
    for (countX = 1; countX < vsxu_width; countX++){
        for (countY = 1; countY < vsxu_height; countY++){
            if (pixels [countX] [countY] [0] > bias) {
                VSXu_Red_Channel_add = VSXu_Red_Channel_add + pixels [countX] [countY] [0];
                Red_divide_count++;
            }
            if (pixels [countX] [countY] [1] > bias) {
                VSXu_Green_Channel_add = VSXu_Green_Channel_add + pixels [countX] [countY] [1];
                Green_divide_count++;
            }
            if (pixels [countX] [countY] [2] > bias) {
                VSXu_Blue_Channel_add = VSXu_Blue_Channel_add + pixels [countX] [countY] [2];
                Blue_divide_count++;
            }
        }
    }

    VSXu_Red_Channel = VSXu_Red_Channel_add / Red_divide_count;
    if (VSXu_Red_Channel) RGB_divide_count++;
    VSXu_Green_Channel = VSXu_Green_Channel_add / Green_divide_count;
    if (VSXu_Green_Channel) RGB_divide_count++;
    VSXu_Blue_Channel = VSXu_Blue_Channel_add / Blue_divide_count;
    if (VSXu_Blue_Channel) RGB_divide_count++;

    if (RGB_divide_count == 0) RGB_divide_count = 1;
    VSXu_RGB_Channel = (VSXu_Red_Channel + VSXu_Green_Channel + VSXu_Blue_Channel) / RGB_divide_count;
*/




//this code here gets the average of all the pixels, excluding blank or biased out pixels
    for (countX = 1; countX < vsxu_width; countX++){
        for (countY = 1; countY < vsxu_height; countY++){
            if (pixels [countX] [countY] [0] > bias) VSXu_Red_Channel_add++;
            if (pixels [countX] [countY] [1] > bias) VSXu_Green_Channel_add++;
            if (pixels [countX] [countY] [2] > bias) VSXu_Blue_Channel_add++;
            }
    }

    total_pixels = vsxu_width * vsxu_height;
    divisor = total_pixels / 256;



    VSXu_Red_Channel = (VSXu_Red_Channel_add / divisor);
    VSXu_Green_Channel = (VSXu_Green_Channel_add / divisor);
    VSXu_Blue_Channel = (VSXu_Blue_Channel_add / divisor);

    VSXu_RGB_Channel = (VSXu_Red_Channel + VSXu_Green_Channel + VSXu_Blue_Channel) / 3;


//this code below assigns the visualiation values to the DMX buffers
    if (Choice1->GetSelection() > 0) {

        if (Choice1->GetSelection() == 1 &&(!CheckBox1->IsChecked())) Channel_1_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 2 &&(!CheckBox2->IsChecked())) Channel_2_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 3 &&(!CheckBox3->IsChecked())) Channel_3_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 4 &&(!CheckBox4->IsChecked())) Channel_4_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 5 &&(!CheckBox5->IsChecked())) Channel_5_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 6 &&(!CheckBox6->IsChecked())) Channel_6_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 7 &&(!CheckBox7->IsChecked())) Channel_7_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 8 &&(!CheckBox8->IsChecked())) Channel_8_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 9 &&(!CheckBox9->IsChecked())) Channel_9_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 10 &&(!CheckBox10->IsChecked())) Channel_10_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 11 &&(!CheckBox11->IsChecked())) Channel_11_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 12 &&(!CheckBox12->IsChecked())) Channel_12_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 13 &&(!CheckBox13->IsChecked())) Channel_13_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 14 &&(!CheckBox14->IsChecked())) Channel_14_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 15 &&(!CheckBox15->IsChecked())) Channel_15_VSXu = VSXu_Red_Channel;
        if (Choice1->GetSelection() == 16 &&(!CheckBox16->IsChecked())) Channel_16_VSXu = VSXu_Red_Channel;
    }

    if (Choice2->GetSelection() > 0) {

        if (Choice2->GetSelection() == 1 &&(!CheckBox1->IsChecked())) Channel_1_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 2 &&(!CheckBox2->IsChecked())) Channel_2_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 3 &&(!CheckBox3->IsChecked())) Channel_3_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 4 &&(!CheckBox4->IsChecked())) Channel_4_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 5 &&(!CheckBox5->IsChecked())) Channel_5_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 6 &&(!CheckBox6->IsChecked())) Channel_6_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 7 &&(!CheckBox7->IsChecked())) Channel_7_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 8 &&(!CheckBox8->IsChecked())) Channel_8_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 9 &&(!CheckBox9->IsChecked())) Channel_9_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 10 &&(!CheckBox10->IsChecked())) Channel_10_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 11 &&(!CheckBox11->IsChecked())) Channel_11_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 12 &&(!CheckBox12->IsChecked())) Channel_12_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 13 &&(!CheckBox13->IsChecked())) Channel_13_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 14 &&(!CheckBox14->IsChecked())) Channel_14_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 15 &&(!CheckBox15->IsChecked())) Channel_15_VSXu = VSXu_Green_Channel;
        if (Choice2->GetSelection() == 16 &&(!CheckBox16->IsChecked())) Channel_16_VSXu = VSXu_Green_Channel;
    }

    if (Choice3->GetSelection() > 0) {

        if (Choice3->GetSelection() == 1 &&(!CheckBox1->IsChecked())) Channel_1_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 2 &&(!CheckBox2->IsChecked())) Channel_2_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 3 &&(!CheckBox3->IsChecked())) Channel_3_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 4 &&(!CheckBox4->IsChecked())) Channel_4_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 5 &&(!CheckBox5->IsChecked())) Channel_5_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 6 &&(!CheckBox6->IsChecked())) Channel_6_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 7 &&(!CheckBox7->IsChecked())) Channel_7_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 8 &&(!CheckBox8->IsChecked())) Channel_8_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 9 &&(!CheckBox9->IsChecked())) Channel_9_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 10 &&(!CheckBox10->IsChecked())) Channel_10_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 11 &&(!CheckBox11->IsChecked())) Channel_11_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 12 &&(!CheckBox12->IsChecked())) Channel_12_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 13 &&(!CheckBox13->IsChecked())) Channel_13_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 14 &&(!CheckBox14->IsChecked())) Channel_14_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 15 &&(!CheckBox15->IsChecked())) Channel_15_VSXu = VSXu_Blue_Channel;
        if (Choice3->GetSelection() == 16 &&(!CheckBox16->IsChecked())) Channel_16_VSXu = VSXu_Blue_Channel;
    }

    if (Choice4->GetSelection() > 0) {

        if (Choice4->GetSelection() == 1 &&(!CheckBox1->IsChecked())) Channel_1_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 2 &&(!CheckBox2->IsChecked())) Channel_2_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 3 &&(!CheckBox3->IsChecked())) Channel_3_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 4 &&(!CheckBox4->IsChecked())) Channel_4_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 5 &&(!CheckBox5->IsChecked())) Channel_5_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 6 &&(!CheckBox6->IsChecked())) Channel_6_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 7 &&(!CheckBox7->IsChecked())) Channel_7_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 8 &&(!CheckBox8->IsChecked())) Channel_8_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 9 &&(!CheckBox9->IsChecked())) Channel_9_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 10 &&(!CheckBox10->IsChecked())) Channel_10_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 11 &&(!CheckBox11->IsChecked())) Channel_11_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 12 &&(!CheckBox12->IsChecked())) Channel_12_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 13 &&(!CheckBox13->IsChecked())) Channel_13_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 14 &&(!CheckBox14->IsChecked())) Channel_14_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 15 &&(!CheckBox15->IsChecked())) Channel_15_VSXu = VSXu_RGB_Channel;
        if (Choice4->GetSelection() == 16 &&(!CheckBox16->IsChecked())) Channel_16_VSXu = VSXu_RGB_Channel;

    }

///this writes general DMX values, everything thats not visualization animation

    if (!CheckBox1->IsChecked())
    {
        if ((Choice1->GetSelection() == 1) || (Choice2->GetSelection() == 1) || (Choice3->GetSelection() == 1) || (Choice4->GetSelection() == 1)) {}
        else Channel_1_VSXu = Slider1->GetValue();
    }
    else Channel_1_VSXu = VSXu_ProfileChannel_1;

    if (!CheckBox2->IsChecked())
    {
        if ((Choice1->GetSelection() == 2) || (Choice2->GetSelection() == 2) || (Choice3->GetSelection() == 2) || (Choice4->GetSelection() == 2)) {}
        else Channel_2_VSXu = Slider2->GetValue();
    }
    else Channel_2_VSXu = VSXu_ProfileChannel_2;

    if (!CheckBox3->IsChecked())
    {
        if ((Choice1->GetSelection() == 3) || (Choice2->GetSelection() == 3) || (Choice3->GetSelection() == 3) || (Choice4->GetSelection() == 3)) {}
        else Channel_3_VSXu = Slider3->GetValue();
    }
    else Channel_3_VSXu = VSXu_ProfileChannel_3;

    if (!CheckBox4->IsChecked())
    {
        if ((Choice1->GetSelection() == 4) || (Choice2->GetSelection() == 4) || (Choice3->GetSelection() == 4) || (Choice4->GetSelection() == 4)) {}
        else Channel_4_VSXu = Slider4->GetValue();
    }
    else Channel_4_VSXu = VSXu_ProfileChannel_4;

    if (!CheckBox5->IsChecked())
    {
        if ((Choice1->GetSelection() == 5) || (Choice2->GetSelection() == 5) || (Choice3->GetSelection() == 5) || (Choice4->GetSelection() == 5)) {}
        else Channel_5_VSXu = Slider5->GetValue();
    }
    else Channel_5_VSXu = VSXu_ProfileChannel_5;

    if (!CheckBox6->IsChecked())
    {
        if ((Choice1->GetSelection() == 6) || (Choice2->GetSelection() == 6) || (Choice3->GetSelection() == 6) || (Choice4->GetSelection() == 6)) {}
        else Channel_6_VSXu = Slider6->GetValue();
    }
    else Channel_6_VSXu = VSXu_ProfileChannel_6;

    if (!CheckBox7->IsChecked())
    {
        if ((Choice1->GetSelection() == 7) || (Choice2->GetSelection() == 7) || (Choice3->GetSelection() == 7) || (Choice4->GetSelection() == 7)) {}
        else Channel_7_VSXu = Slider7->GetValue();
    }
    else Channel_7_VSXu = VSXu_ProfileChannel_7;

    if (!CheckBox8->IsChecked())
    {
        if ((Choice1->GetSelection() == 8) || (Choice2->GetSelection() == 8) || (Choice3->GetSelection() == 8) || (Choice4->GetSelection() == 8)) {}
        else Channel_8_VSXu = Slider8->GetValue();
    }
    else Channel_8_VSXu = VSXu_ProfileChannel_8;

    if (!CheckBox9->IsChecked())
    {
        if ((Choice1->GetSelection() == 9) || (Choice2->GetSelection() == 9) || (Choice3->GetSelection() == 9) || (Choice4->GetSelection() == 9)) {}
        else Channel_9_VSXu = Slider9->GetValue();
    }
    else Channel_9_VSXu = VSXu_ProfileChannel_9;

    if (!CheckBox10->IsChecked())
    {
        if ((Choice1->GetSelection() == 10) || (Choice2->GetSelection() == 10) || (Choice3->GetSelection() == 10) || (Choice4->GetSelection() == 10)) {}
        else Channel_10_VSXu = Slider10->GetValue();
    }
    else Channel_10_VSXu = VSXu_ProfileChannel_10;

    if (!CheckBox11->IsChecked())
    {
        if ((Choice1->GetSelection() == 11) || (Choice2->GetSelection() == 11) || (Choice3->GetSelection() == 11) || (Choice4->GetSelection() == 11)) {}
        else Channel_11_VSXu = Slider11->GetValue();
    }
    else Channel_11_VSXu = VSXu_ProfileChannel_11;

    if (!CheckBox12->IsChecked())
    {
        if ((Choice1->GetSelection() == 12) || (Choice2->GetSelection() == 12) || (Choice3->GetSelection() == 12) || (Choice4->GetSelection() == 12)) {}
        else Channel_12_VSXu = Slider12->GetValue();
    }
    else Channel_12_VSXu = VSXu_ProfileChannel_12;

    if (!CheckBox13->IsChecked())
    {
        if ((Choice1->GetSelection() == 13) || (Choice2->GetSelection() == 13) || (Choice3->GetSelection() == 13) || (Choice4->GetSelection() == 13)) {}
        else Channel_13_VSXu = Slider13->GetValue();
    }
    else Channel_13_VSXu = VSXu_ProfileChannel_13;

    if (!CheckBox14->IsChecked())
    {
        if ((Choice1->GetSelection() == 14) || (Choice2->GetSelection() == 14) || (Choice3->GetSelection() == 14) || (Choice4->GetSelection() == 14)) {}
        else Channel_14_VSXu = Slider14->GetValue();
    }
    else Channel_14_VSXu = VSXu_ProfileChannel_14;

    if (!CheckBox15->IsChecked())
    {
        if ((Choice1->GetSelection() == 15) || (Choice2->GetSelection() == 15) || (Choice3->GetSelection() == 15) || (Choice4->GetSelection() == 15)) {}
        else Channel_15_VSXu = Slider15->GetValue();
    }
    else Channel_15_VSXu = VSXu_ProfileChannel_15;

    if (!CheckBox16->IsChecked())
    {
        if ((Choice1->GetSelection() == 16) || (Choice2->GetSelection() == 16) || (Choice3->GetSelection() == 16) || (Choice4->GetSelection() == 16)) {}
        else Channel_16_VSXu = Slider16->GetValue();
    }
    else Channel_16_VSXu = VSXu_ProfileChannel_16;


}

void VSXuAudioVisualizer::OnChoice1Select(wxCommandEvent& event)
{
}



void VSXuAudioVisualizer::OnClose(wxCloseEvent& event)
{
        if (hasVSXurunonce)
        {
            vsxu_renderer->m_manager->stop();
            vsxu_renderer->deactivate();
            vsxu_renderer->Destroy();
            vsxu_canvas->Destroy();
           // vsxu_frame->Show(false);
            vsxu_frame->Destroy();
            Timer1.Stop();
            timer->Stop();
            if (fullscreen){
                vsxu_width = 640;
                vsxu_height = 480;
                vsxu_frame->SetSize(vsxu_width,vsxu_height);
                //hiding and showing the wxframe refreshes the sizer values
                vsxu_frame->Show(false);
                vsxu_frame->Show(true);
                vsxu_frame->ShowFullScreen(false);
                fullscreen = false;
                vsxu_renderer->m_doResize = true;
            }
            SaveData();
            Destroy();
        }
        else {SaveData(); Destroy();}
}





void VSXuAudioVisualizer::OnTestButtonClick2(wxCommandEvent& event)
{
    vsxu_renderer->m_manager->pick_visual(5);
}

void VSXuAudioVisualizer::OnButton1Click(wxCommandEvent& event)
{
    if (fullscreen){
        vsxu_width = 640;
        vsxu_height = 480;
        vsxu_frame->SetSize(vsxu_width,vsxu_height);
        vsxu_frame->SetPosition(wxPoint(520,50));
        //hiding and showing the wxframe refreshes the sizer values
        vsxu_frame->ShowFullScreen(false);
        vsxu_frame->Show(false);
        vsxu_frame->Show(true);
        fullscreen = false;
        vsxu_renderer->m_doResize = true;
    }
    else {
        //fullscreen code (messes with glreadpixels, i guess because of pointer)
        vsxu_width = wxSystemSettings::GetMetric ( wxSYS_SCREEN_X );
        vsxu_height = wxSystemSettings::GetMetric ( wxSYS_SCREEN_Y );
        if (vsxu_width > 1920) vsxu_width = 1920;
        if (vsxu_height > 1080) vsxu_height = 1080;

        vsxu_renderer->m_doResize = true;

        vsxu_frame->SetSize(vsxu_width,vsxu_height);
        //hiding and showing the wxframe refreshes the sizer values
        vsxu_frame->Show(false);
        vsxu_frame->Show(true);
        vsxu_frame->ShowFullScreen(true);
        fullscreen = true;
    }


}

void VSXuAudioVisualizer::OnLeftDClick(wxMouseEvent& event)
{
    if (fullscreen){
        vsxu_width = 640;
        vsxu_height = 480;
        vsxu_frame->SetSize(vsxu_width,vsxu_height);
        //hiding and showing the wxframe refreshes the sizer values
        vsxu_frame->Show(false);
        vsxu_frame->Show(true);
        vsxu_frame->ShowFullScreen(false);
        fullscreen = false;
        vsxu_renderer->m_doResize = true;
    }
}


void VSXuAudioVisualizer::OnSetFocus(wxFocusEvent& event)
{
    if (fullscreen){
        vsxu_width = 640;
        vsxu_height = 480;
        vsxu_frame->SetSize(vsxu_width,vsxu_height);
        //hiding and showing the wxframe refreshes the sizer values
        vsxu_frame->Show(false);
        vsxu_frame->Show(true);
        vsxu_frame->ShowFullScreen(false);
        fullscreen = false;
        vsxu_renderer->m_doResize = true;
    }
}

void VSXuAudioVisualizer::LoadData(void)
{
    wxTextFile vsxufile;
    vsxufile.Open(vsxufilename, wxConvISO8859_1);

    wxString buffer;

    buffer = vsxufile.GetFirstLine();
    Slider1->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider2->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider3->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider4->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider5->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider6->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider7->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider8->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider9->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider10->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider11->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider12->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider13->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider14->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider15->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Slider16->SetValue(wxAtoi(buffer));

///choice boxes for other selections

    buffer = vsxufile.GetNextLine();
    Choice1->SetSelection(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Choice2->SetSelection(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Choice3->SetSelection(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Choice4->SetSelection(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    Choice5->SetSelection(wxAtoi(buffer));
///check boxes
    buffer = vsxufile.GetNextLine();
    CheckBox1->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox2->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox3->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox4->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox5->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox6->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox7->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox8->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox9->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox10->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox11->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox12->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox13->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox14->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox15->SetValue(wxAtoi(buffer));

    buffer = vsxufile.GetNextLine();
    CheckBox16->SetValue(wxAtoi(buffer));
}

void VSXuAudioVisualizer::SaveData(void)
 {
    wxString BankData;

    wxTextFile vsxufile;
    vsxufile.Create(vsxufilename);

    BankData = wxString::Format(wxT("%i"),Slider1->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider2->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider3->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider4->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider5->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider6->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider7->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider8->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider9->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider10->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider11->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider12->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider13->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider14->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider15->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Slider16->GetValue());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),Choice1->GetSelection());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),Choice2->GetSelection());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),Choice3->GetSelection());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),Choice4->GetSelection());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),Choice5->GetSelection());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);
 ///check boxes
    BankData = wxString::Format(wxT("%i"),CheckBox1->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox2->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox3->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox4->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox5->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox6->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox7->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox8->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox9->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox10->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox11->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox12->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox13->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox14->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox15->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    BankData = wxString::Format(wxT("%i"),CheckBox16->IsChecked());
    vsxufile.AddLine(BankData, wxTextFileType_Dos);

    //these lines save and close the file
    vsxufile.Write(wxTextFileType_Dos, wxConvISO8859_1);
    vsxufile.Close();

}
