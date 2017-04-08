#include "H24CopyVerify.h"

//(*InternalHeaders(H24CopyVerify)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

extern bool copyyesorno;

//(*IdInit(H24CopyVerify)
const long H24CopyVerify::ID_STATICTEXT1 = wxNewId();
const long H24CopyVerify::ID_BUTTON1 = wxNewId();
const long H24CopyVerify::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(H24CopyVerify,wxDialog)
	//(*EventTable(H24CopyVerify)
	//*)
END_EVENT_TABLE()

H24CopyVerify::H24CopyVerify(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(H24CopyVerify)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(357,111));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Are you sure you want to copy the current hour settings\?"), wxPoint(24,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Yes"), wxPoint(24,64), wxSize(104,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("No"), wxPoint(224,64), wxSize(104,32), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24CopyVerify::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&H24CopyVerify::OnButton2Click);
	//*)
	copyyesorno = false;
}

H24CopyVerify::~H24CopyVerify()
{
	//(*Destroy(H24CopyVerify)
	//*)
}

//yes button
void H24CopyVerify::OnButton1Click(wxCommandEvent& event)
{
	copyyesorno = true;
	Destroy();
}

//no button
void H24CopyVerify::OnButton2Click(wxCommandEvent& event)
{
	copyyesorno = false;
	Destroy();
}
