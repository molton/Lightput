#include "lsOverwriteScript.h"

//(*InternalHeaders(lsOverwriteScript)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

extern wxString ScriptName;

extern bool islsoverwrite;
extern bool control_6;

//(*IdInit(lsOverwriteScript)
const long lsOverwriteScript::ID_STATICTEXT1 = wxNewId();
const long lsOverwriteScript::ID_STATICTEXT2 = wxNewId();
const long lsOverwriteScript::ID_BUTTON1 = wxNewId();
const long lsOverwriteScript::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(lsOverwriteScript,wxDialog)
	//(*EventTable(lsOverwriteScript)
	//*)
END_EVENT_TABLE()

lsOverwriteScript::lsOverwriteScript(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(lsOverwriteScript)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(400,154));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Do you want to overwrite the current script file,"), wxPoint(56,32), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Label"), wxPoint(56,56), wxSize(256,17), wxALIGN_CENTRE, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Overwrite Script"), wxPoint(40,96), wxSize(136,29), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont Button1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button1->SetFont(Button1Font);
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(216,96), wxSize(136,29), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont Button2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button2->SetFont(Button2Font);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&lsOverwriteScript::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&lsOverwriteScript::OnButton2Click);
	//*)
	StaticText2->SetLabel(ScriptName);
	islsoverwrite = false;
}

lsOverwriteScript::~lsOverwriteScript()
{
	//(*Destroy(lsOverwriteScript)
	//*)
}

//overwrite button
void lsOverwriteScript::OnButton1Click(wxCommandEvent& event)
{
    islsoverwrite = true;
    control_6 = false;
    Destroy();
}

//cancel button
void lsOverwriteScript::OnButton2Click(wxCommandEvent& event)
{
    islsoverwrite = false;
    control_6 = false;
    Destroy();
}


