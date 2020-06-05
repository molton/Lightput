/*
#include "MidiControl.h"

//(*InternalHeaders(MidiControl)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
#include <wx/bitmap.h>
#include <wx/image.h>
//*)

#include <wx/textfile.h>
#include "wxMidi.h"

wxMidiInDevice* m_pInDev;
wxMidiOutDevice* m_pOutDev;
wxMidiError nErr;
wxMidiMessage* pMsg;
wxMidiShortMessage* pSMsg;

wxString midifilename;

short int NumberofMidiInputDevices;
int midi_message;
extern bool islightprogramonstartup;

///need to do save stuff. start with is changed trigger, make save changes dialog
bool MidiBankDataischanged;

short int current_data1;
short int current_data2;

short int Channel_1_Midi_Bank = -1;
unsigned short int Channel_1_Midi_Data;
short int Channel_2_Midi_Bank = -1;
unsigned short int Channel_2_Midi_Data;
short int Channel_3_Midi_Bank = -1;
unsigned short int Channel_3_Midi_Data;
short int Channel_4_Midi_Bank = -1;
unsigned short int Channel_4_Midi_Data;
short int Channel_5_Midi_Bank = -1;
unsigned short int Channel_5_Midi_Data;
short int Channel_6_Midi_Bank = -1;
unsigned short int Channel_6_Midi_Data;
short int Channel_7_Midi_Bank = -1;
unsigned short int Channel_7_Midi_Data;
short int Channel_8_Midi_Bank = -1;
unsigned short int Channel_8_Midi_Data;
short int Channel_9_Midi_Bank = -1;
unsigned short int Channel_9_Midi_Data;
short int Channel_10_Midi_Bank = -1;
unsigned short int Channel_10_Midi_Data;
short int Channel_11_Midi_Bank = -1;
unsigned short int Channel_11_Midi_Data;
short int Channel_12_Midi_Bank = -1;
unsigned short int Channel_12_Midi_Data;
short int Channel_13_Midi_Bank = -1;
unsigned short int Channel_13_Midi_Data;
short int Channel_14_Midi_Bank = -1;
unsigned short int Channel_14_Midi_Data;
short int Channel_15_Midi_Bank = -1;
unsigned short int Channel_15_Midi_Data;
short int Channel_16_Midi_Bank = -1;
unsigned short int Channel_16_Midi_Data;

//variables for gui10 main DMX engine
extern unsigned short int Channel_1_MidiControl;
extern unsigned short int Channel_2_MidiControl;
extern unsigned short int Channel_3_MidiControl;
extern unsigned short int Channel_4_MidiControl;
extern unsigned short int Channel_5_MidiControl;
extern unsigned short int Channel_6_MidiControl;
extern unsigned short int Channel_7_MidiControl;
extern unsigned short int Channel_8_MidiControl;
extern unsigned short int Channel_9_MidiControl;
extern unsigned short int Channel_10_MidiControl;
extern unsigned short int Channel_11_MidiControl;
extern unsigned short int Channel_12_MidiControl;
extern unsigned short int Channel_13_MidiControl;
extern unsigned short int Channel_14_MidiControl;
extern unsigned short int Channel_15_MidiControl;
extern unsigned short int Channel_16_MidiControl;

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

extern bool MidiInitialize;

//(*IdInit(MidiControl)
const long MidiControl::ID_STATICTEXT1 = wxNewId();
const long MidiControl::ID_STATICTEXT2 = wxNewId();
const long MidiControl::ID_STATICTEXT3 = wxNewId();
const long MidiControl::ID_STATICTEXT4 = wxNewId();
const long MidiControl::ID_STATICTEXT5 = wxNewId();
const long MidiControl::ID_STATICTEXT6 = wxNewId();
const long MidiControl::ID_STATICTEXT7 = wxNewId();
const long MidiControl::ID_STATICTEXT8 = wxNewId();
const long MidiControl::ID_STATICTEXT9 = wxNewId();
const long MidiControl::ID_STATICTEXT10 = wxNewId();
const long MidiControl::ID_STATICTEXT11 = wxNewId();
const long MidiControl::ID_STATICTEXT12 = wxNewId();
const long MidiControl::ID_BUTTON1 = wxNewId();
const long MidiControl::ID_SLIDER1 = wxNewId();
const long MidiControl::ID_STATICTEXT14 = wxNewId();
const long MidiControl::ID_STATICTEXT16 = wxNewId();
const long MidiControl::ID_STATICTEXT15 = wxNewId();
const long MidiControl::ID_STATICTEXT17 = wxNewId();
const long MidiControl::ID_STATICTEXT18 = wxNewId();
const long MidiControl::ID_STATICTEXT19 = wxNewId();
const long MidiControl::ID_BUTTON2 = wxNewId();
const long MidiControl::ID_BUTTON3 = wxNewId();
const long MidiControl::ID_BUTTON4 = wxNewId();
const long MidiControl::ID_BUTTON5 = wxNewId();
const long MidiControl::ID_BUTTON6 = wxNewId();
const long MidiControl::ID_BUTTON7 = wxNewId();
const long MidiControl::ID_BUTTON8 = wxNewId();
const long MidiControl::ID_BUTTON9 = wxNewId();
const long MidiControl::ID_BUTTON10 = wxNewId();
const long MidiControl::ID_BUTTON11 = wxNewId();
const long MidiControl::ID_BUTTON12 = wxNewId();
const long MidiControl::ID_BUTTON13 = wxNewId();
const long MidiControl::ID_BUTTON14 = wxNewId();
const long MidiControl::ID_BUTTON15 = wxNewId();
const long MidiControl::ID_BUTTON16 = wxNewId();
const long MidiControl::ID_STATICTEXT20 = wxNewId();
const long MidiControl::ID_STATICTEXT21 = wxNewId();
const long MidiControl::ID_STATICTEXT22 = wxNewId();
const long MidiControl::ID_STATICTEXT23 = wxNewId();
const long MidiControl::ID_STATICTEXT24 = wxNewId();
const long MidiControl::ID_STATICTEXT25 = wxNewId();
const long MidiControl::ID_STATICTEXT26 = wxNewId();
const long MidiControl::ID_STATICTEXT27 = wxNewId();
const long MidiControl::ID_STATICTEXT28 = wxNewId();
const long MidiControl::ID_STATICTEXT29 = wxNewId();
const long MidiControl::ID_STATICTEXT30 = wxNewId();
const long MidiControl::ID_STATICTEXT31 = wxNewId();
const long MidiControl::ID_STATICTEXT32 = wxNewId();
const long MidiControl::ID_STATICTEXT33 = wxNewId();
const long MidiControl::ID_STATICTEXT34 = wxNewId();
const long MidiControl::ID_STATICTEXT35 = wxNewId();
const long MidiControl::ID_SLIDER2 = wxNewId();
const long MidiControl::ID_SLIDER3 = wxNewId();
const long MidiControl::ID_SLIDER4 = wxNewId();
const long MidiControl::ID_SLIDER5 = wxNewId();
const long MidiControl::ID_SLIDER6 = wxNewId();
const long MidiControl::ID_SLIDER7 = wxNewId();
const long MidiControl::ID_SLIDER8 = wxNewId();
const long MidiControl::ID_SLIDER9 = wxNewId();
const long MidiControl::ID_SLIDER10 = wxNewId();
const long MidiControl::ID_SLIDER11 = wxNewId();
const long MidiControl::ID_SLIDER12 = wxNewId();
const long MidiControl::ID_SLIDER13 = wxNewId();
const long MidiControl::ID_SLIDER14 = wxNewId();
const long MidiControl::ID_SLIDER15 = wxNewId();
const long MidiControl::ID_SLIDER16 = wxNewId();
const long MidiControl::ID_STATICTEXT37 = wxNewId();
const long MidiControl::ID_STATICTEXT38 = wxNewId();
const long MidiControl::ID_STATICBITMAP1 = wxNewId();
const long MidiControl::ID_STATICTEXT39 = wxNewId();
const long MidiControl::ID_STATICTEXT40 = wxNewId();
const long MidiControl::ID_STATICTEXT41 = wxNewId();
const long MidiControl::ID_BUTTON17 = wxNewId();
//*)
const long MidiControl::ID_MIDICONTROL = wxNewId();

BEGIN_EVENT_TABLE(MidiControl,wxDialog)
	//(*EventTable(MidiControl)
	//*)
	EVT_COMMAND (wxID_ANY, wxEVT_MIDI_INPUT , MidiControl::OnMidiReceive)
END_EVENT_TABLE()

MidiControl::MidiControl(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    Channel_1_MidiControl = ls_ProfileChannel_1;
    Channel_2_MidiControl = ls_ProfileChannel_2;
    Channel_3_MidiControl = ls_ProfileChannel_3;
    Channel_4_MidiControl = ls_ProfileChannel_4;
    Channel_5_MidiControl = ls_ProfileChannel_5;
    Channel_6_MidiControl = ls_ProfileChannel_6;
    Channel_7_MidiControl = ls_ProfileChannel_7;
    Channel_8_MidiControl = ls_ProfileChannel_8;
    Channel_9_MidiControl = ls_ProfileChannel_9;
    Channel_10_MidiControl = ls_ProfileChannel_10;
    Channel_11_MidiControl = ls_ProfileChannel_11;
    Channel_12_MidiControl = ls_ProfileChannel_12;
    Channel_13_MidiControl = ls_ProfileChannel_13;
    Channel_14_MidiControl = ls_ProfileChannel_14;
    Channel_15_MidiControl = ls_ProfileChannel_15;
    Channel_16_MidiControl = ls_ProfileChannel_16;

	//(*Initialize(MidiControl)
	Create(parent, wxID_ANY, _("Lightput Midi Controls 0.1"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(615,384));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Channel 1"), wxPoint(16,72), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Channel 2"), wxPoint(16,104), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Channel 3"), wxPoint(16,136), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Channel 4"), wxPoint(16,168), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	wxFont StaticText4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Channel 5"), wxPoint(16,200), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	wxFont StaticText5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText5->SetFont(StaticText5Font);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Channel 6"), wxPoint(16,232), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	wxFont StaticText6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText6->SetFont(StaticText6Font);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Channel 7"), wxPoint(16,264), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	wxFont StaticText7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText7->SetFont(StaticText7Font);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Channel 8"), wxPoint(16,296), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	wxFont StaticText8Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText8->SetFont(StaticText8Font);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Channel 9"), wxPoint(328,72), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	wxFont StaticText9Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText9->SetFont(StaticText9Font);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Channel 10"), wxPoint(328,104), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	wxFont StaticText10Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText10->SetFont(StaticText10Font);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Channel 11"), wxPoint(328,136), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	wxFont StaticText11Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText11->SetFont(StaticText11Font);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Channel 12"), wxPoint(328,168), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	wxFont StaticText12Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText12->SetFont(StaticText12Font);
	Midi_Button1 = new wxButton(this, ID_BUTTON1, _("Set"), wxPoint(88,64), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont Midi_Button1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button1->SetFont(Midi_Button1Font);
	Slider1 = new wxSlider(this, ID_SLIDER1, 0, 0, 127, wxPoint(192,64), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER1"));
	Slider1->Disable();
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("Set Midi Input"), wxPoint(96,42), wxSize(136,17), 0, _T("ID_STATICTEXT14"));
	wxFont StaticText14Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText14->SetFont(StaticText14Font);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("DMX Level"), wxPoint(208,42), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	wxFont StaticText16Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText16->SetFont(StaticText16Font);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Channel 13"), wxPoint(328,200), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	wxFont StaticText15Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText15->SetFont(StaticText15Font);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Channel 14"), wxPoint(328,232), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	wxFont StaticText17Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText17->SetFont(StaticText17Font);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("Channel 15"), wxPoint(328,264), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	wxFont StaticText18Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText18->SetFont(StaticText18Font);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("Channel 16"), wxPoint(328,296), wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	wxFont StaticText19Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText19->SetFont(StaticText19Font);
	Midi_Button2 = new wxButton(this, ID_BUTTON2, _("Set"), wxPoint(88,96), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont Midi_Button2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button2->SetFont(Midi_Button2Font);
	Midi_Button3 = new wxButton(this, ID_BUTTON3, _("Set"), wxPoint(88,128), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	wxFont Midi_Button3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button3->SetFont(Midi_Button3Font);
	Midi_Button4 = new wxButton(this, ID_BUTTON4, _("Set"), wxPoint(88,160), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	wxFont Midi_Button4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button4->SetFont(Midi_Button4Font);
	Midi_Button5 = new wxButton(this, ID_BUTTON5, _("Set"), wxPoint(88,192), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	wxFont Midi_Button5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button5->SetFont(Midi_Button5Font);
	Midi_Button6 = new wxButton(this, ID_BUTTON6, _("Set"), wxPoint(88,224), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	wxFont Midi_Button6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button6->SetFont(Midi_Button6Font);
	Midi_Button7 = new wxButton(this, ID_BUTTON7, _("Set"), wxPoint(88,256), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON7"));
	wxFont Midi_Button7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button7->SetFont(Midi_Button7Font);
	Midi_Button8 = new wxButton(this, ID_BUTTON8, _("Set"), wxPoint(88,288), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON8"));
	wxFont Midi_Button8Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button8->SetFont(Midi_Button8Font);
	Midi_Button9 = new wxButton(this, ID_BUTTON9, _("Set"), wxPoint(408,64), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON9"));
	wxFont Midi_Button9Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button9->SetFont(Midi_Button9Font);
	Midi_Button10 = new wxButton(this, ID_BUTTON10, _("Set"), wxPoint(408,96), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON10"));
	wxFont Midi_Button10Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button10->SetFont(Midi_Button10Font);
	Midi_Button11 = new wxButton(this, ID_BUTTON11, _("Set"), wxPoint(408,128), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON11"));
	wxFont Midi_Button11Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button11->SetFont(Midi_Button11Font);
	Midi_Button12 = new wxButton(this, ID_BUTTON12, _("Set"), wxPoint(408,160), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON12"));
	wxFont Midi_Button12Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button12->SetFont(Midi_Button12Font);
	Midi_Button13 = new wxButton(this, ID_BUTTON13, _("Set"), wxPoint(408,192), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON13"));
	wxFont Midi_Button13Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button13->SetFont(Midi_Button13Font);
	Midi_Button14 = new wxButton(this, ID_BUTTON14, _("Set"), wxPoint(408,224), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON14"));
	wxFont Midi_Button14Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button14->SetFont(Midi_Button14Font);
	Midi_Button15 = new wxButton(this, ID_BUTTON15, _("Set"), wxPoint(408,256), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON15"));
	wxFont Midi_Button15Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button15->SetFont(Midi_Button15Font);
	Midi_Button16 = new wxButton(this, ID_BUTTON16, _("Set"), wxPoint(408,288), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON16"));
	wxFont Midi_Button16Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Midi_Button16->SetFont(Midi_Button16Font);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("Not Set"), wxPoint(136,72), wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	wxFont StaticText20Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText20->SetFont(StaticText20Font);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("Not Set"), wxPoint(136,104), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	wxFont StaticText21Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText21->SetFont(StaticText21Font);
	StaticText22 = new wxStaticText(this, ID_STATICTEXT22, _("Not Set"), wxPoint(136,136), wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	wxFont StaticText22Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText22->SetFont(StaticText22Font);
	StaticText23 = new wxStaticText(this, ID_STATICTEXT23, _("Not Set"), wxPoint(136,168), wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	wxFont StaticText23Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText23->SetFont(StaticText23Font);
	StaticText24 = new wxStaticText(this, ID_STATICTEXT24, _("Not Set"), wxPoint(136,200), wxDefaultSize, 0, _T("ID_STATICTEXT24"));
	wxFont StaticText24Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText24->SetFont(StaticText24Font);
	StaticText25 = new wxStaticText(this, ID_STATICTEXT25, _("Not Set"), wxPoint(136,232), wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	wxFont StaticText25Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText25->SetFont(StaticText25Font);
	StaticText26 = new wxStaticText(this, ID_STATICTEXT26, _("Not Set"), wxPoint(136,264), wxDefaultSize, 0, _T("ID_STATICTEXT26"));
	wxFont StaticText26Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText26->SetFont(StaticText26Font);
	StaticText27 = new wxStaticText(this, ID_STATICTEXT27, _("Not Set"), wxPoint(136,296), wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	wxFont StaticText27Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText27->SetFont(StaticText27Font);
	StaticText28 = new wxStaticText(this, ID_STATICTEXT28, _("Not Set"), wxPoint(456,72), wxDefaultSize, 0, _T("ID_STATICTEXT28"));
	wxFont StaticText28Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText28->SetFont(StaticText28Font);
	StaticText29 = new wxStaticText(this, ID_STATICTEXT29, _("Not Set"), wxPoint(456,104), wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	wxFont StaticText29Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText29->SetFont(StaticText29Font);
	StaticText30 = new wxStaticText(this, ID_STATICTEXT30, _("Not Set"), wxPoint(456,136), wxDefaultSize, 0, _T("ID_STATICTEXT30"));
	wxFont StaticText30Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText30->SetFont(StaticText30Font);
	StaticText31 = new wxStaticText(this, ID_STATICTEXT31, _("Not Set"), wxPoint(456,168), wxDefaultSize, 0, _T("ID_STATICTEXT31"));
	wxFont StaticText31Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText31->SetFont(StaticText31Font);
	StaticText32 = new wxStaticText(this, ID_STATICTEXT32, _("Not Set"), wxPoint(456,200), wxDefaultSize, 0, _T("ID_STATICTEXT32"));
	wxFont StaticText32Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText32->SetFont(StaticText32Font);
	StaticText33 = new wxStaticText(this, ID_STATICTEXT33, _("Not Set"), wxPoint(456,232), wxDefaultSize, 0, _T("ID_STATICTEXT33"));
	wxFont StaticText33Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText33->SetFont(StaticText33Font);
	StaticText34 = new wxStaticText(this, ID_STATICTEXT34, _("Not Set"), wxPoint(456,264), wxDefaultSize, 0, _T("ID_STATICTEXT34"));
	wxFont StaticText34Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText34->SetFont(StaticText34Font);
	StaticText35 = new wxStaticText(this, ID_STATICTEXT35, _("Not Set"), wxPoint(456,296), wxDefaultSize, 0, _T("ID_STATICTEXT35"));
	wxFont StaticText35Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText35->SetFont(StaticText35Font);
	Slider2 = new wxSlider(this, ID_SLIDER2, 0, 0, 127, wxPoint(192,96), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER2"));
	Slider2->Disable();
	Slider3 = new wxSlider(this, ID_SLIDER3, 0, 0, 127, wxPoint(192,128), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER3"));
	Slider3->Disable();
	Slider4 = new wxSlider(this, ID_SLIDER4, 0, 0, 127, wxPoint(192,160), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER4"));
	Slider4->Disable();
	Slider5 = new wxSlider(this, ID_SLIDER5, 0, 0, 127, wxPoint(192,192), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER5"));
	Slider5->Disable();
	Slider6 = new wxSlider(this, ID_SLIDER6, 0, 0, 127, wxPoint(192,224), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER6"));
	Slider6->Disable();
	Slider7 = new wxSlider(this, ID_SLIDER7, 0, 0, 127, wxPoint(192,256), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER7"));
	Slider7->Disable();
	Slider8 = new wxSlider(this, ID_SLIDER8, 0, 0, 127, wxPoint(192,288), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER8"));
	Slider8->Disable();
	Slider9 = new wxSlider(this, ID_SLIDER9, 0, 0, 127, wxPoint(512,64), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER9"));
	Slider9->Disable();
	Slider10 = new wxSlider(this, ID_SLIDER10, 0, 0, 127, wxPoint(512,96), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER10"));
	Slider10->Disable();
	Slider11 = new wxSlider(this, ID_SLIDER11, 0, 0, 127, wxPoint(512,128), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER11"));
	Slider11->Disable();
	Slider12 = new wxSlider(this, ID_SLIDER12, 0, 0, 127, wxPoint(512,160), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER12"));
	Slider12->Disable();
	Slider13 = new wxSlider(this, ID_SLIDER13, 0, 0, 127, wxPoint(512,192), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER13"));
	Slider13->Disable();
	Slider14 = new wxSlider(this, ID_SLIDER14, 0, 0, 127, wxPoint(512,224), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER14"));
	Slider14->Disable();
	Slider15 = new wxSlider(this, ID_SLIDER15, 0, 0, 127, wxPoint(512,256), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER15"));
	Slider15->Disable();
	Slider16 = new wxSlider(this, ID_SLIDER16, 0, 0, 127, wxPoint(512,288), wxSize(88,27), 0, wxDefaultValidator, _T("ID_SLIDER16"));
	Slider16->Disable();
	StaticText37 = new wxStaticText(this, ID_STATICTEXT37, _("Set Midi Input"), wxPoint(424,42), wxDefaultSize, 0, _T("ID_STATICTEXT37"));
	wxFont StaticText37Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText37->SetFont(StaticText37Font);
	StaticText38 = new wxStaticText(this, ID_STATICTEXT38, _("DMX Level"), wxPoint(528,42), wxDefaultSize, 0, _T("ID_STATICTEXT38"));
	wxFont StaticText38Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText38->SetFont(StaticText38Font);
	StaticBitmap1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxBitmap(wxImage(_T("graphics/portmusic_logo.bmp"))), wxPoint(512,336), wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
	StaticText39 = new wxStaticText(this, ID_STATICTEXT39, _("Use the Midi Control on your Midi input device and then click the \"Set\" button on the\nlight channel you wish to assign the Midi Control to.  Lightput Listens to all attached\nMidi devices and all Midi Channels, but only one specific control at a time. "), wxPoint(16,328), wxSize(488,26), 0, _T("ID_STATICTEXT39"));
	wxFont StaticText39Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText39->SetFont(StaticText39Font);
	StaticText40 = new wxStaticText(this, ID_STATICTEXT40, _("Midi Input Devices Available:"), wxPoint(16,16), wxDefaultSize, 0, _T("ID_STATICTEXT40"));
	wxFont StaticText40Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText40->SetFont(StaticText40Font);
	StaticText41 = new wxStaticText(this, ID_STATICTEXT41, _("0"), wxPoint(176,16), wxDefaultSize, 0, _T("ID_STATICTEXT41"));
	wxFont StaticText41Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText41->SetFont(StaticText41Font);
	ClearButton = new wxButton(this, ID_BUTTON17, _("Clear Midi Input Settings"), wxPoint(328,8), wxSize(272,24), 0, wxDefaultValidator, _T("ID_BUTTON17"));
	wxFont ClearButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	ClearButton->SetFont(ClearButtonFont);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button1Click);
	Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider1CmdScroll);
	Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider1CmdScroll);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button2Click);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button3Click);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button4Click);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button5Click);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button6Click);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button7Click);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button8Click);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button9Click);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button10Click);
	Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button11Click);
	Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button12Click);
	Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button13Click);
	Connect(ID_BUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button14Click);
	Connect(ID_BUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button15Click);
	Connect(ID_BUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnMidi_Button16Click);
	Connect(ID_SLIDER2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider2CmdScroll);
	Connect(ID_SLIDER2,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider2CmdScroll);
	Connect(ID_SLIDER3,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider3CmdScroll);
	Connect(ID_SLIDER3,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider3CmdScroll);
	Connect(ID_SLIDER4,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider4CmdScroll);
	Connect(ID_SLIDER4,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider4CmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider5CmdScroll);
	Connect(ID_SLIDER5,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider5CmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider6CmdScroll);
	Connect(ID_SLIDER6,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider6CmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider7CmdScroll);
	Connect(ID_SLIDER7,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider7CmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider8CmdScroll);
	Connect(ID_SLIDER8,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider8CmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider9CmdScroll);
	Connect(ID_SLIDER9,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider9CmdScroll);
	Connect(ID_SLIDER10,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider10CmdScroll);
	Connect(ID_SLIDER10,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider10CmdScroll);
	Connect(ID_SLIDER11,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider11CmdScroll);
	Connect(ID_SLIDER11,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider11CmdScroll);
	Connect(ID_SLIDER12,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider12CmdScroll);
	Connect(ID_SLIDER12,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider12CmdScroll);
	Connect(ID_SLIDER13,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider13CmdScroll);
	Connect(ID_SLIDER13,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider13CmdScroll);
	Connect(ID_SLIDER14,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider14CmdScroll);
	Connect(ID_SLIDER14,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider14CmdScroll);
	Connect(ID_SLIDER15,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider15CmdScroll);
	Connect(ID_SLIDER15,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider15CmdScroll);
	Connect(ID_SLIDER16,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MidiControl::OnSlider16CmdScroll);
	Connect(ID_SLIDER16,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&MidiControl::OnSlider16CmdScroll);
	Connect(ID_BUTTON17,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MidiControl::OnButton1Click2);
	//*)

	 if (MidiInitialize) {
        wxMidiSystem* pMidiSystem = wxMidiSystem::GetInstance();
        int nMaxDevice = pMidiSystem->CountDevices();


        NumberofMidiInputDevices = 0;


        for (int i = 0; i < nMaxDevice; i++){
            m_pOutDev = new wxMidiOutDevice(i);

            if (m_pOutDev->IsInputPort()) {
                m_pInDev = new wxMidiInDevice(i);
                //wxString wxt_device = m_pInDev->DeviceName();
                //MidiDeviceChoice->Append(wxt_device);// (NumberofMidiInputDevices, wxT("device"));
                NumberofMidiInputDevices++;

                m_pInDev->Open();
            }

        }

            //if (m_pInDev->IsInputPort()) m_pInDev->Open();
        midifilename = wxT("./light_programs/midicontrol.lightput");
        MidiInitialize = false;

        }

    StaticText41->SetLabel(wxString::Format(wxT("%i"),NumberofMidiInputDevices));
    m_pInDev->SetFilter(wxMIDI_FILT_ACTIVE | wxMIDI_FILT_CLOCK);
    m_pInDev->Flush();

    m_pInDev->StartListening(this);


	LoadData();

	if (islightprogramonstartup) islightprogramonstartup = false;
}

MidiControl::~MidiControl()
{
	//(*Destroy(MidiControl)
	//*)
    m_pInDev->StopListening();
    SaveData();
}

void MidiControl::OnMidiReceive(wxCommandEvent &event)
{

    m_pInDev->Poll();
    pMsg = m_pInDev->Read(&nErr);

    //get actual midi message as midi shortmessage (data1, data2)
    midi_message = pMsg->GetStatus();
    pSMsg = (wxMidiShortMessage*) pMsg;
    current_data1 = pSMsg->GetData1();
    current_data2 = pSMsg->GetData2();

    //delete messages to prevent issues
    //delete pMsg;
    //delete pSMsg;


if (Channel_1_Midi_Bank == current_data1) {
    Slider1->SetValue(current_data2);
    Channel_1_MidiControl = (current_data2 * 2);
    }
if (Channel_2_Midi_Bank == current_data1) {
    Slider2->SetValue(current_data2);
    Channel_2_MidiControl = (current_data2 * 2);
    }
if (Channel_3_Midi_Bank == current_data1) {
    Slider3->SetValue(current_data2);
    Channel_3_MidiControl = (current_data2 * 2);
    }
if (Channel_4_Midi_Bank == current_data1) {
    Slider4->SetValue(current_data2);
    Channel_4_MidiControl = (current_data2 * 2);
    }
if (Channel_5_Midi_Bank == current_data1) {
    Slider5->SetValue(current_data2);
    Channel_5_MidiControl = (current_data2 * 2);
    }
if (Channel_6_Midi_Bank == current_data1) {
    Slider6->SetValue(current_data2);
    Channel_6_MidiControl = (current_data2 * 2);
    }
if (Channel_7_Midi_Bank == current_data1) {
    Slider7->SetValue(current_data2);
    Channel_7_MidiControl = (current_data2 * 2);
    }
if (Channel_8_Midi_Bank == current_data1) {
    Slider8->SetValue(current_data2);
    Channel_8_MidiControl = (current_data2 * 2);
    }
if (Channel_9_Midi_Bank == current_data1) {
    Slider9->SetValue(current_data2);
    Channel_9_MidiControl = (current_data2 * 2);
    }
if (Channel_10_Midi_Bank == current_data1) {
    Slider10->SetValue(current_data2);
    Channel_10_MidiControl = (current_data2 * 2);
    }
if (Channel_11_Midi_Bank == current_data1) {
    Slider11->SetValue(current_data2);
    Channel_11_MidiControl = (current_data2 * 2);
    }
if (Channel_12_Midi_Bank == current_data1) {
    Slider12->SetValue(current_data2);
    Channel_12_MidiControl = (current_data2 * 2);
    }
if (Channel_13_Midi_Bank == current_data1) {
    Slider13->SetValue(current_data2);
    Channel_13_MidiControl = (current_data2 * 2);
    }
if (Channel_14_Midi_Bank == current_data1) {
    Slider14->SetValue(current_data2);
    Channel_14_MidiControl = (current_data2 * 2);
    }
if (Channel_15_Midi_Bank == current_data1) {
    Slider15->SetValue(current_data2);
    Channel_15_MidiControl = (current_data2 * 2);
    }
if (Channel_16_Midi_Bank == current_data1) {
    Slider16->SetValue(current_data2);
    Channel_16_MidiControl = (current_data2 * 2);
    }



    //this flush line fixes the midi message pileup crashes
    m_pInDev->Flush();



}




void MidiControl::OnClose(wxCloseEvent& event)
{
        m_pInDev->StopListening();
        //m_pInDev->Flush();
        //m_pInDev->~wxMidiInDevice();

        delete pSMsg;
        delete pMsg;

        SaveData();
        Destroy();
}

///midi channel 1 set button
void MidiControl::OnMidi_Button1Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_1_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText20->SetLabel(displayValue);
}

///midi channel 2 set button
void MidiControl::OnMidi_Button2Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_2_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText21->SetLabel(displayValue);
}

///midi channel 3 set button
void MidiControl::OnMidi_Button3Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_3_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText22->SetLabel(displayValue);
}

///midi channel 4 set button
void MidiControl::OnMidi_Button4Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_4_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText23->SetLabel(displayValue);
}

///midi channel 5 set button
void MidiControl::OnMidi_Button5Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_5_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText24->SetLabel(displayValue);
}

///midi channel 6 set button
void MidiControl::OnMidi_Button6Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_6_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText25->SetLabel(displayValue);
}

///midi channel 7 set button
void MidiControl::OnMidi_Button7Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_7_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText26->SetLabel(displayValue);
}

///midi channel 8 set button
void MidiControl::OnMidi_Button8Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_8_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText27->SetLabel(displayValue);
}

///midi channel 9 set button
void MidiControl::OnMidi_Button9Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_9_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText28->SetLabel(displayValue);
}

///midi channel 10 set button
void MidiControl::OnMidi_Button10Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_10_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText29->SetLabel(displayValue);
}

///midi channel 11 set button
void MidiControl::OnMidi_Button11Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_11_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText30->SetLabel(displayValue);
}

///midi channel 12 set button
void MidiControl::OnMidi_Button12Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_12_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText31->SetLabel(displayValue);
}

///midi channel 13 set button
void MidiControl::OnMidi_Button13Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_13_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText32->SetLabel(displayValue);
}

///midi channel 14 set button
void MidiControl::OnMidi_Button14Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_14_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText33->SetLabel(displayValue);
}

///midi channel 15 set button
void MidiControl::OnMidi_Button15Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_15_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText34->SetLabel(displayValue);
}

///midi channel 16 set button
void MidiControl::OnMidi_Button16Click(wxCommandEvent& event)
{
        wxString displayValue;
        Channel_16_Midi_Bank = current_data1;
        displayValue = wxString::Format(wxT("%i"),current_data1);
        StaticText35->SetLabel(displayValue);
}

void MidiControl::OnSlider1CmdScroll(wxScrollEvent& event)
{
    Channel_1_MidiControl = (Slider1->GetValue() * 2);
}

void MidiControl::OnSlider2CmdScroll(wxScrollEvent& event)
{
    Channel_2_MidiControl = (Slider2->GetValue() * 2);
}

void MidiControl::OnSlider3CmdScroll(wxScrollEvent& event)
{
    Channel_3_MidiControl = (Slider3->GetValue() * 2);
}

void MidiControl::OnSlider4CmdScroll(wxScrollEvent& event)
{
    Channel_4_MidiControl = (Slider4->GetValue() * 2);
}

void MidiControl::OnSlider5CmdScroll(wxScrollEvent& event)
{
    Channel_5_MidiControl = (Slider5->GetValue() * 2);
}

void MidiControl::OnSlider6CmdScroll(wxScrollEvent& event)
{
    Channel_6_MidiControl = (Slider6->GetValue() * 2);
}

void MidiControl::OnSlider7CmdScroll(wxScrollEvent& event)
{
    Channel_7_MidiControl = (Slider7->GetValue() * 2);
}

void MidiControl::OnSlider8CmdScroll(wxScrollEvent& event)
{
    Channel_8_MidiControl = (Slider8->GetValue() * 2);
}

void MidiControl::OnSlider9CmdScroll(wxScrollEvent& event)
{
    Channel_9_MidiControl = (Slider9->GetValue() * 2);
}

void MidiControl::OnSlider10CmdScroll(wxScrollEvent& event)
{
    Channel_10_MidiControl = (Slider10->GetValue() * 2);
}

void MidiControl::OnSlider11CmdScroll(wxScrollEvent& event)
{
    Channel_11_MidiControl = (Slider11->GetValue() * 2);
}

void MidiControl::OnSlider12CmdScroll(wxScrollEvent& event)
{
    Channel_12_MidiControl = (Slider12->GetValue() * 2);
}

void MidiControl::OnSlider13CmdScroll(wxScrollEvent& event)
{
    Channel_13_MidiControl = (Slider13->GetValue() * 2);
}

void MidiControl::OnSlider14CmdScroll(wxScrollEvent& event)
{
    Channel_14_MidiControl = (Slider14->GetValue() * 2);
}

void MidiControl::OnSlider15CmdScroll(wxScrollEvent& event)
{
    Channel_15_MidiControl = (Slider15->GetValue() * 2);
}

void MidiControl::OnSlider16CmdScroll(wxScrollEvent& event)
{
    Channel_16_MidiControl = (Slider16->GetValue() * 2);
}

void MidiControl::LoadData(void)
{
    wxTextFile midifile;
    midifile.Open(midifilename, wxConvISO8859_1);

    wxString buffer;

    buffer = midifile.GetFirstLine();
    Channel_1_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_2_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_3_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_4_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_5_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_6_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_7_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_8_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_9_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_10_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_11_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_12_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_13_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_14_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_15_Midi_Bank = wxAtoi(buffer);

    buffer = midifile.GetNextLine();
    Channel_16_Midi_Bank = wxAtoi(buffer);

    wxString displayValue;

    if (Channel_1_Midi_Bank != -1) {
        StaticText20->SetLabel(wxString::Format(wxT("%i"),Channel_1_Midi_Bank));
    }
    if (Channel_2_Midi_Bank != -1) {
        StaticText21->SetLabel(wxString::Format(wxT("%i"),Channel_2_Midi_Bank));
    }
    if (Channel_3_Midi_Bank != -1) {
        StaticText22->SetLabel(wxString::Format(wxT("%i"),Channel_3_Midi_Bank));
    }
    if (Channel_4_Midi_Bank != -1) {
        StaticText23->SetLabel(wxString::Format(wxT("%i"),Channel_4_Midi_Bank));
    }
    if (Channel_5_Midi_Bank != -1) {
        StaticText24->SetLabel(wxString::Format(wxT("%i"),Channel_5_Midi_Bank));
    }
    if (Channel_6_Midi_Bank != -1) {
        StaticText25->SetLabel(wxString::Format(wxT("%i"),Channel_6_Midi_Bank));
    }
    if (Channel_7_Midi_Bank != -1) {
        StaticText26->SetLabel(wxString::Format(wxT("%i"),Channel_7_Midi_Bank));
    }
    if (Channel_8_Midi_Bank != -1) {
        StaticText27->SetLabel(wxString::Format(wxT("%i"),Channel_8_Midi_Bank));
    }
    if (Channel_9_Midi_Bank != -1) {
        StaticText28->SetLabel(wxString::Format(wxT("%i"),Channel_9_Midi_Bank));
    }
    if (Channel_10_Midi_Bank != -1) {
        StaticText29->SetLabel(wxString::Format(wxT("%i"),Channel_10_Midi_Bank));
    }
    if (Channel_11_Midi_Bank != -1) {
        StaticText30->SetLabel(wxString::Format(wxT("%i"),Channel_11_Midi_Bank));
    }
    if (Channel_12_Midi_Bank != -1) {
        StaticText31->SetLabel(wxString::Format(wxT("%i"),Channel_12_Midi_Bank));
    }
    if (Channel_13_Midi_Bank != -1) {
        StaticText32->SetLabel(wxString::Format(wxT("%i"),Channel_13_Midi_Bank));
    }
    if (Channel_14_Midi_Bank != -1) {
        StaticText33->SetLabel(wxString::Format(wxT("%i"),Channel_14_Midi_Bank));
    }
    if (Channel_15_Midi_Bank != -1) {
        StaticText34->SetLabel(wxString::Format(wxT("%i"),Channel_15_Midi_Bank));
    }
    if (Channel_16_Midi_Bank != -1) {
        StaticText35->SetLabel(wxString::Format(wxT("%i"),Channel_16_Midi_Bank));
    }
}

void MidiControl::SaveData(void)
 {
    wxString BankData;

    wxTextFile midifile;
    midifile.Create(midifilename);

    BankData = wxString::Format(wxT("%i"),Channel_1_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_2_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_3_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_4_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_5_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_6_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_7_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_8_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_9_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_10_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_11_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_12_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_13_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_14_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_15_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);
    BankData = wxString::Format(wxT("%i"),Channel_16_Midi_Bank);
    midifile.AddLine(BankData, wxTextFileType_Dos);


    //these lines save and close the file
    midifile.Write(wxTextFileType_Dos, wxConvISO8859_1);
    midifile.Close();

}

void MidiControl::OnButton1Click2(wxCommandEvent& event)
{
    Channel_1_Midi_Bank = -1;
    StaticText20->SetLabel(wxT("Not Set"));
    Channel_2_Midi_Bank = -1;
    StaticText21->SetLabel(wxT("Not Set"));
    Channel_3_Midi_Bank = -1;
    StaticText22->SetLabel(wxT("Not Set"));
    Channel_4_Midi_Bank = -1;
    StaticText23->SetLabel(wxT("Not Set"));
    Channel_5_Midi_Bank = -1;
    StaticText24->SetLabel(wxT("Not Set"));
    Channel_6_Midi_Bank = -1;
    StaticText25->SetLabel(wxT("Not Set"));
    Channel_7_Midi_Bank = -1;
    StaticText26->SetLabel(wxT("Not Set"));
    Channel_8_Midi_Bank = -1;
    StaticText27->SetLabel(wxT("Not Set"));
    Channel_9_Midi_Bank = -1;
    StaticText28->SetLabel(wxT("Not Set"));
    Channel_10_Midi_Bank = -1;
    StaticText29->SetLabel(wxT("Not Set"));
    Channel_11_Midi_Bank = -1;
    StaticText30->SetLabel(wxT("Not Set"));
    Channel_12_Midi_Bank = -1;
    StaticText31->SetLabel(wxT("Not Set"));
    Channel_13_Midi_Bank = -1;
    StaticText32->SetLabel(wxT("Not Set"));
    Channel_14_Midi_Bank = -1;
    StaticText33->SetLabel(wxT("Not Set"));
    Channel_15_Midi_Bank = -1;
    StaticText34->SetLabel(wxT("Not Set"));
    Channel_16_Midi_Bank = -1;
    StaticText35->SetLabel(wxT("Not Set"));
}

*/
