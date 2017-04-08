#include "StopTimer.h"

//(*InternalHeaders(StopTimer)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//(*IdInit(StopTimer)
const long StopTimer::ID_STATICTEXT1 = wxNewId();
const long StopTimer::ID_BUTTON1 = wxNewId();
const long StopTimer::ID_BUTTON2 = wxNewId();
//*)

extern bool stopcancel;
extern bool stopyesorno;

int control_4;

BEGIN_EVENT_TABLE(StopTimer,wxDialog)
	//(*EventTable(StopTimer)
	//*)
END_EVENT_TABLE()

StopTimer::StopTimer(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(StopTimer)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(363,128));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Are you sure you want to stop the 24- Hour Timer\?"), wxPoint(40,32), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Yes"), wxPoint(32,80), wxSize(112,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("No"), wxPoint(224,80), wxSize(112,32), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Button2->SetFocus();
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StopTimer::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StopTimer::OnButton2Click);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&StopTimer::OnClose);
	//*)
	//stopyesorno = false;
	//stopcancel = false;
	//CheckBox1->SetValue(false);
	control_4 = 0;
	//StaticText1->SetFocus();
}

StopTimer::~StopTimer()
{
	//(*Destroy(StopTimer)
	//*)
}

//yes botton
void StopTimer::OnButton1Click(wxCommandEvent& event)
{
    stopyesorno = true;
	//CheckBox1->SetValue(true);
    control_4 = 1;
    //Choice1->SetSelection(1);
/*
    StopWatch1.Start(0);
    do {
        Button1->Enable(false);
        Button2->Enable(false);
    }
    while (StopWatch1.Time() < 2000);
    */
    Destroy();
}

void StopTimer::OnButton2Click(wxCommandEvent& event)
{
    stopyesorno = false;
	//CheckBox1->SetValue(false);
    control_4 = 2;
    //Choice1->SetSelection(2);
    /*
    StopWatch1.Start(0);
    do {
        Button1->Enable(false);
        Button2->Enable(false);
    }
    while (StopWatch1.Time() < 2000);
*/
    Destroy();

}

void StopTimer::OnClose(wxCloseEvent& event)
{
    if (control_4 == 0) {
        //Choice1->SetSelection(0);//stopcancel = true;
        stopyesorno = false;
    }
    Destroy();
}
