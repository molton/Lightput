#include "SaveFirst.h"

//(*InternalHeaders(SaveFirst)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//(*IdInit(SaveFirst)
const long SaveFirst::ID_STATICTEXT1 = wxNewId();
const long SaveFirst::ID_BUTTON1 = wxNewId();
const long SaveFirst::ID_BUTTON2 = wxNewId();
const long SaveFirst::ID_STATICTEXT2 = wxNewId();
const long SaveFirst::ID_STATICTEXT3 = wxNewId();
const long SaveFirst::ID_STATICTEXT5 = wxNewId();
const long SaveFirst::ID_STATICTEXT4 = wxNewId();
//*)
extern wxString profilefilename;
extern bool issavefirst;

BEGIN_EVENT_TABLE(SaveFirst,wxDialog)
	//(*EventTable(SaveFirst)
	//*)
END_EVENT_TABLE()

SaveFirst::SaveFirst(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SaveFirst)
	Create(parent, wxID_ANY, _("Save before continuing\?"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(378,120));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Unsaved Changes have been made to the"), wxPoint(24,8), wxSize(320,13), 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Save Changes"), wxPoint(24,80), wxSize(152,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button1->SetDefault();
	wxFont Button1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button1->SetFont(Button1Font);
	Button2 = new wxButton(this, ID_BUTTON2, _("Continue Without Saving"), wxPoint(208,80), wxSize(152,24), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont Button2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button2->SetFont(Button2Font);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Label"), wxPoint(129,24), wxSize(120,13), 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Do you want to save the current profile set before changing"), wxPoint(24,40), wxSize(320,13), 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("current profile set \""), wxPoint(24,24), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	wxFont StaticText5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText5->SetFont(StaticText5Font);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Profile Sets\?"), wxPoint(24,56), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	wxFont StaticText4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SaveFirst::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SaveFirst::OnButton2Click);
	//*)

	StaticText2->SetLabel(profilefilename + wxT(" \"."));
}

SaveFirst::~SaveFirst()
{
	//(*Destroy(SaveFirst)
	//*)
}

//save changes and import
void SaveFirst::OnButton1Click(wxCommandEvent& event)
{
    issavefirst = true;
    Destroy();
}

//import, cancel changes
void SaveFirst::OnButton2Click(wxCommandEvent& event)
{
    issavefirst = false;
    Destroy();
}

