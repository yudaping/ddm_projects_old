// generated by Fast Light User Interface Designer (fluid) version 1.0108

#ifndef BPlayer_h
#define BPlayer_h
#include <FL/Fl.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_ask.H>
#include "Fl_Drop_Browser.h"
#include "reklam.h"
#include "fl_sound.h"
#include "Fl_Scope.h"
#include "fl_ext_file_chooser.h"
#include <string>
using namespace std;
using namespace audiere;
extern Reklam *adv; 
extern string fname; 
extern int gap; 
extern Fl_Sound *sound; 
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
extern Fl_Button *Open;
extern Fl_Button *Play;
extern Fl_Button *Pause;
extern Fl_Button *Add;
extern Fl_Button *Delete;
extern Fl_Button *First;
extern Fl_Button *Previous;
extern Fl_Button *Next;
extern Fl_Button *Last;
extern Fl_Button *Up;
extern Fl_Button *Down;
extern Fl_Drop_Browser *PList;
#include <FL/Fl_Slider.H>
extern Fl_Slider *Position;
#include <FL/Fl_Value_Slider.H>
extern Fl_Value_Slider *Volume;
extern Fl_Value_Slider *Balance;
#include <FL/Fl_Clock.H>
#include <FL/Fl_Box.H>
extern Fl_Box *Playing;
#include <FL/Fl_Group.H>
extern Fl_Scope *wave;
extern Fl_Button *Load;
extern Fl_Button *Save;
extern Fl_Button *PInfo;
extern Fl_Button *Help;
extern Fl_Button *AudioCD;
Fl_Double_Window* make_window();
void Playing_CB(void*);
void PlayFile();
char * SelectFile();
#include <FL/Fl_Browser.H>
#include <FL/Fl_Return_Button.H>
extern void cb_Ok(Fl_Return_Button*, void*);

class Info {
public:
  Info();
  Fl_Double_Window *window;
  Fl_Browser *Not;
  Fl_Return_Button *Ok;
  void show();
};

class About {
public:
  About();
  Fl_Double_Window *window;
  Fl_Return_Button *Ok;
  Fl_Browser *Not;
  void show();
  void hide();
};
void cb_Ok(Fl_Return_Button*o, void*w);
#endif