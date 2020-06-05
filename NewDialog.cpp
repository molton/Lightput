#include "NewDialog.h"
//#include <stdio.h>
#include <wx/dir.h>
#include <wx/msgdlg.h>
#include <wx/textfile.h>
#include "ExportName.h"
#include "NewProfileName.h"
#include "ProfileOverwrite.h"

//#include "WinTypes.h"
//#include"ftd2xx.h"


//(*InternalHeaders(NewDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

// portmidi initialization

//#include "portmidi.h"
//#include "porttime.h"
/*#include "stdlib.h"
#include "string.h"
#include "assert.h"


#define INPUT_BUFFER_SIZE 100
#define OUTPUT_BUFFER_SIZE 0
#define DRIVER_INFO NULL
#define TIME_PROC ((int32_t (*)(void *)) Pt_Time)
#define TIME_INFO NULL
#define TIME_START Pt_Start(1, 0, 0)

#define STRING_MAX 80

int32_t latency = 0;
*/

wxArrayString files;
extern bool ischanged;
extern bool isloading;
extern bool isexporting;
extern wxString profiledirectory;
extern bool issavefirst;
extern wxString fullpath;
extern wxString nameofexport;
extern bool isnewblankprofile;

//(*IdInit(NewDialog)
const long NewDialog::ID_LISTBOX1 = wxNewId();
const long NewDialog::ID_BUTTON4 = wxNewId();
const long NewDialog::ID_BUTTON5 = wxNewId();
const long NewDialog::ID_BUTTON1 = wxNewId();
const long NewDialog::ID_STATICTEXT1 = wxNewId();
const long NewDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(NewDialog,wxDialog)
	//(*EventTable(NewDialog)
	//*)
END_EVENT_TABLE()

NewDialog::NewDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(NewDialog)
	Create(parent, wxID_ANY, _("Change Profile Sets"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
	SetClientSize(wxSize(433,355));
	ListBox1 = new wxListBox(this, ID_LISTBOX1, wxPoint(48,32), wxSize(336,152), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	Button4 = new wxButton(this, ID_BUTTON4, _("Load Profile Set"), wxPoint(48,232), wxSize(336,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	Button5 = new wxButton(this, ID_BUTTON5, _("Copy the Current Profile Set"), wxPoint(48,264), wxSize(336,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Cancel"), wxPoint(48,304), wxSize(336,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Lightput Profile Set Files"), wxPoint(48,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Create a New Empty Profile Set"), wxPoint(48,200), wxSize(336,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));

	Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,(wxObjectEventFunction)&NewDialog::OnListBox1Select);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewDialog::OnButton4Click);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewDialog::OnButton5Click);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewDialog::OnButton1Click1);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewDialog::OnButton2Click);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&NewDialog::OnInit);
	//*)

//this code block gets
//the contents of that directory aand puts it into files wxStringArray type
wxDir dir(wxGetCwd());
//files = 0;
dir.GetAllFiles(profiledirectory, &files,  wxT("*.lightput"), wxDIR_DEFAULT);
ListBox1->Clear();
//writes "files" to listbox1
ListBox1->Append(files);

}

NewDialog::~NewDialog()
{
	//(*Destroy(NewDialog)
	//*)
}


void NewDialog::OnButton1Click(wxCommandEvent& event)
{
     //TDmxSender *dmx_sender_thread;

     //dmx_sender_thread->Execute();

}

void NewDialog::OnInit(wxInitDialogEvent& event)
{
}

//import button
void NewDialog::OnButton4Click(wxCommandEvent& event)
{
int selection;
selection = ListBox1->GetSelection();

if (selection > -1) {
    isloading = true;
    fullpath = ListBox1->GetStringSelection();
    //profilefilename = fullpath not wxT(".\\profiles\\");


wxString buffer;
wxString charbuffer;
wxString nodirectory;

//these lines take the drectory off the profile name for saving/displaying
    int a = ListBox1->GetSelection();
    buffer = ListBox1->GetString(a);
    charbuffer = buffer;
    int npos = 11;//buffer.Find('.\\profiles\\',true);
    int nvpos = buffer.Find(wxT('.lightput'),true) + 1;

do {

    nodirectory = nodirectory + charbuffer[npos];
    npos++;
} while (npos < nvpos);
nameofexport = nodirectory;
//ListBox1->SetStringSelection(wxT(".\\profiles\\"));

//ListBox1->SetStringSelection(wxT(""));
//int a = ListBox1->GetSelection();
//nameofexport = ListBox1->GetLabel();

//need to make options dialog to generate directory structure



    Destroy();
    }

}

//export button
void NewDialog::OnButton5Click(wxCommandEvent& event)
{
    //create dialog to get filename
    ExportName Dlg(0);
    Dlg.ShowModal();


    //write file with filename
    if (isexporting == true) Destroy();
}


//cancel button
void NewDialog::OnButton1Click1(wxCommandEvent& event)
{
    Destroy();
}


void NewDialog::OnListBox1Select(wxCommandEvent& event)
{
    OnButton4Click(event);
}

//new blank profile button
void NewDialog::OnButton2Click(wxCommandEvent& event)
{
    NewProfileName Dlg(0);
    Dlg.ShowModal();
    if (isnewblankprofile == true) Destroy();
}
