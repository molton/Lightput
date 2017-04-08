#include "SaveOnQuit.h"

//(*InternalHeaders(SaveOnQuit)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//(*IdInit(SaveOnQuit)
const long SaveOnQuit::ID_STATICTEXT1 = wxNewId();
const long SaveOnQuit::ID_BUTTON1 = wxNewId();
const long SaveOnQuit::ID_BUTTON2 = wxNewId();
//*)
extern bool issaveonquit;
extern bool iscancelquit;
bool control_1;

BEGIN_EVENT_TABLE(SaveOnQuit,wxDialog)
	//(*EventTable(SaveOnQuit)
	//*)
END_EVENT_TABLE()

SaveOnQuit::SaveOnQuit(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SaveOnQuit)
	Create(parent, id, _("Quitting Lightput..."), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(362,120));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("The Current Profile Set has changes that have not been saved,\nwould you like to save the current profile before you leave\? "), wxPoint(16,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("Save Profile Set && Quit"), wxPoint(24,80), wxSize(144,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont Button1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button1->SetFont(Button1Font);
	Button2 = new wxButton(this, ID_BUTTON2, _("Quit Without Saving"), wxPoint(200,80), wxSize(144,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont Button2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button2->SetFont(Button2Font);
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SaveOnQuit::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SaveOnQuit::OnButton2Click);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SaveOnQuit::OnClose);
	//*)
control_1 = false;

}

SaveOnQuit::~SaveOnQuit()
{
	//(*Destroy(SaveOnQuit)
	//*)
}

//save and quit button
void SaveOnQuit::OnButton1Click(wxCommandEvent& event)
{
    issaveonquit = true;
    iscancelquit = false;
    control_1 = true;
    Destroy();
}

//quit without saving button
void SaveOnQuit::OnButton2Click(wxCommandEvent& event)
{
    issaveonquit = false;
    iscancelquit = false;
    control_1 = true;
    Destroy();
}

void SaveOnQuit::OnClose(wxCloseEvent& event)
{
    if ((!control_1)) iscancelquit = true;
    Destroy();
}
