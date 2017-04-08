#include "ProfileOverwrite.h"

//(*InternalHeaders(ProfileOverwrite)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//(*IdInit(ProfileOverwrite)
const long ProfileOverwrite::ID_STATICTEXT1 = wxNewId();
const long ProfileOverwrite::ID_STATICTEXT2 = wxNewId();
const long ProfileOverwrite::ID_BUTTON1 = wxNewId();
const long ProfileOverwrite::ID_BUTTON2 = wxNewId();
//*)
extern wxString profilefilename;
extern bool yesorno;
//bool timeryesorno;
extern bool generalcancel;
extern bool isprofilemode;
extern wxString SequencerProfileNames [64];
extern int sequencercurrentprofile;
int control_2;

BEGIN_EVENT_TABLE(ProfileOverwrite,wxDialog)
	//(*EventTable(ProfileOverwrite)
	//*)
END_EVENT_TABLE()

ProfileOverwrite::ProfileOverwrite(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ProfileOverwrite)
	Create(parent, id, _("Overwrite Saved Data\?"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(362,120));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Label"), wxPoint(56,24), wxSize(336,16), 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Label"), wxPoint(56,40), wxSize(336,13), 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Yes"), wxPoint(40,80), wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("No"), wxPoint(192,80), wxSize(128,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProfileOverwrite::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProfileOverwrite::OnButton2Click);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&ProfileOverwrite::OnClose);
	//*)

	control_2 = 0;
	generalcancel = false;

    wxString msg1;
    wxString msg2;
	if (isprofilemode) {
	    msg1 = wxT("The file \"");
        msg2 = wxT("\" already exists,");
        wxString msg3 = wxT("do you want to overwrite it?");
        StaticText1->SetLabel(msg1 << profilefilename << msg2);
        StaticText2->SetLabel(msg3);
	}
	else {
	    msg1 = wxT("Changes have been made to the profiles, would" );
	    msg2 = wxT("you like to save or cancel these changes?" );
        Button1->SetLabel(wxT("Save Changes"));
        Button2->SetLabel(wxT("Cancel Changes"));
        StaticText1->SetLabel(msg1);
        StaticText2->SetLabel(msg2);
	}
}

ProfileOverwrite::~ProfileOverwrite()
{
	//(*Destroy(ProfileOverwrite)
	//*)
}

//yes button
void ProfileOverwrite::OnButton1Click(wxCommandEvent& event)
{
    yesorno = true;
    //timeryesorno = true;
    control_2 = 1;
    Destroy();
}

//nobutton
void ProfileOverwrite::OnButton2Click(wxCommandEvent& event)
{
    yesorno = false;
    //timeryesorno = false;
    control_2 = 2;
    Destroy();
}

void ProfileOverwrite::OnClose(wxCloseEvent& event)
{
    if (control_2 == 0) generalcancel = true;
    Destroy();
}
