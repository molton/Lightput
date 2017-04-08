#include "lsSaveDialog.h"

//(*InternalHeaders(lsSaveDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(lsSaveDialog)
const long lsSaveDialog::ID_TEXTCTRL1 = wxNewId();
const long lsSaveDialog::ID_STATICTEXT1 = wxNewId();
const long lsSaveDialog::ID_STATICTEXT2 = wxNewId();
const long lsSaveDialog::ID_BUTTON1 = wxNewId();
const long lsSaveDialog::ID_BUTTON2 = wxNewId();
//*)

extern bool lsissaving;
extern wxString ScriptName;

BEGIN_EVENT_TABLE(lsSaveDialog,wxDialog)
	//(*EventTable(lsSaveDialog)
	//*)
END_EVENT_TABLE()

lsSaveDialog::lsSaveDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(lsSaveDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(395,154));
	TextCtrlFileName = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(32,64), wxSize(168,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	wxFont TextCtrlFileNameFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrlFileName->SetFont(TextCtrlFileNameFont);
	StaticText_A1 = new wxStaticText(this, ID_STATICTEXT1, _("Save the current Light Script as"), wxPoint(32,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText_A1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText_A1->SetFont(StaticText_A1Font);
	StaticText_A2 = new wxStaticText(this, ID_STATICTEXT2, _(".ls (added automatically)"), wxPoint(200,72), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText_A2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText_A2->SetFont(StaticText_A2Font);
	SaveButton_sd = new wxButton(this, ID_BUTTON1, _("Save"), wxPoint(32,112), wxSize(144,29), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont SaveButton_sdFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	SaveButton_sd->SetFont(SaveButton_sdFont);
	CancelButton_sd = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(216,112), wxSize(144,29), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont CancelButton_sdFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CancelButton_sd->SetFont(CancelButton_sdFont);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&lsSaveDialog::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&lsSaveDialog::OnButton2Click);
	//*)
	lsissaving = false;
	TextCtrlFileName->SetValue(ScriptName.substr(0, ScriptName.size()-3));//substr( ScriptName.length() - 3 ));
	//st = myString.substr(0, myString.size()-1)
}

lsSaveDialog::~lsSaveDialog()
{
	//(*Destroy(lsSaveDialog)
	//*)
}

//on save button press
void lsSaveDialog::OnButton1Click(wxCommandEvent& event)
{
    if (TextCtrlFileName->GetValue() != wxT("")) {
        lsissaving = true;
        ScriptName = TextCtrlFileName->GetValue();
        Destroy();
    }
}

void lsSaveDialog::OnButton2Click(wxCommandEvent& event)
{
    lsissaving = false;
    Destroy();
}
