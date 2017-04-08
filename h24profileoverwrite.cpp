#include "h24profileoverwrite.h"

//(*InternalHeaders(h24profileoverwrite)
#include <wx/intl.h>
#include <wx/string.h>
//*)

extern bool timeryesorno;
extern bool savecancel;
int control_3;

//(*IdInit(h24profileoverwrite)
const long h24profileoverwrite::ID_STATICTEXT1 = wxNewId();
const long h24profileoverwrite::ID_BUTTON1 = wxNewId();
const long h24profileoverwrite::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(h24profileoverwrite,wxDialog)
	//(*EventTable(h24profileoverwrite)
	//*)
END_EVENT_TABLE()

h24profileoverwrite::h24profileoverwrite(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(h24profileoverwrite)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(408,134));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Would you like to save the changes made to the 24 Hour Light timer\nprofiles or cancel the changes that have been made\?"), wxPoint(32,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Save Changes"), wxPoint(16,88), wxSize(176,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel Changes"), wxPoint(224,88), wxSize(176,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&h24profileoverwrite::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&h24profileoverwrite::OnButton2Click);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&h24profileoverwrite::OnClose);
	//*)

	control_3 = 0;
	savecancel = false;
	timeryesorno = false;
}

h24profileoverwrite::~h24profileoverwrite()
{
	//(*Destroy(h24profileoverwrite)
	//*)
}

//save button
void h24profileoverwrite::OnButton1Click(wxCommandEvent& event)
{
    control_3 = 1;
    timeryesorno = true;
    Destroy();
}

//cancel button
void h24profileoverwrite::OnButton2Click(wxCommandEvent& event)
{
    control_3 = 2;
    timeryesorno = false;
    Destroy();
}

void h24profileoverwrite::OnClose(wxCloseEvent& event)
{
    if (control_3 == 0) savecancel = true;
    Destroy();
}
