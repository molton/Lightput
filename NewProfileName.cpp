#include "NewProfileName.h"
#include <wx/msgdlg.h>
//(*InternalHeaders(NewProfileName)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)


//(*IdInit(NewProfileName)
const long NewProfileName::ID_TEXTCTRL1 = wxNewId();
const long NewProfileName::ID_STATICTEXT1 = wxNewId();
const long NewProfileName::ID_STATICTEXT2 = wxNewId();
const long NewProfileName::ID_STATICTEXT3 = wxNewId();
const long NewProfileName::ID_BUTTON1 = wxNewId();
const long NewProfileName::ID_BUTTON2 = wxNewId();
//*)
extern bool isnewblankprofile;
extern wxString nameofnewprofile;
extern wxString profilefilename;

BEGIN_EVENT_TABLE(NewProfileName,wxDialog)
	//(*EventTable(NewProfileName)
	//*)
END_EVENT_TABLE()

NewProfileName::NewProfileName(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(NewProfileName)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(362,120));
	Move(wxDefaultPosition);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(32,48), wxSize(152,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	wxFont TextCtrl1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl1->SetFont(TextCtrl1Font);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Enter a Valid filename for the new profile set."), wxPoint(32,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("(No !,@,#,$,%,^,&,*, etc. keep it to letters and numbers)"), wxPoint(32,24), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _(".Lightput (added automatically)"), wxPoint(184,54), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(40,88), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(192,88), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewProfileName::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewProfileName::OnButton2Click);
	//*)
}

NewProfileName::~NewProfileName()
{
	//(*Destroy(NewProfileName)
	//*)
}

//ok button
void NewProfileName::OnButton1Click(wxCommandEvent& event)
{
    if(TextCtrl1->GetValue() != wxT("")){
    nameofnewprofile = TextCtrl1->GetValue() + wxT(".lightput");
    isnewblankprofile = true;
    Destroy();
    }else wxMessageBox (wxT("Type in a valid file name."), wxT("Error"));
}

//cancel button
void NewProfileName::OnButton2Click(wxCommandEvent& event)
{
    Destroy();
}
