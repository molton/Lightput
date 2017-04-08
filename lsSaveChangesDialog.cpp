#include "lsSaveChangesDialog.h"

//(*InternalHeaders(lsSaveChangesDialog)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//(*IdInit(lsSaveChangesDialog)
const long lsSaveChangesDialog::ID_STATICTEXT1 = wxNewId();
const long lsSaveChangesDialog::ID_BUTTON1 = wxNewId();
const long lsSaveChangesDialog::ID_BUTTON2 = wxNewId();
//*)

extern int savechanges;


BEGIN_EVENT_TABLE(lsSaveChangesDialog,wxDialog)
	//(*EventTable(lsSaveChangesDialog)
	//*)
END_EVENT_TABLE()

lsSaveChangesDialog::lsSaveChangesDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(lsSaveChangesDialog)
	Create(parent, id, _("Save Changes\?"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(400,141));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Changes have been made to the current script file, would\nyou like to save these changes before continuing\?"), wxPoint(16,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Save Current Script"), wxPoint(16,88), wxSize(168,29), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont Button1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button1->SetFont(Button1Font);
	Button2 = new wxButton(this, ID_BUTTON2, _("Continue Without Saving"), wxPoint(216,88), wxSize(168,29), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont Button2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button2->SetFont(Button2Font);
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&lsSaveChangesDialog::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&lsSaveChangesDialog::OnButton2Click);
	//*)
	savechanges = 0;
}

lsSaveChangesDialog::~lsSaveChangesDialog()
{
	//(*Destroy(lsSaveChangesDialog)
	//*)
}

//save changes button
void lsSaveChangesDialog::OnButton1Click(wxCommandEvent& event)
{
    savechanges = 1;
    Destroy();
}

void lsSaveChangesDialog::OnButton2Click(wxCommandEvent& event)
{
    savechanges = 2;
    Destroy();
}
