// generated by Fast Light User Interface Designer (fluid) version 1.0108

#include "main.h"

Fl_Double_Window *window_main=(Fl_Double_Window *)0;

Fl_Input *Age=(Fl_Input *)0;

static void cb_Result(Fl_Button*, void*) {
  Hesapla();
}

Fl_Output *To=(Fl_Output *)0;

Fl_Choice *Sex=(Fl_Choice *)0;

Fl_Choice *Chest=(Fl_Choice *)0;

Fl_Input *BPress=(Fl_Input *)0;

Fl_Input *Cholestral=(Fl_Input *)0;

Fl_Choice *Ecg=(Fl_Choice *)0;

Fl_Input *HRate=(Fl_Input *)0;

Fl_Choice *Exc=(Fl_Choice *)0;

Fl_Input *Oldpeak=(Fl_Input *)0;

Fl_Choice *Slope=(Fl_Choice *)0;

Fl_Choice *NVessel=(Fl_Choice *)0;

Fl_Choice *Thal=(Fl_Choice *)0;

Fl_Choice *BSugar=(Fl_Choice *)0;

int main(int argc, char **argv) {
  { window_main = new Fl_Double_Window(480, 559, "Heart disease");
    window_main->box(FL_PLASTIC_UP_BOX);
    window_main->color(FL_INACTIVE_COLOR);
    window_main->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE);
    { Age = new Fl_Input(305, 10, 100, 24, "Age (20 -100 ) :");
      Age->type(1);
      Age->labelfont(9);
      Age->labelsize(22);
    } // Fl_Input* Age
    { Fl_Button* o = new Fl_Button(35, 494, 115, 26, "Result @->");
      o->box(FL_PLASTIC_UP_BOX);
      o->color((Fl_Color)4);
      o->callback((Fl_Callback*)cb_Result);
    } // Fl_Button* o
    { To = new Fl_Output(170, 496, 280, 24);
      To->labelfont(9);
      To->labelsize(22);
    } // Fl_Output* To
    { Fl_Choice* o = Sex = new Fl_Choice(305, 44, 115, 24, "Sex :");
      Sex->down_box(FL_BORDER_BOX);
      Sex->labelfont(9);
      Sex->labelsize(22);
      Sex->add("Female");
      Sex->add("Male");
      o->value(0);
    } // Fl_Choice* Sex
    { Fl_Choice* o = Chest = new Fl_Choice(305, 78, 115, 24, "Chest Pain Type :");
      Chest->down_box(FL_BORDER_BOX);
      Chest->labelfont(9);
      Chest->labelsize(22);
      Chest->add("Angina");
      Chest->add("Abnang");
      Chest->add("Notang");
      Chest->add("Asympt"); o->value(0);
    } // Fl_Choice* Chest
    { BPress = new Fl_Input(305, 116, 100, 24, "Blood Pressure (70-190) :");
      BPress->type(1);
      BPress->labelfont(9);
      BPress->labelsize(22);
    } // Fl_Input* BPress
    { Cholestral = new Fl_Input(305, 150, 100, 24, "Cholesteral (120-580) :");
      Cholestral->type(1);
      Cholestral->labelfont(9);
      Cholestral->labelsize(22);
    } // Fl_Input* Cholestral
    { Fl_Choice* o = Ecg = new Fl_Choice(305, 215, 115, 24, "Electrocardiographic Results :");
      Ecg->down_box(FL_BORDER_BOX);
      Ecg->labelfont(9);
      Ecg->labelsize(22);
      Ecg->add("Norm");
      Ecg->add("Abn");
      Ecg->add("Hyp");
      o->value(0);
    } // Fl_Choice* Ecg
    { HRate = new Fl_Input(305, 255, 100, 24, "Max heart rate (60-210) :");
      HRate->type(1);
      HRate->labelfont(9);
      HRate->labelsize(22);
    } // Fl_Input* HRate
    { Fl_Choice* o = Exc = new Fl_Choice(305, 289, 115, 24, "Exercise Induced Angina :");
      Exc->down_box(FL_BORDER_BOX);
      Exc->labelfont(9);
      Exc->labelsize(22);
      Exc->add("True");
      Exc->add("False");
      o->value(0);
    } // Fl_Choice* Exc
    { Oldpeak = new Fl_Input(305, 320, 100, 24, "Oldpeak (0-5) :");
      Oldpeak->type(1);
      Oldpeak->labelfont(9);
      Oldpeak->labelsize(22);
    } // Fl_Input* Oldpeak
    { Fl_Choice* o = Slope = new Fl_Choice(305, 360, 115, 24, "Slope :");
      Slope->tooltip("the slope of the peak exercise ST segment");
      Slope->down_box(FL_BORDER_BOX);
      Slope->labelfont(9);
      Slope->labelsize(22);
      Slope->add("Up");
      Slope->add("Flat");
      Slope->add("Down");
      o->value(0);
    } // Fl_Choice* Slope
    { Fl_Choice* o = NVessel = new Fl_Choice(305, 400, 55, 24, "Number of vessels colored :");
      NVessel->down_box(FL_BORDER_BOX);
      NVessel->labelfont(9);
      NVessel->labelsize(22);
      NVessel->add("0");
      NVessel->add("1");
      NVessel->add("2");
      NVessel->add("3");o->value(0);
    } // Fl_Choice* NVessel
    { Fl_Choice* o = Thal = new Fl_Choice(305, 434, 150, 24, "Thal :");
      Thal->down_box(FL_BORDER_BOX);
      Thal->labelfont(9);
      Thal->labelsize(22);
      Thal->add("Normal");
      Thal->add("Fixed Defect");
      Thal->add("Reversable defect");o->value(0);
    } // Fl_Choice* Thal
    { Fl_Choice* o = BSugar = new Fl_Choice(305, 184, 115, 24, "Fasting Blood Sugar  <  120  :");
      BSugar->down_box(FL_BORDER_BOX);
      BSugar->labelfont(9);
      BSugar->labelsize(22);
      BSugar->add("True");
      BSugar->add("False");
      o->value(0);
    } // Fl_Choice* BSugar
    window_main->end();
  } // Fl_Double_Window* window_main
  window_main->show(argc, argv);
  return Fl::run();
}

void Hesapla() {
  char buf[50];
float to;
fann_type *out;
fann_type input[25];
int ch;

struct fann *ann = fann_create_from_file("heart.net");
if(ann==NULL){
   fl_alert("Can not Open Neural Network File - heart.net - " );
   return;
}
// Init
for(int i=0;i<25;i++)input[i]=0;

// Age
input[0]=atof(Age->value());
//Normalizasyon
//  
input[0]=(input[0]-20.0)/80.0;
// Sex
input[1]=Sex->value();

// Chest PainType
ch=(int)Chest->value();
switch (ch){
   case 0: input[2]=1;
          break; 
   case 1: input[3]=1;
          break; 
   case 2: input[4]=1;
          break; 
   case 3: input[5]=1;
          break;                     

}

// Bload Press
input[6]=atof(BPress->value());
input[6]=(input[6]-70.0)/120.0;

// Cholestral
input[7]=atof(Cholestral->value());
input[7]=(input[7]-120.0)/460.0;

//Fasting blood sugar 
input[8]=BSugar->value();

// Chest PainType
ch=(int)Ecg->value();
switch (ch){
   case 0: input[9]=1;
          break; 
   case 1: input[10]=1;
          break; 
   case 2: input[11]=1;
          break;          

}

// Heart Rate
input[12]=atof(HRate->value());
input[12]=(input[12]-60.0)/150.0;


//Exc
input[13]=Exc->value();

// Oldpeak
input[14]=atof(Oldpeak->value());
input[14]=(input[14])/5.0;

// Slope
ch=(int)Slope->value();
switch (ch){
   case 0: input[15]=1;
          break; 
   case 1: input[16]=1;
          break; 
   case 2: input[17]=1;
          break;          

}

// Number of Vessel
ch=(int)NVessel->value();
switch (ch){
   case 0: input[18]=1;
          break; 
   case 1: input[19]=1;
          break; 
   case 2: input[20]=1;
          break; 
   case 3: input[21]=1;
          break;                     

}

// Thal
ch=(int)Thal->value();
switch (ch){
   case 0: input[22]=1;
          break; 
   case 1: input[23]=1;
          break; 
   case 2: input[24]=1;
          break;          

}


out = fann_run(ann, input);
if(*out<0.5) 
   sprintf(buf,"Healthy  %% %.2f",100*((*out)+0.5)/0.5);   
else
   sprintf(buf,"heart disease  %% %.2f",100*(*out));   

To->value(buf);
fann_destroy(ann);
}
