#include "bsAddNewProfile.h"

//(*InternalHeaders(bsAddNewProfile)
#include <wx/string.h>
#include <wx/intl.h>
//*)

extern bool bsyesorno;

//(*IdInit(bsAddNewProfile)
const long bsAddNewProfile::ID_STATICTEXT1 = wxNewId();
const long bsAddNewProfile::ID_TEXTCTRL1 = wxNewId();
const long bsAddNewProfile::ID_BUTTON1 = wxNewId();
const long bsAddNewProfile::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(bsAddNewProfile,wxDialog)
	//(*EventTable(bsAddNewProfile)
	//*)
END_EVENT_TABLE()

bsAddNewProfile::bsAddNewProfile(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(bsAddNewProfile)
	Create(parent, id, _("New Profile"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(400,126));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Enter a name for the new profile."), wxPoint(40,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("New Profile"), wxPoint(40,40), wxSize(320,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Ok"), wxPoint(40,80), wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(248,80), wxSize(115,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bsAddNewProfile::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bsAddNewProfile::OnButton2Click);
	//*)
	bsyesorno = false;
}

bsAddNewProfile::~bsAddNewProfile()
{
	//(*Destroy(bsAddNewProfile)
	//*)
}

//ok button
void bsAddNewProfile::OnButton1Click(wxCommandEvent& event)
{
    bsyesorno = true;
    Destroy();
}

//cancel button
void bsAddNewProfile::OnButton2Click(wxCommandEvent& event)
{
    bsyesorno = false;
    Destroy();
}
