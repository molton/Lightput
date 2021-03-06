//(C) 2013 Michael Johnston

#include "AlarmClock.h"

#include <wx/msgdlg.h>
#include <wx/textfile.h>

//(*InternalHeaders(AlarmClock)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

extern bool isprofilemode;

wxString alarmtime;
bool alarm_is_active;
bool alarm_is_animating;
bool alarminit;
bool alarm_stop;
int alarm_beat;
wxString alarmfilename;

extern bool isIconize;
extern bool islightprogramonstartup;
extern bool isminimizedonstartup;

wxString wxt_Slider1;
wxString wxt_Slider2;

extern bool isalarm;
//extern bool isprofilemode;
int alarm_increment;

//these values are in the same order as the save file
int alarmhour;
int alarmminute;
int alarmampm;
int alarmlightchangetime;
int step1channel;
int step1value;
int step2channel;
int step2value;
int snoozelength;


//buffers for profile when alarm is off/done
extern int alarm_ProfileChannel_1;
extern int alarm_ProfileChannel_2;
extern int alarm_ProfileChannel_3;
extern int alarm_ProfileChannel_4;
extern int alarm_ProfileChannel_5;
extern int alarm_ProfileChannel_6;
extern int alarm_ProfileChannel_7;
extern int alarm_ProfileChannel_8;
extern int alarm_ProfileChannel_9;
extern int alarm_ProfileChannel_10;
extern int alarm_ProfileChannel_11;
extern int alarm_ProfileChannel_12;
extern int alarm_ProfileChannel_13;
extern int alarm_ProfileChannel_14;
extern int alarm_ProfileChannel_15;
extern int alarm_ProfileChannel_16;

//variables for alarm clock
extern unsigned short int Channel_1_alarm;
extern unsigned short int Channel_2_alarm;
extern unsigned short int Channel_3_alarm;
extern unsigned short int Channel_4_alarm;
extern unsigned short int Channel_5_alarm;
extern unsigned short int Channel_6_alarm;
extern unsigned short int Channel_7_alarm;
extern unsigned short int Channel_8_alarm;
extern unsigned short int Channel_9_alarm;
extern unsigned short int Channel_10_alarm;
extern unsigned short int Channel_11_alarm;
extern unsigned short int Channel_12_alarm;
extern unsigned short int Channel_13_alarm;
extern unsigned short int Channel_14_alarm;
extern unsigned short int Channel_15_alarm;
extern unsigned short int Channel_16_alarm;



//(*IdInit(AlarmClock)
const long AlarmClock::ID_STATICBOX1 = wxNewId();
const long AlarmClock::ID_STATICTEXT1 = wxNewId();
const long AlarmClock::ID_STATICTEXT2 = wxNewId();
const long AlarmClock::ID_STATICTEXT3 = wxNewId();
const long AlarmClock::ID_STATICTEXT4 = wxNewId();
const long AlarmClock::ID_BUTTON1 = wxNewId();
const long AlarmClock::ID_CHOICE1 = wxNewId();
const long AlarmClock::ID_CHOICE2 = wxNewId();
const long AlarmClock::ID_CHOICE3 = wxNewId();
const long AlarmClock::ID_STATICTEXT5 = wxNewId();
const long AlarmClock::ID_STATICBOX2 = wxNewId();
const long AlarmClock::ID_CHOICE4 = wxNewId();
const long AlarmClock::ID_CHOICE5 = wxNewId();
const long AlarmClock::ID_SLIDER1 = wxNewId();
const long AlarmClock::ID_SLIDER2 = wxNewId();
const long AlarmClock::ID_CHOICE6 = wxNewId();
const long AlarmClock::ID_STATICTEXT6 = wxNewId();
const long AlarmClock::ID_STATICTEXT7 = wxNewId();
const long AlarmClock::ID_STATICTEXT9 = wxNewId();
const long AlarmClock::ID_STATICTEXT10 = wxNewId();
const long AlarmClock::ID_STATICTEXT11 = wxNewId();
const long AlarmClock::ID_STATICTEXT12 = wxNewId();
const long AlarmClock::ID_BUTTON2 = wxNewId();
const long AlarmClock::ID_CHOICE7 = wxNewId();
const long AlarmClock::ID_STATICTEXT13 = wxNewId();
const long AlarmClock::ID_BUTTON3 = wxNewId();
const long AlarmClock::ID_STATICTEXT8 = wxNewId();
const long AlarmClock::ID_BUTTON4 = wxNewId();
const long AlarmClock::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AlarmClock,wxDialog)
	//(*EventTable(AlarmClock)
	//*)
END_EVENT_TABLE()

AlarmClock::AlarmClock(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AlarmClock)
	Create(parent, wxID_ANY, _("Light Alarm Clock 0.1"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(428,339));
	Move(wxPoint(120,100));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Set Alarm Time"), wxPoint(152,32), wxSize(256,88), 0, _T("ID_STATICBOX1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Label"), wxPoint(32,64), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(16,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Current Time"), wxPoint(32,32), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Alarm Time"), wxPoint(32,112), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Label"), wxPoint(32,144), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	wxFont StaticText4Font(16,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Activate Alarm"), wxPoint(8,192), wxSize(128,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Choice1 = new wxChoice(this, ID_CHOICE1, wxPoint(176,56), wxSize(48,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice1->SetSelection( Choice1->Append(_("01")) );
	Choice1->Append(_("02"));
	Choice1->Append(_("03"));
	Choice1->Append(_("04"));
	Choice1->Append(_("05"));
	Choice1->Append(_("06"));
	Choice1->Append(_("07"));
	Choice1->Append(_("08"));
	Choice1->Append(_("09"));
	Choice1->Append(_("10"));
	Choice1->Append(_("11"));
	Choice1->Append(_("12"));
	Choice2 = new wxChoice(this, ID_CHOICE2, wxPoint(248,56), wxSize(56,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	Choice2->SetSelection( Choice2->Append(_("00")) );
	Choice2->Append(_("01"));
	Choice2->Append(_("02"));
	Choice2->Append(_("03"));
	Choice2->Append(_("04"));
	Choice2->Append(_("05"));
	Choice2->Append(_("06"));
	Choice2->Append(_("07"));
	Choice2->Append(_("08"));
	Choice2->Append(_("09"));
	Choice2->Append(_("10"));
	Choice2->Append(_("11"));
	Choice2->Append(_("12"));
	Choice2->Append(_("13"));
	Choice2->Append(_("14"));
	Choice2->Append(_("15"));
	Choice2->Append(_("16"));
	Choice2->Append(_("17"));
	Choice2->Append(_("18"));
	Choice2->Append(_("19"));
	Choice2->Append(_("20"));
	Choice2->Append(_("21"));
	Choice2->Append(_("22"));
	Choice2->Append(_("23"));
	Choice2->Append(_("24"));
	Choice2->Append(_("25"));
	Choice2->Append(_("26"));
	Choice2->Append(_("27"));
	Choice2->Append(_("28"));
	Choice2->Append(_("29"));
	Choice2->Append(_("30"));
	Choice2->Append(_("31"));
	Choice2->Append(_("32"));
	Choice2->Append(_("33"));
	Choice2->Append(_("34"));
	Choice2->Append(_("35"));
	Choice2->Append(_("36"));
	Choice2->Append(_("37"));
	Choice2->Append(_("38"));
	Choice2->Append(_("39"));
	Choice2->Append(_("40"));
	Choice2->Append(_("41"));
	Choice2->Append(_("42"));
	Choice2->Append(_("43"));
	Choice2->Append(_("44"));
	Choice2->Append(_("45"));
	Choice2->Append(_("46"));
	Choice2->Append(_("47"));
	Choice2->Append(_("48"));
	Choice2->Append(_("49"));
	Choice2->Append(_("50"));
	Choice2->Append(_("51"));
	Choice2->Append(_("52"));
	Choice2->Append(_("53"));
	Choice2->Append(_("54"));
	Choice2->Append(_("55"));
	Choice2->Append(_("56"));
	Choice2->Append(_("57"));
	Choice2->Append(_("58"));
	Choice2->Append(_("59"));
	Choice3 = new wxChoice(this, ID_CHOICE3, wxPoint(320,56), wxSize(56,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
	Choice3->SetSelection( Choice3->Append(_("AM")) );
	Choice3->Append(_("PM"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _(":"), wxPoint(232,59), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Configure Alarm Light"), wxPoint(152,136), wxSize(256,184), 0, _T("ID_STATICBOX2"));
	Choice4 = new wxChoice(this, ID_CHOICE4, wxPoint(264,200), wxSize(104,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
	Choice4->SetSelection( Choice4->Append(_("Channel 1")) );
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
	Choice5 = new wxChoice(this, ID_CHOICE5, wxPoint(264,256), wxSize(104,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
	Choice5->SetSelection( Choice5->Append(_("Channel 1")) );
	Choice5->Append(_("Channel 2"));
	Choice5->Append(_("Channel 3"));
	Choice5->Append(_("Channel 4"));
	Choice5->Append(_("Channel 5"));
	Choice5->Append(_("Channel 6"));
	Choice5->Append(_("Channel 7"));
	Choice5->Append(_("Channel 8"));
	Choice5->Append(_("Channel 9"));
	Choice5->Append(_("Channel 10"));
	Choice5->Append(_("Channel 11"));
	Choice5->Append(_("Channel 12"));
	Choice5->Append(_("Channel 13"));
	Choice5->Append(_("Channel 14"));
	Choice5->Append(_("Channel 15"));
	Choice5->Append(_("Channel 16"));
	Slider1 = new wxSlider(this, ID_SLIDER1, 0, 0, 255, wxPoint(160,232), wxSize(168,24), 0, wxDefaultValidator, _T("ID_SLIDER1"));
	Slider2 = new wxSlider(this, ID_SLIDER2, 0, 0, 255, wxPoint(160,288), wxSize(168,24), 0, wxDefaultValidator, _T("ID_SLIDER2"));
	Choice6 = new wxChoice(this, ID_CHOICE6, wxPoint(304,160), wxSize(40,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE6"));
	Choice6->SetSelection( Choice6->Append(_("0.5")) );
	Choice6->Append(_("1"));
	Choice6->Append(_("2"));
	Choice6->Append(_("3"));
	wxFont Choice6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Choice6->SetFont(Choice6Font);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Alarm light changes every"), wxPoint(160,168), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	wxFont StaticText6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText6->SetFont(StaticText6Font);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("seconds."), wxPoint(344,168), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	wxFont StaticText7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText7->SetFont(StaticText7Font);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Alarm Light Step 1:"), wxPoint(160,208), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	wxFont StaticText9Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText9->SetFont(StaticText9Font);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Alarm Light Step 2:"), wxPoint(160,264), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	wxFont StaticText10Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText10->SetFont(StaticText10Font);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Label"), wxPoint(336,232), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Label"), wxPoint(336,288), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Snooze"), wxPoint(8,240), wxSize(128,32), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Button2->Disable();
	Choice7 = new wxChoice(this, ID_CHOICE7, wxPoint(8,304), wxSize(128,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE7"));
	Choice7->SetSelection( Choice7->Append(_("1 minute")) );
	Choice7->Append(_("2 minutes"));
	Choice7->Append(_("5 minutes"));
	Choice7->Append(_("10 minutes"));
	Choice7->Append(_("15 minutes"));
	Choice7->Append(_("20 minutes"));
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Snooze Length"), wxPoint(16,280), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	Button3 = new wxButton(this, ID_BUTTON3, _("Set Alarm Time"), wxPoint(224,88), wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Label"), wxPoint(448,168), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	Button4 = new wxButton(this, ID_BUTTON4, _("Hide Lightput"), wxPoint(304,0), wxSize(115,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	Timer1.SetOwner(this, ID_TIMER1);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AlarmClock::OnButton1Click);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&AlarmClock::OnChoice1Select);
	Connect(ID_CHOICE3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&AlarmClock::OnChoice3Select);
	Connect(ID_CHOICE4,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&AlarmClock::OnChoice4Select);
	Connect(ID_CHOICE5,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&AlarmClock::OnChoice5Select);
	Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&AlarmClock::OnSlider1CmdScroll);
	Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&AlarmClock::OnSlider1CmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&AlarmClock::OnSlider2CmdScroll1);
	Connect(ID_SLIDER2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&AlarmClock::OnSlider2CmdScroll);
	Connect(ID_SLIDER2,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&AlarmClock::OnSlider2CmdScroll);
	Connect(ID_CHOICE6,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&AlarmClock::OnChoice6Select);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AlarmClock::OnButton2Click);
	Connect(ID_CHOICE7,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&AlarmClock::OnChoice7Select1);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AlarmClock::OnButton3Click1);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AlarmClock::OnButton4Click);
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&AlarmClock::OnTimer1Trigger);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&AlarmClock::OnClose);
	//*)

    alarmfilename = wxT("./light_programs/alarmclock.lightput");

	//this line displays the current time
	StaticText1->SetLabel(wxDateTime::Now().Format(wxT("%I:%M %p")));

    alarm_loadprofiles();

    alarmtime = Choice1->GetString(Choice1->GetSelection()) + wxT(":") + Choice2->GetString(Choice2->GetSelection()) + wxT(" ") + Choice3->GetString(Choice3->GetSelection());
    StaticText4->SetLabel(alarmtime);

    alarm_is_active = false;
    alarm_is_animating = false;
    alarm_stop = false;

        Channel_1_alarm = alarm_ProfileChannel_1;
        Channel_2_alarm = alarm_ProfileChannel_2;
        Channel_3_alarm = alarm_ProfileChannel_3;
        Channel_4_alarm = alarm_ProfileChannel_4;
        Channel_5_alarm = alarm_ProfileChannel_5;
        Channel_6_alarm = alarm_ProfileChannel_6;
        Channel_7_alarm = alarm_ProfileChannel_7;
        Channel_8_alarm = alarm_ProfileChannel_8;
        Channel_9_alarm = alarm_ProfileChannel_9;
        Channel_10_alarm = alarm_ProfileChannel_10;
        Channel_11_alarm = alarm_ProfileChannel_11;
        Channel_12_alarm = alarm_ProfileChannel_12;
        Channel_13_alarm = alarm_ProfileChannel_13;
        Channel_14_alarm = alarm_ProfileChannel_14;
        Channel_15_alarm = alarm_ProfileChannel_15;
        Channel_16_alarm = alarm_ProfileChannel_16;

    isprofilemode = false;

    isalarm = true;

    alarm_beat = 1;

    if (islightprogramonstartup)
    {
        islightprogramonstartup = false;
        //if (isminimizedonstartup) isIconize = true;

        ///activate alarm
           alarm_is_active = true;
        //isalarm = true;
        alarminit = true;
        alarm_stop = false;
        Button1->SetLabel(wxT("Deactivate Alarm"));

        //disable dialog section start
        Choice1->Enable(false);
        Choice2->Enable(false);
        Choice3->Enable(false);
        Choice4->Enable(false);
        Choice5->Enable(false);
        Choice6->Enable(false);
        Button3->Enable(false);
        Slider1->Enable(false);
        Slider2->Enable(false);
        StaticBox1->Enable(false);
        StaticBox2->Enable(false);
        StaticText5->Enable(false);
        StaticText6->Enable(false);
        StaticText7->Enable(false);
        StaticText9->Enable(false);
        StaticText10->Enable(false);
        StaticText11->Enable(false);
        StaticText12->Enable(false);

        alarm_calculateincrements();

        Timer1.Start(100);

    }
}

AlarmClock::~AlarmClock()
{
	//(*Destroy(AlarmClock)
	//*)
}


void AlarmClock::OnChoice1Select(wxCommandEvent& event)
{
}

void AlarmClock::OnTimer1Trigger(wxTimerEvent& event)
{
    //this line redraws the current time after checking that the current time
    //doesn't equal the time currently being displayed on the screen
	if (StaticText1->GetLabel() != wxDateTime::Now().Format(wxT("%I:%M %p"))) StaticText1->SetLabel(wxDateTime::Now().Format(wxT("%I:%M %p")));

        if ((alarm_is_active) && (alarmtime == StaticText1->GetLabel())) {alarm_is_animating = true;

        }
        /* half finished auto snooze feature
        //...if while alarm is animating, the minute changes
        if (StaticText1->GetLabel() != wxDateTime::Now().Format(wxT("%I:%M %p"))){
            StaticText1->SetLabel(wxDateTime::Now().Format(wxT("%I:%M %p")));

            alarmminute++;
            //alarm_is_animating = false;
            snoozehandler();
            Button2->Enable(false);
            return;

        }
        */


        //this code actually executes the alarm, should be elaborated
        //in future releases, this is pretty basic
        //if
        if (alarm_is_animating){
            Button2->Enable(true);
            if (alarm_beat == 1) {

                Channel_1_alarm = 0;
                Channel_2_alarm = 0;
                Channel_3_alarm = 0;
                Channel_4_alarm = 0;
                Channel_5_alarm = 0;
                Channel_6_alarm = 0;
                Channel_7_alarm = 0;
                Channel_8_alarm = 0;
                Channel_9_alarm = 0;
                Channel_11_alarm = 0;
                Channel_12_alarm = 0;
                Channel_13_alarm = 0;
                Channel_14_alarm = 0;
                Channel_15_alarm = 0;
                Channel_16_alarm = 0;

                if (Choice4->GetSelection() == 0) Channel_1_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 1) Channel_2_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 2) Channel_3_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 3) Channel_4_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 4) Channel_5_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 5) Channel_6_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 6) Channel_7_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 7) Channel_8_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 8) Channel_9_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 9) Channel_10_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 10) Channel_11_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 11) Channel_12_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 12) Channel_13_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 13) Channel_14_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 14) Channel_15_alarm = Slider1->GetValue();
                if (Choice4->GetSelection() == 15) Channel_16_alarm = Slider1->GetValue();
            }
            if (alarm_beat == 2) {

                Channel_1_alarm = 0;
                Channel_2_alarm = 0;
                Channel_3_alarm = 0;
                Channel_4_alarm = 0;
                Channel_5_alarm = 0;
                Channel_6_alarm = 0;
                Channel_7_alarm = 0;
                Channel_8_alarm = 0;
                Channel_9_alarm = 0;
                Channel_11_alarm = 0;
                Channel_12_alarm = 0;
                Channel_13_alarm = 0;
                Channel_14_alarm = 0;
                Channel_15_alarm = 0;
                Channel_16_alarm = 0;

                if (Choice5->GetSelection() == 0) Channel_1_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 1) Channel_2_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 2) Channel_3_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 3) Channel_4_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 4) Channel_5_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 5) Channel_6_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 6) Channel_7_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 7) Channel_8_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 8) Channel_9_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 9) Channel_10_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 10) Channel_11_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 11) Channel_12_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 12) Channel_13_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 13) Channel_14_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 14) Channel_15_alarm = Slider2->GetValue();
                if (Choice5->GetSelection() == 15) Channel_16_alarm = Slider2->GetValue();
            }
        }//end if isalarm
        alarm_increment--;
        if (alarm_increment == 0){
            if (alarm_beat == 1) alarm_beat = 2;
            else alarm_beat = 1;
            alarm_calculateincrements();
        }
/*

        if (alarm_stop) {
            alarm_stop = false;
            Button2->Enable(false);


            Channel_1_alarm = alarm_ProfileChannel_1;
            Channel_2_alarm = alarm_ProfileChannel_2;
            Channel_3_alarm = alarm_ProfileChannel_3;
            Channel_4_alarm = alarm_ProfileChannel_4;
            Channel_5_alarm = alarm_ProfileChannel_5;
            Channel_6_alarm = alarm_ProfileChannel_6;
            Channel_7_alarm = alarm_ProfileChannel_7;
            Channel_8_alarm = alarm_ProfileChannel_8;
            Channel_9_alarm = alarm_ProfileChannel_9;
            Channel_10_alarm = alarm_ProfileChannel_10;
            Channel_11_alarm = alarm_ProfileChannel_11;
            Channel_12_alarm = alarm_ProfileChannel_12;
            Channel_13_alarm = alarm_ProfileChannel_13;
            Channel_14_alarm = alarm_ProfileChannel_14;
            Channel_15_alarm = alarm_ProfileChannel_15;
            Channel_16_alarm = alarm_ProfileChannel_16;

            isalarm = false;

        }
    */
    }

//}

void AlarmClock::OnChoice2Select(wxCommandEvent& event)
{
}

void AlarmClock::OnChoice7Select(wxCommandEvent& event)
{
}

/*

*/
//set alarm button


void AlarmClock::OnButton3Click1(wxCommandEvent& event)
{
    alarmhour = Choice1->GetSelection() + 1;
    alarmminute = Choice2->GetSelection();
    alarmampm = Choice3->GetSelection();

    //wxString displayValuehour = wxString::Format(wxT("%i"),Choice1->GetLabel());
    //wxString displayValueminute = wxString::Format(wxT("%i"),Choice2->GetSelection());
    //wxString displayValueampm = wxString::Format(wxT("%i"),Choice3->GetSelection());

    alarmtime = Choice1->GetString(Choice1->GetSelection()) + wxT(":") + Choice2->GetString(Choice2->GetSelection()) + wxT(" ") + Choice3->GetString(Choice3->GetSelection());
    StaticText4->SetLabel(alarmtime);
}

//activate alarm button / stop alarm button
void AlarmClock::OnButton1Click(wxCommandEvent& event)
{
    if (alarm_is_active){
        alarm_is_active = false;
        if (alarm_is_animating) alarm_stop = true;
        Button1->SetLabel(wxT("Activate Alarm"));

        //enable dialog section start
        Choice1->Enable(true);
        Choice2->Enable(true);
        Choice3->Enable(true);
        Choice4->Enable(true);
        Choice5->Enable(true);
        Choice6->Enable(true);
        Button3->Enable(true);
        Slider1->Enable(true);
        Slider2->Enable(true);
        StaticBox1->Enable(true);
        StaticBox2->Enable(true);
        StaticText5->Enable(true);
        StaticText6->Enable(true);
        StaticText7->Enable(true);
        StaticText9->Enable(true);
        StaticText10->Enable(true);
        StaticText11->Enable(true);
        StaticText12->Enable(true);

        if (isalarm) {
            alarm_stop = false;
            Button2->Enable(false);


            Channel_1_alarm = alarm_ProfileChannel_1;
            Channel_2_alarm = alarm_ProfileChannel_2;
            Channel_3_alarm = alarm_ProfileChannel_3;
            Channel_4_alarm = alarm_ProfileChannel_4;
            Channel_5_alarm = alarm_ProfileChannel_5;
            Channel_6_alarm = alarm_ProfileChannel_6;
            Channel_7_alarm = alarm_ProfileChannel_7;
            Channel_8_alarm = alarm_ProfileChannel_8;
            Channel_9_alarm = alarm_ProfileChannel_9;
            Channel_10_alarm = alarm_ProfileChannel_10;
            Channel_11_alarm = alarm_ProfileChannel_11;
            Channel_12_alarm = alarm_ProfileChannel_12;
            Channel_13_alarm = alarm_ProfileChannel_13;
            Channel_14_alarm = alarm_ProfileChannel_14;
            Channel_15_alarm = alarm_ProfileChannel_15;
            Channel_16_alarm = alarm_ProfileChannel_16;

            alarm_is_active = false;
            alarm_is_animating = false;
        }
    }
    else {
        alarm_is_active = true;
        //isalarm = true;
        alarminit = true;
        alarm_stop = false;
        Button1->SetLabel(wxT("Deactivate Alarm"));

        //disable dialog section start
        Choice1->Enable(false);
        Choice2->Enable(false);
        Choice3->Enable(false);
        Choice4->Enable(false);
        Choice5->Enable(false);
        Choice6->Enable(false);
        Button3->Enable(false);
        Slider1->Enable(false);
        Slider2->Enable(false);
        StaticBox1->Enable(false);
        StaticBox2->Enable(false);
        StaticText5->Enable(false);
        StaticText6->Enable(false);
        StaticText7->Enable(false);
        StaticText9->Enable(false);
        StaticText10->Enable(false);
        StaticText11->Enable(false);
        StaticText12->Enable(false);

        alarm_calculateincrements();

    }

}

//snooze button
void AlarmClock::OnButton2Click(wxCommandEvent& event)
{
    alarm_is_animating = false;
    snoozehandler();
}

void AlarmClock::snoozehandler (void)
{
    int snoozeadd;
    //this translates snooze selection into actual minute values
    if (Choice7->GetSelection() == 0) snoozeadd = 1;
    if (Choice7->GetSelection() == 1) snoozeadd = 2;
    if (Choice7->GetSelection() == 2) snoozeadd = 5;
    if (Choice7->GetSelection() == 3) snoozeadd = 10;
    if (Choice7->GetSelection() == 4) snoozeadd = 15;
    if (Choice7->GetSelection() == 5) snoozeadd = 20;
    //wxString wxt_test = wxString::Format(wxT("%i"), alarmminute);
   // wxMessageBox( wxt_test, wxT("wtf"));

    int snoozeadded = snoozeadd + wxAtoi(wxDateTime::Now().Format(wxT("%M")));
    if (snoozeadded > 59){
        snoozeadded = snoozeadded - 60;
        alarmhour++;
        //this if condition changes between am and pm on the alarm time
        if (alarmhour == 12) {
            if (alarmampm) alarmampm = false;
            else alarmampm = true;
        }
        //this condition sets the hour to 1 if it goes past 12
        if (alarmhour > 12) alarmhour = 1;
    }

    alarmminute = snoozeadded;
    alarm_stop = true;

    //converts data into strings for display
    wxString wxt_alarmhour = wxString::Format(wxT("%i"), alarmhour);
    wxString wxt_alarmminute = wxString::Format(wxT("%i"), alarmminute);
    wxString wxt_alarmampm;
    if (!alarmampm) wxt_alarmampm = wxT("AM");
    else  wxt_alarmampm = wxT("PM");

    //this adds leading zero to hour value if 1-9
    wxString wxt_paddedhour = wxT("0") + wxt_alarmhour;
    wxt_paddedhour = wxt_paddedhour.substr( wxt_paddedhour.length() - 2 );
    //this adds leading zero to minute value if 0-9
    wxString wxt_paddedminute = wxT("0") + wxt_alarmminute;
    wxt_paddedminute = wxt_paddedminute.substr( wxt_paddedminute.length() - 2 );

    alarmtime = wxt_paddedhour + wxT(":") + wxt_paddedminute + wxT(" ") + wxt_alarmampm;
    StaticText4->SetLabel(alarmtime);
    Button2->Enable(false);

    //if (alarm_stop) {
        alarm_stop = false;
        Button2->Enable(false);


        Channel_1_alarm = alarm_ProfileChannel_1;
        Channel_2_alarm = alarm_ProfileChannel_2;
        Channel_3_alarm = alarm_ProfileChannel_3;
        Channel_4_alarm = alarm_ProfileChannel_4;
        Channel_5_alarm = alarm_ProfileChannel_5;
        Channel_6_alarm = alarm_ProfileChannel_6;
        Channel_7_alarm = alarm_ProfileChannel_7;
        Channel_8_alarm = alarm_ProfileChannel_8;
        Channel_9_alarm = alarm_ProfileChannel_9;
        Channel_10_alarm = alarm_ProfileChannel_10;
        Channel_11_alarm = alarm_ProfileChannel_11;
        Channel_12_alarm = alarm_ProfileChannel_12;
        Channel_13_alarm = alarm_ProfileChannel_13;
        Channel_14_alarm = alarm_ProfileChannel_14;
        Channel_15_alarm = alarm_ProfileChannel_15;
        Channel_16_alarm = alarm_ProfileChannel_16;

        //isalarm = false;
   // }
}

//time change alarm setting
void AlarmClock::OnChoice6Select(wxCommandEvent& event)
{
    alarm_calculateincrements();
    alarmlightchangetime = Choice6->GetSelection();
}

void AlarmClock::alarm_calculateincrements(void)
{
    if (Choice6->GetSelection() == 0) alarm_increment = 5;
    if (Choice6->GetSelection() == 1) alarm_increment = 10;
    if (Choice6->GetSelection() == 2) alarm_increment = 20;
    if (Choice6->GetSelection() == 3) alarm_increment = 30;
}

void AlarmClock::OnClose(wxCloseEvent& event)
{
        alarm_stop = false;
        Timer1.Stop();

        Channel_1_alarm = alarm_ProfileChannel_1;
        Channel_2_alarm = alarm_ProfileChannel_2;
        Channel_3_alarm = alarm_ProfileChannel_3;
        Channel_4_alarm = alarm_ProfileChannel_4;
        Channel_5_alarm = alarm_ProfileChannel_5;
        Channel_6_alarm = alarm_ProfileChannel_6;
        Channel_7_alarm = alarm_ProfileChannel_7;
        Channel_8_alarm = alarm_ProfileChannel_8;
        Channel_9_alarm = alarm_ProfileChannel_9;
        Channel_10_alarm = alarm_ProfileChannel_10;
        Channel_11_alarm = alarm_ProfileChannel_11;
        Channel_12_alarm = alarm_ProfileChannel_12;
        Channel_13_alarm = alarm_ProfileChannel_13;
        Channel_14_alarm = alarm_ProfileChannel_14;
        Channel_15_alarm = alarm_ProfileChannel_15;
        Channel_16_alarm = alarm_ProfileChannel_16;
        alarm_saveprofiles();
        isalarm = false;
        isprofilemode = true;
        Destroy();

}

void AlarmClock::alarm_loadprofiles(void)
{
    wxTextFile acfile;
    acfile.Open(alarmfilename, wxConvISO8859_1);

    wxString buffer;

    buffer = acfile.GetFirstLine();
    alarmhour = wxAtoi(buffer);

    buffer = acfile.GetNextLine();
    alarmminute = wxAtoi(buffer);

    buffer = acfile.GetNextLine();
    alarmampm = wxAtoi(buffer);

    buffer = acfile.GetNextLine();
    alarmlightchangetime = wxAtoi(buffer);

    buffer = acfile.GetNextLine();
    step1channel = wxAtoi(buffer);

    buffer = acfile.GetNextLine();
    step1value = wxAtoi(buffer);

    buffer = acfile.GetNextLine();
    step2channel = wxAtoi(buffer);

    buffer = acfile.GetNextLine();
    step2value = wxAtoi(buffer);

    buffer = acfile.GetNextLine();
    snoozelength = wxAtoi(buffer);

    Choice1->SetSelection(alarmhour-1);
    Choice2->SetSelection(alarmminute);
    Choice3->SetSelection(alarmampm);
    Choice6->SetSelection(alarmlightchangetime);
    Choice4->SetSelection(step1channel);
    Slider1->SetValue(step1value);
    Choice5->SetSelection(step2channel);
    Slider2->SetValue(step2value);
    Choice7->SetSelection(snoozelength);

    wxt_Slider1 = wxString::Format(wxT("%i"),step1value);
    StaticText11->SetLabel(wxt_Slider1);
    wxt_Slider2 = wxString::Format(wxT("%i"),step2value);
    StaticText12->SetLabel(wxt_Slider2);
}

void AlarmClock::alarm_saveprofiles(void)
 {
    wxString ac1;
    wxString ac2;
    wxString ac3;
    wxString ac4;
    wxString ac5;
    wxString ac6;
    wxString ac7;
    wxString ac8;
    wxString ac9;

    wxTextFile sacfile;
    sacfile.Create(alarmfilename);

    ac1 = wxString::Format(wxT("%i"),alarmhour);
    ac2 = wxString::Format(wxT("%i"),alarmminute);
    ac3 = wxString::Format(wxT("%i"),alarmampm);
    ac4 = wxString::Format(wxT("%i"),alarmlightchangetime);
    ac5 = wxString::Format(wxT("%i"),step1channel);
    ac6 = wxString::Format(wxT("%i"),step1value);
    ac7 = wxString::Format(wxT("%i"),step2channel);
    ac8 = wxString::Format(wxT("%i"),step2value);
    ac9 = wxString::Format(wxT("%i"),snoozelength);

    sacfile.AddLine(ac1, wxTextFileType_Dos);
    sacfile.AddLine(ac2, wxTextFileType_Dos);
    sacfile.AddLine(ac3, wxTextFileType_Dos);
    sacfile.AddLine(ac4, wxTextFileType_Dos);
    sacfile.AddLine(ac5, wxTextFileType_Dos);
    sacfile.AddLine(ac6, wxTextFileType_Dos);
    sacfile.AddLine(ac7, wxTextFileType_Dos);
    sacfile.AddLine(ac8, wxTextFileType_Dos);
    sacfile.AddLine(ac9, wxTextFileType_Dos);

    //these lines save and close the file
    sacfile.Write(wxTextFileType_Dos, wxConvISO8859_1);
    sacfile.Close();

}
//step 1 channel select
void AlarmClock::OnChoice4Select(wxCommandEvent& event)
{
    step1channel = Choice4->GetSelection();
}

void AlarmClock::OnSlider1CmdScroll(wxScrollEvent& event)
{
        step1value = Slider1->GetValue();
        wxt_Slider1 = wxString::Format(wxT("%i"),Slider1->GetValue());
        StaticText11->SetLabel(wxt_Slider1);
}


//step 2 channel select
void AlarmClock::OnChoice5Select(wxCommandEvent& event)
{
    step2channel = Choice5->GetSelection();
}


void AlarmClock::OnSlider2CmdScroll(wxScrollEvent& event)
{
    step2value = Slider2->GetValue();
    wxt_Slider2 = wxString::Format(wxT("%i"),Slider2->GetValue());
    StaticText12->SetLabel(wxt_Slider2);
}

void AlarmClock::OnChoice7Select1(wxCommandEvent& event)
{
    snoozelength = Choice7->GetSelection();
}

void AlarmClock::OnSlider2CmdScroll1(wxScrollEvent& event)
{
}

void AlarmClock::OnChoice3Select(wxCommandEvent& event)
{
}


void AlarmClock::OnButton4Click(wxCommandEvent& event)
{
   //used for windows minimize fix
    isIconize = true;

}

