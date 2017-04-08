#include "DeleteVerify.h"

//(*InternalHeaders(DeleteVerify)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/msgdlg.h>

//(*IdInit(DeleteVerify)
const long DeleteVerify::ID_STATICTEXT1 = wxNewId();
const long DeleteVerify::ID_BUTTON1 = wxNewId();
const long DeleteVerify::ID_BUTTON2 = wxNewId();
const long DeleteVerify::ID_STATICTEXT2 = wxNewId();
//*)

extern wxString Value [64];
extern int currentprofile;
extern bool yesorno;
extern bool isprofilemode;
extern wxString SequencerProfileNames [64];
extern int sequencercurrentprofile;
extern bool is24hmode;
extern bool islightsequencer;

BEGIN_EVENT_TABLE(DeleteVerify,wxDialog)
	//(*EventTable(DeleteVerify)
	//*)
END_EVENT_TABLE()

DeleteVerify::DeleteVerify(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(DeleteVerify)
	Create(parent, id, _("Delete Profile"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(362,120));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Label"), wxPoint(40,24), wxSize(288,16), 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Yes"), wxPoint(64,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("No"), wxPoint(208,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Label"), wxPoint(40,40), wxSize(288,32), 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DeleteVerify::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DeleteVerify::OnButton2Click);
	//*)
    //gui10Frame mainframe;
    wxString del1;
    wxString del2;
    wxString delname;
    wxString quote = wxT("\"");

	if (isprofilemode) del1 = wxT("Are you sure you want to delete the profile");
	if (islightsequencer) del1 = wxT("Are you sure you want to delete the light sequence");
	if (is24hmode) del1 = wxT("Are you sure you want to delete the profile");

	if (isprofilemode) del2 = wxT("\" from this profile set?");
    if (islightsequencer) del2 = wxT("\" from the \nlist of light sequences?");
    if (is24hmode) del2 = wxT("from this profile set?");

	if (isprofilemode) delname = quote << Value[currentprofile] << del2;
	if (islightsequencer) delname = quote << SequencerProfileNames [sequencercurrentprofile] << del2;
    if (is24hmode) delname = del2;

	//Value[currentprofile];
	StaticText1->SetLabel(del1);
	StaticText2->SetLabel(delname);
    //wxString msg = wxString::Format(wxT("%i"),currentprofile);
    //wxString msg = "Lightput version 0.00.0";
    //wxMessageBox(msg, _("About Lightput"));

}

DeleteVerify::~DeleteVerify()
{
	//(*Destroy(DeleteVerify)
	//*)
}

//yes button
void DeleteVerify::OnButton1Click(wxCommandEvent& event)
{
    yesorno = true;
    Destroy();
}

//no button
void DeleteVerify::OnButton2Click(wxCommandEvent& event)
{
    yesorno = false;
    Destroy();
}
