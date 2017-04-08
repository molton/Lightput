#include "ExtenalInput.h"

//(*InternalHeaders(ExtenalInput)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)
#include <wx/textfile.h>
#include <wx/msgdlg.h>

wxTextFile externalinputfile;
wxString EIfilename;

extern bool isIconize;
extern unsigned short int LightputFrequency;

extern bool islightprogramonstartup;
extern bool isminimizedonstartup;

extern unsigned short int Channel_1_ExternalInput;
extern unsigned short int Channel_2_ExternalInput;
extern unsigned short int Channel_3_ExternalInput;
extern unsigned short int Channel_4_ExternalInput;
extern unsigned short int Channel_5_ExternalInput;
extern unsigned short int Channel_6_ExternalInput;
extern unsigned short int Channel_7_ExternalInput;
extern unsigned short int Channel_8_ExternalInput;
extern unsigned short int Channel_9_ExternalInput;
extern unsigned short int Channel_10_ExternalInput;
extern unsigned short int Channel_11_ExternalInput;
extern unsigned short int Channel_12_ExternalInput;
extern unsigned short int Channel_13_ExternalInput;
extern unsigned short int Channel_14_ExternalInput;
extern unsigned short int Channel_15_ExternalInput;
extern unsigned short int Channel_16_ExternalInput;

//(*IdInit(ExtenalInput)
const long ExtenalInput::ID_STATICBOX1 = wxNewId();
const long ExtenalInput::ID_STATICTEXT2 = wxNewId();
const long ExtenalInput::ID_BUTTON2 = wxNewId();
const long ExtenalInput::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ExtenalInput,wxDialog)
	//(*EventTable(ExtenalInput)
	//*)
END_EVENT_TABLE()

ExtenalInput::ExtenalInput(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ExtenalInput)
	Create(parent, wxID_ANY, _("Lightput External Input 0.1"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(470,297));
	Move(wxPoint(100,100));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("External Input Information"), wxPoint(24,24), wxSize(416,208), 0, _T("ID_STATICBOX1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Lightput External Input monitors the contents of a text file in order to\ncontrol lighting.  To interface with Lightput, you simply need to manipulate\nthe text file while Lightput External Input is active.\n\nThe text file is named \"input.lightput\", it is under the directory\n \"./lightput/light_programs/\".\n\nThere are 16 lines in the text file, each line represents a Lightput channel\nand should contain a value between 0 and 255.\n(0 lights completely off, 255 lights completely on, etc.)\n\nLightput External Input is active until this window is closed."), wxPoint(32,56), wxSize(408,156), 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	CloseButton = new wxButton(this, ID_BUTTON2, _("Close External Input"), wxPoint(128,248), wxSize(192,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont CloseButtonFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	CloseButton->SetFont(CloseButtonFont);
	EItimer.SetOwner(this, ID_TIMER1);
	
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ExtenalInput::OnButton2Click);
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&ExtenalInput::OnEItimerTrigger);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&ExtenalInput::OnClose);
	//*)

///create new blank input file, input.lightput

//this creates and blanks the input.lightput file
    EIfilename = wxT("./light_programs/input.lightput");
    externalinputfile.Create(EIfilename);
    externalinputfile.Clear();

    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));
    externalinputfile.AddLine(wxT("0"));

    externalinputfile.Write();

	EItimer.Start(LightputFrequency,false);

    if (islightprogramonstartup)
    {
        islightprogramonstartup = false;
        //if (isminimizedonstartup) isIconize = true;
    }
}

ExtenalInput::~ExtenalInput()
{
	//(*Destroy(ExtenalInput)
	//*)
}

//mimize button
void ExtenalInput::OnButton1Click(wxCommandEvent& event)
{
    isIconize = true;
}

void ExtenalInput::OnEItimerTrigger(wxTimerEvent& event)
{
    ///read and translate DMX info line by line
    externalinputfile.Close();
    externalinputfile.Open(EIfilename);
    if (!(externalinputfile.GetLineCount() < 16))
        {
        Channel_1_ExternalInput = wxAtoi(externalinputfile.GetFirstLine());
        Channel_2_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_3_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_4_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_5_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_6_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_7_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_8_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_9_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_10_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_11_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_12_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_13_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_14_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_15_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        Channel_16_ExternalInput = wxAtoi(externalinputfile.GetNextLine());
        }

}
//close button
void ExtenalInput::OnButton2Click(wxCommandEvent& event)
{
    EItimer.Stop();
    Destroy();
}


void ExtenalInput::OnClose(wxCloseEvent& event)
{
    EItimer.Stop();
    Destroy();
}
