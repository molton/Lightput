#include "bsDeleteProfile.h"

//(*InternalHeaders(bsDeleteProfile)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

extern bool bsyesorno;

//(*IdInit(bsDeleteProfile)
const long bsDeleteProfile::ID_STATICTEXT1 = wxNewId();
const long bsDeleteProfile::ID_BUTTON1 = wxNewId();
const long bsDeleteProfile::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(bsDeleteProfile,wxDialog)
	//(*EventTable(bsDeleteProfile)
	//*)
END_EVENT_TABLE()

bsDeleteProfile::bsDeleteProfile(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(bsDeleteProfile)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(342,117));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Are you sure you want to delete the selected profile\?"), wxPoint(32,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Yes"), wxPoint(32,72), wxSize(96,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("No"), wxPoint(216,72), wxSize(91,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bsDeleteProfile::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bsDeleteProfile::OnButton2Click);
	//*)

	bsyesorno = false;
}

bsDeleteProfile::~bsDeleteProfile()
{
	//(*Destroy(bsDeleteProfile)
	//*)
}

//yes button
void bsDeleteProfile::OnButton1Click(wxCommandEvent& event)
{
    bsyesorno = true;
    Destroy();
}

//no button
void bsDeleteProfile::OnButton2Click(wxCommandEvent& event)
{
    bsyesorno = false;
    Destroy();
}
