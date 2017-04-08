#include "lsLoadDialog.h"

//(*InternalHeaders(lsLoadDialog)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)
#include <wx/dir.h>
#include <wx/msgdlg.h>
#include <wx/textfile.h>

//(*IdInit(lsLoadDialog)
const long lsLoadDialog::ID_LISTBOX1 = wxNewId();
const long lsLoadDialog::ID_BUTTON1 = wxNewId();
const long lsLoadDialog::ID_BUTTON2 = wxNewId();
const long lsLoadDialog::ID_STATICTEXT1 = wxNewId();
//*)

extern wxString ScriptName;
extern bool lsisloading;

wxArrayString lsfiles;

BEGIN_EVENT_TABLE(lsLoadDialog,wxDialog)
	//(*EventTable(lsLoadDialog)
	//*)
END_EVENT_TABLE()

lsLoadDialog::lsLoadDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(lsLoadDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(400,300));
	Move(wxDefaultPosition);
	ListBox1 = new wxListBox(this, ID_LISTBOX1, wxPoint(32,48), wxSize(336,176), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Load"), wxPoint(32,248), wxSize(144,29), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont Button1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button1->SetFont(Button1Font);
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(224,248), wxSize(144,29), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont Button2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button2->SetFont(Button2Font);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Available Light Scripts"), wxPoint(32,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&lsLoadDialog::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&lsLoadDialog::OnButton2Click);
	//*)
    lsisloading = false;

	wxDir lsdir(wxGetCwd());
    lsfiles = 0;
    lsdir.GetAllFiles(wxT("./light_programs/light_scripts/"), &lsfiles,  wxT("*.ls"), wxDIR_FILES);
    ListBox1->Clear();

    //writes "files" to listbox1

    //code to remove directory crap
    int arraysize = lsfiles.GetCount();

    for (int i = 0; i < arraysize; i++)
    {
        wxString lstemp = lsfiles.Item(i);
        lstemp = lstemp.substr( 31 );
        ListBox1->Append(lstemp);
    }

}

lsLoadDialog::~lsLoadDialog()
{
	//(*Destroy(lsLoadDialog)
	//*)
}

//load button
void lsLoadDialog::OnButton1Click(wxCommandEvent& event)
{
    if (ListBox1->GetSelection() != -1) {
        lsisloading = true;
        ScriptName = ListBox1->GetString(ListBox1->GetSelection());
        Destroy();
    }
}

//cancel button
void lsLoadDialog::OnButton2Click(wxCommandEvent& event)
{
    lsisloading = false;
    Destroy();
}
