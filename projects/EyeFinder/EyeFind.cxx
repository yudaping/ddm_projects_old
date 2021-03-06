// generated by Fast Light User Interface Designer (fluid) version 1.0109

#include "EyeFind.h"
IplImage *img; 
Fl_Capture Cap; 
CvMemStorage* storage; 
static char* cascade_names[] ={"haarcascade_frontalface_alt.xml",
                               "haarcascade_frontalface_alt2.xml",
                               "haarcascade_frontalface_alt_tree.xml",
                               "haarcascade_frontalface_default.xml",                                                                                          
                               "haarcascade_profileface.xml",
                               "haarcascade_upperbody.xml",
                               "haarcascade_lowerbody.xml",
                               "haarcascade_fullbody.xml"                         
                               }; 
CvHaarClassifierCascade* cascade; 
Fl_OpenCV *Pict; 
EyeFinder *Eyes; 

Fl_Double_Window *Win=(Fl_Double_Window *)0;

Fl_Button *Open=(Fl_Button *)0;

static void cb_Open(Fl_Button*, void*) {
  if(Source->value()==1)
  OpenVideo_CB();

if(Source->value()==0)
  Open_CB();
}

Fl_Scroll *Board=(Fl_Scroll *)0;

Fl_Output *FName=(Fl_Output *)0;

Fl_Button *Bul=(Fl_Button *)0;

static void cb_Bul(Fl_Button*, void*) {
  FindFaces();
Board->redraw();
Save->activate();
}

Fl_Choice *Source=(Fl_Choice *)0;

static void cb_Source(Fl_Choice*, void*) {
  if(Source->value()==2){
  if(!Cap.CaptureFromCAM(-1)) return;
  Bul->activate();
  playing=true;
  Bul->label("Stop!");
  Cap.SetFrameWidth(Pict->w());
  Cap.SetFrameHeight(Pict->h());
  Fl::add_timeout(0.05, Playing_CB);  
  
};
}

Fl_Button *Save=(Fl_Button *)0;

static void cb_Save(Fl_Button*, void*) {
  char* file;
if(playing){ 
 playing=false;
 Bul->label("Find");
}
file = fl_file_chooser("Save","Picture (*.{jpg,png,bmp,dib,sr,ras,pbm,pgm,ppm,tif,tiff})\t", 0);
if(file==NULL) return;
Pict->Save(file);
}

static void cb_(Fl_Button*, void*) {
  if(playing){ 
 playing=false;
 Bul->label("Find");
}
AboutDlg *ab=new AboutDlg();
ab->show();
}

Fl_Double_Window* make_window() {
  { Win = new Fl_Double_Window(664, 534, "Eye Finder");
    Win->color((Fl_Color)30);
    { Open = new Fl_Button(474, 6, 21, 24, "...");
      Open->tooltip("Open");
      Open->box(FL_GTK_THIN_UP_BOX);
      Open->color(FL_SELECTION_COLOR);
      Open->labelfont(1);
      Open->labelsize(18);
      Open->callback((Fl_Callback*)cb_Open);
    } // Fl_Button* Open
    { Board = new Fl_Scroll(10, 40, 645, 485);
      Board->box(FL_EMBOSSED_FRAME);
      Board->color((Fl_Color)31);
      Pict=new Fl_OpenCV(12,42,640,480);
      Board->add(Pict);
      Pict->FitWindows();
      Board->end();
    } // Fl_Scroll* Board
    { FName = new Fl_Output(152, 6, 312, 24);
    } // Fl_Output* FName
    { Bul = new Fl_Button(505, 6, 55, 24, "Find");
      Bul->tooltip("Open");
      Bul->box(FL_GTK_THIN_UP_BOX);
      Bul->color(FL_SELECTION_COLOR);
      Bul->labelfont(1);
      Bul->labelsize(18);
      Bul->callback((Fl_Callback*)cb_Bul);
      Bul->deactivate();
      LoadHaarClassifier();
    } // Fl_Button* Bul
    { Source = new Fl_Choice(10, 7, 128, 23);
      Source->down_box(FL_BORDER_BOX);
      Source->callback((Fl_Callback*)cb_Source);
      Source->when(FL_WHEN_CHANGED);
      Source->add("Photo");
      Source->add("Video");
      Source->add("WebCam");
      Source->value(0);
    } // Fl_Choice* Source
    { Save = new Fl_Button(565, 6, 55, 24, "Save");
      Save->box(FL_GTK_THIN_UP_BOX);
      Save->color(FL_SELECTION_COLOR);
      Save->labelfont(3);
      Save->labelcolor((Fl_Color)1);
      Save->callback((Fl_Callback*)cb_Save);
      Save->deactivate();
    } // Fl_Button* Save
    { Fl_Button* o = new Fl_Button(630, 6, 21, 24, "?");
      o->tooltip("Open");
      o->box(FL_GTK_THIN_UP_BOX);
      o->color((Fl_Color)9);
      o->labelfont(1);
      o->labelsize(18);
      o->labelcolor((Fl_Color)4);
      o->callback((Fl_Callback*)cb_);
    } // Fl_Button* o
    Win->end();
  } // Fl_Double_Window* Win
  return Win;
}

int main(int argc, char **argv) {
  Fl_Window  * window;
img=0;
storage = 0;
cascade = 0;
Eyes=new EyeFinder();
playing=false;
window = make_window( );
window->show( argc, argv );
return ( Fl :: run( ) );
  return Fl::run();
}

void Open_CB() {
  char* file;

file = fl_file_chooser("Open", "Picture (*.{jpg,png,bmp,dib,sr,ras,pbm,pgm,ppm,tif,tiff})\t", 0);
if(file==NULL) return;
FName->value(file);

// if(img)  cvReleaseImage(&img);

Pict->Load(file, 1); 
img=Pict->image;
// Board->redraw();
Win->redraw();
Bul->activate();
}

void OpenVideo_CB() {
  char* file;

file = fl_file_chooser("Open", "Picture (*.{avi})\t", 0);
if(file==NULL) return;
FName->value(file);
if(!Cap.CaptureFromFile(file)) return;
Bul->activate();
Pict->SetImage(Cap.GetFrame());
Board->redraw();
}

void FindFaces() {
  int nobj=0;

if(playing){ 
 playing=false;
 Bul->label("Find");
 return;
}
if(Source->value()>0){
 playing=true;
 Bul->label("Stop!");
 Fl::add_timeout(0.05, Playing_CB);
 return;
/*
 do{
   if(playing==false) break;
   Pict->GetFrame();
   img=Pict->image;
   nobj=nobj+detect_and_draw();
   Pict->ShowFrame();
   Board->redraw();
   Fl::wait(0);
  }while(Pict->GetPositionPercent()<99.0);
*/

}
else{
  nobj=detect_and_draw();
  Board->redraw();
}  

if(nobj==0)
  fl_message("Sorry Cant Find Any Face ! ");
else
  fl_message("%d Face Found ",nobj);
}

int detect_and_draw() {
  static CvScalar colors[] =
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };

    double scale = 1.3;
    IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
    IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
                         cvRound (img->height/scale)),
                     8, 1 );
    int i;

    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvResize( gray, small_img, CV_INTER_LINEAR );
    cvEqualizeHist( small_img, small_img );
    cvClearMemStorage( storage );


    if( cascade )
    {
//        double t = (double)cvGetTickCount();
        CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
                                            1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                                            cvSize(30, 30) );
//        t = (double)cvGetTickCount() - t;
//        printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
        Eyes->SetImage(img);
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {

            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

            CvPoint leftup,rightdown;
            leftup.x = cvRound(r->x *scale);
            leftup.y = cvRound(r->y *scale);
            rightdown.x = cvRound((r->x + r->width)*scale);
            rightdown.y = cvRound((r->y + r->height)*scale);
            int gap=rightdown.x-leftup.x;
            cvRectangle(img,leftup,rightdown, colors[i%8], 3, 8, 0 );
            Eyes->SetFaceRect(leftup.x,leftup.y,rightdown.x,rightdown.y);
            Eyes->Find();
            CvPoint center;
            center.x =Eyes->leftX;
            center.y =Eyes->leftY;
            cvCircle( img, center, 3+gap/64, colors[i%8], 1+gap/64, 8, 0 );            

            center.x =Eyes->rightX;
            center.y =Eyes->rightY;
            cvCircle( img, center, 3+gap/64, colors[i%8], 1+gap/64, 8, 0 );            



/*
            CvPoint center;
            int radius;
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );
*/
        }
    }

    cvReleaseImage( &gray );
    cvReleaseImage( &small_img );
    return i;
}

void LoadHaarClassifier() {
  if(cascade )
  cvReleaseHaarClassifierCascade(&cascade);

cascade = (CvHaarClassifierCascade*)cvLoad( cascade_names[0], 0, 0, 0 );
  
if( !cascade )
{
    fl_alert("S�n�fland�r�c� y�klenemedi ! ");

    exit(-1);
}
storage = cvCreateMemStorage(0);
}

void Video_FindFaces() {
  int nobj=detect_and_draw();
if(nobj==0)
  fl_message("Malesef Hi� bir �ey  bulamad�m :( ");
else
  fl_message("%d Nesne Bulundu :)",nobj);
}

void Playing_CB(void*) {
  if(playing==false) return;
if(Cap.GetPositionPercent()>=99.0) return;
img=Cap.GetFrame();
detect_and_draw();
Pict->SetImage(img);
Board->redraw();
Fl::wait(0);

Fl::add_timeout(0.05, Playing_CB);
}

AboutDlg::AboutDlg() {
  { Fl_Double_Window* o = window = new Fl_Double_Window(400, 225, "About");
    window->box(FL_GTK_DOWN_BOX);
    window->color((Fl_Color)22);
    window->user_data((void*)(this));
    window->align(FL_ALIGN_CENTER);
    { Ok = new Fl_Return_Button(260, 184, 130, 30, "Ok");
      Ok->box(FL_GTK_THIN_UP_BOX);
      Ok->color(FL_SELECTION_COLOR);
      Ok->callback((Fl_Callback*)cb_Ok);
    } // Fl_Return_Button* Ok
    { Info = new Fl_Browser(10, 14, 380, 160);
      Info->box(FL_GTK_DOWN_BOX);
      Info->color((Fl_Color)31);
      Info->textcolor(4);
    } // Fl_Browser* Info
    o->set_modal();
    window->end();
  } // Fl_Double_Window* window
}

void AboutDlg::show() {
  Info->add("@l@c@C1Eye Finder");
Info->add("  Finds Eyes by using Neural Networks");
Info->add("* Programmed by BlueKid");
Info->add("  http://derindelimavi.blogspot.com/");
Info->add("* Please Send me any suggestion, modification or bugs.");
Info->add(" Don't hesitate to contact me for any question");
Info->add(" I will be very grateful with your feedbacks.");
Info->add(" bluekid70@gmail.com");

window->show();
}

void AboutDlg::hide() {
  window->hide();
}

void cb_Ok(Fl_Return_Button*o, void*w) {
  ((Fl_Window *)(o->parent()))->hide();
}
