#include "AddNewProfile.h"

//(*InternalHeaders(AddNewProfile)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(AddNewProfile)
const long AddNewProfile::ID_STATICTEXT1 = wxNewId();
const long AddNewProfile::ID_TEXTCTRL1 = wxNewId();
const long AddNewProfile::ID_BUTTON1 = wxNewId();
const long AddNewProfile::ID_BUTTON2 = wxNewId();
//*)

extern bool yesorno;

BEGIN_EVENT_TABLE(AddNewProfile,wxDialog)
	//(*EventTable(AddNewProfile)
	//*)
END_EVENT_TABLE()

AddNewProfile::AddNewProfile(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AddNewProfile)
	Create(parent, id, _("Enter the new profile name (no \"!\" or \"@\" allowed)"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("id"));
	SetClientSize(wxSize(362,120));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Enter the name of the new profile"), wxPoint(32,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(32,48), wxSize(296,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl1->SetFocus();
	Button1 = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(40,88), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(192,88), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));

	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AddNewProfile::OnTextCtrl1Text);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AddNewProfile::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AddNewProfile::OnButton2Click);
	//*)

    yesorno = false;
}

AddNewProfile::~AddNewProfile()
{
	//(*Destroy(AddNewProfile)
	//*)
}


void AddNewProfile::OnTextCtrl1Text(wxCommandEvent& event)
{
}

void AddNewProfile::OnButton1Click(wxCommandEvent& event)
{

    //sets a wxChar to hold the comma to search for (used to be a comma)
    wxChar comma = wxT('!');
    wxChar atsymbol = wxT('@');

    int pos = 0;
    int vpos = 0;
    //wxCharBuffer buffer;
    //buffer = TextCtrl1->GetValue(); [profilecount].ToUTF8();

    //this line finds the 1st identifier in my save file format, the first
    //comma, to mark where the end of the first saved value. the profile name
    pos = TextCtrl1->GetValue().Find(comma,false);
    vpos = TextCtrl1->GetValue().Find(atsymbol,false);
    if ((pos == -1 && vpos == -1) && TextCtrl1->GetValue() != wxT("") ) {
        yesorno = true;
        Destroy();
    }
    else wxMessageBox(wxT("Please enter a name for the profile that does not contain exclamation points or @'s"), _("Changes needed"));



    //newprofileValue = TextCtrl1->GetValue();
}

void AddNewProfile::OnButton2Click(wxCommandEvent& event)
{
    TextCtrl1->SetValue(wxT("!"));
    Destroy();
}
