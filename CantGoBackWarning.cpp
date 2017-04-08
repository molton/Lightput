#include "CantGoBackWarning.h"

//(*InternalHeaders(CantGoBackWarning)
#include <wx/string.h>
#include <wx/intl.h>
//*)

extern bool timeryesorno;

//(*IdInit(CantGoBackWarning)
const long CantGoBackWarning::ID_STATICTEXT1 = wxNewId();
const long CantGoBackWarning::ID_BUTTON1 = wxNewId();
const long CantGoBackWarning::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CantGoBackWarning,wxDialog)
	//(*EventTable(CantGoBackWarning)
	//*)
END_EVENT_TABLE()

CantGoBackWarning::CantGoBackWarning(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CantGoBackWarning)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(349,127));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Once Activated, the 24-Hour Timer stays locked on untill \nLightput is closed, do you want to continue\?"), wxPoint(32,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Yes"), wxPoint(32,80), wxSize(104,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("No"), wxPoint(208,80), wxSize(104,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Button2->SetFocus();
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CantGoBackWarning::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CantGoBackWarning::OnButton2Click);
	//*)

	timeryesorno = false;
}

CantGoBackWarning::~CantGoBackWarning()
{
	//(*Destroy(CantGoBackWarning)
	//*)
}

//yes button
void CantGoBackWarning::OnButton1Click(wxCommandEvent& event)
{
    timeryesorno = true;
    Destroy();
}

void CantGoBackWarning::OnButton2Click(wxCommandEvent& event)
{
    timeryesorno = false;
    Destroy();
}
