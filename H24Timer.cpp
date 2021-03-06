//(C) 2013 Michael Johnston

#include "H24Timer.h"
//these are overused, i thought it was eloquent code use
//to reuse these dialogs, but it causes problems
//#include "AddNewProfile.h"
//#include "RenameProfile.h"
//#include "DeleteVerify.h"

#include "StopTimer.h"
#include "h24profileoverwrite.h"
#include "H24RenameProfile.h"
#include "H24AddNewProfile.h"
#include "H24DeleteProfile.h"
#include "H24CopyVerify.h"

#include <wx/msgdlg.h>
#include <wx/textfile.h>

//(*InternalHeaders(H24Timer)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//(*IdInit(H24Timer)
const long H24Timer::ID_STATICBOX1 = wxNewId();
const long H24Timer::ID_LISTBOX1 = wxNewId();
const long H24Timer::ID_SLIDER1 = wxNewId();
const long H24Timer::ID_SLIDER2 = wxNewId();
const long H24Timer::ID_SLIDER3 = wxNewId();
const long H24Timer::ID_SLIDER4 = wxNewId();
const long H24Timer::ID_SLIDER5 = wxNewId();
const long H24Timer::ID_SLIDER6 = wxNewId();
const long H24Timer::ID_SLIDER7 = wxNewId();
const long H24Timer::ID_SLIDER8 = wxNewId();
const long H24Timer::ID_SLIDER9 = wxNewId();
const long H24Timer::ID_SLIDER10 = wxNewId();
const long H24Timer::ID_SLIDER11 = wxNewId();
const long H24Timer::ID_SLIDER12 = wxNewId();
const long H24Timer::ID_SLIDER13 = wxNewId();
const long H24Timer::ID_SLIDER14 = wxNewId();
const long H24Timer::ID_SLIDER15 = wxNewId();
const long H24Timer::ID_SLIDER16 = wxNewId();
const long H24Timer::ID_STATICTEXT1 = wxNewId();
const long H24Timer::ID_STATICTEXT2 = wxNewId();
const long H24Timer::ID_STATICTEXT3 = wxNewId();
const long H24Timer::ID_STATICTEXT4 = wxNewId();
const long H24Timer::ID_STATICTEXT5 = wxNewId();
const long H24Timer::ID_STATICTEXT6 = wxNewId();
const long H24Timer::ID_STATICTEXT7 = wxNewId();
const long H24Timer::ID_STATICTEXT8 = wxNewId();
const long H24Timer::ID_STATICTEXT9 = wxNewId();
const long H24Timer::ID_STATICTEXT10 = wxNewId();
const long H24Timer::ID_STATICTEXT11 = wxNewId();
const long H24Timer::ID_STATICTEXT12 = wxNewId();
const long H24Timer::ID_STATICTEXT13 = wxNewId();
const long H24Timer::ID_STATICTEXT14 = wxNewId();
const long H24Timer::ID_STATICTEXT15 = wxNewId();
const long H24Timer::ID_STATICTEXT16 = wxNewId();
const long H24Timer::ID_STATICTEXT17 = wxNewId();
const long H24Timer::ID_STATICTEXT18 = wxNewId();
const long H24Timer::ID_STATICTEXT19 = wxNewId();
const long H24Timer::ID_STATICTEXT20 = wxNewId();
const long H24Timer::ID_STATICTEXT21 = wxNewId();
const long H24Timer::ID_STATICTEXT22 = wxNewId();
const long H24Timer::ID_STATICTEXT23 = wxNewId();
const long H24Timer::ID_STATICTEXT24 = wxNewId();
const long H24Timer::ID_STATICTEXT25 = wxNewId();
const long H24Timer::ID_STATICTEXT26 = wxNewId();
const long H24Timer::ID_STATICTEXT27 = wxNewId();
const long H24Timer::ID_STATICTEXT28 = wxNewId();
const long H24Timer::ID_STATICTEXT29 = wxNewId();
const long H24Timer::ID_STATICTEXT30 = wxNewId();
const long H24Timer::ID_STATICTEXT31 = wxNewId();
const long H24Timer::ID_STATICTEXT32 = wxNewId();
const long H24Timer::ID_STATICBOX2 = wxNewId();
const long H24Timer::ID_BUTTON1 = wxNewId();
const long H24Timer::ID_CHECKBOX1 = wxNewId();
const long H24Timer::ID_STATICBOX3 = wxNewId();
const long H24Timer::ID_CHOICE1 = wxNewId();
const long H24Timer::ID_STATICTEXT33 = wxNewId();
const long H24Timer::ID_LISTBOX2 = wxNewId();
const long H24Timer::ID_BUTTON2 = wxNewId();
const long H24Timer::ID_BUTTON3 = wxNewId();
const long H24Timer::ID_BUTTON4 = wxNewId();
const long H24Timer::ID_BUTTON5 = wxNewId();
const long H24Timer::ID_BUTTON6 = wxNewId();
const long H24Timer::ID_STATICTEXT34 = wxNewId();
const long H24Timer::ID_STATICTEXT35 = wxNewId();
const long H24Timer::ID_BUTTON7 = wxNewId();
const long H24Timer::ID_BUTTON8 = wxNewId();
const long H24Timer::ID_STATICTEXT36 = wxNewId();
const long H24Timer::ID_BUTTON9 = wxNewId();
const long H24Timer::ID_H24TIMER1 = wxNewId();
//*)

//for rename profile and delete profile
//extern bool yesorno;

//for profile overwrite dialog
bool savecancel;
bool timeryesorno;
bool stopcancel;
bool copyyesorno;


//for stop timer
bool stopyesorno;
extern bool istimeractive;
extern bool isIconize;
bool istimerinit;
bool timerischanged;
wxString H24RenameNameHolder;

extern bool islightprogramonstartup;
extern bool isminimizedonstartup;


//timer variables
int timercurrenthour;
int currentunit;
int getseconds;
int getminutes;
wxString wxt_timercurrenthour;
wxString wxt_timercurrenthourpadded;


//32 profiles, 24 hours (code only uses 0-23 hours)
unsigned short int h24_Channel_1 [32] [24];
unsigned short int h24_Channel_2 [32] [24];
unsigned short int h24_Channel_3 [32] [24];
unsigned short int h24_Channel_4 [32] [24];
unsigned short int h24_Channel_5 [32] [24];
unsigned short int h24_Channel_6 [32] [24];
unsigned short int h24_Channel_7 [32] [24];
unsigned short int h24_Channel_8 [32] [24];
unsigned short int h24_Channel_9 [32] [24];
unsigned short int h24_Channel_10 [32] [24];
unsigned short int h24_Channel_11 [32] [24];
unsigned short int h24_Channel_12 [32] [24];
unsigned short int h24_Channel_13 [32] [24];
unsigned short int h24_Channel_14 [32] [24];
unsigned short int h24_Channel_15 [32] [24];
unsigned short int h24_Channel_16 [32] [24];
unsigned short int issmoothtransition [32] [24];
unsigned short int transitiontime [32] [24];
wxString h24profilenames [32];

//varibles for transition calculations
unsigned short int hourdifference_Channel_1;
float timedivide_Channel_1;
float timecalculated_Channel_1;
unsigned short int hourdifference_Channel_2;
float timedivide_Channel_2;
float timecalculated_Channel_2;
unsigned short int hourdifference_Channel_3;
float timedivide_Channel_3;
float timecalculated_Channel_3;
unsigned short int hourdifference_Channel_4;
float timedivide_Channel_4;
float timecalculated_Channel_4;
unsigned short int hourdifference_Channel_5;
float timedivide_Channel_5;
float timecalculated_Channel_5;
unsigned short int hourdifference_Channel_6;
float timedivide_Channel_6;
float timecalculated_Channel_6;
unsigned short int hourdifference_Channel_7;
float timedivide_Channel_7;
float timecalculated_Channel_7;
unsigned short int hourdifference_Channel_8;
float timedivide_Channel_8;
float timecalculated_Channel_8;
unsigned short int hourdifference_Channel_9;
float timedivide_Channel_9;
float timecalculated_Channel_9;
unsigned short int hourdifference_Channel_10;
float timedivide_Channel_10;
float timecalculated_Channel_10;
unsigned short int hourdifference_Channel_11;
float timedivide_Channel_11;
float timecalculated_Channel_11;
unsigned short int hourdifference_Channel_12;
float timedivide_Channel_12;
float timecalculated_Channel_12;
unsigned short int hourdifference_Channel_13;
float timedivide_Channel_13;
float timecalculated_Channel_13;
unsigned short int hourdifference_Channel_14;
float timedivide_Channel_14;
float timecalculated_Channel_14;
unsigned short int hourdifference_Channel_15;
float timedivide_Channel_15;
float timecalculated_Channel_15;
unsigned short int hourdifference_Channel_16;
float timedivide_Channel_16;
float timecalculated_Channel_16;

//data handler variables
int h24currentprofile;
wxString h24filename;
int h24numberofprofiles;
int h24numberoflines;
int h24pos;
int h24postimes;
int h24profilecount;

int h24currenthour;


//25 lines in each profile times 32 profiles is 1600 values
wxString h24buffer [800];


//output variables for timer
unsigned short int Channel_1_timer;
unsigned short int Channel_2_timer;
unsigned short int Channel_3_timer;
unsigned short int Channel_4_timer;
unsigned short int Channel_5_timer;
unsigned short int Channel_6_timer;
unsigned short int Channel_7_timer;
unsigned short int Channel_8_timer;
unsigned short int Channel_9_timer;
unsigned short int Channel_10_timer;
unsigned short int Channel_11_timer;
unsigned short int Channel_12_timer;
unsigned short int Channel_13_timer;
unsigned short int Channel_14_timer;
unsigned short int Channel_15_timer;
unsigned short int Channel_16_timer;

//holder variables for profile color, to default to
extern unsigned short int timer_ProfileChannel_1;
extern unsigned short int timer_ProfileChannel_2;
extern unsigned short int timer_ProfileChannel_3;
extern unsigned short int timer_ProfileChannel_4;
extern unsigned short int timer_ProfileChannel_5;
extern unsigned short int timer_ProfileChannel_6;
extern unsigned short int timer_ProfileChannel_7;
extern unsigned short int timer_ProfileChannel_8;
extern unsigned short int timer_ProfileChannel_9;
extern unsigned short int timer_ProfileChannel_10;
extern unsigned short int timer_ProfileChannel_11;
extern unsigned short int timer_ProfileChannel_12;
extern unsigned short int timer_ProfileChannel_13;
extern unsigned short int timer_ProfileChannel_14;
extern unsigned short int timer_ProfileChannel_15;
extern unsigned short int timer_ProfileChannel_16;

//another spot where not over allocating array causes problems
unsigned short int hourtransitioncalculations [17] [200];


BEGIN_EVENT_TABLE(H24Timer,wxDialog)
	//(*EventTable(H24Timer)
	//*)
END_EVENT_TABLE()

H24Timer::H24Timer(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(H24Timer)
	Create(parent, wxID_ANY, _("24-Hour Light Timer 0.1"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(820,486));
	Move(wxPoint(100,100));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Light Output Levels (Different levels per hour)"), wxPoint(104,32), wxSize(408,408), 0, _T("ID_STATICBOX1"));
	ListBox1 = new wxListBox(this, ID_LISTBOX1, wxPoint(8,24), wxSize(88,440), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	ListBox1->SetSelection( ListBox1->Append(_("12:00 AM")) );
	ListBox1->Append(_("01:00 AM"));
	ListBox1->Append(_("02:00 AM"));
	ListBox1->Append(_("03:00 AM"));
	ListBox1->Append(_("04:00 AM"));
	ListBox1->Append(_("05:00 AM"));
	ListBox1->Append(_("06:00 AM"));
	ListBox1->Append(_("07:00 AM"));
	ListBox1->Append(_("08:00 AM"));
	ListBox1->Append(_("09:00 AM"));
	ListBox1->Append(_("10:00 AM"));
	ListBox1->Append(_("11:00 AM"));
	ListBox1->Append(_("12:00 PM"));
	ListBox1->Append(_("01:00 PM"));
	ListBox1->Append(_("02:00 PM"));
	ListBox1->Append(_("03:00 PM"));
	ListBox1->Append(_("04:00 PM"));
	ListBox1->Append(_("05:00 PM"));
	ListBox1->Append(_("06:00 PM"));
	ListBox1->Append(_("07:00 PM"));
	ListBox1->Append(_("08:00 PM"));
	ListBox1->Append(_("09:00 PM"));
	ListBox1->Append(_("10:00 PM"));
	ListBox1->Append(_("11:00 PM"));
	wxFont ListBox1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	ListBox1->SetFont(ListBox1Font);
	Slider1 = new wxSlider(this, ID_SLIDER1, 0, 0, 255, wxPoint(160,80), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER1"));
	Slider2 = new wxSlider(this, ID_SLIDER2, 0, 0, 255, wxPoint(200,80), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER2"));
	Slider3 = new wxSlider(this, ID_SLIDER3, 0, 0, 255, wxPoint(240,80), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER3"));
	Slider4 = new wxSlider(this, ID_SLIDER4, 0, 0, 255, wxPoint(280,80), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER4"));
	Slider5 = new wxSlider(this, ID_SLIDER5, 0, 0, 255, wxPoint(320,80), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER5"));
	Slider6 = new wxSlider(this, ID_SLIDER6, 0, 0, 255, wxPoint(360,80), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER6"));
	Slider7 = new wxSlider(this, ID_SLIDER7, 0, 0, 255, wxPoint(400,80), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER7"));
	Slider8 = new wxSlider(this, ID_SLIDER8, 0, 0, 255, wxPoint(440,80), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER8"));
	Slider9 = new wxSlider(this, ID_SLIDER9, 0, 0, 255, wxPoint(160,272), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER9"));
	Slider10 = new wxSlider(this, ID_SLIDER10, 0, 0, 255, wxPoint(200,272), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER10"));
	Slider11 = new wxSlider(this, ID_SLIDER11, 0, 0, 255, wxPoint(240,272), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER11"));
	Slider12 = new wxSlider(this, ID_SLIDER12, 0, 0, 255, wxPoint(280,272), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER12"));
	Slider13 = new wxSlider(this, ID_SLIDER13, 0, 0, 255, wxPoint(320,272), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER13"));
	Slider14 = new wxSlider(this, ID_SLIDER14, 0, 0, 255, wxPoint(360,272), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER14"));
	Slider15 = new wxSlider(this, ID_SLIDER15, 0, 0, 255, wxPoint(400,272), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER15"));
	Slider16 = new wxSlider(this, ID_SLIDER16, 0, 0, 255, wxPoint(440,272), wxSize(24,144), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER16"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Label"), wxPoint(160,224), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Label"), wxPoint(200,224), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Label"), wxPoint(240,224), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Label"), wxPoint(280,224), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Label"), wxPoint(320,224), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Label"), wxPoint(360,224), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Label"), wxPoint(400,224), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Label"), wxPoint(440,224), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Label"), wxPoint(160,416), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Label"), wxPoint(200,416), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Label"), wxPoint(240,416), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Label"), wxPoint(280,416), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Label"), wxPoint(320,416), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("Label"), wxPoint(360,416), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Label"), wxPoint(400,416), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Label"), wxPoint(440,416), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Channel  1"), wxPoint(112,64), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("2"), wxPoint(208,64), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("3"), wxPoint(248,64), wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("4"), wxPoint(288,64), wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("5"), wxPoint(328,64), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	StaticText22 = new wxStaticText(this, ID_STATICTEXT22, _("6"), wxPoint(368,64), wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	StaticText23 = new wxStaticText(this, ID_STATICTEXT23, _("7"), wxPoint(408,64), wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	StaticText24 = new wxStaticText(this, ID_STATICTEXT24, _("8"), wxPoint(448,64), wxDefaultSize, 0, _T("ID_STATICTEXT24"));
	StaticText25 = new wxStaticText(this, ID_STATICTEXT25, _("Channel  9"), wxPoint(112,256), wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	StaticText26 = new wxStaticText(this, ID_STATICTEXT26, _("10"), wxPoint(200,256), wxDefaultSize, 0, _T("ID_STATICTEXT26"));
	StaticText27 = new wxStaticText(this, ID_STATICTEXT27, _("11"), wxPoint(240,256), wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	StaticText28 = new wxStaticText(this, ID_STATICTEXT28, _("12"), wxPoint(280,256), wxDefaultSize, 0, _T("ID_STATICTEXT28"));
	StaticText29 = new wxStaticText(this, ID_STATICTEXT29, _("13"), wxPoint(320,256), wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	StaticText30 = new wxStaticText(this, ID_STATICTEXT30, _("14"), wxPoint(360,256), wxDefaultSize, 0, _T("ID_STATICTEXT30"));
	StaticText31 = new wxStaticText(this, ID_STATICTEXT31, _("15"), wxPoint(400,256), wxDefaultSize, 0, _T("ID_STATICTEXT31"));
	StaticText32 = new wxStaticText(this, ID_STATICTEXT32, _("16"), wxPoint(440,256), wxDefaultSize, 0, _T("ID_STATICTEXT32"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Transition Settings"), wxPoint(528,264), wxSize(272,96), 0, _T("ID_STATICBOX2"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Activate 24-Hour Light Timer"), wxPoint(536,424), wxSize(272,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button1->SetExtraStyle( Button1->GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY );
	CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("Enable transition for this hour"), wxPoint(536,296), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox1->SetValue(false);
	wxFont CheckBox1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox1->SetFont(CheckBox1Font);
	StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("24-Hour Light Timer Profiles"), wxPoint(528,24), wxSize(272,224), 0, _T("ID_STATICBOX3"));
	Choice1 = new wxChoice(this, ID_CHOICE1, wxPoint(688,320), wxSize(104,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice1->SetSelection( Choice1->Append(_("5 minutes")) );
	Choice1->Append(_("10 minutes"));
	Choice1->Append(_("15 minutes"));
	Choice1->Append(_("30 minutes"));
	Choice1->Append(_("45 minutes"));
	StaticText33 = new wxStaticText(this, ID_STATICTEXT33, _("Transition to next hour takes"), wxPoint(536,328), wxDefaultSize, 0, _T("ID_STATICTEXT33"));
	wxFont StaticText33Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText33->SetFont(StaticText33Font);
	ListBox2 = new wxListBox(this, ID_LISTBOX2, wxPoint(536,56), wxSize(208,128), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX2"));
	ListBox2->SetSelection( ListBox2->Append(_("- Empty Profile List - ")) );
	ListBox2->SetFocus();
	wxFont ListBox2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	ListBox2->SetFont(ListBox2Font);
	Button2 = new wxButton(this, ID_BUTTON2, _("New"), wxPoint(536,208), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Button3 = new wxButton(this, ID_BUTTON3, _("Delete"), wxPoint(712,208), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	Button4 = new wxButton(this, ID_BUTTON4, _("Rename"), wxPoint(624,208), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	Button5 = new wxButton(this, ID_BUTTON5, _("Move\nUp"), wxPoint(744,56), wxSize(48,64), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	wxFont Button5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button5->SetFont(Button5Font);
	Button6 = new wxButton(this, ID_BUTTON6, _("Move\nDown"), wxPoint(744,120), wxSize(48,64), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	wxFont Button6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button6->SetFont(Button6Font);
	StaticText34 = new wxStaticText(this, ID_STATICTEXT34, _("Curent Time"), wxPoint(536,368), wxDefaultSize, 0, _T("ID_STATICTEXT34"));
	StaticText35 = new wxStaticText(this, ID_STATICTEXT35, _("Label"), wxPoint(544,392), wxDefaultSize, 0, _T("ID_STATICTEXT35"));
	wxFont StaticText35Font(16,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText35->SetFont(StaticText35Font);
	Button7 = new wxButton(this, ID_BUTTON7, _("Copy to Previous Hour"), wxPoint(120,440), wxSize(168,23), 0, wxDefaultValidator, _T("ID_BUTTON7"));
	Button8 = new wxButton(this, ID_BUTTON8, _("Copy to Next Hour"), wxPoint(336,440), wxSize(168,23), 0, wxDefaultValidator, _T("ID_BUTTON8"));
	StaticText36 = new wxStaticText(this, ID_STATICTEXT36, _("note: Use the \"X\" in the top right corner to deactivate"), wxPoint(528,456), wxDefaultSize, 0, _T("ID_STATICTEXT36"));
	wxFont StaticText36Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText36->SetFont(StaticText36Font);
	Button9 = new wxButton(this, ID_BUTTON9, _("Hide Lightput"), wxPoint(696,0), wxSize(115,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
	H24Timer1.SetOwner(this, ID_H24TIMER1);

	Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&H24Timer::OnListBox1Select);
	Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider1CmdScroll);
	Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider1CmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider2CmdScroll);
	Connect(ID_SLIDER2,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider2CmdScroll);
	Connect(ID_SLIDER3,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider3CmdScroll);
	Connect(ID_SLIDER3,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider3CmdScroll);
	Connect(ID_SLIDER4,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider4CmdScroll);
	Connect(ID_SLIDER4,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider4CmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider5CmdScroll);
	Connect(ID_SLIDER5,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider5CmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider6CmdScroll);
	Connect(ID_SLIDER6,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider6CmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider7CmdScroll);
	Connect(ID_SLIDER7,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider7CmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider8CmdScroll);
	Connect(ID_SLIDER8,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider8CmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider9CmdScroll);
	Connect(ID_SLIDER9,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider9CmdScroll);
	Connect(ID_SLIDER10,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider10CmdScroll);
	Connect(ID_SLIDER10,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider10CmdScroll);
	Connect(ID_SLIDER11,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider11CmdScroll);
	Connect(ID_SLIDER11,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider11CmdScroll);
	Connect(ID_SLIDER12,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider12CmdScroll);
	Connect(ID_SLIDER12,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider12CmdScroll);
	Connect(ID_SLIDER13,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider13CmdScroll);
	Connect(ID_SLIDER13,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider13CmdScroll);
	Connect(ID_SLIDER14,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider14CmdScroll);
	Connect(ID_SLIDER14,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider14CmdScroll);
	Connect(ID_SLIDER15,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider15CmdScroll);
	Connect(ID_SLIDER15,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider15CmdScroll);
	Connect(ID_SLIDER16,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&H24Timer::OnSlider16CmdScroll);
	Connect(ID_SLIDER16,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&H24Timer::OnSlider16CmdScroll);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24Timer::OnButton1Click);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&H24Timer::OnCheckBox1Click);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&H24Timer::OnChoice1Select);
	Connect(ID_LISTBOX2,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&H24Timer::OnListBox2Select);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24Timer::OnButton2Click);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24Timer::OnButton3Click);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24Timer::OnButton4Click);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24Timer::OnButton5Click);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24Timer::OnButton6Click);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24Timer::OnButton7Click);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24Timer::OnButton8Click);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24Timer::OnButton9Click);
	Connect(ID_H24TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&H24Timer::OnH24Timer1Trigger);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&H24Timer::OnClose);
	//*)

    h24currentprofile = 0;
    h24numberofprofiles = 0;
    istimeractive = false;
    timerischanged = false;
    //variable for timer start handling
    istimerinit = true;

    h24filename = wxT("./light_programs/h24timer.lightput");
    h24_loadprofiles();
    StaticText35->SetLabel(wxDateTime::Now().Format(wxT("%I:%M %p")));

    h24currenthour = wxAtoi(wxDateTime::Now().Format(wxT("%H")));

    h24_updatelabels();

    H24Timer1.Start(2000);

    if (islightprogramonstartup)
    {
        islightprogramonstartup = false;
       // if (isminimizedonstartup) isIconize = true;
     ///activate timer




        Button1->Enable(false);
    //if(!istimeractive) {
        //istimerinit = false;
        //stopyesorno = false;
        //disable everything
        StaticBox1->Enable(false);
        StaticBox2->Enable(false);
        StaticBox3->Enable(false);
        ListBox1->Enable(false);
        ListBox2->Enable(false);
        Slider1->Enable(false);
        Slider2->Enable(false);
        Slider3->Enable(false);
        Slider4->Enable(false);
        Slider5->Enable(false);
        Slider6->Enable(false);
        Slider7->Enable(false);
        Slider8->Enable(false);
        Slider9->Enable(false);
        Slider10->Enable(false);
        Slider11->Enable(false);
        Slider12->Enable(false);
        Slider13->Enable(false);
        Slider14->Enable(false);
        Slider15->Enable(false);
        Slider16->Enable(false);
        CheckBox1->Enable(false);
        Button2->Enable(false);
        Button3->Enable(false);
        Button4->Enable(false);
        Button5->Enable(false);
        Button6->Enable(false);
        Button7->Enable(false);
        Button8->Enable(false);
        StaticText1->Enable(false);
        StaticText2->Enable(false);
        StaticText3->Enable(false);
        StaticText4->Enable(false);
        StaticText5->Enable(false);
        StaticText6->Enable(false);
        StaticText7->Enable(false);
        StaticText8->Enable(false);
        StaticText9->Enable(false);
        StaticText10->Enable(false);
        StaticText11->Enable(false);
        StaticText12->Enable(false);
        StaticText13->Enable(false);
        StaticText14->Enable(false);
        StaticText15->Enable(false);
        StaticText16->Enable(false);
        StaticText17->Enable(false);
        StaticText18->Enable(false);
        StaticText19->Enable(false);
        StaticText20->Enable(false);
        StaticText21->Enable(false);
        StaticText22->Enable(false);
        StaticText23->Enable(false);
        StaticText24->Enable(false);
        StaticText25->Enable(false);
        StaticText26->Enable(false);
        StaticText27->Enable(false);
        StaticText28->Enable(false);
        StaticText29->Enable(false);
        StaticText30->Enable(false);
        StaticText31->Enable(false);
        StaticText32->Enable(false);
        StaticText33->Enable(false);
        Choice1->Enable(false);

        Button1->SetLabel(wxT("Deactivate 24-Hour Light Timer"));
        ListBox1->SetSelection(wxAtoi(wxDateTime::Now().Format(wxT("%H"))));

        h24_updatelabels();
        h24_calculatetransition();
        istimeractive = true;

    }
}

H24Timer::~H24Timer()
{
	//(*Destroy(H24Timer)
	//*)
}

//transition time selector
void H24Timer::OnChoice1Select(wxCommandEvent& event)
{
    transitiontime [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Choice1->GetSelection();
    timerischanged = true;
}

void H24Timer::h24_updatelabels(void)
{
    h24currentprofile = ListBox2->GetSelection();

    wxString wxt_s1 = wxString::Format(wxT("%i"),h24_Channel_1 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText1->SetLabel(wxt_s1);
    wxString wxt_s2 = wxString::Format(wxT("%i"),h24_Channel_2 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText2->SetLabel(wxt_s2);
    wxString wxt_s3 = wxString::Format(wxT("%i"),h24_Channel_3 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText3->SetLabel(wxt_s3);
    wxString wxt_s4 = wxString::Format(wxT("%i"),h24_Channel_4 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText4->SetLabel(wxt_s4);
    wxString wxt_s5 = wxString::Format(wxT("%i"),h24_Channel_5 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText5->SetLabel(wxt_s5);
    wxString wxt_s6 = wxString::Format(wxT("%i"),h24_Channel_6 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText6->SetLabel(wxt_s6);
    wxString wxt_s7 = wxString::Format(wxT("%i"),h24_Channel_7 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText7->SetLabel(wxt_s7);
    wxString wxt_s8 = wxString::Format(wxT("%i"),h24_Channel_8 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText8->SetLabel(wxt_s8);
    wxString wxt_s9 = wxString::Format(wxT("%i"),h24_Channel_9 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText9->SetLabel(wxt_s9);
    wxString wxt_s10 = wxString::Format(wxT("%i"),h24_Channel_10 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText10->SetLabel(wxt_s10);
    wxString wxt_s11 = wxString::Format(wxT("%i"),h24_Channel_11 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText11->SetLabel(wxt_s11);
    wxString wxt_s12 = wxString::Format(wxT("%i"),h24_Channel_12 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText12->SetLabel(wxt_s12);
    wxString wxt_s13 = wxString::Format(wxT("%i"),h24_Channel_13 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText13->SetLabel(wxt_s13);
    wxString wxt_s14 = wxString::Format(wxT("%i"),h24_Channel_14 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText14->SetLabel(wxt_s14);
    wxString wxt_s15 = wxString::Format(wxT("%i"),h24_Channel_15 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText15->SetLabel(wxt_s15);\
    wxString wxt_s16 = wxString::Format(wxT("%i"),h24_Channel_16 [h24currentprofile] [ListBox1->GetSelection()]);
    StaticText16->SetLabel(wxt_s16);

    CheckBox1->SetValue(issmoothtransition [h24currentprofile] [ListBox1->GetSelection()]);

    Choice1->SetSelection(transitiontime [h24currentprofile] [ListBox1->GetSelection()]);

    //update sliders
    Slider1->SetValue(h24_Channel_1 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider2->SetValue(h24_Channel_2 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider3->SetValue(h24_Channel_3 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider4->SetValue(h24_Channel_4 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider5->SetValue(h24_Channel_5 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider6->SetValue(h24_Channel_6 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider7->SetValue(h24_Channel_7 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider8->SetValue(h24_Channel_8 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider9->SetValue(h24_Channel_9 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider10->SetValue(h24_Channel_10 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider11->SetValue(h24_Channel_11 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider12->SetValue(h24_Channel_12 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider13->SetValue(h24_Channel_13 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider14->SetValue(h24_Channel_14 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider15->SetValue(h24_Channel_15 [h24currentprofile] [ListBox1->GetSelection()]);
    Slider16->SetValue(h24_Channel_16 [h24currentprofile] [ListBox1->GetSelection()]);

}

void H24Timer::OnSlider1CmdScroll(wxScrollEvent& event)
{
    h24_Channel_1 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider1->GetValue();
    wxString wxt_s1 = wxString::Format(wxT("%i"),Slider1->GetValue());
    StaticText1->SetLabel(wxt_s1);
    timerischanged = true;
}

void H24Timer::OnSlider2CmdScroll(wxScrollEvent& event)
{
    h24_Channel_2 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider2->GetValue();
    wxString wxt_s2 = wxString::Format(wxT("%i"),Slider2->GetValue());
    StaticText2->SetLabel(wxt_s2);
    timerischanged = true;

}

void H24Timer::OnSlider3CmdScroll(wxScrollEvent& event)
{
    h24_Channel_3 [h24currentprofile] [ListBox1->GetSelection()] = Slider3->GetValue();
    wxString wxt_s3 = wxString::Format(wxT("%i"),Slider3->GetValue());
    StaticText3->SetLabel(wxt_s3);
    timerischanged = true;
}

void H24Timer::OnSlider4CmdScroll(wxScrollEvent& event)
{
    h24_Channel_4 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider4->GetValue();
    wxString wxt_s4 = wxString::Format(wxT("%i"),Slider4->GetValue());
    StaticText4->SetLabel(wxt_s4);
    timerischanged = true;
}

void H24Timer::OnSlider5CmdScroll(wxScrollEvent& event)
{
    h24_Channel_5 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider5->GetValue();
    wxString wxt_s5 = wxString::Format(wxT("%i"),Slider5->GetValue());
    StaticText5->SetLabel(wxt_s5);
    timerischanged = true;
}

void H24Timer::OnSlider6CmdScroll(wxScrollEvent& event)
{
    h24_Channel_6 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider6->GetValue();
    wxString wxt_s6 = wxString::Format(wxT("%i"),Slider6->GetValue());
    StaticText6->SetLabel(wxt_s6);
    timerischanged = true;
}

void H24Timer::OnSlider7CmdScroll(wxScrollEvent& event)
{
    h24_Channel_7 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider7->GetValue();
    wxString wxt_s7 = wxString::Format(wxT("%i"),Slider7->GetValue());
    StaticText7->SetLabel(wxt_s7);
    timerischanged = true;
}

void H24Timer::OnSlider8CmdScroll(wxScrollEvent& event)
{
    h24_Channel_8 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider8->GetValue();
    wxString wxt_s8 = wxString::Format(wxT("%i"),Slider8->GetValue());
    StaticText8->SetLabel(wxt_s8);
    timerischanged = true;
}

void H24Timer::OnSlider9CmdScroll(wxScrollEvent& event)
{
    h24_Channel_9 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider9->GetValue();
    wxString wxt_s9 = wxString::Format(wxT("%i"),Slider9->GetValue());
    StaticText9->SetLabel(wxt_s9);
    timerischanged = true;
}

void H24Timer::OnSlider10CmdScroll(wxScrollEvent& event)
{
    h24_Channel_10 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider10->GetValue();
    wxString wxt_s10 = wxString::Format(wxT("%i"),Slider10->GetValue());
    StaticText10->SetLabel(wxt_s10);
    timerischanged = true;
}

void H24Timer::OnSlider11CmdScroll(wxScrollEvent& event)
{
    h24_Channel_11 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider11->GetValue();
    wxString wxt_s11 = wxString::Format(wxT("%i"),Slider11->GetValue());
    StaticText11->SetLabel(wxt_s11);
    timerischanged = true;
}

void H24Timer::OnSlider12CmdScroll(wxScrollEvent& event)
{
    h24_Channel_12 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider12->GetValue();
    wxString wxt_s12 = wxString::Format(wxT("%i"),Slider12->GetValue());
    StaticText12->SetLabel(wxt_s12);
    timerischanged = true;
}

void H24Timer::OnSlider13CmdScroll(wxScrollEvent& event)
{
    h24_Channel_13 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider13->GetValue();
    wxString wxt_s13 = wxString::Format(wxT("%i"),Slider13->GetValue());
    StaticText13->SetLabel(wxt_s13);
    timerischanged = true;
}

void H24Timer::OnSlider14CmdScroll(wxScrollEvent& event)
{
    h24_Channel_14 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider14->GetValue();
    wxString wxt_s14 = wxString::Format(wxT("%i"),Slider14->GetValue());
    StaticText14->SetLabel(wxt_s14);
    }

void H24Timer::OnSlider15CmdScroll(wxScrollEvent& event)
{
    h24_Channel_15 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider15->GetValue();
    wxString wxt_s15 = wxString::Format(wxT("%i"),Slider15->GetValue());
    StaticText15->SetLabel(wxt_s15);
    timerischanged = true;
}

void H24Timer::OnSlider16CmdScroll(wxScrollEvent& event)
{
    h24_Channel_16 [ListBox2->GetSelection()] [ListBox1->GetSelection()] = Slider16->GetValue();
    wxString wxt_s16 = wxString::Format(wxT("%i"),Slider16->GetValue());
    StaticText16->SetLabel(wxt_s16);
    timerischanged = true;
}

void H24Timer::OnListBox1Select(wxCommandEvent& event)
{
    h24_updatelabels();
}

void H24Timer::OnCheckBox1Click(wxCommandEvent& event)
{
    if (CheckBox1->GetValue()) issmoothtransition [ListBox2->GetSelection()] [ListBox1->GetSelection()] = 1;
    else issmoothtransition [ListBox2->GetSelection()] [ListBox1->GetSelection()] = 0;
    timerischanged = true;

}

void H24Timer::OnH24Timer1Trigger(wxTimerEvent& event)
{

            //wxMessageBox (wxT("should happen many times"),wxT("test"));

//this shit just isn't working at all




    //this line redraws the current time after checking that the current time
    //doesn't equal the time currently being displayed on the screen

    if (h24currenthour != wxAtoi(wxDateTime::Now().Format(wxT("%H")))) {
            h24currenthour = wxAtoi(wxDateTime::Now().Format(wxT("%H")));
            ListBox1->SetSelection(wxAtoi(wxDateTime::Now().Format(wxT("%H"))));
            h24_updatelabels();
            h24_calculatetransition();
            //wxMessageBox (wxT("should happen once"),wxT("test"));
    }


	if (StaticText35->GetLabel() != wxDateTime::Now().Format(wxT("%I:%M %p"))) {
	    StaticText35->SetLabel(wxDateTime::Now().Format(wxT("%I:%M %p")));
        //ListBox1->SetSelection(wxAtoi(wxDateTime::Now().Format(wxT("%H"))));
	}

    if (istimeractive) {
        //ListBox1->SetSelection(wxAtoi(wxDateTime::Now().Format(wxT("%H"))));
        getminutes = wxAtoi(wxDateTime::Now().Format(wxT("%M")));
        getseconds = wxAtoi(wxDateTime::Now().Format(wxT("%S")));
        currentunit = (((getminutes * 60) + getseconds) / 20);
        if (currentunit == 0) currentunit = 1;

        Channel_1_timer = hourtransitioncalculations [1] [currentunit];
        Channel_2_timer = hourtransitioncalculations [2] [currentunit];
        Channel_3_timer = hourtransitioncalculations [3] [currentunit];
        Channel_4_timer = hourtransitioncalculations [4] [currentunit];
        Channel_5_timer = hourtransitioncalculations [5] [currentunit];
        Channel_6_timer = hourtransitioncalculations [6] [currentunit];
        Channel_7_timer = hourtransitioncalculations [7] [currentunit];
        Channel_8_timer = hourtransitioncalculations [8] [currentunit];
        Channel_9_timer = hourtransitioncalculations [9] [currentunit];
        Channel_10_timer = hourtransitioncalculations [10] [currentunit];
        Channel_11_timer = hourtransitioncalculations [11] [currentunit];
        Channel_12_timer = hourtransitioncalculations [12] [currentunit];
        Channel_13_timer = hourtransitioncalculations [13] [currentunit];
        Channel_14_timer = hourtransitioncalculations [14] [currentunit];
        Channel_15_timer = hourtransitioncalculations [15] [currentunit];
        Channel_16_timer = hourtransitioncalculations [16] [currentunit];
  }


}


void H24Timer::h24_loadprofiles(void)
{
wxTextFile h24file;
h24file.Open(h24filename, wxConvISO8859_1);
//this line checks if the FILE HAS 3 LINES OR LESS, indicationg that there are no profiles
//then returns out of the profile loading function

//new idea, get line count, divide by 19, thats number of profiles
//subtract 1 from the line count to fix loading bug
h24numberoflines = h24file.GetLineCount() - 1;
//add 1 to the value to fix the assignment of bsnumberofprofiles
h24numberofprofiles = (h24numberoflines + 1) / 25;



if (h24file.GetLineCount() <= 3)return;

int namepos = 1;
ListBox2->Clear();
h24pos = 2;
h24postimes = 0;
int intbuffer;
//count starts at 2 because the getfirstline function before the do loop gets the first count
int count = 2;
//needed to use the getfirstline function, so i did this
    h24buffer [1] = h24file.GetFirstLine();
    ListBox2->Append(h24buffer [1]);
    h24profilenames [0] = h24buffer [1];
    //h24profilenames [namepos++] = h24buffer [h24pos + (h24postimes * 25)];

//this code is less than perfect, this do loop puts all the values from the saved proflie file
//into a buffer, as well as puts the name value, number of beats value, and time value
//into SequencerPrrofileNames, SequencerBeats, and SequencerTime for using and saving later
do {

    h24buffer [h24pos + (h24postimes * 25)] = h24file.GetNextLine();

    if (h24pos == 1) {ListBox2->Append(h24buffer [h24pos + (h24postimes * 25)]); h24profilenames [namepos++] = h24buffer [h24pos + (h24postimes * 25)];}
    //wxString displayValue = wxString::Format(wxT("%i"),ListBox1->GetSelection());
    //wxMessageBox ( displayValue, displayValue);
    //if (h24pos == 2) {Choice1->SetSelection(wxAtoi(buffer [((h24postimes * 19) + 2)])); SequencerBeats [nameh24pos] = wxAtoi(buffer [((h24postimes * 19) + 2)]);}
    //if (h24pos == 3) {TextCtrl1->SetValue(buffer [((h24postimes * 19) + 3)]); SequencerTime [nameh24pos] = wxAtoi(buffer [((h24postimes * 19) + 3)]); nameh24pos++;}
    h24pos++;
    //the if in the next line fixes the problem with the last profile not loading properly
    if (count < h24numberoflines)count++;
    //the nested, 2nd if in the next line fixes the problem with the last profile not loading properly also
    if (h24pos == 26) {h24pos=1;h24postimes++;if (count == h24numberoflines)count++;}
    //those other lines above make sure this while condition stays met untill after
    //the last line of the last profile loads
} while (count <= h24numberoflines);


    //int selection = ListBox1->GetSelection();
    wxString DMXbuffer;
    h24pos = 0;
    // vpos holds the beat posirtion
    int vpos = 1;
    count = 0;
    //this next line gets the number of profiles by dividing the number of lines in
    //the save file by 19, the number of lines each profile takes.
    h24profilecount = (h24numberoflines / 25);
    int profilepos = 0;


//this do loop decodes the lines that hold the DMX values per beat (separated by !'s)
//note it does not search for ! it knows the numbers of spaces to travel
//must save profile with leading 0's

do {
    h24pos = 0;
    vpos = 1;
//12:00 AM

    wxString udbuffer = h24buffer [((profilepos * 25) +2)];

    //wxString displayValue = wxString::Format(wxT("%i"),numberoflines);
    //wxMessageBox ( udbuffer, udbuffer);
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [0] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [0] = wxAtoi(DMXbuffer);
        // moves h24pos past exclamation point
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;



//1:00 AM
    udbuffer = h24buffer [((profilepos * 25) +3)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [1] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [1] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//2:00 AM
    udbuffer = h24buffer [((profilepos * 25) +4)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [2] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [2] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//3:00 AM
    udbuffer = h24buffer [((profilepos * 25) +5)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [3] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [3] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;


//4:00 AM
    udbuffer = h24buffer [((profilepos * 25) +6)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [4] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [4] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//5:00 AM
    udbuffer = h24buffer [((profilepos * 25) +7)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [5] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [5] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//6:00 AM
    udbuffer = h24buffer [((profilepos * 25) +8)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [6] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [6] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//7:00 AM
    udbuffer = h24buffer [((profilepos * 25) +9)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [7] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [7] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//8:00 AM
    udbuffer = h24buffer [((profilepos * 25) +10)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [8] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [8] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//9:00 AM
    udbuffer = h24buffer [((profilepos * 25) +11)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [9] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [9] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//10:00 AM
    udbuffer = h24buffer [((profilepos * 25) +12)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [10] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [10] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//11:00 AM
    udbuffer = h24buffer [((profilepos * 25) +13)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [11] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [11] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//12:00 PM
    udbuffer = h24buffer [((profilepos * 25) +14)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [12] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [12] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//1:00 PM
    udbuffer = h24buffer [((profilepos * 25) +15)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [13] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [13] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//2:00 PM
    udbuffer = h24buffer [((profilepos * 25) +16)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [14] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [14] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//3:00 PM
    udbuffer = h24buffer [((profilepos * 25) +17)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [15] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [15] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//4:00 PM
    udbuffer = h24buffer [((profilepos * 25) +18)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [16] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [16] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//5:00 PM
    udbuffer = h24buffer [((profilepos * 25) +19)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [17] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [17] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//6:00 PM
    udbuffer = h24buffer [((profilepos * 25) +20)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [18] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [18] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//7:00 PM
    udbuffer = h24buffer [((profilepos * 25) +21)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [19] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [19] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//8:00 PM
    udbuffer = h24buffer [((profilepos * 25) +22)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [20] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [20] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//9:00 PM
    udbuffer = h24buffer [((profilepos * 25) +23)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [21] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [21] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//10:00 PM
    udbuffer = h24buffer [((profilepos * 25) +24)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [22] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [22] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;

//11:00 PM
    udbuffer = h24buffer [((profilepos * 25) +25)];
    do{
        DMXbuffer.clear();
        do {
            DMXbuffer = DMXbuffer + udbuffer [h24pos];
            h24pos++;
            count++;
        } while (count < 3);
        count = 0;
        if (vpos == 1) h24_Channel_1 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 2) h24_Channel_2 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 3) h24_Channel_3 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 4) h24_Channel_4 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 5) h24_Channel_5 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 6) h24_Channel_6 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 7) h24_Channel_7 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 8) h24_Channel_8 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 9) h24_Channel_9 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 10) h24_Channel_10 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 11) h24_Channel_11 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 12) h24_Channel_12 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 13) h24_Channel_13 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 14) h24_Channel_14 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 15) h24_Channel_15 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 16) h24_Channel_16 [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 17) issmoothtransition [profilepos] [23] = wxAtoi(DMXbuffer);
        if (vpos == 18) transitiontime [profilepos] [23] = wxAtoi(DMXbuffer);
        h24pos++;
        vpos++;
    } while (vpos < 19);
    vpos = 1;
    h24pos = 0;



  profilepos++;
  }while (h24profilecount >= profilepos);


    //h24_loadprofiles();
    h24_updatelabels();
    ListBox2->SetSelection(0);
    timerischanged = false;

}




//move up button
void H24Timer::OnButton5Click(wxCommandEvent& event)
{
    h24currentprofile = ListBox2->GetSelection();
    //this if condition makes sure there's somewhere to move the profile to
    if (h24currentprofile > 0){


        int copyChannel_1 [24];
        int copyChannel_2 [24];
        int copyChannel_3 [24];
        int copyChannel_4 [24];
        int copyChannel_5 [24];
        int copyChannel_6 [24];
        int copyChannel_7 [24];
        int copyChannel_8 [24];
        int copyChannel_9 [24];
        int copyChannel_10 [24];
        int copyChannel_11 [24];
        int copyChannel_12 [24];
        int copyChannel_13 [24];
        int copyChannel_14 [24];
        int copyChannel_15 [24];
        int copyChannel_16 [24];
        int copyissmoothtransition [24];
        int copytransitiontime [24];
        wxString copyprofilename;
        int copybeatcount;

   //wxMessageBox ( h24profilenames [0], wxT("0"));
    //wxMessageBox ( h24profilenames [1], wxT("1"));
    //wxMessageBox ( h24profilenames [2], wxT("2"));
    //wxMessageBox ( h24profilenames [3], wxT("3"));

        //this code swaps the order of the name variables in the SequencerProfileNames array
        //copy value into buffer (the value above the current profile to be moved down)
        copyprofilename = h24profilenames [h24currentprofile - 1];
        //copy over buffered value
        h24profilenames [h24currentprofile -1] = h24profilenames [h24currentprofile];
        //copy buffered value to propper spot
        h24profilenames [h24currentprofile] = copyprofilename;


// this for loop swaps all the DMX data
for (copybeatcount = 0; copybeatcount < 24; copybeatcount++ )
        {
//displayValue = wxString::Format(wxT("%i"),SequencerChannel_1 [sequencercurrentprofile-1][copybeatcount]);
//wxMessageBox ( displayValue , wxT("sequencercurrentprofile"));
        //copy value into buffer the value above the current profile to be moved down
        copyChannel_1 [copybeatcount] = h24_Channel_1 [h24currentprofile-1][copybeatcount];

//displayValue = wxString::Format(wxT("%i"),SequencerChannel_1 [sequencercurrentprofile][copybeatcount]);
//wxMessageBox ( displayValue , wxT("sequencercurrentprofile"));

        //copy over buffered value
        h24_Channel_1 [h24currentprofile-1][copybeatcount] = h24_Channel_1 [h24currentprofile][copybeatcount];
        //copy buffered value to propper spot
        h24_Channel_1 [h24currentprofile][copybeatcount] = copyChannel_1 [copybeatcount];

//channel 2
        copyChannel_2 [copybeatcount] = h24_Channel_2 [h24currentprofile-1][copybeatcount];
        h24_Channel_2 [h24currentprofile-1][copybeatcount] = h24_Channel_2 [h24currentprofile][copybeatcount];
        h24_Channel_2 [h24currentprofile][copybeatcount] = copyChannel_2 [copybeatcount];
//Channel_3
        copyChannel_3 [copybeatcount] = h24_Channel_3 [h24currentprofile-1][copybeatcount];
        h24_Channel_3 [h24currentprofile-1][copybeatcount] = h24_Channel_3 [h24currentprofile][copybeatcount];
        h24_Channel_3 [h24currentprofile][copybeatcount] = copyChannel_3 [copybeatcount];
//Channel_4
        copyChannel_4 [copybeatcount] = h24_Channel_4 [h24currentprofile-1][copybeatcount];
        h24_Channel_4 [h24currentprofile-1][copybeatcount] = h24_Channel_4 [h24currentprofile][copybeatcount];
        h24_Channel_4 [h24currentprofile][copybeatcount] = copyChannel_4 [copybeatcount];
//Channel_5
        copyChannel_5 [copybeatcount] = h24_Channel_5 [h24currentprofile-1][copybeatcount];
        h24_Channel_5 [h24currentprofile-1][copybeatcount] = h24_Channel_5 [h24currentprofile][copybeatcount];
        h24_Channel_5 [h24currentprofile][copybeatcount] = copyChannel_5 [copybeatcount];
//Channel_6
        copyChannel_6 [copybeatcount] = h24_Channel_6 [h24currentprofile-1][copybeatcount];
        h24_Channel_6 [h24currentprofile-1][copybeatcount] = h24_Channel_6 [h24currentprofile][copybeatcount];
        h24_Channel_6 [h24currentprofile][copybeatcount] = copyChannel_6 [copybeatcount];
//Channel_7
        copyChannel_7 [copybeatcount] = h24_Channel_7 [h24currentprofile-1][copybeatcount];
        h24_Channel_7 [h24currentprofile-1][copybeatcount] = h24_Channel_7 [h24currentprofile][copybeatcount];
        h24_Channel_7 [h24currentprofile][copybeatcount] = copyChannel_7 [copybeatcount];
//Channel_8
        copyChannel_8 [copybeatcount] = h24_Channel_8 [h24currentprofile-1][copybeatcount];
        h24_Channel_8 [h24currentprofile-1][copybeatcount] = h24_Channel_8 [h24currentprofile][copybeatcount];
        h24_Channel_8 [h24currentprofile][copybeatcount] = copyChannel_8 [copybeatcount];
//Channel_9
        copyChannel_9 [copybeatcount] = h24_Channel_9 [h24currentprofile-1][copybeatcount];
        h24_Channel_9 [h24currentprofile-1][copybeatcount] = h24_Channel_9 [h24currentprofile][copybeatcount];
        h24_Channel_9 [h24currentprofile][copybeatcount] = copyChannel_9 [copybeatcount];
//Channel_10
        copyChannel_10 [copybeatcount] = h24_Channel_10 [h24currentprofile-1][copybeatcount];
        h24_Channel_10 [h24currentprofile-1][copybeatcount] = h24_Channel_10 [h24currentprofile][copybeatcount];
        h24_Channel_10 [h24currentprofile][copybeatcount] = copyChannel_10 [copybeatcount];
//Channel_11
        copyChannel_11 [copybeatcount] = h24_Channel_11 [h24currentprofile-1][copybeatcount];
        h24_Channel_11 [h24currentprofile-1][copybeatcount] = h24_Channel_11 [h24currentprofile][copybeatcount];
        h24_Channel_11 [h24currentprofile][copybeatcount] = copyChannel_11 [copybeatcount];
//Channel_12
        copyChannel_12 [copybeatcount] = h24_Channel_12 [h24currentprofile-1][copybeatcount];
        h24_Channel_12 [h24currentprofile-1][copybeatcount] = h24_Channel_12 [h24currentprofile][copybeatcount];
        h24_Channel_12 [h24currentprofile][copybeatcount] = copyChannel_12 [copybeatcount];
//Channel_13
        copyChannel_13 [copybeatcount] = h24_Channel_13 [h24currentprofile-1][copybeatcount];
        h24_Channel_13 [h24currentprofile-1][copybeatcount] = h24_Channel_13 [h24currentprofile][copybeatcount];
        h24_Channel_13 [h24currentprofile][copybeatcount] = copyChannel_13 [copybeatcount];
//Channel_14
        copyChannel_14 [copybeatcount] = h24_Channel_14 [h24currentprofile-1][copybeatcount];
        h24_Channel_14 [h24currentprofile-1][copybeatcount] = h24_Channel_14 [h24currentprofile][copybeatcount];
        h24_Channel_14 [h24currentprofile][copybeatcount] = copyChannel_14 [copybeatcount];
//Channel_15
        copyChannel_15 [copybeatcount] = h24_Channel_15 [h24currentprofile-1][copybeatcount];
        h24_Channel_15 [h24currentprofile-1][copybeatcount] = h24_Channel_15 [h24currentprofile][copybeatcount];
        h24_Channel_15 [h24currentprofile][copybeatcount] = copyChannel_15 [copybeatcount];
//Channel_16
        copyChannel_16 [copybeatcount] = h24_Channel_16 [h24currentprofile-1][copybeatcount];
        h24_Channel_16 [h24currentprofile-1][copybeatcount] = h24_Channel_16 [h24currentprofile][copybeatcount];
        h24_Channel_16 [h24currentprofile][copybeatcount] = copyChannel_16 [copybeatcount];
//issmoothtransition
        copyissmoothtransition[copybeatcount] = issmoothtransition [h24currentprofile-1][copybeatcount];
        issmoothtransition [h24currentprofile-1][copybeatcount] = issmoothtransition [h24currentprofile][copybeatcount];
        issmoothtransition [h24currentprofile][copybeatcount] = copyissmoothtransition [copybeatcount];
//transitiontime
        copytransitiontime [copybeatcount] = transitiontime [h24currentprofile-1][copybeatcount];
        transitiontime [h24currentprofile-1][copybeatcount] = transitiontime [h24currentprofile][copybeatcount];
        transitiontime [h24currentprofile][copybeatcount] = copytransitiontime [copybeatcount];

    }//close for loop





        //This code swaps the order of the profiles in the listbox

    //wxMessageBox ( h24profilenames [0], wxT("0"));
    //wxMessageBox ( h24profilenames [1], wxT("1"));
    //wxMessageBox ( h24profilenames [2], wxT("2"));
    //wxMessageBox ( h24profilenames [3], wxT("3"));


        //insert values in correct spot on listbox
        ListBox2->Insert(h24profilenames [h24currentprofile],h24currentprofile);
        ListBox2->Insert(h24profilenames [h24currentprofile-1],h24currentprofile-1);

        //ListBox2->Insert(wxT("1"),h24currentprofile);
        //ListBox2->Insert(wxT("2"),h24currentprofile-1);

        //delete the old listbox values
//this area also needed to be changed for linux

        //fix the "listbox delete" bug
        int holderforvaluethatgetsinadvertentlydeleted = h24currentprofile;

        ListBox2->Delete(h24currentprofile);

        //put the value back into sequencercurrentprofile
        h24currentprofile = holderforvaluethatgetsinadvertentlydeleted;

        ListBox2->Delete(h24currentprofile+1);

        //put the value back into sequencercurrentprofile again
        h24currentprofile = holderforvaluethatgetsinadvertentlydeleted;


        //set the listbox selection in the right spot
        ListBox2->SetSelection(--h24currentprofile);

        timerischanged = true;
    }
}


void H24Timer::OnListBox2Select(wxCommandEvent& event)
{
    h24_updatelabels();
    h24_calculatetransition();
}

//move down button
void H24Timer::OnButton6Click(wxCommandEvent& event)
{
        h24currentprofile = ListBox2->GetSelection();
    //this if condition makes sure there's somewhere to move the profile to
    if ((h24currentprofile + 1 < h24numberofprofiles)&&(h24currentprofile+1 > 0)){


        int copyChannel_1 [24];
        int copyChannel_2 [24];
        int copyChannel_3 [24];
        int copyChannel_4 [24];
        int copyChannel_5 [24];
        int copyChannel_6 [24];
        int copyChannel_7 [24];
        int copyChannel_8 [24];
        int copyChannel_9 [24];
        int copyChannel_10 [24];
        int copyChannel_11 [24];
        int copyChannel_12 [24];
        int copyChannel_13 [24];
        int copyChannel_14 [24];
        int copyChannel_15 [24];
        int copyChannel_16 [24];
        int copyissmoothtransition [24];
        int copytransitiontime [24];
        wxString copyprofilename;
        int copybeatcount;

   //wxMessageBox ( h24profilenames [0], wxT("0"));
    //wxMessageBox ( h24profilenames [1], wxT("1"));
    //wxMessageBox ( h24profilenames [2], wxT("2"));
    //wxMessageBox ( h24profilenames [3], wxT("3"));

        //this code swaps the order of the name variables in the SequencerProfileNames array
        //copy value into buffer (the value above the current profile to be moved down)
        copyprofilename = h24profilenames [h24currentprofile + 1];
        //copy over buffered value
        h24profilenames [h24currentprofile + 1] = h24profilenames [h24currentprofile];
        //copy buffered value to propper spot
        h24profilenames [h24currentprofile] = copyprofilename;


// this for loop swaps all the DMX data
for (copybeatcount = 0; copybeatcount < 24; copybeatcount++ )
        {
        copyChannel_1 [copybeatcount] = h24_Channel_1 [h24currentprofile+1][copybeatcount];
        //copy over buffered value
        h24_Channel_1 [h24currentprofile+1][copybeatcount] = h24_Channel_1 [h24currentprofile][copybeatcount];
        //copy buffered value to propper spot
        h24_Channel_1 [h24currentprofile][copybeatcount] = copyChannel_1 [copybeatcount];

//channel 2
        copyChannel_2 [copybeatcount] = h24_Channel_2 [h24currentprofile+1][copybeatcount];
        h24_Channel_2 [h24currentprofile+1][copybeatcount] = h24_Channel_2 [h24currentprofile][copybeatcount];
        h24_Channel_2 [h24currentprofile][copybeatcount] = copyChannel_2 [copybeatcount];
//Channel_3
        copyChannel_3 [copybeatcount] = h24_Channel_3 [h24currentprofile+1][copybeatcount];
        h24_Channel_3 [h24currentprofile+1][copybeatcount] = h24_Channel_3 [h24currentprofile][copybeatcount];
        h24_Channel_3 [h24currentprofile][copybeatcount] = copyChannel_3 [copybeatcount];
//Channel_4
        copyChannel_4 [copybeatcount] = h24_Channel_4 [h24currentprofile+1][copybeatcount];
        h24_Channel_4 [h24currentprofile+1][copybeatcount] = h24_Channel_4 [h24currentprofile][copybeatcount];
        h24_Channel_4 [h24currentprofile][copybeatcount] = copyChannel_4 [copybeatcount];
//Channel_5
        copyChannel_5 [copybeatcount] = h24_Channel_5 [h24currentprofile+1][copybeatcount];
        h24_Channel_5 [h24currentprofile+1][copybeatcount] = h24_Channel_5 [h24currentprofile][copybeatcount];
        h24_Channel_5 [h24currentprofile][copybeatcount] = copyChannel_5 [copybeatcount];
//Channel_6
        copyChannel_6 [copybeatcount] = h24_Channel_6 [h24currentprofile+1][copybeatcount];
        h24_Channel_6 [h24currentprofile+1][copybeatcount] = h24_Channel_6 [h24currentprofile][copybeatcount];
        h24_Channel_6 [h24currentprofile][copybeatcount] = copyChannel_6 [copybeatcount];
//Channel_7
        copyChannel_7 [copybeatcount] = h24_Channel_7 [h24currentprofile+1][copybeatcount];
        h24_Channel_7 [h24currentprofile+1][copybeatcount] = h24_Channel_7 [h24currentprofile][copybeatcount];
        h24_Channel_7 [h24currentprofile][copybeatcount] = copyChannel_7 [copybeatcount];
//Channel_8
        copyChannel_8 [copybeatcount] = h24_Channel_8 [h24currentprofile+1][copybeatcount];
        h24_Channel_8 [h24currentprofile+1][copybeatcount] = h24_Channel_8 [h24currentprofile][copybeatcount];
        h24_Channel_8 [h24currentprofile][copybeatcount] = copyChannel_8 [copybeatcount];
//Channel_9
        copyChannel_9 [copybeatcount] = h24_Channel_9 [h24currentprofile+1][copybeatcount];
        h24_Channel_9 [h24currentprofile+1][copybeatcount] = h24_Channel_9 [h24currentprofile][copybeatcount];
        h24_Channel_9 [h24currentprofile][copybeatcount] = copyChannel_9 [copybeatcount];
//Channel_10
        copyChannel_10 [copybeatcount] = h24_Channel_10 [h24currentprofile+1][copybeatcount];
        h24_Channel_10 [h24currentprofile+1][copybeatcount] = h24_Channel_10 [h24currentprofile][copybeatcount];
        h24_Channel_10 [h24currentprofile][copybeatcount] = copyChannel_10 [copybeatcount];
//Channel_11
        copyChannel_11 [copybeatcount] = h24_Channel_11 [h24currentprofile+1][copybeatcount];
        h24_Channel_11 [h24currentprofile+1][copybeatcount] = h24_Channel_11 [h24currentprofile][copybeatcount];
        h24_Channel_11 [h24currentprofile][copybeatcount] = copyChannel_11 [copybeatcount];
//Channel_12
        copyChannel_12 [copybeatcount] = h24_Channel_12 [h24currentprofile+1][copybeatcount];
        h24_Channel_12 [h24currentprofile+1][copybeatcount] = h24_Channel_12 [h24currentprofile][copybeatcount];
        h24_Channel_12 [h24currentprofile][copybeatcount] = copyChannel_12 [copybeatcount];
//Channel_13
        copyChannel_13 [copybeatcount] = h24_Channel_13 [h24currentprofile+1][copybeatcount];
        h24_Channel_13 [h24currentprofile+1][copybeatcount] = h24_Channel_13 [h24currentprofile][copybeatcount];
        h24_Channel_13 [h24currentprofile][copybeatcount] = copyChannel_13 [copybeatcount];
//Channel_14
        copyChannel_14 [copybeatcount] = h24_Channel_14 [h24currentprofile+1][copybeatcount];
        h24_Channel_14 [h24currentprofile+1][copybeatcount] = h24_Channel_14 [h24currentprofile][copybeatcount];
        h24_Channel_14 [h24currentprofile][copybeatcount] = copyChannel_14 [copybeatcount];
//Channel_15
        copyChannel_15 [copybeatcount] = h24_Channel_15 [h24currentprofile+1][copybeatcount];
        h24_Channel_15 [h24currentprofile+1][copybeatcount] = h24_Channel_15 [h24currentprofile][copybeatcount];
        h24_Channel_15 [h24currentprofile][copybeatcount] = copyChannel_15 [copybeatcount];
//Channel_16
        copyChannel_16 [copybeatcount] = h24_Channel_16 [h24currentprofile+1][copybeatcount];
        h24_Channel_16 [h24currentprofile+1][copybeatcount] = h24_Channel_16 [h24currentprofile][copybeatcount];
        h24_Channel_16 [h24currentprofile][copybeatcount] = copyChannel_16 [copybeatcount];
//issmoothtransition
        copyissmoothtransition[copybeatcount] = issmoothtransition [h24currentprofile+1][copybeatcount];
        issmoothtransition [h24currentprofile+1][copybeatcount] = issmoothtransition [h24currentprofile][copybeatcount];
        issmoothtransition [h24currentprofile][copybeatcount] = copyissmoothtransition [copybeatcount];
//transitiontime
        copytransitiontime [copybeatcount] = transitiontime [h24currentprofile+1][copybeatcount];
        transitiontime [h24currentprofile+1][copybeatcount] = transitiontime [h24currentprofile][copybeatcount];
        transitiontime [h24currentprofile][copybeatcount] = copytransitiontime [copybeatcount];

    }//close for loop





        //This code swaps the order of the profiles in the listbox

    //wxMessageBox ( h24profilenames [0], wxT("0"));
    //wxMessageBox ( h24profilenames [1], wxT("1"));
    //wxMessageBox ( h24profilenames [2], wxT("2"));
    //wxMessageBox ( h24profilenames [3], wxT("3"));


        //insert values in correct spot on listbox
        ListBox2->Insert(h24profilenames [h24currentprofile],h24currentprofile);
        ListBox2->Insert(h24profilenames [h24currentprofile+1],h24currentprofile+1);

        //ListBox2->Insert(wxT("1"),h24currentprofile+1);
        //ListBox2->Insert(wxT("2"),h24currentprofile);

        //delete the old listbox values
//this area also needed to be changed for linux

        //fix the "listbox delete" bug
        int holderforvaluethatgetsinadvertentlydeleted = h24currentprofile;

        ListBox2->Delete(h24currentprofile+1);

        //put the value back into sequencercurrentprofile
        h24currentprofile = holderforvaluethatgetsinadvertentlydeleted;

       ListBox2->Delete(h24currentprofile+2);

        //put the value back into sequencercurrentprofile again
        h24currentprofile = holderforvaluethatgetsinadvertentlydeleted;



        ListBox2->SetSelection(++h24currentprofile);

        timerischanged = true;
    }

}

//activate timer button
void H24Timer::OnButton1Click(wxCommandEvent& event)
{
    //StopWatch1.Start(0);
    //do {}
    //while (StopWatch1.Time() < 2000);

    //CantGoBackWarning Dlg(0);
    //Dlg.ShowModal();

    if (!istimeractive) {

    StopWatch1.Start(0);
    do {}
    while (StopWatch1.Time() < 2000);

        Button1->Enable(false);
    //if(!istimeractive) {
        //istimerinit = false;
        //stopyesorno = false;
        //disable everything
        StaticBox1->Enable(false);
        StaticBox2->Enable(false);
        StaticBox3->Enable(false);
        ListBox1->Enable(false);
        ListBox2->Enable(false);
        Slider1->Enable(false);
        Slider2->Enable(false);
        Slider3->Enable(false);
        Slider4->Enable(false);
        Slider5->Enable(false);
        Slider6->Enable(false);
        Slider7->Enable(false);
        Slider8->Enable(false);
        Slider9->Enable(false);
        Slider10->Enable(false);
        Slider11->Enable(false);
        Slider12->Enable(false);
        Slider13->Enable(false);
        Slider14->Enable(false);
        Slider15->Enable(false);
        Slider16->Enable(false);
        CheckBox1->Enable(false);
        Button2->Enable(false);
        Button3->Enable(false);
        Button4->Enable(false);
        Button5->Enable(false);
        Button6->Enable(false);
        Button7->Enable(false);
        Button8->Enable(false);
        StaticText1->Enable(false);
        StaticText2->Enable(false);
        StaticText3->Enable(false);
        StaticText4->Enable(false);
        StaticText5->Enable(false);
        StaticText6->Enable(false);
        StaticText7->Enable(false);
        StaticText8->Enable(false);
        StaticText9->Enable(false);
        StaticText10->Enable(false);
        StaticText11->Enable(false);
        StaticText12->Enable(false);
        StaticText13->Enable(false);
        StaticText14->Enable(false);
        StaticText15->Enable(false);
        StaticText16->Enable(false);
        StaticText17->Enable(false);
        StaticText18->Enable(false);
        StaticText19->Enable(false);
        StaticText20->Enable(false);
        StaticText21->Enable(false);
        StaticText22->Enable(false);
        StaticText23->Enable(false);
        StaticText24->Enable(false);
        StaticText25->Enable(false);
        StaticText26->Enable(false);
        StaticText27->Enable(false);
        StaticText28->Enable(false);
        StaticText29->Enable(false);
        StaticText30->Enable(false);
        StaticText31->Enable(false);
        StaticText32->Enable(false);
        StaticText33->Enable(false);
        Choice1->Enable(false);

        Button1->SetLabel(wxT("Deactivate 24-Hour Light Timer"));
        ListBox1->SetSelection(wxAtoi(wxDateTime::Now().Format(wxT("%H"))));

        h24_updatelabels();
        h24_calculatetransition();
        istimeractive = true;

        }
    else {
        stop_timer();
    }
}



void H24Timer::h24_calculatetransition(void)
{
    //this should run at timer start and sny hour change

    unsigned short int fadeoutunits;
    unsigned short int currentfadeoutunits;

    //wxMessageBox (wxT("should happen once"),wxT("test"));

    h24currentprofile = ListBox2->GetSelection();
    unsigned short int currenthour = ListBox1->GetSelection();

    //false is subract true is add
    bool addorsubtract1;
    bool addorsubtract2;
    bool addorsubtract3;
    bool addorsubtract4;
    bool addorsubtract5;
    bool addorsubtract6;
    bool addorsubtract7;
    bool addorsubtract8;
    bool addorsubtract9;
    bool addorsubtract10;
    bool addorsubtract11;
    bool addorsubtract12;
    bool addorsubtract13;
    bool addorsubtract14;
    bool addorsubtract15;
    bool addorsubtract16;

    unsigned short int currentchannel1 = h24_Channel_1 [h24currentprofile] [currenthour];
    unsigned short int currentchannel2 = h24_Channel_2 [h24currentprofile] [currenthour];
    unsigned short int currentchannel3 = h24_Channel_3 [h24currentprofile] [currenthour];
    unsigned short int currentchannel4 = h24_Channel_4 [h24currentprofile] [currenthour];
    unsigned short int currentchannel5 = h24_Channel_5 [h24currentprofile] [currenthour];
    unsigned short int currentchannel6 = h24_Channel_6 [h24currentprofile] [currenthour];
    unsigned short int currentchannel7 = h24_Channel_7 [h24currentprofile] [currenthour];
    unsigned short int currentchannel8 = h24_Channel_8 [h24currentprofile] [currenthour];
    unsigned short int currentchannel9 = h24_Channel_9 [h24currentprofile] [currenthour];
    unsigned short int currentchannel10 = h24_Channel_10 [h24currentprofile] [currenthour];
    unsigned short int currentchannel11 = h24_Channel_11 [h24currentprofile] [currenthour];
    unsigned short int currentchannel12 = h24_Channel_12 [h24currentprofile] [currenthour];
    unsigned short int currentchannel13 = h24_Channel_13 [h24currentprofile] [currenthour];
    unsigned short int currentchannel14 = h24_Channel_14 [h24currentprofile] [currenthour];
    unsigned short int currentchannel15 = h24_Channel_15 [h24currentprofile] [currenthour];
    unsigned short int currentchannel16 = h24_Channel_16 [h24currentprofile] [currenthour];

//timer had to be adjusted to change the values every 20 seconds to keep the data arrays from being too large

    //convert transition selection to actual transion time
    if (issmoothtransition [h24currentprofile] [currenthour] == 1) {
        if (transitiontime [h24currentprofile] [currenthour] == 0) fadeoutunits = 15;// 5 minutes
        if (transitiontime [h24currentprofile] [currenthour] == 1) fadeoutunits = 30;// 10 minutes
        if (transitiontime [h24currentprofile] [currenthour] == 2) fadeoutunits = 45;// 15 minutes
        if (transitiontime [h24currentprofile] [currenthour] == 3) fadeoutunits = 90;// 30 minutes
        if (transitiontime [h24currentprofile] [currenthour] == 4) fadeoutunits = 135;// 45 minutes
        //if (transitiontime [h24currentprofile] [currenthour] == 5) fadeoutunits = 180;// entire hour
    }
    else fadeoutunits = 1; //no smooth transition

/*
    //convert transition selection to actual transion time
    if (issmoothtransition [h24currentprofile] [currenthour] == 1) {
        if (transitiontime [h24currentprofile] [currenthour] == 0) fadeoutunits = 30;// 5 minutes
        if (transitiontime [h24currentprofile] [currenthour] == 1) fadeoutunits = 60;// 10 minutes
        if (transitiontime [h24currentprofile] [currenthour] == 2) fadeoutunits = 90;// 15 minutes
        if (transitiontime [h24currentprofile] [currenthour] == 3) fadeoutunits = 180;// 30 minutes
        if (transitiontime [h24currentprofile] [currenthour] == 4) fadeoutunits = 270;// 45 minutes
        if (transitiontime [h24currentprofile] [currenthour] == 5) fadeoutunits = 360;// entire hour
    }
    else fadeoutunits = 1; //no smooth transition
*/


    //calculate entire hours worth of transtion data
    unsigned short int unitcountdown = 180;


    //variable to handle 24th hour to 1st hour change
    unsigned short int nexthour = currenthour + 1;
    if (nexthour == 24) nexthour = 0;



    //get the difference between this hour and next's dmx values and determine if its less or more
    if (currentchannel1 > h24_Channel_1 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_1 = currentchannel1 - h24_Channel_1 [h24currentprofile] [nexthour];
        addorsubtract1 = false;
    }
    if (h24_Channel_1 [h24currentprofile] [nexthour] > currentchannel1) {
        hourdifference_Channel_1 = h24_Channel_1 [h24currentprofile] [nexthour] - currentchannel1;
        addorsubtract1 = true;
    }
    if (h24_Channel_1 [h24currentprofile] [nexthour] == currentchannel1)
        hourdifference_Channel_1 = 1;
    //channel 2
    if (currentchannel2 > h24_Channel_2 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_2 = currentchannel2 - h24_Channel_2 [h24currentprofile] [nexthour];
        addorsubtract2 = false;
    }
    if (h24_Channel_2 [h24currentprofile] [nexthour] > currentchannel2){
        hourdifference_Channel_2 = h24_Channel_2 [h24currentprofile] [nexthour] - currentchannel2;
        addorsubtract2 = true;
    }
    if (h24_Channel_2 [h24currentprofile] [nexthour] == currentchannel2)
        hourdifference_Channel_2 = 1;
    //channel 3
    if (currentchannel3 > h24_Channel_3 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_3 = currentchannel3- h24_Channel_3 [h24currentprofile] [nexthour];
        addorsubtract3 = false;
    }
    if (h24_Channel_3 [h24currentprofile] [nexthour] > currentchannel3) {
        hourdifference_Channel_3 = h24_Channel_3 [h24currentprofile] [nexthour] - currentchannel3;
        addorsubtract3 = true;
    }
    if (h24_Channel_3 [h24currentprofile] [nexthour] == currentchannel3)
        hourdifference_Channel_3 = 1;
    //channel 4
    if (currentchannel4 > h24_Channel_4 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_4 = currentchannel4 - h24_Channel_4 [h24currentprofile] [nexthour];
        addorsubtract4 = false;
    }
    if (h24_Channel_4 [h24currentprofile] [nexthour] > currentchannel4) {
        hourdifference_Channel_4 = h24_Channel_4 [h24currentprofile] [nexthour] - currentchannel4;
        addorsubtract4 = true;
    }
    if (h24_Channel_4 [h24currentprofile] [nexthour] == currentchannel4)
        hourdifference_Channel_4 = 1;
    //channel 5
    if (currentchannel5 > h24_Channel_5 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_5 = currentchannel5 - h24_Channel_5 [h24currentprofile] [nexthour];
        addorsubtract5 = false;
    }
    if (h24_Channel_5 [h24currentprofile] [nexthour] > currentchannel5) {
        hourdifference_Channel_5 = h24_Channel_5 [h24currentprofile] [nexthour] - currentchannel5;
        addorsubtract5 = true;
    }
    if (h24_Channel_5 [h24currentprofile] [nexthour] == currentchannel5)
        hourdifference_Channel_5 = 1;
    //channel 6
    if (currentchannel6 > h24_Channel_6 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_6 = currentchannel6 - h24_Channel_6 [h24currentprofile] [nexthour];
        addorsubtract6 = false;
    }
    if (h24_Channel_6 [h24currentprofile] [nexthour] > currentchannel6) {
        hourdifference_Channel_6 = h24_Channel_6 [h24currentprofile] [nexthour] - currentchannel6;
        addorsubtract6 = true;
    }
    if (h24_Channel_6 [h24currentprofile] [nexthour] == currentchannel6)
        hourdifference_Channel_6 = 1;
    //channel 7
    if (currentchannel7 > h24_Channel_7 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_7 = currentchannel7 - h24_Channel_7 [h24currentprofile] [nexthour];
        addorsubtract7 = false;
    }
    if (h24_Channel_7 [h24currentprofile] [nexthour] > currentchannel7) {
        hourdifference_Channel_7 = h24_Channel_7 [h24currentprofile] [nexthour] - currentchannel7;
        addorsubtract7 = true;
    }
    if (h24_Channel_7 [h24currentprofile] [nexthour] == currentchannel7)
        hourdifference_Channel_7 = 1;
    //channel 8
    if (currentchannel8 > h24_Channel_8 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_8 = currentchannel8 - h24_Channel_8 [h24currentprofile] [nexthour];
        addorsubtract8 = false;
    }
    if (h24_Channel_8 [h24currentprofile] [nexthour] > currentchannel8) {
        hourdifference_Channel_8 = h24_Channel_8 [h24currentprofile] [nexthour] - currentchannel8;
        addorsubtract8 = true;
    }
    if (h24_Channel_8 [h24currentprofile] [nexthour] == currentchannel8)
        hourdifference_Channel_8 = 1;
    //channel 9
    if (currentchannel9 > h24_Channel_9 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_9 = currentchannel9 - h24_Channel_9 [h24currentprofile] [nexthour];
        addorsubtract9 = false;
    }
    if (h24_Channel_9 [h24currentprofile] [nexthour] > currentchannel9) {
        hourdifference_Channel_9 = h24_Channel_9 [h24currentprofile] [nexthour] - currentchannel9;
        addorsubtract9 = true;
    }
    if (h24_Channel_9 [h24currentprofile] [nexthour] == currentchannel9)
        hourdifference_Channel_9 = 1;
    //channel 10
    if (currentchannel10 > h24_Channel_10 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_10 = currentchannel10 - h24_Channel_10 [h24currentprofile] [nexthour];
        addorsubtract10 = false;
    }
    if (h24_Channel_10 [h24currentprofile] [nexthour] > currentchannel10) {
        hourdifference_Channel_10 = h24_Channel_10 [h24currentprofile] [nexthour] - currentchannel10;
        addorsubtract10 = true;
    }
    if (h24_Channel_10 [h24currentprofile] [nexthour] == currentchannel10)
        hourdifference_Channel_10 = 1;
    //channel 11
    if (currentchannel11 > h24_Channel_11 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_11 = currentchannel11 - h24_Channel_11 [h24currentprofile] [nexthour];
        addorsubtract11 = false;
    }
    if (h24_Channel_11 [h24currentprofile] [nexthour] > currentchannel11) {
        hourdifference_Channel_11 = h24_Channel_11 [h24currentprofile] [nexthour] - currentchannel11;
        addorsubtract11 = true;
    }
    if (h24_Channel_11 [h24currentprofile] [nexthour] == currentchannel11)
        hourdifference_Channel_11 = 1;
    //channel 12
    if (currentchannel12 > h24_Channel_12 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_12 = currentchannel12 - h24_Channel_12 [h24currentprofile] [nexthour];
        addorsubtract12 = false;
    }
    if (h24_Channel_12 [h24currentprofile] [nexthour] > currentchannel12) {
        hourdifference_Channel_12 = h24_Channel_12 [h24currentprofile] [nexthour] - currentchannel12;
        addorsubtract12 = true;
    }
    if (h24_Channel_12 [h24currentprofile] [nexthour] == currentchannel12)
        hourdifference_Channel_12 = 1;
    //channel 13
    if (currentchannel13 > h24_Channel_13 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_13 = currentchannel13 - h24_Channel_13 [h24currentprofile] [nexthour];
        addorsubtract13 = false;
    }
    if (h24_Channel_13 [h24currentprofile] [nexthour] > currentchannel13) {
        hourdifference_Channel_13 = h24_Channel_13 [h24currentprofile] [nexthour] - currentchannel13;
        addorsubtract13 = true;
    }
    if (h24_Channel_13 [h24currentprofile] [nexthour] == currentchannel13)
        hourdifference_Channel_13 = 1;
    //channel 14
    if (currentchannel14 > h24_Channel_14 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_14 = currentchannel14 - h24_Channel_14 [h24currentprofile] [nexthour];
        addorsubtract14 = false;
    }
    if (h24_Channel_14 [h24currentprofile] [nexthour] > currentchannel14) {
        hourdifference_Channel_14 = h24_Channel_14 [h24currentprofile] [nexthour] - currentchannel14;
        addorsubtract14 = true;
    }
    if (h24_Channel_14 [h24currentprofile] [nexthour] == currentchannel14)
        hourdifference_Channel_14 = 1;
    //channel 15
    if (currentchannel15 > h24_Channel_15 [h24currentprofile] [nexthour]){
        hourdifference_Channel_15 = currentchannel15- h24_Channel_15 [h24currentprofile] [nexthour];
        addorsubtract15 = false;
    }
    if (h24_Channel_15 [h24currentprofile] [nexthour] > currentchannel15) {
        hourdifference_Channel_15 = h24_Channel_15 [h24currentprofile] [nexthour] - currentchannel15;
        addorsubtract15 = true;
    }
    if (h24_Channel_15 [h24currentprofile] [nexthour] == currentchannel15)
        hourdifference_Channel_15 = 1;
    //channel 16
    if (currentchannel16 > h24_Channel_16 [h24currentprofile] [nexthour]) {
        hourdifference_Channel_16 = currentchannel16 - h24_Channel_16 [h24currentprofile] [nexthour];
        addorsubtract16 = false;
    }
    if (h24_Channel_16 [h24currentprofile] [nexthour] > currentchannel16) {
        hourdifference_Channel_16 = h24_Channel_16 [h24currentprofile] [nexthour] - currentchannel16;
        addorsubtract16 = true;
    }
    if (h24_Channel_16 [h24currentprofile] [nexthour] == currentchannel16)
        hourdifference_Channel_16 = 1;



    //this is the actual calculation that figures out the increments to add by
    timedivide_Channel_1 = hourdifference_Channel_1 / fadeoutunits;
    timedivide_Channel_2 = hourdifference_Channel_2 / fadeoutunits;
    timedivide_Channel_3 = hourdifference_Channel_3 / fadeoutunits;
    timedivide_Channel_4 = hourdifference_Channel_4 / fadeoutunits;
    timedivide_Channel_5 = hourdifference_Channel_5 / fadeoutunits;
    timedivide_Channel_6 = hourdifference_Channel_6 / fadeoutunits;
    timedivide_Channel_7 = hourdifference_Channel_7 / fadeoutunits;
    timedivide_Channel_8 = hourdifference_Channel_8 / fadeoutunits;
    timedivide_Channel_9 = hourdifference_Channel_9 / fadeoutunits;
    timedivide_Channel_10 = hourdifference_Channel_10 / fadeoutunits;
    timedivide_Channel_11 = hourdifference_Channel_11 / fadeoutunits;
    timedivide_Channel_12 = hourdifference_Channel_12 / fadeoutunits;
    timedivide_Channel_13 = hourdifference_Channel_13 / fadeoutunits;
    timedivide_Channel_14 = hourdifference_Channel_14 / fadeoutunits;
    timedivide_Channel_15 = hourdifference_Channel_15 / fadeoutunits;
    timedivide_Channel_16 = hourdifference_Channel_16 / fadeoutunits;

    //set timecalculateds value to the next hours value to calculate from with countdown/countup
    timecalculated_Channel_1 = h24_Channel_1 [h24currentprofile] [nexthour];
    timecalculated_Channel_2 = h24_Channel_2 [h24currentprofile] [nexthour];
    timecalculated_Channel_3 = h24_Channel_3 [h24currentprofile] [nexthour];
    timecalculated_Channel_4 = h24_Channel_4 [h24currentprofile] [nexthour];
    timecalculated_Channel_5 = h24_Channel_5 [h24currentprofile] [nexthour];
    timecalculated_Channel_6 = h24_Channel_6 [h24currentprofile] [nexthour];
    timecalculated_Channel_7 = h24_Channel_7 [h24currentprofile] [nexthour];
    timecalculated_Channel_8 = h24_Channel_8 [h24currentprofile] [nexthour];
    timecalculated_Channel_9 = h24_Channel_9 [h24currentprofile] [nexthour];
    timecalculated_Channel_10 = h24_Channel_10 [h24currentprofile] [nexthour];
    timecalculated_Channel_11 = h24_Channel_11 [h24currentprofile] [nexthour];
    timecalculated_Channel_12 = h24_Channel_12 [h24currentprofile] [nexthour];
    timecalculated_Channel_13 = h24_Channel_13 [h24currentprofile] [nexthour];
    timecalculated_Channel_14 = h24_Channel_14 [h24currentprofile] [nexthour];
    timecalculated_Channel_15 = h24_Channel_15 [h24currentprofile] [nexthour];
    timecalculated_Channel_16 = h24_Channel_16 [h24currentprofile] [nexthour];

    //sets the starting pounsigned short int for count up (this is used to avoid float subtraction issuas)
    unsigned short int unitcountup = unitcountdown - fadeoutunits;

    //this here foor loop populates the hourtransitioncalculations array with the fade values
    for(unsigned short int unitcount = 0; unitcount < fadeoutunits; unitcount++) {

        //Channel_1
        if (addorsubtract1) {
            timecalculated_Channel_1 = timecalculated_Channel_1 + timedivide_Channel_1;
            hourtransitioncalculations [1] [unitcountup] = timecalculated_Channel_1;
            }
        else {
            timecalculated_Channel_1 = timecalculated_Channel_1 + timedivide_Channel_1;
            hourtransitioncalculations [1] [unitcountdown] = timecalculated_Channel_1;
        }
        //Channel_2
        if (addorsubtract2) {
            timecalculated_Channel_2 = timecalculated_Channel_2 + timedivide_Channel_2;
            hourtransitioncalculations [2] [unitcountup] = timecalculated_Channel_2;
            }
        else {
            timecalculated_Channel_2 = timecalculated_Channel_2 + timedivide_Channel_2;
            hourtransitioncalculations [2] [unitcountdown] = timecalculated_Channel_2;
        }
        //Channel_3
        if (addorsubtract3) {
            timecalculated_Channel_3 = timecalculated_Channel_3 + timedivide_Channel_3;
            hourtransitioncalculations [3] [unitcountup] = timecalculated_Channel_3;
            }
        else {
            timecalculated_Channel_3 = timecalculated_Channel_3 + timedivide_Channel_3;
            hourtransitioncalculations [3] [unitcountdown] = timecalculated_Channel_3;
        }
        //Channel_4
        if (addorsubtract4) {
            timecalculated_Channel_4 = timecalculated_Channel_4 + timedivide_Channel_4;
            hourtransitioncalculations [4] [unitcountup] = timecalculated_Channel_4;
            }
        else {
            timecalculated_Channel_4 = timecalculated_Channel_4 + timedivide_Channel_4;
            hourtransitioncalculations [4] [unitcountdown] = timecalculated_Channel_4;
        }
        //Channel_5
        if (addorsubtract5) {
            timecalculated_Channel_5 = timecalculated_Channel_5 + timedivide_Channel_5;
            hourtransitioncalculations [5] [unitcountup] = timecalculated_Channel_5;
            }
        else {
            timecalculated_Channel_5 = timecalculated_Channel_5 + timedivide_Channel_5;
            hourtransitioncalculations [5] [unitcountdown] = timecalculated_Channel_5;
        }
        //Channel_6
        if (addorsubtract6) {
            timecalculated_Channel_6 = timecalculated_Channel_6 + timedivide_Channel_6;
            hourtransitioncalculations [6] [unitcountup] = timecalculated_Channel_6;
            }
        else {
            timecalculated_Channel_6 = timecalculated_Channel_6 + timedivide_Channel_6;
            hourtransitioncalculations [6] [unitcountdown] = timecalculated_Channel_6;
        }
        //Channel_7
        if (addorsubtract7) {
            timecalculated_Channel_7 = timecalculated_Channel_7 + timedivide_Channel_7;
            hourtransitioncalculations [7] [unitcountup] = timecalculated_Channel_7;
            }
        else {
            timecalculated_Channel_7 = timecalculated_Channel_7 + timedivide_Channel_7;
            hourtransitioncalculations [7] [unitcountdown] = timecalculated_Channel_7;
        }
        //Channel_8
        if (addorsubtract8) {
            timecalculated_Channel_8 = timecalculated_Channel_8 + timedivide_Channel_8;
            hourtransitioncalculations [8] [unitcountup] = timecalculated_Channel_8;
            }
        else {
            timecalculated_Channel_8 = timecalculated_Channel_8 + timedivide_Channel_8;
            hourtransitioncalculations [8] [unitcountdown] = timecalculated_Channel_8;
        }
        //Channel_9
        if (addorsubtract9) {
            timecalculated_Channel_9 = timecalculated_Channel_9 + timedivide_Channel_9;
            hourtransitioncalculations [9] [unitcountup] = timecalculated_Channel_9;
            }
        else {
            timecalculated_Channel_9 = timecalculated_Channel_9 + timedivide_Channel_9;
            hourtransitioncalculations [9] [unitcountdown] = timecalculated_Channel_9;
        }
        //Channel_10
        if (addorsubtract10) {
            timecalculated_Channel_10 = timecalculated_Channel_10 + timedivide_Channel_10;
            hourtransitioncalculations [10] [unitcountup] = timecalculated_Channel_10;
            }
        else {
            timecalculated_Channel_10 = timecalculated_Channel_10 + timedivide_Channel_10;
            hourtransitioncalculations [10] [unitcountdown] = timecalculated_Channel_10;
        }
        //Channel_11
        if (addorsubtract11) {
            timecalculated_Channel_11 = timecalculated_Channel_11 + timedivide_Channel_11;
            hourtransitioncalculations [11] [unitcountup] = timecalculated_Channel_11;
            }
        else {
            timecalculated_Channel_11 = timecalculated_Channel_11 + timedivide_Channel_11;
            hourtransitioncalculations [11] [unitcountdown] = timecalculated_Channel_11;
        }
        //Channel_12
        if (addorsubtract12) {
            timecalculated_Channel_12 = timecalculated_Channel_12 + timedivide_Channel_12;
            hourtransitioncalculations [12] [unitcountup] = timecalculated_Channel_12;
            }
        else {
            timecalculated_Channel_12 = timecalculated_Channel_12 + timedivide_Channel_12;
            hourtransitioncalculations [12] [unitcountdown] = timecalculated_Channel_12;
        }
        //Channel_13
        if (addorsubtract13) {
            timecalculated_Channel_13 = timecalculated_Channel_13 + timedivide_Channel_13;
            hourtransitioncalculations [13] [unitcountup] = timecalculated_Channel_13;
            }
        else {
            timecalculated_Channel_13 = timecalculated_Channel_13 + timedivide_Channel_13;
            hourtransitioncalculations [13] [unitcountdown] = timecalculated_Channel_13;
        }
        //Channel_14
        if (addorsubtract14) {
            timecalculated_Channel_14 = timecalculated_Channel_14 + timedivide_Channel_14;
            hourtransitioncalculations [14] [unitcountup] = timecalculated_Channel_14;
            }
        else {
            timecalculated_Channel_14 = timecalculated_Channel_14 + timedivide_Channel_14;
            hourtransitioncalculations [14] [unitcountdown] = timecalculated_Channel_14;
        }
        //Channel_15
        if (addorsubtract15) {
            timecalculated_Channel_15 = timecalculated_Channel_15 + timedivide_Channel_15;
            hourtransitioncalculations [15] [unitcountup] = timecalculated_Channel_15;
            }
        else {
            timecalculated_Channel_15 = timecalculated_Channel_15 + timedivide_Channel_15;
            hourtransitioncalculations [15] [unitcountdown] = timecalculated_Channel_15;
        }
        //Channel_16
        if (addorsubtract16) {
            timecalculated_Channel_16 = timecalculated_Channel_16 + timedivide_Channel_16;
            hourtransitioncalculations [16] [unitcountup] = timecalculated_Channel_16;
            }
        else {
            timecalculated_Channel_16 = timecalculated_Channel_16 + timedivide_Channel_16;
            hourtransitioncalculations [16] [unitcountdown] = timecalculated_Channel_16;
        }

        unitcountdown--;
        unitcountup++;
    }



    //this here do loop populates the hourtransitioncalculations array with the rest of the values
    for(unsigned short int dummy; unitcountdown > 0; unitcountdown--) {
        //Channel_1
        hourtransitioncalculations [1] [unitcountdown] = currentchannel1;
        //Channel_2
        hourtransitioncalculations [2] [unitcountdown] = currentchannel2;
        //Channel_3
        hourtransitioncalculations [3] [unitcountdown] = currentchannel3;
        //Channel_4
        hourtransitioncalculations [4] [unitcountdown] = currentchannel4;
        //Channel_5
        hourtransitioncalculations [5] [unitcountdown] = currentchannel5;
        //Channel_6
        hourtransitioncalculations [6] [unitcountdown] = currentchannel6;
        //Channel_7
        hourtransitioncalculations [7] [unitcountdown] = currentchannel7;
        //Channel_8
        hourtransitioncalculations [8] [unitcountdown] = currentchannel8;
        //Channel_9
        hourtransitioncalculations [9] [unitcountdown] = currentchannel9;
        //Channel_10
        hourtransitioncalculations [10] [unitcountdown] = currentchannel10;
        //Channel_11
        hourtransitioncalculations [11] [unitcountdown] = currentchannel11;
        //Channel_12
        hourtransitioncalculations [12] [unitcountdown] = currentchannel12;
        //Channel_13
        hourtransitioncalculations [13] [unitcountdown] = currentchannel13;
        //Channel_14
        hourtransitioncalculations [14] [unitcountdown] = currentchannel14;
        //Channel_15
        hourtransitioncalculations [15] [unitcountdown] = currentchannel15;
        //Channel_16
        hourtransitioncalculations [16] [unitcountdown] = currentchannel16;
    }


}

//new profile button
void H24Timer::OnButton2Click(wxCommandEvent& event)
{

    if (h24numberofprofiles == 32){
        wxMessageBox (wxT("This Profile Set is already at the maximum amount of profiles currently available by Lightput, please create a new profile set to store more profiles."),wxT("Too Many Profiles"));
        return;
    }

    //this code grants access to variables in another file using a classs instance of
    H24AddNewProfile Dlg(0);
    //opens dialog
    Dlg.ShowModal();

    h24profilenames [h24numberofprofiles] = Dlg.TextCtrl1->GetValue();
    if (timeryesorno) {


        //clear data for current profile value
        for (int n = 0; n < 24; n++) {
            h24_Channel_1 [h24numberofprofiles] [n] = 0;
            h24_Channel_2 [h24numberofprofiles] [n] = 0;
            h24_Channel_3 [h24numberofprofiles] [n] = 0;
            h24_Channel_4 [h24numberofprofiles] [n] = 0;
            h24_Channel_5 [h24numberofprofiles] [n] = 0;
            h24_Channel_6 [h24numberofprofiles] [n] = 0;
            h24_Channel_7 [h24numberofprofiles] [n] = 0;
            h24_Channel_8 [h24numberofprofiles] [n] = 0;
            h24_Channel_9 [h24numberofprofiles] [n] = 0;
            h24_Channel_10 [h24numberofprofiles] [n] = 0;
            h24_Channel_11 [h24numberofprofiles] [n] = 0;
            h24_Channel_12 [h24numberofprofiles] [n] = 0;
            h24_Channel_13 [h24numberofprofiles] [n] = 0;
            h24_Channel_14 [h24numberofprofiles] [n] = 0;
            h24_Channel_15 [h24numberofprofiles] [n] = 0;
            h24_Channel_16 [h24numberofprofiles] [n] = 0;
            issmoothtransition [h24numberofprofiles] [n] = 0;
            transitiontime [h24numberofprofiles] [n] = 0;
        }
    timeryesorno = false;
    }
    else return;
    ListBox2->SetSelection(ListBox2->Append(h24profilenames [h24numberofprofiles]));
    h24currentprofile = ListBox2->GetSelection();

    h24numberofprofiles++;
    h24_updatelabels();
    timerischanged = true;
}

//rename profile button
void H24Timer::OnButton4Click(wxCommandEvent& event)
{

    if (ListBox2->GetSelection() != -1){
        h24currentprofile = ListBox2->GetSelection();

        H24RenameNameHolder = ListBox2->GetString(h24currentprofile);

        //this code grants access to variables in another file using a classs instance of
        //DeleteVerify, Dlg
        H24RenameProfile Dlg(0);
        //opens dialog
        Dlg.ShowModal();
        wxString newname = Dlg.TextCtrl1->GetValue();
        if (timeryesorno == true) {
            h24profilenames [h24currentprofile] = newname;
            ListBox2->Insert(h24profilenames [h24currentprofile],h24currentprofile);

            ListBox2->SetSelection(h24currentprofile);

//more "listbox->delete" linux bugfix
            int holdervalueforbugfix = h24currentprofile;

            ListBox2->Delete(h24currentprofile+1);

            h24currentprofile = holdervalueforbugfix;

            timerischanged = true;

        }// closes inner if
    }// closes if
    else wxMessageBox(wxT("Select a profile to rename first."), _("Error"));



}


//delete profile button
void H24Timer::OnButton3Click(wxCommandEvent& event)
{

    if (ListBox2->GetSelection() != -1){
        h24currentprofile = ListBox2->GetSelection();
        H24DeleteProfile Dlg(0);
        //opens dialog
        Dlg.ShowModal();
        if (timeryesorno == true){
            //ischanged = true;


            //this form loop confuses me, but it basically moves every value
            //below the current and being deleted value up one spot in the arrays
            //holding he values
            int n;
            for (int profilemove = h24currentprofile ; profilemove < h24numberofprofiles; profilemove++)
                {
                    h24profilenames [profilemove] = h24profilenames [profilemove+1];

                    for (n = 0; n < 24; n++) issmoothtransition [profilemove] [n] = issmoothtransition [profilemove+1] [n];
                    for (n = 0; n < 24; n++) transitiontime [profilemove] [n] = transitiontime [profilemove+1] [n];

                    for (n = 0; n < 24; n++) h24_Channel_1 [profilemove] [n] = h24_Channel_1 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_2 [profilemove] [n] = h24_Channel_2 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_3 [profilemove] [n] = h24_Channel_3 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_4 [profilemove] [n] = h24_Channel_4 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_5 [profilemove] [n] = h24_Channel_5 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_6 [profilemove] [n] = h24_Channel_6 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_7 [profilemove] [n] = h24_Channel_7 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_8 [profilemove] [n] = h24_Channel_8 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_9 [profilemove] [n] = h24_Channel_9 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_10 [profilemove] [n] = h24_Channel_10 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_11 [profilemove] [n] = h24_Channel_11 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_12 [profilemove] [n] = h24_Channel_12 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_13 [profilemove] [n] = h24_Channel_13 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_14 [profilemove] [n] = h24_Channel_14 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_15 [profilemove] [n] = h24_Channel_15 [profilemove+1] [n];
                    for (n = 0; n < 24; n++) h24_Channel_16 [profilemove] [n] = h24_Channel_16 [profilemove+1] [n];
                }//closes the for

                //the folowing code handles the listbox selection

                //this int has to be here because the listbox delete function also deletes the value "currentprofile" in Linux builds!!
                int holderforvaluethatinadverdentlygetsdeleted = h24currentprofile;

                ListBox2->Delete(h24currentprofile);

                //puts the currentvalue value back from holder
                h24currentprofile = holderforvaluethatinadverdentlygetsdeleted;

                //the else is for if the listbox selection is the last one, it knows to move the selection up
                if (h24currentprofile < h24numberofprofiles-1)ListBox2->SetSelection(h24currentprofile);
                else ListBox1->SetSelection(--h24currentprofile);
                h24numberofprofiles--;


                if (h24numberofprofiles == 0) {
                    h24currentprofile = 0;
                    h24profilenames [h24currentprofile] = wxT("Blank Profile");
                    for (int n = 0; n < 24; n++) {
                        h24_Channel_1 [h24currentprofile] [n] = 0;
                        h24_Channel_2 [h24currentprofile] [n] = 0;
                        h24_Channel_3 [h24currentprofile] [n] = 0;
                        h24_Channel_4 [h24currentprofile] [n] = 0;
                        h24_Channel_5 [h24currentprofile] [n] = 0;
                        h24_Channel_6 [h24currentprofile] [n] = 0;
                        h24_Channel_7 [h24currentprofile] [n] = 0;
                        h24_Channel_8 [h24currentprofile] [n] = 0;
                        h24_Channel_9 [h24currentprofile] [n] = 0;
                        h24_Channel_10 [h24currentprofile] [n] = 0;
                        h24_Channel_11 [h24currentprofile] [n] = 0;
                        h24_Channel_12 [h24currentprofile] [n] = 0;
                        h24_Channel_13 [h24currentprofile] [n] = 0;
                        h24_Channel_14 [h24currentprofile] [n] = 0;
                        h24_Channel_15 [h24currentprofile] [n] = 0;
                        h24_Channel_16 [h24currentprofile] [n] = 0;
                        issmoothtransition [h24currentprofile] [n] = 0;
                        transitiontime [h24currentprofile] [n] = 0;
                    }
                h24_updatelabels();
            }
        timerischanged = true;
       }
    }
}

//saves profile data
void H24Timer::saveprofiles(void)
{
    wxTextFile h24file(h24filename);
    wxChar padding = wxT('0');

    timeryesorno = false;
    savecancel = false;
    int count = 1;
    int currentprofile_save = 1;
    int currentlinenumber_save = 1;
    int totallinenumber_save = 1;
    //sets a wxChar to hold the comma to search for (used too be a comma)
    wxChar comma = wxT('!');
    //this condition checks if the file in question already exists
    if (h24file.Exists()) {
        //sequencercurrentprofile = ListBox1->GetSelection();
        //this code grants access to variables in another file using a classs instance of
        //DeleteVerify, Dlg
        h24profileoverwrite Dlg(0);
        //opens dialog
        Dlg.ShowModal();
        if (!timeryesorno) return;
        }

    h24file.Create(h24filename);
    //wxMessageBox (wxT("test"),wxT("test"));

    wxString h24_Channel_1_pad [32] [24];
    wxString h24_Channel_1_padded [32] [24];
    wxString h24_Channel_2_pad [32] [24];
    wxString h24_Channel_2_padded [32] [24];
    wxString h24_Channel_3_pad [32] [24];
    wxString h24_Channel_3_padded [32] [24];
    wxString h24_Channel_4_pad [32] [24];
    wxString h24_Channel_4_padded [32] [24];
    wxString h24_Channel_5_pad [32] [24];
    wxString h24_Channel_5_padded [32] [24];
    wxString h24_Channel_6_pad [32] [24];
    wxString h24_Channel_6_padded [32] [24];
    wxString h24_Channel_7_pad [32] [24];
    wxString h24_Channel_7_padded [32] [24];
    wxString h24_Channel_8_pad [32] [24];
    wxString h24_Channel_8_padded [32] [24];
    wxString h24_Channel_9_pad [32] [24];
    wxString h24_Channel_9_padded [32] [24];
    wxString h24_Channel_10_pad [32] [24];
    wxString h24_Channel_10_padded [32] [24];
    wxString h24_Channel_11_pad [32] [24];
    wxString h24_Channel_11_padded [32] [24];
    wxString h24_Channel_12_pad [32] [24];
    wxString h24_Channel_12_padded [32] [24];
    wxString h24_Channel_13_pad [32] [24];
    wxString h24_Channel_13_padded [32] [24];
    wxString h24_Channel_14_pad [32] [24];
    wxString h24_Channel_14_padded [32] [24];
    wxString h24_Channel_15_pad [32] [24];
    wxString h24_Channel_15_padded [32] [24];
    wxString h24_Channel_16_pad [32] [24];
    wxString h24_Channel_16_padded [32] [24];
    wxString issmoothtransition_pad [32] [24];
    wxString issmoothtransition_padded [32] [24];
    wxString transitiontime_pad [32] [24];
    wxString transitiontime_padded [32] [24];







//this while loop is run once here to gill the padded values, its seperate from the other
//while loop with the same condition to isolate the numbering difference of the sequencer channel values
        while (h24numberofprofiles >= currentprofile_save) {


            //this code pads the value with leading zeros for proper data storage
            //makes it easy to load if they all have the same number of characters

            for (count = 0; count < 24; count++) {
                h24_Channel_1_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_1 [currentprofile_save-1][count]);
                h24_Channel_1_padded [currentprofile_save][count]= wxT("00") + h24_Channel_1_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_1_padded [currentprofile_save][count] = h24_Channel_1_padded[currentprofile_save][count].substr( h24_Channel_1_padded[currentprofile_save][count].length() - 3 );
            }//close for
            //channel _2
            for (count = 0; count < 24; count++) {
                h24_Channel_2_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_2 [currentprofile_save-1][count]);
                h24_Channel_2_padded [currentprofile_save][count]= wxT("00") + h24_Channel_2_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_2_padded [currentprofile_save][count] = h24_Channel_2_padded[currentprofile_save][count].substr( h24_Channel_2_padded[currentprofile_save][count].length() - 3 );
            }//close for _2
            //channel _3
            for (count = 0; count < 24; count++) {
                h24_Channel_3_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_3 [currentprofile_save-1][count]);
                h24_Channel_3_padded [currentprofile_save][count]= wxT("00") + h24_Channel_3_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_3_padded [currentprofile_save][count] = h24_Channel_3_padded[currentprofile_save][count].substr( h24_Channel_3_padded[currentprofile_save][count].length() - 3 );
            }//close for
            //channel _4
            for (count = 0; count < 24; count++) {
                h24_Channel_4_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_4 [currentprofile_save-1][count]);
                h24_Channel_4_padded [currentprofile_save][count]= wxT("00") + h24_Channel_4_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_4_padded [currentprofile_save][count] = h24_Channel_4_padded[currentprofile_save][count].substr( h24_Channel_4_padded[currentprofile_save][count].length() - 3 );
            }//close for _4
            //channel _5
            for (count = 0; count < 24; count++) {
                h24_Channel_5_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_5 [currentprofile_save-1][count]);
                h24_Channel_5_padded [currentprofile_save][count]= wxT("00") + h24_Channel_5_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_5_padded [currentprofile_save][count] = h24_Channel_5_padded[currentprofile_save][count].substr( h24_Channel_5_padded[currentprofile_save][count].length() - 3 );
            }//close for _5
            //channel _8
            for (count = 0; count < 24; count++) {
                h24_Channel_6_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_6 [currentprofile_save-1][count]);
                h24_Channel_6_padded [currentprofile_save][count]= wxT("00") + h24_Channel_6_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_6_padded [currentprofile_save][count] = h24_Channel_6_padded[currentprofile_save][count].substr( h24_Channel_6_padded[currentprofile_save][count].length() - 3 );
            }//close for _6
            //channel _7
            for (count = 0; count < 24; count++) {
                h24_Channel_7_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_7 [currentprofile_save-1][count]);
                h24_Channel_7_padded [currentprofile_save][count]= wxT("00") + h24_Channel_7_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_7_padded [currentprofile_save][count] = h24_Channel_7_padded[currentprofile_save][count].substr( h24_Channel_7_padded[currentprofile_save][count].length() - 3 );
            }//close for _7
            //channel _8
            for (count = 0; count < 24; count++) {
                h24_Channel_8_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_8 [currentprofile_save-1][count]);
                h24_Channel_8_padded [currentprofile_save][count]= wxT("00") + h24_Channel_8_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_8_padded [currentprofile_save][count] = h24_Channel_8_padded[currentprofile_save][count].substr( h24_Channel_8_padded[currentprofile_save][count].length() - 3 );
            }//close for _8
            //channel _9
            for (count = 0; count < 24; count++) {
                h24_Channel_9_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_9 [currentprofile_save-1][count]);
                h24_Channel_9_padded [currentprofile_save][count]= wxT("00") + h24_Channel_9_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_9_padded [currentprofile_save][count] = h24_Channel_9_padded[currentprofile_save][count].substr( h24_Channel_9_padded[currentprofile_save][count].length() - 3 );
            }//close for _9
            //channel _10
            for (count = 0; count < 24; count++) {
                h24_Channel_10_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_10 [currentprofile_save-1][count]);
                h24_Channel_10_padded [currentprofile_save][count]= wxT("00") + h24_Channel_10_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_10_padded [currentprofile_save][count] = h24_Channel_10_padded[currentprofile_save][count].substr( h24_Channel_10_padded[currentprofile_save][count].length() - 3 );
            }//close for _10
            //channel _11
            for (count = 0; count < 24; count++) {
                h24_Channel_11_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_11 [currentprofile_save-1][count]);
                h24_Channel_11_padded [currentprofile_save][count]= wxT("00") + h24_Channel_11_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_11_padded [currentprofile_save][count] = h24_Channel_11_padded[currentprofile_save][count].substr( h24_Channel_11_padded[currentprofile_save][count].length() - 3 );
            }//close for _11
            //channel _12
            for (count = 0; count < 24; count++) {
                h24_Channel_12_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_12 [currentprofile_save-1][count]);
                h24_Channel_12_padded [currentprofile_save][count]= wxT("00") + h24_Channel_12_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_12_padded [currentprofile_save][count] = h24_Channel_12_padded[currentprofile_save][count].substr( h24_Channel_12_padded[currentprofile_save][count].length() - 3 );
            }//close for _12
            //channel _13
            for (count = 0; count < 24; count++) {
                h24_Channel_13_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_13 [currentprofile_save-1][count]);
                h24_Channel_13_padded [currentprofile_save][count]= wxT("00") + h24_Channel_13_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_13_padded [currentprofile_save][count] = h24_Channel_13_padded[currentprofile_save][count].substr( h24_Channel_13_padded[currentprofile_save][count].length() - 3 );
            }//close for _13
            //channel _14
            for (count = 0; count < 24; count++) {
                h24_Channel_14_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_14 [currentprofile_save-1][count]);
                h24_Channel_14_padded [currentprofile_save][count]= wxT("00") + h24_Channel_14_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_14_padded [currentprofile_save][count] = h24_Channel_14_padded[currentprofile_save][count].substr( h24_Channel_14_padded[currentprofile_save][count].length() - 3 );
            }//close for _14
            //channel _15
            for (count = 0; count < 24; count++) {
                h24_Channel_15_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_15 [currentprofile_save-1][count]);
                h24_Channel_15_padded [currentprofile_save][count]= wxT("00") + h24_Channel_15_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_15_padded [currentprofile_save][count] = h24_Channel_15_padded[currentprofile_save][count].substr( h24_Channel_15_padded[currentprofile_save][count].length() - 3 );
            }//close for _15
            //channel _16
            for (count = 0; count < 24; count++) {
                h24_Channel_16_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),h24_Channel_16 [currentprofile_save-1][count]);
                h24_Channel_16_padded [currentprofile_save][count]= wxT("00") + h24_Channel_16_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                h24_Channel_16_padded [currentprofile_save][count] = h24_Channel_16_padded[currentprofile_save][count].substr( h24_Channel_16_padded[currentprofile_save][count].length() - 3 );
            }//close for

            for (count = 0; count < 24; count++) {
                issmoothtransition_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),issmoothtransition [currentprofile_save-1][count]);
                issmoothtransition_padded [currentprofile_save][count]= wxT("00") + issmoothtransition_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                issmoothtransition_padded [currentprofile_save][count] = issmoothtransition_padded [currentprofile_save][count].substr( issmoothtransition_padded[currentprofile_save][count].length() - 3 );
            }//close for
            for (count = 0; count < 24; count++) {
                transitiontime_pad [currentprofile_save][count] = wxString::Format(wxT("%i"),transitiontime [currentprofile_save-1][count]);
                transitiontime_padded [currentprofile_save][count]= wxT("00") + transitiontime_pad [currentprofile_save][count];
                //this line cuts off any characters past three
                transitiontime_padded [currentprofile_save][count] = transitiontime_padded [currentprofile_save][count].substr( transitiontime_padded[currentprofile_save][count].length() - 3 );
            }//close for

        currentprofile_save++;
        }//close while
        currentprofile_save = 1;

        while (h24numberofprofiles >= currentprofile_save) {

/*
        //this is where yuo build up the lines to save

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
*/
            //displayValue = wxString::Format(wxT("%i"),SequencerTime [currentprofile_save]);
            h24buffer [currentlinenumber_save] = h24profilenames [currentprofile_save-1];
            h24file.AddLine(h24buffer [currentlinenumber_save], wxTextFileType_Dos);//ther was a ++ on save
            //12:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][0] << comma
                << h24_Channel_2_padded [currentprofile_save][0] << comma
                << h24_Channel_3_padded [currentprofile_save][0] << comma
                << h24_Channel_4_padded [currentprofile_save][0] << comma
                << h24_Channel_5_padded [currentprofile_save][0] << comma
                << h24_Channel_6_padded [currentprofile_save][0] << comma
                << h24_Channel_7_padded [currentprofile_save][0] << comma
                << h24_Channel_8_padded [currentprofile_save][0] << comma
                << h24_Channel_9_padded [currentprofile_save][0] << comma
                << h24_Channel_10_padded [currentprofile_save][0] << comma
                << h24_Channel_11_padded [currentprofile_save][0] << comma
                << h24_Channel_12_padded [currentprofile_save][0] << comma
                << h24_Channel_13_padded [currentprofile_save][0] << comma
                << h24_Channel_14_padded [currentprofile_save][0] << comma
                << h24_Channel_15_padded [currentprofile_save][0] << comma
                << h24_Channel_16_padded [currentprofile_save][0] << comma
                << issmoothtransition_padded [currentprofile_save][0] << comma
                << transitiontime_padded [currentprofile_save][0];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //1:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][1] << comma
                << h24_Channel_2_padded [currentprofile_save][1] << comma
                << h24_Channel_3_padded [currentprofile_save][1] << comma
                << h24_Channel_4_padded [currentprofile_save][1] << comma
                << h24_Channel_5_padded [currentprofile_save][1] << comma
                << h24_Channel_6_padded [currentprofile_save][1] << comma
                << h24_Channel_7_padded [currentprofile_save][1] << comma
                << h24_Channel_8_padded [currentprofile_save][1] << comma
                << h24_Channel_9_padded [currentprofile_save][1] << comma
                << h24_Channel_10_padded [currentprofile_save][1] << comma
                << h24_Channel_11_padded [currentprofile_save][1] << comma
                << h24_Channel_12_padded [currentprofile_save][1] << comma
                << h24_Channel_13_padded [currentprofile_save][1] << comma
                << h24_Channel_14_padded [currentprofile_save][1] << comma
                << h24_Channel_15_padded [currentprofile_save][1] << comma
                << h24_Channel_16_padded [currentprofile_save][1] << comma
                << issmoothtransition_padded [currentprofile_save][1] << comma
                << transitiontime_padded [currentprofile_save][1];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //2:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][2] << comma
                << h24_Channel_2_padded [currentprofile_save][2] << comma
                << h24_Channel_3_padded [currentprofile_save][2] << comma
                << h24_Channel_4_padded [currentprofile_save][2] << comma
                << h24_Channel_5_padded [currentprofile_save][2] << comma
                << h24_Channel_6_padded [currentprofile_save][2] << comma
                << h24_Channel_7_padded [currentprofile_save][2] << comma
                << h24_Channel_8_padded [currentprofile_save][2] << comma
                << h24_Channel_9_padded [currentprofile_save][2] << comma
                << h24_Channel_10_padded [currentprofile_save][2] << comma
                << h24_Channel_11_padded [currentprofile_save][2] << comma
                << h24_Channel_12_padded [currentprofile_save][2] << comma
                << h24_Channel_13_padded [currentprofile_save][2] << comma
                << h24_Channel_14_padded [currentprofile_save][2] << comma
                << h24_Channel_15_padded [currentprofile_save][2] << comma
                << h24_Channel_16_padded [currentprofile_save][2] << comma
                << issmoothtransition_padded [currentprofile_save][2] << comma
                << transitiontime_padded [currentprofile_save][2];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //3:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][3] << comma
                << h24_Channel_2_padded [currentprofile_save][3] << comma
                << h24_Channel_3_padded [currentprofile_save][3] << comma
                << h24_Channel_4_padded [currentprofile_save][3] << comma
                << h24_Channel_5_padded [currentprofile_save][3] << comma
                << h24_Channel_6_padded [currentprofile_save][3] << comma
                << h24_Channel_7_padded [currentprofile_save][3] << comma
                << h24_Channel_8_padded [currentprofile_save][3] << comma
                << h24_Channel_9_padded [currentprofile_save][3] << comma
                << h24_Channel_10_padded [currentprofile_save][3] << comma
                << h24_Channel_11_padded [currentprofile_save][3] << comma
                << h24_Channel_12_padded [currentprofile_save][3] << comma
                << h24_Channel_13_padded [currentprofile_save][3] << comma
                << h24_Channel_14_padded [currentprofile_save][3] << comma
                << h24_Channel_15_padded [currentprofile_save][3] << comma
                << h24_Channel_16_padded [currentprofile_save][3] << comma
                << issmoothtransition_padded [currentprofile_save][3] << comma
                << transitiontime_padded [currentprofile_save][3];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //4:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][4] << comma
                << h24_Channel_2_padded [currentprofile_save][4] << comma
                << h24_Channel_3_padded [currentprofile_save][4] << comma
                << h24_Channel_4_padded [currentprofile_save][4] << comma
                << h24_Channel_5_padded [currentprofile_save][4] << comma
                << h24_Channel_6_padded [currentprofile_save][4] << comma
                << h24_Channel_7_padded [currentprofile_save][4] << comma
                << h24_Channel_8_padded [currentprofile_save][4] << comma
                << h24_Channel_9_padded [currentprofile_save][4] << comma
                << h24_Channel_10_padded [currentprofile_save][4] << comma
                << h24_Channel_11_padded [currentprofile_save][4] << comma
                << h24_Channel_12_padded [currentprofile_save][4] << comma
                << h24_Channel_13_padded [currentprofile_save][4] << comma
                << h24_Channel_14_padded [currentprofile_save][4] << comma
                << h24_Channel_15_padded [currentprofile_save][4] << comma
                << h24_Channel_16_padded [currentprofile_save][4] << comma
                << issmoothtransition_padded [currentprofile_save][4] << comma
                << transitiontime_padded [currentprofile_save][4];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //5:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][5] << comma
                << h24_Channel_2_padded [currentprofile_save][5] << comma
                << h24_Channel_3_padded [currentprofile_save][5] << comma
                << h24_Channel_4_padded [currentprofile_save][5] << comma
                << h24_Channel_5_padded [currentprofile_save][5] << comma
                << h24_Channel_6_padded [currentprofile_save][5] << comma
                << h24_Channel_7_padded [currentprofile_save][5] << comma
                << h24_Channel_8_padded [currentprofile_save][5] << comma
                << h24_Channel_9_padded [currentprofile_save][5] << comma
                << h24_Channel_10_padded [currentprofile_save][5] << comma
                << h24_Channel_11_padded [currentprofile_save][5] << comma
                << h24_Channel_12_padded [currentprofile_save][5] << comma
                << h24_Channel_13_padded [currentprofile_save][5] << comma
                << h24_Channel_14_padded [currentprofile_save][5] << comma
                << h24_Channel_15_padded [currentprofile_save][5] << comma
                << h24_Channel_16_padded [currentprofile_save][5] << comma
                << issmoothtransition_padded [currentprofile_save][5] << comma
                << transitiontime_padded [currentprofile_save][5];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

       //6:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][6] << comma
                << h24_Channel_2_padded [currentprofile_save][6] << comma
                << h24_Channel_3_padded [currentprofile_save][6] << comma
                << h24_Channel_4_padded [currentprofile_save][6] << comma
                << h24_Channel_5_padded [currentprofile_save][6] << comma
                << h24_Channel_6_padded [currentprofile_save][6] << comma
                << h24_Channel_7_padded [currentprofile_save][6] << comma
                << h24_Channel_8_padded [currentprofile_save][6] << comma
                << h24_Channel_9_padded [currentprofile_save][6] << comma
                << h24_Channel_10_padded [currentprofile_save][6] << comma
                << h24_Channel_11_padded [currentprofile_save][6] << comma
                << h24_Channel_12_padded [currentprofile_save][6] << comma
                << h24_Channel_13_padded [currentprofile_save][6] << comma
                << h24_Channel_14_padded [currentprofile_save][6] << comma
                << h24_Channel_15_padded [currentprofile_save][6] << comma
                << h24_Channel_16_padded [currentprofile_save][6] << comma
                << issmoothtransition_padded [currentprofile_save][6] << comma
                << transitiontime_padded [currentprofile_save][6];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //7:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][7] << comma
                << h24_Channel_2_padded [currentprofile_save][7] << comma
                << h24_Channel_3_padded [currentprofile_save][7] << comma
                << h24_Channel_4_padded [currentprofile_save][7] << comma
                << h24_Channel_5_padded [currentprofile_save][7] << comma
                << h24_Channel_6_padded [currentprofile_save][7] << comma
                << h24_Channel_7_padded [currentprofile_save][7] << comma
                << h24_Channel_8_padded [currentprofile_save][7] << comma
                << h24_Channel_9_padded [currentprofile_save][7] << comma
                << h24_Channel_10_padded [currentprofile_save][7] << comma
                << h24_Channel_11_padded [currentprofile_save][7] << comma
                << h24_Channel_12_padded [currentprofile_save][7] << comma
                << h24_Channel_13_padded [currentprofile_save][7] << comma
                << h24_Channel_14_padded [currentprofile_save][7] << comma
                << h24_Channel_15_padded [currentprofile_save][7] << comma
                << h24_Channel_16_padded [currentprofile_save][7] << comma
                << issmoothtransition_padded [currentprofile_save][7] << comma
                << transitiontime_padded [currentprofile_save][7];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //8:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][8] << comma
                << h24_Channel_2_padded [currentprofile_save][8] << comma
                << h24_Channel_3_padded [currentprofile_save][8] << comma
                << h24_Channel_4_padded [currentprofile_save][8] << comma
                << h24_Channel_5_padded [currentprofile_save][8] << comma
                << h24_Channel_6_padded [currentprofile_save][8] << comma
                << h24_Channel_7_padded [currentprofile_save][8] << comma
                << h24_Channel_8_padded [currentprofile_save][8] << comma
                << h24_Channel_9_padded [currentprofile_save][8] << comma
                << h24_Channel_10_padded [currentprofile_save][8] << comma
                << h24_Channel_11_padded [currentprofile_save][8] << comma
                << h24_Channel_12_padded [currentprofile_save][8] << comma
                << h24_Channel_13_padded [currentprofile_save][8] << comma
                << h24_Channel_14_padded [currentprofile_save][8] << comma
                << h24_Channel_15_padded [currentprofile_save][8] << comma
                << h24_Channel_16_padded [currentprofile_save][8] << comma
                << issmoothtransition_padded [currentprofile_save][8] << comma
                << transitiontime_padded [currentprofile_save][8];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //9:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][9] << comma
                << h24_Channel_2_padded [currentprofile_save][9] << comma
                << h24_Channel_3_padded [currentprofile_save][9] << comma
                << h24_Channel_4_padded [currentprofile_save][9] << comma
                << h24_Channel_5_padded [currentprofile_save][9] << comma
                << h24_Channel_6_padded [currentprofile_save][9] << comma
                << h24_Channel_7_padded [currentprofile_save][9] << comma
                << h24_Channel_8_padded [currentprofile_save][9] << comma
                << h24_Channel_9_padded [currentprofile_save][9] << comma
                << h24_Channel_10_padded [currentprofile_save][9] << comma
                << h24_Channel_11_padded [currentprofile_save][9] << comma
                << h24_Channel_12_padded [currentprofile_save][9] << comma
                << h24_Channel_13_padded [currentprofile_save][9] << comma
                << h24_Channel_14_padded [currentprofile_save][9] << comma
                << h24_Channel_15_padded [currentprofile_save][9] << comma
                << h24_Channel_16_padded [currentprofile_save][9] << comma
                << issmoothtransition_padded [currentprofile_save][9] << comma
                << transitiontime_padded [currentprofile_save][9];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

       //10:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][10] << comma
                << h24_Channel_2_padded [currentprofile_save][10] << comma
                << h24_Channel_3_padded [currentprofile_save][10] << comma
                << h24_Channel_4_padded [currentprofile_save][10] << comma
                << h24_Channel_5_padded [currentprofile_save][10] << comma
                << h24_Channel_6_padded [currentprofile_save][10] << comma
                << h24_Channel_7_padded [currentprofile_save][10] << comma
                << h24_Channel_8_padded [currentprofile_save][10] << comma
                << h24_Channel_9_padded [currentprofile_save][10] << comma
                << h24_Channel_10_padded [currentprofile_save][10] << comma
                << h24_Channel_11_padded [currentprofile_save][10] << comma
                << h24_Channel_12_padded [currentprofile_save][10] << comma
                << h24_Channel_13_padded [currentprofile_save][10] << comma
                << h24_Channel_14_padded [currentprofile_save][10] << comma
                << h24_Channel_15_padded [currentprofile_save][10] << comma
                << h24_Channel_16_padded [currentprofile_save][10] << comma
                << issmoothtransition_padded [currentprofile_save][10] << comma
                << transitiontime_padded [currentprofile_save][10];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //11:00 am
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][11] << comma
                << h24_Channel_2_padded [currentprofile_save][11] << comma
                << h24_Channel_3_padded [currentprofile_save][11] << comma
                << h24_Channel_4_padded [currentprofile_save][11] << comma
                << h24_Channel_5_padded [currentprofile_save][11] << comma
                << h24_Channel_6_padded [currentprofile_save][11] << comma
                << h24_Channel_7_padded [currentprofile_save][11] << comma
                << h24_Channel_8_padded [currentprofile_save][11] << comma
                << h24_Channel_9_padded [currentprofile_save][11] << comma
                << h24_Channel_10_padded [currentprofile_save][11] << comma
                << h24_Channel_11_padded [currentprofile_save][11] << comma
                << h24_Channel_12_padded [currentprofile_save][11] << comma
                << h24_Channel_13_padded [currentprofile_save][11] << comma
                << h24_Channel_14_padded [currentprofile_save][11] << comma
                << h24_Channel_15_padded [currentprofile_save][11] << comma
                << h24_Channel_16_padded [currentprofile_save][11] << comma
                << issmoothtransition_padded [currentprofile_save][11] << comma
                << transitiontime_padded [currentprofile_save][11];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //12:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][12] << comma
                << h24_Channel_2_padded [currentprofile_save][12] << comma
                << h24_Channel_3_padded [currentprofile_save][12] << comma
                << h24_Channel_4_padded [currentprofile_save][12] << comma
                << h24_Channel_5_padded [currentprofile_save][12] << comma
                << h24_Channel_6_padded [currentprofile_save][12] << comma
                << h24_Channel_7_padded [currentprofile_save][12] << comma
                << h24_Channel_8_padded [currentprofile_save][12] << comma
                << h24_Channel_9_padded [currentprofile_save][12] << comma
                << h24_Channel_10_padded [currentprofile_save][12] << comma
                << h24_Channel_11_padded [currentprofile_save][12] << comma
                << h24_Channel_12_padded [currentprofile_save][12] << comma
                << h24_Channel_13_padded [currentprofile_save][12] << comma
                << h24_Channel_14_padded [currentprofile_save][12] << comma
                << h24_Channel_15_padded [currentprofile_save][12] << comma
                << h24_Channel_16_padded [currentprofile_save][12] << comma
                << issmoothtransition_padded [currentprofile_save][12] << comma
                << transitiontime_padded [currentprofile_save][12];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //1:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][13] << comma
                << h24_Channel_2_padded [currentprofile_save][13] << comma
                << h24_Channel_3_padded [currentprofile_save][13] << comma
                << h24_Channel_4_padded [currentprofile_save][13] << comma
                << h24_Channel_5_padded [currentprofile_save][13] << comma
                << h24_Channel_6_padded [currentprofile_save][13] << comma
                << h24_Channel_7_padded [currentprofile_save][13] << comma
                << h24_Channel_8_padded [currentprofile_save][13] << comma
                << h24_Channel_9_padded [currentprofile_save][13] << comma
                << h24_Channel_10_padded [currentprofile_save][13] << comma
                << h24_Channel_11_padded [currentprofile_save][13] << comma
                << h24_Channel_12_padded [currentprofile_save][13] << comma
                << h24_Channel_13_padded [currentprofile_save][13] << comma
                << h24_Channel_14_padded [currentprofile_save][13] << comma
                << h24_Channel_15_padded [currentprofile_save][13] << comma
                << h24_Channel_16_padded [currentprofile_save][13] << comma
                << issmoothtransition_padded [currentprofile_save][13] << comma
                << transitiontime_padded [currentprofile_save][13];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);
       //2:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][14] << comma
                << h24_Channel_2_padded [currentprofile_save][14] << comma
                << h24_Channel_3_padded [currentprofile_save][14] << comma
                << h24_Channel_4_padded [currentprofile_save][14] << comma
                << h24_Channel_5_padded [currentprofile_save][14] << comma
                << h24_Channel_6_padded [currentprofile_save][14] << comma
                << h24_Channel_7_padded [currentprofile_save][14] << comma
                << h24_Channel_8_padded [currentprofile_save][14] << comma
                << h24_Channel_9_padded [currentprofile_save][14] << comma
                << h24_Channel_10_padded [currentprofile_save][14] << comma
                << h24_Channel_11_padded [currentprofile_save][14] << comma
                << h24_Channel_12_padded [currentprofile_save][14] << comma
                << h24_Channel_13_padded [currentprofile_save][14] << comma
                << h24_Channel_14_padded [currentprofile_save][14] << comma
                << h24_Channel_15_padded [currentprofile_save][14] << comma
                << h24_Channel_16_padded [currentprofile_save][14] << comma
                << issmoothtransition_padded [currentprofile_save][14] << comma
                << transitiontime_padded [currentprofile_save][14];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //3:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][15] << comma
                << h24_Channel_2_padded [currentprofile_save][15] << comma
                << h24_Channel_3_padded [currentprofile_save][15] << comma
                << h24_Channel_4_padded [currentprofile_save][15] << comma
                << h24_Channel_5_padded [currentprofile_save][15] << comma
                << h24_Channel_6_padded [currentprofile_save][15] << comma
                << h24_Channel_7_padded [currentprofile_save][15] << comma
                << h24_Channel_8_padded [currentprofile_save][15] << comma
                << h24_Channel_9_padded [currentprofile_save][15] << comma
                << h24_Channel_10_padded [currentprofile_save][15] << comma
                << h24_Channel_11_padded [currentprofile_save][15] << comma
                << h24_Channel_12_padded [currentprofile_save][15] << comma
                << h24_Channel_13_padded [currentprofile_save][15] << comma
                << h24_Channel_14_padded [currentprofile_save][15] << comma
                << h24_Channel_15_padded [currentprofile_save][15] << comma
                << h24_Channel_16_padded [currentprofile_save][15] << comma
                << issmoothtransition_padded [currentprofile_save][15] << comma
                << transitiontime_padded [currentprofile_save][15];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //4:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][16] << comma
                << h24_Channel_2_padded [currentprofile_save][16] << comma
                << h24_Channel_3_padded [currentprofile_save][16] << comma
                << h24_Channel_4_padded [currentprofile_save][16] << comma
                << h24_Channel_5_padded [currentprofile_save][16] << comma
                << h24_Channel_6_padded [currentprofile_save][16] << comma
                << h24_Channel_7_padded [currentprofile_save][16] << comma
                << h24_Channel_8_padded [currentprofile_save][16] << comma
                << h24_Channel_9_padded [currentprofile_save][16] << comma
                << h24_Channel_10_padded [currentprofile_save][16] << comma
                << h24_Channel_11_padded [currentprofile_save][16] << comma
                << h24_Channel_12_padded [currentprofile_save][16] << comma
                << h24_Channel_13_padded [currentprofile_save][16] << comma
                << h24_Channel_14_padded [currentprofile_save][16] << comma
                << h24_Channel_15_padded [currentprofile_save][16] << comma
                << h24_Channel_16_padded [currentprofile_save][16] << comma
                << issmoothtransition_padded [currentprofile_save][16] << comma
                << transitiontime_padded [currentprofile_save][16];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //5:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][17] << comma
                << h24_Channel_2_padded [currentprofile_save][17] << comma
                << h24_Channel_3_padded [currentprofile_save][17] << comma
                << h24_Channel_4_padded [currentprofile_save][17] << comma
                << h24_Channel_5_padded [currentprofile_save][17] << comma
                << h24_Channel_6_padded [currentprofile_save][17] << comma
                << h24_Channel_7_padded [currentprofile_save][17] << comma
                << h24_Channel_8_padded [currentprofile_save][17] << comma
                << h24_Channel_9_padded [currentprofile_save][17] << comma
                << h24_Channel_10_padded [currentprofile_save][17] << comma
                << h24_Channel_11_padded [currentprofile_save][17] << comma
                << h24_Channel_12_padded [currentprofile_save][17] << comma
                << h24_Channel_13_padded [currentprofile_save][17] << comma
                << h24_Channel_14_padded [currentprofile_save][17] << comma
                << h24_Channel_15_padded [currentprofile_save][17] << comma
                << h24_Channel_16_padded [currentprofile_save][17] << comma
                << issmoothtransition_padded [currentprofile_save][17] << comma
                << transitiontime_padded [currentprofile_save][17];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);
       //6:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][18] << comma
                << h24_Channel_2_padded [currentprofile_save][18] << comma
                << h24_Channel_3_padded [currentprofile_save][18] << comma
                << h24_Channel_4_padded [currentprofile_save][18] << comma
                << h24_Channel_5_padded [currentprofile_save][18] << comma
                << h24_Channel_6_padded [currentprofile_save][18] << comma
                << h24_Channel_7_padded [currentprofile_save][18] << comma
                << h24_Channel_8_padded [currentprofile_save][18] << comma
                << h24_Channel_9_padded [currentprofile_save][18] << comma
                << h24_Channel_10_padded [currentprofile_save][18] << comma
                << h24_Channel_11_padded [currentprofile_save][18] << comma
                << h24_Channel_12_padded [currentprofile_save][18] << comma
                << h24_Channel_13_padded [currentprofile_save][18] << comma
                << h24_Channel_14_padded [currentprofile_save][18] << comma
                << h24_Channel_15_padded [currentprofile_save][18] << comma
                << h24_Channel_16_padded [currentprofile_save][18] << comma
                << issmoothtransition_padded [currentprofile_save][18] << comma
                << transitiontime_padded [currentprofile_save][18];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //7:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][19] << comma
                << h24_Channel_2_padded [currentprofile_save][19] << comma
                << h24_Channel_3_padded [currentprofile_save][19] << comma
                << h24_Channel_4_padded [currentprofile_save][19] << comma
                << h24_Channel_5_padded [currentprofile_save][19] << comma
                << h24_Channel_6_padded [currentprofile_save][19] << comma
                << h24_Channel_7_padded [currentprofile_save][19] << comma
                << h24_Channel_8_padded [currentprofile_save][19] << comma
                << h24_Channel_9_padded [currentprofile_save][19] << comma
                << h24_Channel_10_padded [currentprofile_save][19] << comma
                << h24_Channel_11_padded [currentprofile_save][19] << comma
                << h24_Channel_12_padded [currentprofile_save][19] << comma
                << h24_Channel_13_padded [currentprofile_save][19] << comma
                << h24_Channel_14_padded [currentprofile_save][19] << comma
                << h24_Channel_15_padded [currentprofile_save][19] << comma
                << h24_Channel_16_padded [currentprofile_save][19] << comma
                << issmoothtransition_padded [currentprofile_save][19] << comma
                << transitiontime_padded [currentprofile_save][19];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //8:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][20] << comma
                << h24_Channel_2_padded [currentprofile_save][20] << comma
                << h24_Channel_3_padded [currentprofile_save][20] << comma
                << h24_Channel_4_padded [currentprofile_save][20] << comma
                << h24_Channel_5_padded [currentprofile_save][20] << comma
                << h24_Channel_6_padded [currentprofile_save][20] << comma
                << h24_Channel_7_padded [currentprofile_save][20] << comma
                << h24_Channel_8_padded [currentprofile_save][20] << comma
                << h24_Channel_9_padded [currentprofile_save][20] << comma
                << h24_Channel_10_padded [currentprofile_save][20] << comma
                << h24_Channel_11_padded [currentprofile_save][20] << comma
                << h24_Channel_12_padded [currentprofile_save][20] << comma
                << h24_Channel_13_padded [currentprofile_save][20] << comma
                << h24_Channel_14_padded [currentprofile_save][20] << comma
                << h24_Channel_15_padded [currentprofile_save][20] << comma
                << h24_Channel_16_padded [currentprofile_save][20] << comma
                << issmoothtransition_padded [currentprofile_save][20] << comma
                << transitiontime_padded [currentprofile_save][20];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //9:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][21] << comma
                << h24_Channel_2_padded [currentprofile_save][21] << comma
                << h24_Channel_3_padded [currentprofile_save][21] << comma
                << h24_Channel_4_padded [currentprofile_save][21] << comma
                << h24_Channel_5_padded [currentprofile_save][21] << comma
                << h24_Channel_6_padded [currentprofile_save][21] << comma
                << h24_Channel_7_padded [currentprofile_save][21] << comma
                << h24_Channel_8_padded [currentprofile_save][21] << comma
                << h24_Channel_9_padded [currentprofile_save][21] << comma
                << h24_Channel_10_padded [currentprofile_save][21] << comma
                << h24_Channel_11_padded [currentprofile_save][21] << comma
                << h24_Channel_12_padded [currentprofile_save][21] << comma
                << h24_Channel_13_padded [currentprofile_save][21] << comma
                << h24_Channel_14_padded [currentprofile_save][21] << comma
                << h24_Channel_15_padded [currentprofile_save][21] << comma
                << h24_Channel_16_padded [currentprofile_save][21] << comma
                << issmoothtransition_padded [currentprofile_save][21] << comma
                << transitiontime_padded [currentprofile_save][21];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);
       //10:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][22] << comma
                << h24_Channel_2_padded [currentprofile_save][22] << comma
                << h24_Channel_3_padded [currentprofile_save][22] << comma
                << h24_Channel_4_padded [currentprofile_save][22] << comma
                << h24_Channel_5_padded [currentprofile_save][22] << comma
                << h24_Channel_6_padded [currentprofile_save][22] << comma
                << h24_Channel_7_padded [currentprofile_save][22] << comma
                << h24_Channel_8_padded [currentprofile_save][22] << comma
                << h24_Channel_9_padded [currentprofile_save][22] << comma
                << h24_Channel_10_padded [currentprofile_save][22] << comma
                << h24_Channel_11_padded [currentprofile_save][22] << comma
                << h24_Channel_12_padded [currentprofile_save][22] << comma
                << h24_Channel_13_padded [currentprofile_save][22] << comma
                << h24_Channel_14_padded [currentprofile_save][22] << comma
                << h24_Channel_15_padded [currentprofile_save][22] << comma
                << h24_Channel_16_padded [currentprofile_save][22] << comma
                << issmoothtransition_padded [currentprofile_save][22] << comma
                << transitiontime_padded [currentprofile_save][22];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            //11:00 pm
            h24buffer [currentlinenumber_save]
                 = h24_Channel_1_padded [currentprofile_save][23] << comma
                << h24_Channel_2_padded [currentprofile_save][23] << comma
                << h24_Channel_3_padded [currentprofile_save][23] << comma
                << h24_Channel_4_padded [currentprofile_save][23] << comma
                << h24_Channel_5_padded [currentprofile_save][23] << comma
                << h24_Channel_6_padded [currentprofile_save][23] << comma
                << h24_Channel_7_padded [currentprofile_save][23] << comma
                << h24_Channel_8_padded [currentprofile_save][23] << comma
                << h24_Channel_9_padded [currentprofile_save][23] << comma
                << h24_Channel_10_padded [currentprofile_save][23] << comma
                << h24_Channel_11_padded [currentprofile_save][23] << comma
                << h24_Channel_12_padded [currentprofile_save][23] << comma
                << h24_Channel_13_padded [currentprofile_save][23] << comma
                << h24_Channel_14_padded [currentprofile_save][23] << comma
                << h24_Channel_15_padded [currentprofile_save][23] << comma
                << h24_Channel_16_padded [currentprofile_save][23] << comma
                << issmoothtransition_padded [currentprofile_save][23] << comma
                << transitiontime_padded [currentprofile_save][23];
            h24file.AddLine(h24buffer [currentlinenumber_save++], wxTextFileType_Dos);

            currentprofile_save++;

        }
        h24file.Write(wxTextFileType_Dos, wxConvISO8859_1);
        h24file.Close();





}

void H24Timer::OnClose(wxCloseEvent& event)
{
    savecancel = false;
    if (istimeractive) {stop_timer(); return;}
    if (timerischanged) saveprofiles();
    if (savecancel) return;
    //if (!savecancel) {
        H24Timer1.Stop();
        if (istimeractive) {
            StopTimer Dlg(0);
            Dlg.ShowModal();
            if (stopyesorno) {

                    Destroy();
            }
        }
        else {
            //istimeractive = false;
            Destroy();
        }
        //{
            //H24Timer Dlg(0);
            //Dlg.AcceptAndClose();
        //}
        //else wxMessageBox (wxT("Stop the timer before closing."));
   // }
}

//copy to previous hour button
void H24Timer::OnButton7Click(wxCommandEvent& event)
{
    copyyesorno = false;

    H24CopyVerify Dlg(0);
    Dlg.ShowModal();

    if (copyyesorno) {
        int previoushour = ((ListBox1->GetSelection())-1);
        if (previoushour == -1) previoushour = 23;
        h24_Channel_1 [h24currentprofile] [previoushour] = Slider1->GetValue();
        h24_Channel_2 [h24currentprofile] [previoushour] = Slider2->GetValue();
        h24_Channel_3 [h24currentprofile] [previoushour] = Slider3->GetValue();
        h24_Channel_4 [h24currentprofile] [previoushour] = Slider4->GetValue();
        h24_Channel_5 [h24currentprofile] [previoushour] = Slider5->GetValue();
        h24_Channel_6 [h24currentprofile] [previoushour] = Slider6->GetValue();
        h24_Channel_7 [h24currentprofile] [previoushour] = Slider7->GetValue();
        h24_Channel_8 [h24currentprofile] [previoushour] = Slider8->GetValue();
        h24_Channel_9 [h24currentprofile] [previoushour] = Slider9->GetValue();
        h24_Channel_10 [h24currentprofile] [previoushour] = Slider10->GetValue();
        h24_Channel_11 [h24currentprofile] [previoushour] = Slider11->GetValue();
        h24_Channel_12 [h24currentprofile] [previoushour] = Slider12->GetValue();
        h24_Channel_13 [h24currentprofile] [previoushour] = Slider13->GetValue();
        h24_Channel_14 [h24currentprofile] [previoushour] = Slider14->GetValue();
        h24_Channel_15 [h24currentprofile] [previoushour] = Slider15->GetValue();
        h24_Channel_16 [h24currentprofile] [previoushour] = Slider16->GetValue();

        issmoothtransition [h24currentprofile] [previoushour] = CheckBox1->GetValue();
        transitiontime [h24currentprofile] [previoushour] = Choice1->GetSelection();

        ListBox1->SetSelection(previoushour);
        h24_updatelabels();

        timerischanged = true;
    }
}

//copy to next hour button
void H24Timer::OnButton8Click(wxCommandEvent& event)
{
    //isIconize = true;
    copyyesorno = false;

    H24CopyVerify Dlg(0);
    Dlg.ShowModal();

    if (copyyesorno) {
        int nexthour = ((ListBox1->GetSelection())+1);
        if (nexthour == 24) nexthour = 0;
        h24_Channel_1 [h24currentprofile] [nexthour] = Slider1->GetValue();
        h24_Channel_2 [h24currentprofile] [nexthour] = Slider2->GetValue();
        h24_Channel_3 [h24currentprofile] [nexthour] = Slider3->GetValue();
        h24_Channel_4 [h24currentprofile] [nexthour] = Slider4->GetValue();
        h24_Channel_5 [h24currentprofile] [nexthour] = Slider5->GetValue();
        h24_Channel_6 [h24currentprofile] [nexthour] = Slider6->GetValue();
        h24_Channel_7 [h24currentprofile] [nexthour] = Slider7->GetValue();
        h24_Channel_8 [h24currentprofile] [nexthour] = Slider8->GetValue();
        h24_Channel_9 [h24currentprofile] [nexthour] = Slider9->GetValue();
        h24_Channel_10 [h24currentprofile] [nexthour] = Slider10->GetValue();
        h24_Channel_11 [h24currentprofile] [nexthour] = Slider11->GetValue();
        h24_Channel_12 [h24currentprofile] [nexthour] = Slider12->GetValue();
        h24_Channel_13 [h24currentprofile] [nexthour] = Slider13->GetValue();
        h24_Channel_14 [h24currentprofile] [nexthour] = Slider14->GetValue();
        h24_Channel_15 [h24currentprofile] [nexthour] = Slider15->GetValue();
        h24_Channel_16 [h24currentprofile] [nexthour] = Slider16->GetValue();

        issmoothtransition [h24currentprofile] [nexthour] = CheckBox1->GetValue();
        transitiontime [h24currentprofile] [nexthour] = Choice1->GetSelection();

        ListBox1->SetSelection(nexthour);
        h24_updatelabels();

        timerischanged = true;
    }
}

void H24Timer::stop_timer(void)
{

        StopTimer Dlg2(0);
        Dlg2.ShowModal();




        //Button1->Enable(false);
       // StaticText35->SetFocus();
       // Sleep(200);

    if (stopyesorno) {
/*
            unsigned short int sgetminutes = wxAtoi(wxDateTime::Now().Format(wxT("%M")));
            unsigned short int sgetseconds = wxAtoi(wxDateTime::Now().Format(wxT("%S")));
            unsigned short int scurrentunit = (((sgetminutes * 60) + sgetseconds) / 20);
            if (scurrentunit == 0) scurrentunit = 1;

            for (int unitc = currentunit - 1; unitc < (currentunit + 5); unitc++ ) {

                hourtransitioncalculations [1] [unitc] = timer_ProfileChannel_1;
                hourtransitioncalculations [2] [unitc] = timer_ProfileChannel_2;
                hourtransitioncalculations [3] [unitc] = timer_ProfileChannel_3;
                hourtransitioncalculations [4] [unitc] = timer_ProfileChannel_4;
                hourtransitioncalculations [5] [unitc] = timer_ProfileChannel_5;
                hourtransitioncalculations [6] [unitc] = timer_ProfileChannel_6;
                hourtransitioncalculations [7] [unitc] = timer_ProfileChannel_7;
                hourtransitioncalculations [8] [unitc] = timer_ProfileChannel_8;
                hourtransitioncalculations [9] [unitc] = timer_ProfileChannel_9;
                hourtransitioncalculations [10] [unitc] = timer_ProfileChannel_10;
                hourtransitioncalculations [11] [unitc] = timer_ProfileChannel_11;
                hourtransitioncalculations [12] [unitc] = timer_ProfileChannel_12;
                hourtransitioncalculations [13] [unitc] = timer_ProfileChannel_13;
                hourtransitioncalculations [14] [unitc] = timer_ProfileChannel_14;
                hourtransitioncalculations [15] [unitc] = timer_ProfileChannel_15;
                hourtransitioncalculations [16] [unitc] = timer_ProfileChannel_16;
            }
*/
            //enable everything
            StaticBox1->Enable(true);
            StaticBox2->Enable(true);
            StaticBox3->Enable(true);
            ListBox1->Enable(true);
            ListBox2->Enable(true);
            Slider1->Enable(true);
            Slider2->Enable(true);
            Slider3->Enable(true);
            Slider4->Enable(true);
            Slider5->Enable(true);
            Slider6->Enable(true);
            Slider7->Enable(true);
            Slider8->Enable(true);
            Slider9->Enable(true);
            Slider10->Enable(true);
            Slider11->Enable(true);
            Slider12->Enable(true);
            Slider13->Enable(true);
            Slider14->Enable(true);
            Slider15->Enable(true);
            Slider16->Enable(true);
            CheckBox1->Enable(true);
            Button1->Enable(true);
            Button2->Enable(true);
            Button3->Enable(true);
            Button4->Enable(true);
            Button5->Enable(true);
            Button6->Enable(true);
            Button7->Enable(true);
            Button8->Enable(true);
            StaticText1->Enable(true);
            StaticText2->Enable(true);
            StaticText3->Enable(true);
            StaticText4->Enable(true);
            StaticText5->Enable(true);
            StaticText6->Enable(true);
            StaticText7->Enable(true);
            StaticText8->Enable(true);
            StaticText9->Enable(true);
            StaticText10->Enable(true);
            StaticText11->Enable(true);
            StaticText12->Enable(true);
            StaticText13->Enable(true);
            StaticText14->Enable(true);
            StaticText15->Enable(true);
            StaticText16->Enable(true);
            StaticText17->Enable(true);
            StaticText18->Enable(true);
            StaticText19->Enable(true);
            StaticText20->Enable(true);
            StaticText21->Enable(true);
            StaticText22->Enable(true);
            StaticText23->Enable(true);
            StaticText24->Enable(true);
            StaticText25->Enable(true);
            StaticText26->Enable(true);
            StaticText27->Enable(true);
            StaticText28->Enable(true);
            StaticText29->Enable(true);
            StaticText30->Enable(true);
            StaticText31->Enable(true);
            StaticText32->Enable(true);
            StaticText33->Enable(true);
            Choice1->Enable(true);


            Button1->SetLabel(wxT("Activate 24-Hour Light Timer"));
/*
            Channel_1_timer = timer_ProfileChannel_1;
            Channel_2_timer = timer_ProfileChannel_2;
            Channel_3_timer = timer_ProfileChannel_3;
            Channel_4_timer = timer_ProfileChannel_4;
            Channel_5_timer = timer_ProfileChannel_5;
            Channel_6_timer = timer_ProfileChannel_6;
            Channel_7_timer = timer_ProfileChannel_7;
            Channel_8_timer = timer_ProfileChannel_8;
            Channel_9_timer = timer_ProfileChannel_9;
            Channel_10_timer = timer_ProfileChannel_10;
            Channel_11_timer = timer_ProfileChannel_11;
            Channel_12_timer = timer_ProfileChannel_12;
            Channel_13_timer = timer_ProfileChannel_13;
            Channel_14_timer = timer_ProfileChannel_14;
            Channel_15_timer = timer_ProfileChannel_15;
            Channel_16_timer = timer_ProfileChannel_16;
*/




            //wxMessageBox (wxT("test"),wxT("test"));

            //StopWatch1.Start(0);
            //do {}
            //while (StopWatch1.Time() < 2000);

            //Sleep(1000);

            istimeractive = false;
            //Button1->Enable(true);
            //Choice1->Enable(true);
        }//close if stopyesorno
           // else {
               // Button1->Enable(true);
               // return;
       // }
        //Button1->Enable(true);

}


/*

void H24Timer::OnResize1(wxSizeEvent& event)
{
            //isIconize = true;
}

void H24Timer::OnEraseBackground1(wxEraseEvent& event)
{
                //isIconize = true;
}

void H24Timer::OnKillFocus1(wxFocusEvent& event)
{
                //isIconize = true;
}

void H24Timer::OnMouseLeave1(wxMouseEvent& event)
{
                //isIconize = true;
}

void H24Timer::OnSetFocus(wxFocusEvent& event)
{
                //isIconize = true;
}

void H24Timer::OnPaint(wxPaintEvent& event)
{

}
*/


void H24Timer::OnButton9Click(wxCommandEvent& event)
{
    //used for windows minimize fix
    isIconize = true;

}

