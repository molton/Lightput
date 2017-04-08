/***************************************************************
 * Name:      gui10Main.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2012    09-30
 * Copyright:  (C) Michael Johnston
 * License:
 **************************************************************/

#include "gui10Main.h"

#include "FTDI_interface.h"
#include "NewDialog.h"
#include "AddNewProfile.h"
#include "DeleteVerify.h"
#include "RenameProfile.h"
#include "ProfileOverwrite.h"
#include "LightPrograms.h"
#include "SaveOnQuit.h"
#include "Options.h"
#include "SaveFirst.h"

#include <wx/textfile.h>
#include <wx/msgdlg.h>
#include <wx/timer.h>
#include <wx/event.h>
//#include <wx/toplevel.h>
//(*InternalHeaders(gui10Frame)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
//*)


//#include "wxMidi.h"


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(gui10Frame)
const long gui10Frame::ID_STATICBOX1 = wxNewId();
const long gui10Frame::ID_LISTBOX1 = wxNewId();
const long gui10Frame::ID_BUTTON4 = wxNewId();
const long gui10Frame::ID_BUTTON8 = wxNewId();
const long gui10Frame::ID_BUTTON7 = wxNewId();
const long gui10Frame::ID_BUTTON2 = wxNewId();
const long gui10Frame::ID_BUTTON6 = wxNewId();
const long gui10Frame::ID_BUTTON1 = wxNewId();
const long gui10Frame::ID_BUTTON9 = wxNewId();
const long gui10Frame::ID_BUTTON11 = wxNewId();
const long gui10Frame::ID_BUTTON3 = wxNewId();
const long gui10Frame::ID_BUTTON12 = wxNewId();
const long gui10Frame::ID_BUTTON5 = wxNewId();
const long gui10Frame::ID_SLIDER1 = wxNewId();
const long gui10Frame::ID_SLIDER2 = wxNewId();
const long gui10Frame::ID_SLIDER3 = wxNewId();
const long gui10Frame::ID_SLIDER4 = wxNewId();
const long gui10Frame::ID_SLIDER5 = wxNewId();
const long gui10Frame::ID_SLIDER6 = wxNewId();
const long gui10Frame::ID_SLIDER7 = wxNewId();
const long gui10Frame::ID_SLIDER8 = wxNewId();
const long gui10Frame::ID_SLIDER9 = wxNewId();
const long gui10Frame::ID_SLIDER10 = wxNewId();
const long gui10Frame::ID_SLIDER11 = wxNewId();
const long gui10Frame::ID_SLIDER12 = wxNewId();
const long gui10Frame::ID_SLIDER13 = wxNewId();
const long gui10Frame::ID_SLIDER14 = wxNewId();
const long gui10Frame::ID_SLIDER15 = wxNewId();
const long gui10Frame::ID_SLIDER16 = wxNewId();
const long gui10Frame::ID_STATICTEXT2 = wxNewId();
const long gui10Frame::ID_STATICTEXT4 = wxNewId();
const long gui10Frame::ID_STATICTEXT3 = wxNewId();
const long gui10Frame::ID_STATICTEXT1 = wxNewId();
const long gui10Frame::ID_STATICTEXT5 = wxNewId();
const long gui10Frame::ID_STATICTEXT6 = wxNewId();
const long gui10Frame::ID_STATICTEXT7 = wxNewId();
const long gui10Frame::ID_STATICTEXT8 = wxNewId();
const long gui10Frame::ID_STATICTEXT9 = wxNewId();
const long gui10Frame::ID_STATICTEXT10 = wxNewId();
const long gui10Frame::ID_STATICTEXT12 = wxNewId();
const long gui10Frame::ID_STATICTEXT17 = wxNewId();
const long gui10Frame::ID_STATICTEXT18 = wxNewId();
const long gui10Frame::ID_STATICTEXT22 = wxNewId();
const long gui10Frame::ID_STATICTEXT21 = wxNewId();
const long gui10Frame::ID_STATICTEXT20 = wxNewId();
const long gui10Frame::ID_STATICTEXT19 = wxNewId();
const long gui10Frame::ID_STATICTEXT16 = wxNewId();
const long gui10Frame::ID_STATICTEXT15 = wxNewId();
const long gui10Frame::ID_STATICTEXT14 = wxNewId();
const long gui10Frame::ID_STATICTEXT13 = wxNewId();
const long gui10Frame::ID_STATICTEXT11 = wxNewId();
const long gui10Frame::ID_STATICTEXT23 = wxNewId();
const long gui10Frame::ID_STATICTEXT24 = wxNewId();
const long gui10Frame::ID_STATICTEXT25 = wxNewId();
const long gui10Frame::ID_STATICTEXT26 = wxNewId();
const long gui10Frame::ID_STATICTEXT27 = wxNewId();
const long gui10Frame::ID_STATICTEXT28 = wxNewId();
const long gui10Frame::ID_STATICTEXT29 = wxNewId();
const long gui10Frame::ID_STATICTEXT30 = wxNewId();
const long gui10Frame::ID_STATICTEXT31 = wxNewId();
const long gui10Frame::ID_STATICTEXT32 = wxNewId();
const long gui10Frame::ID_STATICTEXT33 = wxNewId();
const long gui10Frame::ID_STATICTEXT34 = wxNewId();
const long gui10Frame::ID_STATICTEXT35 = wxNewId();
const long gui10Frame::ID_STATICTEXT36 = wxNewId();
const long gui10Frame::ID_MENUITEM2 = wxNewId();
const long gui10Frame::ID_MENUITEM1 = wxNewId();
const long gui10Frame::idMenuQuit = wxNewId();
const long gui10Frame::idMenuHelp = wxNewId();
const long gui10Frame::idMenuAbout = wxNewId();
const long gui10Frame::ID_TIMER1 = wxNewId();
//*)


bool isconnected;
bool isconnectionattempt;
bool isactive;
bool isselectionchange;
bool isloading;
bool isnamevariable;
bool isprofilemode;
bool issavefirst;
bool isexporting;
bool isnewblankprofile;
bool issaveonquit;
bool iscancelquit;
//lets program know if a profile set should be saved or not
bool ischanged;
bool isbeattimecalculationchange;

bool isfirstruninitialize;

bool istimeractive;

//these bools control the main timer's code path
bool isbs;
bool isalarm;
bool is24hmode;
bool isMidiControlmode;
bool isVSXumode;
bool isLightScripts;

bool islightsequencer;

bool isIconize;

bool VSXuInitialize;
bool hasVSXurunonce;

bool MidiInitialize;

bool isExternalInput;



//for delete verify
bool yesorno;
bool generalcancel;


//int profileselection = 0;
int numberofprofiles;
int currentprofile;
wxString messageboxtest;
wxString newprofileValue;
wxString profilefilename;
//directory thing can be removed
wxString directory = wxT("./");
wxString profiledirectory;
wxString fullpath;
wxString nameofexport;
wxString nameofnewprofile;
unsigned short int LightputFrequency;
bool isminimizedonstartup;
bool islightprogramonstartup;
bool runlightprogramonstartup;
//linux startup fix
unsigned short int counttostart;

unsigned short int startuplightprogram;

//extern VSXuRenderer *vsxu_renderer;

//i couldnt figure out a way to dynamically assign
//these array initializers, so I made the value a static
//64, which restricts the amount of profiles to 64
wxString Value [64];
wxString tempValue [64];
//int numberofvalues [64];
unsigned short int v1 [64];
unsigned short int v2 [64];
unsigned short int v3 [64];
unsigned short int v4 [64];
unsigned short int v5 [64];
unsigned short int v6 [64];
unsigned short int v7 [64];
unsigned short int v8 [64];
unsigned short int v9 [64];
unsigned short int v10 [64];
unsigned short int v11 [64];
unsigned short int v12 [64];
unsigned short int v13 [64];
unsigned short int v14 [64];
unsigned short int v15 [64];
unsigned short int v16 [64];

unsigned short int StartingDMXChannel;
unsigned short int blankchannels;
unsigned short int Channel_1;
unsigned short int Channel_2;
unsigned short int Channel_3;
unsigned short int Channel_4;
unsigned short int Channel_5;
unsigned short int Channel_6;
unsigned short int Channel_7;
unsigned short int Channel_8;
unsigned short int Channel_9;
unsigned short int Channel_10;
unsigned short int Channel_11;
unsigned short int Channel_12;
unsigned short int Channel_13;
unsigned short int Channel_14;
unsigned short int Channel_15;
unsigned short int Channel_16;

unsigned short int s1v;
unsigned short int s2v;
unsigned short int s3v;
unsigned short int s4v;
unsigned short int s5v;
unsigned short int s6v;
unsigned short int s7v;
unsigned short int s8v;
unsigned short int s9v;
unsigned short int s10v;
unsigned short int s11v;
unsigned short int s12v;
unsigned short int s13v;
unsigned short int s14v;
unsigned short int s15v;
unsigned short int s16v;

wxString s1value;
wxString s2value;
wxString s3value;
wxString s4value;
wxString s5value;
wxString s6value;
wxString s7value;
wxString s8value;
wxString s9value;
wxString s10value;
wxString s11value;
wxString s12value;
wxString s13value;
wxString s14value;
wxString s15value;
wxString s16value;

//variables for DMX information transmission
FT_STATUS ftStatus;
FT_STATUS ftStatus2;
FT_HANDLE ftHandle1;
FT_HANDLE ftHandle2;
FT_HANDLE ftHandle3;
FT_HANDLE ftHandle4;

//DMXtimer LightputEngineTimer;

unsigned short int dmxmode;
bool is_usb_connected;
bool is_usb_connected2;
bool is_usb_connected3;
bool is_usb_connected4;
bool isDMXcascade;
unsigned short int DMXcascadecount;

FTDI_interface *dmx_sender_thread;
FTDI_interface *dmx_sender_thread2;
FTDI_interface *dmx_sender_thread3;
FTDI_interface *dmx_sender_thread4;

//variables for light script options
bool islsRepeat;
bool islsStartOn1;


//buffers for profile when blinking is off/done
unsigned short int ProfileChannel_1;
unsigned short int ProfileChannel_2;
unsigned short int ProfileChannel_3;
unsigned short int ProfileChannel_4;
unsigned short int ProfileChannel_5;
unsigned short int ProfileChannel_6;
unsigned short int ProfileChannel_7;
unsigned short int ProfileChannel_8;
unsigned short int ProfileChannel_9;
unsigned short int ProfileChannel_10;
unsigned short int ProfileChannel_11;
unsigned short int ProfileChannel_12;
unsigned short int ProfileChannel_13;
unsigned short int ProfileChannel_14;
unsigned short int ProfileChannel_15;
unsigned short int ProfileChannel_16;

unsigned short int bs_ProfileChannel_1;
unsigned short int bs_ProfileChannel_2;
unsigned short int bs_ProfileChannel_3;
unsigned short int bs_ProfileChannel_4;
unsigned short int bs_ProfileChannel_5;
unsigned short int bs_ProfileChannel_6;
unsigned short int bs_ProfileChannel_7;
unsigned short int bs_ProfileChannel_8;
unsigned short int bs_ProfileChannel_9;
unsigned short int bs_ProfileChannel_10;
unsigned short int bs_ProfileChannel_11;
unsigned short int bs_ProfileChannel_12;
unsigned short int bs_ProfileChannel_13;
unsigned short int bs_ProfileChannel_14;
unsigned short int bs_ProfileChannel_15;
unsigned short int bs_ProfileChannel_16;

unsigned short int ls_ProfileChannel_1;
unsigned short int ls_ProfileChannel_2;
unsigned short int ls_ProfileChannel_3;
unsigned short int ls_ProfileChannel_4;
unsigned short int ls_ProfileChannel_5;
unsigned short int ls_ProfileChannel_6;
unsigned short int ls_ProfileChannel_7;
unsigned short int ls_ProfileChannel_8;
unsigned short int ls_ProfileChannel_9;
unsigned short int ls_ProfileChannel_10;
unsigned short int ls_ProfileChannel_11;
unsigned short int ls_ProfileChannel_12;
unsigned short int ls_ProfileChannel_13;
unsigned short int ls_ProfileChannel_14;
unsigned short int ls_ProfileChannel_15;
unsigned short int ls_ProfileChannel_16;


unsigned short int alarm_ProfileChannel_1;
unsigned short int alarm_ProfileChannel_2;
unsigned short int alarm_ProfileChannel_3;
unsigned short int alarm_ProfileChannel_4;
unsigned short int alarm_ProfileChannel_5;
unsigned short int alarm_ProfileChannel_6;
unsigned short int alarm_ProfileChannel_7;
unsigned short int alarm_ProfileChannel_8;
unsigned short int alarm_ProfileChannel_9;
unsigned short int alarm_ProfileChannel_10;
unsigned short int alarm_ProfileChannel_11;
unsigned short int alarm_ProfileChannel_12;
unsigned short int alarm_ProfileChannel_13;
unsigned short int alarm_ProfileChannel_14;
unsigned short int alarm_ProfileChannel_15;
unsigned short int alarm_ProfileChannel_16;

unsigned short int timer_ProfileChannel_1;
unsigned short int timer_ProfileChannel_2;
unsigned short int timer_ProfileChannel_3;
unsigned short int timer_ProfileChannel_4;
unsigned short int timer_ProfileChannel_5;
unsigned short int timer_ProfileChannel_6;
unsigned short int timer_ProfileChannel_7;
unsigned short int timer_ProfileChannel_8;
unsigned short int timer_ProfileChannel_9;
unsigned short int timer_ProfileChannel_10;
unsigned short int timer_ProfileChannel_11;
unsigned short int timer_ProfileChannel_12;
unsigned short int timer_ProfileChannel_13;
unsigned short int timer_ProfileChannel_14;
unsigned short int timer_ProfileChannel_15;
unsigned short int timer_ProfileChannel_16;

unsigned short int VSXu_ProfileChannel_1;
unsigned short int VSXu_ProfileChannel_2;
unsigned short int VSXu_ProfileChannel_3;
unsigned short int VSXu_ProfileChannel_4;
unsigned short int VSXu_ProfileChannel_5;
unsigned short int VSXu_ProfileChannel_6;
unsigned short int VSXu_ProfileChannel_7;
unsigned short int VSXu_ProfileChannel_8;
unsigned short int VSXu_ProfileChannel_9;
unsigned short int VSXu_ProfileChannel_10;
unsigned short int VSXu_ProfileChannel_11;
unsigned short int VSXu_ProfileChannel_12;
unsigned short int VSXu_ProfileChannel_13;
unsigned short int VSXu_ProfileChannel_14;
unsigned short int VSXu_ProfileChannel_15;
unsigned short int VSXu_ProfileChannel_16;


unsigned short int Channel_1_VSXu;
unsigned short int Channel_2_VSXu;
unsigned short int Channel_3_VSXu;
unsigned short int Channel_4_VSXu;
unsigned short int Channel_5_VSXu;
unsigned short int Channel_6_VSXu;
unsigned short int Channel_7_VSXu;
unsigned short int Channel_8_VSXu;
unsigned short int Channel_9_VSXu;
unsigned short int Channel_10_VSXu;
unsigned short int Channel_11_VSXu;
unsigned short int Channel_12_VSXu;
unsigned short int Channel_13_VSXu;
unsigned short int Channel_14_VSXu;
unsigned short int Channel_15_VSXu;
unsigned short int Channel_16_VSXu;

unsigned short int Channel_1_MidiControl;
unsigned short int Channel_2_MidiControl;
unsigned short int Channel_3_MidiControl;
unsigned short int Channel_4_MidiControl;
unsigned short int Channel_5_MidiControl;
unsigned short int Channel_6_MidiControl;
unsigned short int Channel_7_MidiControl;
unsigned short int Channel_8_MidiControl;
unsigned short int Channel_9_MidiControl;
unsigned short int Channel_10_MidiControl;
unsigned short int Channel_11_MidiControl;
unsigned short int Channel_12_MidiControl;
unsigned short int Channel_13_MidiControl;
unsigned short int Channel_14_MidiControl;
unsigned short int Channel_15_MidiControl;
unsigned short int Channel_16_MidiControl;

unsigned short int Channel_1_ExternalInput;
unsigned short int Channel_2_ExternalInput;
unsigned short int Channel_3_ExternalInput;
unsigned short int Channel_4_ExternalInput;
unsigned short int Channel_5_ExternalInput;
unsigned short int Channel_6_ExternalInput;
unsigned short int Channel_7_ExternalInput;
unsigned short int Channel_8_ExternalInput;
unsigned short int Channel_9_ExternalInput;
unsigned short int Channel_10_ExternalInput;
unsigned short int Channel_11_ExternalInput;
unsigned short int Channel_12_ExternalInput;
unsigned short int Channel_13_ExternalInput;
unsigned short int Channel_14_ExternalInput;
unsigned short int Channel_15_ExternalInput;
unsigned short int Channel_16_ExternalInput;

//options variables
unsigned short int option_dmxmode;
wxString option_defaultprofile;
unsigned short int option_profiletime;
//this value is for an option for the blink sequencer, to set the default transition type
bool issmooth;
bool issmoothstart;
unsigned short int beattime;

//variables for smooth transition
double Channel_1_difference;
double Channel_1_increment;
double Channel_1_added;
unsigned short int Channel_1_new;
unsigned short int Channel_1_out;
double Channel_2_difference;
double Channel_2_increment;
double Channel_2_added;
unsigned short int Channel_2_new;
unsigned short int Channel_2_out;
double Channel_3_difference;
double Channel_3_increment;
double Channel_3_added;
unsigned short int Channel_3_new;
unsigned short int Channel_3_out;
double Channel_4_difference;
double Channel_4_increment;
double Channel_4_added;
unsigned short int Channel_4_new;
unsigned short int Channel_4_out;
double Channel_5_difference;
double Channel_5_increment;
double Channel_5_added;
unsigned short int Channel_5_new;
unsigned short int Channel_5_out;
double Channel_6_difference;
double Channel_6_increment;
double Channel_6_added;
unsigned short int Channel_6_new;
unsigned short int Channel_6_out;
double Channel_7_difference;
double Channel_7_increment;
double Channel_7_added;
unsigned short int Channel_7_new;
unsigned short int Channel_7_out;
double Channel_8_difference;
double Channel_8_increment;
double Channel_8_added;
unsigned short int Channel_8_new;
unsigned short int Channel_8_out;
double Channel_9_difference;
double Channel_9_increment;
double Channel_9_added;
unsigned short int Channel_9_new;
unsigned short int Channel_9_out;
double Channel_10_difference;
double Channel_10_increment;
double Channel_10_added;
unsigned short int Channel_10_new;
unsigned short int Channel_10_out;
double Channel_11_difference;
double Channel_11_increment;
double Channel_11_added;
unsigned short int Channel_11_new;
unsigned short int Channel_11_out;
double Channel_12_difference;
double Channel_12_increment;
double Channel_12_added;
unsigned short int Channel_12_new;
unsigned short int Channel_12_out;
double Channel_13_difference;
double Channel_13_increment;
double Channel_13_added;
unsigned short int Channel_13_new;
unsigned short int Channel_13_out;
double Channel_14_difference;
double Channel_14_increment;
double Channel_14_added;
unsigned short int Channel_14_new;
unsigned short int Channel_14_out;
double Channel_15_difference;
double Channel_15_increment;
double Channel_15_added;
unsigned short int Channel_15_new;
unsigned short int Channel_15_out;
double Channel_16_difference;
double Channel_16_increment;
double Channel_16_added;
unsigned short int Channel_16_new;
unsigned short int Channel_16_out;



//variables for light sequencer
extern double bsChannel_1_difference;
extern double bsChannel_1_increment;
extern double bsChannel_1_added;
extern unsigned short int bsChannel_1_new;
extern unsigned short int bsChannel_1_out;
extern double bsChannel_2_difference;
extern double bsChannel_2_increment;
extern double bsChannel_2_added;
extern unsigned short int bsChannel_2_new;
extern unsigned short int bsChannel_2_out;
extern double bsChannel_3_difference;
extern double bsChannel_3_increment;
extern double bsChannel_3_added;
extern unsigned short int bsChannel_3_new;
extern unsigned short int bsChannel_3_out;
extern double bsChannel_4_difference;
extern double bsChannel_4_increment;
extern double bsChannel_4_added;
extern unsigned short int bsChannel_4_new;
extern unsigned short int bsChannel_4_out;
extern double bsChannel_5_difference;
extern double bsChannel_5_increment;
extern double bsChannel_5_added;
extern unsigned short int bsChannel_5_new;
extern unsigned short int bsChannel_5_out;
extern double bsChannel_6_difference;
extern double bsChannel_6_increment;
extern double bsChannel_6_added;
extern unsigned short int bsChannel_6_new;
extern unsigned short int bsChannel_6_out;
extern double bsChannel_7_difference;
extern double bsChannel_7_increment;
extern double bsChannel_7_added;
extern unsigned short int bsChannel_7_new;
extern unsigned short int bsChannel_7_out;
extern double bsChannel_8_difference;
extern double bsChannel_8_increment;
extern double bsChannel_8_added;
extern unsigned short int bsChannel_8_new;
extern unsigned short int bsChannel_8_out;
extern double bsChannel_9_difference;
extern double bsChannel_9_increment;
extern double bsChannel_9_added;
extern unsigned short int bsChannel_9_new;
extern unsigned short int bsChannel_9_out;
extern double bsChannel_10_difference;
extern double bsChannel_10_increment;
extern double bsChannel_10_added;
extern unsigned short int bsChannel_10_new;
extern unsigned short int bsChannel_10_out;
extern double bsChannel_11_difference;
extern double bsChannel_11_increment;
extern double bsChannel_11_added;
extern unsigned short int bsChannel_11_new;
extern unsigned short int bsChannel_11_out;
extern double bsChannel_12_difference;
extern double bsChannel_12_increment;
extern double bsChannel_12_added;
extern unsigned short int bsChannel_12_new;
extern unsigned short int bsChannel_12_out;
extern double bsChannel_13_difference;
extern double bsChannel_13_increment;
extern double bsChannel_13_added;
extern unsigned short int bsChannel_13_new;
extern unsigned short int bsChannel_13_out;
extern double bsChannel_14_difference;
extern double bsChannel_14_increment;
extern double bsChannel_14_added;
extern unsigned short int bsChannel_14_new;
extern unsigned short int bsChannel_14_out;
extern double bsChannel_15_difference;
extern double bsChannel_15_increment;
extern double bsChannel_15_added;
extern unsigned short int bsChannel_15_new;
extern unsigned short int bsChannel_15_out;
extern double bsChannel_16_difference;
extern double bsChannel_16_increment;
extern double bsChannel_16_added;
extern unsigned short int bsChannel_16_new;
extern unsigned short int bsChannel_16_out;

//variables for light scripts
extern double lsChannel_1_difference;
extern double lsChannel_1_increment;
extern double lsChannel_1_added;
extern unsigned short int lsChannel_1_new;
extern unsigned short int lsChannel_1_out;
extern double lsChannel_2_difference;
extern double lsChannel_2_increment;
extern double lsChannel_2_added;
extern unsigned short int lsChannel_2_new;
extern unsigned short int lsChannel_2_out;
extern double lsChannel_3_difference;
extern double lsChannel_3_increment;
extern double lsChannel_3_added;
extern unsigned short int lsChannel_3_new;
extern unsigned short int lsChannel_3_out;
extern double lsChannel_4_difference;
extern double lsChannel_4_increment;
extern double lsChannel_4_added;
extern unsigned short int lsChannel_4_new;
extern unsigned short int lsChannel_4_out;
extern double lsChannel_5_difference;
extern double lsChannel_5_increment;
extern double lsChannel_5_added;
extern unsigned short int lsChannel_5_new;
extern unsigned short int lsChannel_5_out;
extern double lsChannel_6_difference;
extern double lsChannel_6_increment;
extern double lsChannel_6_added;
extern unsigned short int lsChannel_6_new;
extern unsigned short int lsChannel_6_out;
extern double lsChannel_7_difference;
extern double lsChannel_7_increment;
extern double lsChannel_7_added;
extern unsigned short int lsChannel_7_new;
extern unsigned short int lsChannel_7_out;
extern double lsChannel_8_difference;
extern double lsChannel_8_increment;
extern double lsChannel_8_added;
extern unsigned short int lsChannel_8_new;
extern unsigned short int lsChannel_8_out;
extern double lsChannel_9_difference;
extern double lsChannel_9_increment;
extern double lsChannel_9_added;
extern unsigned short int lsChannel_9_new;
extern unsigned short int lsChannel_9_out;
extern double lsChannel_10_difference;
extern double lsChannel_10_increment;
extern double lsChannel_10_added;
extern unsigned short int lsChannel_10_new;
extern unsigned short int lsChannel_10_out;
extern double lsChannel_11_difference;
extern double lsChannel_11_increment;
extern double lsChannel_11_added;
extern unsigned short int lsChannel_11_new;
extern unsigned short int lsChannel_11_out;
extern double lsChannel_12_difference;
extern double lsChannel_12_increment;
extern double lsChannel_12_added;
extern unsigned short int lsChannel_12_new;
extern unsigned short int lsChannel_12_out;
extern double lsChannel_13_difference;
extern double lsChannel_13_increment;
extern double lsChannel_13_added;
extern unsigned short int lsChannel_13_new;
extern unsigned short int lsChannel_13_out;
extern double lsChannel_14_difference;
extern double lsChannel_14_increment;
extern double lsChannel_14_added;
extern unsigned short int lsChannel_14_new;
extern unsigned short int lsChannel_14_out;
extern double lsChannel_15_difference;
extern double lsChannel_15_increment;
extern double lsChannel_15_added;
extern unsigned short int lsChannel_15_new;
extern unsigned short int lsChannel_15_out;
extern double lsChannel_16_difference;
extern double lsChannel_16_increment;
extern double lsChannel_16_added;
extern unsigned short int lsChannel_16_new;
extern unsigned short int lsChannel_16_out;


//output variables for alarm clock
unsigned short int Channel_1_alarm;
unsigned short int Channel_2_alarm;
unsigned short int Channel_3_alarm;
unsigned short int Channel_4_alarm;
unsigned short int Channel_5_alarm;
unsigned short int Channel_6_alarm;
unsigned short int Channel_7_alarm;
unsigned short int Channel_8_alarm;
unsigned short int Channel_9_alarm;
unsigned short int Channel_10_alarm;
unsigned short int Channel_11_alarm;
unsigned short int Channel_12_alarm;
unsigned short int Channel_13_alarm;
unsigned short int Channel_14_alarm;
unsigned short int Channel_15_alarm;
unsigned short int Channel_16_alarm;


//output variables for timer
extern unsigned short int Channel_1_timer;
extern unsigned short int Channel_2_timer;
extern unsigned short int Channel_3_timer;
extern unsigned short int Channel_4_timer;
extern unsigned short int Channel_5_timer;
extern unsigned short int Channel_6_timer;
extern unsigned short int Channel_7_timer;
extern unsigned short int Channel_8_timer;
extern unsigned short int Channel_9_timer;
extern unsigned short int Channel_10_timer;
extern unsigned short int Channel_11_timer;
extern unsigned short int Channel_12_timer;
extern unsigned short int Channel_13_timer;
extern unsigned short int Channel_14_timer;
extern unsigned short int Channel_15_timer;
extern unsigned short int Channel_16_timer;



BEGIN_EVENT_TABLE(gui10Frame,wxFrame)
    //(*EventTable(gui10Frame)
    //*)
END_EVENT_TABLE()


gui10Frame::gui10Frame(wxWindow* parent,wxWindowID id)
{



    /*SingleInstanceChecker1.Create(wxTheApp->GetAppName() + _T("_") + wxGetUserId() + _T("_Guard"));
if (SingleInstanceChecker1.IsAnotherRunning()){
    wxMessageBox (wxT("Only one instance of Lightput is allowed to run at a time.  Please close any instances of Lightput that are currently open before opening Lightput."),wxT("Error"));
    Destroy();
}
*/
//size 430 4 channel - 840 16 channel mode
    //SetClientSize(wxSize(445,568));
    //SetMinSize(wxSize(445,568));
   // SetMaxSize(wxSize(445,568));

    //(*Initialize(gui10Frame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuItem* MenuItem5;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("Lightput 1.0 (with VSXu audio visualizer)"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL, _T("wxID_ANY"));
    SetClientSize(wxSize(843,524));
    Move(wxPoint(50,50));
    SetMaxSize(wxSize(840,568));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("graphics/Lightput.ico"))));
    	SetIcon(FrameIcon);
    }
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(16,0), wxSize(288,60), 0, _T("ID_STATICBOX1"));
    ListBox1 = new wxListBox(this, ID_LISTBOX1, wxPoint(16,72), wxSize(352,128), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    ListBox1->SetFocus();
    Button4 = new wxButton(this, ID_BUTTON4, _("Connect"), wxPoint(320,8), wxSize(96,48), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    wxFont Button4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button4->SetFont(Button4Font);
    Button8 = new wxButton(this, ID_BUTTON8, _("Move\nUp"), wxPoint(368,72), wxSize(48,64), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    wxFont Button8Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button8->SetFont(Button8Font);
    Button7 = new wxButton(this, ID_BUTTON7, _("Move\nDown"), wxPoint(368,136), wxSize(48,64), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    wxFont Button7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button7->SetFont(Button7Font);
    Button2 = new wxButton(this, ID_BUTTON2, _("Light Programs"), wxPoint(24,216), wxSize(120,24), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    wxFont Button2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button2->SetFont(Button2Font);
    Button6 = new wxButton(this, ID_BUTTON6, _("Delete Profile"), wxPoint(160,216), wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    wxFont Button6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button6->SetFont(Button6Font);
    Button1 = new wxButton(this, ID_BUTTON1, _("Save Profile Set"), wxPoint(296,216), wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    wxFont Button1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button1->SetFont(Button1Font);
    Button9 = new wxButton(this, ID_BUTTON9, _("New Profile"), wxPoint(24,248), wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    wxFont Button9Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button9->SetFont(Button9Font);
    Button9->SetHelpText(_("Adds a new profile containing current DMX values"));
    Button11 = new wxButton(this, ID_BUTTON11, _("Rename Profile"), wxPoint(160,248), wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON11"));
    wxFont Button11Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button11->SetFont(Button11Font);
    Button3 = new wxButton(this, ID_BUTTON3, _("Change Profiles"), wxPoint(296,248), wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    wxFont Button3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button3->SetFont(Button3Font);
    Button12 = new wxButton(this, ID_BUTTON12, _("Options"), wxPoint(32,464), wxSize(120,29), 0, wxDefaultValidator, _T("ID_BUTTON12"));
    wxFont Button12Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button12->SetFont(Button12Font);
    Button5 = new wxButton(this, ID_BUTTON5, _("Switch to 16-Channel DMX Mode"), wxPoint(184,464), wxSize(232,31), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    wxFont Button5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button5->SetFont(Button5Font);
    Slider1 = new wxSlider(this, ID_SLIDER1, 0, 0, 255, wxPoint(104,288), wxSize(272,24), 0, wxDefaultValidator, _T("ID_SLIDER1"));
    Slider2 = new wxSlider(this, ID_SLIDER2, 0, 0, 255, wxPoint(104,328), wxSize(272,24), 0, wxDefaultValidator, _T("ID_SLIDER2"));
    Slider3 = new wxSlider(this, ID_SLIDER3, 0, 0, 255, wxPoint(104,368), wxSize(272,24), 0, wxDefaultValidator, _T("ID_SLIDER3"));
    Slider4 = new wxSlider(this, ID_SLIDER4, 0, 0, 255, wxPoint(104,408), wxSize(272,24), 0, wxDefaultValidator, _T("ID_SLIDER4"));
    Slider5 = new wxSlider(this, ID_SLIDER5, 0, 0, 255, wxPoint(568,16), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER5"));
    Slider6 = new wxSlider(this, ID_SLIDER6, 0, 0, 255, wxPoint(568,56), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER6"));
    Slider7 = new wxSlider(this, ID_SLIDER7, 0, 0, 255, wxPoint(568,96), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER7"));
    Slider8 = new wxSlider(this, ID_SLIDER8, 0, 0, 255, wxPoint(568,136), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER8"));
    Slider9 = new wxSlider(this, ID_SLIDER9, 0, 0, 255, wxPoint(568,176), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER9"));
    Slider10 = new wxSlider(this, ID_SLIDER10, 0, 0, 255, wxPoint(568,216), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER10"));
    Slider11 = new wxSlider(this, ID_SLIDER11, 0, 0, 255, wxPoint(568,256), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER11"));
    Slider12 = new wxSlider(this, ID_SLIDER12, 0, 0, 255, wxPoint(568,296), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER12"));
    Slider13 = new wxSlider(this, ID_SLIDER13, 0, 0, 255, wxPoint(568,336), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER13"));
    Slider14 = new wxSlider(this, ID_SLIDER14, 0, 0, 255, wxPoint(568,376), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER14"));
    Slider15 = new wxSlider(this, ID_SLIDER15, 0, 0, 255, wxPoint(568,416), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER15"));
    Slider16 = new wxSlider(this, ID_SLIDER16, 0, 0, 255, wxPoint(568,456), wxSize(216,24), 0, wxDefaultValidator, _T("ID_SLIDER16"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Channel 1"), wxPoint(32,288), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Channel 4"), wxPoint(32,408), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Channel 3"), wxPoint(32,368), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Channel 2"), wxPoint(32,328), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Label"), wxPoint(392,288), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Label"), wxPoint(392,328), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Label"), wxPoint(392,368), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Label"), wxPoint(392,408), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Status:"), wxPoint(32,20), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_STATICTEXT9"));
    wxFont StaticText9Font(9,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText9->SetFont(StaticText9Font);
    StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Label"), wxPoint(80,20), wxSize(210,17), wxTAB_TRAVERSAL, _T("ID_STATICTEXT10"));
    StaticText10->SetForegroundColour(wxColour(0,0,0));
    wxFont StaticText10Font(9,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText10->SetFont(StaticText10Font);
    StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Channel 5"), wxPoint(488,16), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Channel 10"), wxPoint(488,216), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("Channel 11"), wxPoint(488,256), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    StaticText22 = new wxStaticText(this, ID_STATICTEXT22, _("Channel 16"), wxPoint(488,456), wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("Channel 15"), wxPoint(488,416), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("Channel 14"), wxPoint(488,376), wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("Channel 13"), wxPoint(488,336), wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Channel 12"), wxPoint(488,296), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Channel 9"), wxPoint(488,176), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("Channel 8"), wxPoint(488,136), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Channel 7"), wxPoint(488,96), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Channel 6"), wxPoint(488,56), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    StaticText23 = new wxStaticText(this, ID_STATICTEXT23, _("Label"), wxPoint(800,16), wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    StaticText24 = new wxStaticText(this, ID_STATICTEXT24, _("Label"), wxPoint(800,56), wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    StaticText25 = new wxStaticText(this, ID_STATICTEXT25, _("Label"), wxPoint(800,96), wxDefaultSize, 0, _T("ID_STATICTEXT25"));
    StaticText26 = new wxStaticText(this, ID_STATICTEXT26, _("Label"), wxPoint(800,136), wxDefaultSize, 0, _T("ID_STATICTEXT26"));
    StaticText27 = new wxStaticText(this, ID_STATICTEXT27, _("Label"), wxPoint(800,176), wxDefaultSize, 0, _T("ID_STATICTEXT27"));
    StaticText28 = new wxStaticText(this, ID_STATICTEXT28, _("Label"), wxPoint(800,216), wxDefaultSize, 0, _T("ID_STATICTEXT28"));
    StaticText29 = new wxStaticText(this, ID_STATICTEXT29, _("Label"), wxPoint(800,256), wxDefaultSize, 0, _T("ID_STATICTEXT29"));
    StaticText30 = new wxStaticText(this, ID_STATICTEXT30, _("Label"), wxPoint(800,296), wxDefaultSize, 0, _T("ID_STATICTEXT30"));
    StaticText31 = new wxStaticText(this, ID_STATICTEXT31, _("Label"), wxPoint(800,336), wxDefaultSize, 0, _T("ID_STATICTEXT31"));
    StaticText32 = new wxStaticText(this, ID_STATICTEXT32, _("Label"), wxPoint(800,376), wxDefaultSize, 0, _T("ID_STATICTEXT32"));
    StaticText33 = new wxStaticText(this, ID_STATICTEXT33, _("Label"), wxPoint(800,416), wxDefaultSize, 0, _T("ID_STATICTEXT33"));
    StaticText34 = new wxStaticText(this, ID_STATICTEXT34, _("Label"), wxPoint(800,456), wxDefaultSize, 0, _T("ID_STATICTEXT34"));
    StaticText35 = new wxStaticText(this, ID_STATICTEXT35, _("Profile Set:"), wxPoint(32,36), wxSize(96,20), wxTAB_TRAVERSAL, _T("ID_STATICTEXT35"));
    wxFont StaticText35Font(9,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText35->SetFont(StaticText35Font);
    StaticText36 = new wxStaticText(this, ID_STATICTEXT36, _("Label"), wxPoint(100,36), wxSize(184,13), wxTAB_TRAVERSAL, _T("ID_STATICTEXT36"));
    wxFont StaticText36Font(9,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText36->SetFont(StaticText36Font);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem4 = new wxMenuItem(Menu1, ID_MENUITEM2, _("Light Programs"), _("Open up Lightput\'s Light Program Sub-Menu"), wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Options"), _("Change Lightput options"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem5 = new wxMenuItem(Menu2, idMenuHelp, _("Help\tF1"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem5);
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    Timer1.SetOwner(this, ID_TIMER1);

    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&gui10Frame::OnListBox1Select);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton4Click);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton8Click);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton7Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton2Click2);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton6Click);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton1Click2);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton1Click1);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton11Click1);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton3Click);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton12Click2);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&gui10Frame::OnButton5Click);
    Connect(ID_SLIDER1,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider1CmdScroll1);
    Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider1CmdScroll);
    Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider1CmdScroll);
    Connect(ID_SLIDER2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider2CmdScroll);
    Connect(ID_SLIDER2,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider2CmdScroll);
    Connect(ID_SLIDER3,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider3CmdScroll);
    Connect(ID_SLIDER3,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider3CmdScroll);
    Connect(ID_SLIDER4,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider4CmdScroll);
    Connect(ID_SLIDER4,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider4CmdScroll);
    Connect(ID_SLIDER5,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider5CmdScroll);
    Connect(ID_SLIDER5,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider5CmdScroll);
    Connect(ID_SLIDER6,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider6CmdScroll);
    Connect(ID_SLIDER6,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider6CmdScroll);
    Connect(ID_SLIDER7,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider7CmdScroll);
    Connect(ID_SLIDER7,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider7CmdScroll);
    Connect(ID_SLIDER8,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider8CmdScroll);
    Connect(ID_SLIDER8,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider8CmdScroll);
    Connect(ID_SLIDER9,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider9CmdScroll);
    Connect(ID_SLIDER9,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider9CmdScroll);
    Connect(ID_SLIDER10,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider10CmdScroll);
    Connect(ID_SLIDER10,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider10CmdScroll);
    Connect(ID_SLIDER11,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider11CmdScroll);
    Connect(ID_SLIDER11,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider11CmdScroll);
    Connect(ID_SLIDER12,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider12CmdScroll);
    Connect(ID_SLIDER12,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider12CmdScroll);
    Connect(ID_SLIDER13,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider13CmdScroll);
    Connect(ID_SLIDER13,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider13CmdScroll);
    Connect(ID_SLIDER14,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider14CmdScroll);
    Connect(ID_SLIDER14,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider14CmdScroll);
    Connect(ID_SLIDER15,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider15CmdScroll);
    Connect(ID_SLIDER15,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider15CmdScroll);
    Connect(ID_SLIDER16,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&gui10Frame::OnSlider16CmdScroll);
    Connect(ID_SLIDER16,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui10Frame::OnSlider16CmdScroll);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gui10Frame::OnMenuItem4Selected);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gui10Frame::OnMENUITEM1);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gui10Frame::OnQuit);
    Connect(idMenuHelp,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gui10Frame::OnHelp);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gui10Frame::OnAbout);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&gui10Frame::OnTimer1Trigger);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&gui10Frame::OnClose);
    //*)


//initialize stuff



isconnected = false;
isconnectionattempt = true;
isactive = false;
isselectionchange = true;
isloading = true;
isnamevariable = false;
issavefirst = false;
isexporting = false;
isnewblankprofile = false;
issaveonquit = false;
iscancelquit = false;
isfirstruninitialize = true;

is24hmode = false;
isMidiControlmode = false;
isIconize = false;
hasVSXurunonce = false;

VSXuInitialize = true;
MidiInitialize = true;
isExternalInput = false;
//linux startup fix
counttostart = 0;

LightputFrequency = 60;

//calls the function that establishes the needed rs-485 serial connection
//this line loads profile if isloading value is true, which is when the
//program is opened or after loading a new profile file
    //sets the window for default 4-channel mode
    //SetMinSize(wxSize(445,568));
    //SetMaxSize(wxSize(445,568));
    //SetClientSize(wxSize(445,568));
    loadoptions();

    profiledirectory = wxT("./profiles/");
    profilefilename = option_defaultprofile;
    fullpath = profiledirectory + profilefilename;
    dmxmode = option_dmxmode;
    //something to handle transition time here


    //this handles the window size
    if (dmxmode == 4) {
    SetMinSize(wxSize(445,530));
    SetMaxSize(wxSize(445,530));
    SetClientSize(wxSize(445,530));
    Button5->SetLabel(wxT("Switch to 16-Channel DMX Mode"));
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
    } else
    {
    SetMaxSize(wxSize(840,530));
    SetClientSize(wxSize(840,530));
    SetMinSize(wxSize(840,530));
    dmxmode = 16;
    Button5->SetLabel(wxT("Switch to 4-Channel DMX Mode"));
    }

    if (isloading == true){
        DMXconnect();
        loadprofile();
        }

   if (isconnected) {
        Button4->SetLabel(wxT("Stop"));
        DMXSend_initialize();
        }
    else Button4->Enable(true);

    updateprofile();
    updatesliders();
    updateprofileinterval();
    isbeattimecalculationchange = true;

    isprofilemode = true;
    isbs = false;
    isalarm = false;
    istimeractive = false;

    isprofilemode = false;

    Timer1.Start(LightputFrequency,false);

}

void gui10Frame::setoutputchannels(void)
{
   Channel_1 = StartingDMXChannel+1;
   Channel_2 = StartingDMXChannel+2;
   Channel_3 = StartingDMXChannel+3;
   Channel_4 = StartingDMXChannel+4;
   Channel_5 = StartingDMXChannel+5;
   Channel_6 = StartingDMXChannel+6;
   Channel_7 = StartingDMXChannel+7;
   Channel_8 = StartingDMXChannel+8;
   Channel_9 = StartingDMXChannel+9;
   Channel_10 = StartingDMXChannel+10;
   Channel_11 = StartingDMXChannel+11;
   Channel_12 = StartingDMXChannel+12;
   Channel_13 = StartingDMXChannel+13;
   Channel_14 = StartingDMXChannel+14;
   Channel_15 = StartingDMXChannel+15;
   Channel_16 = StartingDMXChannel+16;
}

void gui10Frame::DMXconnect(void)
{


//linux DMX connect code

    DWORD numDevs;

    char *BufPtrs[4];
    char Buf[64];
    char Buf2[64];
    char Buf3[64];
    char Buf4[64];

    BufPtrs[0] = Buf;
    BufPtrs[1] = Buf2;
    BufPtrs[2] = Buf3;
    BufPtrs[3] = Buf4;
    BufPtrs[4] = NULL;

    is_usb_connected2 = false;
    is_usb_connected3 = false;
    is_usb_connected4 = false;


    ftStatus = FT_ListDevices(BufPtrs,&numDevs,FT_LIST_ALL|FT_OPEN_BY_SERIAL_NUMBER);
    //ftStatus2 = FT_ListDevices(0,Buf2,FT_LIST_BY_INDEX|FT_OPEN_BY_DESCRIPTION);


    ftHandle1 = FT_W32_CreateFile(BufPtrs[0],GENERIC_READ|GENERIC_WRITE,0,0,
        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FT_OPEN_BY_SERIAL_NUMBER,0);
   // ftHandle1


    if (ftHandle1 == INVALID_HANDLE_VALUE) {
        //Sets text box color and lebel for message
        StaticText10->SetForegroundColour(wxColour(wxT("RED")));
        StaticText10->SetLabel(wxT("No FTDI RS-485 device connected"));
        isconnected = false;
        return;
    } else {
        StaticText10->SetForegroundColour(wxColour(wxT("RED")));
        StaticText10->SetLabel(wxT("Problem loading libftd2xx"));
    }


    FTDCB ftDCB;
    if (FT_W32_GetCommState(ftHandle1,&ftDCB)) {
        ftDCB.BaudRate = 250000;
        ftDCB.Parity = FT_PARITY_NONE;
        ftDCB.StopBits = FT_STOP_BITS_2;
        ftDCB.ByteSize = FT_BITS_8;
        ftDCB.fOutX = false;
        ftDCB.fInX = false;
        ftDCB.fErrorChar = false;
        ftDCB.fBinary = true;
        ftDCB.fRtsControl = false;
        ftDCB.fAbortOnError = false;

        if (!FT_W32_SetCommState(ftHandle1,&ftDCB)) {
            StaticText10->SetForegroundColour(wxColour(wxT("RED")));
            StaticText10->SetLabel(wxT("Set baud rate error!"));
            isconnected = false;
            return ;
        }

    StaticText10->SetForegroundColour(wxColour(wxT("BLACK")));
    StaticText10->SetLabel(wxT("FTDI RS-485 device connected"));

    FT_W32_PurgeComm(ftHandle1,FT_PURGE_TX | FT_PURGE_RX);

    isconnected = true;
    }

//connection 1 sholuld be open now


    ftHandle2 = FT_W32_CreateFile(BufPtrs[1],GENERIC_READ|GENERIC_WRITE,0,0,
        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FT_OPEN_BY_SERIAL_NUMBER,0);


    if (ftHandle2 == INVALID_HANDLE_VALUE) {
        //is_usb_connected2 = false;
        //return;
    }

    FTDCB ftDCB2;
    if (FT_W32_GetCommState(ftHandle2,&ftDCB2)) {
        ftDCB2.BaudRate = 250000;
        ftDCB2.Parity = FT_PARITY_NONE;
        ftDCB2.StopBits = FT_STOP_BITS_2;
        ftDCB2.ByteSize = FT_BITS_8;
        ftDCB2.fOutX = false;
        ftDCB2.fInX = false;
        ftDCB2.fErrorChar = false;
        ftDCB2.fBinary = true;
        ftDCB2.fRtsControl = false;
        ftDCB2.fAbortOnError = false;

        if (!FT_W32_SetCommState(ftHandle2,&ftDCB2)) {;
            is_usb_connected2 = false;
            return ;
        }

        FT_W32_PurgeComm(ftHandle2,FT_PURGE_TX | FT_PURGE_RX);

        is_usb_connected2 = true;

        StaticText10->SetForegroundColour(wxColour(wxT("BLACK")));
        StaticText10->SetLabel(wxT("2 FTDI RS-485 devices connected"));

    }//connection 2 is open at this point

    ftHandle3 = FT_W32_CreateFile(BufPtrs[2],GENERIC_READ|GENERIC_WRITE,0,0,
        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FT_OPEN_BY_SERIAL_NUMBER,0);

    if (ftHandle3 == INVALID_HANDLE_VALUE) {
        is_usb_connected3 = false;
        return;
    }

    FTDCB ftDCB3;
    if (FT_W32_GetCommState(ftHandle3,&ftDCB3)) {
        ftDCB2.BaudRate = 250000;
        ftDCB2.Parity = FT_PARITY_NONE;
        ftDCB2.StopBits = FT_STOP_BITS_2;
        ftDCB2.ByteSize = FT_BITS_8;
        ftDCB2.fOutX = false;
        ftDCB2.fInX = false;
        ftDCB2.fErrorChar = false;
        ftDCB2.fBinary = true;
        ftDCB2.fRtsControl = false;
        ftDCB2.fAbortOnError = false;

        if (!FT_W32_SetCommState(ftHandle3,&ftDCB3)) {;
            is_usb_connected2 = false;
            return ;
        }


        FT_W32_PurgeComm(ftHandle3,FT_PURGE_TX | FT_PURGE_RX);

        is_usb_connected3 = true;

        StaticText10->SetForegroundColour(wxColour(wxT("BLACK")));
        StaticText10->SetLabel(wxT("3 FTDI RS-485 devices connected"));
    }//connection 3 is open at this point

    ftHandle4 = FT_W32_CreateFile(BufPtrs[3],GENERIC_READ|GENERIC_WRITE,0,0,
        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FT_OPEN_BY_SERIAL_NUMBER,0);

    if (ftHandle4 == INVALID_HANDLE_VALUE) {
        is_usb_connected4 = false;
        return;
    }

    FTDCB ftDCB4;
    if (FT_W32_GetCommState(ftHandle4,&ftDCB4)) {
        ftDCB2.BaudRate = 250000;
        ftDCB2.Parity = FT_PARITY_NONE;
        ftDCB2.StopBits = FT_STOP_BITS_2;
        ftDCB2.ByteSize = FT_BITS_8;
        ftDCB2.fOutX = false;
        ftDCB2.fInX = false;
        ftDCB2.fErrorChar = false;
        ftDCB2.fBinary = true;
        ftDCB2.fRtsControl = false;
        ftDCB2.fAbortOnError = false;

        if (!FT_W32_SetCommState(ftHandle4,&ftDCB)) {;
            is_usb_connected4 = false;
            return ;
        }


        FT_W32_PurgeComm(ftHandle4,FT_PURGE_TX | FT_PURGE_RX);

        is_usb_connected4 = true;

        StaticText10->SetForegroundColour(wxColour(wxT("BLACK")));
        StaticText10->SetLabel(wxT("4 FTDI RS-485 devices connected"));

    //connection 4 is open at this point
    }


/*Windows DMX connect code

char Buf[64];

    is_usb_connected2 = false;
    is_usb_connected3 = false;
    is_usb_connected4 = false;

    ftStatus = FT_ListDevices(0,Buf,FT_LIST_BY_INDEX|FT_OPEN_BY_DESCRIPTION);

    ftHandle1 = FT_W32_CreateFile(Buf,GENERIC_READ|GENERIC_WRITE,0,0,
        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FT_OPEN_BY_DESCRIPTION,0);


    if (ftHandle1 == INVALID_HANDLE_VALUE) {
        //Sets text box color and lebel for message
        StaticText10->SetForegroundColour(wxColour(wxT("RED")));
        StaticText10->SetLabel(wxT("No FTDI RS-485 device connected"));
        isconnected = false;
        return;
    } else {
        StaticText10->SetForegroundColour(wxColour(wxT("RED")));
        StaticText10->SetLabel(wxT("Problem loading libftd2xx"));
    }


    FTDCB ftDCB;
    if (FT_W32_GetCommState(ftHandle1,&ftDCB)) {
        ftDCB.BaudRate = 250000;
        ftDCB.Parity = FT_PARITY_NONE;
        ftDCB.StopBits = FT_STOP_BITS_2;
        ftDCB.ByteSize = FT_BITS_8;
        ftDCB.fOutX = false;
        ftDCB.fInX = false;
        ftDCB.fErrorChar = false;
        ftDCB.fBinary = true;
        ftDCB.fRtsControl = false;
        ftDCB.fAbortOnError = false;

        if (!FT_W32_SetCommState(ftHandle1,&ftDCB)) {
            StaticText10->SetForegroundColour(wxColour(wxT("RED")));
            StaticText10->SetLabel(wxT("Set baud rate error!"));
            isconnected = false;
            return ;
        }
    }
    StaticText10->SetForegroundColour(wxColour(wxT("BLACK")));
    StaticText10->SetLabel(wxT("FTDI RS-485 device connected"));

    FT_W32_PurgeComm(ftHandle1,FT_PURGE_TX | FT_PURGE_RX);

    isconnected = true;

//connection 1 sholuld be open now

    ftHandle2 = FT_W32_CreateFile(Buf,GENERIC_READ|GENERIC_WRITE,0,0,
        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FT_OPEN_BY_DESCRIPTION,0);

    if (ftHandle2 == INVALID_HANDLE_VALUE) {
        is_usb_connected2 = false;
        return;
    }

    FTDCB ftDCB2;
    if (FT_W32_GetCommState(ftHandle2,&ftDCB2)) {
        ftDCB2.BaudRate = 250000;
        ftDCB2.Parity = FT_PARITY_NONE;
        ftDCB2.StopBits = FT_STOP_BITS_2;
        ftDCB2.ByteSize = FT_BITS_8;
        ftDCB2.fOutX = false;
        ftDCB2.fInX = false;
        ftDCB2.fErrorChar = false;
        ftDCB2.fBinary = true;
        ftDCB2.fRtsControl = false;
        ftDCB2.fAbortOnError = false;

        if (!FT_W32_SetCommState(ftHandle2,&ftDCB2)) {;
            is_usb_connected2 = false;
            return ;
        }

        FT_W32_PurgeComm(ftHandle2,FT_PURGE_TX | FT_PURGE_RX);

        is_usb_connected2 = true;

        StaticText10->SetForegroundColour(wxColour(wxT("BLACK")));
        StaticText10->SetLabel(wxT("2 FTDI RS-485 devices connected"));

    }//connection 2 is open at this point

    ftHandle3 = FT_W32_CreateFile(Buf,GENERIC_READ|GENERIC_WRITE,0,0,
        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FT_OPEN_BY_DESCRIPTION,0);

    if (ftHandle3 == INVALID_HANDLE_VALUE) {
        is_usb_connected3 = false;
        return;
    }

    FTDCB ftDCB3;
    if (FT_W32_GetCommState(ftHandle3,&ftDCB3)) {
        ftDCB2.BaudRate = 250000;
        ftDCB2.Parity = FT_PARITY_NONE;
        ftDCB2.StopBits = FT_STOP_BITS_2;
        ftDCB2.ByteSize = FT_BITS_8;
        ftDCB2.fOutX = false;
        ftDCB2.fInX = false;
        ftDCB2.fErrorChar = false;
        ftDCB2.fBinary = true;
        ftDCB2.fRtsControl = false;
        ftDCB2.fAbortOnError = false;

        if (!FT_W32_SetCommState(ftHandle3,&ftDCB3)) {;
            is_usb_connected2 = false;
            return ;
        }


        FT_W32_PurgeComm(ftHandle3,FT_PURGE_TX | FT_PURGE_RX);

        is_usb_connected3 = true;

        StaticText10->SetForegroundColour(wxColour(wxT("BLACK")));
        StaticText10->SetLabel(wxT("3 FTDI RS-485 devices connected"));
    }//connection 3 is open at this point

    ftHandle4 = FT_W32_CreateFile(Buf,GENERIC_READ|GENERIC_WRITE,0,0,
        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FT_OPEN_BY_DESCRIPTION,0);

    if (ftHandle4 == INVALID_HANDLE_VALUE) {
        is_usb_connected4 = false;
        return;
    }

    FTDCB ftDCB4;
    if (FT_W32_GetCommState(ftHandle4,&ftDCB4)) {
        ftDCB2.BaudRate = 250000;
        ftDCB2.Parity = FT_PARITY_NONE;
        ftDCB2.StopBits = FT_STOP_BITS_2;
        ftDCB2.ByteSize = FT_BITS_8;
        ftDCB2.fOutX = false;
        ftDCB2.fInX = false;
        ftDCB2.fErrorChar = false;
        ftDCB2.fBinary = true;
        ftDCB2.fRtsControl = false;
        ftDCB2.fAbortOnError = false;

        if (!FT_W32_SetCommState(ftHandle4,&ftDCB)) {;
            is_usb_connected4 = false;
            return ;
        }


        FT_W32_PurgeComm(ftHandle4,FT_PURGE_TX | FT_PURGE_RX);

        is_usb_connected4 = true;

        StaticText10->SetForegroundColour(wxColour(wxT("BLACK")));
        StaticText10->SetLabel(wxT("4 FTDI RS-485 devices connected"));

    //connection 4 is open at this point
    }
*/

}



void gui10Frame::DMXSend_initialize(void)
{

        dmx_sender_thread = new FTDI_interface();
        //FTDI_interface dmx_sender_thread;
        dmx_sender_thread->ftHandle = ftHandle1;
        dmx_sender_thread->StartCode = 0;

       if (is_usb_connected2) {
            dmx_sender_thread2 = new FTDI_interface();
            dmx_sender_thread2->ftHandle = ftHandle2;
            dmx_sender_thread2->StartCode = 0;
            if (is_usb_connected3) {
                dmx_sender_thread3 = new FTDI_interface();
                dmx_sender_thread3->ftHandle = ftHandle3;
                dmx_sender_thread3->StartCode = 0;
                }
                if (is_usb_connected4) {
                dmx_sender_thread4 = new FTDI_interface();
                dmx_sender_thread4->ftHandle = ftHandle4;
                dmx_sender_thread4->StartCode = 0;
                }
        }
/*
        dmx_sender_thread->DMXSend();

        if (is_usb_connected2) {
            dmx_sender_thread2->DMXSend();
            if (is_usb_connected3) {
                dmx_sender_thread3->DMXSend();
                if (is_usb_connected4) dmx_sender_thread4->DMXSend();

            }
        }
*/


}



gui10Frame::~gui10Frame()
{
    //(*Destroy(gui10Frame)
    //*)
}

void gui10Frame::loadoptions(void)
{
wxTextFile ofile;
//this line actually opens the file options.lightput
ofile.Open(directory + wxT("options.lightput"), wxConvISO8859_1);
int count;
wxString buffer;

int optioncheck = ofile.GetLineCount();
if (optioncheck > 0) {
    //first line is determnes if the profile screen is in 4 or 16 channel mode
    buffer = ofile.GetFirstLine();
    option_dmxmode = wxAtoi(buffer);
    //next line in the options file holds the name of the default profile set
    option_defaultprofile = ofile.GetNextLine();
    //next line in the options file holds the profile transiton time
    buffer = ofile.GetNextLine();
    option_profiletime = wxAtoi(buffer);
    //next line in the options file holds the light sequencer smooth transtition value
    buffer = ofile.GetNextLine();
    issmooth = wxAtoi(buffer);
    //next line in the options file holds the light sequencer smooth start value
    buffer = ofile.GetNextLine();
    issmoothstart = wxAtoi(buffer);
    //next line in the options file holds the default dmx channel setting
    buffer = ofile.GetNextLine();
    StartingDMXChannel = wxAtoi(buffer);

    //next line is for DMC copy or not
    buffer = ofile.GetNextLine();
    isDMXcascade = wxAtoi(buffer);

    //next line is for Light script option start on 1
    buffer = ofile.GetNextLine();
    islsStartOn1 = wxAtoi(buffer);

    //next line is for Light script option repeat
    buffer = ofile.GetNextLine();
    islsRepeat = wxAtoi(buffer);

    //next line is for Lightput frequency
    buffer = ofile.GetNextLine();
    LightputFrequency = wxAtoi(buffer);

    //next line is for the minimize on startup option
    //buffer = ofile.GetNextLine();
    //isminimizedonstartup = wxAtoi(buffer);

    //next line is for the run Light program at startup option
    //buffer = ofile.GetNextLine();
    //runlightprogramonstartup = wxAtoi(buffer);
    //islightprogramonstartup = wxAtoi(buffer);

    //next line is for Light progrqam selection
    //buffer = ofile.GetNextLine();
    //startuplightprogram = wxAtoi(buffer);


    //if (issmooth) wxMessageBox(wxT("issmooth is true"),wxT("issmooth is true"));
     //wxMessageBox(buffer,buffer);

    //dont forget to remove this
    //StartingDMXChannel=0;
    }
else{
    option_dmxmode = 4;
    option_defaultprofile = wxT("profiles.lightput");
    option_profiletime = 1;
    issmooth = 1;
    issmoothstart = 1;
    StartingDMXChannel = 0;
    isDMXcascade = 0;
    }

}

//sets the correct profile transition time for the DMX engine
void gui10Frame::updateprofileinterval(void)
{
    if (option_profiletime == 0) beattime = 60;
    if (option_profiletime == 1) beattime = 1000;
    if (option_profiletime == 2) beattime = 2000;
    if (option_profiletime == 3) beattime = 3000;
    if (option_profiletime == 4) beattime = 4000;
    if (option_profiletime == 5) beattime = 5000;
    if (option_profiletime == 6) beattime = 6000;
    if (option_profiletime == 7) beattime = 7000;
    if (option_profiletime == 8) beattime = 8000;
    if (option_profiletime == 9) beattime = 9000;
    if (option_profiletime == 10) beattime = 10000;
}

void gui10Frame::loadprofile(void)
{

//wxString fullpath;
// this value is used to count the different values in the saved
// profile file, there are 5, thwe first is the name, the other 4
// are integer values 0-127
int currentvalue = 0;
//this value holds the current profile (each profile a new line in
//saved file) for data processing purposes
int profilecount = 0;
//opens a new instance of the class wxTextFile, called pfile
wxTextFile pfile;
//sets a wxChar to hold the comma to search for (used to be a comma)
wxChar comma = wxT('!');
wxChar atsymbol = wxT('@');

//this line actually opens the file profiles.lightput
pfile.Open(fullpath, wxConvISO8859_1);
//this line gets the number of lines in the loaded file using
//the GetLineCount function and puts it into the value
//numberofprofiles for data processing purposes (loading the
//values correctly from profiles.Lightput)
numberofprofiles = pfile.GetLineCount();

//these lines initialize variables for the code that will search and extract
//saved lightput values form the file profiles.lightput
int pos;
int vpos;
int count;
//the first value being the name and of variable length needs special code
//the other values are all three characters seperated by a comma, so
//they are simpler to process, check out the if else isnamevariable == true lines below
isnamevariable = true;
//this wxCharBuffer object is needed for the data extraction because the searching functions
//rely on it in stead of the wxstring value because the wxCharBuffer can be accessed as
//an array, although that might be true for wxstrings too
//changed to wxstring becasue it works and wxcharbuffer doesn't compile in linux i386

//This Vaalue has to be a wxCharBuffer in Linux 64-bit builds. a wxString in linux 32-bit builds
//and it works as either in good ol forgiving windows
//wxCharBuffer buffer;

wxString buffer;

ListBox1->Clear();
do {
    //I initially tried to use another do loop for this code, but the GetNextLine function was
    //not working propperly that way, this basically advances the current line these loops are working with
    //until the end of the file is reached
    for ( Value [profilecount] = pfile.GetFirstLine(); !pfile.Eof(); Value [profilecount] = pfile.GetNextLine())
    {
        tempValue [profilecount] = Value [profilecount];

        buffer = Value [profilecount];
        //buffer = Value [profilecount].ToAscii();

        do {    //this do loop puts an entire line of the file profiles.lightput into wxString "Value"
                //and int "v1"-"v4" array designations based on the profilecount variable

                if (isnamevariable == true)
                {
                    count = 0;
                    pos = Value[profilecount].Find(comma,false);
                //the other values are of a set length of characters, so the code for the rest
                //of the values on the line is simple, add 4 to the value of pos and 1 to the
                //value of count to skip the comma and the loop will grap the propper 3
                //characters to convert to an integer value
                }else pos = pos + 4;

                //clears the wxString "Value" variable
                tempValue [profilecount] = wxT("");
                //"while the character number marking end of the search is greater than the current character number"
                while (pos > count)
                {
                    //this line puts the string value in "Value" together character by character as the loop continues
                    tempValue [profilecount] = tempValue [profilecount] + buffer[count];
                    count++;
                //wxMessageBox(tempValue [profilecount], wxT("test"));
                }

                //more special code to handle that first name value in the profile format, this puts the
                //name of the profile in the listbox in the right spot based on the profilecount variable
                if (isnamevariable == true) {
                    ListBox1->SetSelection(ListBox1->Append(tempValue [profilecount]) );
                     Value [profilecount] = tempValue [profilecount];
                    //since this is the last bit of special code to handle that first name value in the
                    //saved profile.lightput format, this next line tells the program the rest of the
                    //values loaded form that line of profiles.lightput are not variable length names.
                    isnamevariable = false;
                }
                else
                {
                    //converts wxstring "tempValue" to int value
                    int num;
                    num = wxAtoi(tempValue [profilecount]);
                    //places int value into arrays
                    if (currentvalue == 1) v1 [profilecount] = num;
                    if (currentvalue == 2) v2 [profilecount] = num;
                    if (currentvalue == 3) v3 [profilecount] = num;
                    if (currentvalue == 4) v4 [profilecount] = num;
                    if (currentvalue == 5) v5 [profilecount] = num;
                    if (currentvalue == 6) v6 [profilecount] = num;
                    if (currentvalue == 7) v7 [profilecount] = num;
                    if (currentvalue == 8) v8 [profilecount] = num;
                    if (currentvalue == 9) v9 [profilecount] = num;
                    if (currentvalue == 10) v10 [profilecount] = num;
                    if (currentvalue == 11) v11 [profilecount] = num;
                    if (currentvalue == 12) v12 [profilecount] = num;
                    if (currentvalue == 13) v13 [profilecount] = num;
                    if (currentvalue == 14) v14 [profilecount] = num;
                    if (currentvalue == 15) v15 [profilecount] = num;
                    if (currentvalue == 16) v16 [profilecount] = num;


                }
                //move the line character counter past the comma
                count++;
                //move the value counter so the program knows where to place data
                currentvalue++;
            } while (currentvalue < 17); //numberofvalues[profilecount]);
            //reset the current value and isname variable for the next line loaded from
            //profiles.lightput
            currentvalue = 0;
            isnamevariable = true;
            //increment the profilecount value so the do loop knows when the last profile
            //has been loaded and ends.
            profilecount++;
            count = 0;
    }// this bracket closes the for loop

    //when profilecount++ makes profilecount bigger than numberofprofiles, which
    //is the number of total lines in the loaded file (each line is a profile) it knows
    //theres no more to load and the while condition is met
} while (numberofprofiles > profilecount);

//Sets the selection of listbox1 to the first, default value
ListBox1->Select(0);
currentprofile = 0;
//chnges isloading to false so the main window function doesnt keep loading (calling loadprofiles)
isloading = false;
//this line updates the current profile file label i the top left
StaticText36->SetLabel(profilefilename);

ischanged = false;
}


void gui10Frame::updateprofile(void)
{
 //this code block updates the profiles

    wxString displayValue;
//    profileselection = ListBox1->GetSelection();

    //channel 1 value
    displayValue = wxString::Format(wxT("%i"),v1 [currentprofile]);
    //draws loaded value
    StaticText5->SetLabel(displayValue);
    //sets slider to loaded value
    Slider1->SetValue(v1 [currentprofile]);
    //sets DMX value holder


     //channel 2 value
    displayValue = wxString::Format(wxT("%i"),v2 [currentprofile]);
    //draws loaded value
    StaticText6->SetLabel(displayValue);
    //sets slider to loaded value
    Slider2->SetValue(v2 [currentprofile]);

    //channel 3 value
    displayValue = wxString::Format(wxT("%i"),v3 [currentprofile]);
    //draws loaded value
    StaticText7->SetLabel(displayValue);
    //sets slider to loaded value
    Slider3->SetValue(v3 [currentprofile]);

    //channel 4 value
    displayValue = wxString::Format(wxT("%i"),v4 [currentprofile]);
    //draws loaded value
    StaticText8->SetLabel(displayValue);
    //sets slider to loaded value
    Slider4->SetValue(v4 [currentprofile]);
    //Channel 5
    displayValue = wxString::Format(wxT("%i"),v5 [currentprofile]);
    StaticText23->SetLabel(displayValue);
    Slider5->SetValue(v5 [currentprofile]);
    //Channel 6
    displayValue = wxString::Format(wxT("%i"),v6 [currentprofile]);
    StaticText24->SetLabel(displayValue);
    Slider6->SetValue(v6 [currentprofile]);
    //Channel 7
    displayValue = wxString::Format(wxT("%i"),v7 [currentprofile]);
    StaticText25->SetLabel(displayValue);
    Slider7->SetValue(v7 [currentprofile]);
    //Channel 5
    displayValue = wxString::Format(wxT("%i"),v8 [currentprofile]);
    StaticText26->SetLabel(displayValue);
    Slider8->SetValue(v8 [currentprofile]);
    //Channel 9
    displayValue = wxString::Format(wxT("%i"),v9 [currentprofile]);
    StaticText27->SetLabel(displayValue);
    Slider9->SetValue(v9 [currentprofile]);
    //Channel 10
    displayValue = wxString::Format(wxT("%i"),v10 [currentprofile]);
    StaticText28->SetLabel(displayValue);
    Slider10->SetValue(v10 [currentprofile]);
    //Channel 11
    displayValue = wxString::Format(wxT("%i"),v11 [currentprofile]);
    StaticText29->SetLabel(displayValue);
    Slider11->SetValue(v11 [currentprofile]);
    //Channel 12
    displayValue = wxString::Format(wxT("%i"),v12 [currentprofile]);
    StaticText30->SetLabel(displayValue);
    Slider12->SetValue(v12 [currentprofile]);
    //Channel 13
    displayValue = wxString::Format(wxT("%i"),v13 [currentprofile]);
    StaticText31->SetLabel(displayValue);
    Slider13->SetValue(v13 [currentprofile]);
    //Channel 14
    displayValue = wxString::Format(wxT("%i"),v14 [currentprofile]);
    StaticText32->SetLabel(displayValue);
    Slider14->SetValue(v14 [currentprofile]);
    //Channel 15
    displayValue = wxString::Format(wxT("%i"),v15 [currentprofile]);
    StaticText33->SetLabel(displayValue);
    Slider15->SetValue(v15 [currentprofile]);
    //Channel 16
    displayValue = wxString::Format(wxT("%i"),v16 [currentprofile]);
    StaticText34->SetLabel(displayValue);
    Slider16->SetValue(v16 [currentprofile]);

}



void gui10Frame::OnQuit(wxCommandEvent& event)
{
    //you should probably get rid of this function
    Close();

}

void gui10Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxT("Lightput 1.0 \nBy Michael Johnston \n \nVSXu Audio Visualizer\n© 2003-2013 Vovoid Media Technologies AB, Sweden");
    wxMessageBox(msg, _("About Lightput"));
}

void gui10Frame::OnMENUITEM1 (wxCommandEvent& event)
{
    Options Dlg(0);
    Dlg.ShowModal();
    loadoptions();
    setoutputchannels();
    updateprofileinterval();
    isbeattimecalculationchange = true;
}


void gui10Frame::OnButton1Click(wxCommandEvent& event)
{

}

void gui10Frame::OnButton2Click(wxCommandEvent& event)
{
}

//import export button
void gui10Frame::OnButton3Click(wxCommandEvent& event)
{
//this condition checks if the save before import dialog  should come up
if (ischanged == true){
    isloading = false;
    SaveFirst sDlg(0);
    //issavefirst = false;
    sDlg.ShowModal();
    }
    //this condition goes to the save dialog if the save option was selected from
    //the save before import dialog
if (issavefirst == true) {
    //profilefilename = "test.lighput";
    OnButton1Click2(event);
    //issavefirst = false;
    //ischanged = false;
    issavefirst = false;
    return;
    }

    //this brings up the actual import export window
    NewDialog Dlg(0);
    Dlg.ShowModal();

    //this conditions checks if an export is being done
    if (isexporting == true) {
        StaticText36->SetLabel(profilefilename);
        saveprofile();
        isexporting = false;
        return;
    //this conditon checks if a new profile was selected to be imported
    } else if (isloading == true){
        loadprofile();
        updateprofile();
        updatesliders();
        isloading = false;
        profilefilename = nameofexport;
        StaticText36->SetLabel(profilefilename);
        ischanged = false;
        return;
    }

    if (isnewblankprofile == true) {
        ListBox1->Clear();
        numberofprofiles = 1;
        currentprofile = 0;
        Value[currentprofile] = wxT("Default");
        v1[currentprofile] = 0;
        v2[currentprofile] = 0;
        v3[currentprofile] = 0;
        v4[currentprofile] = 0;
        v5[currentprofile] = 0;
        v6[currentprofile] = 0;
        v7[currentprofile] = 0;
        v8[currentprofile] = 0;
        v9[currentprofile] = 0;
        v10[currentprofile] = 0;
        v11[currentprofile] = 0;
        v12[currentprofile] = 0;
        v13[currentprofile] = 0;
        v14[currentprofile] = 0;
        v15[currentprofile] = 0;
        v16[currentprofile] = 0;
        isnewblankprofile = false;
        updateprofile();
        updatesliders();
        profilefilename = nameofnewprofile;
        StaticText36->SetLabel(profilefilename);
        ListBox1->Append(Value[currentprofile]);
    }


}

//the connect button
//the connect button becomes a stop / Start button until restart
void gui10Frame::OnButton4Click(wxCommandEvent& event)
{

    if (!isconnected) {
        DMXconnect();
        if (isconnected) DMXSend_initialize();
    }
    if (isconnected){
        if (Timer1.IsRunning() == false){
            Button4->SetLabel(wxT("Stop"));
            Timer1.Start(LightputFrequency,false);
            }
        else {
            Button4->SetLabel(wxT("Start"));
            Timer1.Stop();
        }
    }
}

//this button is the Add new profile button
void gui10Frame::OnButton1Click1(wxCommandEvent& event)
{
    if (numberofprofiles == 64){
        wxMessageBox (wxT("This Profile Set is already at the maximum amount of profiles currently available by Lightput, please create a new profile set to store more profiles."),wxT("Too Many Profiles"));
        return;
    }


    //this code grants access to variables in another file using a classs instance of
    //AddNewProfile, Dlg
    AddNewProfile Dlg(0);
    //opens dialog
    Dlg.ShowModal();
    //gets value from externel file using class instaNCE
    newprofileValue = Dlg.TextCtrl1->GetValue();
    if ((newprofileValue != wxT("!"))&& (yesorno)) {
        ListBox1->SetSelection(ListBox1->Append(newprofileValue));
        numberofprofiles++;
        v1 [numberofprofiles] = 0;
        v2 [numberofprofiles] = 0;
        v3 [numberofprofiles] = 0;
        v4 [numberofprofiles] = 0;
        v5 [numberofprofiles] = 0;
        v6 [numberofprofiles] = 0;
        v7 [numberofprofiles] = 0;
        v8 [numberofprofiles] = 0;
        v9 [numberofprofiles] = 0;
        v10 [numberofprofiles] = 0;
        v11 [numberofprofiles] = 0;
        v12 [numberofprofiles] = 0;
        v13 [numberofprofiles] = 0;
        v14 [numberofprofiles] = 0;
        v15 [numberofprofiles] = 0;
        v16 [numberofprofiles] = 0;
        //numberofprofiles++;
        currentprofile = ListBox1->GetSelection();
        Value [currentprofile] = newprofileValue;
        ischanged = true;
        updatesliders();
        yesorno = false;
    }

}

void gui10Frame::updatesliders (void)
{
    Slider1->SetValue(v1[currentprofile]);
    Slider2->SetValue(v2[currentprofile]);
    Slider3->SetValue(v3[currentprofile]);
    Slider4->SetValue(v4[currentprofile]);
    Slider5->SetValue(v5[currentprofile]);
    Slider6->SetValue(v6[currentprofile]);
    Slider7->SetValue(v7[currentprofile]);
    Slider8->SetValue(v8[currentprofile]);
    Slider9->SetValue(v9[currentprofile]);
    Slider10->SetValue(v10[currentprofile]);
    Slider11->SetValue(v11[currentprofile]);
    Slider12->SetValue(v12[currentprofile]);
    Slider13->SetValue(v13[currentprofile]);
    Slider14->SetValue(v14[currentprofile]);
    Slider15->SetValue(v15[currentprofile]);
    Slider16->SetValue(v16[currentprofile]);

    s1v = Slider1->GetValue();
    s1value = wxString::Format(wxT("%i"),s1v);
    StaticText5->SetLabel(s1value);
    s2v = Slider2->GetValue();
    s2value = wxString::Format(wxT("%i"),s2v);
    StaticText6->SetLabel(s2value);
    s3v = Slider3->GetValue();
    s3value = wxString::Format(wxT("%i"),s3v);
    StaticText7->SetLabel(s3value);

    s4v = Slider4->GetValue();
    s4value = wxString::Format(wxT("%i"),s4v);
    StaticText8->SetLabel(s4value);

    s5v = Slider5->GetValue();
    wxString s5value = wxString::Format(wxT("%i"),s5v);
    StaticText23->SetLabel(s5value);

    s6v = Slider6->GetValue();
    wxString s6value = wxString::Format(wxT("%i"),s6v);
    StaticText24->SetLabel(s6value);

    s7v = Slider7->GetValue();
    wxString s7value = wxString::Format(wxT("%i"),s7v);
    StaticText25->SetLabel(s7value);

    s8v = Slider8->GetValue();
    wxString s8value = wxString::Format(wxT("%i"),s8v);
    StaticText26->SetLabel(s8value);

    s9v = Slider9->GetValue();
    wxString s9value = wxString::Format(wxT("%i"),s9v);
    StaticText27->SetLabel(s9value);

    s10v = Slider10->GetValue();
    wxString s10value = wxString::Format(wxT("%i"),s10v);
    StaticText28->SetLabel(s10value);

    s11v = Slider11->GetValue();
    wxString s11value = wxString::Format(wxT("%i"),s11v);
    StaticText29->SetLabel(s11value);

    s12v = Slider12->GetValue();
    wxString s12value = wxString::Format(wxT("%i"),s12v);
    StaticText30->SetLabel(s12value);

    s13v = Slider13->GetValue();
    wxString s13value = wxString::Format(wxT("%i"),s13v);
    StaticText31->SetLabel(s13value);

    s14v = Slider14->GetValue();
    wxString s14value = wxString::Format(wxT("%i"),s14v);
    StaticText32->SetLabel(s14value);

    s15v = Slider15->GetValue();
    wxString s15value = wxString::Format(wxT("%i"),s15v);
    StaticText33->SetLabel(s15value);

    s16v = Slider16->GetValue();
    wxString s16value = wxString::Format(wxT("%i"),s16v);
    StaticText34->SetLabel(s16value);

}

void gui10Frame::OnSlider1CmdScroll1(wxScrollEvent& event)
{
//oy, how do i get rid of this in wxwidgets so it stops coming back
}


void gui10Frame::OnSlider1CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    //currentprofile = ListBox1->GetSelection();
    //gets value from slider
    s1v = Slider1->GetValue();
    //updates system variable for this value
    v1 [currentprofile] = s1v;
    Channel_1_out = s1v;
    Channel_1_new = s1v;
    Channel_1_added = s1v;
    //converts int to wxstring
    s1value = wxString::Format(wxT("%i"),s1v);
    //draws updated value
    StaticText5->SetLabel(s1value);
}

void gui10Frame::OnSlider2CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    //gets value from slider
    s2v = Slider2->GetValue();
    //updates system variable for this value
    v2 [currentprofile] = s2v;
    Channel_2_out = s2v;
    Channel_2_new = s2v;
    Channel_2_added = s2v;
    //converts int to wxstring
    s2value = wxString::Format(wxT("%i"),s2v);
    //draws updated value
    StaticText6->SetLabel(s2value);
}

void gui10Frame::OnSlider3CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    //gets value from slider
    s3v = Slider3->GetValue();
    //updates system variable for this value
    v3 [currentprofile] = s3v;
    Channel_3_out = s3v;
    Channel_3_new = s3v;
    Channel_3_added = s3v;
    //converts int to wxstring
    s3value = wxString::Format(wxT("%i"),s3v);
    //draws updated value
    StaticText7->SetLabel(s3value);
}

void gui10Frame::OnSlider4CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    //gets value from slider
    s4v = Slider4->GetValue();
    //updates system variable for this value
    v4 [currentprofile] = s4v;
    //stops the slider from fading (and causing issues)
    Channel_4_out = s4v;
    Channel_4_new = s4v;
    Channel_4_added = s4v;
    //converts int to wxstring
    s4value = wxString::Format(wxT("%i"),s4v);
    //draws updated value
    StaticText8->SetLabel(s4value);
}

void gui10Frame::OnSlider5CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s5v = Slider5->GetValue();
    v5 [currentprofile] = s5v;
    Channel_5_out = s5v;
    Channel_5_new = s5v;
    Channel_5_added = s5v;
    wxString s5value = wxString::Format(wxT("%i"),s5v);
    StaticText23->SetLabel(s5value);
}


void gui10Frame::OnSlider6CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s6v = Slider6->GetValue();
    v6 [currentprofile] = s6v;
    Channel_6_out = s6v;
    Channel_6_new = s6v;
    Channel_6_added = s6v;
    wxString s6value = wxString::Format(wxT("%i"),s6v);
    StaticText24->SetLabel(s6value);
}


void gui10Frame::OnSlider7CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s7v = Slider7->GetValue();
    v7 [currentprofile] = s7v;
    Channel_7_out = s7v;
    Channel_7_new = s7v;
    Channel_7_added = s7v;
    wxString s7value = wxString::Format(wxT("%i"),s7v);
    StaticText25->SetLabel(s7value);
}

void gui10Frame::OnSlider8CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s8v = Slider8->GetValue();
    v8 [currentprofile] = s8v;
    Channel_8_out = s8v;
    Channel_8_new = s8v;
    Channel_8_added = s8v;
    wxString s8value = wxString::Format(wxT("%i"),s8v);
    StaticText26->SetLabel(s8value);
}

void gui10Frame::OnSlider9CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s9v = Slider9->GetValue();
    v9 [currentprofile] = s9v;
    Channel_9_out = s9v;
    Channel_9_new = s9v;
    Channel_9_added = s9v;
    wxString s9value = wxString::Format(wxT("%i"),s9v);
    StaticText27->SetLabel(s9value);
}

void gui10Frame::OnSlider10CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s10v = Slider10->GetValue();
    v10 [currentprofile] = s10v;
    Channel_10_out = s10v;
    Channel_10_new = s10v;
    Channel_10_added = s10v;
    wxString s10value = wxString::Format(wxT("%i"),s10v);
    StaticText28->SetLabel(s10value);
}

void gui10Frame::OnSlider11CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s11v = Slider11->GetValue();
    v11 [currentprofile] = s11v;
    Channel_11_out = s11v;
    Channel_11_new = s11v;
    Channel_11_added = s11v;
    wxString s11value = wxString::Format(wxT("%i"),s11v);
    StaticText29->SetLabel(s11value);
}

void gui10Frame::OnSlider12CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s12v = Slider12->GetValue();
    v12 [currentprofile] = s12v;
    Channel_12_out = s12v;
    Channel_12_new = s12v;
    Channel_12_added = s12v;
    wxString s12value = wxString::Format(wxT("%i"),s12v);
    StaticText30->SetLabel(s12value);
}

void gui10Frame::OnSlider13CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s13v = Slider13->GetValue();
    v13 [currentprofile] = s13v;
    Channel_13_out = s13v;
    Channel_13_new = s13v;
    Channel_13_added = s13v;
    wxString s13value = wxString::Format(wxT("%i"),s13v);
    StaticText31->SetLabel(s13value);
}

void gui10Frame::OnSlider14CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s14v = Slider14->GetValue();
    v14 [currentprofile] = s14v;
    Channel_14_out = s14v;
    Channel_14_new = s14v;
    Channel_14_added = s14v;
    wxString s14value = wxString::Format(wxT("%i"),s14v);
    StaticText32->SetLabel(s14value);
}

void gui10Frame::OnSlider15CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s15v = Slider15->GetValue();
    v15 [currentprofile] = s15v;
    Channel_15_out = s15v;
    Channel_15_new = s15v;
    Channel_15_added = s15v;
    wxString s15value = wxString::Format(wxT("%i"),s15v);
    StaticText33->SetLabel(s15value);
}

void gui10Frame::OnSlider16CmdScroll(wxScrollEvent& event)
{
    ischanged = true;
    s16v = Slider16->GetValue();
    v16 [currentprofile] = s16v;
    Channel_16_new = s16v;
    Channel_16_out = s16v;
    Channel_16_added = s16v;
    wxString s16value = wxString::Format(wxT("%i"),s16v);
    StaticText34->SetLabel(s16value);
}

void gui10Frame::OnChoice2Select(wxCommandEvent& event)
{
}

//this handles clicking on list box
void gui10Frame::OnListBox1Select(wxCommandEvent& event)
{
currentprofile = ListBox1->GetSelection();
updateprofile();
updatesliders();
calculateincrements();





}

void gui10Frame::OnButton11Click(wxCommandEvent& event)
{

}



//this is the delete profiles button
void gui10Frame::OnButton6Click(wxCommandEvent& event)
{

    if (ListBox1->GetSelection() != -1){
    //this code grants access to variables in another file using a classs instance of
    //DeleteVerify, Dlg
    currentprofile = ListBox1->GetSelection();
    DeleteVerify Dlg(0);
    //opens dialog
    Dlg.ShowModal();
        if (yesorno == true){
            ischanged = true;


            //this form loop confuses me, but it basically moves every value
            //below the current and being deleted value up one spot in the arrays
            //holding he values
            for (int profilemove = currentprofile ; profilemove < numberofprofiles; profilemove++)
                {
                    Value [profilemove] = Value [profilemove+1];
                    v1 [profilemove] = v1 [profilemove+1];
                    v2 [profilemove] = v2 [profilemove+1];
                    v3 [profilemove] = v3 [profilemove+1];
                    v4 [profilemove] = v4 [profilemove+1];
                    v5 [profilemove] = v5 [profilemove+1];
                    v6 [profilemove] = v6 [profilemove+1];
                    v7 [profilemove] = v7 [profilemove+1];
                    v8 [profilemove] = v8 [profilemove+1];
                    v9 [profilemove] = v9 [profilemove+1];
                    v10 [profilemove] = v10 [profilemove+1];
                    v11 [profilemove] = v11 [profilemove+1];
                    v12 [profilemove] = v12 [profilemove+1];
                    v13 [profilemove] = v13 [profilemove+1];
                    v14 [profilemove] = v14 [profilemove+1];
                    v15 [profilemove] = v15 [profilemove+1];
                    v16 [profilemove] = v16 [profilemove+1];


        }//closes the for

        //the folowing code handles the listbox selection

        //this int has to be here because the listbox delete function also deletes the value "currentprofile" in Linux builds!!
        int holderforvaluethatinadverdentlygetsdeleted = currentprofile;

        ListBox1->Delete(currentprofile);

        //puts the currentvalue value back from holder
        currentprofile = holderforvaluethatinadverdentlygetsdeleted;

        //the else is for if the listbox selection is the last one, it knows to move the selection up
        if (currentprofile < numberofprofiles-1)ListBox1->SetSelection(currentprofile);
        else ListBox1->SetSelection(--currentprofile);
        numberofprofiles--;


        updateprofile();
        updatesliders();

        if (/*(currentprofile == -1)&&*/(numberofprofiles == 0)) {
            Value [0] = wxT("Blank Profile");
            v1 [0] = 0;
            v2 [0] = 0;
            v3 [0] = 0;
            v4 [0] = 0;
            v5 [0] = 0;
            v6 [0] = 0;
            v7 [0] = 0;
            v8 [0] = 0;
            v9 [0] = 0;
            v10 [0] = 0;
            v11 [0] = 0;
            v12 [0] = 0;
            v13 [0] = 0;
            v14 [0] = 0;
            v15 [0] = 0;
            v16 [0] = 0;
            currentprofile = 0;

            updateprofile();
            updatesliders();
        }


        //this condition catches when you delete the last value on the listbox and the selection leaves
        //the listbox and causes problems
       // else {}



    }//closes inner if

}//closes the if
else wxMessageBox(wxT("Select a profile to delete first."), _("Error"));
}




void gui10Frame::OnButton2Click1(wxCommandEvent& event)
{



}
//this function resizes the dialog and sets the profiles for 4 and 16 channel modes
void gui10Frame::OnButton5Click(wxCommandEvent& event)
{
    if (dmxmode == 4) {
    dmxmode = 16;
    SetMaxSize(wxSize(840,530));
    SetClientSize(wxSize(840,530));
    SetMinSize(wxSize(840,530));
    Button5->SetLabel(wxT("Switch to 4-Channel DMX Mode"));

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

    }
    else {
    dmxmode = 4;
    SetMinSize(wxSize(445,530));
    SetMaxSize(wxSize(445,530));
    SetClientSize(wxSize(445,530));
    Button5->SetLabel(wxT("Switch to 16-Channel DMX Mode"));

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
    }
}

void gui10Frame::OnClose(wxCloseEvent& event)
{
    if (ischanged) {
            SaveOnQuit Dlg(0);
            Dlg.ShowModal();
            if (iscancelquit) return;
            //else {Timer1.Stop(); Destroy();}
    }
    // this else is for if isschanged != true, no saves to change
    else {
        Timer1.Stop();
        //delete gui10Frame::SingleInstanceChecker1;
        //~gui10Frame::SingleInstanceChecker1;
        //VSXuAudioVisualizer::vsxu_renderer->Destroy();

        Destroy();
         }
    //this is for if user selected to save on quit
    if (issaveonquit) {


        //save code pasted in

        wxString newfile [numberofprofiles];
        wxTextFile spfile(profiledirectory + profilefilename);
        wxChar padding = wxT('0');
        //create / holds place for a text file and is used to check if it
        //already exists with exists function
        //spfile.Exists(profiledirectory + profilefilename);
        //wxMessageBox (profilefilename, profilefilename);
        //spfile.Create(fullpath);
        int count = 0;
        //sets a wxChar to hold the comma to search for (used too be a comma)
        wxChar comma = wxT('!');
        //initialize yesorno value before the overwrite dialog appears (needed for Linix only apparently)
        yesorno = false;
        //this condition checks if the file in question already exists
        if (spfile.Exists()) {
            currentprofile = ListBox1->GetSelection();
            //this code grants access to variables in another file using a classs instance of
            //DeleteVerify, Dlg
            ProfileOverwrite Dlg(0);
            //opens dialog
            Dlg.ShowModal();
            if (yesorno == false) return;
            }
        spfile.Create(profiledirectory + profilefilename);
        wxString v1pad;
        wxString v1padded;
        wxString v2pad;
        wxString v2padded;
        wxString v3pad;
        wxString v3padded;
        wxString v4pad;
        wxString v4padded;
        wxString v5pad;
        wxString v5padded;
        wxString v6pad;
        wxString v6padded;
        wxString v7pad;
        wxString v7padded;
        wxString v8pad;
        wxString v8padded;
        wxString v9pad;
        wxString v9padded;
        wxString v10pad;
        wxString v10padded;
        wxString v11pad;
        wxString v11padded;
        wxString v12pad;
        wxString v12padded;
        wxString v13pad;
        wxString v13padded;
        wxString v14pad;
        wxString v14padded;
        wxString v15pad;
        wxString v15padded;
        wxString v16pad;
        wxString v16padded;

        while (numberofprofiles > count) {


            //this code pads the value with leading zeros for proper data storage
            //makes it easy to load if they all have the same number of characters
            v1pad = wxString::Format(wxT("%i"),v1 [count]);
            v1padded = wxT("00") + v1pad;
            //this line cuts off any characters past three
            v1padded = v1padded.substr( v1padded.length() - 3 );
            //channel 2
            v2pad = wxString::Format(wxT("%i"),v2 [count]);
            v2padded = wxT("00") + v2pad;
            v2padded = v2padded.substr( v2padded.length() - 3 );
            //channel 3
            v3pad = wxString::Format(wxT("%i"),v3 [count]);
            v3padded = wxT("00") + v3pad;
            v3padded = v3padded.substr( v3padded.length() - 3 );
            //channel 4...
            v4pad = wxString::Format(wxT("%i"),v4 [count]);
            v4padded = wxT("00") + v4pad;
            v4padded = v4padded.substr( v4padded.length() - 3 );

            v5pad = wxString::Format(wxT("%i"),v5 [count]);
            v5padded = wxT("00") + v5pad;
            v5padded = v5padded.substr( v5padded.length() - 3 );

            v6pad = wxString::Format(wxT("%i"),v6 [count]);
            v6padded = wxT("00") + v6pad;
            v6padded = v6padded.substr( v6padded.length() - 3 );

            v7pad = wxString::Format(wxT("%i"),v7 [count]);
            v7padded = wxT("00") + v7pad;
            v7padded = v7padded.substr( v7padded.length() - 3 );

            v8pad = wxString::Format(wxT("%i"),v8 [count]);
            v8padded = wxT("00") + v8pad;
            v8padded = v8padded.substr( v8padded.length() - 3 );

            v9pad = wxString::Format(wxT("%i"),v9 [count]);
            v9padded = wxT("00") + v9pad;
            v9padded = v9padded.substr( v9padded.length() - 3 );

            v10pad = wxString::Format(wxT("%i"),v10 [count]);
            v10padded = wxT("00") + v10pad;
            v10padded = v10padded.substr( v10padded.length() - 3 );

            v11pad = wxString::Format(wxT("%i"),v11 [count]);
            v11padded = wxT("00") + v11pad;
            v11padded = v11padded.substr( v11padded.length() - 3 );

            v12pad = wxString::Format(wxT("%i"),v12 [count]);
            v12padded = wxT("00") + v12pad;
            v12padded = v12padded.substr( v12padded.length() - 3 );

            v13pad = wxString::Format(wxT("%i"),v13 [count]);
            v13padded = wxT("00") + v13pad;
            v13padded = v13padded.substr( v13padded.length() - 3 );

            v14pad = wxString::Format(wxT("%i"),v14 [count]);
            v14padded = wxT("00") + v14pad;
            v14padded = v14padded.substr( v14padded.length() - 3 );

            v15pad = wxString::Format(wxT("%i"),v15 [count]);
            v15padded = wxT("00") + v15pad;
            v15padded = v15padded.substr( v15padded.length() - 3 );

            v16pad = wxString::Format(wxT("%i"),v16 [count]);
            v16padded = wxT("00") + v16pad;
            v16padded = v16padded.substr( v16padded.length() - 3 );

            //a line of the saved profile while loop continues until
            //each line of the profile is written
            newfile [count] << Value [count] << comma << v1padded
            << comma << v2padded << comma << v3padded << comma
            << v4padded << comma << v5padded << comma << v6padded
            << comma << v7padded << comma << v8padded << comma << v9padded
            << comma << v10padded << comma << v11padded << comma << v12padded
            << comma << v13padded << comma << v14padded << comma << v15padded
            << comma << v16padded;

            spfile.AddLine(newfile [count], wxTextFileType_Dos);
            count++;
            }
        //these lines save and close the file
        spfile.Write(wxTextFileType_Dos, wxConvISO8859_1);
        spfile.Close();
        ischanged = false;
        Timer1.Stop();
        Destroy();
        }
    //this is for if user selected exit without saving
    else {Timer1.Stop(); Destroy();}
}




//move profile up button
void gui10Frame::OnButton8Click(wxCommandEvent& event)
{
    currentprofile = ListBox1->GetSelection();
    //this if condition makes sure there's somewhere to move the profile to
    if (currentprofile > 0){

    ischanged = true;
    //his value swaps the name values
    tempValue [currentprofile] = Value [currentprofile - 1];
    Value [currentprofile - 1] = Value [currentprofile];
    Value [currentprofile] = tempValue [currentprofile];
    //this code arranges the names in the listbox
    //ListBox1->Delete(ListBox1->GetSelection());
    //ListBox1->Insert(Value[currentprofile-1],currentprofile -1);
    ListBox1->Insert(Value[currentprofile],currentprofile-1);
    ListBox1->Insert(Value[(currentprofile)-1],currentprofile);







    //set selection on listbox so moved profile is selected
    ListBox1->SetSelection(currentprofile);
    //swap Channel 1 data...
    int tempv1 = v1 [currentprofile - 1];
    v1 [currentprofile - 1] = v1 [currentprofile];
    v1 [currentprofile] = tempv1;

    int tempv2 = v2 [currentprofile - 1];
    v2 [currentprofile - 1] = v2 [currentprofile];
    v2 [currentprofile] = tempv2;

    int tempv3 = v3 [currentprofile - 1];
    v3 [currentprofile - 1] = v3 [currentprofile];
    v3 [currentprofile] = tempv3;

    int tempv4 = v4 [currentprofile - 1];
    v4 [currentprofile - 1] = v4 [currentprofile];
    v4 [currentprofile] = tempv4;

    int tempv5 = v5 [currentprofile - 1];
    v5 [currentprofile - 1] = v5 [currentprofile];
    v5 [currentprofile] = tempv5;

    int tempv6 = v6 [currentprofile - 1];
    v6 [currentprofile - 1] = v6 [currentprofile];
    v6 [currentprofile] = tempv6;

    int tempv7 = v7 [currentprofile - 1];
    v7 [currentprofile - 1] = v7 [currentprofile];
    v7 [currentprofile] = tempv7;

    int tempv8 = v8 [currentprofile - 1];
    v8 [currentprofile - 1] = v8 [currentprofile];
    v8 [currentprofile] = tempv8;

    int tempv9 = v9 [currentprofile - 1];
    v9 [currentprofile - 1] = v9 [currentprofile];
    v9 [currentprofile] = tempv9;

    int tempv10 = v10 [currentprofile - 1];
    v10 [currentprofile - 1] = v10 [currentprofile];
    v10 [currentprofile] = tempv10;

    int tempv11 = v11 [currentprofile - 1];
    v11 [currentprofile - 1] = v11 [currentprofile];
    v11 [currentprofile] = tempv11;

    int tempv12 = v12 [currentprofile - 1];
    v12 [currentprofile - 1] = v12 [currentprofile];
    v12 [currentprofile] = tempv12;

    int tempv13 = v13 [currentprofile - 1];
    v13 [currentprofile - 1] = v13 [currentprofile];
    v13 [currentprofile] = tempv13;

    int tempv14 = v14 [currentprofile - 1];
    v14 [currentprofile - 1] = v14 [currentprofile];
    v14 [currentprofile] = tempv14;

    int tempv15 = v15 [currentprofile - 1];
    v15 [currentprofile - 1] = v15 [currentprofile];
    v15 [currentprofile] = tempv15;

    int tempv16 = v16 [currentprofile - 1];
    v16 [currentprofile - 1] = v16 [currentprofile];
    v16 [currentprofile] = tempv16;

//more "listbox->delete" linux bugfix
    int holdervalueforbugfix = currentprofile;

    ListBox1->Delete((currentprofile)-1);

    currentprofile = holdervalueforbugfix;

    ListBox1->Delete((currentprofile) +1);

    currentprofile = holdervalueforbugfix;

    currentprofile--;


    }//end if statement

}

//move profile down button
void gui10Frame::OnButton7Click(wxCommandEvent& event)
{
    currentprofile = ListBox1->GetSelection();
    //this if condition makes sure there's somewhere to move the profile to
    if (currentprofile < numberofprofiles - 1){

    ischanged = true;
    //his value swaps the name values

    tempValue [currentprofile] = Value [currentprofile + 1];
    Value [currentprofile + 1] = Value [currentprofile];
    Value [currentprofile] = tempValue [currentprofile];
    //this code arranges the names in the listbox



            ListBox1->Insert(Value[currentprofile+1],currentprofile);
            ListBox1->Insert(Value[(currentprofile)],(currentprofile)+1);

//more "listbox->delete" linux bugfix
            int holdervalueforbugfix = currentprofile;

            ListBox1->Delete(currentprofile);

            currentprofile = holdervalueforbugfix;

            ListBox1->Delete((currentprofile)+2);

            currentprofile = holdervalueforbugfix;

    //set selection on listbox so moved profile is selected
    ListBox1->SetSelection((currentprofile)+1);
    //swap Channel 1 data...
    int tempv1 = v1 [currentprofile + 1];
    v1 [currentprofile + 1] = v1 [currentprofile];
    v1 [currentprofile] = tempv1;

    int tempv2 = v2 [currentprofile + 1];
    v2 [currentprofile + 1] = v2 [currentprofile];
    v2 [currentprofile] = tempv2;

    int tempv3 = v3 [currentprofile + 1];
    v3 [currentprofile + 1] = v3 [currentprofile];
    v3 [currentprofile] = tempv3;

    int tempv4 = v4 [currentprofile + 1];
    v4 [currentprofile + 1] = v4 [currentprofile];
    v4 [currentprofile] = tempv4;

    int tempv5 = v5 [currentprofile + 1];
    v5 [currentprofile + 1] = v5 [currentprofile];
    v5 [currentprofile] = tempv5;

    int tempv6 = v6 [currentprofile + 1];
    v6 [currentprofile + 1] = v6 [currentprofile];
    v6 [currentprofile] = tempv6;

    int tempv7 = v7 [currentprofile + 1];
    v7 [currentprofile + 1] = v7 [currentprofile];
    v7 [currentprofile] = tempv7;

    int tempv8 = v8 [currentprofile + 1];
    v8 [currentprofile + 1] = v8 [currentprofile];
    v8 [currentprofile] = tempv8;

    int tempv9 = v9 [currentprofile + 1];
    v9 [currentprofile + 1] = v9 [currentprofile];
    v9 [currentprofile] = tempv9;

    int tempv10 = v10 [currentprofile + 1];
    v10 [currentprofile + 1] = v10 [currentprofile];
    v10 [currentprofile] = tempv10;

    int tempv11 = v11 [currentprofile + 1];
    v11 [currentprofile + 1] = v11 [currentprofile];
    v11 [currentprofile] = tempv11;

    int tempv12 = v12 [currentprofile + 1];
    v12 [currentprofile + 1] = v12 [currentprofile];
    v12 [currentprofile] = tempv12;

    int tempv13 = v13 [currentprofile + 1];
    v13 [currentprofile + 1] = v13 [currentprofile];
    v13 [currentprofile] = tempv13;

    int tempv14 = v14 [currentprofile + 1];
    v14 [currentprofile + 1] = v14 [currentprofile];
    v14 [currentprofile] = tempv14;

    int tempv15 = v15 [currentprofile + 1];
    v15 [currentprofile + 1] = v15 [currentprofile];
    v15 [currentprofile] = tempv15;

    int tempv16 = v16 [currentprofile + 1];
    v16 [currentprofile + 1] = v16 [currentprofile];
    v16 [currentprofile] = tempv16;
    currentprofile++;
    }//end if statement
}



//save profile button
void gui10Frame::OnButton1Click2(wxCommandEvent& event)
{
    saveprofile();
}

void gui10Frame::saveprofile(void)

{
    wxString newfile [numberofprofiles];
    wxTextFile spfile(profiledirectory + profilefilename);
    wxChar padding = wxT('0');
    //create / holds place for a text file and is used to check if it
    //already exists with exists function
    //spfile.Exists(profiledirectory + profilefilename);
    //wxMessageBox (profilefilename, profilefilename);
    //spfile.Create(fullpath);
    int count = 0;
    //sets a wxChar to hold the comma to search for (used too be a comma)
    wxChar comma = wxT('!');
    //this condition checks if the file in question already exists
    if ((spfile.Exists())&&(!isexporting)) { //(spfile.GetLineCount() < 0){
        currentprofile = ListBox1->GetSelection();
        //this code grants access to variables in another file using a classs instance of
        //DeleteVerify, Dlg
        ProfileOverwrite Dlg(0);
        //opens dialog
        Dlg.ShowModal();
        if (yesorno == false) return;
        }
    spfile.Create(profiledirectory + profilefilename);
    wxString v1pad;
    wxString v1padded;
    wxString v2pad;
    wxString v2padded;
    wxString v3pad;
    wxString v3padded;
    wxString v4pad;
    wxString v4padded;
    wxString v5pad;
    wxString v5padded;
    wxString v6pad;
    wxString v6padded;
    wxString v7pad;
    wxString v7padded;
    wxString v8pad;
    wxString v8padded;
    wxString v9pad;
    wxString v9padded;
    wxString v10pad;
    wxString v10padded;
    wxString v11pad;
    wxString v11padded;
    wxString v12pad;
    wxString v12padded;
    wxString v13pad;
    wxString v13padded;
    wxString v14pad;
    wxString v14padded;
    wxString v15pad;
    wxString v15padded;
    wxString v16pad;
    wxString v16padded;

    while (numberofprofiles > count) {


        //this code pads the value with leading zeros for proper data storage
        //makes it easy to load if they all have the same number of characters
        v1pad = wxString::Format(wxT("%i"),v1 [count]);
        v1padded = wxT("00") + v1pad;
        //this line cuts off any characters past three
        v1padded = v1padded.substr( v1padded.length() - 3 );
        //channel 2
        v2pad = wxString::Format(wxT("%i"),v2 [count]);
        v2padded = wxT("00") + v2pad;
        v2padded = v2padded.substr( v2padded.length() - 3 );
        //channel 3
        v3pad = wxString::Format(wxT("%i"),v3 [count]);
        v3padded = wxT("00") + v3pad;
        v3padded = v3padded.substr( v3padded.length() - 3 );
        //channel 4...
        v4pad = wxString::Format(wxT("%i"),v4 [count]);
        v4padded = wxT("00") + v4pad;
        v4padded = v4padded.substr( v4padded.length() - 3 );

        v5pad = wxString::Format(wxT("%i"),v5 [count]);
        v5padded = wxT("00") + v5pad;
        v5padded = v5padded.substr( v5padded.length() - 3 );

        v6pad = wxString::Format(wxT("%i"),v6 [count]);
        v6padded = wxT("00") + v6pad;
        v6padded = v6padded.substr( v6padded.length() - 3 );

        v7pad = wxString::Format(wxT("%i"),v7 [count]);
        v7padded = wxT("00") + v7pad;
        v7padded = v7padded.substr( v7padded.length() - 3 );

        v8pad = wxString::Format(wxT("%i"),v8 [count]);
        v8padded = wxT("00") + v8pad;
        v8padded = v8padded.substr( v8padded.length() - 3 );

        v9pad = wxString::Format(wxT("%i"),v9 [count]);
        v9padded = wxT("00") + v9pad;
        v9padded = v9padded.substr( v9padded.length() - 3 );

        v10pad = wxString::Format(wxT("%i"),v10 [count]);
        v10padded = wxT("00") + v10pad;
        v10padded = v10padded.substr( v10padded.length() - 3 );

        v11pad = wxString::Format(wxT("%i"),v11 [count]);
        v11padded = wxT("00") + v11pad;
        v11padded = v11padded.substr( v11padded.length() - 3 );

        v12pad = wxString::Format(wxT("%i"),v12 [count]);
        v12padded = wxT("00") + v12pad;
        v12padded = v12padded.substr( v12padded.length() - 3 );

        v13pad = wxString::Format(wxT("%i"),v13 [count]);
        v13padded = wxT("00") + v13pad;
        v13padded = v13padded.substr( v13padded.length() - 3 );

        v14pad = wxString::Format(wxT("%i"),v14 [count]);
        v14padded = wxT("00") + v14pad;
        v14padded = v14padded.substr( v14padded.length() - 3 );

        v15pad = wxString::Format(wxT("%i"),v15 [count]);
        v15padded = wxT("00") + v15pad;
        v15padded = v15padded.substr( v15padded.length() - 3 );

        v16pad = wxString::Format(wxT("%i"),v16 [count]);
        v16padded = wxT("00") + v16pad;
        v16padded = v16padded.substr( v16padded.length() - 3 );

        //a line of the saved profile while loop continues until
        //each line of the profile is written
       newfile [count] << Value [count] << comma << v1padded
       << comma << v2padded << comma << v3padded << comma
       << v4padded << comma << v5padded << comma << v6padded
       << comma << v7padded << comma << v8padded << comma << v9padded
       << comma << v10padded << comma << v11padded << comma << v12padded
       << comma << v13padded << comma << v14padded << comma << v15padded
       << comma << v16padded;

        spfile.AddLine(newfile [count], wxTextFileType_Dos);
        count++;
        }
    //these lines save and close the file
    spfile.Write(wxTextFileType_Dos, wxConvISO8859_1);
    spfile.Close();
    ischanged = false;
    return;
}


//rename profile button
void gui10Frame::OnButton11Click1(wxCommandEvent& event)
{
    if (ListBox1->GetSelection() != -1){
        currentprofile = ListBox1->GetSelection();
        //this code grants access to variables in another file using a classs instance of
        //DeleteVerify, Dlg
        RenameProfile Dlg(0);
        //opens dialog
        Dlg.ShowModal();
        wxString newname = Dlg.TextCtrl1->GetValue();
        if (yesorno == true) {
            Value[currentprofile] = newname;
            ListBox1->Insert(Value[currentprofile],currentprofile);

            ListBox1->SetSelection(currentprofile);

//more "listbox->delete" linux bugfix
            int holdervalueforbugfix = currentprofile;

            ListBox1->Delete(currentprofile+1);

            currentprofile = holdervalueforbugfix;

            ischanged = true;

        }// closes inner if
        }// closes if
        else wxMessageBox(wxT("Select a profile to rename first."), _("Error"));


}

//light programs button
void gui10Frame::OnButton2Click2(wxCommandEvent& event)
{
    LightProgramStart();

    LightPrograms Dlg(0);
    Dlg.ShowModal();

    LightProgramStop();

    saveoptions();
}

void gui10Frame::RunLightProgramOnStartup(void)
{
/* failed attempt to get this working in linux
        LightProgramStart();

        LightPrograms *LPDlg = new LightPrograms(0);
        LPDlg->Show();

        //LightPrograms Dlg(0);
        //Dlg.Start();

        LightProgramStop();
        //islightprogramonstartup = false;

        saveoptions();
        */
}

void gui10Frame::InitializeLightputEngine(void)
{

            isfirstruninitialize = false;

            setoutputchannels();
            isbs = false;
            isalarm = false;
            istimeractive = false;
            isprofilemode = true;

            updateprofile();
            updatesliders();
            updateprofileinterval();
            calculateincrements();

            //if (isminimizedonstartup&&(!runlightprogramonstartup)) isIconize = true;

}

void gui10Frame::OnTimer1Trigger(wxTimerEvent& event)
//void DMXtimer::Notify()
{

    if (isconnected)
    {
            if (isfirstruninitialize) InitializeLightputEngine();
            if (isbs) {

                  //this is the smooth transition engine
               if (bsChannel_1_out != bsChannel_1_new) {
                    if (bsChannel_1_new > bsChannel_1_out) {
                        bsChannel_1_added = bsChannel_1_added + bsChannel_1_increment;
                        bsChannel_1_out = bsChannel_1_added;
                        if (bsChannel_1_new <= bsChannel_1_out) {bsChannel_1_out = bsChannel_1_new; bsChannel_1_added = bsChannel_1_new; }
                        }
                    if (bsChannel_1_new < bsChannel_1_out) {
                        bsChannel_1_added = bsChannel_1_added - bsChannel_1_increment;
                        bsChannel_1_out = bsChannel_1_added;
                        if (bsChannel_1_out <= bsChannel_1_new) {bsChannel_1_out = bsChannel_1_new; bsChannel_1_added = bsChannel_1_new;}
                        }
                }
               if (bsChannel_2_out != bsChannel_2_new) {
                    if (bsChannel_2_new > bsChannel_2_out) {
                        bsChannel_2_added = bsChannel_2_added + bsChannel_2_increment;
                        bsChannel_2_out = bsChannel_2_added;
                        if (bsChannel_2_new <= bsChannel_2_out) {bsChannel_2_out = bsChannel_2_new; bsChannel_2_added = bsChannel_2_new; }
                        }
                    if (bsChannel_2_new < bsChannel_2_out) {
                        bsChannel_2_added = bsChannel_2_added - bsChannel_2_increment;
                        bsChannel_2_out = bsChannel_2_added;
                        if (bsChannel_2_out <= bsChannel_2_new) {bsChannel_2_out = bsChannel_2_new; bsChannel_2_added = bsChannel_2_new;}
                        }
                }
                if (bsChannel_3_out != bsChannel_3_new) {
                    if (bsChannel_3_new > bsChannel_3_out) {
                        bsChannel_3_added = bsChannel_3_added + bsChannel_3_increment;
                        bsChannel_3_out = bsChannel_3_added;
                        if (bsChannel_3_new <= bsChannel_3_out) {bsChannel_3_out = bsChannel_3_new; bsChannel_3_added = bsChannel_3_new; }
                        }
                    if (bsChannel_3_new < bsChannel_3_out) {
                        bsChannel_3_added = bsChannel_3_added - bsChannel_3_increment;
                        bsChannel_3_out = bsChannel_3_added;
                        if (bsChannel_3_out <= bsChannel_3_new) {bsChannel_3_out = bsChannel_3_new; bsChannel_3_added = bsChannel_3_new;}
                        }
                }
               if (bsChannel_4_out != bsChannel_4_new) {
                    if (bsChannel_4_new > bsChannel_4_out) {
                        bsChannel_4_added = bsChannel_4_added + bsChannel_4_increment;
                        bsChannel_4_out = bsChannel_4_added;
                        if (bsChannel_4_new <= bsChannel_4_out) {bsChannel_4_out = bsChannel_4_new; bsChannel_4_added = bsChannel_4_new; }
                        }
                    if (bsChannel_4_new < bsChannel_4_out) {
                        bsChannel_4_added = bsChannel_4_added - bsChannel_4_increment;
                        bsChannel_4_out = bsChannel_4_added;
                        if (bsChannel_4_out <= bsChannel_4_new) {bsChannel_4_out = bsChannel_4_new; bsChannel_4_added = bsChannel_4_new;}
                        }
                }
               if (bsChannel_5_out != bsChannel_5_new) {
                    if (bsChannel_5_new > bsChannel_5_out) {
                        bsChannel_5_added = bsChannel_5_added + bsChannel_5_increment;
                        bsChannel_5_out = bsChannel_5_added;
                        if (bsChannel_5_new <= bsChannel_5_out) {bsChannel_5_out = bsChannel_5_new; bsChannel_5_added = bsChannel_5_new; }
                        }
                    if (bsChannel_5_new < bsChannel_5_out) {
                        bsChannel_5_added = bsChannel_5_added - bsChannel_5_increment;
                        bsChannel_5_out = bsChannel_5_added;
                        if (bsChannel_5_out <= bsChannel_5_new) {bsChannel_5_out = bsChannel_5_new; bsChannel_5_added = bsChannel_5_new;}
                        }
                }
               if (bsChannel_6_out != bsChannel_6_new) {
                    if (bsChannel_6_new > bsChannel_6_out) {
                        bsChannel_6_added = bsChannel_6_added + bsChannel_6_increment;
                        bsChannel_6_out = bsChannel_6_added;
                        if (bsChannel_6_new <= bsChannel_6_out) {bsChannel_6_out = bsChannel_6_new; bsChannel_6_added = bsChannel_6_new; }
                        }
                    if (bsChannel_6_new < bsChannel_6_out) {
                        bsChannel_6_added = bsChannel_6_added - bsChannel_6_increment;
                        bsChannel_6_out = bsChannel_6_added;
                        if (bsChannel_6_out <= bsChannel_6_new) {bsChannel_6_out = bsChannel_6_new; bsChannel_6_added = bsChannel_6_new;}
                        }
                }
               if (bsChannel_7_out != bsChannel_7_new) {
                    if (bsChannel_7_new > bsChannel_7_out) {
                        bsChannel_7_added = bsChannel_7_added + bsChannel_7_increment;
                        bsChannel_7_out = bsChannel_7_added;
                        if (bsChannel_7_new <= bsChannel_7_out) {bsChannel_7_out = bsChannel_7_new; bsChannel_7_added = bsChannel_7_new; }
                        }
                    if (bsChannel_7_new < bsChannel_7_out) {
                        bsChannel_7_added = bsChannel_7_added - bsChannel_7_increment;
                        bsChannel_7_out = bsChannel_7_added;
                        if (bsChannel_7_out <= bsChannel_7_new) {bsChannel_7_out = bsChannel_7_new; bsChannel_7_added = bsChannel_7_new;}
                        }
                }
               if (bsChannel_8_out != bsChannel_8_new) {
                    if (bsChannel_8_new > bsChannel_8_out) {
                        bsChannel_8_added = bsChannel_8_added + bsChannel_8_increment;
                        bsChannel_8_out = bsChannel_8_added;
                        if (bsChannel_8_new <= bsChannel_8_out) {bsChannel_8_out = bsChannel_8_new; bsChannel_8_added = bsChannel_8_new; }
                        }
                    if (bsChannel_8_new < bsChannel_8_out) {
                        bsChannel_8_added = bsChannel_8_added - bsChannel_8_increment;
                        bsChannel_8_out = bsChannel_8_added;
                        if (bsChannel_8_out <= bsChannel_8_new) {bsChannel_8_out = bsChannel_8_new; bsChannel_8_added = bsChannel_8_new;}
                        }
                }
               if (bsChannel_9_out != bsChannel_9_new) {
                    if (bsChannel_9_new > bsChannel_9_out) {
                        bsChannel_9_added = bsChannel_9_added + bsChannel_9_increment;
                        bsChannel_9_out = bsChannel_9_added;
                        if (bsChannel_9_new <= bsChannel_9_out) {bsChannel_9_out = bsChannel_9_new; bsChannel_9_added = bsChannel_9_new; }
                        }
                    if (bsChannel_9_new < bsChannel_9_out) {
                        bsChannel_9_added = bsChannel_9_added - bsChannel_9_increment;
                        bsChannel_9_out = bsChannel_9_added;
                        if (bsChannel_9_out <= bsChannel_9_new) {bsChannel_9_out = bsChannel_9_new; bsChannel_9_added = bsChannel_9_new;}
                        }
                }
               if (bsChannel_10_out != bsChannel_10_new) {
                    if (bsChannel_10_new > bsChannel_10_out) {
                        bsChannel_10_added = bsChannel_10_added + bsChannel_10_increment;
                        bsChannel_10_out = bsChannel_10_added;
                        if (bsChannel_10_new <= bsChannel_10_out) {bsChannel_10_out = bsChannel_10_new; bsChannel_10_added = bsChannel_10_new; }
                        }
                    if (bsChannel_10_new < bsChannel_10_out) {
                        bsChannel_10_added = bsChannel_10_added - bsChannel_10_increment;
                        bsChannel_10_out = bsChannel_10_added;
                        if (bsChannel_10_out <= bsChannel_10_new) {bsChannel_10_out = bsChannel_10_new; bsChannel_10_added = bsChannel_10_new;}
                        }
                }
               if (bsChannel_11_out != bsChannel_11_new) {
                    if (bsChannel_11_new > bsChannel_11_out) {
                        bsChannel_11_added = bsChannel_11_added + bsChannel_11_increment;
                        bsChannel_11_out = bsChannel_11_added;
                        if (bsChannel_11_new <= bsChannel_11_out) {bsChannel_11_out = bsChannel_11_new; bsChannel_11_added = bsChannel_11_new; }
                        }
                    if (bsChannel_11_new < bsChannel_11_out) {
                        bsChannel_11_added = bsChannel_11_added - bsChannel_11_increment;
                        bsChannel_11_out = bsChannel_11_added;
                        if (bsChannel_11_out <= bsChannel_11_new) {bsChannel_11_out = bsChannel_11_new; bsChannel_11_added = bsChannel_11_new;}
                        }
                }
               if (bsChannel_12_out != bsChannel_12_new) {
                    if (bsChannel_12_new > bsChannel_12_out) {
                        bsChannel_12_added = bsChannel_12_added + bsChannel_12_increment;
                        bsChannel_12_out = bsChannel_12_added;
                        if (bsChannel_12_new <= bsChannel_12_out) {bsChannel_12_out = bsChannel_12_new; bsChannel_12_added = bsChannel_12_new; }
                        }
                    if (bsChannel_12_new < bsChannel_12_out) {
                        bsChannel_12_added = bsChannel_12_added - bsChannel_12_increment;
                        bsChannel_12_out = bsChannel_12_added;
                        if (bsChannel_12_out <= bsChannel_12_new) {bsChannel_12_out = bsChannel_12_new; bsChannel_12_added = bsChannel_12_new;}
                        }
                }
               if (bsChannel_13_out != bsChannel_13_new) {
                    if (bsChannel_13_new > bsChannel_13_out) {
                        bsChannel_13_added = bsChannel_13_added + bsChannel_13_increment;
                        bsChannel_13_out = bsChannel_13_added;
                        if (bsChannel_13_new <= bsChannel_13_out) {bsChannel_13_out = bsChannel_13_new; bsChannel_13_added = bsChannel_13_new; }
                        }
                    if (bsChannel_13_new < bsChannel_13_out) {
                        bsChannel_13_added = bsChannel_13_added - bsChannel_13_increment;
                        bsChannel_13_out = bsChannel_13_added;
                        if (bsChannel_13_out <= bsChannel_13_new) {bsChannel_13_out = bsChannel_13_new; bsChannel_13_added = bsChannel_13_new;}
                        }
                }
               if (bsChannel_14_out != bsChannel_14_new) {
                    if (bsChannel_14_new > bsChannel_14_out) {
                        bsChannel_14_added = bsChannel_14_added + bsChannel_14_increment;
                        bsChannel_14_out = bsChannel_14_added;
                        if (bsChannel_14_new <= bsChannel_14_out) {bsChannel_14_out = bsChannel_14_new; bsChannel_14_added = bsChannel_14_new; }
                        }
                    if (bsChannel_14_new < bsChannel_14_out) {
                        bsChannel_14_added = bsChannel_14_added - bsChannel_14_increment;
                        bsChannel_14_out = bsChannel_14_added;
                        if (bsChannel_14_out <= bsChannel_14_new) {bsChannel_14_out = bsChannel_14_new; bsChannel_14_added = bsChannel_14_new;}
                        }
                }
               if (bsChannel_15_out != bsChannel_15_new) {
                    if (bsChannel_15_new > bsChannel_15_out) {
                        bsChannel_15_added = bsChannel_15_added + bsChannel_15_increment;
                        bsChannel_15_out = bsChannel_15_added;
                        if (bsChannel_15_new <= bsChannel_15_out) {bsChannel_15_out = bsChannel_15_new; bsChannel_15_added = bsChannel_15_new; }
                        }
                    if (bsChannel_15_new < bsChannel_15_out) {
                        bsChannel_15_added = bsChannel_15_added - bsChannel_15_increment;
                        bsChannel_15_out = bsChannel_15_added;
                        if (bsChannel_15_out <= bsChannel_15_new) {bsChannel_15_out = bsChannel_15_new; bsChannel_15_added = bsChannel_15_new;}
                        }
                }
               if (bsChannel_16_out != bsChannel_16_new) {
                    if (bsChannel_16_new > bsChannel_16_out) {
                        bsChannel_16_added = bsChannel_16_added + bsChannel_16_increment;
                        bsChannel_16_out = bsChannel_16_added;
                        if (bsChannel_16_new <= bsChannel_16_out) {bsChannel_16_out = bsChannel_16_new; bsChannel_16_added = bsChannel_16_new; }
                        }
                    if (bsChannel_16_new < bsChannel_16_out) {
                        bsChannel_16_added = bsChannel_16_added - bsChannel_16_increment;
                        bsChannel_16_out = bsChannel_16_added;
                        if (bsChannel_16_out <= bsChannel_16_new) {bsChannel_16_out = bsChannel_16_new; bsChannel_16_added = bsChannel_16_new;}
                        }
                    }

                Channel_1_out = bsChannel_1_out;
                Channel_2_out = bsChannel_2_out;
                Channel_3_out = bsChannel_3_out;
                Channel_4_out = bsChannel_4_out;
                Channel_5_out = bsChannel_5_out;
                Channel_6_out = bsChannel_6_out;
                Channel_7_out = bsChannel_7_out;
                Channel_8_out = bsChannel_8_out;
                Channel_9_out = bsChannel_9_out;
                Channel_10_out = bsChannel_10_out;
                Channel_11_out = bsChannel_11_out;
                Channel_12_out = bsChannel_12_out;
                Channel_13_out = bsChannel_13_out;
                Channel_14_out = bsChannel_14_out;
                Channel_15_out = bsChannel_15_out;
                Channel_16_out = bsChannel_16_out;

                }//close if isbs

                if (isalarm) { //&& !isprofilemode) {

                Channel_1_out = Channel_1_alarm;
                Channel_2_out = Channel_2_alarm;
                Channel_3_out = Channel_3_alarm;
                Channel_4_out = Channel_4_alarm;
                Channel_5_out = Channel_5_alarm;
                Channel_6_out = Channel_6_alarm;
                Channel_7_out = Channel_7_alarm;
                Channel_8_out = Channel_8_alarm;
                Channel_9_out = Channel_9_alarm;
                Channel_10_out = Channel_10_alarm;
                Channel_11_out = Channel_11_alarm;
                Channel_12_out = Channel_12_alarm;
                Channel_13_out = Channel_13_alarm;
                Channel_14_out = Channel_14_alarm;
                Channel_15_out = Channel_15_alarm;
                Channel_16_out = Channel_16_alarm;

                }

                if (istimeractive){ //&& !isprofilemode) {

                Channel_1_out = Channel_1_timer;
                Channel_2_out = Channel_2_timer;
                Channel_3_out = Channel_3_timer;
                Channel_4_out = Channel_4_timer;
                Channel_5_out = Channel_5_timer;
                Channel_6_out = Channel_6_timer;
                Channel_7_out = Channel_7_timer;
                Channel_8_out = Channel_8_timer;
                Channel_9_out = Channel_9_timer;
                Channel_10_out = Channel_10_timer;
                Channel_11_out = Channel_11_timer;
                Channel_12_out = Channel_12_timer;
                Channel_13_out = Channel_13_timer;
                Channel_14_out = Channel_14_timer;
                Channel_15_out = Channel_15_timer;
                Channel_16_out = Channel_16_timer;
                }

        if (isprofilemode) {

                  //this is the smooth transition engine
               if (Channel_1_out != Channel_1_new) {
                    if (Channel_1_new > Channel_1_out) {
                        Channel_1_added = Channel_1_added + Channel_1_increment;
                        Channel_1_out = Channel_1_added;
                        if (Channel_1_new <= Channel_1_out) {Channel_1_out = Channel_1_new; Channel_1_added = Channel_1_new; }
                        }
                    if (Channel_1_new < Channel_1_out) {
                        Channel_1_added = Channel_1_added - Channel_1_increment;
                        Channel_1_out = Channel_1_added;
                        if (Channel_1_out <= Channel_1_new) {Channel_1_out = Channel_1_new; Channel_1_added = Channel_1_new;}
                        }
                }
               if (Channel_2_out != Channel_2_new) {
                    if (Channel_2_new > Channel_2_out) {
                        Channel_2_added = Channel_2_added + Channel_2_increment;
                        Channel_2_out = Channel_2_added;
                        if (Channel_2_new <= Channel_2_out) {Channel_2_out = Channel_2_new; Channel_2_added = Channel_2_new; }
                        }
                    if (Channel_2_new < Channel_2_out) {
                        Channel_2_added = Channel_2_added - Channel_2_increment;
                        Channel_2_out = Channel_2_added;
                        if (Channel_2_out <= Channel_2_new) {Channel_2_out = Channel_2_new; Channel_2_added = Channel_2_new;}
                        }
                }
                if (Channel_3_out != Channel_3_new) {
                    if (Channel_3_new > Channel_3_out) {
                        Channel_3_added = Channel_3_added + Channel_3_increment;
                        Channel_3_out = Channel_3_added;
                        if (Channel_3_new <= Channel_3_out) {Channel_3_out = Channel_3_new; Channel_3_added = Channel_3_new; }
                        }
                    if (Channel_3_new < Channel_3_out) {
                        Channel_3_added = Channel_3_added - Channel_3_increment;
                        Channel_3_out = Channel_3_added;
                        if (Channel_3_out <= Channel_3_new) {Channel_3_out = Channel_3_new; Channel_3_added = Channel_3_new;}
                        }
                }
               if (Channel_4_out != Channel_4_new) {
                    if (Channel_4_new > Channel_4_out) {
                        Channel_4_added = Channel_4_added + Channel_4_increment;
                        Channel_4_out = Channel_4_added;
                        if (Channel_4_new <= Channel_4_out) {Channel_4_out = Channel_4_new; Channel_4_added = Channel_4_new; }
                        }
                    if (Channel_4_new < Channel_4_out) {
                        Channel_4_added = Channel_4_added - Channel_4_increment;
                        Channel_4_out = Channel_4_added;
                        if (Channel_4_out <= Channel_4_new) {Channel_4_out = Channel_4_new; Channel_4_added = Channel_4_new;}
                        }
                }
               if (Channel_5_out != Channel_5_new) {
                    if (Channel_5_new > Channel_5_out) {
                        Channel_5_added = Channel_5_added + Channel_5_increment;
                        Channel_5_out = Channel_5_added;
                        if (Channel_5_new <= Channel_5_out) {Channel_5_out = Channel_5_new; Channel_5_added = Channel_5_new; }
                        }
                    if (Channel_5_new < Channel_5_out) {
                        Channel_5_added = Channel_5_added - Channel_5_increment;
                        Channel_5_out = Channel_5_added;
                        if (Channel_5_out <= Channel_5_new) {Channel_5_out = Channel_5_new; Channel_5_added = Channel_5_new;}
                        }
                }
               if (Channel_6_out != Channel_6_new) {
                    if (Channel_6_new > Channel_6_out) {
                        Channel_6_added = Channel_6_added + Channel_6_increment;
                        Channel_6_out = Channel_6_added;
                        if (Channel_6_new <= Channel_6_out) {Channel_6_out = Channel_6_new; Channel_6_added = Channel_6_new; }
                        }
                    if (Channel_6_new < Channel_6_out) {
                        Channel_6_added = Channel_6_added - Channel_6_increment;
                        Channel_6_out = Channel_6_added;
                        if (Channel_6_out <= Channel_6_new) {Channel_6_out = Channel_6_new; Channel_6_added = Channel_6_new;}
                        }
                }
               if (Channel_7_out != Channel_7_new) {
                    if (Channel_7_new > Channel_7_out) {
                        Channel_7_added = Channel_7_added + Channel_7_increment;
                        Channel_7_out = Channel_7_added;
                        if (Channel_7_new <= Channel_7_out) {Channel_7_out = Channel_7_new; Channel_7_added = Channel_7_new; }
                        }
                    if (Channel_7_new < Channel_7_out) {
                        Channel_7_added = Channel_7_added - Channel_7_increment;
                        Channel_7_out = Channel_7_added;
                        if (Channel_7_out <= Channel_7_new) {Channel_7_out = Channel_7_new; Channel_7_added = Channel_7_new;}
                        }
                }
               if (Channel_8_out != Channel_8_new) {
                    if (Channel_8_new > Channel_8_out) {
                        Channel_8_added = Channel_8_added + Channel_8_increment;
                        Channel_8_out = Channel_8_added;
                        if (Channel_8_new <= Channel_8_out) {Channel_8_out = Channel_8_new; Channel_8_added = Channel_8_new; }
                        }
                    if (Channel_8_new < Channel_8_out) {
                        Channel_8_added = Channel_8_added - Channel_8_increment;
                        Channel_8_out = Channel_8_added;
                        if (Channel_8_out <= Channel_8_new) {Channel_8_out = Channel_8_new; Channel_8_added = Channel_8_new;}
                        }
                }
               if (Channel_9_out != Channel_9_new) {
                    if (Channel_9_new > Channel_9_out) {
                        Channel_9_added = Channel_9_added + Channel_9_increment;
                        Channel_9_out = Channel_9_added;
                        if (Channel_9_new <= Channel_9_out) {Channel_9_out = Channel_9_new; Channel_9_added = Channel_9_new; }
                        }
                    if (Channel_9_new < Channel_9_out) {
                        Channel_9_added = Channel_9_added - Channel_9_increment;
                        Channel_9_out = Channel_9_added;
                        if (Channel_9_out <= Channel_9_new) {Channel_9_out = Channel_9_new; Channel_9_added = Channel_9_new;}
                        }
                }
               if (Channel_10_out != Channel_10_new) {
                    if (Channel_10_new > Channel_10_out) {
                        Channel_10_added = Channel_10_added + Channel_10_increment;
                        Channel_10_out = Channel_10_added;
                        if (Channel_10_new <= Channel_10_out) {Channel_10_out = Channel_10_new; Channel_10_added = Channel_10_new; }
                        }
                    if (Channel_10_new < Channel_10_out) {
                        Channel_10_added = Channel_10_added - Channel_10_increment;
                        Channel_10_out = Channel_10_added;
                        if (Channel_10_out <= Channel_10_new) {Channel_10_out = Channel_10_new; Channel_10_added = Channel_10_new;}
                        }
                }
               if (Channel_11_out != Channel_11_new) {
                    if (Channel_11_new > Channel_11_out) {
                        Channel_11_added = Channel_11_added + Channel_11_increment;
                        Channel_11_out = Channel_11_added;
                        if (Channel_11_new <= Channel_11_out) {Channel_11_out = Channel_11_new; Channel_11_added = Channel_11_new; }
                        }
                    if (Channel_11_new < Channel_11_out) {
                        Channel_11_added = Channel_11_added - Channel_11_increment;
                        Channel_11_out = Channel_11_added;
                        if (Channel_11_out <= Channel_11_new) {Channel_11_out = Channel_11_new; Channel_11_added = Channel_11_new;}
                        }
                }
               if (Channel_12_out != Channel_12_new) {
                    if (Channel_12_new > Channel_12_out) {
                        Channel_12_added = Channel_12_added + Channel_12_increment;
                        Channel_12_out = Channel_12_added;
                        if (Channel_12_new <= Channel_12_out) {Channel_12_out = Channel_12_new; Channel_12_added = Channel_12_new; }
                        }
                    if (Channel_12_new < Channel_12_out) {
                        Channel_12_added = Channel_12_added - Channel_12_increment;
                        Channel_12_out = Channel_12_added;
                        if (Channel_12_out <= Channel_12_new) {Channel_12_out = Channel_12_new; Channel_12_added = Channel_12_new;}
                        }
                }
               if (Channel_13_out != Channel_13_new) {
                    if (Channel_13_new > Channel_13_out) {
                        Channel_13_added = Channel_13_added + Channel_13_increment;
                        Channel_13_out = Channel_13_added;
                        if (Channel_13_new <= Channel_13_out) {Channel_13_out = Channel_13_new; Channel_13_added = Channel_13_new; }
                        }
                    if (Channel_13_new < Channel_13_out) {
                        Channel_13_added = Channel_13_added - Channel_13_increment;
                        Channel_13_out = Channel_13_added;
                        if (Channel_13_out <= Channel_13_new) {Channel_13_out = Channel_13_new; Channel_13_added = Channel_13_new;}
                        }
                }
               if (Channel_14_out != Channel_14_new) {
                    if (Channel_14_new > Channel_14_out) {
                        Channel_14_added = Channel_14_added + Channel_14_increment;
                        Channel_14_out = Channel_14_added;
                        if (Channel_14_new <= Channel_14_out) {Channel_14_out = Channel_14_new; Channel_14_added = Channel_14_new; }
                        }
                    if (Channel_14_new < Channel_14_out) {
                        Channel_14_added = Channel_14_added - Channel_14_increment;
                        Channel_14_out = Channel_14_added;
                        if (Channel_14_out <= Channel_14_new) {Channel_14_out = Channel_14_new; Channel_14_added = Channel_14_new;}
                        }
                }
               if (Channel_15_out != Channel_15_new) {
                    if (Channel_15_new > Channel_15_out) {
                        Channel_15_added = Channel_15_added + Channel_15_increment;
                        Channel_15_out = Channel_15_added;
                        if (Channel_15_new <= Channel_15_out) {Channel_15_out = Channel_15_new; Channel_15_added = Channel_15_new; }
                        }
                    if (Channel_15_new < Channel_15_out) {
                        Channel_15_added = Channel_15_added - Channel_15_increment;
                        Channel_15_out = Channel_15_added;
                        if (Channel_15_out <= Channel_15_new) {Channel_15_out = Channel_15_new; Channel_15_added = Channel_15_new;}
                        }
                }
               if (Channel_16_out != Channel_16_new) {
                    if (Channel_16_new > Channel_16_out) {
                        Channel_16_added = Channel_16_added + Channel_16_increment;
                        Channel_16_out = Channel_16_added;
                        if (Channel_16_new <= Channel_16_out) {Channel_16_out = Channel_16_new; Channel_16_added = Channel_16_new; }
                        }
                    if (Channel_16_new < Channel_16_out) {
                        Channel_16_added = Channel_16_added - Channel_16_increment;
                        Channel_16_out = Channel_16_added;
                        if (Channel_16_out <= Channel_16_new) {Channel_16_out = Channel_16_new; Channel_16_added = Channel_16_new;}
                        }

                    }
                    Channel_1_new = (v1[currentprofile]);
                    Channel_2_new = (v2[currentprofile]);
                    Channel_3_new = (v3[currentprofile]);
                    Channel_4_new = (v4[currentprofile]);
                    Channel_5_new = (v5[currentprofile]);
                    Channel_6_new = (v6[currentprofile]);
                    Channel_7_new = (v7[currentprofile]);
                    Channel_8_new = (v8[currentprofile]);
                    Channel_9_new = (v9[currentprofile]);
                    Channel_10_new = (v10[currentprofile]);
                    Channel_11_new = (v11[currentprofile]);
                    Channel_12_new = (v12[currentprofile]);
                    Channel_13_new = (v13[currentprofile]);
                    Channel_14_new = (v14[currentprofile]);
                    Channel_15_new = (v15[currentprofile]);
                    Channel_16_new = (v16[currentprofile]);

                    ///this generally prevents freaking out
                    calculateincrements();

                }

                if (isVSXumode){

                    Channel_1_out = Channel_1_VSXu;
                    Channel_2_out = Channel_2_VSXu;
                    Channel_3_out = Channel_3_VSXu;
                    Channel_4_out = Channel_4_VSXu;
                    Channel_5_out = Channel_5_VSXu;
                    Channel_6_out = Channel_6_VSXu;
                    Channel_7_out = Channel_7_VSXu;
                    Channel_8_out = Channel_8_VSXu;
                    Channel_9_out = Channel_9_VSXu;
                    Channel_10_out = Channel_10_VSXu;
                    Channel_11_out = Channel_11_VSXu;
                    Channel_12_out = Channel_12_VSXu;
                    Channel_13_out = Channel_13_VSXu;
                    Channel_14_out = Channel_14_VSXu;
                    Channel_15_out = Channel_15_VSXu;
                    Channel_16_out = Channel_16_VSXu;
                }

                if (isMidiControlmode){

                    Channel_1_out = Channel_1_MidiControl;
                    Channel_2_out = Channel_2_MidiControl;
                    Channel_3_out = Channel_3_MidiControl;
                    Channel_4_out = Channel_4_MidiControl;
                    Channel_5_out = Channel_5_MidiControl;
                    Channel_6_out = Channel_6_MidiControl;
                    Channel_7_out = Channel_7_MidiControl;
                    Channel_8_out = Channel_8_MidiControl;
                    Channel_9_out = Channel_9_MidiControl;
                    Channel_10_out = Channel_10_MidiControl;
                    Channel_11_out = Channel_11_MidiControl;
                    Channel_12_out = Channel_12_MidiControl;
                    Channel_13_out = Channel_13_MidiControl;
                    Channel_14_out = Channel_14_MidiControl;
                    Channel_15_out = Channel_15_MidiControl;
                    Channel_16_out = Channel_16_MidiControl;
                }


            if (isLightScripts) {

                  //this is the smooth transition engine
               if (lsChannel_1_out != lsChannel_1_new) {
                    if (lsChannel_1_new > lsChannel_1_out) {
                        lsChannel_1_added = lsChannel_1_added + lsChannel_1_increment;
                        lsChannel_1_out = lsChannel_1_added;
                        if (lsChannel_1_new <= lsChannel_1_out) {lsChannel_1_out = lsChannel_1_new; lsChannel_1_added = lsChannel_1_new; }
                        }
                    if (lsChannel_1_new < lsChannel_1_out) {
                        lsChannel_1_added = lsChannel_1_added - lsChannel_1_increment;
                        lsChannel_1_out = lsChannel_1_added;
                        if (lsChannel_1_out <= lsChannel_1_new) {lsChannel_1_out = lsChannel_1_new; lsChannel_1_added = lsChannel_1_new;}
                        }
                }
               if (lsChannel_2_out != lsChannel_2_new) {
                    if (lsChannel_2_new > lsChannel_2_out) {
                        lsChannel_2_added = lsChannel_2_added + lsChannel_2_increment;
                        lsChannel_2_out = lsChannel_2_added;
                        if (lsChannel_2_new <= lsChannel_2_out) {lsChannel_2_out = lsChannel_2_new; lsChannel_2_added = lsChannel_2_new; }
                        }
                    if (lsChannel_2_new < lsChannel_2_out) {
                        lsChannel_2_added = lsChannel_2_added - lsChannel_2_increment;
                        lsChannel_2_out = lsChannel_2_added;
                        if (lsChannel_2_out <= lsChannel_2_new) {lsChannel_2_out = lsChannel_2_new; lsChannel_2_added = lsChannel_2_new;}
                        }
                }
                if (lsChannel_3_out != lsChannel_3_new) {
                    if (lsChannel_3_new > lsChannel_3_out) {
                        lsChannel_3_added = lsChannel_3_added + lsChannel_3_increment;
                        lsChannel_3_out = lsChannel_3_added;
                        if (lsChannel_3_new <= lsChannel_3_out) {lsChannel_3_out = lsChannel_3_new; lsChannel_3_added = lsChannel_3_new; }
                        }
                    if (lsChannel_3_new < lsChannel_3_out) {
                        lsChannel_3_added = lsChannel_3_added - lsChannel_3_increment;
                        lsChannel_3_out = lsChannel_3_added;
                        if (lsChannel_3_out <= lsChannel_3_new) {lsChannel_3_out = lsChannel_3_new; lsChannel_3_added = lsChannel_3_new;}
                        }
                }
               if (lsChannel_4_out != lsChannel_4_new) {
                    if (lsChannel_4_new > lsChannel_4_out) {
                        lsChannel_4_added = lsChannel_4_added + lsChannel_4_increment;
                        lsChannel_4_out = lsChannel_4_added;
                        if (lsChannel_4_new <= lsChannel_4_out) {lsChannel_4_out = lsChannel_4_new; lsChannel_4_added = lsChannel_4_new; }
                        }
                    if (lsChannel_4_new < lsChannel_4_out) {
                        lsChannel_4_added = lsChannel_4_added - lsChannel_4_increment;
                        lsChannel_4_out = lsChannel_4_added;
                        if (lsChannel_4_out <= lsChannel_4_new) {lsChannel_4_out = lsChannel_4_new; lsChannel_4_added = lsChannel_4_new;}
                        }
                }
               if (lsChannel_5_out != lsChannel_5_new) {
                    if (lsChannel_5_new > lsChannel_5_out) {
                        lsChannel_5_added = lsChannel_5_added + lsChannel_5_increment;
                        lsChannel_5_out = lsChannel_5_added;
                        if (lsChannel_5_new <= lsChannel_5_out) {lsChannel_5_out = lsChannel_5_new; lsChannel_5_added = lsChannel_5_new; }
                        }
                    if (lsChannel_5_new < lsChannel_5_out) {
                        lsChannel_5_added = lsChannel_5_added - lsChannel_5_increment;
                        lsChannel_5_out = lsChannel_5_added;
                        if (lsChannel_5_out <= lsChannel_5_new) {lsChannel_5_out = lsChannel_5_new; lsChannel_5_added = lsChannel_5_new;}
                        }
                }
               if (lsChannel_6_out != lsChannel_6_new) {
                    if (lsChannel_6_new > lsChannel_6_out) {
                        lsChannel_6_added = lsChannel_6_added + lsChannel_6_increment;
                        lsChannel_6_out = lsChannel_6_added;
                        if (lsChannel_6_new <= lsChannel_6_out) {lsChannel_6_out = lsChannel_6_new; lsChannel_6_added = lsChannel_6_new; }
                        }
                    if (lsChannel_6_new < lsChannel_6_out) {
                        lsChannel_6_added = lsChannel_6_added - lsChannel_6_increment;
                        lsChannel_6_out = lsChannel_6_added;
                        if (lsChannel_6_out <= lsChannel_6_new) {lsChannel_6_out = lsChannel_6_new; lsChannel_6_added = lsChannel_6_new;}
                        }
                }
               if (lsChannel_7_out != lsChannel_7_new) {
                    if (lsChannel_7_new > lsChannel_7_out) {
                        lsChannel_7_added = lsChannel_7_added + lsChannel_7_increment;
                        lsChannel_7_out = lsChannel_7_added;
                        if (lsChannel_7_new <= lsChannel_7_out) {lsChannel_7_out = lsChannel_7_new; lsChannel_7_added = lsChannel_7_new; }
                        }
                    if (lsChannel_7_new < lsChannel_7_out) {
                        lsChannel_7_added = lsChannel_7_added - lsChannel_7_increment;
                        lsChannel_7_out = lsChannel_7_added;
                        if (lsChannel_7_out <= lsChannel_7_new) {lsChannel_7_out = lsChannel_7_new; lsChannel_7_added = lsChannel_7_new;}
                        }
                }
               if (lsChannel_8_out != lsChannel_8_new) {
                    if (lsChannel_8_new > lsChannel_8_out) {
                        lsChannel_8_added = lsChannel_8_added + lsChannel_8_increment;
                        lsChannel_8_out = lsChannel_8_added;
                        if (lsChannel_8_new <= lsChannel_8_out) {lsChannel_8_out = lsChannel_8_new; lsChannel_8_added = lsChannel_8_new; }
                        }
                    if (lsChannel_8_new < lsChannel_8_out) {
                        lsChannel_8_added = lsChannel_8_added - lsChannel_8_increment;
                        lsChannel_8_out = lsChannel_8_added;
                        if (lsChannel_8_out <= lsChannel_8_new) {lsChannel_8_out = lsChannel_8_new; lsChannel_8_added = lsChannel_8_new;}
                        }
                }
               if (lsChannel_9_out != lsChannel_9_new) {
                    if (lsChannel_9_new > lsChannel_9_out) {
                        lsChannel_9_added = lsChannel_9_added + lsChannel_9_increment;
                        lsChannel_9_out = lsChannel_9_added;
                        if (lsChannel_9_new <= lsChannel_9_out) {lsChannel_9_out = lsChannel_9_new; lsChannel_9_added = lsChannel_9_new; }
                        }
                    if (lsChannel_9_new < lsChannel_9_out) {
                        lsChannel_9_added = lsChannel_9_added - lsChannel_9_increment;
                        lsChannel_9_out = lsChannel_9_added;
                        if (lsChannel_9_out <= lsChannel_9_new) {lsChannel_9_out = lsChannel_9_new; lsChannel_9_added = lsChannel_9_new;}
                        }
                }
               if (lsChannel_10_out != lsChannel_10_new) {
                    if (lsChannel_10_new > lsChannel_10_out) {
                        lsChannel_10_added = lsChannel_10_added + lsChannel_10_increment;
                        lsChannel_10_out = lsChannel_10_added;
                        if (lsChannel_10_new <= lsChannel_10_out) {lsChannel_10_out = lsChannel_10_new; lsChannel_10_added = lsChannel_10_new; }
                        }
                    if (lsChannel_10_new < lsChannel_10_out) {
                        lsChannel_10_added = lsChannel_10_added - lsChannel_10_increment;
                        lsChannel_10_out = lsChannel_10_added;
                        if (lsChannel_10_out <= lsChannel_10_new) {lsChannel_10_out = lsChannel_10_new; lsChannel_10_added = lsChannel_10_new;}
                        }
                }
               if (lsChannel_11_out != lsChannel_11_new) {
                    if (lsChannel_11_new > lsChannel_11_out) {
                        lsChannel_11_added = lsChannel_11_added + lsChannel_11_increment;
                        lsChannel_11_out = lsChannel_11_added;
                        if (lsChannel_11_new <= lsChannel_11_out) {lsChannel_11_out = lsChannel_11_new; lsChannel_11_added = lsChannel_11_new; }
                        }
                    if (lsChannel_11_new < lsChannel_11_out) {
                        lsChannel_11_added = lsChannel_11_added - lsChannel_11_increment;
                        lsChannel_11_out = lsChannel_11_added;
                        if (lsChannel_11_out <= lsChannel_11_new) {lsChannel_11_out = lsChannel_11_new; lsChannel_11_added = lsChannel_11_new;}
                        }
                }
               if (lsChannel_12_out != lsChannel_12_new) {
                    if (lsChannel_12_new > lsChannel_12_out) {
                        lsChannel_12_added = lsChannel_12_added + lsChannel_12_increment;
                        lsChannel_12_out = lsChannel_12_added;
                        if (lsChannel_12_new <= lsChannel_12_out) {lsChannel_12_out = lsChannel_12_new; lsChannel_12_added = lsChannel_12_new; }
                        }
                    if (lsChannel_12_new < lsChannel_12_out) {
                        lsChannel_12_added = lsChannel_12_added - lsChannel_12_increment;
                        lsChannel_12_out = lsChannel_12_added;
                        if (lsChannel_12_out <= lsChannel_12_new) {lsChannel_12_out = lsChannel_12_new; lsChannel_12_added = lsChannel_12_new;}
                        }
                }
               if (lsChannel_13_out != lsChannel_13_new) {
                    if (lsChannel_13_new > lsChannel_13_out) {
                        lsChannel_13_added = lsChannel_13_added + lsChannel_13_increment;
                        lsChannel_13_out = lsChannel_13_added;
                        if (lsChannel_13_new <= lsChannel_13_out) {lsChannel_13_out = lsChannel_13_new; lsChannel_13_added = lsChannel_13_new; }
                        }
                    if (lsChannel_13_new < lsChannel_13_out) {
                        lsChannel_13_added = lsChannel_13_added - lsChannel_13_increment;
                        lsChannel_13_out = lsChannel_13_added;
                        if (lsChannel_13_out <= lsChannel_13_new) {lsChannel_13_out = lsChannel_13_new; lsChannel_13_added = lsChannel_13_new;}
                        }
                }
               if (lsChannel_14_out != lsChannel_14_new) {
                    if (lsChannel_14_new > lsChannel_14_out) {
                        lsChannel_14_added = lsChannel_14_added + lsChannel_14_increment;
                        lsChannel_14_out = lsChannel_14_added;
                        if (lsChannel_14_new <= lsChannel_14_out) {lsChannel_14_out = lsChannel_14_new; lsChannel_14_added = lsChannel_14_new; }
                        }
                    if (lsChannel_14_new < lsChannel_14_out) {
                        lsChannel_14_added = lsChannel_14_added - lsChannel_14_increment;
                        lsChannel_14_out = lsChannel_14_added;
                        if (lsChannel_14_out <= lsChannel_14_new) {lsChannel_14_out = lsChannel_14_new; lsChannel_14_added = lsChannel_14_new;}
                        }
                }
               if (lsChannel_15_out != lsChannel_15_new) {
                    if (lsChannel_15_new > lsChannel_15_out) {
                        lsChannel_15_added = lsChannel_15_added + lsChannel_15_increment;
                        lsChannel_15_out = lsChannel_15_added;
                        if (lsChannel_15_new <= lsChannel_15_out) {lsChannel_15_out = lsChannel_15_new; lsChannel_15_added = lsChannel_15_new; }
                        }
                    if (lsChannel_15_new < lsChannel_15_out) {
                        lsChannel_15_added = lsChannel_15_added - lsChannel_15_increment;
                        lsChannel_15_out = lsChannel_15_added;
                        if (lsChannel_15_out <= lsChannel_15_new) {lsChannel_15_out = lsChannel_15_new; lsChannel_15_added = lsChannel_15_new;}
                        }
                }
               if (lsChannel_16_out != lsChannel_16_new) {
                    if (lsChannel_16_new > lsChannel_16_out) {
                        lsChannel_16_added = lsChannel_16_added + lsChannel_16_increment;
                        lsChannel_16_out = lsChannel_16_added;
                        if (lsChannel_16_new <= lsChannel_16_out) {lsChannel_16_out = lsChannel_16_new; lsChannel_16_added = lsChannel_16_new; }
                        }
                    if (lsChannel_16_new < lsChannel_16_out) {
                        lsChannel_16_added = lsChannel_16_added - lsChannel_16_increment;
                        lsChannel_16_out = lsChannel_16_added;
                        if (lsChannel_16_out <= lsChannel_16_new) {lsChannel_16_out = lsChannel_16_new; lsChannel_16_added = lsChannel_16_new;}
                        }
                    }

                Channel_1_out = lsChannel_1_out;
                Channel_2_out = lsChannel_2_out;
                Channel_3_out = lsChannel_3_out;
                Channel_4_out = lsChannel_4_out;
                Channel_5_out = lsChannel_5_out;
                Channel_6_out = lsChannel_6_out;
                Channel_7_out = lsChannel_7_out;
                Channel_8_out = lsChannel_8_out;
                Channel_9_out = lsChannel_9_out;
                Channel_10_out = lsChannel_10_out;
                Channel_11_out = lsChannel_11_out;
                Channel_12_out = lsChannel_12_out;
                Channel_13_out = lsChannel_13_out;
                Channel_14_out = lsChannel_14_out;
                Channel_15_out = lsChannel_15_out;
                Channel_16_out = lsChannel_16_out;

                }//close if isLightScripts


                if (isExternalInput){

                    Channel_1_out = Channel_1_ExternalInput;
                    Channel_2_out = Channel_2_ExternalInput;
                    Channel_3_out = Channel_3_ExternalInput;
                    Channel_4_out = Channel_4_ExternalInput;
                    Channel_5_out = Channel_5_ExternalInput;
                    Channel_6_out = Channel_6_ExternalInput;
                    Channel_7_out = Channel_7_ExternalInput;
                    Channel_8_out = Channel_8_ExternalInput;
                    Channel_9_out = Channel_9_ExternalInput;
                    Channel_10_out = Channel_10_ExternalInput;
                    Channel_11_out = Channel_11_ExternalInput;
                    Channel_12_out = Channel_12_ExternalInput;
                    Channel_13_out = Channel_13_ExternalInput;
                    Channel_14_out = Channel_14_ExternalInput;
                    Channel_15_out = Channel_15_ExternalInput;
                    Channel_16_out = Channel_16_ExternalInput;
                }



                //if (isbeattimecalculationchange) {updateprofileinterval(); calculateincrements(); isbeattimecalculationchange = false;}
        //add code to cascade the 16 channels to all 512 channels
                if (!isDMXcascade){

                //this fills in the blank channel data after the Lightput chanels
                    if (StartingDMXChannel < 495) for (blankchannels = 511; blankchannels > (StartingDMXChannel + 16); blankchannels--) {
                            memset(dmx_sender_thread->DMXData, 0,blankchannels);
                        }
                    if ((StartingDMXChannel < 495)&&(is_usb_connected2)) for (blankchannels = 511; blankchannels > (StartingDMXChannel + 16); blankchannels--) {
                            memset(dmx_sender_thread2->DMXData, 0,blankchannels);
                        }
                    if ((StartingDMXChannel < 495)&&(is_usb_connected3)) for (blankchannels = 511; blankchannels > (StartingDMXChannel + 16); blankchannels--) {
                            memset(dmx_sender_thread3->DMXData, 0,blankchannels);
                        }
                    if ((StartingDMXChannel < 495)&&(is_usb_connected4)) for (blankchannels = 511; blankchannels > (StartingDMXChannel + 16); blankchannels--) {
                            memset(dmx_sender_thread4->DMXData, 0,blankchannels);
                        }

                    memset(dmx_sender_thread->DMXData, Channel_16_out,Channel_16);
                    memset(dmx_sender_thread->DMXData, Channel_15_out,Channel_15);
                    memset(dmx_sender_thread->DMXData, Channel_14_out,Channel_14);
                    memset(dmx_sender_thread->DMXData, Channel_13_out,Channel_13);
                    memset(dmx_sender_thread->DMXData, Channel_12_out,Channel_12);
                    memset(dmx_sender_thread->DMXData, Channel_11_out,Channel_11);
                    memset(dmx_sender_thread->DMXData, Channel_10_out,Channel_10);
                    memset(dmx_sender_thread->DMXData, Channel_9_out,Channel_9);
                    memset(dmx_sender_thread->DMXData, Channel_8_out,Channel_8);
                    memset(dmx_sender_thread->DMXData, Channel_7_out,Channel_7);
                    memset(dmx_sender_thread->DMXData, Channel_6_out,Channel_6);
                    memset(dmx_sender_thread->DMXData, Channel_5_out,Channel_5);
                    memset(dmx_sender_thread->DMXData, Channel_4_out,Channel_4);
                    memset(dmx_sender_thread->DMXData, Channel_3_out,Channel_3);
                    memset(dmx_sender_thread->DMXData, Channel_2_out,Channel_2);
                    memset(dmx_sender_thread->DMXData, Channel_1_out,Channel_1);

                    if (is_usb_connected2) {
                        memset(dmx_sender_thread2->DMXData, Channel_16_out,Channel_16);
                        memset(dmx_sender_thread2->DMXData, Channel_15_out,Channel_15);
                        memset(dmx_sender_thread2->DMXData, Channel_14_out,Channel_14);
                        memset(dmx_sender_thread2->DMXData, Channel_13_out,Channel_13);
                        memset(dmx_sender_thread2->DMXData, Channel_12_out,Channel_12);
                        memset(dmx_sender_thread2->DMXData, Channel_11_out,Channel_11);
                        memset(dmx_sender_thread2->DMXData, Channel_10_out,Channel_10);
                        memset(dmx_sender_thread2->DMXData, Channel_9_out,Channel_9);
                        memset(dmx_sender_thread2->DMXData, Channel_8_out,Channel_8);
                        memset(dmx_sender_thread2->DMXData, Channel_7_out,Channel_7);
                        memset(dmx_sender_thread2->DMXData, Channel_6_out,Channel_6);
                        memset(dmx_sender_thread2->DMXData, Channel_5_out,Channel_5);
                        memset(dmx_sender_thread2->DMXData, Channel_4_out,Channel_4);
                        memset(dmx_sender_thread2->DMXData, Channel_3_out,Channel_3);
                        memset(dmx_sender_thread2->DMXData, Channel_2_out,Channel_2);
                        memset(dmx_sender_thread2->DMXData, Channel_1_out,Channel_1);
                    }
                    if (is_usb_connected3) {
                        memset(dmx_sender_thread3->DMXData, Channel_16_out,Channel_16);
                        memset(dmx_sender_thread3->DMXData, Channel_15_out,Channel_15);
                        memset(dmx_sender_thread3->DMXData, Channel_14_out,Channel_14);
                        memset(dmx_sender_thread3->DMXData, Channel_13_out,Channel_13);
                        memset(dmx_sender_thread3->DMXData, Channel_12_out,Channel_12);
                        memset(dmx_sender_thread3->DMXData, Channel_11_out,Channel_11);
                        memset(dmx_sender_thread3->DMXData, Channel_10_out,Channel_10);
                        memset(dmx_sender_thread3->DMXData, Channel_9_out,Channel_9);
                        memset(dmx_sender_thread3->DMXData, Channel_8_out,Channel_8);
                        memset(dmx_sender_thread3->DMXData, Channel_7_out,Channel_7);
                        memset(dmx_sender_thread3->DMXData, Channel_6_out,Channel_6);
                        memset(dmx_sender_thread3->DMXData, Channel_5_out,Channel_5);
                        memset(dmx_sender_thread3->DMXData, Channel_4_out,Channel_4);
                        memset(dmx_sender_thread3->DMXData, Channel_3_out,Channel_3);
                        memset(dmx_sender_thread3->DMXData, Channel_2_out,Channel_2);
                        memset(dmx_sender_thread3->DMXData, Channel_1_out,Channel_1);
                    }
                    if (is_usb_connected4) {
                        memset(dmx_sender_thread4->DMXData, Channel_16_out,Channel_16);
                        memset(dmx_sender_thread4->DMXData, Channel_15_out,Channel_15);
                        memset(dmx_sender_thread4->DMXData, Channel_14_out,Channel_14);
                        memset(dmx_sender_thread4->DMXData, Channel_13_out,Channel_13);
                        memset(dmx_sender_thread4->DMXData, Channel_12_out,Channel_12);
                        memset(dmx_sender_thread4->DMXData, Channel_11_out,Channel_11);
                        memset(dmx_sender_thread4->DMXData, Channel_10_out,Channel_10);
                        memset(dmx_sender_thread4->DMXData, Channel_9_out,Channel_9);
                        memset(dmx_sender_thread4->DMXData, Channel_8_out,Channel_8);
                        memset(dmx_sender_thread4->DMXData, Channel_7_out,Channel_7);
                        memset(dmx_sender_thread4->DMXData, Channel_6_out,Channel_6);
                        memset(dmx_sender_thread4->DMXData, Channel_5_out,Channel_5);
                        memset(dmx_sender_thread4->DMXData, Channel_4_out,Channel_4);
                        memset(dmx_sender_thread4->DMXData, Channel_3_out,Channel_3);
                        memset(dmx_sender_thread4->DMXData, Channel_2_out,Channel_2);
                        memset(dmx_sender_thread4->DMXData, Channel_1_out,Channel_1);
                    }



                    //this fills in the blank channel data if the channel output isnt the deafault
                    if (Channel_1 > 1) for (blankchannels = Channel_1-1; blankchannels > 0; blankchannels--) {
                            memset(dmx_sender_thread->DMXData, 0,blankchannels);
                        }
                    if (is_usb_connected2) if (Channel_1 > 1) for (blankchannels = Channel_1-1; blankchannels > 0; blankchannels--) {
                            memset(dmx_sender_thread2->DMXData, 0,blankchannels);
                        }
                    if (is_usb_connected3) if (Channel_1 > 1) for (blankchannels = Channel_1-1; blankchannels > 0; blankchannels--) {
                            memset(dmx_sender_thread3->DMXData, 0,blankchannels);
                        }
                    if (is_usb_connected4) if (Channel_1 > 1) for (blankchannels = Channel_1-1; blankchannels > 0; blankchannels--) {
                            memset(dmx_sender_thread4->DMXData, 0,blankchannels);
                        }
                }

                else{ // if isDMXcascade
///check to make sure this works
                DMXcascadecount = 512;
                for (int i=0; i<32;i++)
                {
                    memset(dmx_sender_thread->DMXData, Channel_16_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_15_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_14_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_13_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_12_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_11_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_10_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_9_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_8_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_7_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_6_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_5_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_4_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_3_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_2_out,DMXcascadecount--);
                    memset(dmx_sender_thread->DMXData, Channel_1_out,DMXcascadecount--);
                }


                if (is_usb_connected2) {

                    DMXcascadecount = 512;
                    for (int i=0; i<32;i++)
                    {
                        memset(dmx_sender_thread2->DMXData, Channel_16_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_15_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_14_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_13_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_12_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_11_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_10_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_9_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_8_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_7_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_6_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_5_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_4_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_3_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_2_out,DMXcascadecount--);
                        memset(dmx_sender_thread2->DMXData, Channel_1_out,DMXcascadecount--);
                    }
                }

                if (is_usb_connected3) {
                    DMXcascadecount = 512;
                    for (int i=0; i<32;i++)
                    {
                        memset(dmx_sender_thread3->DMXData, Channel_16_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_15_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_14_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_13_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_12_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_11_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_10_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_9_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_8_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_7_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_6_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_5_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_4_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_3_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_2_out,DMXcascadecount--);
                        memset(dmx_sender_thread3->DMXData, Channel_1_out,DMXcascadecount--);
                    }
                }

                if (is_usb_connected4) {
                    DMXcascadecount = 512;
                    for (int i=0; i<32;i++)
                    {
                        memset(dmx_sender_thread4->DMXData, Channel_16_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_15_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_14_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_13_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_12_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_11_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_10_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_9_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_8_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_7_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_6_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_5_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_4_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_3_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_2_out,DMXcascadecount--);
                        memset(dmx_sender_thread4->DMXData, Channel_1_out,DMXcascadecount--);
                    }

                }
        } //close else
///this is what actually sends the prepared DMX stream
                dmx_sender_thread->DMXSend();
                if (is_usb_connected2) {
                    dmx_sender_thread2->DMXSend();
                    if (is_usb_connected3) {
                        dmx_sender_thread3->DMXSend();
                        if (is_usb_connected4) dmx_sender_thread4->DMXSend();
                    }
                }

        }
/*
    if (isfirstruninitialize)
    {
        counttostart++;
        if (counttostart > 30)
        {
            if (islightprogramonstartup)
            {
                InitializeLightputEngine();
                isfirstruninitialize = false;
                //isprofilemode = false;
                RunLightProgramOnStartup();
            }
            else isfirstruninitialize = false;
        }
    }
*/

 /*used for windows minimize fix
    if (isIconize) {

        //Iconize(true);
        isIconize = false;
    }
*/
}

void gui10Frame::calculateincrements(void)
{
           if (Channel_1_new > Channel_1_out) Channel_1_difference = Channel_1_new - Channel_1_out;
           if (Channel_1_new < Channel_1_out) Channel_1_difference = Channel_1_out - Channel_1_new;
           Channel_1_increment = Channel_1_difference / ((beattime/LightputFrequency));

           if (Channel_2_new > Channel_2_out) Channel_2_difference = Channel_2_new - Channel_2_out;
           if (Channel_2_new < Channel_2_out) Channel_2_difference = Channel_2_out - Channel_2_new;
           Channel_2_increment = Channel_2_difference / ((beattime/LightputFrequency));

           if (Channel_3_new > Channel_3_out) Channel_3_difference = Channel_3_new - Channel_3_out;
           if (Channel_3_new < Channel_3_out) Channel_3_difference = Channel_3_out - Channel_3_new;
           Channel_3_increment = Channel_3_difference / ((beattime/LightputFrequency));

           if (Channel_4_new > Channel_4_out) Channel_4_difference = Channel_4_new - Channel_4_out;
           if (Channel_4_new < Channel_4_out) Channel_4_difference = Channel_4_out - Channel_4_new;
           Channel_4_increment = Channel_4_difference / ((beattime/LightputFrequency));

           if (Channel_5_new > Channel_5_out) Channel_5_difference = Channel_5_new - Channel_5_out;
           if (Channel_5_new < Channel_5_out) Channel_5_difference = Channel_5_out - Channel_5_new;
           Channel_5_increment = Channel_5_difference / ((beattime/LightputFrequency));

           if (Channel_6_new > Channel_6_out) Channel_6_difference = Channel_6_new - Channel_6_out;
           if (Channel_6_new < Channel_6_out) Channel_6_difference = Channel_6_out - Channel_6_new;
           Channel_6_increment = Channel_6_difference / ((beattime/LightputFrequency));

           if (Channel_7_new > Channel_7_out) Channel_7_difference = Channel_7_new - Channel_7_out;
           if (Channel_7_new < Channel_7_out) Channel_7_difference = Channel_7_out - Channel_7_new;
           Channel_7_increment = Channel_7_difference / ((beattime/LightputFrequency));

           if (Channel_8_new > Channel_8_out) Channel_8_difference = Channel_8_new - Channel_8_out;
           if (Channel_8_new < Channel_8_out) Channel_8_difference = Channel_8_out - Channel_8_new;
           Channel_8_increment = Channel_8_difference / ((beattime/LightputFrequency));

           if (Channel_9_new > Channel_9_out) Channel_9_difference = Channel_9_new - Channel_9_out;
           if (Channel_9_new < Channel_9_out) Channel_9_difference = Channel_9_out - Channel_9_new;
           Channel_9_increment = Channel_9_difference / ((beattime/LightputFrequency));

           if (Channel_10_new > Channel_10_out) Channel_10_difference = Channel_10_new - Channel_10_out;
           if (Channel_10_new < Channel_10_out) Channel_10_difference = Channel_10_out - Channel_10_new;
           Channel_10_increment = Channel_10_difference / ((beattime/LightputFrequency));

           if (Channel_11_new > Channel_11_out) Channel_11_difference = Channel_11_new - Channel_11_out;
           if (Channel_11_new < Channel_11_out) Channel_11_difference = Channel_11_out - Channel_11_new;
           Channel_11_increment = Channel_11_difference / ((beattime/LightputFrequency));

           if (Channel_12_new > Channel_12_out) Channel_12_difference = Channel_12_new - Channel_12_out;
           if (Channel_12_new < Channel_12_out) Channel_12_difference = Channel_12_out - Channel_12_new;
           Channel_12_increment = Channel_12_difference / ((beattime/LightputFrequency));

           if (Channel_13_new > Channel_13_out) Channel_13_difference = Channel_13_new - Channel_13_out;
           if (Channel_13_new < Channel_13_out) Channel_13_difference = Channel_13_out - Channel_13_new;
           Channel_13_increment = Channel_13_difference / ((beattime/LightputFrequency));

           if (Channel_14_new > Channel_14_out) Channel_14_difference = Channel_14_new - Channel_14_out;
           if (Channel_14_new < Channel_14_out) Channel_14_difference = Channel_14_out - Channel_14_new;
           Channel_14_increment = Channel_14_difference / ((beattime/LightputFrequency));

           if (Channel_15_new > Channel_15_out) Channel_15_difference = Channel_15_new - Channel_15_out;
           if (Channel_15_new < Channel_15_out) Channel_15_difference = Channel_15_out - Channel_15_new;
           Channel_15_increment = Channel_15_difference / ((beattime/LightputFrequency));

           if (Channel_16_new > Channel_16_out) Channel_16_difference = Channel_16_new - Channel_16_out;
           if (Channel_16_new < Channel_16_out) Channel_16_difference = Channel_16_out - Channel_16_new;
           Channel_16_increment = Channel_16_difference / ((beattime/LightputFrequency));
}



void gui10Frame::OnMenuItem4Selected(wxCommandEvent& event)
{

    LightProgramStart();

    LightPrograms Dlg(0);
    Dlg.ShowModal();

    LightProgramStop();

    saveoptions();

    }
//options button
void gui10Frame::OnButton12Click(wxCommandEvent& event)
{
    Options Dlg(0);
    Dlg.ShowModal();
    loadoptions();
    setoutputchannels();
    updateprofileinterval();
    isbeattimecalculationchange = true;
}


void gui10Frame::OnButton12Click1(wxCommandEvent& event)
{

//char to wxstring
    //wxString wxt_input(input, wxConvUTF8);
    //wxString wxt_input;// = wxString::FromUTF8(input);
//    wxt_input = wxString::FromAscii(input);
    //wxt_input = input;
   // wxMessageBox (wxt_input,wxt_input);
}

void gui10Frame::LightProgramStart(void)
{

     //isprofilemode = false;

    ///finishes up the transition before loading the light program
    Channel_1_out = Channel_1_new;
    Channel_2_out = Channel_2_new;
    Channel_3_out = Channel_3_new;
    Channel_4_out = Channel_4_new;
    Channel_5_out = Channel_5_new;
    Channel_6_out = Channel_6_new;
    Channel_7_out = Channel_7_new;
    Channel_8_out = Channel_8_new;
    Channel_9_out = Channel_9_new;
    Channel_10_out = Channel_10_new;
    Channel_11_out = Channel_11_new;
    Channel_12_out = Channel_12_new;
    Channel_13_out = Channel_13_new;
    Channel_14_out = Channel_14_new;
    Channel_15_out = Channel_15_new;
    Channel_16_out = Channel_16_new;

    bs_ProfileChannel_1 = Channel_1_out;
    bs_ProfileChannel_2 = Channel_2_out;
    bs_ProfileChannel_3 = Channel_3_out;
    bs_ProfileChannel_4 = Channel_4_out;
    bs_ProfileChannel_5 = Channel_5_out;
    bs_ProfileChannel_6 = Channel_6_out;
    bs_ProfileChannel_7 = Channel_7_out;
    bs_ProfileChannel_8 = Channel_8_out;
    bs_ProfileChannel_9 = Channel_9_out;
    bs_ProfileChannel_10 = Channel_10_out;
    bs_ProfileChannel_11 = Channel_11_out;
    bs_ProfileChannel_12 = Channel_12_out;
    bs_ProfileChannel_13 = Channel_13_out;
    bs_ProfileChannel_14 = Channel_14_out;
    bs_ProfileChannel_15 = Channel_15_out;
    bs_ProfileChannel_16 = Channel_16_out;

    ls_ProfileChannel_1 = Channel_1_out;
    ls_ProfileChannel_2 = Channel_2_out;
    ls_ProfileChannel_3 = Channel_3_out;
    ls_ProfileChannel_4 = Channel_4_out;
    ls_ProfileChannel_5 = Channel_5_out;
    ls_ProfileChannel_6 = Channel_6_out;
    ls_ProfileChannel_7 = Channel_7_out;
    ls_ProfileChannel_8 = Channel_8_out;
    ls_ProfileChannel_9 = Channel_9_out;
    ls_ProfileChannel_10 = Channel_10_out;
    ls_ProfileChannel_11 = Channel_11_out;
    ls_ProfileChannel_12 = Channel_12_out;
    ls_ProfileChannel_13 = Channel_13_out;
    ls_ProfileChannel_14 = Channel_14_out;
    ls_ProfileChannel_15 = Channel_15_out;
    ls_ProfileChannel_16 = Channel_16_out;

    alarm_ProfileChannel_1 = Channel_1_out;
    alarm_ProfileChannel_2 = Channel_2_out;
    alarm_ProfileChannel_3 = Channel_3_out;
    alarm_ProfileChannel_4 = Channel_4_out;
    alarm_ProfileChannel_5 = Channel_5_out;
    alarm_ProfileChannel_6 = Channel_6_out;
    alarm_ProfileChannel_7 = Channel_7_out;
    alarm_ProfileChannel_8 = Channel_8_out;
    alarm_ProfileChannel_9 = Channel_9_out;
    alarm_ProfileChannel_10 = Channel_10_out;
    alarm_ProfileChannel_11 = Channel_11_out;
    alarm_ProfileChannel_12 = Channel_12_out;
    alarm_ProfileChannel_13 = Channel_13_out;
    alarm_ProfileChannel_14 = Channel_14_out;
    alarm_ProfileChannel_15 = Channel_15_out;
    alarm_ProfileChannel_16 = Channel_16_out;

    timer_ProfileChannel_1 = Channel_1_out;
    timer_ProfileChannel_2 = Channel_2_out;
    timer_ProfileChannel_3 = Channel_3_out;
    timer_ProfileChannel_4 = Channel_4_out;
    timer_ProfileChannel_5 = Channel_5_out;
    timer_ProfileChannel_6 = Channel_6_out;
    timer_ProfileChannel_7 = Channel_7_out;
    timer_ProfileChannel_8 = Channel_8_out;
    timer_ProfileChannel_9 = Channel_9_out;
    timer_ProfileChannel_10 = Channel_10_out;
    timer_ProfileChannel_11 = Channel_11_out;
    timer_ProfileChannel_12 = Channel_12_out;
    timer_ProfileChannel_13 = Channel_13_out;
    timer_ProfileChannel_14 = Channel_14_out;
    timer_ProfileChannel_15 = Channel_15_out;
    timer_ProfileChannel_16 = Channel_16_out;

    VSXu_ProfileChannel_1 = Channel_1_out;
    VSXu_ProfileChannel_2 = Channel_2_out;
    VSXu_ProfileChannel_3 = Channel_3_out;
    VSXu_ProfileChannel_4 = Channel_4_out;
    VSXu_ProfileChannel_5 = Channel_5_out;
    VSXu_ProfileChannel_6 = Channel_6_out;
    VSXu_ProfileChannel_7 = Channel_7_out;
    VSXu_ProfileChannel_8 = Channel_8_out;
    VSXu_ProfileChannel_9 = Channel_9_out;
    VSXu_ProfileChannel_10 = Channel_10_out;
    VSXu_ProfileChannel_11 = Channel_11_out;
    VSXu_ProfileChannel_12 = Channel_12_out;
    VSXu_ProfileChannel_13 = Channel_13_out;
    VSXu_ProfileChannel_14 = Channel_14_out;
    VSXu_ProfileChannel_15 = Channel_15_out;
    VSXu_ProfileChannel_16 = Channel_16_out;

}

void gui10Frame::LightProgramStop(void)
{

if (islightsequencer || is24hmode || isMidiControlmode || isExternalInput) {
    //put values back to avoid the profile mode freak out
    Channel_1_out = bs_ProfileChannel_1;
    Channel_1_new = bs_ProfileChannel_1;
    Channel_1_added = bs_ProfileChannel_1;

    Channel_2_out = bs_ProfileChannel_2;
    Channel_2_new = bs_ProfileChannel_2;
    Channel_2_added = bs_ProfileChannel_2;

    Channel_3_out = bs_ProfileChannel_3;
    Channel_3_new = bs_ProfileChannel_3;
    Channel_3_added = bs_ProfileChannel_3;

    Channel_4_out = bs_ProfileChannel_4;
    Channel_4_new = bs_ProfileChannel_4;
    Channel_4_added = bs_ProfileChannel_4;

    Channel_5_out = bs_ProfileChannel_5;
    Channel_5_new = bs_ProfileChannel_5;
    Channel_5_added = bs_ProfileChannel_5;

    Channel_6_out = bs_ProfileChannel_6;
    Channel_6_new = bs_ProfileChannel_6;
    Channel_6_added = bs_ProfileChannel_6;

    Channel_7_out = bs_ProfileChannel_7;
    Channel_7_new = bs_ProfileChannel_7;
    Channel_7_added = bs_ProfileChannel_7;

    Channel_8_out = bs_ProfileChannel_8;
    Channel_8_new = bs_ProfileChannel_8;
    Channel_8_added = bs_ProfileChannel_8;

    Channel_9_out = bs_ProfileChannel_9;
    Channel_9_new = bs_ProfileChannel_9;
    Channel_9_added = bs_ProfileChannel_9;

    Channel_10_out = bs_ProfileChannel_10;
    Channel_10_new = bs_ProfileChannel_10;
    Channel_10_added = bs_ProfileChannel_10;

    Channel_11_out = bs_ProfileChannel_11;
    Channel_11_new = bs_ProfileChannel_11;
    Channel_11_added = bs_ProfileChannel_11;

    Channel_12_out = bs_ProfileChannel_12;
    Channel_12_new = bs_ProfileChannel_12;
    Channel_12_added = bs_ProfileChannel_12;

    Channel_13_out = bs_ProfileChannel_13;
    Channel_13_new = bs_ProfileChannel_13;
    Channel_13_added = bs_ProfileChannel_13;

    Channel_14_out = bs_ProfileChannel_14;
    Channel_14_new = bs_ProfileChannel_14;
    Channel_14_added = bs_ProfileChannel_14;

    Channel_15_out = bs_ProfileChannel_15;
    Channel_15_new = bs_ProfileChannel_15;
    Channel_15_added = bs_ProfileChannel_15;

    Channel_16_out = bs_ProfileChannel_16;
    Channel_16_new = bs_ProfileChannel_16;
    Channel_16_added = bs_ProfileChannel_16;
    islightsequencer = false;
    is24hmode = false;
    isMidiControlmode = false;
    isExternalInput = false;
    isprofilemode = true;
    }

    isbeattimecalculationchange = true;

    isprofilemode = true;
    isalarm = false;

    updateprofileinterval();
    calculateincrements();

}

void gui10Frame::saveoptions(void)
{

    //update options from light programs
    wxString o1;
    //wxString o2;
    wxString o3;
    wxString o4;
    wxString o5;
    wxString o6;
    wxString o7;
    wxString o8;
    wxString o9;
    wxString o10; //frequency
    wxString o11; //minimized
    wxString o12; //run light program
    wxString o13; //light program selection

    wxTextFile sofile;
    sofile.Create(wxT("options.lightput"));

    //wxMessageBox (option_defaultprofile, o1);

    o1 = wxString::Format(wxT("%i"),option_dmxmode);
    o3 = wxString::Format(wxT("%i"),option_profiletime);
    o4 = wxString::Format(wxT("%i"),issmooth);
    o5 = wxString::Format(wxT("%i"),issmoothstart);
    o6 = wxString::Format(wxT("%i"),StartingDMXChannel);
    o7 = wxString::Format(wxT("%i"),isDMXcascade);
    o8 = wxString::Format(wxT("%i"),islsStartOn1);
    o9 = wxString::Format(wxT("%i"),islsRepeat);

    if (LightputFrequency == 60) o10 = wxT("60");
    if (LightputFrequency == 80) o10 = wxT("80");
    if (LightputFrequency == 120) o10 = wxT("120");
    if (LightputFrequency == 250) o10 = wxT("250");
    if (LightputFrequency == 500) o10 = wxT("500");
    if (LightputFrequency == 1000) o10 = wxT("1000");
    if (LightputFrequency == 2000) o10 = wxT("2000");

    o11 = wxString::Format(wxT("%i"),isminimizedonstartup);
    o12 = wxString::Format(wxT("%i"),runlightprogramonstartup);
    o13 = wxString::Format(wxT("%i"),startuplightprogram);


    sofile.AddLine(o1, wxTextFileType_Dos);
    sofile.AddLine(option_defaultprofile, wxTextFileType_Dos);
    sofile.AddLine(o3, wxTextFileType_Dos);
    sofile.AddLine(o4, wxTextFileType_Dos);
    sofile.AddLine(o5, wxTextFileType_Dos);
    sofile.AddLine(o6, wxTextFileType_Dos);
    sofile.AddLine(o7, wxTextFileType_Dos);
    sofile.AddLine(o8, wxTextFileType_Dos);
    sofile.AddLine(o9, wxTextFileType_Dos);
    sofile.AddLine(o10, wxTextFileType_Dos);
    sofile.AddLine(o11, wxTextFileType_Dos);
    sofile.AddLine(o12, wxTextFileType_Dos);
    sofile.AddLine(o13, wxTextFileType_Dos);

    //these lines save and close the file
    sofile.Write(wxTextFileType_Dos, wxConvISO8859_1);
    sofile.Close();
}

//options button
void gui10Frame::OnButton12Click2(wxCommandEvent& event)
{
    Options Dlg(0);
    Dlg.ShowModal();
    loadoptions();
    setoutputchannels();
    updateprofileinterval();
    isbeattimecalculationchange = true;
}

void gui10Frame::OnHelp(wxCommandEvent& event)
{
    wxMessageBox(wxT("Lightput is used for controlling DMX lighting hardware.  \n \nEach DMX channel has an 8-bit value, 0-255, which is used to determine the brightness of the DMX channel.  The color of the light depends on which color lights you have assigned to different DMX channels.  Most of the examples included with Lightput are setup as red light from channel 1, green light from channel 2, and blue light from channel 3. \n \nYou can assign the brightness and color of the lights by making and switching between light profiles from the main window or you can use the Light Programs to animate light in different ways.  \n \nLight Programs can be activated by default in the options menu so as soon as Lightput starts it loads and activates the selected Light Program.   \n \nLightput only works with FTDI RS-485 communication hardware.  Other RS-485 adapters have not been tested and probably do not work with Lightput. \n \nCheck out lightput.com for more information."),wxT("Help"));

}


void gui10Frame::OnMouseEnter1(wxMouseEvent& event)
{
    //InitializeLightputEngine();
}
