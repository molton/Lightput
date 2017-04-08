#include "H24DeleteProfile.h"

//(*InternalHeaders(H24DeleteProfile)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

extern bool timeryesorno;

//(*IdInit(H24DeleteProfile)
const long H24DeleteProfile::ID_STATICTEXT1 = wxNewId();
const long H24DeleteProfile::ID_BUTTON1 = wxNewId();
const long H24DeleteProfile::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(H24DeleteProfile,wxDialog)
	//(*EventTable(H24DeleteProfile)
	//*)
END_EVENT_TABLE()

H24DeleteProfile::H24DeleteProfile(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(H24DeleteProfile)
	Create(parent, id, _("Delete Profile\?"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(400,124));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Are you sure you want to delete the selected profile\?"), wxPoint(56,32), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Yes"), wxPoint(48,80), wxSize(96,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("No"), wxPoint(256,80), wxSize(91,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24DeleteProfile::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24DeleteProfile::OnButton2Click);
	//*)

	timeryesorno = false;
}

H24DeleteProfile::~H24DeleteProfile()
{
	//(*Destroy(H24DeleteProfile)
	//*)
}

//yes button
void H24DeleteProfile::OnButton1Click(wxCommandEvent& event)
{
    timeryesorno = true;
    Destroy();
}

//no button
void H24DeleteProfile::OnButton2Click(wxCommandEvent& event)
{
    timeryesorno = false;
    Destroy();
}
