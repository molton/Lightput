#ifndef TOOMANYPROFILES_H
#define TOOMANYPROFILES_H

//(*Headers(TooManyProfiles)
#include <wx/dialog.h>
//*)

class TooManyProfiles: public wxDialog
{
	public:

		TooManyProfiles(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~TooManyProfiles();

		//(*Declarations(TooManyProfiles)
		//*)

	protected:

		//(*Identifiers(TooManyProfiles)
		//*)

	private:

		//(*Handlers(TooManyProfiles)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
