#include "bsRenameProfile.h"

//(*InternalHeaders(bsRenameProfile)
#include <wx/intl.h>
#include <wx/string.h>
//*)

extern bool bsyesorno;
extern wxString bsRenameNameHolder;

//(*IdInit(bsRenameProfile)
const long bsRenameProfile::ID_STATICTEXT1 = wxNewId();
const long bsRenameProfile::ID_TEXTCTRL1 = wxNewId();
const long bsRenameProfile::ID_BUTTON1 = wxNewId();
const long bsRenameProfile::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(bsRenameProfile,wxDialog)
	//(*EventTable(bsRenameProfile)
	//*)
END_EVENT_TABLE()

bsRenameProfile::bsRenameProfile(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(bsRenameProfile)
	Create(parent, id, _("Rename Profile"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(336,107));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Enter a new name for the selected profile."), wxPoint(24,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(24,40), wxSize(280,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Ok"), wxPoint(24,72), wxSize(96,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(208,72), wxSize(91,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bsRenameProfile::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bsRenameProfile::OnButton2Click);
	//*)

	bsyesorno = false;
	TextCtrl1->SetValue(bsRenameNameHolder);
}

bsRenameProfile::~bsRenameProfile()
{
	//(*Destroy(bsRenameProfile)
	//*)
}

//ok button
void bsRenameProfile::OnButton1Click(wxCommandEvent& event)
{
    bsyesorno = true;
    Destroy();
}

void bsRenameProfile::OnButton2Click(wxCommandEvent& event)
{
    bsyesorno = false;
    Destroy();
}
