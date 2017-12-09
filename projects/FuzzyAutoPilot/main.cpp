// generated by Fast Light User Interface Designer (fluid) version 1.0109

#include "main.h"
#include "rota.h"
#include <stdlib.h>
int RotaLine,PlaneLine; 
static int k; 
double x,y,ry; 

Fl_PlotXY *plot=(Fl_PlotXY *)0;

Fl_Button *start=(Fl_Button *)0;

static void cb_start(Fl_Button*, void*) {
  SimulationStart();
}

Fl_Browser *out=(Fl_Browser *)0;

Fl_Value_Output *PRota=(Fl_Value_Output *)0;

Fl_Dial *Dm=(Fl_Dial *)0;

Fl_Value_Output *PPos=(Fl_Value_Output *)0;

Fl_Value_Output *PAngle=(Fl_Value_Output *)0;

int main(int argc, char **argv) {
  Fl_Double_Window* w;
  srand( time(NULL) );
 x=0;
 y=Rota(0);
 if(rand()%2)
   y+=rand()%50+20;
 else
   y-=rand()%50+20;
  { Fl_Double_Window* o = new Fl_Double_Window(727, 595, "Bulan\375k Mant\375k ile Otamatik Pilot");
    w = o;
    o->color((Fl_Color)31);
    o->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE);
    { plot = new Fl_PlotXY(5, 38, 715, 380);
      plot->box(FL_GTK_THIN_DOWN_BOX);
      plot->color((Fl_Color)38);
      plot->selection_color(FL_BACKGROUND_COLOR);
      plot->labeltype(FL_NORMAL_LABEL);
      plot->labelfont(0);
      plot->labelsize(14);
      plot->labelcolor(FL_FOREGROUND_COLOR);
      plot->align(FL_ALIGN_CENTER);
      plot->when(FL_WHEN_RELEASE);
      RotaLine=plot->newline(0,-10,73,210,FL_PLOTXY_FIXED,FL_RED,"");
      PlaneLine=plot->newline(0,-10,73,210,FL_PLOTXY_FIXED,FL_BLUE,"");
    } // Fl_PlotXY* plot
    { start = new Fl_Button(660, 3, 60, 25, "@>");
      start->tooltip("Similasyonu \307""al\375\376t\375r");
      start->box(FL_GTK_UP_BOX);
      start->color(FL_SELECTION_COLOR);
      start->labelcolor((Fl_Color)1);
      start->callback((Fl_Callback*)cb_start);
    } // Fl_Button* start
    { out = new Fl_Browser(5, 431, 400, 154);
      out->type(3);
      out->column_widths(widths);
      out->column_char('\t');
    } // Fl_Browser* out
    { PRota = new Fl_Value_Output(590, 437, 130, 24, "Rota Y :");
    } // Fl_Value_Output* PRota
    { Dm = new Fl_Dial(420, 433, 85, 75);
      Dm->type(1);
      Dm->color((Fl_Color)14);
      Dm->selection_color((Fl_Color)1);
      Dm->minimum(-30);
      Dm->maximum(30);
      Dm->step(1);
    } // Fl_Dial* Dm
    { Fl_Box* o = new Fl_Box(11, 21, 25, 7, "Rota");
      o->box(FL_THIN_UP_BOX);
      o->color((Fl_Color)1);
      o->align(FL_ALIGN_RIGHT);
    } // Fl_Box* o
    { Fl_Box* o = new Fl_Box(80, 21, 7, 7, "U\347""ak Pozisyonu");
      o->box(FL_OVAL_BOX);
      o->color((Fl_Color)4);
      o->align(FL_ALIGN_RIGHT);
    } // Fl_Box* o
    { PPos = new Fl_Value_Output(590, 476, 130, 24, "U\347""ak Y :");
    } // Fl_Value_Output* PPos
    { PAngle = new Fl_Value_Output(590, 516, 130, 24, "U\347""ak A\347\375s\375");
    } // Fl_Value_Output* PAngle
    o->end();
  } // Fl_Double_Window* o
  w->show(argc, argv);
  return Fl::run();
}

void SimulationStart() {
  x=0;
 y=Rota(0);
 k=rand()%100;
 if(rand()%2)
   y+=rand()%50+20;
 else
   y-=rand()%50+20;
   
 plot->clear(RotaLine);
 plot->clear(PlaneLine); 
 plot->drawmode(PlaneLine,FL_PLOTXY_DOT);
 out->clear();
 out->add(" Rota Yeri \t U�ak Yeri\t Rotadan Fark\t U�ak A��s�\t");
 PAngle->value(0);
 PPos->value(0);
 PRota->value(0);
 start->deactivate();
 Fl::add_timeout(0.15,Simulate);
}

double Rota(double t) {
  return (100*sin((double)3.14*(t+k)/36)+100);
}

void Simulate(void *) {
  char buf[252];
  int i;
  
  ry=Rota(x);
  sprintf(buf," %.1lf \t %.1lf \t %.1f \t %.1lf",ry,y,(ry-y),PAngle->value());
  plot->add(RotaLine,x,ry);
  PRota->value(ry);
  plot->add(PlaneLine,x,y);     
  PPos->value(y);  
  plot->redraw();
  out->add(buf); 
  y=GetNewY(y,ry,Rota(x+1));         
  
  if(x<72)
     Fl::add_timeout(0.15,Simulate); 
   else
     start->activate();
  x=x+1;
}

double GetNewY(double y,double ry,double ryn ) {
  double Dy1,Dy2;
    Dy1=y-ry;
    Dy2=y-ryn;

    DeltaPNow[LEFT]=sfl_fuzzyfier_s(Dy1, -50.0, 0.0);
    DeltaPNow[CENTER]=sfl_fuzzyfier_a(Dy1, -25.0, 0.0 , 25.0 );
    DeltaPNow[RIGHT]=sfl_fuzzyfier_z(Dy1, 0.0, 50.0);

    DeltaPNext[LEFT]=sfl_fuzzyfier_s(Dy2, -50.0, 0.0);
    DeltaPNext[CENTER]=sfl_fuzzyfier_a(Dy2, -25.0, 0.0 , 25.0 );
    DeltaPNext[RIGHT]=sfl_fuzzyfier_z(Dy2, 0.0, 50.0);

    Angle[BIGLEFT]=sfl_and(DeltaPNow[LEFT],DeltaPNext[LEFT]);
    Angle[ALEFT]=sfl_or(sfl_and(DeltaPNow[LEFT],DeltaPNext[CENTER]),sfl_and(DeltaPNow[CENTER],DeltaPNext[LEFT]));

    Angle[ACENTER]=sfl_or(sfl_or(sfl_and(DeltaPNow[LEFT],DeltaPNext[RIGHT]),sfl_and(DeltaPNow[CENTER],DeltaPNext[CENTER])),sfl_and(DeltaPNow[RIGHT],DeltaPNext[LEFT]));
    Angle[ARIGHT]=sfl_or(sfl_and(DeltaPNow[RIGHT],DeltaPNext[CENTER]),sfl_and(DeltaPNow[CENTER],DeltaPNext[RIGHT]));
    Angle[BIGRIGHT]=sfl_and(DeltaPNow[RIGHT],DeltaPNext[RIGHT]);

    double a=sfl_defuzzyfier_coa(5,Angle,angle_maxima);
    PAngle->value(a); 
    Dm->value(a);
//    printf( "Angle %lf \n\n",a);

    return (y-100*tan(3.14*a/360));
}
