#include "bsProfileOverwrite.h"

//(*InternalHeaders(bsProfileOverwrite)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

extern bool bsyesorno;
extern bool bscancel;
int control_5;

//(*IdInit(bsProfileOverwrite)
const long bsProfileOverwrite::ID_STATICTEXT1 = wxNewId();
const long bsProfileOverwrite::ID_BUTTON1 = wxNewId();
const long bsProfileOverwrite::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(bsProfileOverwrite,wxDialog)
	//(*EventTable(bsProfileOverwrite)
	//*)
END_EVENT_TABLE()

bsProfileOverwrite::bsProfileOverwrite(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(bsProfileOverwrite)
	Create(parent, wxID_ANY, _("Save or Cancel Changes"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(378,111));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Would you like to save the changes made to the Light \nSequencer profiles or do you want to cancel the changes\?"), wxPoint(32,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Save Changes"), wxPoint(24,64), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel Changes"), wxPoint(216,64), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bsProfileOverwrite::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bsProfileOverwrite::OnButton2Click1);
	//*)
	bsyesorno = false;
	bscancel = true;
	control_5 = 0;
}

bsProfileOverwrite::~bsProfileOverwrite()
{
	//(*Destroy(bsProfileOverwrite)
	//*)
}

//save changes button
void bsProfileOverwrite::OnButton1Click(wxCommandEvent& event)
{
    bsyesorno = true;
    bscancel = false;
    control_5 = 1;
    Destroy();
}

//weird confusing glitch with wxsmith
void bsProfileOverwrite::OnButton2Click(wxCommandEvent& event)
{

}


//cancel changes
void bsProfileOverwrite::OnButton2Click1(wxCommandEvent& event)
{
    bsyesorno = false;
    bscancel = false;
    control_5 = 2;
    Destroy();
}
