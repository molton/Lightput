/***************************************************************
 * Name:      gui10App.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2012-09-30
 * Copyright:  ()
 * License:
 **************************************************************/

#include "gui10App.h"
//#include <windows.h>
//#include "WinTypes.h"
#include <stdio.h>

//#include "ftd2xx.h"

//(*AppHeaders
#include "gui10Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(gui10App);

bool gui10App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	gui10Frame* Frame = new gui10Frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
