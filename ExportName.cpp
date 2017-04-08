#include "ExportName.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(ExportName)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//(*IdInit(ExportName)
const long ExportName::ID_TEXTCTRL1 = wxNewId();
const long ExportName::ID_STATICTEXT1 = wxNewId();
const long ExportName::ID_STATICTEXT2 = wxNewId();
const long ExportName::ID_BUTTON1 = wxNewId();
const long ExportName::ID_BUTTON2 = wxNewId();
const long ExportName::ID_STATICTEXT3 = wxNewId();
//*)

extern wxString profilefilename;
extern bool isexporting;

BEGIN_EVENT_TABLE(ExportName,wxDialog)
	//(*EventTable(ExportName)
	//*)
END_EVENT_TABLE()

ExportName::ExportName(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ExportName)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(362,120));
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(32,48), wxSize(152,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _(".Lightput (added automatically)"), wxPoint(184,54), wxSize(150,21), 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Enter a Valid filename for the profile set you\'re exporting."), wxPoint(32,8), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(40,88), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(192,88), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("(No !,@,#,$,%,^,&,*, etc. keep it to letters and numbers)"), wxPoint(32,24), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);

	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ExportName::OnTextCtrl1Text);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ExportName::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ExportName::OnButton2Click);
	//*)
}

ExportName::~ExportName()
{
	//(*Destroy(ExportName)
	//*)
}

//ok button
void ExportName::OnButton1Click(wxCommandEvent& event)
{
    if(TextCtrl1->GetValue() != wxT("")){
    profilefilename = TextCtrl1->GetValue() + wxT(".lightput");
    isexporting = true;
    Destroy();
    }else wxMessageBox (wxT("Type in a valid file name."), wxT("Error"));

}

void ExportName::OnTextCtrl1Text(wxCommandEvent& event)
{
}

//cancel button
void ExportName::OnButton2Click(wxCommandEvent& event)
{
    Destroy();
}
