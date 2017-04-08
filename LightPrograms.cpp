#include "LightPrograms.h"

//(*InternalHeaders(LightPrograms)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)
#include <wx/msgdlg.h>
#include "BlinkSequencer.h"
#include "AlarmClock.h"
#include "H24Timer.h"
#include "VSXuAudioVisualizer.h"
#include "MidiControl.h"
#include "LightScripts.h"
#include "ExtenalInput.h"

//(*IdInit(LightPrograms)
const long LightPrograms::ID_BUTTON1 = wxNewId();
const long LightPrograms::ID_BUTTON4 = wxNewId();
const long LightPrograms::ID_BUTTON2 = wxNewId();
const long LightPrograms::ID_BUTTON5 = wxNewId();
const long LightPrograms::ID_BUTTON7 = wxNewId();
const long LightPrograms::ID_BUTTON3 = wxNewId();
const long LightPrograms::ID_BUTTON8 = wxNewId();
const long LightPrograms::ID_BUTTON6 = wxNewId();
//*)

extern bool isprofilemode;
extern bool isbs;
extern bool istimeractive;
extern bool isVSXumode;
extern bool isMidiControlmode;
extern bool isLightScripts;
//the alarm does it;s own thing

extern bool is24hmode;
extern bool islightsequencer;
extern bool hasVSXurunonce;
extern bool isExternalInput;

extern bool islightprogramonstartup;
extern unsigned short int startuplightprogram;

unsigned short int count;

BEGIN_EVENT_TABLE(LightPrograms,wxDialog)
	//(*EventTable(LightPrograms)
	//*)
END_EVENT_TABLE()

LightPrograms::LightPrograms(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(LightPrograms)
	Create(parent, wxID_ANY, _("Light Programs"), wxDefaultPosition, wxDefaultSize, wxCAPTION, _T("wxID_ANY"));
	SetClientSize(wxSize(283,305));
	Move(wxPoint(200,200));
	LightSequencerButton = new wxButton(this, ID_BUTTON1, _("Light\nSequencer"), wxPoint(24,24), wxSize(104,40), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	LightSequencerButton->Disable();
	wxFont LightSequencerButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	LightSequencerButton->SetFont(LightSequencerButtonFont);
	LightScriptsButton = new wxButton(this, ID_BUTTON4, _("Light Scripts"), wxPoint(24,80), wxSize(104,40), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	LightScriptsButton->Disable();
	wxFont LightScriptsButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	LightScriptsButton->SetFont(LightScriptsButtonFont);
	LightAlarmClockButton = new wxButton(this, ID_BUTTON2, _("Light\nAlarm Clock"), wxPoint(24,192), wxSize(104,40), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	LightAlarmClockButton->Disable();
	wxFont LightAlarmClockButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	LightAlarmClockButton->SetFont(LightAlarmClockButtonFont);
	H24TimerButton = new wxButton(this, ID_BUTTON5, _("24-Hour \nLight Timer"), wxPoint(24,136), wxSize(104,40), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	H24TimerButton->Disable();
	wxFont H24TimerButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	H24TimerButton->SetFont(H24TimerButtonFont);
	MidiButton = new wxButton(this, ID_BUTTON7, _("Midi\nControl"), wxPoint(152,80), wxSize(104,40), 0, wxDefaultValidator, _T("ID_BUTTON7"));
	MidiButton->Disable();
	wxFont MidiButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	MidiButton->SetFont(MidiButtonFont);
	VSXuButton = new wxButton(this, ID_BUTTON3, _("Lightput\nExternal Input"), wxPoint(152,136), wxSize(104,40), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	VSXuButton->Disable();
	wxFont VSXuButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	VSXuButton->SetFont(VSXuButtonFont);
	CloseButton = new wxButton(this, ID_BUTTON8, _("Close"), wxPoint(88,248), wxSize(104,40), 0, wxDefaultValidator, _T("ID_BUTTON8"));
	CloseButton->Disable();
	wxFont CloseButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CloseButton->SetFont(CloseButtonFont);
	ActualVSXuButton = new wxButton(this, ID_BUTTON6, _("VSXu Audio\nVisualizer"), wxPoint(152,24), wxSize(104,40), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	ActualVSXuButton->Disable();
	wxFont ActualVSXuButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	ActualVSXuButton->SetFont(ActualVSXuButtonFont);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightPrograms::OnButton1Click);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightPrograms::OnButton4Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightPrograms::OnButton2Click);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightPrograms::OnButton5Click);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightPrograms::OnMidiButtonClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightPrograms::OnButton3Click);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightPrograms::OnButton8Click);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LightPrograms::OnActualVSXuButtonClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&LightPrograms::OnClose);
	//*)

    is24hmode = false;
    isbs = false;
    isVSXumode = false;
    isprofilemode = false;
    EnableButtons();

/*
    //wxMessageBox(wxT("test"),wxT("test0"));
    if (islightprogramonstartup)
    {
        //wxMessageBox(wxT("test"),wxT("test1"));
        for (int i = 0; i < 10; i++)
        {
            if (startuplightprogram == 0) ///Light Sequencer
            {
                isbs = true;
               // isprofilemode = false;
                DisableButtons();
                 islightsequencer = true;
                //BlinkSequencer sDlg(0);
               // sDlg.ShowModal();
               //wxMessageBox(wxT("test"),wxT("test2"));
                BlinkSequencer *bsDlg = new BlinkSequencer(0);
                bsDlg->ShowModal();

                isbs = false;
                isprofilemode = true;
                //EnableButtons();
            }
            if (startuplightprogram == 1) ///Light Alarm Clock
            {
               // isprofilemode = false;
                DisableButtons();
                //AlarmClock acDlg(0);
                //acDlg.ShowModal();
                AlarmClock *acDlg = new AlarmClock(0);
                acDlg->Show();
                isprofilemode = true;
                //EnableButtons();
            }
            if (startuplightprogram == 2) ///24-Hour Light Timer
            {
               // isprofilemode = false;
                DisableButtons();
                is24hmode = true;
                H24Timer *h24Dlg = new H24Timer(0);
                h24Dlg->Show();
                //H24Timer h24Dlg(0);
                //h24Dlg.ShowModal();
                //EnableButtons();
                istimeractive = false;
            }
            if (startuplightprogram == 3) ///Midi Control
            {
                //isprofilemode = false;
                DisableButtons();
                isMidiControlmode = true;
                MidiControl *MidiDlg = new MidiControl(0);
                MidiDlg->Show();
                //MidiControl MidiDlg(0);
                //MidiDlg.ShowModal();
                //EnableButtons();

            }
            if (startuplightprogram == 4) ///Lightput External Input
            {
                DisableButtons();
                //isprofilemode = false;
                isExternalInput = true;
                ExtenalInput *eiDlg = new ExtenalInput(0);
                eiDlg->Show();
                //ExtenalInput EIDlg(0);
                //EIDlg.ShowModal();
                //EnableButtons();
            }
        }
    islightprogramonstartup = false;
    EnableButtons();
    }
*/
}


LightPrograms::~LightPrograms()
{
	//(*Destroy(LightPrograms)
	//*)
}

//blink sequencer button
void LightPrograms::OnButton1Click(wxCommandEvent& event)
{
    isbs = true;
    isprofilemode = false;
    DisableButtons();
    islightsequencer = true;
    BlinkSequencer sDlg(0);
    sDlg.ShowModal();
    isbs = false;
    isprofilemode = true;
    EnableButtons();
}


void LightPrograms::OnClose(wxCloseEvent& event)
{
    //lets notify function know this is going back to profile mode
    //isprofilemode = true;
    LightPrograms Dlg(0);
    Dlg.AcceptAndClose();
    //Destroy();
}
//Light Alarm Clock button
void LightPrograms::OnButton2Click(wxCommandEvent& event)
{
    isprofilemode = false;
    DisableButtons();
    AlarmClock acDlg(0);
    acDlg.ShowModal();
    isprofilemode = true;
    EnableButtons();

}

//light scripts button
void LightPrograms::OnButton4Click(wxCommandEvent& event)
{
    isprofilemode = false;
    DisableButtons();
    isLightScripts = true;

    LightScripts lsDlg(0);
    lsDlg.ShowModal();

    isLightScripts = false;
    EnableButtons();
    isprofilemode = true;
}

void LightPrograms::OnButton8Click(wxCommandEvent& event)
{
    //isprofilemode = true;

    Destroy();
}
//24- hour light program button
void LightPrograms::OnButton5Click(wxCommandEvent& event)
{
    isprofilemode = false;
    DisableButtons();
    is24hmode = true;
    H24Timer h24Dlg(0);
    h24Dlg.ShowModal();

    EnableButtons();
    //if (istimeractive) Destroy();
    istimeractive = false;
}

//VSXu button
void LightPrograms::OnButton3Click(wxCommandEvent& event)
{
    DisableButtons();
    isprofilemode = false;
    isExternalInput = true;
    //VSXuAudioVisualizer VSXuDlg(0);
    //VSXuDlg.ShowModal();
    ExtenalInput EIDlg(0);
    EIDlg.ShowModal();

    isExternalInput = false;
    isprofilemode = true;
   // isVSXumode = false;
    EnableButtons();
}

void LightPrograms::DisableButtons (void)
{

    ///disable any other running programs that don't switch back colors at the light program menu
    is24hmode = false;
    isMidiControlmode = false;
    isExternalInput = false;

    LightSequencerButton->Enable(false);
    LightAlarmClockButton->Enable(false);
    H24TimerButton->Enable(false);
    LightScriptsButton->Enable(false);
    VSXuButton->Enable(false);
    MidiButton->Enable(false);
    ActualVSXuButton->Enable(false);
    CloseButton->Enable(false);
}

void LightPrograms::EnableButtons (void)
{
    LightSequencerButton->Enable(true);
    LightAlarmClockButton->Enable(true);
    H24TimerButton->Enable(true);
    LightScriptsButton->Enable(true);
    VSXuButton->Enable(true);
    MidiButton->Enable(true);
    ActualVSXuButton->Enable(true);
    CloseButton->Enable(true);
}



void LightPrograms::OnMidiButtonClick(wxCommandEvent& event)
{

    isprofilemode = false;
    DisableButtons();
    isMidiControlmode = true;

    MidiControl MidiDlg(0);
    MidiDlg.ShowModal();
    EnableButtons();

}



void LightPrograms::OnActualVSXuButtonClick(wxCommandEvent& event)
{
    DisableButtons();
    isprofilemode = false;

    VSXuAudioVisualizer VSXuDlg(0);
    VSXuDlg.ShowModal();


    isprofilemode = true;
    isVSXumode = false;
    EnableButtons();
}
