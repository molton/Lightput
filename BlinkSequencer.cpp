//(C) 2013 Michael Johnston

#include "BlinkSequencer.h"

//(*InternalHeaders(BlinkSequencer)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)
#include <wx/msgdlg.h>
#include <wx/textfile.h>

//so much for reusing these dialogs, it causes lots of problems
//#include "AddNewProfile.h"
//#include "RenameProfile.h"
//#include "DeleteVerify.h"
//#include "ProfileOverwrite.h"

#include "bsAddNewProfile.h"
#include "bsRenameProfile.h"
#include "bsDeleteProfile.h"
#include "bsProfileOverwrite.h"


//apparently this stuff worked fine on older linux / wx widgets versions but
//but on this software certain things need to be set to initialize
//once and then never happen again

bool bool_is_initialized;

bool bsischanged;
bool istempomeasure;
wxString bsnewprofileValue;
wxString bsRenameNameHolder;

extern bool isIconize;

//extern bool isprofilemode;

//extern bool yesorno;
//extern bool generalcancel;

bool bsyesorno;
bool bscancel;

unsigned long int bsbeattime;

//variables for new transitional system
double bsChannel_1_difference;
double bsChannel_1_increment;
double bsChannel_1_added;
unsigned short int bsChannel_1_new;
unsigned short int bsChannel_1_out;
double bsChannel_2_difference;
double bsChannel_2_increment;
double bsChannel_2_added;
unsigned short int bsChannel_2_new;
unsigned short int bsChannel_2_out;
double bsChannel_3_difference;
double bsChannel_3_increment;
double bsChannel_3_added;
unsigned short int bsChannel_3_new;
unsigned short int bsChannel_3_out;
double bsChannel_4_difference;
double bsChannel_4_increment;
double bsChannel_4_added;
unsigned short int bsChannel_4_new;
unsigned short int bsChannel_4_out;
double bsChannel_5_difference;
double bsChannel_5_increment;
double bsChannel_5_added;
unsigned short int bsChannel_5_new;
unsigned short int bsChannel_5_out;
double bsChannel_6_difference;
double bsChannel_6_increment;
double bsChannel_6_added;
unsigned short int bsChannel_6_new;
unsigned short int bsChannel_6_out;
double bsChannel_7_difference;
double bsChannel_7_increment;
double bsChannel_7_added;
unsigned short int bsChannel_7_new;
unsigned short int bsChannel_7_out;
double bsChannel_8_difference;
double bsChannel_8_increment;
double bsChannel_8_added;
unsigned short int bsChannel_8_new;
unsigned short int bsChannel_8_out;
double bsChannel_9_difference;
double bsChannel_9_increment;
double bsChannel_9_added;
unsigned short int bsChannel_9_new;
unsigned short int bsChannel_9_out;
double bsChannel_10_difference;
double bsChannel_10_increment;
double bsChannel_10_added;
unsigned short int bsChannel_10_new;
unsigned short int bsChannel_10_out;
double bsChannel_11_difference;
double bsChannel_11_increment;
double bsChannel_11_added;
unsigned short int bsChannel_11_new;
unsigned short int bsChannel_11_out;
double bsChannel_12_difference;
double bsChannel_12_increment;
double bsChannel_12_added;
unsigned short int bsChannel_12_new;
unsigned short int bsChannel_12_out;
double bsChannel_13_difference;
double bsChannel_13_increment;
double bsChannel_13_added;
unsigned short int bsChannel_13_new;
unsigned short int bsChannel_13_out;
double bsChannel_14_difference;
double bsChannel_14_increment;
double bsChannel_14_added;
unsigned short int bsChannel_14_new;
unsigned short int bsChannel_14_out;
double bsChannel_15_difference;
double bsChannel_15_increment;
double bsChannel_15_added;
unsigned short int bsChannel_15_new;
unsigned short int bsChannel_15_out;
double bsChannel_16_difference;
double bsChannel_16_increment;
double bsChannel_16_added;
unsigned short int bsChannel_16_new;
unsigned short int bsChannel_16_out;

//float time_divide;


//extern bool isprogramstarted;
//extern bool beatchange;
bool ispaused;
//this comparevalue is used to determine if text control output has changed
int comparevalue;

wxString SequencerProfileNames [64];
unsigned short int SequencerBeats [64];
unsigned long int SequencerTime [64];
unsigned short int SequencerExemptChannels [64] [16];
unsigned short int SequencerChannel_1 [64] [12];
unsigned short int SequencerChannel_2 [64] [12];
unsigned short int SequencerChannel_3 [64] [12];
unsigned short int SequencerChannel_4 [64] [12];
unsigned short int SequencerChannel_5 [64] [12];
unsigned short int SequencerChannel_6 [64] [12];
unsigned short int SequencerChannel_7 [64] [12];
unsigned short int SequencerChannel_8 [64] [12];
unsigned short int SequencerChannel_9 [64] [12];
unsigned short int SequencerChannel_10 [64] [12];
unsigned short int SequencerChannel_11 [64] [12];
unsigned short int SequencerChannel_12 [64] [12];
unsigned short int SequencerChannel_13 [64] [12];
unsigned short int SequencerChannel_14 [64] [12];
unsigned short int SequencerChannel_15 [64] [12];
unsigned short int SequencerChannel_16 [64] [12];


//for testing

int profilecount;


wxString displayValue;

extern bool islightprogramonstartup;
extern bool isminimizedonstartup;

//19 lines per profile * 64 profiles = 1216 lines
wxString buffer [1216];



//buffers for profile when blinking is off/done
extern int bs_ProfileChannel_1;
extern int bs_ProfileChannel_2;
extern int bs_ProfileChannel_3;
extern int bs_ProfileChannel_4;
extern int bs_ProfileChannel_5;
extern int bs_ProfileChannel_6;
extern int bs_ProfileChannel_7;
extern int bs_ProfileChannel_8;
extern int bs_ProfileChannel_9;
extern int bs_ProfileChannel_10;
extern int bs_ProfileChannel_11;
extern int bs_ProfileChannel_12;
extern int bs_ProfileChannel_13;
extern int bs_ProfileChannel_14;
extern int bs_ProfileChannel_15;
extern int bs_ProfileChannel_16;

//these boolean values tell a function whih beats are enabled
bool e3;
bool e4;
bool e5;
bool e6;
bool e7;
bool e8;
bool e9;
bool e10;
bool e11;
bool e12;

bool isstarted = false;
unsigned short int beat;
unsigned short int lastbeat;
unsigned short int previousbeat;
unsigned short int channel;
wxString blinksequencerfilename;
extern wxString directory;
//these variables hold the profile save data format dimensions
unsigned short int pos;
unsigned short int postimes;
unsigned short int bsnumberofprofiles;
unsigned short int sequencercurrentprofile;

//this value is for the default transition type
extern bool issmooth;
extern bool issmoothstart;
extern unsigned short int LightputFrequency;


//(*IdInit(BlinkSequencer)
const long BlinkSequencer::ID_STATICBOX1 = wxNewId();
const long BlinkSequencer::ID_STATICBOX4 = wxNewId();
const long BlinkSequencer::ID_STATICBOX3 = wxNewId();
const long BlinkSequencer::ID_STATICBOX2 = wxNewId();
const long BlinkSequencer::ID_CHOICE1 = wxNewId();
const long BlinkSequencer::ID_SLIDER1 = wxNewId();
const long BlinkSequencer::ID_SLIDER2 = wxNewId();
const long BlinkSequencer::ID_SLIDER3 = wxNewId();
const long BlinkSequencer::ID_SLIDER4 = wxNewId();
const long BlinkSequencer::ID_SLIDER5 = wxNewId();
const long BlinkSequencer::ID_SLIDER6 = wxNewId();
const long BlinkSequencer::ID_SLIDER7 = wxNewId();
const long BlinkSequencer::ID_SLIDER8 = wxNewId();
const long BlinkSequencer::ID_SLIDER9 = wxNewId();
const long BlinkSequencer::ID_SLIDER10 = wxNewId();
const long BlinkSequencer::ID_SLIDER11 = wxNewId();
const long BlinkSequencer::ID_SLIDER12 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT1 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT2 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT3 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT4 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT5 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT6 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT7 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT8 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT9 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT10 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT11 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT12 = wxNewId();
const long BlinkSequencer::ID_CHOICE3 = wxNewId();
const long BlinkSequencer::ID_LISTBOX1 = wxNewId();
const long BlinkSequencer::ID_BUTTON3 = wxNewId();
const long BlinkSequencer::ID_BUTTON4 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT13 = wxNewId();
const long BlinkSequencer::ID_BUTTON5 = wxNewId();
const long BlinkSequencer::ID_TEXTCTRL1 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT16 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT14 = wxNewId();
const long BlinkSequencer::ID_BUTTON6 = wxNewId();
const long BlinkSequencer::ID_BUTTON7 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT17 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT19 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT20 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT21 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT22 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT23 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT24 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT25 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT26 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT27 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT28 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT29 = wxNewId();
const long BlinkSequencer::ID_BUTTON1 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT30 = wxNewId();
const long BlinkSequencer::ID_BUTTON2 = wxNewId();
const long BlinkSequencer::ID_RADIOBUTTON1 = wxNewId();
const long BlinkSequencer::ID_RADIOBUTTON2 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT31 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX1 = wxNewId();
const long BlinkSequencer::ID_BUTTON9 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT15 = wxNewId();
const long BlinkSequencer::ID_CHOICE2 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT18 = wxNewId();
const long BlinkSequencer::ID_STATICTEXT32 = wxNewId();
const long BlinkSequencer::ID_BUTTON8 = wxNewId();
const long BlinkSequencer::ID_STATICBOX5 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX2 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX3 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX4 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX5 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX6 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX7 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX8 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX9 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX10 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX11 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX12 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX13 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX14 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX15 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX16 = wxNewId();
const long BlinkSequencer::ID_CHECKBOX17 = wxNewId();
const long BlinkSequencer::ID_TIMER1 = wxNewId();
//*)
//BStimer BS_time1;

BEGIN_EVENT_TABLE(BlinkSequencer,wxDialog)
	//(*EventTable(BlinkSequencer)
	//*)
END_EVENT_TABLE()

BlinkSequencer::BlinkSequencer(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //put the propper color data into the lights from profile mode
    bsChannel_1_out = bs_ProfileChannel_1;
    bsChannel_2_out = bs_ProfileChannel_2;
    bsChannel_3_out = bs_ProfileChannel_3;
    bsChannel_4_out = bs_ProfileChannel_4;
    bsChannel_5_out = bs_ProfileChannel_5;
    bsChannel_6_out = bs_ProfileChannel_6;
    bsChannel_7_out = bs_ProfileChannel_7;
    bsChannel_8_out = bs_ProfileChannel_8;
    bsChannel_9_out = bs_ProfileChannel_9;
    bsChannel_10_out = bs_ProfileChannel_10;
    bsChannel_11_out = bs_ProfileChannel_11;
    bsChannel_12_out = bs_ProfileChannel_12;
    bsChannel_13_out = bs_ProfileChannel_13;
    bsChannel_14_out = bs_ProfileChannel_14;
    bsChannel_15_out = bs_ProfileChannel_15;
    bsChannel_16_out = bs_ProfileChannel_16;
    bsChannel_1_new = bs_ProfileChannel_1;
    bsChannel_2_new = bs_ProfileChannel_2;
    bsChannel_3_new = bs_ProfileChannel_3;
    bsChannel_4_new = bs_ProfileChannel_4;
    bsChannel_5_new = bs_ProfileChannel_5;
    bsChannel_6_new = bs_ProfileChannel_6;
    bsChannel_7_new = bs_ProfileChannel_7;
    bsChannel_8_new = bs_ProfileChannel_8;
    bsChannel_9_new = bs_ProfileChannel_9;
    bsChannel_10_new = bs_ProfileChannel_10;
    bsChannel_11_new = bs_ProfileChannel_11;
    bsChannel_12_new = bs_ProfileChannel_12;
    bsChannel_13_new = bs_ProfileChannel_13;
    bsChannel_14_new = bs_ProfileChannel_14;
    bsChannel_15_new = bs_ProfileChannel_15;
    bsChannel_16_new = bs_ProfileChannel_16;
    bsChannel_1_added = bs_ProfileChannel_1;
    bsChannel_2_added = bs_ProfileChannel_2;
    bsChannel_3_added = bs_ProfileChannel_3;
    bsChannel_4_added = bs_ProfileChannel_4;
    bsChannel_5_added = bs_ProfileChannel_5;
    bsChannel_6_added = bs_ProfileChannel_6;
    bsChannel_7_added = bs_ProfileChannel_7;
    bsChannel_8_added = bs_ProfileChannel_8;
    bsChannel_9_added = bs_ProfileChannel_9;
    bsChannel_10_added = bs_ProfileChannel_10;
    bsChannel_11_added = bs_ProfileChannel_11;
    bsChannel_12_added = bs_ProfileChannel_12;
    bsChannel_13_added = bs_ProfileChannel_13;
    bsChannel_14_added = bs_ProfileChannel_14;
    bsChannel_15_added = bs_ProfileChannel_15;
    bsChannel_16_added = bs_ProfileChannel_16;


	//(*Initialize(BlinkSequencer)
	Create(parent, wxID_ANY, _("Light Sequencer 0.3"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(859,475));
	Move(wxPoint(100,100));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Light Sequence"), wxPoint(40,120), wxSize(784,224), 0, _T("ID_STATICBOX1"));
	StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("Current Channel"), wxPoint(56,144), wxSize(160,56), 0, _T("ID_STATICBOX4"));
	StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("Light Sequence Configuration"), wxPoint(40,8), wxSize(344,104), 0, _T("ID_STATICBOX3"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Light Sequence Profiles"), wxPoint(392,8), wxSize(432,104), 0, _T("ID_STATICBOX2"));
	Choice1 = new wxChoice(this, ID_CHOICE1, wxPoint(215,28), wxSize(56,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice1->SetSelection( Choice1->Append(_("2")) );
	Choice1->Append(_("3"));
	Choice1->Append(_("4"));
	Choice1->Append(_("5"));
	Choice1->Append(_("6"));
	Choice1->Append(_("7"));
	Choice1->Append(_("8"));
	Choice1->Append(_("9"));
	Choice1->Append(_("10"));
	Choice1->Append(_("11"));
	Choice1->Append(_("12"));
	Choice1->SetFocus();
	Choice1->SetExtraStyle( Choice1->GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY );
	Slider1 = new wxSlider(this, ID_SLIDER1, 0, 0, 255, wxPoint(240,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER1"));
	Slider2 = new wxSlider(this, ID_SLIDER2, 0, 0, 255, wxPoint(286,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER2"));
	Slider3 = new wxSlider(this, ID_SLIDER3, 0, 0, 255, wxPoint(334,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER3"));
	Slider4 = new wxSlider(this, ID_SLIDER4, 0, 0, 255, wxPoint(382,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER4"));
	Slider5 = new wxSlider(this, ID_SLIDER5, 0, 0, 255, wxPoint(430,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER5"));
	Slider6 = new wxSlider(this, ID_SLIDER6, 0, 0, 255, wxPoint(478,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER6"));
	Slider7 = new wxSlider(this, ID_SLIDER7, 0, 0, 255, wxPoint(526,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER7"));
	Slider8 = new wxSlider(this, ID_SLIDER8, 0, 0, 255, wxPoint(574,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER8"));
	Slider9 = new wxSlider(this, ID_SLIDER9, 0, 0, 255, wxPoint(622,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER9"));
	Slider10 = new wxSlider(this, ID_SLIDER10, 0, 0, 255, wxPoint(670,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER10"));
	Slider11 = new wxSlider(this, ID_SLIDER11, 0, 0, 255, wxPoint(718,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER11"));
	Slider12 = new wxSlider(this, ID_SLIDER12, 0, 0, 255, wxPoint(766,160), wxSize(24,136), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER12"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("1"), wxPoint(247,136), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("2"), wxPoint(295,136), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("3"), wxPoint(343,136), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("4"), wxPoint(391,136), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("5"), wxPoint(439,136), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("6"), wxPoint(487,136), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("7"), wxPoint(535,136), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("8"), wxPoint(583,136), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("9"), wxPoint(631,136), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("10"), wxPoint(676,136), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("11"), wxPoint(724,136), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("12"), wxPoint(772,136), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	Choice3 = new wxChoice(this, ID_CHOICE3, wxPoint(80,168), wxSize(112,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
	Choice3->SetSelection( Choice3->Append(_("Channel 1")) );
	Choice3->Append(_("Channel 2"));
	Choice3->Append(_("Channel 3"));
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
	ListBox1 = new wxListBox(this, ID_LISTBOX1, wxPoint(504,24), wxSize(264,80), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	ListBox1->SetSelection( ListBox1->Append(_("-Empty Profile List-")) );
	ListBox1->SetFocus();
	wxFont ListBox1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	ListBox1->SetFont(ListBox1Font);
	Button3 = new wxButton(this, ID_BUTTON3, _("Rename"), wxPoint(408,52), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	Button4 = new wxButton(this, ID_BUTTON4, _("Delete"), wxPoint(408,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Number of beats in sequence:"), wxPoint(48,32), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	wxFont StaticText13Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText13->SetFont(StaticText13Font);
	Button5 = new wxButton(this, ID_BUTTON5, _("Start"), wxPoint(40,408), wxSize(112,32), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("1000"), wxPoint(128,52), wxSize(64,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	wxFont TextCtrl1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl1->SetFont(TextCtrl1Font);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Time per beat:"), wxPoint(48,56), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	wxFont StaticText16Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText16->SetFont(StaticText16Font);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("milliseconds."), wxPoint(200,56), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	wxFont StaticText14Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText14->SetFont(StaticText14Font);
	Button6 = new wxButton(this, ID_BUTTON6, _("Move\nUp"), wxPoint(768,24), wxSize(48,40), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	wxFont Button6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button6->SetFont(Button6Font);
	Button7 = new wxButton(this, ID_BUTTON7, _("Move\nDown"), wxPoint(768,64), wxSize(48,40), 0, wxDefaultValidator, _T("ID_BUTTON7"));
	wxFont Button7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button7->SetFont(Button7Font);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Label"), wxPoint(240,304), wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT17"));
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("Label"), wxPoint(288,304), wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT19"));
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("Label"), wxPoint(336,304), wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("Label"), wxPoint(384,304), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	StaticText22 = new wxStaticText(this, ID_STATICTEXT22, _("Label"), wxPoint(432,304), wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	StaticText23 = new wxStaticText(this, ID_STATICTEXT23, _("Label"), wxPoint(480,304), wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	StaticText24 = new wxStaticText(this, ID_STATICTEXT24, _("Label"), wxPoint(528,304), wxDefaultSize, 0, _T("ID_STATICTEXT24"));
	StaticText25 = new wxStaticText(this, ID_STATICTEXT25, _("Label"), wxPoint(576,304), wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	StaticText26 = new wxStaticText(this, ID_STATICTEXT26, _("Label"), wxPoint(624,304), wxDefaultSize, 0, _T("ID_STATICTEXT26"));
	StaticText27 = new wxStaticText(this, ID_STATICTEXT27, _("Label"), wxPoint(672,304), wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	StaticText28 = new wxStaticText(this, ID_STATICTEXT28, _("Label"), wxPoint(720,304), wxDefaultSize, 0, _T("ID_STATICTEXT28"));
	StaticText29 = new wxStaticText(this, ID_STATICTEXT29, _("Label"), wxPoint(768,304), wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Pause"), wxPoint(176,408), wxSize(112,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button1->Disable();
	StaticText30 = new wxStaticText(this, ID_STATICTEXT30, wxEmptyString, wxPoint(240,320), wxDefaultSize, 0, _T("ID_STATICTEXT30"));
	Button2 = new wxButton(this, ID_BUTTON2, _("New"), wxPoint(408,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	RadioButton1 = new wxRadioButton(this, ID_RADIOBUTTON1, _("Blink"), wxPoint(112,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	wxFont RadioButton1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	RadioButton1->SetFont(RadioButton1Font);
	RadioButton2 = new wxRadioButton(this, ID_RADIOBUTTON2, _("Smooth"), wxPoint(168,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	wxFont RadioButton2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	RadioButton2->SetFont(RadioButton2Font);
	StaticText31 = new wxStaticText(this, ID_STATICTEXT31, _("Transition"), wxPoint(48,82), wxDefaultSize, 0, _T("ID_STATICTEXT31"));
	wxFont StaticText31Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText31->SetFont(StaticText31Font);
	CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("Smooth Start"), wxPoint(256,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox1->SetValue(false);
	wxFont CheckBox1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox1->SetFont(CheckBox1Font);
	Button9 = new wxButton(this, ID_BUTTON9, _("Set Tempo"), wxPoint(296,46), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Or"), wxPoint(276,56), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	wxFont StaticText15Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText15->SetFont(StaticText15Font);
	Choice2 = new wxChoice(this, ID_CHOICE2, wxPoint(128,376), wxSize(40,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	Choice2->SetSelection( Choice2->Append(_("1")) );
	Choice2->Append(_("2"));
	Choice2->Append(_("3"));
	Choice2->Append(_("4"));
	Choice2->Append(_("5"));
	Choice2->Append(_("6"));
	Choice2->Append(_("7"));
	Choice2->Append(_("8"));
	Choice2->Append(_("9"));
	Choice2->Append(_("10"));
	Choice2->Append(_("11"));
	Choice2->Append(_("12"));
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("Start On Beat"), wxPoint(40,380), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	StaticText32 = new wxStaticText(this, ID_STATICTEXT32, _("note: The maximum amount of time each beat will run, 9999999 ms, is about 2 hours and 46 and \na half minutes, 7200000 ms is an even 2 hours per beat and makes the light sequencer run for a \ncomplete 24 hours before returning to beat 1 and the original color.  60 ms is the minimum.\n\nnote: The easiest way to visualize the changes you are making to the light pattern is to adjust \nthe beat time to 1000-3000 ms, start the sequencer, and pause it on the beat you want to \nchange and change the pattern while paused"), wxPoint(320,350), wxDefaultSize, 0, _T("ID_STATICTEXT32"));
	wxFont StaticText32Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText32->SetFont(StaticText32Font);
	Button8 = new wxButton(this, ID_BUTTON8, _("Hide Lightput"), wxPoint(744,0), wxSize(115,24), 0, wxDefaultValidator, _T("ID_BUTTON8"));
	StaticBox5 = new wxStaticBox(this, ID_STATICBOX5, _("Exempt Channels"), wxPoint(56,208), wxSize(168,120), 0, _T("ID_STATICBOX5"));
	CheckBox2 = new wxCheckBox(this, ID_CHECKBOX2, _("1"), wxPoint(72,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBox2->SetValue(false);
	CheckBox3 = new wxCheckBox(this, ID_CHECKBOX3, _("2"), wxPoint(104,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	CheckBox3->SetValue(false);
	CheckBox4 = new wxCheckBox(this, ID_CHECKBOX4, _("3"), wxPoint(136,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	CheckBox4->SetValue(false);
	CheckBox5 = new wxCheckBox(this, ID_CHECKBOX5, _("4"), wxPoint(168,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	CheckBox5->SetValue(false);
	CheckBox6 = new wxCheckBox(this, ID_CHECKBOX6, _("5"), wxPoint(72,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	CheckBox6->SetValue(false);
	CheckBox7 = new wxCheckBox(this, ID_CHECKBOX7, _("6"), wxPoint(104,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	CheckBox7->SetValue(false);
	CheckBox8 = new wxCheckBox(this, ID_CHECKBOX8, _("7"), wxPoint(136,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	CheckBox8->SetValue(false);
	CheckBox9 = new wxCheckBox(this, ID_CHECKBOX9, _("8"), wxPoint(168,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	CheckBox9->SetValue(false);
	CheckBox10 = new wxCheckBox(this, ID_CHECKBOX10, _("9"), wxPoint(72,280), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	CheckBox10->SetValue(false);
	CheckBox11 = new wxCheckBox(this, ID_CHECKBOX11, _("10"), wxPoint(104,280), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	CheckBox11->SetValue(false);
	CheckBox12 = new wxCheckBox(this, ID_CHECKBOX12, _("11"), wxPoint(136,280), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	CheckBox12->SetValue(false);
	CheckBox13 = new wxCheckBox(this, ID_CHECKBOX13, _("12"), wxPoint(168,280), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	CheckBox13->SetValue(false);
	CheckBox14 = new wxCheckBox(this, ID_CHECKBOX14, _("13"), wxPoint(72,304), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	CheckBox14->SetValue(false);
	CheckBox15 = new wxCheckBox(this, ID_CHECKBOX15, _("14"), wxPoint(104,304), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	CheckBox15->SetValue(false);
	CheckBox16 = new wxCheckBox(this, ID_CHECKBOX16, _("15"), wxPoint(136,304), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
	CheckBox16->SetValue(false);
	CheckBox17 = new wxCheckBox(this, ID_CHECKBOX17, _("16"), wxPoint(168,304), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX17"));
	CheckBox17->SetValue(false);
	Timer1.SetOwner(this, ID_TIMER1);
	Center();

	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&BlinkSequencer::OnChoice1Select);
	Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider1CmdScroll);
	Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider1CmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider2CmdScroll);
	Connect(ID_SLIDER2,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider2CmdScroll);
	Connect(ID_SLIDER3,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider3CmdScroll);
	Connect(ID_SLIDER3,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider3CmdScroll);
	Connect(ID_SLIDER4,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider4CmdScroll);
	Connect(ID_SLIDER4,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider4CmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider5CmdScroll);
	Connect(ID_SLIDER5,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider5CmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider6CmdScroll);
	Connect(ID_SLIDER6,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider6CmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider7CmdScroll);
	Connect(ID_SLIDER7,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider7CmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider8CmdScroll);
	Connect(ID_SLIDER8,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider8CmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider9CmdScroll);
	Connect(ID_SLIDER9,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider9CmdScroll);
	Connect(ID_SLIDER10,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider10CmdScroll);
	Connect(ID_SLIDER10,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider10CmdScroll);
	Connect(ID_SLIDER11,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider11CmdScroll);
	Connect(ID_SLIDER11,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider11CmdScroll);
	Connect(ID_SLIDER12,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BlinkSequencer::OnSlider12CmdScroll);
	Connect(ID_SLIDER12,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnSlider12CmdScroll);
	Connect(ID_CHOICE3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&BlinkSequencer::OnChoice3Select);
	Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&BlinkSequencer::OnListBox1Select);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnButton3Click);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnButton4Click);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnButton5Click);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BlinkSequencer::OnTextCtrl1Text);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&BlinkSequencer::OnTextCtrl1TextEnter);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnButton6Click);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnButton7Click);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnButton1Click1);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnButton2Click);
	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&BlinkSequencer::OnRadioButton1Select);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&BlinkSequencer::OnRadioButton2Select);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox1Click1);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnButton9Click);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&BlinkSequencer::OnChoice2Select1);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnButton8Click2);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox2Click);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox3Click);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox4Click);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox5Click);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox6Click);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox7Click);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox8Click);
	Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox9Click);
	Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox10Click);
	Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox11Click);
	Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox12Click);
	Connect(ID_CHECKBOX13,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox13Click);
	Connect(ID_CHECKBOX14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox14Click);
	Connect(ID_CHECKBOX15,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox15Click);
	Connect(ID_CHECKBOX16,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox16Click);
	Connect(ID_CHECKBOX17,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BlinkSequencer::OnCheckBox17Click);
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&BlinkSequencer::OnTimer1Trigger);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&BlinkSequencer::OnClose);
	//*)

//these setup things in the event of a missing or blank profile list
SequencerProfileNames [1] = wxT("Unnamed Sequence");
SequencerBeats [1] = 0;
SequencerTime [1] = 1000;
/*
moved to light programs
ProfileChannel_1 = Channel_1_out;
ProfileChannel_2 = Channel_2_out;
ProfileChannel_3 = Channel_3_out;
ProfileChannel_4 = Channel_4_out;
ProfileChannel_5 = Channel_5_out;
ProfileChannel_6 = Channel_6_out;
ProfileChannel_7 = Channel_7_out;
ProfileChannel_8 = Channel_8_out;
ProfileChannel_9 = Channel_9_out;
ProfileChannel_10 = Channel_10_out;
ProfileChannel_11 = Channel_11_out;
ProfileChannel_12 = Channel_12_out;
ProfileChannel_13 = Channel_13_out;
ProfileChannel_14 = Channel_14_out;
ProfileChannel_15 = Channel_15_out;
ProfileChannel_16 = Channel_16_out;
*/
if (issmooth) {RadioButton2->SetValue(true); CheckBox1->Enable(true);}
else {RadioButton1->SetValue(true); CheckBox1->Enable(false);}
if (issmoothstart) {CheckBox1->SetValue(true); CheckBox1->Enable(true);}
else CheckBox1->SetValue(false);

channel = 1;
lastbeat = 2;
istempomeasure = false;
Choice2->Clear();
Choice2->SetSelection( Choice2->Append(_("1")) );
Choice2->Append(_("2"));

blinksequencerfilename = wxT("./light_programs/blinksequencer.lightput");

loadprofiles();

ispaused = false;
bsischanged = false;
bscancel = false;
bsyesorno = false;
//beat = Choice2->GetSelection()+1;

//changebeat();
//beattime = wxAtoi(TextCtrl1->GetValue());

updateprofile();

if (islightprogramonstartup)
{
    islightprogramonstartup = false;
    //if (isminimizedonstartup) isIconize = true;

    ///activate sequencer

                Button5->SetLabel(wxT("Stop"));
                Button1->Enable(true);
                Choice1->Enable(false);
                TextCtrl1->Enable(false);
                ListBox1->Enable(false);
                CheckBox1->Enable(false);
                Choice2->Enable(false);

                Button2->Enable(false);
                Button3->Enable(false);
                Button4->Enable(false);
                Button6->Enable(false);
                Button7->Enable(false);
                Button9->Enable(false);

                //beattime = wxAtoi(TextCtrl1->GetValue());
                lastbeat = SequencerBeats [(ListBox1->GetSelection())+1];
                bsbeattime = SequencerTime[(ListBox1->GetSelection())+1];
                ///Timer1.Start(bsbeattime,false);
                //beat = 1;
                ispaused = false;
                changebeat();
                beat = Choice2->GetSelection()+1;


                beatcounter();

                if (!CheckBox2->IsChecked()) bsChannel_1_new = SequencerChannel_1 [ListBox1->GetSelection()] [beat];
                if (!CheckBox3->IsChecked()) bsChannel_2_new = SequencerChannel_2 [ListBox1->GetSelection()] [beat];
                if (!CheckBox4->IsChecked()) bsChannel_3_new = SequencerChannel_3 [ListBox1->GetSelection()] [beat];
                if (!CheckBox5->IsChecked()) bsChannel_4_new = SequencerChannel_4 [ListBox1->GetSelection()] [beat];
                if (!CheckBox6->IsChecked()) bsChannel_5_new = SequencerChannel_5 [ListBox1->GetSelection()] [beat];
                if (!CheckBox7->IsChecked()) bsChannel_6_new = SequencerChannel_6 [ListBox1->GetSelection()] [beat];
                if (!CheckBox8->IsChecked()) bsChannel_7_new = SequencerChannel_7 [ListBox1->GetSelection()] [beat];
                if (!CheckBox9->IsChecked()) bsChannel_8_new = SequencerChannel_8 [ListBox1->GetSelection()] [beat];
                if (!CheckBox10->IsChecked()) bsChannel_9_new = SequencerChannel_9 [ListBox1->GetSelection()] [beat];
                if (!CheckBox11->IsChecked()) bsChannel_10_new = SequencerChannel_10 [ListBox1->GetSelection()] [beat];
                if (!CheckBox12->IsChecked()) bsChannel_11_new = SequencerChannel_11 [ListBox1->GetSelection()] [beat];
                if (!CheckBox13->IsChecked()) bsChannel_12_new = SequencerChannel_12 [ListBox1->GetSelection()] [beat];
                if (!CheckBox14->IsChecked()) bsChannel_13_new = SequencerChannel_13 [ListBox1->GetSelection()] [beat];
                if (!CheckBox15->IsChecked()) bsChannel_14_new = SequencerChannel_14 [ListBox1->GetSelection()] [beat];
                if (!CheckBox16->IsChecked()) bsChannel_15_new = SequencerChannel_15 [ListBox1->GetSelection()] [beat];
                if (!CheckBox17->IsChecked()) bsChannel_16_new = SequencerChannel_16 [ListBox1->GetSelection()] [beat];

                if ((CheckBox1->GetValue())&&(RadioButton2->GetValue())){
                    //previous beat gets the right previous beat values for smooth start
                    if (beat == 1) previousbeat = lastbeat;
                    else previousbeat = beat - 1;

                    if (!CheckBox2->IsChecked()) {bsChannel_1_out = SequencerChannel_1 [ListBox1->GetSelection()] [previousbeat]; bsChannel_1_added = bsChannel_1_out;}
                    if (!CheckBox3->IsChecked()) {bsChannel_2_out = SequencerChannel_2 [ListBox1->GetSelection()] [previousbeat]; bsChannel_2_added = bsChannel_2_out;}
                    if (!CheckBox4->IsChecked()) {bsChannel_3_out = SequencerChannel_3 [ListBox1->GetSelection()] [previousbeat]; bsChannel_3_added = bsChannel_3_out;}
                    if (!CheckBox5->IsChecked()) {bsChannel_4_out = SequencerChannel_4 [ListBox1->GetSelection()] [previousbeat]; bsChannel_4_added = bsChannel_4_out;}
                    if (!CheckBox6->IsChecked()) {bsChannel_5_out = SequencerChannel_5 [ListBox1->GetSelection()] [previousbeat]; bsChannel_5_added = bsChannel_5_out;}
                    if (!CheckBox7->IsChecked()) {bsChannel_6_out = SequencerChannel_6 [ListBox1->GetSelection()] [previousbeat]; bsChannel_6_added = bsChannel_6_out;}
                    if (!CheckBox8->IsChecked()) {bsChannel_7_out = SequencerChannel_7 [ListBox1->GetSelection()] [previousbeat]; bsChannel_7_added = bsChannel_7_out;}
                    if (!CheckBox9->IsChecked()) {bsChannel_8_out = SequencerChannel_8 [ListBox1->GetSelection()] [previousbeat]; bsChannel_8_added = bsChannel_8_out;}
                    if (!CheckBox10->IsChecked()) {bsChannel_9_out = SequencerChannel_9 [ListBox1->GetSelection()] [previousbeat]; bsChannel_9_added = bsChannel_9_out;}
                    if (!CheckBox11->IsChecked()) {bsChannel_10_out = SequencerChannel_10 [ListBox1->GetSelection()] [previousbeat]; bsChannel_10_added = bsChannel_10_out;}
                    if (!CheckBox12->IsChecked()) {bsChannel_11_out = SequencerChannel_11 [ListBox1->GetSelection()] [previousbeat]; bsChannel_11_added = bsChannel_11_out;}
                    if (!CheckBox13->IsChecked()) {bsChannel_12_out = SequencerChannel_12 [ListBox1->GetSelection()] [previousbeat]; bsChannel_12_added = bsChannel_12_out;}
                    if (!CheckBox14->IsChecked()) {bsChannel_13_out = SequencerChannel_13 [ListBox1->GetSelection()] [previousbeat]; bsChannel_13_added = bsChannel_13_out;}
                    if (!CheckBox15->IsChecked()) {bsChannel_14_out = SequencerChannel_14 [ListBox1->GetSelection()] [previousbeat]; bsChannel_14_added = bsChannel_14_out;}
                    if (!CheckBox16->IsChecked()) {bsChannel_15_out = SequencerChannel_15 [ListBox1->GetSelection()] [previousbeat]; bsChannel_15_added = bsChannel_15_out;}
                    if (!CheckBox17->IsChecked()) {bsChannel_16_out = SequencerChannel_16 [ListBox1->GetSelection()] [previousbeat]; bsChannel_16_added = bsChannel_16_out;}
                }
                else {
                    bsChannel_1_out = bsChannel_1_new;
                    bsChannel_2_out = bsChannel_2_new;
                    bsChannel_3_out = bsChannel_3_new;
                    bsChannel_4_out = bsChannel_4_new;
                    bsChannel_5_out = bsChannel_5_new;
                    bsChannel_6_out = bsChannel_6_new;
                    bsChannel_7_out = bsChannel_7_new;
                    bsChannel_8_out = bsChannel_8_new;
                    bsChannel_9_out = bsChannel_9_new;
                    bsChannel_10_out = bsChannel_10_new;
                    bsChannel_11_out = bsChannel_11_new;
                    bsChannel_12_out = bsChannel_12_new;
                    bsChannel_13_out = bsChannel_13_new;
                    bsChannel_14_out = bsChannel_14_new;
                    bsChannel_15_out = bsChannel_15_new;
                    bsChannel_16_out = bsChannel_16_new;

                    bsChannel_1_added = bsChannel_1_new;
                    bsChannel_2_added = bsChannel_2_new;
                    bsChannel_3_added = bsChannel_3_new;
                    bsChannel_4_added = bsChannel_4_new;
                    bsChannel_5_added = bsChannel_5_new;
                    bsChannel_6_added = bsChannel_6_new;
                    bsChannel_7_added = bsChannel_7_new;
                    bsChannel_8_added = bsChannel_8_new;
                    bsChannel_9_added = bsChannel_9_new;
                    bsChannel_10_added = bsChannel_10_new;
                    bsChannel_11_added = bsChannel_11_new;
                    bsChannel_12_added = bsChannel_12_new;
                    bsChannel_13_added = bsChannel_13_new;
                    bsChannel_14_added = bsChannel_14_new;
                    bsChannel_15_added = bsChannel_15_new;
                    bsChannel_16_added = bsChannel_16_new;
                }
            bscalculateincrements();

            ///moved
            Timer1.Start(bsbeattime,false);

            // moved Timer1.Start(beattime,false);
            //beat = 0;
            //beatcounter();
            beat++;
            //beatcounter();
            if (beat > lastbeat) beat = 1;
            }
///end activate timer code

}



BlinkSequencer::~BlinkSequencer()
{
	//(*Destroy(BlinkSequencer)
	//*)
}

void BlinkSequencer::changebeat()
{

 	if (Choice1->GetSelection() == 0){lastbeat = 2;beat = 1;e3=false;e4=false;e5=false;e6=false;e7=false;e8=false;e9=false;e10=false;e11=false;e12=false;}
 	if (Choice1->GetSelection() == 1){lastbeat = 3;beat = 1;e3=true;e4=false;e5=false;e6=false;e7=false;e8=false;e9=false;e10=false;e11=false;e12=false;}
 	if (Choice1->GetSelection() == 2){lastbeat = 4;beat = 1;e3=true;e4=true;e5=false;e6=false;e7=false;e8=false;e9=false;e10=false;e11=false;e12=false;}
 	if (Choice1->GetSelection() == 3){lastbeat = 5;beat = 1;e3=true;e4=true;e5=true;e6=false;e7=false;e8=false;e9=false;e10=false;e11=false;e12=false;}
 	if (Choice1->GetSelection() == 4){lastbeat = 6;beat = 1;e3=true;e4=true;e5=true;e6=true;e7=false;e8=false;e9=false;e10=false;e11=false;e12=false;}
 	if (Choice1->GetSelection() == 5){lastbeat = 7;beat = 1;e3=true;e4=true;e5=true;e6=true;e7=true;e8=false;e9=false;e10=false;e11=false;e12=false;}
 	if (Choice1->GetSelection() == 6){lastbeat = 8;beat = 1;e3=true;e4=true;e5=true;e6=true;e7=true;e8=true;e9=false;e10=false;e11=false;e12=false;}
 	if (Choice1->GetSelection() == 7){lastbeat = 9;beat = 1;e3=true;e4=true;e5=true;e6=true;e7=true;e8=true;e9=true;e10=false;e11=false;e12=false;}
 	if (Choice1->GetSelection() == 8){lastbeat = 10;beat = 1;e3=true;e4=true;e5=true;e6=true;e7=true;e8=true;e9=true;e10=true;e11=false;e12=false;}
 	if (Choice1->GetSelection() == 9){lastbeat = 11;beat = 1;e3=true;e4=true;e5=true;e6=true;e7=true;e8=true;e9=true;e10=true;e11=true;e12=false;}
 	if (Choice1->GetSelection() == 10){lastbeat = 12;beat = 1;e3=true;e4=true;e5=true;e6=true;e7=true;e8=true;e9=true;e10=true;e11=true;e12=true;}

    //wxString displayValue = wxString::Format(wxT("%i"),Choice1->GetSelection());
    //wxMessageBox ( displayValue, displayValue);

    StaticText3->Enable(e3);
    Slider3->Enable(e3);
    StaticText4->Enable(e4);
    Slider4->Enable(e4);
    StaticText5->Enable(e5);
    Slider5->Enable(e5);
    StaticText6->Enable(e6);;
    Slider6->Enable(e6);
    StaticText7->Enable(e7);
    Slider7->Enable(e7);
    StaticText8->Enable(e8);
    Slider8->Enable(e8);
    StaticText9->Enable(e9);
    Slider9->Enable(e9);
    StaticText10->Enable(e10);
    Slider10->Enable(e10);
    StaticText11->Enable(e11);
    Slider11->Enable(e11);
    StaticText12->Enable(e12);
    Slider12->Enable(e12);


    }

void BlinkSequencer::updatestartbeatbox(void)
{
    if (lastbeat == 2) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
    }

    if (lastbeat == 3) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
        Choice2->Append(_("3"));
    }

    if (lastbeat == 4) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
        Choice2->Append(_("3"));
        Choice2->Append(_("4"));
    }

    if (lastbeat == 5) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
        Choice2->Append(_("3"));
        Choice2->Append(_("4"));
        Choice2->Append(_("5"));
    }

    if (lastbeat == 6) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
        Choice2->Append(_("3"));
        Choice2->Append(_("4"));
        Choice2->Append(_("5"));
        Choice2->Append(_("6"));
    }

    if (lastbeat == 7) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
        Choice2->Append(_("3"));
        Choice2->Append(_("4"));
        Choice2->Append(_("5"));
        Choice2->Append(_("6"));
        Choice2->Append(_("7"));
    }

    if (lastbeat == 8) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
        Choice2->Append(_("3"));
        Choice2->Append(_("4"));
        Choice2->Append(_("5"));
        Choice2->Append(_("6"));
        Choice2->Append(_("7"));
        Choice2->Append(_("8"));
    }

    if (lastbeat == 9) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
        Choice2->Append(_("3"));
        Choice2->Append(_("4"));
        Choice2->Append(_("5"));
        Choice2->Append(_("6"));
        Choice2->Append(_("7"));
        Choice2->Append(_("8"));
        Choice2->Append(_("9"));
    }

    if (lastbeat == 10) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
        Choice2->Append(_("3"));
        Choice2->Append(_("4"));
        Choice2->Append(_("5"));
        Choice2->Append(_("6"));
        Choice2->Append(_("7"));
        Choice2->Append(_("8"));
        Choice2->Append(_("9"));
        Choice2->Append(_("10"));
    }

    if (lastbeat == 11) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
        Choice2->Append(_("3"));
        Choice2->Append(_("4"));
        Choice2->Append(_("5"));
        Choice2->Append(_("6"));
        Choice2->Append(_("7"));
        Choice2->Append(_("8"));
        Choice2->Append(_("9"));
        Choice2->Append(_("10"));
        Choice2->Append(_("11"));
    }


    if (lastbeat == 12) {
        Choice2->Clear();
        Choice2->SetSelection( Choice2->Append(_("1")) );
        Choice2->Append(_("2"));
        Choice2->Append(_("3"));
        Choice2->Append(_("4"));
        Choice2->Append(_("5"));
        Choice2->Append(_("6"));
        Choice2->Append(_("7"));
        Choice2->Append(_("8"));
        Choice2->Append(_("9"));
        Choice2->Append(_("10"));
        Choice2->Append(_("11"));
        Choice2->Append(_("12"));

}

}
//beats selector
void BlinkSequencer::OnChoice1Select(wxCommandEvent& event)
{
    changebeat();
    //commit changes to current profile
    SequencerBeats[ListBox1->GetSelection()+1] = Choice1->GetCurrentSelection();
    updatestartbeatbox();
    bsischanged = true;
}

//save button
void BlinkSequencer::OnButton1Click(wxCommandEvent& event)
{
}

//start/stop button button
void BlinkSequencer::OnButton5Click(wxCommandEvent& event)
{

///this corrects incorrect user input
    if ((SequencerTime [sequencercurrentprofile] < 60) || ((SequencerTime [sequencercurrentprofile] > 9999999))) {
         SequencerTime [sequencercurrentprofile] = 1000;
         TextCtrl1->SetValue(wxT("1000"));
    }

    if (Timer1.IsRunning() == false){
                Button5->SetLabel(wxT("Stop"));
                Button1->Enable(true);
                Choice1->Enable(false);
                TextCtrl1->Enable(false);
                ListBox1->Enable(false);
                CheckBox1->Enable(false);
                Choice2->Enable(false);

                Button2->Enable(false);
                Button3->Enable(false);
                Button4->Enable(false);
                Button6->Enable(false);
                Button7->Enable(false);
                Button9->Enable(false);

                //beattime = wxAtoi(TextCtrl1->GetValue());
                lastbeat = SequencerBeats [(ListBox1->GetSelection())+1];
                bsbeattime = SequencerTime[(ListBox1->GetSelection())+1];
                ///Timer1.Start(bsbeattime,false);
                //beat = 1;
                ispaused = false;
                changebeat();
                beat = Choice2->GetSelection()+1;


                beatcounter();

                if (!CheckBox2->IsChecked()) bsChannel_1_new = SequencerChannel_1 [ListBox1->GetSelection()] [beat];
                if (!CheckBox3->IsChecked()) bsChannel_2_new = SequencerChannel_2 [ListBox1->GetSelection()] [beat];
                if (!CheckBox4->IsChecked()) bsChannel_3_new = SequencerChannel_3 [ListBox1->GetSelection()] [beat];
                if (!CheckBox5->IsChecked()) bsChannel_4_new = SequencerChannel_4 [ListBox1->GetSelection()] [beat];
                if (!CheckBox6->IsChecked()) bsChannel_5_new = SequencerChannel_5 [ListBox1->GetSelection()] [beat];
                if (!CheckBox7->IsChecked()) bsChannel_6_new = SequencerChannel_6 [ListBox1->GetSelection()] [beat];
                if (!CheckBox8->IsChecked()) bsChannel_7_new = SequencerChannel_7 [ListBox1->GetSelection()] [beat];
                if (!CheckBox9->IsChecked()) bsChannel_8_new = SequencerChannel_8 [ListBox1->GetSelection()] [beat];
                if (!CheckBox10->IsChecked()) bsChannel_9_new = SequencerChannel_9 [ListBox1->GetSelection()] [beat];
                if (!CheckBox11->IsChecked()) bsChannel_10_new = SequencerChannel_10 [ListBox1->GetSelection()] [beat];
                if (!CheckBox12->IsChecked()) bsChannel_11_new = SequencerChannel_11 [ListBox1->GetSelection()] [beat];
                if (!CheckBox13->IsChecked()) bsChannel_12_new = SequencerChannel_12 [ListBox1->GetSelection()] [beat];
                if (!CheckBox14->IsChecked()) bsChannel_13_new = SequencerChannel_13 [ListBox1->GetSelection()] [beat];
                if (!CheckBox15->IsChecked()) bsChannel_14_new = SequencerChannel_14 [ListBox1->GetSelection()] [beat];
                if (!CheckBox16->IsChecked()) bsChannel_15_new = SequencerChannel_15 [ListBox1->GetSelection()] [beat];
                if (!CheckBox17->IsChecked()) bsChannel_16_new = SequencerChannel_16 [ListBox1->GetSelection()] [beat];

                if ((CheckBox1->GetValue())&&(RadioButton2->GetValue())){
                    //previous beat gets the right previous beat values for smooth start
                    if (beat == 1) previousbeat = lastbeat;
                    else previousbeat = beat - 1;

                    if (!CheckBox2->IsChecked()) {bsChannel_1_out = SequencerChannel_1 [ListBox1->GetSelection()] [previousbeat]; bsChannel_1_added = bsChannel_1_out;}
                    if (!CheckBox3->IsChecked()) {bsChannel_2_out = SequencerChannel_2 [ListBox1->GetSelection()] [previousbeat]; bsChannel_2_added = bsChannel_2_out;}
                    if (!CheckBox4->IsChecked()) {bsChannel_3_out = SequencerChannel_3 [ListBox1->GetSelection()] [previousbeat]; bsChannel_3_added = bsChannel_3_out;}
                    if (!CheckBox5->IsChecked()) {bsChannel_4_out = SequencerChannel_4 [ListBox1->GetSelection()] [previousbeat]; bsChannel_4_added = bsChannel_4_out;}
                    if (!CheckBox6->IsChecked()) {bsChannel_5_out = SequencerChannel_5 [ListBox1->GetSelection()] [previousbeat]; bsChannel_5_added = bsChannel_5_out;}
                    if (!CheckBox7->IsChecked()) {bsChannel_6_out = SequencerChannel_6 [ListBox1->GetSelection()] [previousbeat]; bsChannel_6_added = bsChannel_6_out;}
                    if (!CheckBox8->IsChecked()) {bsChannel_7_out = SequencerChannel_7 [ListBox1->GetSelection()] [previousbeat]; bsChannel_7_added = bsChannel_7_out;}
                    if (!CheckBox9->IsChecked()) {bsChannel_8_out = SequencerChannel_8 [ListBox1->GetSelection()] [previousbeat]; bsChannel_8_added = bsChannel_8_out;}
                    if (!CheckBox10->IsChecked()) {bsChannel_9_out = SequencerChannel_9 [ListBox1->GetSelection()] [previousbeat]; bsChannel_9_added = bsChannel_9_out;}
                    if (!CheckBox11->IsChecked()) {bsChannel_10_out = SequencerChannel_10 [ListBox1->GetSelection()] [previousbeat]; bsChannel_10_added = bsChannel_10_out;}
                    if (!CheckBox12->IsChecked()) {bsChannel_11_out = SequencerChannel_11 [ListBox1->GetSelection()] [previousbeat]; bsChannel_11_added = bsChannel_11_out;}
                    if (!CheckBox13->IsChecked()) {bsChannel_12_out = SequencerChannel_12 [ListBox1->GetSelection()] [previousbeat]; bsChannel_12_added = bsChannel_12_out;}
                    if (!CheckBox14->IsChecked()) {bsChannel_13_out = SequencerChannel_13 [ListBox1->GetSelection()] [previousbeat]; bsChannel_13_added = bsChannel_13_out;}
                    if (!CheckBox15->IsChecked()) {bsChannel_14_out = SequencerChannel_14 [ListBox1->GetSelection()] [previousbeat]; bsChannel_14_added = bsChannel_14_out;}
                    if (!CheckBox16->IsChecked()) {bsChannel_15_out = SequencerChannel_15 [ListBox1->GetSelection()] [previousbeat]; bsChannel_15_added = bsChannel_15_out;}
                    if (!CheckBox17->IsChecked()) {bsChannel_16_out = SequencerChannel_16 [ListBox1->GetSelection()] [previousbeat]; bsChannel_16_added = bsChannel_16_out;}

                }
                else {
                    bsChannel_1_out = bsChannel_1_new;
                    bsChannel_2_out = bsChannel_2_new;
                    bsChannel_3_out = bsChannel_3_new;
                    bsChannel_4_out = bsChannel_4_new;
                    bsChannel_5_out = bsChannel_5_new;
                    bsChannel_6_out = bsChannel_6_new;
                    bsChannel_7_out = bsChannel_7_new;
                    bsChannel_8_out = bsChannel_8_new;
                    bsChannel_9_out = bsChannel_9_new;
                    bsChannel_10_out = bsChannel_10_new;
                    bsChannel_11_out = bsChannel_11_new;
                    bsChannel_12_out = bsChannel_12_new;
                    bsChannel_13_out = bsChannel_13_new;
                    bsChannel_14_out = bsChannel_14_new;
                    bsChannel_15_out = bsChannel_15_new;
                    bsChannel_16_out = bsChannel_16_new;

                    bsChannel_1_added = bsChannel_1_new;
                    bsChannel_2_added = bsChannel_2_new;
                    bsChannel_3_added = bsChannel_3_new;
                    bsChannel_4_added = bsChannel_4_new;
                    bsChannel_5_added = bsChannel_5_new;
                    bsChannel_6_added = bsChannel_6_new;
                    bsChannel_7_added = bsChannel_7_new;
                    bsChannel_8_added = bsChannel_8_new;
                    bsChannel_9_added = bsChannel_9_new;
                    bsChannel_10_added = bsChannel_10_new;
                    bsChannel_11_added = bsChannel_11_new;
                    bsChannel_12_added = bsChannel_12_new;
                    bsChannel_13_added = bsChannel_13_new;
                    bsChannel_14_added = bsChannel_14_new;
                    bsChannel_15_added = bsChannel_15_new;
                    bsChannel_16_added = bsChannel_16_new;
                }
            bscalculateincrements();

            ///moved
            Timer1.Start(bsbeattime,false);

            // moved Timer1.Start(beattime,false);
            //beat = 0;
            //beatcounter();
            beat++;
            //beatcounter();
            if (beat > lastbeat) beat = 1;
            }
        else {
                Button5->SetLabel(wxT("Start"));
                Button1->Enable(false);
                Timer1.Stop();
                //isprogramstarted = false;

                bsChannel_1_out = bs_ProfileChannel_1;
                bsChannel_2_out = bs_ProfileChannel_2;
                bsChannel_3_out = bs_ProfileChannel_3;
                bsChannel_4_out = bs_ProfileChannel_4;
                bsChannel_5_out = bs_ProfileChannel_5;
                bsChannel_6_out = bs_ProfileChannel_6;
                bsChannel_7_out = bs_ProfileChannel_7;
                bsChannel_8_out = bs_ProfileChannel_8;
                bsChannel_9_out = bs_ProfileChannel_9;
                bsChannel_10_out = bs_ProfileChannel_10;
                bsChannel_11_out = bs_ProfileChannel_11;
                bsChannel_12_out = bs_ProfileChannel_12;
                bsChannel_13_out = bs_ProfileChannel_13;
                bsChannel_14_out = bs_ProfileChannel_14;
                bsChannel_15_out = bs_ProfileChannel_15;
                bsChannel_16_out = bs_ProfileChannel_16;
                bsChannel_1_new = bs_ProfileChannel_1;
                bsChannel_2_new = bs_ProfileChannel_2;
                bsChannel_3_new = bs_ProfileChannel_3;
                bsChannel_4_new = bs_ProfileChannel_4;
                bsChannel_5_new = bs_ProfileChannel_5;
                bsChannel_6_new = bs_ProfileChannel_6;
                bsChannel_7_new = bs_ProfileChannel_7;
                bsChannel_8_new = bs_ProfileChannel_8;
                bsChannel_9_new = bs_ProfileChannel_9;
                bsChannel_10_new = bs_ProfileChannel_10;
                bsChannel_11_new = bs_ProfileChannel_11;
                bsChannel_12_new = bs_ProfileChannel_12;
                bsChannel_13_new = bs_ProfileChannel_13;
                bsChannel_14_new = bs_ProfileChannel_14;
                bsChannel_15_new = bs_ProfileChannel_15;
                bsChannel_16_new = bs_ProfileChannel_16;

//these lines re-enable buttons, etc.
                Choice1->Enable(true);
                TextCtrl1->Enable(true);
                ListBox1->Enable(true);
                Choice2->Enable(true);

                Button2->Enable(true);
                Button3->Enable(true);
                Button4->Enable(true);
                Button6->Enable(true);
                Button7->Enable(true);
                Button9->Enable(true);
//these lines re-enable the DMX data labels and sliders that were disabled during play
                StaticText1->Enable(true);
                Slider1->Enable(true);
                StaticText17->Enable(true);
                StaticText2->Enable(true);
                Slider2->Enable(true);
                StaticText19->Enable(true);
                StaticText3->Enable(true);
                Slider3->Enable(true);
                StaticText20->Enable(true);
                StaticText4->Enable(true);
                Slider4->Enable(true);
                StaticText21->Enable(true);
                StaticText5->Enable(true);
                Slider5->Enable(true);
                StaticText22->Enable(true);
                StaticText6->Enable(true);
                Slider6->Enable(true);
                StaticText23->Enable(true);
                StaticText7->Enable(true);
                Slider7->Enable(true);
                StaticText24->Enable(true);
                StaticText8->Enable(true);
                Slider8->Enable(true);
                StaticText25->Enable(true);
                StaticText9->Enable(true);
                Slider9->Enable(true);
                StaticText26->Enable(true);
                StaticText10->Enable(true);
                Slider10->Enable(true);
                StaticText27->Enable(true);
                StaticText11->Enable(true);
                Slider11->Enable(true);
                StaticText28->Enable(true);
                StaticText12->Enable(true);
                Slider12->Enable(true);
                StaticText29->Enable(true);
//run changebeat to re-disable the labels and sliders that are supposed to be disabled
                changebeat();
                ispaused=false;
                //beattime = wxAtoi(TextCtrl1->GetValue());
                //Button1->SetLabel(wxT("Pause"));
                if (RadioButton2->GetValue()) CheckBox1->Enable(true);
    }
//if (beat == lastbeat) beat = 1;
}


//channel selector
void BlinkSequencer::OnChoice3Select(wxCommandEvent& event)
{
    updatechannels();
}


void BlinkSequencer::OnSlider1CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [1] = Slider1->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider1->GetValue()); StaticText17->SetLabel(displayValue);}
    //wxString displayValue = wxString::Format(wxT("%i"),SequencerSlider2Channel_1 [1]);
    //wxMessageBox ( displayValue, displayValue);
    bsischanged = true;
}

void BlinkSequencer::OnSlider2CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [2] = Slider2->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider2->GetValue()); StaticText19->SetLabel(displayValue);}
    bsischanged = true;
}

void BlinkSequencer::OnSlider3CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [3] = Slider3->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider3->GetValue()); StaticText20->SetLabel(displayValue);}
    bsischanged = true;
}

void BlinkSequencer::OnSlider4CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [4] = Slider4->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider4->GetValue()); StaticText21->SetLabel(displayValue);}
    bsischanged = true;
}


void BlinkSequencer::OnSlider5CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [5] = Slider5->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider5->GetValue()); StaticText22->SetLabel(displayValue);}
    bsischanged = true;
}

void BlinkSequencer::OnSlider6CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [6] = Slider6->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider6->GetValue()); StaticText23->SetLabel(displayValue);}
    bsischanged = true;
}

void BlinkSequencer::OnSlider7CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [7] = Slider7->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider7->GetValue()); StaticText24->SetLabel(displayValue);}
    bsischanged = true;
}

void BlinkSequencer::OnSlider8CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [8] = Slider8->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider8->GetValue()); StaticText25->SetLabel(displayValue);}
    bsischanged = true;
}

void BlinkSequencer::OnSlider9CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [9] = Slider9->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider9->GetValue()); StaticText26->SetLabel(displayValue);}
    bsischanged = true;
}

void BlinkSequencer::OnSlider10CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [10] = Slider10->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider10->GetValue()); StaticText27->SetLabel(displayValue);}
    bsischanged = true;
}


void BlinkSequencer::OnSlider11CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [11] = Slider11->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider11->GetValue()); StaticText28->SetLabel(displayValue);}
    bsischanged = true;
}

void BlinkSequencer::OnSlider12CmdScroll(wxScrollEvent& event)
{
    if (channel == 1) {SequencerChannel_1 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 2) {SequencerChannel_2 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 3) {SequencerChannel_3 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 4) {SequencerChannel_4 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 5) {SequencerChannel_5 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 6) {SequencerChannel_6 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 7) {SequencerChannel_7 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 8) {SequencerChannel_8 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 9) {SequencerChannel_9 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 10) {SequencerChannel_10 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 11) {SequencerChannel_11 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 12) {SequencerChannel_12 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 13) {SequencerChannel_13 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 14) {SequencerChannel_14 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 15) {SequencerChannel_15 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    if (channel == 16) {SequencerChannel_16 [ListBox1->GetSelection()] [12] = Slider12->GetValue(); displayValue = wxString::Format(wxT("%i"),Slider12->GetValue()); StaticText29->SetLabel(displayValue);}
    bsischanged = true;
}


void BlinkSequencer::OnTextCtrl1Text(wxCommandEvent& event)
{
    bsbeattime = wxAtoi(TextCtrl1->GetValue());
    /*convert wxstring time value to int
   // if (((beattime >= 20) && (beattime <= 9999999)))
//i don't know why its not !firstrunthrough, but whatever works...
    if ((!((beattime >= 60) && (beattime <= 9999999)))&&(firstrunthrough))
    wxMessageBox (wxT("Please enter a numeric value between 60 and 9999999 milliseconds"),
                  wxT("Error with millisecond value"));
    //else commit changes to current profile
    else*/
        comparevalue = SequencerTime[ListBox1->GetSelection()+1];
        SequencerTime[ListBox1->GetSelection()+1] = wxAtoi(TextCtrl1->GetValue());
        if (SequencerTime[ListBox1->GetSelection()+1] != comparevalue) bsischanged = true;
}

void BlinkSequencer::savenewprofile(void)

{

        wxTextFile spfile(blinksequencerfilename);
        wxChar padding = wxT('0');

        int count = 1;
        int currentprofile_save = 1;
        int currentlinenumber_save = 1;
        int totallinenumber_save = 1;
        //sets a wxChar to hold the comma to search for (used too be a comma)
        wxChar comma = wxT('!');
        //this condition checks if the file in question already exists
        if (spfile.Exists()) {
            sequencercurrentprofile = ListBox1->GetSelection();
            //this code grants access to variables in another file using a classs instance of
            //DeleteVerify, Dlg
            bsProfileOverwrite Dlg(0);
            //opens dialog
            Dlg.ShowModal();
            if (bsyesorno){

                wxString SequencerChannel_1_pad [64] [12];
                wxString SequencerChannel_1_padded [64] [12];
                wxString SequencerChannel_2_pad [64] [12];
                wxString SequencerChannel_2_padded [64] [12];
                wxString SequencerChannel_3_pad [64] [12];
                wxString SequencerChannel_3_padded [64] [12];
                wxString SequencerChannel_4_pad [64] [12];
                wxString SequencerChannel_4_padded [64] [12];
                wxString SequencerChannel_5_pad [64] [12];
                wxString SequencerChannel_5_padded [64] [12];
                wxString SequencerChannel_6_pad [64] [12];
                wxString SequencerChannel_6_padded [64] [12];
                wxString SequencerChannel_7_pad [64] [12];
                wxString SequencerChannel_7_padded [64] [12];
                wxString SequencerChannel_8_pad [64] [12];
                wxString SequencerChannel_8_padded [64] [12];
                wxString SequencerChannel_9_pad [64] [12];
                wxString SequencerChannel_9_padded [64] [12];
                wxString SequencerChannel_10_pad [64] [12];
                wxString SequencerChannel_10_padded [64] [12];
                wxString SequencerChannel_11_pad [64] [12];
                wxString SequencerChannel_11_padded [64] [12];
                wxString SequencerChannel_12_pad [64] [12];
                wxString SequencerChannel_12_padded [64] [12];
                wxString SequencerChannel_13_pad [64] [12];
                wxString SequencerChannel_13_padded [64] [12];
                wxString SequencerChannel_14_pad [64] [12];
                wxString SequencerChannel_14_padded [64] [12];
                wxString SequencerChannel_15_pad [64] [12];
                wxString SequencerChannel_15_padded [64] [12];
                wxString SequencerChannel_16_pad [64] [12];
                wxString SequencerChannel_16_padded [64] [12];

        //this while loop is run once here to gill the padded values, its seperate from the other
        //while loop with the same condition to isolate the numbering difference of the sequencer channel values
                while (bsnumberofprofiles >= currentprofile_save) {


                    //this code pads the value with leading zeros for proper data storage
                    //makes it easy to load if they all have the same number of characters

                    for (count = 1; count < 13; count++) {
                        SequencerChannel_1_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_1 [currentprofile_save-1][count]);
                        SequencerChannel_1_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_1_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_1_padded [currentprofile_save][count] = SequencerChannel_1_padded[currentprofile_save][count].substr( SequencerChannel_1_padded[currentprofile_save][count].length() - 3 );
                    }//close for
                    //channel _2
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_2_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_2 [currentprofile_save-1][count]);
                        SequencerChannel_2_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_2_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_2_padded [currentprofile_save][count] = SequencerChannel_2_padded[currentprofile_save][count].substr( SequencerChannel_2_padded[currentprofile_save][count].length() - 3 );
                    }//close for _2
                    //channel _3
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_3_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_3 [currentprofile_save-1][count]);
                        SequencerChannel_3_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_3_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_3_padded [currentprofile_save][count] = SequencerChannel_3_padded[currentprofile_save][count].substr( SequencerChannel_3_padded[currentprofile_save][count].length() - 3 );
                    }//close for
                    //channel _4
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_4_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_4 [currentprofile_save-1][count]);
                        SequencerChannel_4_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_4_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_4_padded [currentprofile_save][count] = SequencerChannel_4_padded[currentprofile_save][count].substr( SequencerChannel_4_padded[currentprofile_save][count].length() - 3 );
                    }//close for _4
                    //channel _5
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_5_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_5 [currentprofile_save-1][count]);
                        SequencerChannel_5_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_5_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_5_padded [currentprofile_save][count] = SequencerChannel_5_padded[currentprofile_save][count].substr( SequencerChannel_5_padded[currentprofile_save][count].length() - 3 );
                    }//close for _5
                    //channel _8
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_6_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_6 [currentprofile_save-1][count]);
                        SequencerChannel_6_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_6_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_6_padded [currentprofile_save][count] = SequencerChannel_6_padded[currentprofile_save][count].substr( SequencerChannel_6_padded[currentprofile_save][count].length() - 3 );
                    }//close for _6
                    //channel _7
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_7_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_7 [currentprofile_save-1][count]);
                        SequencerChannel_7_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_7_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_7_padded [currentprofile_save][count] = SequencerChannel_7_padded[currentprofile_save][count].substr( SequencerChannel_7_padded[currentprofile_save][count].length() - 3 );
                    }//close for _7
                    //channel _8
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_8_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_8 [currentprofile_save-1][count]);
                        SequencerChannel_8_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_8_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_8_padded [currentprofile_save][count] = SequencerChannel_8_padded[currentprofile_save][count].substr( SequencerChannel_8_padded[currentprofile_save][count].length() - 3 );
                    }//close for _8
                    //channel _9
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_9_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_9 [currentprofile_save-1][count]);
                        SequencerChannel_9_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_9_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_9_padded [currentprofile_save][count] = SequencerChannel_9_padded[currentprofile_save][count].substr( SequencerChannel_9_padded[currentprofile_save][count].length() - 3 );
                    }//close for _9
                    //channel _10
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_10_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_10 [currentprofile_save-1][count]);
                        SequencerChannel_10_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_10_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_10_padded [currentprofile_save][count] = SequencerChannel_10_padded[currentprofile_save][count].substr( SequencerChannel_10_padded[currentprofile_save][count].length() - 3 );
                    }//close for _10
                    //channel _11
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_11_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_11 [currentprofile_save-1][count]);
                        SequencerChannel_11_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_11_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_11_padded [currentprofile_save][count] = SequencerChannel_11_padded[currentprofile_save][count].substr( SequencerChannel_11_padded[currentprofile_save][count].length() - 3 );
                    }//close for _11
                    //channel _12
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_12_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_12 [currentprofile_save-1][count]);
                        SequencerChannel_12_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_12_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_12_padded [currentprofile_save][count] = SequencerChannel_12_padded[currentprofile_save][count].substr( SequencerChannel_12_padded[currentprofile_save][count].length() - 3 );
                    }//close for _12
                    //channel _13
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_13_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_13 [currentprofile_save-1][count]);
                        SequencerChannel_13_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_13_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_13_padded [currentprofile_save][count] = SequencerChannel_13_padded[currentprofile_save][count].substr( SequencerChannel_13_padded[currentprofile_save][count].length() - 3 );
                    }//close for _13
                    //channel _14
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_14_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_14 [currentprofile_save-1][count]);
                        SequencerChannel_14_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_14_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_14_padded [currentprofile_save][count] = SequencerChannel_14_padded[currentprofile_save][count].substr( SequencerChannel_14_padded[currentprofile_save][count].length() - 3 );
                    }//close for _14
                    //channel _15
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_15_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_15 [currentprofile_save-1][count]);
                        SequencerChannel_15_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_15_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_15_padded [currentprofile_save][count] = SequencerChannel_15_padded[currentprofile_save][count].substr( SequencerChannel_15_padded[currentprofile_save][count].length() - 3 );
                    }//close for _15
                    //channel _16
                    for (count = 1; count < 13; count++) {
                        SequencerChannel_16_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),SequencerChannel_16 [currentprofile_save-1][count]);
                        SequencerChannel_16_padded [currentprofile_save][count]= wxT("00") + SequencerChannel_16_pad [currentprofile_save][count];
                        //this line cuts off any characters past three
                        SequencerChannel_16_padded [currentprofile_save][count] = SequencerChannel_16_padded[currentprofile_save][count].substr( SequencerChannel_16_padded[currentprofile_save][count].length() - 3 );
                    }//close for
                currentprofile_save++;
                }//close while
                currentprofile_save = 1;

                while (bsnumberofprofiles >= currentprofile_save) {


                    //wxString test1 = wxT("test1");
                    //newfile [currentlinenumber_save] = test1;//SequencerProfileNames [currentprofile_save];
                    //spfile.AddLine(newfile [currentlinenumber_save], wxTextFileType_Dos);

                    //wxString test1 = wxT("test1");
                    buffer [currentlinenumber_save] = SequencerProfileNames [currentprofile_save];
                    spfile.AddLine(buffer[currentlinenumber_save++], wxTextFileType_Dos);
                    //totallinenumber_save++;
                    displayValue = wxString::Format(wxT("%i"),SequencerBeats [currentprofile_save]);
                    buffer [currentlinenumber_save] = displayValue;
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);


                    if ((SequencerTime [currentprofile_save] < 60) || ((SequencerTime [currentprofile_save] > 9999999))) SequencerTime [currentprofile_save] = 1000;

                    displayValue = wxString::Format(wxT("%i"),SequencerTime [currentprofile_save]);
                    buffer [currentlinenumber_save] = displayValue;
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);



                    ///converts exempt channel values into one string like 0000000000000000
                    displayValue = wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [0])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [1])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [2])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [3])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [4])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [5])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [6])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [7])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [8])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [9])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [10])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [11])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [12])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [13])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [14])
                        << wxString::Format(wxT("%i"),SequencerExemptChannels [currentprofile_save] [15]);

                    buffer [currentlinenumber_save] = displayValue;
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);




                    buffer [currentlinenumber_save] = SequencerChannel_1_padded [currentprofile_save][1] << comma
                        << SequencerChannel_1_padded [currentprofile_save][2] << comma
                        << SequencerChannel_1_padded [currentprofile_save][3] << comma
                        << SequencerChannel_1_padded [currentprofile_save][4] << comma
                        << SequencerChannel_1_padded [currentprofile_save][5] << comma
                        << SequencerChannel_1_padded [currentprofile_save][6] << comma
                        << SequencerChannel_1_padded [currentprofile_save][7] << comma
                        << SequencerChannel_1_padded [currentprofile_save][8] << comma
                        << SequencerChannel_1_padded [currentprofile_save][9] << comma
                        << SequencerChannel_1_padded [currentprofile_save][10] << comma
                        << SequencerChannel_1_padded [currentprofile_save][11] << comma
                        << SequencerChannel_1_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_2_padded [currentprofile_save][1] << comma
                        << SequencerChannel_2_padded [currentprofile_save][2] << comma
                        << SequencerChannel_2_padded [currentprofile_save][3] << comma
                        << SequencerChannel_2_padded [currentprofile_save][4] << comma
                        << SequencerChannel_2_padded [currentprofile_save][5] << comma
                        << SequencerChannel_2_padded [currentprofile_save][6] << comma
                        << SequencerChannel_2_padded [currentprofile_save][7] << comma
                        << SequencerChannel_2_padded [currentprofile_save][8] << comma
                        << SequencerChannel_2_padded [currentprofile_save][9] << comma
                        << SequencerChannel_2_padded [currentprofile_save][10] << comma
                        << SequencerChannel_2_padded [currentprofile_save][11] << comma
                        << SequencerChannel_2_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_3_padded [currentprofile_save][1] << comma
                        << SequencerChannel_3_padded [currentprofile_save][2] << comma
                        << SequencerChannel_3_padded [currentprofile_save][3] << comma
                        << SequencerChannel_3_padded [currentprofile_save][4] << comma
                        << SequencerChannel_3_padded [currentprofile_save][5] << comma
                        << SequencerChannel_3_padded [currentprofile_save][6] << comma
                        << SequencerChannel_3_padded [currentprofile_save][7] << comma
                        << SequencerChannel_3_padded [currentprofile_save][8] << comma
                        << SequencerChannel_3_padded [currentprofile_save][9] << comma
                        << SequencerChannel_3_padded [currentprofile_save][10] << comma
                        << SequencerChannel_3_padded [currentprofile_save][11] << comma
                        << SequencerChannel_3_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_4_padded [currentprofile_save][1] << comma
                        << SequencerChannel_4_padded [currentprofile_save][2] << comma
                        << SequencerChannel_4_padded [currentprofile_save][3] << comma
                        << SequencerChannel_4_padded [currentprofile_save][4] << comma
                        << SequencerChannel_4_padded [currentprofile_save][5] << comma
                        << SequencerChannel_4_padded [currentprofile_save][6] << comma
                        << SequencerChannel_4_padded [currentprofile_save][7] << comma
                        << SequencerChannel_4_padded [currentprofile_save][8] << comma
                        << SequencerChannel_4_padded [currentprofile_save][9] << comma
                        << SequencerChannel_4_padded [currentprofile_save][10] << comma
                        << SequencerChannel_4_padded [currentprofile_save][11] << comma
                        << SequencerChannel_4_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_5_padded [currentprofile_save][1] << comma
                        << SequencerChannel_5_padded [currentprofile_save][2] << comma
                        << SequencerChannel_5_padded [currentprofile_save][3] << comma
                        << SequencerChannel_5_padded [currentprofile_save][4] << comma
                        << SequencerChannel_5_padded [currentprofile_save][5] << comma
                        << SequencerChannel_5_padded [currentprofile_save][6] << comma
                        << SequencerChannel_5_padded [currentprofile_save][7] << comma
                        << SequencerChannel_5_padded [currentprofile_save][8] << comma
                        << SequencerChannel_5_padded [currentprofile_save][9] << comma
                        << SequencerChannel_5_padded [currentprofile_save][10] << comma
                        << SequencerChannel_5_padded [currentprofile_save][11] << comma
                        << SequencerChannel_5_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_6_padded [currentprofile_save][1] << comma
                        << SequencerChannel_6_padded [currentprofile_save][2] << comma
                        << SequencerChannel_6_padded [currentprofile_save][3] << comma
                        << SequencerChannel_6_padded [currentprofile_save][4] << comma
                        << SequencerChannel_6_padded [currentprofile_save][5] << comma
                        << SequencerChannel_6_padded [currentprofile_save][6] << comma
                        << SequencerChannel_6_padded [currentprofile_save][7] << comma
                        << SequencerChannel_6_padded [currentprofile_save][8] << comma
                        << SequencerChannel_6_padded [currentprofile_save][9] << comma
                        << SequencerChannel_6_padded [currentprofile_save][10] << comma
                        << SequencerChannel_6_padded [currentprofile_save][11] << comma
                        << SequencerChannel_6_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_7_padded [currentprofile_save][1] << comma
                        << SequencerChannel_7_padded [currentprofile_save][2] << comma
                        << SequencerChannel_7_padded [currentprofile_save][3] << comma
                        << SequencerChannel_7_padded [currentprofile_save][4] << comma
                        << SequencerChannel_7_padded [currentprofile_save][5] << comma
                        << SequencerChannel_7_padded [currentprofile_save][6] << comma
                        << SequencerChannel_7_padded [currentprofile_save][7] << comma
                        << SequencerChannel_7_padded [currentprofile_save][8] << comma
                        << SequencerChannel_7_padded [currentprofile_save][9] << comma
                        << SequencerChannel_7_padded [currentprofile_save][10] << comma
                        << SequencerChannel_7_padded [currentprofile_save][11] << comma
                        << SequencerChannel_7_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_8_padded [currentprofile_save][1] << comma
                        << SequencerChannel_8_padded [currentprofile_save][2] << comma
                        << SequencerChannel_8_padded [currentprofile_save][3] << comma
                        << SequencerChannel_8_padded [currentprofile_save][4] << comma
                        << SequencerChannel_8_padded [currentprofile_save][5] << comma
                        << SequencerChannel_8_padded [currentprofile_save][6] << comma
                        << SequencerChannel_8_padded [currentprofile_save][7] << comma
                        << SequencerChannel_8_padded [currentprofile_save][8] << comma
                        << SequencerChannel_8_padded [currentprofile_save][9] << comma
                        << SequencerChannel_8_padded [currentprofile_save][10] << comma
                        << SequencerChannel_8_padded [currentprofile_save][11] << comma
                        << SequencerChannel_8_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_9_padded [currentprofile_save][1] << comma
                        << SequencerChannel_9_padded [currentprofile_save][2] << comma
                        << SequencerChannel_9_padded [currentprofile_save][3] << comma
                        << SequencerChannel_9_padded [currentprofile_save][4] << comma
                        << SequencerChannel_9_padded [currentprofile_save][5] << comma
                        << SequencerChannel_9_padded [currentprofile_save][6] << comma
                        << SequencerChannel_9_padded [currentprofile_save][7] << comma
                        << SequencerChannel_9_padded [currentprofile_save][8] << comma
                        << SequencerChannel_9_padded [currentprofile_save][9] << comma
                        << SequencerChannel_9_padded [currentprofile_save][10] << comma
                        << SequencerChannel_9_padded [currentprofile_save][11] << comma
                        << SequencerChannel_9_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_10_padded [currentprofile_save][1] << comma
                        << SequencerChannel_10_padded [currentprofile_save][2] << comma
                        << SequencerChannel_10_padded [currentprofile_save][3] << comma
                        << SequencerChannel_10_padded [currentprofile_save][4] << comma
                        << SequencerChannel_10_padded [currentprofile_save][5] << comma
                        << SequencerChannel_10_padded [currentprofile_save][6] << comma
                        << SequencerChannel_10_padded [currentprofile_save][7] << comma
                        << SequencerChannel_10_padded [currentprofile_save][8] << comma
                        << SequencerChannel_10_padded [currentprofile_save][9] << comma
                        << SequencerChannel_10_padded [currentprofile_save][10] << comma
                        << SequencerChannel_10_padded [currentprofile_save][11] << comma
                        << SequencerChannel_10_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_11_padded [currentprofile_save][1] << comma
                        << SequencerChannel_11_padded [currentprofile_save][2] << comma
                        << SequencerChannel_11_padded [currentprofile_save][3] << comma
                        << SequencerChannel_11_padded [currentprofile_save][4] << comma
                        << SequencerChannel_11_padded [currentprofile_save][5] << comma
                        << SequencerChannel_11_padded [currentprofile_save][6] << comma
                        << SequencerChannel_11_padded [currentprofile_save][7] << comma
                        << SequencerChannel_11_padded [currentprofile_save][8] << comma
                        << SequencerChannel_11_padded [currentprofile_save][9] << comma
                        << SequencerChannel_11_padded [currentprofile_save][10] << comma
                        << SequencerChannel_11_padded [currentprofile_save][11] << comma
                        << SequencerChannel_11_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_12_padded [currentprofile_save][1] << comma
                        << SequencerChannel_12_padded [currentprofile_save][2] << comma
                        << SequencerChannel_12_padded [currentprofile_save][3] << comma
                        << SequencerChannel_12_padded [currentprofile_save][4] << comma
                        << SequencerChannel_12_padded [currentprofile_save][5] << comma
                        << SequencerChannel_12_padded [currentprofile_save][6] << comma
                        << SequencerChannel_12_padded [currentprofile_save][7] << comma
                        << SequencerChannel_12_padded [currentprofile_save][8] << comma
                        << SequencerChannel_12_padded [currentprofile_save][9] << comma
                        << SequencerChannel_12_padded [currentprofile_save][10] << comma
                        << SequencerChannel_12_padded [currentprofile_save][11] << comma
                        << SequencerChannel_12_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_13_padded [currentprofile_save][1] << comma
                        << SequencerChannel_13_padded [currentprofile_save][2] << comma
                        << SequencerChannel_13_padded [currentprofile_save][3] << comma
                        << SequencerChannel_13_padded [currentprofile_save][4] << comma
                        << SequencerChannel_13_padded [currentprofile_save][5] << comma
                        << SequencerChannel_13_padded [currentprofile_save][6] << comma
                        << SequencerChannel_13_padded [currentprofile_save][7] << comma
                        << SequencerChannel_13_padded [currentprofile_save][8] << comma
                        << SequencerChannel_13_padded [currentprofile_save][9] << comma
                        << SequencerChannel_13_padded [currentprofile_save][10] << comma
                        << SequencerChannel_13_padded [currentprofile_save][11] << comma
                        << SequencerChannel_13_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_14_padded [currentprofile_save][1] << comma
                        << SequencerChannel_14_padded [currentprofile_save][2] << comma
                        << SequencerChannel_14_padded [currentprofile_save][3] << comma
                        << SequencerChannel_14_padded [currentprofile_save][4] << comma
                        << SequencerChannel_14_padded [currentprofile_save][5] << comma
                        << SequencerChannel_14_padded [currentprofile_save][6] << comma
                        << SequencerChannel_14_padded [currentprofile_save][7] << comma
                        << SequencerChannel_14_padded [currentprofile_save][8] << comma
                        << SequencerChannel_14_padded [currentprofile_save][9] << comma
                        << SequencerChannel_14_padded [currentprofile_save][10] << comma
                        << SequencerChannel_14_padded [currentprofile_save][11] << comma
                        << SequencerChannel_14_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_15_padded [currentprofile_save][1] << comma
                        << SequencerChannel_15_padded [currentprofile_save][2] << comma
                        << SequencerChannel_15_padded [currentprofile_save][3] << comma
                        << SequencerChannel_15_padded [currentprofile_save][4] << comma
                        << SequencerChannel_15_padded [currentprofile_save][5] << comma
                        << SequencerChannel_15_padded [currentprofile_save][6] << comma
                        << SequencerChannel_15_padded [currentprofile_save][7] << comma
                        << SequencerChannel_15_padded [currentprofile_save][8] << comma
                        << SequencerChannel_15_padded [currentprofile_save][9] << comma
                        << SequencerChannel_15_padded [currentprofile_save][10] << comma
                        << SequencerChannel_15_padded [currentprofile_save][11] << comma
                        << SequencerChannel_15_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    buffer [currentlinenumber_save] = SequencerChannel_16_padded [currentprofile_save][1] << comma
                        << SequencerChannel_16_padded [currentprofile_save][2] << comma
                        << SequencerChannel_16_padded [currentprofile_save][3] << comma
                        << SequencerChannel_16_padded [currentprofile_save][4] << comma
                        << SequencerChannel_16_padded [currentprofile_save][5] << comma
                        << SequencerChannel_16_padded [currentprofile_save][6] << comma
                        << SequencerChannel_16_padded [currentprofile_save][7] << comma
                        << SequencerChannel_16_padded [currentprofile_save][8] << comma
                        << SequencerChannel_16_padded [currentprofile_save][9] << comma
                        << SequencerChannel_16_padded [currentprofile_save][10] << comma
                        << SequencerChannel_16_padded [currentprofile_save][11] << comma
                        << SequencerChannel_16_padded [currentprofile_save][12];
                    spfile.AddLine(buffer [currentlinenumber_save++], wxTextFileType_Dos);

                    currentprofile_save++;

                }
                spfile.Write(wxTextFileType_Dos, wxConvISO8859_1);
                spfile.Close();
                spfile.Create(blinksequencerfilename);
                }
            }





}

void BlinkSequencer::loadprofiles(void)
{
wxTextFile bsfile;
bsfile.Clear();
bsfile.Open(blinksequencerfilename, wxConvISO8859_1);
//this line checks if the FILE HAS 3 LINES OR LESS, indicationg that there are no profiles
//then returns out of the profile loading function

//new idea, get line count, divide by 19, thats number of profiles
//subtract 1 from the line count to fix loading bug
int numberoflines = bsfile.GetLineCount() ;
//add 1 to the value to fix the assignment of bsnumberofprofiles
bsnumberofprofiles = (numberoflines + 1) / 20;

    //wxString displayValue = wxString::Format(wxT("%i"),numberoflines);
    //wxMessageBox ( displayValue, displayValue);

if (bsfile.GetLineCount() <= 3)return;

int namepos = 1;
ListBox1->Clear();
pos = 2;
postimes = 0;
int intbuffer;
wxString exemptchannels;
int exemptchannelspos;

//count starts at 2 because the getfirstline function before the do loop gets the first count
int count = 2;
//needed to use the getfirstline function, so i did this
    buffer [1] = bsfile.GetFirstLine();
    ListBox1->Append(buffer [1]);
    SequencerProfileNames [1] = buffer [1];

//this code is less than perfect, this do loop puts all the values from the saved proflie file
//into a buffer, as well as puts the name value, number of beats value, and time value
//into SequencerPrrofileNames, SequencerBeats, and SequencerTime for using and saving later
do {

    buffer [pos + (postimes * 20)] = bsfile.GetNextLine();

    ///the if pos == 1 condition checks and handles the profile name being loaded
    if (pos == 1) {ListBox1->Append(buffer [pos + (postimes * 20)]); SequencerProfileNames [namepos] = buffer [pos + (postimes * 20)];}
    ///the if pos == 2 condition checks and handles the number of beats for the profile being loaded
    if (pos == 2) {Choice1->SetSelection(wxAtoi(buffer [((postimes * 20) + 2)])); SequencerBeats [namepos] = wxAtoi(buffer [((postimes * 20) + 2)]);}
    ///the if pos == 3 condition checks and handles the time per beat of the profilebeing loaded
    if (pos == 3) {TextCtrl1->SetValue(buffer [((postimes * 20) + 3)]); SequencerTime [namepos] = wxAtoi(buffer [((postimes * 20) + 3)]); namepos++;}
    ///the if pos == 4 condition checks and handles the exempt channels of the profile being loaded
    if (pos == 4)
        {
           exemptchannels = buffer [((postimes * 20) + 4)];
           wxString tvalue;

           for (exemptchannelspos = 0; exemptchannelspos < 16 ; exemptchannelspos++)
           {
               tvalue = exemptchannels [exemptchannelspos];
               //namepos-1 fixes loading error
               SequencerExemptChannels [namepos-1] [exemptchannelspos] = wxAtoi(tvalue);
           }
        }

    pos++;

    //the if in the next line fixes the problem with the last profile not loading properly
    if (count < numberoflines)count++;
    //the nested, 2nd if in the next line fixes the problem with the last profile not loading properly also
    if (pos == 21) {pos=1;postimes++;if (count == numberoflines)count++;}
    //those other lines above make sure this while condition stays met untill after
    //the last line of the last profile loads
} while (count <= numberoflines);


    //int selection = ListBox1->GetSelection();
    wxString DMXbuffer;
    int pos = 0;
    // vpos holds the beat posirtion
    int vpos = 1;
    count = 0;
    //this next line gets the number of profiles by dividing the number of lines in
    //the save file by 19, the number of lines each profile takes.
    profilecount = (numberoflines / 20);
    int profilepos = 0;


//this do loop decodes the lines that hold the DMX values per beat (separated by !'s)
//note it does not search for ! it knows the numbers of spaces to travel
//must save profile with leading 0's

do {
    pos = 0;
    vpos = 1;
//channel 1
    //this multiplies the selection of the listbox by 19 and adds 4 to be at the first DMX value of the selected profile
    wxString udbuffer = buffer [((profilepos * 20) +5)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_1 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;

//channel 2
    } while (vpos < 13);
    vpos = 1;
    pos = 0;

    udbuffer = buffer [((profilepos * 20) +6)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_2 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 3
    udbuffer = buffer [((profilepos * 20) +7)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_3 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 4
    udbuffer = buffer [((profilepos * 20) +8)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_4 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 5
    udbuffer = buffer [((profilepos * 20) +9)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_5 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 6
    udbuffer = buffer [((profilepos * 20) +10)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_6 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 7
    udbuffer = buffer [((profilepos * 20) +11)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_7 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 8
    udbuffer = buffer [((profilepos * 20) +12)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_8 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 9
    udbuffer = buffer [((profilepos * 20) +13)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_9 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 10
    udbuffer = buffer [((profilepos * 20) +14)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_10 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 11
    udbuffer = buffer [((profilepos * 20) +15)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_11 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 12
    udbuffer = buffer [((profilepos * 20) +16)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_12 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 13
    udbuffer = buffer [((profilepos * 20) +17)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_13 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 14
    udbuffer = buffer [((profilepos * 20) +18)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_14 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 15
    udbuffer = buffer [((profilepos * 20) +19)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
            count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_15 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    vpos = 1;
    pos = 0;
//channel 16
    udbuffer = buffer [((profilepos * 20) +20)];
    do{
        DMXbuffer.clear();
        do {
            //this is where the error occurs, on the 1st time around the do loop
            DMXbuffer = DMXbuffer + udbuffer [pos];
            pos++;
           count++;
        } while (count < 3);
        count = 0;
        SequencerChannel_16 [profilepos] [vpos] = wxAtoi(DMXbuffer);
        pos++;
        vpos++;
    } while (vpos < 13);
    profilepos++;
}while (profilecount >= profilepos);



ListBox1->SetSelection(0);
updateprofile();


}



void BlinkSequencer::updateprofile (void)
{
/*
    Choice1->SetSelection(SequencerBeats[ListBox1->GetSelection()+1]);

    wxString convertValue = wxString::Format(wxT("%i"),SequencerTime[ListBox1->GetSelection()+1]);
    TextCtrl1->SetValue(convertValue);

    sequencercurrentprofile = ListBox1->GetSelection()+1;
*/

    Choice1->SetSelection(SequencerBeats[ListBox1->GetSelection()]);

    wxString convertValue = wxString::Format(wxT("%i"),SequencerTime[ListBox1->GetSelection()]);
    TextCtrl1->SetValue(convertValue);

    sequencercurrentprofile = ListBox1->GetSelection();

    if (SequencerExemptChannels [sequencercurrentprofile][0] == true) CheckBox2->SetValue(true);
    else CheckBox2->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][1] == true) CheckBox3->SetValue(true);
    else CheckBox3->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][2] == true) CheckBox4->SetValue(true);
    else CheckBox4->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][3] == true) CheckBox5->SetValue(true);
    else CheckBox5->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][4] == true) CheckBox6->SetValue(true);
    else CheckBox6->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][5] == true) CheckBox7->SetValue(true);
    else CheckBox7->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][6] == true) CheckBox8->SetValue(true);
    else CheckBox8->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][7] == true) CheckBox9->SetValue(true);
    else CheckBox9->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][8] == true) CheckBox10->SetValue(true);
    else CheckBox10->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][9] == true) CheckBox11->SetValue(true);
    else CheckBox11->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][10] == true) CheckBox12->SetValue(true);
    else CheckBox12->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][11] == true) CheckBox13->SetValue(true);
    else CheckBox13->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][12] == true) CheckBox14->SetValue(true);
    else CheckBox14->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][13] == true) CheckBox15->SetValue(true);
    else CheckBox15->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][14] == true) CheckBox16->SetValue(true);
    else CheckBox16->SetValue(false);
    if (SequencerExemptChannels [sequencercurrentprofile][15] == true) CheckBox17->SetValue(true);
    else CheckBox17->SetValue(false);

/*
    lastbeat = SequencerBeats [(ListBox1->GetSelection())+1];
    bsbeattime = SequencerTime[(ListBox1->GetSelection())+1];
*/


    lastbeat = SequencerBeats [(ListBox1->GetSelection())];
    bsbeattime = SequencerTime[(ListBox1->GetSelection())];


    updatechannels();
    changebeat();
    updatelabels();
    //updatestartbeatbox();
/*
    wxString displayValue = wxString::Format(wxT("%i"),SequencerExemptChannels [ListBox1->GetSelection()+1][0]);
    wxMessageBox(wxT("Channel 1"),displayValue);
    displayValue = wxString::Format(wxT("%i"),SequencerExemptChannels [ListBox1->GetSelection()+1][1]);
    wxMessageBox(wxT("Channel 2"),displayValue);
    displayValue = wxString::Format(wxT("%i"),SequencerExemptChannels [ListBox1->GetSelection()+1][2]);
    wxMessageBox(wxT("Channel 3"),displayValue);
    displayValue = wxString::Format(wxT("%i"),SequencerExemptChannels [ListBox1->GetSelection()+1][3]);
    wxMessageBox(wxT("Channel 4"),displayValue);
*/
}

void BlinkSequencer::OnClose(wxCloseEvent& event)
{
    bscancel = false;
    if (Timer1.IsRunning() == true){wxMessageBox(wxT("Please stop the blink sequencer before exiting."),wxT("Stop the blink sequencer"));return;}
    else {

        if (bsischanged) savenewprofile();

        if (!bscancel) Destroy();
        }
}



void BlinkSequencer::OnListBox1Select(wxCommandEvent& event)
{
  updateprofile();
  updatestartbeatbox();

}


void BlinkSequencer::updatechannels(void)
{
    channel = Choice3->GetSelection() + 1;
    if (channel == 1) {
        Slider1->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_1 [ListBox1->GetSelection()] [12]);
    }
    if (channel == 2) {
        Slider1->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_2 [ListBox1->GetSelection()] [12]);
    }
        if (channel == 3) {
        Slider1->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_3 [ListBox1->GetSelection()] [12]);
    }
        if (channel == 4) {
        Slider1->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_4 [ListBox1->GetSelection()] [12]);
    }
    if (channel == 5) {
        Slider1->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_5 [ListBox1->GetSelection()] [12]);
    }
    if (channel == 6) {
        Slider1->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_6 [ListBox1->GetSelection()] [12]);
    }
        if (channel == 7) {
        Slider1->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_7 [ListBox1->GetSelection()] [12]);
    }
        if (channel == 8) {
        Slider1->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_8 [ListBox1->GetSelection()] [12]);
    }
        if (channel == 9) {
        Slider1->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_9 [ListBox1->GetSelection()] [12]);
    }
    if (channel == 10) {
        Slider1->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_10 [ListBox1->GetSelection()] [12]);
    }
        if (channel == 11) {
        Slider1->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_11 [ListBox1->GetSelection()] [12]);
    }
        if (channel == 12) {
        Slider1->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_12 [ListBox1->GetSelection()] [12]);
    }
        if (channel == 13) {
        Slider1->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_13 [ListBox1->GetSelection()] [12]);
    }
    if (channel == 14) {
        Slider1->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_14 [ListBox1->GetSelection()] [12]);
    }
        if (channel == 15) {
        Slider1->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_15 [ListBox1->GetSelection()] [12]);
    }
        if (channel == 16) {
        Slider1->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [1]);
        Slider2->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [2]);
        Slider3->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [3]);
        Slider4->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [4]);
        Slider5->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [5]);
        Slider6->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [6]);
        Slider7->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [7]);
        Slider8->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [8]);
        Slider9->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [9]);
        Slider10->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [10]);
        Slider11->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [11]);
        Slider12->SetValue(SequencerChannel_16 [ListBox1->GetSelection()] [12]);


        //wxString displayValue = wxString::Format(wxT("%i"),SequencerChannel_16 [ListBox1->GetSelection()][4]);
        //wxMessageBox ( displayValue, displayValue);
    }
    updatelabels();
}

void BlinkSequencer::OnTimer1Trigger(wxTimerEvent& event)
{
   // pausehandler();

     if (beat > lastbeat) beat = 1;
     if (!ispaused) beatcounter();

    if (!CheckBox2->IsChecked()) bsChannel_1_new = SequencerChannel_1 [ListBox1->GetSelection()] [beat];
    else bsChannel_1_new = bs_ProfileChannel_1;
    if (!CheckBox3->IsChecked()) bsChannel_2_new = SequencerChannel_2 [ListBox1->GetSelection()] [beat];
    else bsChannel_2_new = bs_ProfileChannel_2;
    if (!CheckBox4->IsChecked()) bsChannel_3_new = SequencerChannel_3 [ListBox1->GetSelection()] [beat];
    else bsChannel_3_new = bs_ProfileChannel_3;
    if (!CheckBox5->IsChecked()) bsChannel_4_new = SequencerChannel_4 [ListBox1->GetSelection()] [beat];
    else bsChannel_4_new = bs_ProfileChannel_4;
    if (!CheckBox6->IsChecked()) bsChannel_5_new = SequencerChannel_5 [ListBox1->GetSelection()] [beat];
    else bsChannel_5_new = bs_ProfileChannel_5;
    if (!CheckBox7->IsChecked()) bsChannel_6_new = SequencerChannel_6 [ListBox1->GetSelection()] [beat];
    else bsChannel_6_new = bs_ProfileChannel_6;
    if (!CheckBox8->IsChecked()) bsChannel_7_new = SequencerChannel_7 [ListBox1->GetSelection()] [beat];
    else bsChannel_7_new = bs_ProfileChannel_7;
    if (!CheckBox9->IsChecked()) bsChannel_8_new = SequencerChannel_8 [ListBox1->GetSelection()] [beat];
    else bsChannel_8_new = bs_ProfileChannel_8;
    if (!CheckBox10->IsChecked()) bsChannel_9_new = SequencerChannel_9 [ListBox1->GetSelection()] [beat];
    else bsChannel_9_new = bs_ProfileChannel_9;
    if (!CheckBox11->IsChecked()) bsChannel_10_new = SequencerChannel_10 [ListBox1->GetSelection()] [beat];
    else bsChannel_10_new = bs_ProfileChannel_10;
    if (!CheckBox12->IsChecked()) bsChannel_11_new = SequencerChannel_11 [ListBox1->GetSelection()] [beat];
    else bsChannel_11_new = bs_ProfileChannel_11;
    if (!CheckBox13->IsChecked()) bsChannel_12_new = SequencerChannel_12 [ListBox1->GetSelection()] [beat];
    else bsChannel_12_new = bs_ProfileChannel_12;
    if (!CheckBox14->IsChecked()) bsChannel_13_new = SequencerChannel_13 [ListBox1->GetSelection()] [beat];
    else bsChannel_13_new = bs_ProfileChannel_13;
    if (!CheckBox15->IsChecked()) bsChannel_14_new = SequencerChannel_14 [ListBox1->GetSelection()] [beat];
    else bsChannel_14_new = bs_ProfileChannel_14;
    if (!CheckBox16->IsChecked()) bsChannel_15_new = SequencerChannel_15 [ListBox1->GetSelection()] [beat];
    else bsChannel_15_new = bs_ProfileChannel_15;
    if (!CheckBox17->IsChecked()) bsChannel_16_new = SequencerChannel_16 [ListBox1->GetSelection()] [beat];
    else bsChannel_16_new = bs_ProfileChannel_16;


if ((!issmooth)||(ispaused)) {

    bsChannel_1_out = bsChannel_1_new;
    bsChannel_2_out = bsChannel_2_new;
    bsChannel_3_out = bsChannel_3_new;
    bsChannel_4_out = bsChannel_4_new;
    bsChannel_5_out = bsChannel_5_new;
    bsChannel_6_out = bsChannel_6_new;
    bsChannel_7_out = bsChannel_7_new;
    bsChannel_8_out = bsChannel_8_new;
    bsChannel_9_out = bsChannel_9_new;
    bsChannel_10_out = bsChannel_10_new;
    bsChannel_11_out = bsChannel_11_new;
    bsChannel_12_out = bsChannel_12_new;
    bsChannel_13_out = bsChannel_13_new;
    bsChannel_14_out = bsChannel_14_new;
    bsChannel_15_out = bsChannel_15_new;
    bsChannel_16_out = bsChannel_16_new;


}


    if(!ispaused) {
        bscalculateincrements();
        beatcounter();
        if (beat == lastbeat) beat = 0;
        beat++;
   }
}

void BlinkSequencer::bscalculateincrements(void)
//how the fuck this uses all subtraction of floats and actually works is beyond me...
{
           if (bsChannel_1_new > bsChannel_1_out) bsChannel_1_difference = bsChannel_1_new - bsChannel_1_out;
           if (bsChannel_1_new < bsChannel_1_out) bsChannel_1_difference = bsChannel_1_out - bsChannel_1_new;
           bsChannel_1_increment = bsChannel_1_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_2_new > bsChannel_2_out) bsChannel_2_difference = bsChannel_2_new - bsChannel_2_out;
           if (bsChannel_2_new < bsChannel_2_out) bsChannel_2_difference = bsChannel_2_out - bsChannel_2_new;
           bsChannel_2_increment = bsChannel_2_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_3_new > bsChannel_3_out) bsChannel_3_difference = bsChannel_3_new - bsChannel_3_out;
           if (bsChannel_3_new < bsChannel_3_out) bsChannel_3_difference = bsChannel_3_out - bsChannel_3_new;
           bsChannel_3_increment = bsChannel_3_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_4_new > bsChannel_4_out) bsChannel_4_difference = bsChannel_4_new - bsChannel_4_out;
           if (bsChannel_4_new < bsChannel_4_out) bsChannel_4_difference = bsChannel_4_out - bsChannel_4_new;
           bsChannel_4_increment = bsChannel_4_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_5_new > bsChannel_5_out) bsChannel_5_difference = bsChannel_5_new - bsChannel_5_out;
           if (bsChannel_5_new < bsChannel_5_out) bsChannel_5_difference = bsChannel_5_out - bsChannel_5_new;
           bsChannel_5_increment = bsChannel_5_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_6_new > bsChannel_6_out) bsChannel_6_difference = bsChannel_6_new - bsChannel_6_out;
           if (bsChannel_6_new < bsChannel_6_out) bsChannel_6_difference = bsChannel_6_out - bsChannel_6_new;
           bsChannel_6_increment = bsChannel_6_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_7_new > bsChannel_7_out) bsChannel_7_difference = bsChannel_7_new - bsChannel_7_out;
           if (bsChannel_7_new < bsChannel_7_out) bsChannel_7_difference = bsChannel_7_out - bsChannel_7_new;
           bsChannel_7_increment = bsChannel_7_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_8_new > bsChannel_8_out) bsChannel_8_difference = bsChannel_8_new - bsChannel_8_out;
           if (bsChannel_8_new < bsChannel_8_out) bsChannel_8_difference = bsChannel_8_out - bsChannel_8_new;
           bsChannel_8_increment = bsChannel_8_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_9_new > bsChannel_9_out) bsChannel_9_difference = bsChannel_9_new - bsChannel_9_out;
           if (bsChannel_9_new < bsChannel_9_out) bsChannel_9_difference = bsChannel_9_out - bsChannel_9_new;
           bsChannel_9_increment = bsChannel_9_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_10_new > bsChannel_10_out) bsChannel_10_difference = bsChannel_10_new - bsChannel_10_out;
           if (bsChannel_10_new < bsChannel_10_out) bsChannel_10_difference = bsChannel_10_out - bsChannel_10_new;
           bsChannel_10_increment = bsChannel_10_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_11_new > bsChannel_11_out) bsChannel_11_difference = bsChannel_11_new - bsChannel_11_out;
           if (bsChannel_11_new < bsChannel_11_out) bsChannel_11_difference = bsChannel_11_out - bsChannel_11_new;
           bsChannel_11_increment = bsChannel_11_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_12_new > bsChannel_12_out) bsChannel_12_difference = bsChannel_12_new - bsChannel_12_out;
           if (bsChannel_12_new < bsChannel_12_out) bsChannel_12_difference = bsChannel_12_out - bsChannel_12_new;
           bsChannel_12_increment = bsChannel_12_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_13_new > bsChannel_13_out) bsChannel_13_difference = bsChannel_13_new - bsChannel_13_out;
           if (bsChannel_13_new < bsChannel_13_out) bsChannel_13_difference = bsChannel_13_out - bsChannel_13_new;
           bsChannel_13_increment = bsChannel_13_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_14_new > bsChannel_14_out) bsChannel_14_difference = bsChannel_14_new - bsChannel_14_out;
           if (bsChannel_14_new < bsChannel_14_out) bsChannel_14_difference = bsChannel_14_out - bsChannel_14_new;
           bsChannel_14_increment = bsChannel_14_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_15_new > bsChannel_15_out) bsChannel_15_difference = bsChannel_15_new - bsChannel_15_out;
           if (bsChannel_15_new < bsChannel_15_out) bsChannel_15_difference = bsChannel_15_out - bsChannel_15_new;
           bsChannel_15_increment = bsChannel_15_difference / ((bsbeattime/LightputFrequency));

           if (bsChannel_16_new > bsChannel_16_out) bsChannel_16_difference = bsChannel_16_new - bsChannel_16_out;
           if (bsChannel_16_new < bsChannel_16_out) bsChannel_16_difference = bsChannel_16_out - bsChannel_16_new;
           bsChannel_16_increment = bsChannel_16_difference / ((bsbeattime/LightputFrequency));
}


void BlinkSequencer::beatcounter(void)
{
    StaticText1->Enable(false);
    Slider1->Enable(false);
    StaticText17->Enable(false);
    StaticText2->Enable(false);
    Slider2->Enable(false);
    StaticText19->Enable(false);
    StaticText3->Enable(false);
    Slider3->Enable(false);
    StaticText20->Enable(false);
    StaticText4->Enable(false);
    Slider4->Enable(false);
    StaticText21->Enable(false);
    StaticText5->Enable(false);
    Slider5->Enable(false);
    StaticText22->Enable(false);
    StaticText6->Enable(false);
    Slider6->Enable(false);
    StaticText23->Enable(false);
    StaticText7->Enable(false);
    Slider7->Enable(false);
    StaticText24->Enable(false);
    StaticText8->Enable(false);
    Slider8->Enable(false);
    StaticText25->Enable(false);
    StaticText9->Enable(false);
    Slider9->Enable(false);
    StaticText26->Enable(false);
    StaticText10->Enable(false);
    Slider10->Enable(false);
    StaticText27->Enable(false);
    StaticText11->Enable(false);
    Slider11->Enable(false);
    StaticText28->Enable(false);
    StaticText12->Enable(false);
    Slider12->Enable(false);
    StaticText29->Enable(false);



    if (beat == 1) {StaticText1->Enable(true); StaticText17->Enable(true); if (ispaused) Slider1->Enable(true);}
    if (beat == 2) {StaticText2->Enable(true); StaticText19->Enable(true); if (ispaused) Slider2->Enable(true);}
    if (beat == 3) {StaticText3->Enable(true); StaticText20->Enable(true); if (ispaused) Slider3->Enable(true);}
    if (beat == 4) {StaticText4->Enable(true); StaticText21->Enable(true); if (ispaused) Slider4->Enable(true);}
    if (beat == 5) {StaticText5->Enable(true); StaticText22->Enable(true); if (ispaused) Slider5->Enable(true);}
    if (beat == 6) {StaticText6->Enable(true); StaticText23->Enable(true); if (ispaused) Slider6->Enable(true);}
    if (beat == 7) {StaticText7->Enable(true); StaticText24->Enable(true); if (ispaused) Slider7->Enable(true);}
    if (beat == 8) {StaticText8->Enable(true); StaticText25->Enable(true); if (ispaused) Slider8->Enable(true);}
    if (beat == 9) {StaticText9->Enable(true); StaticText26->Enable(true); if (ispaused) Slider9->Enable(true);}
    if (beat == 10) {StaticText10->Enable(true); StaticText27->Enable(true); if (ispaused) Slider10->Enable(true);}
    if (beat == 11) {StaticText11->Enable(true); StaticText28->Enable(true); if (ispaused) Slider11->Enable(true);}
    if (beat == 12) {StaticText12->Enable(true); StaticText29->Enable(true); if (ispaused) Slider12->Enable(true);}



    //changebeat();

}

//new profile button
void BlinkSequencer::OnButton2Click(wxCommandEvent& event)
{
    if (bsnumberofprofiles == 63){
        wxMessageBox (wxT("You have reached the maximum amount of light sequences currently available by Lightput. You will have to delete a sequence to make a new one."),wxT("Too Many Profiles"));
        return;
    }


    bsAddNewProfile Dlg(0);
    //opens dialog
    Dlg.ShowModal();

    bsnewprofileValue = Dlg.TextCtrl1->GetValue();
    if (bsyesorno) {
//add new profile name to the bottom of the profile list
        if (bsnumberofprofiles == 0) ListBox1->Clear();
        ListBox1->SetSelection(ListBox1->Append(bsnewprofileValue));
//setup new profile
        sequencercurrentprofile = ListBox1->GetSelection() + 1;
        SequencerProfileNames [sequencercurrentprofile] = bsnewprofileValue;
        SequencerBeats [sequencercurrentprofile] = 0;
        SequencerTime [sequencercurrentprofile] = 3000;
        for (int i = 1; i < 13; i++) {
            SequencerChannel_1 [sequencercurrentprofile-1] [i] = 0;
            SequencerChannel_2 [sequencercurrentprofile-1] [i] = 0;
            SequencerChannel_3 [sequencercurrentprofile-1] [i] = 0;
            SequencerChannel_4 [sequencercurrentprofile-1] [i] = 0;
            SequencerChannel_5 [sequencercurrentprofile-1] [i] = 0;
            SequencerChannel_6 [sequencercurrentprofile-1] [i] = 0;
            SequencerChannel_7 [sequencercurrentprofile-1] [i] = 0;
            SequencerChannel_8 [sequencercurrentprofile] [i] = 0;
            SequencerChannel_9 [sequencercurrentprofile] [i] = 0;
            SequencerChannel_10 [sequencercurrentprofile] [i] = 0;
            SequencerChannel_11 [sequencercurrentprofile] [i] = 0;
            SequencerChannel_12 [sequencercurrentprofile] [i] = 0;
            SequencerChannel_13 [sequencercurrentprofile] [i] = 0;
            SequencerChannel_14 [sequencercurrentprofile] [i] = 0;
            SequencerChannel_15 [sequencercurrentprofile] [i] = 0;
            SequencerChannel_16 [sequencercurrentprofile] [i] = 0;
        }

        CheckBox2->SetValue(false);
        CheckBox3->SetValue(false);
        CheckBox4->SetValue(false);
        CheckBox5->SetValue(false);
        CheckBox6->SetValue(false);
        CheckBox7->SetValue(false);
        CheckBox8->SetValue(false);
        CheckBox9->SetValue(false);
        CheckBox10->SetValue(false);
        CheckBox11->SetValue(false);
        CheckBox12->SetValue(false);
        CheckBox13->SetValue(false);
        CheckBox14->SetValue(false);
        CheckBox15->SetValue(false);
        CheckBox16->SetValue(false);
        CheckBox17->SetValue(false);

        updateprofile();
        bsnumberofprofiles++;;
        bsischanged = true;
        bsyesorno = false;
    }

}

//move up button
void BlinkSequencer::OnButton6Click(wxCommandEvent& event)
{
    sequencercurrentprofile = (ListBox1->GetSelection());
    //this if condition makes sure there's somewhere to move the profile to
    if (sequencercurrentprofile > 0){

        wxString copyname;
        int copybeats;
        int copytime;
        bool copyexemptions [16];
        //initialised these as 15 instead of 12 because of bug
        int copyChannel_1 [15];
        int copyChannel_2 [15];
        int copyChannel_3 [15];
        int copyChannel_4 [15];
        int copyChannel_5 [15];
        int copyChannel_6 [15];
        int copyChannel_7 [15];
        int copyChannel_8 [15];
        int copyChannel_9 [15];
        int copyChannel_10 [15];
        int copyChannel_11 [15];
        int copyChannel_12 [15];
        int copyChannel_13 [15];
        int copyChannel_14 [15];
        int copyChannel_15 [15];
        int copyChannel_16 [15];

        //this code swaps the DMX data
        int copybeatcount;
        int copycount;


//this code swaps the order of the name variables in the SequencerProfileNames array
        //copy value into buffer (the value above the current profile to be moved down)
        copyname = SequencerProfileNames [sequencercurrentprofile];
        //copy over buffered value
        SequencerProfileNames [sequencercurrentprofile] = SequencerProfileNames [sequencercurrentprofile + 1];
        //copy buffered value to propper spot
        SequencerProfileNames [sequencercurrentprofile + 1] = copyname;

//this code swaps the order of the beats variables in the SequencerBeats array
        //copy value into buffer (the value above the current profile to be moved down)
        copybeats = SequencerBeats [sequencercurrentprofile];
        //copy over buffered value
        SequencerBeats [sequencercurrentprofile] = SequencerBeats [sequencercurrentprofile + 1];
        //copy buffered value to propper spot
        SequencerBeats [sequencercurrentprofile + 1] = copybeats;

//this code swaps the order of the time variables in the SequencerTime array
        //copy value into buffer (the value above the current profile to be moved down)
        copytime = SequencerTime [sequencercurrentprofile];
        //copy over buffered value
        SequencerTime [sequencercurrentprofile] = SequencerTime [sequencercurrentprofile + 1];
        //copy buffered value to propper spot
        SequencerTime [sequencercurrentprofile + 1] = copytime;


        for (int copyexemptionscount = 0; copyexemptionscount < 16; copyexemptionscount++)
        {
          copyexemptions [copyexemptionscount] = SequencerExemptChannels [sequencercurrentprofile][copyexemptionscount];
          SequencerExemptChannels [sequencercurrentprofile][copyexemptionscount] = SequencerExemptChannels [sequencercurrentprofile + 1][copyexemptionscount];
          SequencerExemptChannels [sequencercurrentprofile + 1][copyexemptionscount] = copyexemptions [copyexemptionscount];
        }

// this for loop swaps all the DMX data
for (copybeatcount = 1; copybeatcount < 13; copybeatcount++ )
        {
//displayValue = wxString::Format(wxT("%i"),SequencerChannel_1 [sequencercurrentprofile-1][copybeatcount]);
//wxMessageBox ( displayValue , wxT("sequencercurrentprofile"));
        //copy value into buffer the value above the current profile to be moved down
        copyChannel_1 [copybeatcount] = SequencerChannel_1 [sequencercurrentprofile-1][copybeatcount];

//displayValue = wxString::Format(wxT("%i"),SequencerChannel_1 [sequencercurrentprofile][copybeatcount]);
//wxMessageBox ( displayValue , wxT("sequencercurrentprofile"));

        //copy over buffered value
        SequencerChannel_1 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_1 [sequencercurrentprofile][copybeatcount];
        //copy buffered value to propper spot
        SequencerChannel_1 [sequencercurrentprofile][copybeatcount] = copyChannel_1 [copybeatcount];

//channel 2
        copyChannel_2 [copybeatcount] = SequencerChannel_2 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_2 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_2 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_2 [sequencercurrentprofile][copybeatcount] = copyChannel_2 [copybeatcount];
//channel 3
        copyChannel_3 [copybeatcount] = SequencerChannel_3 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_3 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_3 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_3 [sequencercurrentprofile][copybeatcount] = copyChannel_3 [copybeatcount];
//channel 4
        copyChannel_4 [copybeatcount] = SequencerChannel_4 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_4 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_4 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_4 [sequencercurrentprofile][copybeatcount] = copyChannel_4 [copybeatcount];
//Channel 5
        copyChannel_5 [copybeatcount] = SequencerChannel_5 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_5 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_5 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_5 [sequencercurrentprofile][copybeatcount] = copyChannel_5 [copybeatcount];
//channel 6
        copyChannel_6 [copybeatcount] = SequencerChannel_6 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_6 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_6 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_6 [sequencercurrentprofile][copybeatcount] = copyChannel_6 [copybeatcount];
//channel 7
        copyChannel_7 [copybeatcount] = SequencerChannel_7 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_7 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_7 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_7 [sequencercurrentprofile][copybeatcount] = copyChannel_7 [copybeatcount];
//channel 8
        copyChannel_8 [copybeatcount] = SequencerChannel_8 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_8 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_8 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_8 [sequencercurrentprofile][copybeatcount] = copyChannel_8 [copybeatcount];
//Channel 9
        copyChannel_9 [copybeatcount] = SequencerChannel_9 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_9 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_9 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_9 [sequencercurrentprofile][copybeatcount] = copyChannel_9 [copybeatcount];
//channel 10
        copyChannel_10 [copybeatcount] = SequencerChannel_10 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_10 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_10 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_10 [sequencercurrentprofile][copybeatcount] = copyChannel_10 [copybeatcount];
//channel 11
        copyChannel_11 [copybeatcount] = SequencerChannel_11 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_11 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_11 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_11 [sequencercurrentprofile][copybeatcount] = copyChannel_11 [copybeatcount];
//channel 12
        copyChannel_12 [copybeatcount] = SequencerChannel_12 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_12 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_12 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_12 [sequencercurrentprofile][copybeatcount] = copyChannel_12 [copybeatcount];
//Channel 13
        copyChannel_13 [copybeatcount] = SequencerChannel_13 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_13 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_13 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_13 [sequencercurrentprofile][copybeatcount] = copyChannel_13 [copybeatcount];
//channel 14
        copyChannel_14 [copybeatcount] = SequencerChannel_14 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_14 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_14 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_14 [sequencercurrentprofile][copybeatcount] = copyChannel_14 [copybeatcount];
//channel 15
        copyChannel_15 [copybeatcount] = SequencerChannel_15 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_15 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_15 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_15 [sequencercurrentprofile][copybeatcount] = copyChannel_15 [copybeatcount];
//Channel 16
        copyChannel_16 [copybeatcount] = SequencerChannel_16 [sequencercurrentprofile-1][copybeatcount];
        SequencerChannel_16 [sequencercurrentprofile-1][copybeatcount] = SequencerChannel_16 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_16 [sequencercurrentprofile][copybeatcount] = copyChannel_16 [copybeatcount];

    }//close for loop


//This code swaps the order of the profiles in the listbox

    //wxMessageBox ( SequencerProfileNames [0], wxT("0"));
    //wxMessageBox ( SequencerProfileNames [1], wxT("1"));
    //wxMessageBox ( SequencerProfileNames [2], wxT("2"));
    //wxMessageBox ( SequencerProfileNames [3], wxT("3"));


        //insert values in correct spot on listbox
        ListBox1->Insert(SequencerProfileNames [sequencercurrentprofile+1],sequencercurrentprofile);
        ListBox1->Insert(SequencerProfileNames [sequencercurrentprofile],sequencercurrentprofile-1);
        //delete the old listbox values
//this area also needed to be changed for linux

        //fix the "listbox delete" bug
        int holderforvaluethatgetsinadvertentlydeleted = sequencercurrentprofile;

        ListBox1->Delete(sequencercurrentprofile);

        //put the value back into sequencercurrentprofile
        sequencercurrentprofile = holderforvaluethatgetsinadvertentlydeleted;

        ListBox1->Delete(sequencercurrentprofile+1);

        //put the value back into sequencercurrentprofile again
        sequencercurrentprofile = holderforvaluethatgetsinadvertentlydeleted;


//set the listbox selection in the right spot
ListBox1->SetSelection(--sequencercurrentprofile);

//this line works in windows, fixes a problem in linux with the selection change
//if (ListBox1->GetSelection() == -1) ListBox1->SetSelection(sequencercurrentprofile);
updateprofile();

bsischanged = true;

    }
}



//move down button
void BlinkSequencer::OnButton7Click(wxCommandEvent& event)
{

        sequencercurrentprofile = (ListBox1->GetSelection());
    //this if condition makes sure there's somewhere to move the profile to
    if (sequencercurrentprofile < bsnumberofprofiles-1){

        wxString copyname;
        int copybeats;
        int copytime;
        bool copyexemptions [16];
        //initialised these as 15 instead of 12 because of bug
        int copyChannel_1 [15];
        int copyChannel_2 [15];
        int copyChannel_3 [15];
        int copyChannel_4 [15];
        int copyChannel_5 [15];
        int copyChannel_6 [15];
        int copyChannel_7 [15];
        int copyChannel_8 [15];
        int copyChannel_9 [15];
        int copyChannel_10 [15];
        int copyChannel_11 [15];
        int copyChannel_12 [15];
        int copyChannel_13 [15];
        int copyChannel_14 [15];
        int copyChannel_15 [15];
        int copyChannel_16 [15];

        //this code swaps the DMX data
        int copybeatcount;
        int copycount;


        copyname = SequencerProfileNames [sequencercurrentprofile+2];
        //copy over buffered value
        SequencerProfileNames [sequencercurrentprofile+2] = SequencerProfileNames [sequencercurrentprofile+1];
        //copy buffered value to propper spot
        SequencerProfileNames [sequencercurrentprofile+1] = copyname;

//this code swaps the order of the beats variables in the SequencerBeats array
        //copy value into buffer (the value above the current profile to be moved up)
        copybeats = SequencerBeats [sequencercurrentprofile+2];
        //copy over buffered value
        SequencerBeats [sequencercurrentprofile+2] = SequencerBeats [sequencercurrentprofile+1];
        //copy buffered value to propper spot
        SequencerBeats [sequencercurrentprofile+1] = copybeats;

//this code swaps the order of the time variables in the SequencerTime array
        //copy value into buffer (the value above the current profile to be moved up)
        copytime = SequencerTime [sequencercurrentprofile+2];
        //copy over buffered value
        SequencerTime [sequencercurrentprofile+2] = SequencerTime [sequencercurrentprofile+1];
        //copy buffered value to propper spot
        SequencerTime [sequencercurrentprofile+1] = copytime;

///exemption handling
        for (int copyexemptionscount = 0; copyexemptionscount < 16; copyexemptionscount++)
        {
          copyexemptions [copyexemptionscount] = SequencerExemptChannels [sequencercurrentprofile + 2][copyexemptionscount];
          SequencerExemptChannels [sequencercurrentprofile+2][copyexemptionscount] = SequencerExemptChannels [sequencercurrentprofile + 1][copyexemptionscount];
          SequencerExemptChannels [sequencercurrentprofile + 1][copyexemptionscount] = copyexemptions [copyexemptionscount];
        }


// this for loop swaps all the DMX data
for (copybeatcount = 1; copybeatcount < 13; copybeatcount++ )
        {
//displayValue = wxString::Format(wxT("%i"),SequencerChannel_1 [sequencercurrentprofile-1][copybeatcount]);
//wxMessageBox ( displayValue , wxT("sequencercurrentprofile"));

        //copy value into buffer the value above the current profile to be moved up
        copyChannel_1 [copybeatcount] = SequencerChannel_1 [sequencercurrentprofile+1][copybeatcount];
        //copy over buffered value
        SequencerChannel_1 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_1 [sequencercurrentprofile][copybeatcount];
        //copy buffered value to propper spot
        SequencerChannel_1 [sequencercurrentprofile][copybeatcount] = copyChannel_1 [copybeatcount];

//channel 2
        copyChannel_2 [copybeatcount] = SequencerChannel_2 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_2 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_2 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_2 [sequencercurrentprofile][copybeatcount] = copyChannel_2 [copybeatcount];
//channel 3
        copyChannel_3 [copybeatcount] = SequencerChannel_3 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_3 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_3 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_3 [sequencercurrentprofile][copybeatcount] = copyChannel_3 [copybeatcount];
//channel 4
        copyChannel_4 [copybeatcount] = SequencerChannel_4 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_4 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_4 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_4 [sequencercurrentprofile][copybeatcount] = copyChannel_4 [copybeatcount];
//Channel 5
        copyChannel_5 [copybeatcount] = SequencerChannel_5 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_5 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_5 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_5 [sequencercurrentprofile][copybeatcount] = copyChannel_5 [copybeatcount];
//channel 6
        copyChannel_6 [copybeatcount] = SequencerChannel_6 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_6 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_6 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_6 [sequencercurrentprofile][copybeatcount] = copyChannel_6 [copybeatcount];
//channel 7
        copyChannel_7 [copybeatcount] = SequencerChannel_7 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_7 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_7 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_7 [sequencercurrentprofile][copybeatcount] = copyChannel_7 [copybeatcount];
//channel 8
        copyChannel_8 [copybeatcount] = SequencerChannel_8 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_8 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_8 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_8 [sequencercurrentprofile][copybeatcount] = copyChannel_8 [copybeatcount];
//Channel 9
        copyChannel_9 [copybeatcount] = SequencerChannel_9 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_9 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_9 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_9 [sequencercurrentprofile][copybeatcount] = copyChannel_9 [copybeatcount];
//channel 10
        copyChannel_10 [copybeatcount] = SequencerChannel_10 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_10 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_10 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_10 [sequencercurrentprofile][copybeatcount] = copyChannel_10 [copybeatcount];
//channel 11
        copyChannel_11 [copybeatcount] = SequencerChannel_11 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_11 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_11 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_11 [sequencercurrentprofile][copybeatcount] = copyChannel_11 [copybeatcount];
//channel 12
        copyChannel_12 [copybeatcount] = SequencerChannel_12 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_12 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_12 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_12 [sequencercurrentprofile][copybeatcount] = copyChannel_12 [copybeatcount];
//Channel 13
        copyChannel_13 [copybeatcount] = SequencerChannel_13 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_13 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_13 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_13 [sequencercurrentprofile][copybeatcount] = copyChannel_13 [copybeatcount];
//channel 14
        copyChannel_14 [copybeatcount] = SequencerChannel_14 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_14 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_14 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_14 [sequencercurrentprofile][copybeatcount] = copyChannel_14 [copybeatcount];
//channel 15
        copyChannel_15 [copybeatcount] = SequencerChannel_15 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_15 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_15 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_15 [sequencercurrentprofile][copybeatcount] = copyChannel_15 [copybeatcount];
//Channel 16
        copyChannel_16 [copybeatcount] = SequencerChannel_16 [sequencercurrentprofile+1][copybeatcount];
        SequencerChannel_16 [sequencercurrentprofile+1][copybeatcount] = SequencerChannel_16 [sequencercurrentprofile][copybeatcount];
        SequencerChannel_16 [sequencercurrentprofile][copybeatcount] = copyChannel_16 [copybeatcount];

    }//close for loop


//This code swaps the order of the profiles in the listbox


    //wxString displayValue = wxString::Format(wxT("%i"),Choice1->GetSelection());


        //insert values in correct spot on listbox


        //ListBox1->Insert(SequencerProfileNames [sequencercurrentprofile+2],sequencercurrentprofile+1);
        //ListBox1->Insert(SequencerProfileNames [sequencercurrentprofile+1],sequencercurrentprofile);

        //ListBox1->Insert(SequencerProfileNames [sequencercurrentprofile+2],sequencercurrentprofile+1);
        ListBox1->Insert(SequencerProfileNames [sequencercurrentprofile+1],sequencercurrentprofile);

        //delete the old listbox values
//this area also needed to be changed for linux
        //ListBox1->Delete(sequencercurrentprofile+1);
        //ListBox1->Delete(sequencercurrentprofile+2);

        //more linux "listbox->delete" bugfix
        int holdervalueforbugfix = sequencercurrentprofile;

        ListBox1->Delete(sequencercurrentprofile+2);
        //ListBox1->Delete(sequencercurrentprofile+3);

        sequencercurrentprofile = holdervalueforbugfix;



        //set the listbox selection in the right spot
        ListBox1->SetSelection(sequencercurrentprofile+1);

        updateprofile();

        bsischanged = true;

    }
}

void BlinkSequencer::updatelabels (void)
{
        //beat 1 label
        displayValue = wxString::Format(wxT("%i"),Slider1->GetValue());
        StaticText17->SetLabel(displayValue);
        //beat 2 label
        displayValue = wxString::Format(wxT("%i"),Slider2->GetValue());
        StaticText19->SetLabel(displayValue);
        //beat 3 label
        displayValue = wxString::Format(wxT("%i"),Slider3->GetValue());
        StaticText20->SetLabel(displayValue);
        //beat 4 label
        displayValue = wxString::Format(wxT("%i"),Slider4->GetValue());
        StaticText21->SetLabel(displayValue);
        //beat 5 label
        displayValue = wxString::Format(wxT("%i"),Slider5->GetValue());
        StaticText22->SetLabel(displayValue);
        //beat 6 label
        displayValue = wxString::Format(wxT("%i"),Slider6->GetValue());
        StaticText23->SetLabel(displayValue);
        //beat 7 label
        displayValue = wxString::Format(wxT("%i"),Slider7->GetValue());
        StaticText24->SetLabel(displayValue);
        //beat 8 label
        displayValue = wxString::Format(wxT("%i"),Slider8->GetValue());
        StaticText25->SetLabel(displayValue);
        //beat 9 label
        displayValue = wxString::Format(wxT("%i"),Slider9->GetValue());
        StaticText26->SetLabel(displayValue);
        //beat 10 label
        displayValue = wxString::Format(wxT("%i"),Slider10->GetValue());
        StaticText27->SetLabel(displayValue);
        //beat 11 label
        displayValue = wxString::Format(wxT("%i"),Slider11->GetValue());
        StaticText28->SetLabel(displayValue);
        //beat 12 label
        displayValue = wxString::Format(wxT("%i"),Slider12->GetValue());
        StaticText29->SetLabel(displayValue);

}

//pause button
void BlinkSequencer::OnButton1Click1(wxCommandEvent& event)
{

    if (ispaused) {
        Timer1.Stop();
        ispaused = false;
        Timer1.Start(bsbeattime,false);
        Button1->SetLabel(wxT("Pause"));

                bsChannel_1_new = SequencerChannel_1 [ListBox1->GetSelection()] [beat];
                bsChannel_2_new = SequencerChannel_2 [ListBox1->GetSelection()] [beat];
                bsChannel_3_new = SequencerChannel_3 [ListBox1->GetSelection()] [beat];
                bsChannel_4_new = SequencerChannel_4 [ListBox1->GetSelection()] [beat];
                bsChannel_5_new = SequencerChannel_5 [ListBox1->GetSelection()] [beat];
                bsChannel_6_new = SequencerChannel_6 [ListBox1->GetSelection()] [beat];
                bsChannel_7_new = SequencerChannel_7 [ListBox1->GetSelection()] [beat];
                bsChannel_8_new = SequencerChannel_8 [ListBox1->GetSelection()] [beat];
                bsChannel_9_new = SequencerChannel_9 [ListBox1->GetSelection()] [beat];
                bsChannel_10_new = SequencerChannel_10 [ListBox1->GetSelection()] [beat];
                bsChannel_11_new = SequencerChannel_11 [ListBox1->GetSelection()] [beat];
                bsChannel_12_new = SequencerChannel_12 [ListBox1->GetSelection()] [beat];
                bsChannel_13_new = SequencerChannel_13 [ListBox1->GetSelection()] [beat];
                bsChannel_14_new = SequencerChannel_14 [ListBox1->GetSelection()] [beat];
                bsChannel_15_new = SequencerChannel_15 [ListBox1->GetSelection()] [beat];
                bsChannel_16_new = SequencerChannel_16 [ListBox1->GetSelection()] [beat];

                bsChannel_1_out = bsChannel_1_new;
                bsChannel_2_out = bsChannel_2_new;
                bsChannel_3_out = bsChannel_3_new;
                bsChannel_4_out = bsChannel_4_new;
                bsChannel_5_out = bsChannel_5_new;
                bsChannel_6_out = bsChannel_6_new;
                bsChannel_7_out = bsChannel_7_new;
                bsChannel_8_out = bsChannel_8_new;
                bsChannel_9_out = bsChannel_9_new;
                bsChannel_10_out = bsChannel_10_new;
                bsChannel_11_out = bsChannel_11_new;
                bsChannel_12_out = bsChannel_12_new;
                bsChannel_13_out = bsChannel_13_new;
                bsChannel_14_out = bsChannel_14_new;
                bsChannel_15_out = bsChannel_15_new;
                bsChannel_16_out = bsChannel_16_new;

                bsChannel_1_added = bsChannel_1_new;
                bsChannel_2_added = bsChannel_2_new;
                bsChannel_3_added = bsChannel_3_new;
                bsChannel_4_added = bsChannel_4_new;
                bsChannel_5_added = bsChannel_5_new;
                bsChannel_6_added = bsChannel_6_new;
                bsChannel_7_added = bsChannel_7_new;
                bsChannel_8_added = bsChannel_8_new;
                bsChannel_9_added = bsChannel_9_new;
                bsChannel_10_added = bsChannel_10_new;
                bsChannel_11_added = bsChannel_11_new;
                bsChannel_12_added = bsChannel_12_new;
                bsChannel_13_added = bsChannel_13_new;
                bsChannel_14_added = bsChannel_14_new;
                bsChannel_15_added = bsChannel_15_new;
                bsChannel_16_added = bsChannel_16_new;

                if (beat == lastbeat) beat = 0;
                beat++;


    }
    else {
        Timer1.Stop();
        ispaused = true;
        Timer1.Start(20,false);
        Button1->SetLabel(wxT("Play"));
        beat--;
        if (beat == 0) beat = lastbeat;
        beatcounter();

       // displayValue = wxString::Format(wxT("%i"),beat);
        //wxMessageBox ( displayValue , wxT("beat post --"));

    }
}

void BlinkSequencer::OnRadioButton1Select(wxCommandEvent& event)
{
    issmooth = false;
    CheckBox1->Enable(false);
}

void BlinkSequencer::OnRadioButton2Select(wxCommandEvent& event)
{
    issmooth = true;
    if (!Timer1.IsRunning()) CheckBox1->Enable(true);
}


void BlinkSequencer::OnCheckBox1Click1(wxCommandEvent& event)
{
    if (CheckBox1->GetValue()) issmoothstart = true;
    else issmoothstart = false;
}

void BlinkSequencer::OnChoice2Select1(wxCommandEvent& event)
{
    //if (Choice2->GetSelection(); == 0) beat = 1;


}

//rename profile button
void BlinkSequencer::OnButton3Click(wxCommandEvent& event)
{

    if (ListBox1->GetSelection() != -1){
        sequencercurrentprofile = ListBox1->GetSelection();

        bsRenameNameHolder = ListBox1->GetString(sequencercurrentprofile);
        //this code grants access to variables in another file using a classs instance of
        bsRenameProfile Dlg(0);
        //opens dialog
        Dlg.ShowModal();
        wxString newname = Dlg.TextCtrl1->GetValue();
        if (bsyesorno == true) {
            SequencerProfileNames [sequencercurrentprofile+1] = newname;
            ListBox1->Insert(SequencerProfileNames [sequencercurrentprofile+1],sequencercurrentprofile+1);

            //ListBox1->SetSelection(sequencercurrentprofile);

            //more "listbox->delete" bugfix
            int holdervalueforbugfix = sequencercurrentprofile;

            ListBox1->Delete(sequencercurrentprofile);

            sequencercurrentprofile = holdervalueforbugfix;

            ListBox1->SetSelection(sequencercurrentprofile);

            updateprofile();

            bsischanged = true;

        }// closes inner if
        }// closes if
        else wxMessageBox(wxT("Select a profile to rename first."), _("Error"));



}

//delete profile button
void BlinkSequencer::OnButton4Click(wxCommandEvent& event)
{
    if (ListBox1->GetSelection() != -1){
    sequencercurrentprofile = ListBox1->GetSelection()+1;
    //this code grants access to variables in another file using a classs instance of
    //DeleteVerify, Dlg
    bsDeleteProfile Dlg(0);
    //opens dialog
    Dlg.ShowModal();
        if (bsyesorno == true){
            bsischanged = true;
            int beatnumber;
                //currentprofile = ListBox1->GetSelection();

        //this for loop confuses me, but it basically moves every value
        //below the current and being deleted value up one spot in the arrays
        //holding he values
         for (int profilemove = sequencercurrentprofile ; profilemove < bsnumberofprofiles; profilemove++)
            {
                SequencerProfileNames [profilemove] = SequencerProfileNames [profilemove+1];
                SequencerBeats [profilemove] = SequencerBeats [profilemove+1];
                SequencerTime [profilemove] = SequencerTime [profilemove+1];
                SequencerExemptChannels [profilemove] [0] = SequencerExemptChannels [profilemove+1] [0];
                SequencerExemptChannels [profilemove] [1] = SequencerExemptChannels [profilemove+1] [1];
                SequencerExemptChannels [profilemove] [2] = SequencerExemptChannels [profilemove+1] [2];
                SequencerExemptChannels [profilemove] [3] = SequencerExemptChannels [profilemove+1] [3];
                SequencerExemptChannels [profilemove] [4] = SequencerExemptChannels [profilemove+1] [4];
                SequencerExemptChannels [profilemove] [5] = SequencerExemptChannels [profilemove+1] [5];
                SequencerExemptChannels [profilemove] [6] = SequencerExemptChannels [profilemove+1] [6];
                SequencerExemptChannels [profilemove] [7] = SequencerExemptChannels [profilemove+1] [7];
                SequencerExemptChannels [profilemove] [8] = SequencerExemptChannels [profilemove+1] [8];
                SequencerExemptChannels [profilemove] [9] = SequencerExemptChannels [profilemove+1] [9];
                SequencerExemptChannels [profilemove] [10] = SequencerExemptChannels [profilemove+1] [10];
                SequencerExemptChannels [profilemove] [11] = SequencerExemptChannels [profilemove+1] [11];
                SequencerExemptChannels [profilemove] [12] = SequencerExemptChannels [profilemove+1] [12];
                SequencerExemptChannels [profilemove] [13] = SequencerExemptChannels [profilemove+1] [13];
                SequencerExemptChannels [profilemove] [14] = SequencerExemptChannels [profilemove+1] [14];
                SequencerExemptChannels [profilemove] [15] = SequencerExemptChannels [profilemove+1] [15];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_1 [profilemove-1] [beatnumber] = SequencerChannel_1 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_2 [profilemove-1] [beatnumber] = SequencerChannel_2 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_3 [profilemove-1] [beatnumber] = SequencerChannel_3 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_4 [profilemove-1] [beatnumber] = SequencerChannel_4 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_5 [profilemove-1] [beatnumber] = SequencerChannel_5 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_6 [profilemove-1] [beatnumber] = SequencerChannel_6 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_7 [profilemove-1] [beatnumber] = SequencerChannel_7 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_8 [profilemove-1] [beatnumber] = SequencerChannel_8 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_9 [profilemove-1] [beatnumber] = SequencerChannel_9 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_10 [profilemove-1] [beatnumber] = SequencerChannel_10 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_11 [profilemove-1] [beatnumber] = SequencerChannel_11 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_12 [profilemove-1] [beatnumber] = SequencerChannel_12 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_13 [profilemove-1] [beatnumber] = SequencerChannel_13 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_14 [profilemove-1] [beatnumber] = SequencerChannel_14 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_15 [profilemove-1] [beatnumber] = SequencerChannel_15 [profilemove] [beatnumber];
                for (beatnumber = 1; beatnumber < 13; beatnumber++) SequencerChannel_16 [profilemove-1] [beatnumber] = SequencerChannel_16 [profilemove] [beatnumber];

            }//closes the for
            //currentprofile = ListBox1->GetSelection();

            //more "listbox->delete" bugfix
            int holdervalueforbugfix = sequencercurrentprofile;

            ListBox1->Delete(sequencercurrentprofile-1);

            sequencercurrentprofile = holdervalueforbugfix;

            sequencercurrentprofile--;
            bsnumberofprofiles--;
            if (sequencercurrentprofile > 0) {

                ListBox1->SetSelection(sequencercurrentprofile-1);
            }
            else {
                ListBox1->SetSelection(sequencercurrentprofile);
            }
            //ListBox1->SetSelection((sequencercurrentprofile));
            //bsnumberofprofiles--;
            sequencercurrentprofile = ListBox1->GetSelection()+1;
            updateprofile();


        }//closes inner if
    }//closes the if
    else wxMessageBox(wxT("Select a profile to delete first."), _("Error"));
}


//set tempo button
void BlinkSequencer::OnButton9Click(wxCommandEvent& event)
{
    if (!istempomeasure) {
        istempomeasure = true;
        Button9->SetLabel(wxT("Click Again"));
        StopWatch1.Start(0);
    }
    else {
        istempomeasure = false;
        displayValue = wxString::Format(wxT("%i"),StopWatch1.Time());
        TextCtrl1->SetValue(displayValue);
        Button9->SetLabel(wxT("Set Tempo"));
        bsischanged = true;
    }

    //wxMessageBox (displayValue,displayValue);
}

void BlinkSequencer::OnTextCtrl1TextEnter(wxCommandEvent& event)
{
    bsischanged = true;
}


void BlinkSequencer::OnButton8Click2(wxCommandEvent& event)
{
     //used for windows minimize fix
    isIconize = true;

}


void BlinkSequencer::OnCheckBox2Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [0] = CheckBox2->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox3Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [1] = CheckBox3->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox4Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [2] = CheckBox4->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox5Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [3] = CheckBox5->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox6Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [4] = CheckBox6->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox7Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [5] = CheckBox7->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox8Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [6] = CheckBox8->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox9Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [7] = CheckBox9->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox10Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [8] = CheckBox10->IsChecked();
  bsischanged = true;
}
void BlinkSequencer::OnCheckBox11Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [9] = CheckBox11->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox12Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [10] = CheckBox12->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox13Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [11] = CheckBox13->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox14Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [12] = CheckBox14->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox15Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [13] = CheckBox15->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox16Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [14] = CheckBox16->IsChecked();
  bsischanged = true;
}

void BlinkSequencer::OnCheckBox17Click(wxCommandEvent& event)
{
  SequencerExemptChannels [ListBox1->GetSelection()+1] [15] = CheckBox17->IsChecked();
  bsischanged = true;
}
