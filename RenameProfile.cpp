#include "RenameProfile.h"

//(*InternalHeaders(RenameProfile)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/msgdlg.h>

//(*IdInit(RenameProfile)
const long RenameProfile::ID_STATICTEXT1 = wxNewId();
const long RenameProfile::ID_TEXTCTRL1 = wxNewId();
const long RenameProfile::ID_BUTTON1 = wxNewId();
const long RenameProfile::ID_BUTTON2 = wxNewId();
//*)
extern wxString Value [64];
extern wxString SequencerProfileNames [64];
extern int currentprofile;
extern int sequencercurrentprofile;
extern bool yesorno;
extern bool isprofilemode;

BEGIN_EVENT_TABLE(RenameProfile,wxDialog)
	//(*EventTable(RenameProfile)
	//*)
END_EVENT_TABLE()

RenameProfile::RenameProfile(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(RenameProfile)
	Create(parent, wxID_ANY, _("Rename Profile"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(362,120));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Enter new profile name"), wxPoint(32,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxPoint(32,48), wxSize(296,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl1->SetFocus();
	Button1 = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(40,88), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(192,88), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Center();
	
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&RenameProfile::OnTextCtrl1Text);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RenameProfile::OnButton1Click1);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RenameProfile::OnButton2Click1);
	//*)
	if (isprofilemode) TextCtrl1->SetValue(Value[currentprofile]);
    else TextCtrl1->SetValue(SequencerProfileNames [sequencercurrentprofile + 1]);
}

RenameProfile::~RenameProfile()
{
	//(*Destroy(RenameProfile)
	//*)
}

//Ok button
void RenameProfile::OnButton1Click(wxCommandEvent& event)
{
    //if (!isprofilemode) SequencerProfileNames [sequencercurrentprofile] = TextCtrl1->GetValue();
}

//cancel button
void RenameProfile::OnButton2Click(wxCommandEvent& event)
{

}

void RenameProfile::OnButton2Click1(wxCommandEvent& event)
{
    yesorno = false;
    Destroy();
}

void RenameProfile::OnTextCtrl1Text(wxCommandEvent& event)
{

}

void RenameProfile::OnButton1Click1(wxCommandEvent& event)
{

if (!isprofilemode) {
    //SequencerProfileNames [sequencercurrentprofile+1] = TextCtrl1->GetValue();
    yesorno = true;
    Destroy();
    }
else {
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
    if ((pos == -1 && vpos == -1) && TextCtrl1->GetValue() != wxT("")){
        yesorno = true;
        Destroy();
        }
    else wxMessageBox(wxT("Please enter a name for the profile.  The name can't contain exclamation points or at symbols '@', please take any of those out of the name and try again."), _("Changes needed"));
    }
}
