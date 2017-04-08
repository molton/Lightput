#include "LightScripts.h"
#include "lsSaveDialog.h"
#include "lsLoadDialog.h"
#include "lsSaveChangesDialog.h"
#include "lsOverwriteScript.h"

//(*InternalHeaders(LightScripts)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)
#include <wx/textfile.h>
#include <wx/msgdlg.h>

//(*IdInit(LightScripts)
const long LightScripts::ID_STATICBOX1 = wxNewId();
const long LightScripts::ID_STATICBOX2 = wxNewId();
const long LightScripts::ID_STATICTEXT1 = wxNewId();
const long LightScripts::ID_CHECKBOX1 = wxNewId();
const long LightScripts::ID_TEXTCTRL1 = wxNewId();
const long LightScripts::ID_TEXTCTRL2 = wxNewId();
const long LightScripts::ID_TEXTCTRL3 = wxNewId();
const long LightScripts::ID_TEXTCTRL4 = wxNewId();
const long LightScripts::ID_TEXTCTRL5 = wxNewId();
const long LightScripts::ID_TEXTCTRL6 = wxNewId();
const long LightScripts::ID_TEXTCTRL7 = wxNewId();
const long LightScripts::ID_TEXTCTRL8 = wxNewId();
const long LightScripts::ID_STATICTEXT2 = wxNewId();
const long LightScripts::ID_STATICTEXT3 = wxNewId();
const long LightScripts::ID_STATICTEXT4 = wxNewId();
const long LightScripts::ID_STATICTEXT5 = wxNewId();
const long LightScripts::ID_STATICTEXT6 = wxNewId();
const long LightScripts::ID_STATICTEXT7 = wxNewId();
const long LightScripts::ID_STATICTEXT8 = wxNewId();
const long LightScripts::ID_CHECKBOX2 = wxNewId();
const long LightScripts::ID_CHECKBOX3 = wxNewId();
const long LightScripts::ID_CHECKBOX4 = wxNewId();
const long LightScripts::ID_CHECKBOX5 = wxNewId();
const long LightScripts::ID_CHECKBOX6 = wxNewId();
const long LightScripts::ID_CHECKBOX7 = wxNewId();
const long LightScripts::ID_CHECKBOX8 = wxNewId();
const long LightScripts::ID_STATICTEXT9 = wxNewId();
const long LightScripts::ID_TEXTCTRL9 = wxNewId();
const long LightScripts::ID_CHECKBOX9 = wxNewId();
const long LightScripts::ID_STATICLINE1 = wxNewId();
const long LightScripts::ID_STATICTEXT10 = wxNewId();
const long LightScripts::ID_STATICTEXT11 = wxNewId();
const long LightScripts::ID_STATICTEXT12 = wxNewId();
const long LightScripts::ID_STATICTEXT13 = wxNewId();
const long LightScripts::ID_STATICTEXT14 = wxNewId();
const long LightScripts::ID_STATICTEXT15 = wxNewId();
const long LightScripts::ID_STATICTEXT16 = wxNewId();
const long LightScripts::ID_TEXTCTRL10 = wxNewId();
const long LightScripts::ID_TEXTCTRL11 = wxNewId();
const long LightScripts::ID_TEXTCTRL12 = wxNewId();
const long LightScripts::ID_TEXTCTRL13 = wxNewId();
const long LightScripts::ID_TEXTCTRL14 = wxNewId();
const long LightScripts::ID_TEXTCTRL15 = wxNewId();
const long LightScripts::ID_TEXTCTRL16 = wxNewId();
const long LightScripts::ID_CHECKBOX10 = wxNewId();
const long LightScripts::ID_CHECKBOX11 = wxNewId();
const long LightScripts::ID_CHECKBOX12 = wxNewId();
const long LightScripts::ID_CHECKBOX13 = wxNewId();
const long LightScripts::ID_CHECKBOX14 = wxNewId();
const long LightScripts::ID_CHECKBOX15 = wxNewId();
const long LightScripts::ID_CHECKBOX16 = wxNewId();
const long LightScripts::ID_STATICBOX3 = wxNewId();
const long LightScripts::ID_BUTTON1 = wxNewId();
const long LightScripts::ID_BUTTON2 = wxNewId();
const long LightScripts::ID_STATICTEXT17 = wxNewId();
const long LightScripts::ID_STATICTEXT18 = wxNewId();
const long LightScripts::ID_STATICTEXT19 = wxNewId();
const long LightScripts::ID_STATICTEXT20 = wxNewId();
const long LightScripts::ID_BUTTON3 = wxNewId();
const long LightScripts::ID_BUTTON4 = wxNewId();
const long LightScripts::ID_STATICTEXT21 = wxNewId();
const long LightScripts::ID_TEXTCTRL17 = wxNewId();
const long LightScripts::ID_BUTTON5 = wxNewId();
const long LightScripts::ID_BUTTON6 = wxNewId();
const long LightScripts::ID_BUTTON7 = wxNewId();
const long LightScripts::ID_STATICBOX4 = wxNewId();
const long LightScripts::ID_BUTTON8 = wxNewId();
const long LightScripts::ID_BUTTON9 = wxNewId();
const long LightScripts::ID_CHECKBOX17 = wxNewId();
const long LightScripts::ID_STATICBOX5 = wxNewId();
const long LightScripts::ID_RADIOBUTTON1 = wxNewId();
const long LightScripts::ID_RADIOBUTTON2 = wxNewId();
const long LightScripts::ID_STATICBOX6 = wxNewId();
const long LightScripts::ID_TEXTCTRL18 = wxNewId();
const long LightScripts::ID_STATICTEXT22 = wxNewId();
const long LightScripts::ID_BUTTON10 = wxNewId();
const long LightScripts::ID_BUTTON11 = wxNewId();
const long LightScripts::ID_STATICTEXT23 = wxNewId();
const long LightScripts::ID_STATICTEXT24 = wxNewId();
const long LightScripts::ID_BUTTON12 = wxNewId();
const long LightScripts::ID_TIMER1 = wxNewId();
//*)

unsigned short int current_scriptfile_data [16];
unsigned short int previous_scriptfile_data [16];
unsigned short int current_scriptfile_transition [16];
int current_scriptfile_time;
unsigned int total_linenumber;
unsigned int current_linenumber;
int time_so_far;

bool isinsert;
bool scriptischanged;
bool lsisstarted;
bool lsispaused;

//these varibales are controls for dialogs
bool lsissaving;
bool lsisloading;
bool islsoverwrite;
wxString ScriptName;
int savechanges;
bool textctrlfunctionautorunfix;

extern bool isIconize;

//variables for system options
extern bool islsRepeat;
extern bool islsStartOn1;
extern unsigned short int LightputFrequency;

bool control_6;

//variables for new transitional system
double lsChannel_1_difference;
double lsChannel_1_increment;
double lsChannel_1_added;
unsigned short int lsChannel_1_new;
unsigned short int lsChannel_1_out;
double lsChannel_2_difference;
double lsChannel_2_increment;
double lsChannel_2_added;
unsigned short int lsChannel_2_new;
unsigned short int lsChannel_2_out;
double lsChannel_3_difference;
double lsChannel_3_increment;
double lsChannel_3_added;
unsigned short int lsChannel_3_new;
unsigned short int lsChannel_3_out;
double lsChannel_4_difference;
double lsChannel_4_increment;
double lsChannel_4_added;
unsigned short int lsChannel_4_new;
unsigned short int lsChannel_4_out;
double lsChannel_5_difference;
double lsChannel_5_increment;
double lsChannel_5_added;
unsigned short int lsChannel_5_new;
unsigned short int lsChannel_5_out;
double lsChannel_6_difference;
double lsChannel_6_increment;
double lsChannel_6_added;
unsigned short int lsChannel_6_new;
unsigned short int lsChannel_6_out;
double lsChannel_7_difference;
double lsChannel_7_increment;
double lsChannel_7_added;
unsigned short int lsChannel_7_new;
unsigned short int lsChannel_7_out;
double lsChannel_8_difference;
double lsChannel_8_increment;
double lsChannel_8_added;
unsigned short int lsChannel_8_new;
unsigned short int lsChannel_8_out;
double lsChannel_9_difference;
double lsChannel_9_increment;
double lsChannel_9_added;
unsigned short int lsChannel_9_new;
unsigned short int lsChannel_9_out;
double lsChannel_10_difference;
double lsChannel_10_increment;
double lsChannel_10_added;
unsigned short int lsChannel_10_new;
unsigned short int lsChannel_10_out;
double lsChannel_11_difference;
double lsChannel_11_increment;
double lsChannel_11_added;
unsigned short int lsChannel_11_new;
unsigned short int lsChannel_11_out;
double lsChannel_12_difference;
double lsChannel_12_increment;
double lsChannel_12_added;
unsigned short int lsChannel_12_new;
unsigned short int lsChannel_12_out;
double lsChannel_13_difference;
double lsChannel_13_increment;
double lsChannel_13_added;
unsigned short int lsChannel_13_new;
unsigned short int lsChannel_13_out;
double lsChannel_14_difference;
double lsChannel_14_increment;
double lsChannel_14_added;
unsigned short int lsChannel_14_new;
unsigned short int lsChannel_14_out;
double lsChannel_15_difference;
double lsChannel_15_increment;
double lsChannel_15_added;
unsigned short int lsChannel_15_new;
unsigned short int lsChannel_15_out;
double lsChannel_16_difference;
double lsChannel_16_increment;
double lsChannel_16_added;
unsigned short int lsChannel_16_new;
unsigned short int lsChannel_16_out;

//buffers for profile when blinking is off/done
extern int ls_ProfileChannel_1;
extern int ls_ProfileChannel_2;
extern int ls_ProfileChannel_3;
extern int ls_ProfileChannel_4;
extern int ls_ProfileChannel_5;
extern int ls_ProfileChannel_6;
extern int ls_ProfileChannel_7;
extern int ls_ProfileChannel_8;
extern int ls_ProfileChannel_9;
extern int ls_ProfileChannel_10;
extern int ls_ProfileChannel_11;
extern int ls_ProfileChannel_12;
extern int ls_ProfileChannel_13;
extern int ls_ProfileChannel_14;
extern int ls_ProfileChannel_15;
extern int ls_ProfileChannel_16;

//variables for the working text file
wxString currentscriptfilename;
wxTextFile currentscripttempfile;

BEGIN_EVENT_TABLE(LightScripts,wxDialog)
	//(*EventTable(LightScripts)
	//*)
END_EVENT_TABLE()

LightScripts::LightScripts(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //put the propper color data into the lights from profile mode
    lsChannel_1_out = ls_ProfileChannel_1;
    lsChannel_2_out = ls_ProfileChannel_2;
    lsChannel_3_out = ls_ProfileChannel_3;
    lsChannel_4_out = ls_ProfileChannel_4;
    lsChannel_5_out = ls_ProfileChannel_5;
    lsChannel_6_out = ls_ProfileChannel_6;
    lsChannel_7_out = ls_ProfileChannel_7;
    lsChannel_8_out = ls_ProfileChannel_8;
    lsChannel_9_out = ls_ProfileChannel_9;
    lsChannel_10_out = ls_ProfileChannel_10;
    lsChannel_11_out = ls_ProfileChannel_11;
    lsChannel_12_out = ls_ProfileChannel_12;
    lsChannel_13_out = ls_ProfileChannel_13;
    lsChannel_14_out = ls_ProfileChannel_14;
    lsChannel_15_out = ls_ProfileChannel_15;
    lsChannel_16_out = ls_ProfileChannel_16;
    lsChannel_1_new = ls_ProfileChannel_1;
    lsChannel_2_new = ls_ProfileChannel_2;
    lsChannel_3_new = ls_ProfileChannel_3;
    lsChannel_4_new = ls_ProfileChannel_4;
    lsChannel_5_new = ls_ProfileChannel_5;
    lsChannel_6_new = ls_ProfileChannel_6;
    lsChannel_7_new = ls_ProfileChannel_7;
    lsChannel_8_new = ls_ProfileChannel_8;
    lsChannel_9_new = ls_ProfileChannel_9;
    lsChannel_10_new = ls_ProfileChannel_10;
    lsChannel_11_new = ls_ProfileChannel_11;
    lsChannel_12_new = ls_ProfileChannel_12;
    lsChannel_13_new = ls_ProfileChannel_13;
    lsChannel_14_new = ls_ProfileChannel_14;
    lsChannel_15_new = ls_ProfileChannel_15;
    lsChannel_16_new = ls_ProfileChannel_16;
    lsChannel_1_added = ls_ProfileChannel_1;
    lsChannel_2_added = ls_ProfileChannel_2;
    lsChannel_3_added = ls_ProfileChannel_3;
    lsChannel_4_added = ls_ProfileChannel_4;
    lsChannel_5_added = ls_ProfileChannel_5;
    lsChannel_6_added = ls_ProfileChannel_6;
    lsChannel_7_added = ls_ProfileChannel_7;
    lsChannel_8_added = ls_ProfileChannel_8;
    lsChannel_9_added = ls_ProfileChannel_9;
    lsChannel_10_added = ls_ProfileChannel_10;
    lsChannel_11_added = ls_ProfileChannel_11;
    lsChannel_12_added = ls_ProfileChannel_12;
    lsChannel_13_added = ls_ProfileChannel_13;
    lsChannel_14_added = ls_ProfileChannel_14;
    lsChannel_15_added = ls_ProfileChannel_15;
    lsChannel_16_added = ls_ProfileChannel_16;

    time_so_far = 0;
    lsisstarted = false;
    lsispaused = false;

    lsissaving = false;
    lsisloading = false;

    textctrlfunctionautorunfix = true;

	//(*Initialize(LightScripts)
	Create(parent, wxID_ANY, _("Light Scripts 0.1"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(719,498));
	Move(wxPoint(100,100));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Script Current Position"), wxPoint(24,8), wxSize(272,88), 0, _T("ID_STATICBOX1"));
	wxFont StaticBox1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox1->SetFont(StaticBox1Font);
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Set DMX Values and Transition Settings for the Current Script Position"), wxPoint(24,104), wxSize(552,288), 0, _T("ID_STATICBOX2"));
	wxFont StaticBox2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox2->SetFont(StaticBox2Font);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Channel 1"), wxPoint(48,136), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("Smooth"), wxPoint(216,131), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox1->SetValue(false);
	wxFont CheckBox1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox1->SetFont(CheckBox1Font);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxPoint(120,128), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	wxFont TextCtrl1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl1->SetFont(TextCtrl1Font);
	TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("Text"), wxPoint(120,160), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	wxFont TextCtrl2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl2->SetFont(TextCtrl2Font);
	TextCtrl3 = new wxTextCtrl(this, ID_TEXTCTRL3, _("Text"), wxPoint(120,192), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	wxFont TextCtrl3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl3->SetFont(TextCtrl3Font);
	TextCtrl4 = new wxTextCtrl(this, ID_TEXTCTRL4, _("Text"), wxPoint(120,224), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	wxFont TextCtrl4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl4->SetFont(TextCtrl4Font);
	TextCtrl5 = new wxTextCtrl(this, ID_TEXTCTRL5, _("Text"), wxPoint(120,256), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	wxFont TextCtrl5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl5->SetFont(TextCtrl5Font);
	TextCtrl6 = new wxTextCtrl(this, ID_TEXTCTRL6, _("Text"), wxPoint(120,288), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	wxFont TextCtrl6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl6->SetFont(TextCtrl6Font);
	TextCtrl7 = new wxTextCtrl(this, ID_TEXTCTRL7, _("Text"), wxPoint(120,320), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	wxFont TextCtrl7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl7->SetFont(TextCtrl7Font);
	TextCtrl8 = new wxTextCtrl(this, ID_TEXTCTRL8, _("Text"), wxPoint(120,352), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
	wxFont TextCtrl8Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl8->SetFont(TextCtrl8Font);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Channel 2"), wxPoint(48,168), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Channel 3"), wxPoint(48,200), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Channel 4"), wxPoint(48,232), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	wxFont StaticText4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Channel 5"), wxPoint(48,264), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	wxFont StaticText5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText5->SetFont(StaticText5Font);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Channel 6"), wxPoint(48,296), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	wxFont StaticText6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText6->SetFont(StaticText6Font);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Channel 7"), wxPoint(48,328), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	wxFont StaticText7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText7->SetFont(StaticText7Font);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Channel 8"), wxPoint(48,360), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	wxFont StaticText8Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText8->SetFont(StaticText8Font);
	CheckBox2 = new wxCheckBox(this, ID_CHECKBOX2, _("Smooth"), wxPoint(216,162), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBox2->SetValue(false);
	wxFont CheckBox2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox2->SetFont(CheckBox2Font);
	CheckBox3 = new wxCheckBox(this, ID_CHECKBOX3, _("Smooth"), wxPoint(216,193), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	CheckBox3->SetValue(false);
	wxFont CheckBox3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox3->SetFont(CheckBox3Font);
	CheckBox4 = new wxCheckBox(this, ID_CHECKBOX4, _("Smooth"), wxPoint(216,225), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	CheckBox4->SetValue(false);
	wxFont CheckBox4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox4->SetFont(CheckBox4Font);
	CheckBox5 = new wxCheckBox(this, ID_CHECKBOX5, _("Smooth"), wxPoint(216,257), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	CheckBox5->SetValue(false);
	wxFont CheckBox5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox5->SetFont(CheckBox5Font);
	CheckBox6 = new wxCheckBox(this, ID_CHECKBOX6, _("Smooth"), wxPoint(216,289), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	CheckBox6->SetValue(false);
	wxFont CheckBox6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox6->SetFont(CheckBox6Font);
	CheckBox7 = new wxCheckBox(this, ID_CHECKBOX7, _("Smooth"), wxPoint(216,321), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	CheckBox7->SetValue(false);
	wxFont CheckBox7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox7->SetFont(CheckBox7Font);
	CheckBox8 = new wxCheckBox(this, ID_CHECKBOX8, _("Smooth"), wxPoint(216,353), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	CheckBox8->SetValue(false);
	wxFont CheckBox8Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox8->SetFont(CheckBox8Font);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Channel 9"), wxPoint(320,136), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	wxFont StaticText9Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText9->SetFont(StaticText9Font);
	TextCtrl9 = new wxTextCtrl(this, ID_TEXTCTRL9, _("Text"), wxPoint(392,128), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
	wxFont TextCtrl9Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl9->SetFont(TextCtrl9Font);
	CheckBox9 = new wxCheckBox(this, ID_CHECKBOX9, _("Smooth"), wxPoint(488,131), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	CheckBox9->SetValue(false);
	wxFont CheckBox9Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox9->SetFont(CheckBox9Font);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxPoint(296,136), wxSize(2,240), wxLI_VERTICAL, _T("ID_STATICLINE1"));
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Channel 10"), wxPoint(320,168), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	wxFont StaticText10Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText10->SetFont(StaticText10Font);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Channel 11"), wxPoint(320,200), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	wxFont StaticText11Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText11->SetFont(StaticText11Font);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Channel 12"), wxPoint(320,232), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	wxFont StaticText12Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText12->SetFont(StaticText12Font);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Channel 13"), wxPoint(320,264), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	wxFont StaticText13Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText13->SetFont(StaticText13Font);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("Channel 14"), wxPoint(320,296), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	wxFont StaticText14Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText14->SetFont(StaticText14Font);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Channel 15\'"), wxPoint(320,328), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	wxFont StaticText15Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText15->SetFont(StaticText15Font);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Channel 16"), wxPoint(320,360), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	wxFont StaticText16Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText16->SetFont(StaticText16Font);
	TextCtrl10 = new wxTextCtrl(this, ID_TEXTCTRL10, _("Text"), wxPoint(392,160), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL10"));
	wxFont TextCtrl10Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl10->SetFont(TextCtrl10Font);
	TextCtrl11 = new wxTextCtrl(this, ID_TEXTCTRL11, _("Text"), wxPoint(392,192), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL11"));
	wxFont TextCtrl11Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl11->SetFont(TextCtrl11Font);
	TextCtrl12 = new wxTextCtrl(this, ID_TEXTCTRL12, _("Text"), wxPoint(392,224), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL12"));
	wxFont TextCtrl12Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl12->SetFont(TextCtrl12Font);
	TextCtrl13 = new wxTextCtrl(this, ID_TEXTCTRL13, _("Text"), wxPoint(392,256), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL13"));
	wxFont TextCtrl13Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl13->SetFont(TextCtrl13Font);
	TextCtrl14 = new wxTextCtrl(this, ID_TEXTCTRL14, _("Text"), wxPoint(392,288), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL14"));
	wxFont TextCtrl14Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl14->SetFont(TextCtrl14Font);
	TextCtrl15 = new wxTextCtrl(this, ID_TEXTCTRL15, _("Text"), wxPoint(392,320), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL15"));
	wxFont TextCtrl15Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl15->SetFont(TextCtrl15Font);
	TextCtrl16 = new wxTextCtrl(this, ID_TEXTCTRL16, _("Text"), wxPoint(392,352), wxSize(80,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL16"));
	wxFont TextCtrl16Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl16->SetFont(TextCtrl16Font);
	CheckBox10 = new wxCheckBox(this, ID_CHECKBOX10, _("Smooth"), wxPoint(488,161), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	CheckBox10->SetValue(false);
	wxFont CheckBox10Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox10->SetFont(CheckBox10Font);
	CheckBox11 = new wxCheckBox(this, ID_CHECKBOX11, _("Smooth"), wxPoint(488,193), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	CheckBox11->SetValue(false);
	wxFont CheckBox11Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox11->SetFont(CheckBox11Font);
	CheckBox12 = new wxCheckBox(this, ID_CHECKBOX12, _("Smooth"), wxPoint(488,225), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	CheckBox12->SetValue(false);
	wxFont CheckBox12Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox12->SetFont(CheckBox12Font);
	CheckBox13 = new wxCheckBox(this, ID_CHECKBOX13, _("Smooth"), wxPoint(488,257), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	CheckBox13->SetValue(false);
	wxFont CheckBox13Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox13->SetFont(CheckBox13Font);
	CheckBox14 = new wxCheckBox(this, ID_CHECKBOX14, _("Smooth"), wxPoint(488,289), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	CheckBox14->SetValue(false);
	wxFont CheckBox14Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox14->SetFont(CheckBox14Font);
	CheckBox15 = new wxCheckBox(this, ID_CHECKBOX15, _("Smooth"), wxPoint(488,321), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	CheckBox15->SetValue(false);
	wxFont CheckBox15Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox15->SetFont(CheckBox15Font);
	CheckBox16 = new wxCheckBox(this, ID_CHECKBOX16, _("Smooth"), wxPoint(488,353), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
	CheckBox16->SetValue(false);
	wxFont CheckBox16Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox16->SetFont(CheckBox16Font);
	StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("Save / Load Script"), wxPoint(312,8), wxSize(264,88), 0, _T("ID_STATICBOX3"));
	wxFont StaticBox3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox3->SetFont(StaticBox3Font);
	SaveButton = new wxButton(this, ID_BUTTON1, _("Save"), wxPoint(328,24), wxSize(112,24), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont SaveButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	SaveButton->SetFont(SaveButtonFont);
	LoadButton = new wxButton(this, ID_BUTTON2, _("Load"), wxPoint(456,24), wxSize(112,24), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont LoadButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	LoadButton->SetFont(LoadButtonFont);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Current Script:"), wxPoint(328,72), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	wxFont StaticText17Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText17->SetFont(StaticText17Font);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("None"), wxPoint(416,72), wxSize(152,13), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT18"));
	StaticText18->SetMaxSize(wxSize(152,13));
	wxFont StaticText18Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText18->SetFont(StaticText18Font);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("Step:"), wxPoint(40,24), wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	wxFont StaticText19Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText19->SetFont(StaticText19Font);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("1 of 1"), wxPoint(80,24), wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	wxFont StaticText20Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText20->SetFont(StaticText20Font);
	PreviousButton = new wxButton(this, ID_BUTTON3, _("Previous Step"), wxPoint(40,40), wxSize(112,24), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	wxFont PreviousButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	PreviousButton->SetFont(PreviousButtonFont);
	NextButton = new wxButton(this, ID_BUTTON4, _("Next Step"), wxPoint(168,40), wxSize(112,24), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	wxFont NextButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	NextButton->SetFont(NextButtonFont);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("Jump To Step"), wxPoint(40,74), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	wxFont StaticText21Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText21->SetFont(StaticText21Font);
	TextCtrl17 = new wxTextCtrl(this, ID_TEXTCTRL17, _("0"), wxPoint(120,72), wxSize(120,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL17"));
	wxFont TextCtrl17Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl17->SetFont(TextCtrl17Font);
	GoButton = new wxButton(this, ID_BUTTON5, _("Go"), wxPoint(248,72), wxSize(32,21), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	wxFont GoButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	GoButton->SetFont(GoButtonFont);
	Button6 = new wxButton(this, ID_BUTTON6, _("Insert New Step at Current Position"), wxPoint(32,408), wxSize(248,29), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	wxFont Button6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button6->SetFont(Button6Font);
	DeleteButton = new wxButton(this, ID_BUTTON7, _("Delete Step at Current Position"), wxPoint(320,408), wxSize(248,29), 0, wxDefaultValidator, _T("ID_BUTTON7"));
	wxFont DeleteButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	DeleteButton->SetFont(DeleteButtonFont);
	StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("Script Playback"), wxPoint(584,32), wxSize(112,136), 0, _T("ID_STATICBOX4"));
	wxFont StaticBox4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox4->SetFont(StaticBox4Font);
	StartStopButton = new wxButton(this, ID_BUTTON8, _("Start"), wxPoint(600,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	wxFont StartStopButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StartStopButton->SetFont(StartStopButtonFont);
	PauseButton = new wxButton(this, ID_BUTTON9, _("Pause"), wxPoint(600,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
	wxFont PauseButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	PauseButton->SetFont(PauseButtonFont);
	CheckBox17 = new wxCheckBox(this, ID_CHECKBOX17, _("Start on \nStep 1"), wxPoint(592,136), wxSize(88,13), 0, wxDefaultValidator, _T("ID_CHECKBOX17"));
	CheckBox17->SetValue(false);
	wxFont CheckBox17Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox17->SetFont(CheckBox17Font);
	StaticBox5 = new wxStaticBox(this, ID_STATICBOX5, _("Repeat Settings"), wxPoint(584,176), wxSize(112,128), 0, _T("ID_STATICBOX5"));
	wxFont StaticBox5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox5->SetFont(StaticBox5Font);
	RadioButton1 = new wxRadioButton(this, ID_RADIOBUTTON1, wxEmptyString, wxPoint(592,192), wxSize(16,55), 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	wxFont RadioButton1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	RadioButton1->SetFont(RadioButton1Font);
	RadioButton2 = new wxRadioButton(this, ID_RADIOBUTTON2, wxEmptyString, wxPoint(592,264), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	wxFont RadioButton2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	RadioButton2->SetFont(RadioButton2Font);
	StaticBox6 = new wxStaticBox(this, ID_STATICBOX6, _("Current Step Time"), wxPoint(584,304), wxSize(112,168), 0, _T("ID_STATICBOX6"));
	wxFont StaticBox6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox6->SetFont(StaticBox6Font);
	TextCtrl18 = new wxTextCtrl(this, ID_TEXTCTRL18, _("Text"), wxPoint(592,336), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL18"));
	wxFont TextCtrl18Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl18->SetFont(TextCtrl18Font);
	StaticText22 = new wxStaticText(this, ID_STATICTEXT22, _("In Milliseconds\nuse values\nbetween 60\nand 9999999\n\n(1000 ms is one\nminute, etc.)"), wxPoint(600,368), wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	wxFont StaticText22Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText22->SetFont(StaticText22Font);
	CopyButton = new wxButton(this, ID_BUTTON10, _("Copy Current Step Settings to New Step"), wxPoint(32,448), wxSize(248,29), 0, wxDefaultValidator, _T("ID_BUTTON10"));
	wxFont CopyButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CopyButton->SetFont(CopyButtonFont);
	NewScriptButton = new wxButton(this, ID_BUTTON11, _("New Script"), wxPoint(456,48), wxSize(112,24), 0, wxDefaultValidator, _T("ID_BUTTON11"));
	wxFont NewScriptButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	NewScriptButton->SetFont(NewScriptButtonFont);
	StaticText23 = new wxStaticText(this, ID_STATICTEXT23, _("Stop playback\nat the end of\nthe script"), wxPoint(616,200), wxSize(80,40), 0, _T("ID_STATICTEXT23"));
	wxFont StaticText23Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText23->SetFont(StaticText23Font);
	StaticText24 = new wxStaticText(this, ID_STATICTEXT24, _("Repeat\nplayback of\nthe script"), wxPoint(616,256), wxDefaultSize, 0, _T("ID_STATICTEXT24"));
	wxFont StaticText24Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText24->SetFont(StaticText24Font);
	HideButton = new wxButton(this, ID_BUTTON12, _("Hide Lightput"), wxPoint(584,0), wxSize(112,23), 0, wxDefaultValidator, _T("ID_BUTTON12"));
	wxFont HideButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	HideButton->SetFont(HideButtonFont);
	LightScriptTimer.SetOwner(this, ID_TIMER1);
	
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox1Click);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl1Text);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl2Text);
	Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl3Text);
	Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl4Text);
	Connect(ID_TEXTCTRL5,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl5Text);
	Connect(ID_TEXTCTRL6,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl6Text);
	Connect(ID_TEXTCTRL7,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl7Text);
	Connect(ID_TEXTCTRL8,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl8Text);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox2Click);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox3Click);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox4Click);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox5Click);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox6Click);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox7Click);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox8Click);
	Connect(ID_TEXTCTRL9,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl9Text);
	Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox9Click);
	Connect(ID_TEXTCTRL10,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl10Text);
	Connect(ID_TEXTCTRL11,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl11Text);
	Connect(ID_TEXTCTRL12,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl12Text);
	Connect(ID_TEXTCTRL13,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl13Text);
	Connect(ID_TEXTCTRL14,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl14Text);
	Connect(ID_TEXTCTRL15,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl15Text);
	Connect(ID_TEXTCTRL16,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl16Text);
	Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox10Click);
	Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox11Click);
	Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox12Click);
	Connect(ID_CHECKBOX13,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox13Click);
	Connect(ID_CHECKBOX14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox14Click);
	Connect(ID_CHECKBOX15,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox15Click);
	Connect(ID_CHECKBOX16,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox16Click);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnSaveButtonClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnLoadButtonClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnPreviousButtonClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnNextButtonClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnGoButtonClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnButton6Click);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnDeleteButtonClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnStartStopButtonClick);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnPauseButtonClick);
	Connect(ID_CHECKBOX17,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&LightScripts::OnCheckBox17Click);
	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&LightScripts::OnRadioButton1Select);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&LightScripts::OnRadioButton2Select);
	Connect(ID_TEXTCTRL18,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LightScripts::OnTextCtrl18Text);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnCopyButtonClick);
	Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnNewScriptButtonClick);
	Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightScripts::OnHideButtonClick);
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&LightScripts::OnLightScriptTimerTrigger);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&LightScripts::OnClose);
	//*)

	if (islsStartOn1) CheckBox17->SetValue(true);
	if (islsRepeat) RadioButton2->SetValue(true);
	else RadioButton1->SetValue(true);

	//create the temporary, working script file to be saved or discarded
    currentscriptfilename = wxT("./light_programs/light_scripts/blankscript");
    currentscripttempfile.Create(currentscriptfilename);

    currentscripttempfile.Clear();
    currentscripttempfile.Write();


    BlankStep();
    total_linenumber = 1;
    current_linenumber = 1;


    ScriptName = wxT("");
    isinsert = true;
    scriptischanged = false;
    CommitCurrentLine();

}

LightScripts::~LightScripts()
{
	//(*Destroy(LightScripts)
	//*)
    currentscripttempfile.Close();
}

void LightScripts::BlankStep(void)
{
    TextCtrl1->SetValue(wxT("0"));
    TextCtrl2->SetValue(wxT("0"));
    TextCtrl3->SetValue(wxT("0"));
    TextCtrl4->SetValue(wxT("0"));
    TextCtrl5->SetValue(wxT("0"));
    TextCtrl6->SetValue(wxT("0"));
    TextCtrl7->SetValue(wxT("0"));
    TextCtrl8->SetValue(wxT("0"));
    TextCtrl9->SetValue(wxT("0"));
    TextCtrl10->SetValue(wxT("0"));
    TextCtrl11->SetValue(wxT("0"));
    TextCtrl12->SetValue(wxT("0"));
    TextCtrl13->SetValue(wxT("0"));
    TextCtrl14->SetValue(wxT("0"));
    TextCtrl15->SetValue(wxT("0"));
    TextCtrl16->SetValue(wxT("0"));

    TextCtrl18->SetValue(wxT("1000"));

    for (int i = 0; i < 16; i++){
        current_scriptfile_data [i] = 0;
        current_scriptfile_transition [i] = 0;
    }
    current_scriptfile_time = 1000;

    CheckBox1->SetValue(false);
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
}

///insert new step button
void LightScripts::OnButton6Click(wxCommandEvent& event)
{
    //save any current chnages
    isinsert = true;
    CommitCurrentLine();

    current_linenumber++;
    total_linenumber++;

    ///make condition for copy or not

    BlankStep();
    UpdateStepCounter();
}

///updates the "step 1 of 1" thing
void LightScripts::UpdateStepCounter(void)
{
    wxString firstnumber;
    wxString wxt_of = wxT(" of ");
    wxString secondnumber;
    wxString alltogether;

    firstnumber = wxString::Format(wxT("%i"),current_linenumber);
    secondnumber = wxString::Format(wxT("%i"),total_linenumber);

    alltogether = firstnumber + wxt_of + secondnumber;

    //actually put the update up
    StaticText20->SetLabel(alltogether);
}

///commit the current line to the working text file
void LightScripts::CommitCurrentLine(void)
{
    wxString valuepad;
    wxString valuepadded;

    wxString linepart;
    wxString spacer = wxT("#");

    int intvalue;

    //textctrl18 is the step time box
    intvalue = wxAtoi(TextCtrl18->GetValue());

    /* this handles making sure the time value is valid, doing it on entering the
    //value itself is kind of problematic, user friendlier this way
    if (!((intvalue > 59) &&(intvalue < 10000000)) || (TextCtrl18->GetValue().IsNumber() == false)  )  {
        TextCtrl18->SetValue(wxT("1000"));
        intvalue = 1000;
    }
    current_scriptfile_time = intvalue;
*/

///format time and add to line
    //this code pads the value with leading zeros for proper data storage
    //makes it easy to load if they all have the same number of characters
    valuepad = wxString::Format(wxT("%i"),current_scriptfile_time);
    valuepadded = wxT("000000") + valuepad;
    //this line cuts off any characters past three
    valuepadded = valuepadded.substr( valuepadded.length() - 7 );

    wxString line = valuepadded + spacer;

///format DMX values and add to line
    for (int i = 0; i < 16; i++) {
        linepart = wxString::Format(wxT("%i"),current_scriptfile_data [i]);

        valuepadded = wxT("00") + linepart;
        valuepadded = valuepadded.substr( valuepadded.length() - 3 );

        linepart = valuepadded + spacer;
        line = line + linepart;
        }


///format transition choice (boolean, 1 or 0) and add to line (not using # spacer)
    for (int i = 0; i < 16; i++) {

        linepart = wxString::Format(wxT("%i"),current_scriptfile_transition [i]);
        line = line + linepart;
/*
        if (i == 0) CheckBox1->SetValue(wxAtoi(linepart));
        if (i == 1) CheckBox2->SetValue(wxAtoi(linepart));
        if (i == 2) CheckBox3->SetValue(wxAtoi(linepart));
        if (i == 3) CheckBox4->SetValue(wxAtoi(linepart));
        if (i == 4) CheckBox5->SetValue(wxAtoi(linepart));
        if (i == 5) CheckBox6->SetValue(wxAtoi(linepart));
        if (i == 6) CheckBox7->SetValue(wxAtoi(linepart));
        if (i == 7) CheckBox8->SetValue(wxAtoi(linepart));
        if (i == 8) CheckBox9->SetValue(wxAtoi(linepart));
        if (i == 9) CheckBox10->SetValue(wxAtoi(linepart));
        if (i == 10) CheckBox11->SetValue(wxAtoi(linepart));
        if (i == 11) CheckBox12->SetValue(wxAtoi(linepart));
        if (i == 12) CheckBox13->SetValue(wxAtoi(linepart));
        if (i == 13) CheckBox14->SetValue(wxAtoi(linepart));
        if (i == 14) CheckBox15->SetValue(wxAtoi(linepart));
        if (i == 15) CheckBox16->SetValue(wxAtoi(linepart));
*/
        }




///insert line, or delete line and insert new line
    if (!isinsert){
        if (current_linenumber > total_linenumber) {
            current_linenumber = 1;
            //currentscripttempfile.RemoveLine(current_linenumber);
        }
        //else
        currentscripttempfile.RemoveLine(current_linenumber - 1);
    }
    currentscripttempfile.InsertLine(line,current_linenumber - 1,wxTextFileType_Dos);
    isinsert = false;
}

///load the current line from the working text file
void LightScripts::LoadCurrentLine(void)
{
    wxString valuepad;
    wxString line;

    int pos = 0;
    int pos2 = 0;
    int count = 0;

    //clear out previous data
   current_scriptfile_time = 1000;
    for (int i = 0; i < 16; i++){
        current_scriptfile_data [i] = 0;
        current_scriptfile_transition [i] = 0;
    }

    line = currentscripttempfile.GetLine(current_linenumber - 1);

    ///get time from current line
    valuepad.clear();
    do {
        valuepad = valuepad + line [pos];
        pos++;
        //count++;
    } while (pos < 7);

    //write int value to buffer
    current_scriptfile_time = wxAtoi(valuepad);
    //convert to int, back to string to get rid of leading 0's
    //this isn the first thing to go if more efficiency is needed
    TextCtrl18->SetValue((wxString::Format(wxT("%i"),current_scriptfile_time)));

    //to skip over the spacer
    pos++;

    ///get the DMX values
    do {
        valuepad.clear();
        do {
            valuepad = valuepad + line [pos];
            pos++;
            count++;
        } while (count < 3);

        count = 0;

        //write int value to buffer
        current_scriptfile_data [pos2] = wxAtoi(valuepad);
        //convert to int, back to string to get rid of leading 0's
        //this isn the first thing to go if more efficiency is needed

        if (pos2 == 0) TextCtrl1->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 1) TextCtrl2->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 2) TextCtrl3->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 3) TextCtrl4->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 4) TextCtrl5->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 5) TextCtrl6->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 6) TextCtrl7->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 7) TextCtrl8->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 8) TextCtrl9->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 9) TextCtrl10->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 10) TextCtrl11->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 11) TextCtrl12->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 12) TextCtrl13->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 13) TextCtrl14->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 14) TextCtrl15->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));
        if (pos2 == 15) TextCtrl16->SetValue((wxString::Format(wxT("%i"),current_scriptfile_data [pos2])));

        pos2++;
        pos++;

    } while (pos < 72); //there are 72 characters in the line before the transiton data

    ///last part is to get the transition values and update everything for those

///adjust all of this to be a for loop like this stuff

    for (int i = 0; pos < 88 ; pos++) {
        if (pos == 72) {
            valuepad = line [pos];
            CheckBox1->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [0] = wxAtoi(valuepad);
        }
        if (pos == 73) {
            valuepad = line [pos];
            CheckBox2->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [1] = wxAtoi(valuepad);
        }
        if (pos == 74) {
            valuepad = line [pos];
            CheckBox3->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [2] = wxAtoi(valuepad);
        }
        if (pos == 75) {
            valuepad = line [pos];
            CheckBox4->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [3] = wxAtoi(valuepad);
        }
        if (pos == 76) {
            valuepad = line [pos];
            CheckBox5->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [4] = wxAtoi(valuepad);
        }
        if (pos == 77) {
            valuepad = line [pos];
            CheckBox6->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [5] = wxAtoi(valuepad);
        }
        if (pos == 78) {
            valuepad = line [pos];
            CheckBox7->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [6] = wxAtoi(valuepad);
        }
        if (pos == 79) {
            valuepad = line [pos];
            CheckBox8->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [7] = wxAtoi(valuepad);
        }
        if (pos == 80) {
            valuepad = line [pos];
            CheckBox9->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [8] = wxAtoi(valuepad);
        }
        if (pos == 81) {
            valuepad = line [pos];
            CheckBox10->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [9] = wxAtoi(valuepad);
        }
        if (pos == 82) {
            valuepad = line [pos];
            CheckBox11->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [10] = wxAtoi(valuepad);
        }
        if (pos == 83) {
            valuepad = line [pos];
            CheckBox12->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [11] = wxAtoi(valuepad);
        }
        if (pos == 84) {
            valuepad = line [pos];
            CheckBox13->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [12] = wxAtoi(valuepad);
        }
        if (pos == 85) {
            valuepad = line [pos];
            CheckBox14->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [13] = wxAtoi(valuepad);
        }
        if (pos == 86) {
            valuepad = line [pos];
            CheckBox15->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [14] = wxAtoi(valuepad);
        }
        if (pos == 87) {
            valuepad = line [pos];
            CheckBox16->SetValue(wxAtoi(valuepad));
            current_scriptfile_transition [15] = wxAtoi(valuepad);

        }
    }

}

///save button
void LightScripts::OnSaveButtonClick(wxCommandEvent& event)
{
    SaveScript();
}

void LightScripts::SaveScript(void)
{
    //commit last line to fix smooth checkbox bug
    CommitCurrentLine();
    //int lineholder = current_linenumber;
    //current_linenumber = total_linenumber + 1;
    //CommitCurrentLine();
    //current_linenumber = lineholder;

    if (StaticText18->GetLabel() != wxT("None")) ScriptName = StaticText18->GetLabel();
    //have to remove .ls, do it in the save dialog

    //lsSaveDialog lsSaveDlg(0);
    lsSaveDialog *lsSaveDlg = new lsSaveDialog(0);
    lsSaveDlg->ShowModal();
    ///add file name dialog

   if (lsissaving) {

        wxString scriptfilename = wxT("./light_programs/light_scripts/") + ScriptName + wxT(".ls");
        wxTextFile scriptfile(scriptfilename);
       // control_6 = false;

        if (scriptfile.Exists()) {
            scriptfile.Close();
            islsoverwrite = false;
            ///doing things this way keeps showmodal() from causing crashes
            lsOverwriteScript *lsOverwriteDlg = new lsOverwriteScript(0);
            lsOverwriteDlg->ShowModal();
            if (!islsoverwrite) lsissaving = false;
            //control_6 = true;
        }
        else islsoverwrite = true; //write the file if not an overwrite scenario

        if (islsoverwrite) {
            currentscripttempfile.Create(scriptfilename);
            currentscripttempfile.Write(wxTextFileType_Dos, wxConvISO8859_1);
        }
        //put working tempfile back in its right spot after saving
        currentscriptfilename = wxT("./light_programs/light_scripts/blankscript");
        currentscripttempfile.Create(currentscriptfilename);
        currentscripttempfile.Clear();
        currentscripttempfile.Write();


        if (lsissaving)StaticText18->SetLabel(ScriptName + wxT(".ls"));

        scriptischanged = false;
   }
}

///these functions are for updating the values when the user enters them
void LightScripts::OnTextCtrl1Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl1->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl1->GetValue().IsNumber() == false)  )  {
        TextCtrl1->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [0] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl2Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
        scriptischanged = true;

        int intvalue = wxAtoi(TextCtrl2->GetValue());

        if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl2->GetValue().IsNumber() == false)  )  {
            TextCtrl2->SetValue(wxT("0"));
            intvalue = 0;
        }
        current_scriptfile_data [1] = intvalue;
        CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl3Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl3->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl3->GetValue().IsNumber() == false)  )  {
        TextCtrl3->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [2] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl4Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl4->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl4->GetValue().IsNumber() == false)  )  {
        TextCtrl4->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [3] = intvalue;
    CommitCurrentLine();

    }
}

void LightScripts::OnTextCtrl5Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl5->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl5->GetValue().IsNumber() == false)  )  {
        TextCtrl5->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [4] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl6Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl6->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl6->GetValue().IsNumber() == false)  )  {
        TextCtrl6->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [5] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl7Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl7->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl7->GetValue().IsNumber() == false)  )  {
        TextCtrl7->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [6] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl8Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl8->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl8->GetValue().IsNumber() == false)  )  {
        TextCtrl8->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [7] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl9Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl9->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl9->GetValue().IsNumber() == false)  )  {
        TextCtrl9->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [8] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl10Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl10->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl10->GetValue().IsNumber() == false)  )  {
        TextCtrl10->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [9] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl11Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl11->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl11->GetValue().IsNumber() == false)  )  {
        TextCtrl11->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [10] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl12Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl12->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl12->GetValue().IsNumber() == false)  )  {
        TextCtrl12->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [11] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl13Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl13->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl13->GetValue().IsNumber() == false)  )  {
        TextCtrl13->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [12] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl14Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl14->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl14->GetValue().IsNumber() == false)  )  {
        TextCtrl14->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [13] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl15Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl15->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl15->GetValue().IsNumber() == false)  )  {
        TextCtrl15->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [14] = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnTextCtrl16Text(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue = wxAtoi(TextCtrl16->GetValue());

    if (!((intvalue > -1) &&(intvalue < 256)) || (TextCtrl16->GetValue().IsNumber() == false)  )  {
        TextCtrl16->SetValue(wxT("0"));
        intvalue = 0;
    }
    current_scriptfile_data [15] = intvalue;
    CommitCurrentLine();
    }
}


///these functions are for updating the transition value when the user checks or unchecks
void LightScripts::OnCheckBox1Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [0] = CheckBox1->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox2Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [1] = CheckBox2->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox3Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [2] = CheckBox3->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox4Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [3] = CheckBox4->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox5Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [4] = CheckBox5->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox6Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [5] = CheckBox6->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox7Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [6] = CheckBox7->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox8Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [7] = CheckBox8->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox9Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [8] = CheckBox9->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox10Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [9] = CheckBox10->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox11Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [10] = CheckBox11->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox12Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [11] = CheckBox12->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox13Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [12] = CheckBox13->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox14Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [13] = CheckBox14->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox15Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [14] = CheckBox15->GetValue();
    CommitCurrentLine();
    }
}

void LightScripts::OnCheckBox16Click(wxCommandEvent& event)
{
    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;
    current_scriptfile_transition [15] = CheckBox16->GetValue();
    CommitCurrentLine();
    }
}

///this handles when users enter data into the transition time
void LightScripts::OnTextCtrl18Text(wxCommandEvent& event)
{

    if (textctrlfunctionautorunfix)
    {
    scriptischanged = true;

    int intvalue;
    intvalue = wxAtoi(TextCtrl18->GetValue());

    if (!((intvalue > 59) &&(intvalue < 10000000)) || (TextCtrl18->GetValue().IsNumber() == false)  )  {
        TextCtrl18->SetValue(wxT("1000"));
        intvalue = 1000;
    }
    current_scriptfile_time = intvalue;
    CommitCurrentLine();
    }
}

void LightScripts::OnPreviousButtonClick(wxCommandEvent& event)
{
    textctrlfunctionautorunfix = false;
    if (current_linenumber > 1)
    {
        CommitCurrentLine();
        current_linenumber--;
        LoadCurrentLine();

        UpdateStepCounter();
    }
    textctrlfunctionautorunfix = true;
}

void LightScripts::OnNextButtonClick(wxCommandEvent& event)
{
    textctrlfunctionautorunfix = false;
    if (current_linenumber < total_linenumber)
    {
        CommitCurrentLine();
        current_linenumber++;
        LoadCurrentLine();

        UpdateStepCounter();
    }
    textctrlfunctionautorunfix = true;
}

//"Go" navigation button
void LightScripts::OnGoButtonClick(wxCommandEvent& event)
{
    textctrlfunctionautorunfix = false;
    int intvalue = wxAtoi(TextCtrl17->GetValue());

    if (!((intvalue > 0) &&(intvalue <= total_linenumber)) || (TextCtrl1->GetValue().IsNumber() == false)) {
        wxMessageBox( wxT("Enter a valid step number before pressing the go button."),wxT("Error"));
    }
    else //load the selected step
    {
        CommitCurrentLine();
        current_linenumber = intvalue;
        LoadCurrentLine();

        UpdateStepCounter();
    }
    textctrlfunctionautorunfix = true;
}

///heres the DMX engine stuff, the timer and the calculate increments function
void LightScripts::OnLightScriptTimerTrigger(wxTimerEvent& event)
{

    //this advances to the next step
    if (time_so_far > current_scriptfile_time)
    {
        //don't think i need this
        CommitCurrentLine();

        current_linenumber++;

        //LoadCurrentLine();
        time_so_far = 0;
        //return;


        //checks to see if its the end of the script, if so, either repeat or end
        if (current_linenumber >  total_linenumber){
            if (RadioButton1->GetValue()) {
                StopSettings();
                LightScriptTimer.Stop();
                current_linenumber = 1;
                LoadCurrentLine();

                UpdateStepCounter();
                return;
            }
            if (RadioButton2->GetValue()) {



                //CommitCurrentLine();
                current_linenumber = 1;
                LoadCurrentLine();

                UpdateStepCounter();
                return;
            }

        }

                LoadCurrentLine();
                UpdateStepCounter();
    } //closes original if (    if (time_so_far > current_scriptfile_time)   )

    if (!lsispaused) {
        lsChannel_1_new = current_scriptfile_data [0];
        lsChannel_2_new = current_scriptfile_data [1];
        lsChannel_3_new = current_scriptfile_data [2];
        lsChannel_4_new = current_scriptfile_data [3];
        lsChannel_5_new = current_scriptfile_data [4];
        lsChannel_6_new = current_scriptfile_data [5];
        lsChannel_7_new = current_scriptfile_data [6];
        lsChannel_8_new = current_scriptfile_data [7];
        lsChannel_9_new = current_scriptfile_data [8];
        lsChannel_10_new = current_scriptfile_data [9];
        lsChannel_11_new = current_scriptfile_data [10];
        lsChannel_12_new = current_scriptfile_data [11];
        lsChannel_13_new = current_scriptfile_data [12];
        lsChannel_14_new = current_scriptfile_data [13];
        lsChannel_15_new = current_scriptfile_data [14];
        lsChannel_16_new = current_scriptfile_data [15];

        if (!current_scriptfile_transition [0]) {lsChannel_1_out = lsChannel_1_new; lsChannel_1_added = lsChannel_1_new;}
        if (!current_scriptfile_transition [1]) {lsChannel_2_out = lsChannel_2_new; lsChannel_2_added = lsChannel_2_new;}
        if (!current_scriptfile_transition [2]) {lsChannel_3_out = lsChannel_3_new; lsChannel_3_added = lsChannel_3_new;}
        if (!current_scriptfile_transition [3]) {lsChannel_4_out = lsChannel_4_new; lsChannel_4_added = lsChannel_4_new;}
        if (!current_scriptfile_transition [4]) {lsChannel_5_out = lsChannel_5_new; lsChannel_5_added = lsChannel_5_new;}
        if (!current_scriptfile_transition [5]) {lsChannel_6_out = lsChannel_6_new; lsChannel_6_added = lsChannel_6_new;}
        if (!current_scriptfile_transition [6]) {lsChannel_7_out = lsChannel_7_new; lsChannel_7_added = lsChannel_7_new;}
        if (!current_scriptfile_transition [7]) {lsChannel_8_out = lsChannel_8_new; lsChannel_8_added = lsChannel_8_new;}
        if (!current_scriptfile_transition [8]) {lsChannel_9_out = lsChannel_9_new; lsChannel_9_added = lsChannel_9_new;}
        if (!current_scriptfile_transition [9]) {lsChannel_10_out = lsChannel_10_new; lsChannel_10_added = lsChannel_10_new;}
        if (!current_scriptfile_transition [10]) {lsChannel_11_out = lsChannel_11_new; lsChannel_11_added = lsChannel_11_new;}
        if (!current_scriptfile_transition [11]) {lsChannel_12_out = lsChannel_12_new; lsChannel_12_added = lsChannel_12_new;}
        if (!current_scriptfile_transition [12]) {lsChannel_13_out = lsChannel_13_new; lsChannel_13_added = lsChannel_13_new;}
        if (!current_scriptfile_transition [13]) {lsChannel_14_out = lsChannel_14_new; lsChannel_14_added = lsChannel_14_new;}
        if (!current_scriptfile_transition [14]) {lsChannel_15_out = lsChannel_15_new; lsChannel_15_added = lsChannel_15_new;}
        if (!current_scriptfile_transition [15]) {lsChannel_16_out = lsChannel_16_new; lsChannel_16_added = lsChannel_16_new;}

        CalculateIncrements();

        time_so_far = time_so_far + LightputFrequency;
    }
}

void LightScripts::CalculateIncrements(void)
//how the fuck this uses all subtraction of floats and actually works is beyond me...
//i think it works as long as increments are calculated continually, which is why the
//24 houl light mode works less accurately
{

           if (lsChannel_1_new > lsChannel_1_out) lsChannel_1_difference = lsChannel_1_new - lsChannel_1_out;
           if (lsChannel_1_new < lsChannel_1_out) lsChannel_1_difference = lsChannel_1_out - lsChannel_1_new;
           lsChannel_1_increment = lsChannel_1_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_2_new > lsChannel_2_out) lsChannel_2_difference = lsChannel_2_new - lsChannel_2_out;
           if (lsChannel_2_new < lsChannel_2_out) lsChannel_2_difference = lsChannel_2_out - lsChannel_2_new;
           lsChannel_2_increment = lsChannel_2_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_3_new > lsChannel_3_out) lsChannel_3_difference = lsChannel_3_new - lsChannel_3_out;
           if (lsChannel_3_new < lsChannel_3_out) lsChannel_3_difference = lsChannel_3_out - lsChannel_3_new;
           lsChannel_3_increment = lsChannel_3_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_4_new > lsChannel_4_out) lsChannel_4_difference = lsChannel_4_new - lsChannel_4_out;
           if (lsChannel_4_new < lsChannel_4_out) lsChannel_4_difference = lsChannel_4_out - lsChannel_4_new;
           lsChannel_4_increment = lsChannel_4_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_5_new > lsChannel_5_out) lsChannel_5_difference = lsChannel_5_new - lsChannel_5_out;
           if (lsChannel_5_new < lsChannel_5_out) lsChannel_5_difference = lsChannel_5_out - lsChannel_5_new;
           lsChannel_5_increment = lsChannel_5_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_6_new > lsChannel_6_out) lsChannel_6_difference = lsChannel_6_new - lsChannel_6_out;
           if (lsChannel_6_new < lsChannel_6_out) lsChannel_6_difference = lsChannel_6_out - lsChannel_6_new;
           lsChannel_6_increment = lsChannel_6_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_7_new > lsChannel_7_out) lsChannel_7_difference = lsChannel_7_new - lsChannel_7_out;
           if (lsChannel_7_new < lsChannel_7_out) lsChannel_7_difference = lsChannel_7_out - lsChannel_7_new;
           lsChannel_7_increment = lsChannel_7_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_8_new > lsChannel_8_out) lsChannel_8_difference = lsChannel_8_new - lsChannel_8_out;
           if (lsChannel_8_new < lsChannel_8_out) lsChannel_8_difference = lsChannel_8_out - lsChannel_8_new;
           lsChannel_8_increment = lsChannel_8_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_9_new > lsChannel_9_out) lsChannel_9_difference = lsChannel_9_new - lsChannel_9_out;
           if (lsChannel_9_new < lsChannel_9_out) lsChannel_9_difference = lsChannel_9_out - lsChannel_9_new;
           lsChannel_9_increment = lsChannel_9_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_10_new > lsChannel_10_out) lsChannel_10_difference = lsChannel_10_new - lsChannel_10_out;
           if (lsChannel_10_new < lsChannel_10_out) lsChannel_10_difference = lsChannel_10_out - lsChannel_10_new;
           lsChannel_10_increment = lsChannel_10_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_11_new > lsChannel_11_out) lsChannel_11_difference = lsChannel_11_new - lsChannel_11_out;
           if (lsChannel_11_new < lsChannel_11_out) lsChannel_11_difference = lsChannel_11_out - lsChannel_11_new;
           lsChannel_11_increment = lsChannel_11_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_12_new > lsChannel_12_out) lsChannel_12_difference = lsChannel_12_new - lsChannel_12_out;
           if (lsChannel_12_new < lsChannel_12_out) lsChannel_12_difference = lsChannel_12_out - lsChannel_12_new;
           lsChannel_12_increment = lsChannel_12_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_13_new > lsChannel_13_out) lsChannel_13_difference = lsChannel_13_new - lsChannel_13_out;
           if (lsChannel_13_new < lsChannel_13_out) lsChannel_13_difference = lsChannel_13_out - lsChannel_13_new;
           lsChannel_13_increment = lsChannel_13_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_14_new > lsChannel_14_out) lsChannel_14_difference = lsChannel_14_new - lsChannel_14_out;
           if (lsChannel_14_new < lsChannel_14_out) lsChannel_14_difference = lsChannel_14_out - lsChannel_14_new;
           lsChannel_14_increment = lsChannel_14_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_15_new > lsChannel_15_out) lsChannel_15_difference = lsChannel_15_new - lsChannel_15_out;
           if (lsChannel_15_new < lsChannel_15_out) lsChannel_15_difference = lsChannel_15_out - lsChannel_15_new;
           lsChannel_15_increment = lsChannel_15_difference / ((current_scriptfile_time/LightputFrequency));

           if (lsChannel_16_new > lsChannel_16_out) lsChannel_16_difference = lsChannel_16_new - lsChannel_16_out;
           if (lsChannel_16_new < lsChannel_16_out) lsChannel_16_difference = lsChannel_16_out - lsChannel_16_new;
           lsChannel_16_increment = lsChannel_16_difference / ((current_scriptfile_time/LightputFrequency));
}

void LightScripts::OnStartStopButtonClick(wxCommandEvent& event)
{
    textctrlfunctionautorunfix = false;
    CommitCurrentLine();
    if (!lsisstarted) {

        if (islsStartOn1) current_linenumber = 1;

        LoadCurrentLine();

        UpdateStepCounter();

        lsChannel_1_new = current_scriptfile_data [0];
        lsChannel_2_new = current_scriptfile_data [1];
        lsChannel_3_new = current_scriptfile_data [2];
        lsChannel_4_new = current_scriptfile_data [3];
        lsChannel_5_new = current_scriptfile_data [4];
        lsChannel_6_new = current_scriptfile_data [5];
        lsChannel_7_new = current_scriptfile_data [6];
        lsChannel_8_new = current_scriptfile_data [7];
        lsChannel_9_new = current_scriptfile_data [8];
        lsChannel_10_new = current_scriptfile_data [9];
        lsChannel_11_new = current_scriptfile_data [10];
        lsChannel_12_new = current_scriptfile_data [11];
        lsChannel_13_new = current_scriptfile_data [12];
        lsChannel_14_new = current_scriptfile_data [13];
        lsChannel_15_new = current_scriptfile_data [14];
        lsChannel_16_new = current_scriptfile_data [15];

        CalculateIncrements();

        StartSettings();
        LightScriptTimer.Start(LightputFrequency,false);
    }
    else // if istarted is true, stop
    {
        StopSettings();
        LightScriptTimer.Stop();
        time_so_far = 0;
        textctrlfunctionautorunfix = true;
    }
}

void LightScripts::StartSettings(void)
{
   TextCtrl1->Enable(false);
   TextCtrl2->Enable(false);
   TextCtrl3->Enable(false);
   TextCtrl4->Enable(false);
   TextCtrl5->Enable(false);
   TextCtrl6->Enable(false);
   TextCtrl7->Enable(false);
   TextCtrl8->Enable(false);
   TextCtrl9->Enable(false);
   TextCtrl10->Enable(false);
   TextCtrl11->Enable(false);
   TextCtrl12->Enable(false);
   TextCtrl13->Enable(false);
   TextCtrl14->Enable(false);
   TextCtrl15->Enable(false);
   TextCtrl16->Enable(false);
   TextCtrl17->Enable(false);
   TextCtrl18->Enable(false);

   CheckBox1->Enable(false);
   CheckBox2->Enable(false);
   CheckBox3->Enable(false);
   CheckBox4->Enable(false);
   CheckBox5->Enable(false);
   CheckBox6->Enable(false);
   CheckBox7->Enable(false);
   CheckBox8->Enable(false);
   CheckBox9->Enable(false);
   CheckBox10->Enable(false);
   CheckBox11->Enable(false);
   CheckBox12->Enable(false);
   CheckBox13->Enable(false);
   CheckBox14->Enable(false);
   CheckBox15->Enable(false);
   CheckBox16->Enable(false);
   CheckBox17->Enable(false);

   PreviousButton->Enable(false);
   NextButton->Enable(false);
   SaveButton->Enable(false);
   LoadButton->Enable(false);
   DeleteButton->Enable(false);
   CopyButton->Enable(false);
   Button6->Enable(false);
   GoButton->Enable(false);
   NewScriptButton->Enable(false);

   StartStopButton->SetLabel(wxT("Stop"));

   lsisstarted = true;

}

void LightScripts::StopSettings(void)
{
   TextCtrl1->Enable(true);
   TextCtrl2->Enable(true);
   TextCtrl3->Enable(true);
   TextCtrl4->Enable(true);
   TextCtrl5->Enable(true);
   TextCtrl6->Enable(true);
   TextCtrl7->Enable(true);
   TextCtrl8->Enable(true);
   TextCtrl9->Enable(true);
   TextCtrl10->Enable(true);
   TextCtrl11->Enable(true);
   TextCtrl12->Enable(true);
   TextCtrl13->Enable(true);
   TextCtrl14->Enable(true);
   TextCtrl15->Enable(true);
   TextCtrl16->Enable(true);
   TextCtrl17->Enable(true);
   TextCtrl18->Enable(true);

   CheckBox1->Enable(true);
   CheckBox2->Enable(true);
   CheckBox3->Enable(true);
   CheckBox4->Enable(true);
   CheckBox5->Enable(true);
   CheckBox6->Enable(true);
   CheckBox7->Enable(true);
   CheckBox8->Enable(true);
   CheckBox9->Enable(true);
   CheckBox10->Enable(true);
   CheckBox11->Enable(true);
   CheckBox12->Enable(true);
   CheckBox13->Enable(true);
   CheckBox14->Enable(true);
   CheckBox15->Enable(true);
   CheckBox16->Enable(true);
   CheckBox17->Enable(true);

   PreviousButton->Enable(true);
   NextButton->Enable(true);
   SaveButton->Enable(true);
   LoadButton->Enable(true);
   DeleteButton->Enable(true);
   CopyButton->Enable(true);
   Button6->Enable(true);
   GoButton->Enable(true);
   NewScriptButton->Enable(true);

   StartStopButton->SetLabel(wxT("Start"));

   ///non-gui stuff

    lsisstarted = false;



    //dmx engine restore to profile
    lsChannel_1_out = ls_ProfileChannel_1;
    lsChannel_2_out = ls_ProfileChannel_2;
    lsChannel_3_out = ls_ProfileChannel_3;
    lsChannel_4_out = ls_ProfileChannel_4;
    lsChannel_5_out = ls_ProfileChannel_5;
    lsChannel_6_out = ls_ProfileChannel_6;
    lsChannel_7_out = ls_ProfileChannel_7;
    lsChannel_8_out = ls_ProfileChannel_8;
    lsChannel_9_out = ls_ProfileChannel_9;
    lsChannel_10_out = ls_ProfileChannel_10;
    lsChannel_11_out = ls_ProfileChannel_11;
    lsChannel_12_out = ls_ProfileChannel_12;
    lsChannel_13_out = ls_ProfileChannel_13;
    lsChannel_14_out = ls_ProfileChannel_14;
    lsChannel_15_out = ls_ProfileChannel_15;
    lsChannel_16_out = ls_ProfileChannel_16;
    lsChannel_1_new = ls_ProfileChannel_1;
    lsChannel_2_new = ls_ProfileChannel_2;
    lsChannel_3_new = ls_ProfileChannel_3;
    lsChannel_4_new = ls_ProfileChannel_4;
    lsChannel_5_new = ls_ProfileChannel_5;
    lsChannel_6_new = ls_ProfileChannel_6;
    lsChannel_7_new = ls_ProfileChannel_7;
    lsChannel_8_new = ls_ProfileChannel_8;
    lsChannel_9_new = ls_ProfileChannel_9;
    lsChannel_10_new = ls_ProfileChannel_10;
    lsChannel_11_new = ls_ProfileChannel_11;
    lsChannel_12_new = ls_ProfileChannel_12;
    lsChannel_13_new = ls_ProfileChannel_13;
    lsChannel_14_new = ls_ProfileChannel_14;
    lsChannel_15_new = ls_ProfileChannel_15;
    lsChannel_16_new = ls_ProfileChannel_16;
    lsChannel_1_added = ls_ProfileChannel_1;
    lsChannel_2_added = ls_ProfileChannel_2;
    lsChannel_3_added = ls_ProfileChannel_3;
    lsChannel_4_added = ls_ProfileChannel_4;
    lsChannel_5_added = ls_ProfileChannel_5;
    lsChannel_6_added = ls_ProfileChannel_6;
    lsChannel_7_added = ls_ProfileChannel_7;
    lsChannel_8_added = ls_ProfileChannel_8;
    lsChannel_9_added = ls_ProfileChannel_9;
    lsChannel_10_added = ls_ProfileChannel_10;
    lsChannel_11_added = ls_ProfileChannel_11;
    lsChannel_12_added = ls_ProfileChannel_12;
    lsChannel_13_added = ls_ProfileChannel_13;
    lsChannel_14_added = ls_ProfileChannel_14;
    lsChannel_15_added = ls_ProfileChannel_15;
    lsChannel_16_added = ls_ProfileChannel_16;

}




void LightScripts::OnPauseButtonClick(wxCommandEvent& event)
{
    if (lsispaused) lsispaused = false;
    else lsispaused = true;
}


void LightScripts::OnLoadButtonClick(wxCommandEvent& event)
{

    savechanges = 0;

    if (scriptischanged){
        lsSaveChangesDialog lsSaveChangesDlg(0);
               // do {
        lsSaveChangesDlg.ShowModal();

        }
      //  while (savechanges == 0);

        if (savechanges == 1) {

            lsissaving = false;
            SaveScript();

            } //if saving
        else if (savechanges = 2) int dummy; //if not saving
        else return; //if canceled
    //}
    lsLoadDialog *lsLoadingDlg = new lsLoadDialog(0);
    //lsLoadDialog lsLoadDlg(0);
    lsLoadingDlg->ShowModal();
    ///add file name dialog

   if (lsisloading) {

        wxString scriptfilename = wxT("./light_programs/light_scripts/") + ScriptName;
        wxTextFile scriptfile;
        scriptfile.Open(scriptfilename);
        scriptfile.Create(currentscriptfilename);
        scriptfile.Write(wxTextFileType_Dos, wxConvISO8859_1);

        //put working tempfile back after copying it from saved file
        currentscriptfilename = wxT("./light_programs/light_scripts/blankscript");

        currentscripttempfile.Clear();
        currentscripttempfile.Open(currentscriptfilename);

        total_linenumber = currentscripttempfile.GetLineCount();
        current_linenumber = 1;

        currentscripttempfile.GoToLine(0);
        LoadCurrentLine();

        StaticText18->SetLabel(ScriptName);

        UpdateStepCounter();

        scriptischanged = false;
   }
}

void LightScripts::OnDeleteButtonClick(wxCommandEvent& event)
{


    if ((total_linenumber > 1)) {
        if (current_linenumber > 1) {
            current_linenumber--;
            currentscripttempfile.RemoveLine(current_linenumber);
        }
            else currentscripttempfile.RemoveLine(current_linenumber -1);
        total_linenumber--;
        LoadCurrentLine();
        UpdateStepCounter();

    }
}

/* how come this works?

void LightScripts::OnNextButtonClick(wxCommandEvent& event)
{
    if (current_linenumber < total_linenumber)
    {
        CommitCurrentLine();
        current_linenumber++;
        LoadCurrentLine();

        UpdateStepCounter();
    }

}
*/

void LightScripts::OnCopyButtonClick(wxCommandEvent& event)
{

    CommitCurrentLine();

    isinsert = true;
    current_linenumber++;
    CommitCurrentLine();
    total_linenumber++;
    LoadCurrentLine();
    CommitCurrentLine();
    UpdateStepCounter();
}

//on start on 1 box check / uncheck
void LightScripts::OnCheckBox17Click(wxCommandEvent& event)
{
    if (CheckBox17->GetValue()) islsStartOn1 = true;
    else islsStartOn1 = false;
}

//repeat radio button
void LightScripts::OnRadioButton2Select(wxCommandEvent& event)
{
    islsRepeat = true;
}
//stop / repeat radio button
void LightScripts::OnRadioButton1Select(wxCommandEvent& event)
{
    islsRepeat = false;
}


void LightScripts::OnNewScriptButtonClick(wxCommandEvent& event)
{
      savechanges = 0;

    if (scriptischanged){
        lsSaveChangesDialog lsSaveChangesDlg(0);
               // do {
        lsSaveChangesDlg.ShowModal();

        }
      //  while (savechanges == 0);

        if (savechanges == 1) {

            lsissaving = false;
            SaveScript();

            } //if saving
        else if (savechanges = 2) int dummy; //if not saving
        else return; //if canceled

///this is where the new script is formed
    //total_linenumber = 1;
    //current_linenumber = 1;

    ///clear blankscriipt file
    currentscriptfilename = wxT("./light_programs/light_scripts/blankscript");
    currentscripttempfile.Clear();
    currentscripttempfile.Write();

    total_linenumber = 1;
    current_linenumber = 1;

    CommitCurrentLine();
    ///correct new profile bugs
    StaticText18->SetLabel(wxT(""));

    UpdateStepCounter();

    BlankStep();


}

void LightScripts::OnClose(wxCloseEvent& event)
{
     savechanges = 0;

    if (scriptischanged){
        lsSaveChangesDialog lsSaveChangesDlg(0);
               // do {
        lsSaveChangesDlg.ShowModal();

        }
        else {
            LightScriptTimer.Stop();
            Destroy();
        }
      //  while (savechanges == 0);

        if (savechanges == 1) {

            lsissaving = false;
            SaveScript();
            if (!lsissaving) return;

            } //if saving
        else if (savechanges == 0) return; //if canceled
        LightScriptTimer.Stop();
        Destroy();

}

void LightScripts::OnHideButtonClick(wxCommandEvent& event)
{
    //used for windows minimize fix
    isIconize = true;
}
