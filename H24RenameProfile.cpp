#include "H24RenameProfile.h"

//(*InternalHeaders(H24RenameProfile)
#include <wx/intl.h>
#include <wx/string.h>
//*)

extern bool timeryesorno;
extern wxString H24RenameNameHolder;

//(*IdInit(H24RenameProfile)
const long H24RenameProfile::ID_TEXTCTRL1 = wxNewId();
const long H24RenameProfile::ID_STATICTEXT1 = wxNewId();
const long H24RenameProfile::ID_BUTTON1 = wxNewId();
const long H24RenameProfile::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(H24RenameProfile,wxDialog)
	//(*EventTable(H24RenameProfile)
	//*)
END_EVENT_TABLE()

H24RenameProfile::H24RenameProfile(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(H24RenameProfile)
	Create(parent, wxID_ANY, _("Rename selected profile"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(376,131));
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(32,48), wxSize(296,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl1->SetFocus();
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Enter the new name for the selected profile"), wxPoint(32,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Ok"), wxPoint(32,88), wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel\n"), wxPoint(208,88), wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24RenameProfile::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24RenameProfile::OnButton2Click);
	//*)

    timeryesorno = false;
    TextCtrl1->SetValue(H24RenameNameHolder);
}


H24RenameProfile::~H24RenameProfile()
{
	//(*Destroy(H24RenameProfile)
	//*)
}

//ok button
void H24RenameProfile::OnButton1Click(wxCommandEvent& event)
{
    timeryesorno = true;
    Destroy();
}

void H24RenameProfile::OnButton2Click(wxCommandEvent& event)
{
    timeryesorno = false;
    Destroy();
}

void H24RenameProfile::OnTextCtrl1Text(wxCommandEvent& event)
{
}
