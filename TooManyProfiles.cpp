#include "TooManyProfiles.h"

//(*InternalHeaders(TooManyProfiles)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(TooManyProfiles)
//*)

BEGIN_EVENT_TABLE(TooManyProfiles,wxDialog)
	//(*EventTable(TooManyProfiles)
	//*)
END_EVENT_TABLE()

TooManyProfiles::TooManyProfiles(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(TooManyProfiles)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	//*)
}

TooManyProfiles::~TooManyProfiles()
{
	//(*Destroy(TooManyProfiles)
	//*)
}

