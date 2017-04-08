#include "H24AddNewProfile.h"

//(*InternalHeaders(H24AddNewProfile)
#include <wx/string.h>
#include <wx/intl.h>
//*)

extern bool timeryesorno;

//(*IdInit(H24AddNewProfile)
const long H24AddNewProfile::ID_STATICTEXT1 = wxNewId();
const long H24AddNewProfile::ID_TEXTCTRL1 = wxNewId();
const long H24AddNewProfile::ID_BUTTON1 = wxNewId();
const long H24AddNewProfile::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(H24AddNewProfile,wxDialog)
	//(*EventTable(H24AddNewProfile)
	//*)
END_EVENT_TABLE()

H24AddNewProfile::H24AddNewProfile(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(H24AddNewProfile)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(400,140));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Enter a name for the new profile"), wxPoint(24,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("New Profile"), wxPoint(24,48), wxSize(344,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl1->SetFocus();
	Button1 = new wxButton(this, ID_BUTTON1, _("Ok"), wxPoint(24,96), wxSize(136,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(232,96), wxSize(136,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24AddNewProfile::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24AddNewProfile::OnButton2Click);
	//*)
    timeryesorno = false;
}

H24AddNewProfile::~H24AddNewProfile()
{
	//(*Destroy(H24AddNewProfile)
	//*)
}

//ok button
void H24AddNewProfile::OnButton1Click(wxCommandEvent& event)
{
    timeryesorno = true;
    Destroy();
}

void H24AddNewProfile::OnButton2Click(wxCommandEvent& event)
{
    timeryesorno = false;
    Destroy();
}
