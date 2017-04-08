#include "Options.h"

//(*InternalHeaders(Options)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)
#include <wx/msgdlg.h>
#include <wx/textfile.h>

//(*IdInit(Options)
const long Options::ID_STATICBOX2 = wxNewId();
const long Options::ID_STATICBOX1 = wxNewId();
const long Options::ID_RADIOBUTTON1 = wxNewId();
const long Options::ID_RADIOBUTTON2 = wxNewId();
const long Options::ID_TEXTCTRL1 = wxNewId();
const long Options::ID_STATICBOX4 = wxNewId();
const long Options::ID_CHOICE1 = wxNewId();
const long Options::ID_STATICTEXT2 = wxNewId();
const long Options::ID_BUTTON1 = wxNewId();
const long Options::ID_BUTTON2 = wxNewId();
const long Options::ID_STATICBOX3 = wxNewId();
const long Options::ID_CHECKBOX1 = wxNewId();
const long Options::ID_CHECKBOX2 = wxNewId();
const long Options::ID_STATICBOX5 = wxNewId();
const long Options::ID_CHOICE2 = wxNewId();
const long Options::ID_STATICTEXT3 = wxNewId();
const long Options::ID_CHECKBOX3 = wxNewId();
const long Options::ID_STATICBOX6 = wxNewId();
const long Options::ID_CHECKBOX4 = wxNewId();
const long Options::ID_CHECKBOX5 = wxNewId();
const long Options::ID_STATICBOX7 = wxNewId();
const long Options::ID_CHOICE3 = wxNewId();
const long Options::ID_STATICBOX8 = wxNewId();
const long Options::ID_CHECKBOX6 = wxNewId();
const long Options::ID_CHECKBOX7 = wxNewId();
const long Options::ID_CHOICE4 = wxNewId();
const long Options::ID_STATICTEXT1 = wxNewId();
//*)

//options variables
extern unsigned short int option_dmxmode;
extern wxString option_defaultprofile;
extern unsigned short int option_profiletime;
extern bool issmooth;
extern bool issmoothstart;
extern unsigned short int StartingDMXChannel;
extern bool isDMXcascade;
extern unsigned short int LightputFrequency;
extern bool isminimizedonstartup;
extern bool runlightprogramonstartup;
extern unsigned short int startuplightprogram;


//variables for light scripts options
extern bool islsRepeat;
extern bool islsStartOn1;


BEGIN_EVENT_TABLE(Options,wxDialog)
	//(*EventTable(Options)
	//*)
END_EVENT_TABLE()

Options::Options(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(Options)
	Create(parent, wxID_ANY, _("Lightput Options"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(561,345));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Default Profile Set"), wxPoint(16,112), wxSize(168,56), 0, _T("ID_STATICBOX2"));
	wxFont StaticBox2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox2->SetFont(StaticBox2Font);
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Default DMX Mode"), wxPoint(16,16), wxSize(168,88), 0, _T("ID_STATICBOX1"));
	wxFont StaticBox1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox1->SetFont(StaticBox1Font);
	RadioButton1 = new wxRadioButton(this, ID_RADIOBUTTON1, _("4-Channel"), wxPoint(32,40), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	wxFont RadioButton1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	RadioButton1->SetFont(RadioButton1Font);
	RadioButton2 = new wxRadioButton(this, ID_RADIOBUTTON2, _("16-Channel"), wxPoint(32,64), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	wxFont RadioButton2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	RadioButton2->SetFont(RadioButton2Font);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("profiles.lightput"), wxPoint(24,136), wxSize(152,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	wxFont TextCtrl1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	TextCtrl1->SetFont(TextCtrl1Font);
	StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("Profile Light Transition"), wxPoint(16,240), wxSize(168,56), 0, _T("ID_STATICBOX4"));
	wxFont StaticBox4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox4->SetFont(StaticBox4Font);
	TransitionChoice = new wxChoice(this, ID_CHOICE1, wxPoint(24,264), wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	TransitionChoice->Append(_("0"));
	TransitionChoice->Append(_("1"));
	TransitionChoice->Append(_("2"));
	TransitionChoice->Append(_("3"));
	TransitionChoice->Append(_("4"));
	TransitionChoice->Append(_("5"));
	TransitionChoice->Append(_("6"));
	TransitionChoice->Append(_("7"));
	TransitionChoice->Append(_("8"));
	TransitionChoice->Append(_("9"));
	TransitionChoice->Append(_("10"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Seconds"), wxPoint(120,272), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	Button1 = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(88,304), wxSize(160,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont Button1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button1->SetFont(Button1Font);
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(312,304), wxSize(160,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont Button2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Button2->SetFont(Button2Font);
	StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("Light Sequencer Options"), wxPoint(200,112), wxSize(160,72), 0, _T("ID_STATICBOX3"));
	wxFont StaticBox3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox3->SetFont(StaticBox3Font);
	CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("Smooth Transitions"), wxPoint(216,128), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox1->SetValue(false);
	wxFont CheckBox1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox1->SetFont(CheckBox1Font);
	CheckBox2 = new wxCheckBox(this, ID_CHECKBOX2, _("Smooth Start"), wxPoint(216,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBox2->SetValue(false);
	wxFont CheckBox2Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox2->SetFont(CheckBox2Font);
	StaticBox5 = new wxStaticBox(this, ID_STATICBOX5, _("Change DMX Output Channels"), wxPoint(200,16), wxSize(336,88), 0, _T("ID_STATICBOX5"));
	wxFont StaticBox5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox5->SetFont(StaticBox5Font);
	Choice2 = new wxChoice(this, ID_CHOICE2, wxPoint(416,40), wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	Choice2->Append(_("1"));
	Choice2->Append(_("2"));
	Choice2->Append(_("3"));
	Choice2->Append(_("4"));
	Choice2->Append(_("5"));
	Choice2->Append(_("6"));
	Choice2->Append(_("7"));
	Choice2->Append(_("8"));
	Choice2->Append(_("9"));
	Choice2->Append(_("10"));
	Choice2->Append(_("11"));
	Choice2->Append(_("12"));
	Choice2->Append(_("13"));
	Choice2->Append(_("14"));
	Choice2->Append(_("15"));
	Choice2->Append(_("16"));
	Choice2->Append(_("17"));
	Choice2->Append(_("18"));
	Choice2->Append(_("19"));
	Choice2->Append(_("20"));
	Choice2->Append(_("21"));
	Choice2->Append(_("22"));
	Choice2->Append(_("23"));
	Choice2->Append(_("24"));
	Choice2->Append(_("25"));
	Choice2->Append(_("26"));
	Choice2->Append(_("27"));
	Choice2->Append(_("28"));
	Choice2->Append(_("29"));
	Choice2->Append(_("30"));
	Choice2->Append(_("31"));
	Choice2->Append(_("32"));
	Choice2->Append(_("33"));
	Choice2->Append(_("34"));
	Choice2->Append(_("35"));
	Choice2->Append(_("36"));
	Choice2->Append(_("37"));
	Choice2->Append(_("38"));
	Choice2->Append(_("39"));
	Choice2->Append(_("40"));
	Choice2->Append(_("41"));
	Choice2->Append(_("42"));
	Choice2->Append(_("43"));
	Choice2->Append(_("44"));
	Choice2->Append(_("45"));
	Choice2->Append(_("46"));
	Choice2->Append(_("47"));
	Choice2->Append(_("48"));
	Choice2->Append(_("49"));
	Choice2->Append(_("50"));
	Choice2->Append(_("51"));
	Choice2->Append(_("52"));
	Choice2->Append(_("53"));
	Choice2->Append(_("54"));
	Choice2->Append(_("55"));
	Choice2->Append(_("56"));
	Choice2->Append(_("57"));
	Choice2->Append(_("58"));
	Choice2->Append(_("59"));
	Choice2->Append(_("60"));
	Choice2->Append(_("61"));
	Choice2->Append(_("62"));
	Choice2->Append(_("63"));
	Choice2->Append(_("64"));
	Choice2->Append(_("65"));
	Choice2->Append(_("66"));
	Choice2->Append(_("67"));
	Choice2->Append(_("68"));
	Choice2->Append(_("69"));
	Choice2->Append(_("70"));
	Choice2->Append(_("71"));
	Choice2->Append(_("72"));
	Choice2->Append(_("73"));
	Choice2->Append(_("74"));
	Choice2->Append(_("75"));
	Choice2->Append(_("76"));
	Choice2->Append(_("77"));
	Choice2->Append(_("78"));
	Choice2->Append(_("79"));
	Choice2->Append(_("80"));
	Choice2->Append(_("81"));
	Choice2->Append(_("82"));
	Choice2->Append(_("83"));
	Choice2->Append(_("84"));
	Choice2->Append(_("85"));
	Choice2->Append(_("86"));
	Choice2->Append(_("87"));
	Choice2->Append(_("88"));
	Choice2->Append(_("89"));
	Choice2->Append(_("90"));
	Choice2->Append(_("91"));
	Choice2->Append(_("92"));
	Choice2->Append(_("93"));
	Choice2->Append(_("94"));
	Choice2->Append(_("95"));
	Choice2->Append(_("96"));
	Choice2->Append(_("97"));
	Choice2->Append(_("98"));
	Choice2->Append(_("99"));
	Choice2->Append(_("100"));
	Choice2->Append(_("101"));
	Choice2->Append(_("102"));
	Choice2->Append(_("103"));
	Choice2->Append(_("104"));
	Choice2->Append(_("105"));
	Choice2->Append(_("106"));
	Choice2->Append(_("107"));
	Choice2->Append(_("108"));
	Choice2->Append(_("109"));
	Choice2->Append(_("110"));
	Choice2->Append(_("111"));
	Choice2->Append(_("112"));
	Choice2->Append(_("113"));
	Choice2->Append(_("114"));
	Choice2->Append(_("115"));
	Choice2->Append(_("116"));
	Choice2->Append(_("117"));
	Choice2->Append(_("118"));
	Choice2->Append(_("119"));
	Choice2->Append(_("120"));
	Choice2->Append(_("121"));
	Choice2->Append(_("122"));
	Choice2->Append(_("123"));
	Choice2->Append(_("124"));
	Choice2->Append(_("125"));
	Choice2->Append(_("126"));
	Choice2->Append(_("127"));
	Choice2->Append(_("128"));
	Choice2->Append(_("129"));
	Choice2->Append(_("130"));
	Choice2->Append(_("131"));
	Choice2->Append(_("132"));
	Choice2->Append(_("133"));
	Choice2->Append(_("134"));
	Choice2->Append(_("135"));
	Choice2->Append(_("136"));
	Choice2->Append(_("137"));
	Choice2->Append(_("138"));
	Choice2->Append(_("139"));
	Choice2->Append(_("140"));
	Choice2->Append(_("141"));
	Choice2->Append(_("142"));
	Choice2->Append(_("143"));
	Choice2->Append(_("144"));
	Choice2->Append(_("145"));
	Choice2->Append(_("146"));
	Choice2->Append(_("147"));
	Choice2->Append(_("148"));
	Choice2->Append(_("149"));
	Choice2->Append(_("150"));
	Choice2->Append(_("151"));
	Choice2->Append(_("152"));
	Choice2->Append(_("153"));
	Choice2->Append(_("154"));
	Choice2->Append(_("155"));
	Choice2->Append(_("156"));
	Choice2->Append(_("157"));
	Choice2->Append(_("158"));
	Choice2->Append(_("159"));
	Choice2->Append(_("160"));
	Choice2->Append(_("161"));
	Choice2->Append(_("162"));
	Choice2->Append(_("163"));
	Choice2->Append(_("164"));
	Choice2->Append(_("165"));
	Choice2->Append(_("166"));
	Choice2->Append(_("167"));
	Choice2->Append(_("168"));
	Choice2->Append(_("169"));
	Choice2->Append(_("170"));
	Choice2->Append(_("171"));
	Choice2->Append(_("172"));
	Choice2->Append(_("173"));
	Choice2->Append(_("174"));
	Choice2->Append(_("175"));
	Choice2->Append(_("176"));
	Choice2->Append(_("177"));
	Choice2->Append(_("178"));
	Choice2->Append(_("179"));
	Choice2->Append(_("180"));
	Choice2->Append(_("181"));
	Choice2->Append(_("182"));
	Choice2->Append(_("183"));
	Choice2->Append(_("184"));
	Choice2->Append(_("185"));
	Choice2->Append(_("186"));
	Choice2->Append(_("187"));
	Choice2->Append(_("188"));
	Choice2->Append(_("189"));
	Choice2->Append(_("190"));
	Choice2->Append(_("191"));
	Choice2->Append(_("192"));
	Choice2->Append(_("193"));
	Choice2->Append(_("194"));
	Choice2->Append(_("195"));
	Choice2->Append(_("196"));
	Choice2->Append(_("197"));
	Choice2->Append(_("198"));
	Choice2->Append(_("199"));
	Choice2->Append(_("200"));
	Choice2->Append(_("201"));
	Choice2->Append(_("202"));
	Choice2->Append(_("203"));
	Choice2->Append(_("204"));
	Choice2->Append(_("205"));
	Choice2->Append(_("206"));
	Choice2->Append(_("207"));
	Choice2->Append(_("208"));
	Choice2->Append(_("209"));
	Choice2->Append(_("210"));
	Choice2->Append(_("211"));
	Choice2->Append(_("212"));
	Choice2->Append(_("213"));
	Choice2->Append(_("214"));
	Choice2->Append(_("215"));
	Choice2->Append(_("216"));
	Choice2->Append(_("217"));
	Choice2->Append(_("218"));
	Choice2->Append(_("219"));
	Choice2->Append(_("220"));
	Choice2->Append(_("221"));
	Choice2->Append(_("222"));
	Choice2->Append(_("223"));
	Choice2->Append(_("224"));
	Choice2->Append(_("225"));
	Choice2->Append(_("226"));
	Choice2->Append(_("227"));
	Choice2->Append(_("228"));
	Choice2->Append(_("229"));
	Choice2->Append(_("230"));
	Choice2->Append(_("231"));
	Choice2->Append(_("232"));
	Choice2->Append(_("233"));
	Choice2->Append(_("234"));
	Choice2->Append(_("235"));
	Choice2->Append(_("236"));
	Choice2->Append(_("237"));
	Choice2->Append(_("238"));
	Choice2->Append(_("239"));
	Choice2->Append(_("240"));
	Choice2->Append(_("241"));
	Choice2->Append(_("242"));
	Choice2->Append(_("243"));
	Choice2->Append(_("244"));
	Choice2->Append(_("245"));
	Choice2->Append(_("246"));
	Choice2->Append(_("247"));
	Choice2->Append(_("248"));
	Choice2->Append(_("249"));
	Choice2->Append(_("250"));
	Choice2->Append(_("251"));
	Choice2->Append(_("252"));
	Choice2->Append(_("253"));
	Choice2->Append(_("254"));
	Choice2->Append(_("255"));
	Choice2->Append(_("256"));
	Choice2->Append(_("257"));
	Choice2->Append(_("258"));
	Choice2->Append(_("259"));
	Choice2->Append(_("260"));
	Choice2->Append(_("261"));
	Choice2->Append(_("262"));
	Choice2->Append(_("263"));
	Choice2->Append(_("264"));
	Choice2->Append(_("265"));
	Choice2->Append(_("266"));
	Choice2->Append(_("267"));
	Choice2->Append(_("268"));
	Choice2->Append(_("269"));
	Choice2->Append(_("270"));
	Choice2->Append(_("271"));
	Choice2->Append(_("272"));
	Choice2->Append(_("273"));
	Choice2->Append(_("274"));
	Choice2->Append(_("275"));
	Choice2->Append(_("276"));
	Choice2->Append(_("277"));
	Choice2->Append(_("278"));
	Choice2->Append(_("279"));
	Choice2->Append(_("280"));
	Choice2->Append(_("281"));
	Choice2->Append(_("282"));
	Choice2->Append(_("283"));
	Choice2->Append(_("284"));
	Choice2->Append(_("285"));
	Choice2->Append(_("286"));
	Choice2->Append(_("287"));
	Choice2->Append(_("288"));
	Choice2->Append(_("289"));
	Choice2->Append(_("290"));
	Choice2->Append(_("291"));
	Choice2->Append(_("292"));
	Choice2->Append(_("293"));
	Choice2->Append(_("294"));
	Choice2->Append(_("295"));
	Choice2->Append(_("296"));
	Choice2->Append(_("297"));
	Choice2->Append(_("298"));
	Choice2->Append(_("299"));
	Choice2->Append(_("300"));
	Choice2->Append(_("301"));
	Choice2->Append(_("302"));
	Choice2->Append(_("303"));
	Choice2->Append(_("304"));
	Choice2->Append(_("305"));
	Choice2->Append(_("306"));
	Choice2->Append(_("307"));
	Choice2->Append(_("308"));
	Choice2->Append(_("309"));
	Choice2->Append(_("310"));
	Choice2->Append(_("311"));
	Choice2->Append(_("312"));
	Choice2->Append(_("313"));
	Choice2->Append(_("314"));
	Choice2->Append(_("315"));
	Choice2->Append(_("316"));
	Choice2->Append(_("317"));
	Choice2->Append(_("318"));
	Choice2->Append(_("319"));
	Choice2->Append(_("320"));
	Choice2->Append(_("321"));
	Choice2->Append(_("322"));
	Choice2->Append(_("323"));
	Choice2->Append(_("324"));
	Choice2->Append(_("325"));
	Choice2->Append(_("326"));
	Choice2->Append(_("327"));
	Choice2->Append(_("328"));
	Choice2->Append(_("329"));
	Choice2->Append(_("330"));
	Choice2->Append(_("331"));
	Choice2->Append(_("332"));
	Choice2->Append(_("333"));
	Choice2->Append(_("334"));
	Choice2->Append(_("335"));
	Choice2->Append(_("336"));
	Choice2->Append(_("337"));
	Choice2->Append(_("338"));
	Choice2->Append(_("339"));
	Choice2->Append(_("340"));
	Choice2->Append(_("341"));
	Choice2->Append(_("342"));
	Choice2->Append(_("343"));
	Choice2->Append(_("344"));
	Choice2->Append(_("345"));
	Choice2->Append(_("346"));
	Choice2->Append(_("347"));
	Choice2->Append(_("348"));
	Choice2->Append(_("349"));
	Choice2->Append(_("350"));
	Choice2->Append(_("351"));
	Choice2->Append(_("352"));
	Choice2->Append(_("353"));
	Choice2->Append(_("354"));
	Choice2->Append(_("355"));
	Choice2->Append(_("356"));
	Choice2->Append(_("357"));
	Choice2->Append(_("358"));
	Choice2->Append(_("359"));
	Choice2->Append(_("360"));
	Choice2->Append(_("361"));
	Choice2->Append(_("362"));
	Choice2->Append(_("363"));
	Choice2->Append(_("364"));
	Choice2->Append(_("365"));
	Choice2->Append(_("366"));
	Choice2->Append(_("367"));
	Choice2->Append(_("368"));
	Choice2->Append(_("369"));
	Choice2->Append(_("370"));
	Choice2->Append(_("371"));
	Choice2->Append(_("372"));
	Choice2->Append(_("373"));
	Choice2->Append(_("374"));
	Choice2->Append(_("375"));
	Choice2->Append(_("376"));
	Choice2->Append(_("377"));
	Choice2->Append(_("378"));
	Choice2->Append(_("379"));
	Choice2->Append(_("380"));
	Choice2->Append(_("381"));
	Choice2->Append(_("382"));
	Choice2->Append(_("383"));
	Choice2->Append(_("384"));
	Choice2->Append(_("385"));
	Choice2->Append(_("386"));
	Choice2->Append(_("387"));
	Choice2->Append(_("388"));
	Choice2->Append(_("389"));
	Choice2->Append(_("390"));
	Choice2->Append(_("391"));
	Choice2->Append(_("392"));
	Choice2->Append(_("393"));
	Choice2->Append(_("394"));
	Choice2->Append(_("395"));
	Choice2->Append(_("396"));
	Choice2->Append(_("397"));
	Choice2->Append(_("398"));
	Choice2->Append(_("399"));
	Choice2->Append(_("400"));
	Choice2->Append(_("401"));
	Choice2->Append(_("402"));
	Choice2->Append(_("403"));
	Choice2->Append(_("404"));
	Choice2->Append(_("405"));
	Choice2->Append(_("406"));
	Choice2->Append(_("407"));
	Choice2->Append(_("408"));
	Choice2->Append(_("409"));
	Choice2->Append(_("410"));
	Choice2->Append(_("411"));
	Choice2->Append(_("412"));
	Choice2->Append(_("413"));
	Choice2->Append(_("414"));
	Choice2->Append(_("415"));
	Choice2->Append(_("416"));
	Choice2->Append(_("417"));
	Choice2->Append(_("418"));
	Choice2->Append(_("419"));
	Choice2->Append(_("420"));
	Choice2->Append(_("421"));
	Choice2->Append(_("422"));
	Choice2->Append(_("423"));
	Choice2->Append(_("424"));
	Choice2->Append(_("425"));
	Choice2->Append(_("426"));
	Choice2->Append(_("427"));
	Choice2->Append(_("428"));
	Choice2->Append(_("429"));
	Choice2->Append(_("430"));
	Choice2->Append(_("431"));
	Choice2->Append(_("432"));
	Choice2->Append(_("433"));
	Choice2->Append(_("434"));
	Choice2->Append(_("435"));
	Choice2->Append(_("436"));
	Choice2->Append(_("437"));
	Choice2->Append(_("438"));
	Choice2->Append(_("439"));
	Choice2->Append(_("440"));
	Choice2->Append(_("441"));
	Choice2->Append(_("442"));
	Choice2->Append(_("443"));
	Choice2->Append(_("444"));
	Choice2->Append(_("445"));
	Choice2->Append(_("446"));
	Choice2->Append(_("447"));
	Choice2->Append(_("448"));
	Choice2->Append(_("449"));
	Choice2->Append(_("450"));
	Choice2->Append(_("451"));
	Choice2->Append(_("452"));
	Choice2->Append(_("453"));
	Choice2->Append(_("454"));
	Choice2->Append(_("455"));
	Choice2->Append(_("456"));
	Choice2->Append(_("457"));
	Choice2->Append(_("458"));
	Choice2->Append(_("459"));
	Choice2->Append(_("460"));
	Choice2->Append(_("461"));
	Choice2->Append(_("462"));
	Choice2->Append(_("463"));
	Choice2->Append(_("464"));
	Choice2->Append(_("465"));
	Choice2->Append(_("466"));
	Choice2->Append(_("467"));
	Choice2->Append(_("468"));
	Choice2->Append(_("469"));
	Choice2->Append(_("470"));
	Choice2->Append(_("471"));
	Choice2->Append(_("472"));
	Choice2->Append(_("473"));
	Choice2->Append(_("474"));
	Choice2->Append(_("475"));
	Choice2->Append(_("476"));
	Choice2->Append(_("477"));
	Choice2->Append(_("478"));
	Choice2->Append(_("479"));
	Choice2->Append(_("480"));
	Choice2->Append(_("481"));
	Choice2->Append(_("482"));
	Choice2->Append(_("483"));
	Choice2->Append(_("484"));
	Choice2->Append(_("485"));
	Choice2->Append(_("486"));
	Choice2->Append(_("487"));
	Choice2->Append(_("488"));
	Choice2->Append(_("489"));
	Choice2->Append(_("490"));
	Choice2->Append(_("491"));
	Choice2->Append(_("492"));
	Choice2->Append(_("493"));
	Choice2->Append(_("494"));
	Choice2->Append(_("495"));
	Choice2->Append(_("496"));
	Choice2->Append(_("497"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Lightput Channel 1 = DMX Channel"), wxPoint(216,48), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	CheckBox3 = new wxCheckBox(this, ID_CHECKBOX3, _("Copy output to all 512 channels"), wxPoint(216,72), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	CheckBox3->SetValue(false);
	wxFont CheckBox3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox3->SetFont(CheckBox3Font);
	StaticBox6 = new wxStaticBox(this, ID_STATICBOX6, _("Light Scripts Options"), wxPoint(376,112), wxSize(159,72), 0, _T("ID_STATICBOX6"));
	wxFont StaticBox6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox6->SetFont(StaticBox6Font);
	CheckBox4 = new wxCheckBox(this, ID_CHECKBOX4, _("Start on Step 1"), wxPoint(384,128), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	CheckBox4->SetValue(false);
	wxFont CheckBox4Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox4->SetFont(CheckBox4Font);
	CheckBox5 = new wxCheckBox(this, ID_CHECKBOX5, _("Repeat"), wxPoint(384,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	CheckBox5->SetValue(false);
	wxFont CheckBox5Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox5->SetFont(CheckBox5Font);
	StaticBox7 = new wxStaticBox(this, ID_STATICBOX7, _("DMX Frequency"), wxPoint(16,176), wxSize(168,56), 0, _T("ID_STATICBOX7"));
	wxFont StaticBox7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticBox7->SetFont(StaticBox7Font);
	Choice1 = new wxChoice(this, ID_CHOICE3, wxPoint(24,200), wxSize(152,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
	Choice1->Append(_("16.6 Hz (default)"));
	Choice1->Append(_("12.5 Hz"));
	Choice1->Append(_("8 Hz"));
	Choice1->Append(_("4 Hz"));
	Choice1->Append(_("2 Hz"));
	Choice1->Append(_("1 Hz"));
	wxFont Choice1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Choice1->SetFont(Choice1Font);
	StaticBox8 = new wxStaticBox(this, ID_STATICBOX8, _("Startup Options"), wxPoint(200,192), wxSize(184,104), 0, _T("ID_STATICBOX8"));
	wxFont StaticBox8Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox8->SetFont(StaticBox8Font);
	CheckBox6 = new wxCheckBox(this, ID_CHECKBOX6, _("Start Lightput Minimized"), wxPoint(216,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	CheckBox6->SetValue(false);
	wxFont CheckBox6Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox6->SetFont(CheckBox6Font);
	CheckBox7 = new wxCheckBox(this, ID_CHECKBOX7, _("Light Program at startup"), wxPoint(216,240), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	CheckBox7->SetValue(false);
	wxFont CheckBox7Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	CheckBox7->SetFont(CheckBox7Font);
	Choice3 = new wxChoice(this, ID_CHOICE4, wxPoint(216,264), wxSize(152,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
	Choice3->Append(_("Light Sequencer"));
	Choice3->Append(_("Light Alarm Clock"));
	Choice3->Append(_("24-Hour Light Timer"));
	Choice3->Append(_("Midi Control"));
	Choice3->Append(_("Lightput External Input"));
	wxFont Choice3Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	Choice3->SetFont(Choice3Font);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Frequency Changes don\'t\ntake effect until the DMX\nengine is restarted.  DMX\nchannel options don\'t take\neffect until the Options\ndialog is closed."), wxPoint(392,216), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);

	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&Options::OnRadioButton1Select);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Options::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Options::OnButton2Click);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Options::OnCheckBox1Click);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Options::OnCheckBox2Click);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&Options::OnChoice2Select);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Options::OnCheckBox3Click);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Options::OnCheckBox4Click);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Options::OnCheckBox5Click);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Options::OnCheckBox6Click);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Options::OnCheckBox7Click);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&Options::OnInit);
	//*)

	if (option_dmxmode == 4) RadioButton1->SetValue(true);
	if (option_dmxmode == 16) RadioButton2->SetValue(true);
	TextCtrl1->SetValue(option_defaultprofile);
	if (issmooth) CheckBox1->SetValue(true);
	if (issmoothstart) CheckBox2->SetValue(true);
    if (isDMXcascade) CheckBox3->SetValue(true);
    if (islsStartOn1) CheckBox4->SetValue(true);
    if (islsRepeat) CheckBox5->SetValue(true);

    //disable startup options in linux
    //if (isminimizedonstartup) CheckBox6->SetValue(true);
    //if (runlightprogramonstartup) CheckBox7->SetValue(true);
    StaticBox8->Enable(false);
    CheckBox6->Enable(false);
    CheckBox7->Enable(false);
    Choice3->Enable(false);

    Choice3->SetSelection(startuplightprogram);
    TransitionChoice->SetSelection(option_profiletime);
    Choice2->SetSelection(StartingDMXChannel);

    if (LightputFrequency == 2000) Choice1->SetSelection(6);
    if (LightputFrequency == 1000) Choice1->SetSelection(5);
    if (LightputFrequency == 500) Choice1->SetSelection(4);
    if (LightputFrequency == 250) Choice1->SetSelection(3);
    if (LightputFrequency == 120) Choice1->SetSelection(2);
    if (LightputFrequency == 80) Choice1->SetSelection(1);
    if (LightputFrequency == 60) Choice1->SetSelection(0);

}

Options::~Options()
{
	//(*Destroy(Options)
	//*)
}

//cancel button
void Options::OnButton2Click(wxCommandEvent& event)
{
    Destroy();
}

//save options button (OK button)
void Options::OnButton1Click(wxCommandEvent& event)
{

    wxString o1;
    //wxString o2;
    wxString o3;
    wxString o4;
    wxString o5;
    wxString o6;
    wxString o7;
    wxString o8; //light script variable
    wxString o9; //light script variable
    wxString o10; //Frequency setting
    wxString o11; //minimized
    wxString o12; //run light program
    wxString o13; //light program selection

    wxTextFile sofile;
    sofile.Create(wxT("options.lightput"));

    if (RadioButton1->GetValue()) option_dmxmode = 4;
    if (RadioButton2->GetValue()) option_dmxmode = 16;

    option_defaultprofile = TextCtrl1->GetValue();
    o3 = TransitionChoice->GetString(TransitionChoice->GetSelection());

    if (CheckBox1->GetValue()) issmooth = true;
    else issmooth = false;
    if (CheckBox2->GetValue()) issmoothstart = true;
    else issmoothstart = false;

    //wxMessageBox (option_defaultprofile, o1);

    o1 = wxString::Format(wxT("%i"),option_dmxmode);
    //o3 = wxString::Format(wxT("%i"),option_profiletime);
    o4 = wxString::Format(wxT("%i"),issmooth);
    o5 = wxString::Format(wxT("%i"),issmoothstart);
    o6 = wxString::Format(wxT("%i"),StartingDMXChannel);
    o7 = wxString::Format(wxT("%i"),isDMXcascade);
    o8 = wxString::Format(wxT("%i"),islsStartOn1);
    o9 = wxString::Format(wxT("%i"),islsRepeat);

    if (Choice1->GetSelection() == 0) o10 = wxT("60");
    if (Choice1->GetSelection() == 1) o10 = wxT("80");
    if (Choice1->GetSelection() == 2) o10 = wxT("120");
    if (Choice1->GetSelection() == 3) o10 = wxT("250");
    if (Choice1->GetSelection() == 4) o10 = wxT("500");
    if (Choice1->GetSelection() == 5) o10 = wxT("1000");
    if (Choice1->GetSelection() == 6) o10 = wxT("2000");
///not saving or recalling properly
    o11 = wxString::Format(wxT("%i"),isminimizedonstartup);
    o12 = wxString::Format(wxT("%i"),runlightprogramonstartup);

    o13 = wxString::Format(wxT("%i"),Choice3->GetSelection());


    sofile.AddLine(o1, wxTextFileType_Dos);
    sofile.AddLine(option_defaultprofile, wxTextFileType_Dos);
    sofile.AddLine(o3, wxTextFileType_Dos);
    sofile.AddLine(o4, wxTextFileType_Dos);
    sofile.AddLine(o5, wxTextFileType_Dos);
    sofile.AddLine(o6, wxTextFileType_Dos);
    sofile.AddLine(o7, wxTextFileType_Dos);
    sofile.AddLine(o8, wxTextFileType_Dos);
    sofile.AddLine(o9, wxTextFileType_Dos);
    sofile.AddLine(o10, wxTextFileType_Dos);
    sofile.AddLine(o11, wxTextFileType_Dos);
    sofile.AddLine(o12, wxTextFileType_Dos);
    sofile.AddLine(o13, wxTextFileType_Dos);

    //these lines save and close the file
    sofile.Write(wxTextFileType_Dos, wxConvISO8859_1);
    sofile.Close();
    Destroy();


}


void Options::OnRadioButton1Select(wxCommandEvent& event)
{

}

//light sequencer options smooth transitions
void Options::OnCheckBox1Click(wxCommandEvent& event)
{
    if (CheckBox1->GetValue()) issmooth = true;
    else issmooth = false;
}

//light sequencer options smooth start
void Options::OnCheckBox2Click(wxCommandEvent& event)
{
    if (CheckBox2->GetValue()) issmoothstart = true;
    else issmoothstart = false;
}

void Options::OnChoice2Select(wxCommandEvent& event)
{
    StartingDMXChannel = Choice2->GetSelection();
}

//copy DMX to 512 channels option
void Options::OnCheckBox3Click(wxCommandEvent& event)
{
    if (CheckBox3->GetValue()) isDMXcascade = true;
    else isDMXcascade = false;
}
//light script option start on 1
void Options::OnCheckBox4Click(wxCommandEvent& event)
{
    if (CheckBox4->GetValue()) islsStartOn1 = true;
    else islsStartOn1 = false;
}
//light script option repeat
void Options::OnCheckBox5Click(wxCommandEvent& event)
{
    if (CheckBox4->GetValue()) islsRepeat = true;
    else islsRepeat = false;
}

void Options::OnInit(wxInitDialogEvent& event)
{
}

void Options::OnChoice1Select(wxCommandEvent& event)
{
}
//minimize on start box
void Options::OnCheckBox6Click(wxCommandEvent& event)
{
    if (CheckBox6->IsChecked()) isminimizedonstartup = true;
    else isminimizedonstartup = false;
}

//load light program on start box
void Options::OnCheckBox7Click(wxCommandEvent& event)
{
    if (CheckBox7->IsChecked()) runlightprogramonstartup = true;
    else runlightprogramonstartup = false;
}
