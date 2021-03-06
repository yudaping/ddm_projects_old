// generated by Fast Light User Interface Designer (fluid) version 1.0109

#include "Blobs.h"
IplImage *src; 
CBlobResult blobs; 
Fl_OpenCV *Pict; 

Fl_Double_Window *Win=(Fl_Double_Window *)0;

Fl_Button *Open=(Fl_Button *)0;

Fl_Scroll *Board=(Fl_Scroll *)0;

Fl_Output *FName=(Fl_Output *)0;

Fl_Button *Save=(Fl_Button *)0;

Fl_Button *Find=(Fl_Button *)0;

static void cb_Find(Fl_Button*, void*) {
  Apply();
}

Fl_Counter *No=(Fl_Counter *)0;

static void cb_No(Fl_Counter*, void*) {
  ShowBlob();
}

Fl_Value_Slider *Thresh=(Fl_Value_Slider *)0;

Fl_Value_Slider *MBlob=(Fl_Value_Slider *)0;

Fl_Counter *Stype=(Fl_Counter *)0;

Fl_Double_Window* make_window() {
  { Win = new Fl_Double_Window(654, 551, "cvBlobsLib Demo ");
    Win->tooltip("http://derindelimavi.blogspot.com/");
    Win->color((Fl_Color)23);
    { Open = new Fl_Button(425, 4, 30, 26, "...");
      Open->tooltip("Open");
      Open->box(FL_GTK_THIN_UP_BOX);
      Open->color(FL_SELECTION_COLOR);
      Open->labelfont(1);
      Open->labelsize(18);
      Open->callback((Fl_Callback*)Open_CB);
    } // Fl_Button* Open
    { Board = new Fl_Scroll(5, 65, 640, 480);
      Board->box(FL_FLAT_BOX);
      Board->color((Fl_Color)19);
      Pict=new Fl_OpenCV(Board->x(),Board->y(),Board->w(),Board->h());
      Board->add(Pict);
      Pict->FitWindows();
      Board->end();
    } // Fl_Scroll* Board
    { FName = new Fl_Output(55, 6, 360, 24, "Image :");
    } // Fl_Output* FName
    { Save = new Fl_Button(559, 4, 86, 26, "Save Blobs");
      Save->tooltip("Open");
      Save->box(FL_GTK_UP_BOX);
      Save->color(FL_SELECTION_COLOR);
      Save->labelfont(1);
      Save->labelsize(10);
      Save->callback((Fl_Callback*)Save_CB);
      Save->deactivate();
    } // Fl_Button* Save
    { Find = new Fl_Button(460, 4, 91, 26, "Find Blobs");
      Find->tooltip("Open");
      Find->box(FL_GTK_UP_BOX);
      Find->color(FL_SELECTION_COLOR);
      Find->labelfont(1);
      Find->labelsize(10);
      Find->callback((Fl_Callback*)cb_Find);
      Find->deactivate();
    } // Fl_Button* Find
    { No = new Fl_Counter(45, 36, 95, 24, "Blob :");
      No->type(1);
      No->box(FL_GTK_UP_BOX);
      No->color((Fl_Color)21);
      No->labelcolor((Fl_Color)4);
      No->minimum(0);
      No->maximum(10);
      No->step(1);
      No->callback((Fl_Callback*)cb_No);
      No->align(FL_ALIGN_LEFT);
    } // Fl_Counter* No
    { Thresh = new Fl_Value_Slider(415, 34, 136, 26, "Thrsh :");
      Thresh->tooltip("Threshold value");
      Thresh->type(5);
      Thresh->box(FL_GTK_UP_BOX);
      Thresh->color((Fl_Color)21);
      Thresh->maximum(255);
      Thresh->step(1);
      Thresh->value(100);
      Thresh->textsize(14);
      Thresh->align(FL_ALIGN_LEFT);
    } // Fl_Value_Slider* Thresh
    { MBlob = new Fl_Value_Slider(205, 36, 155, 24, "Min Blob");
      MBlob->tooltip("discard the blobs with less area ...  pixels");
      MBlob->type(5);
      MBlob->box(FL_GTK_UP_BOX);
      MBlob->color((Fl_Color)22);
      MBlob->minimum(1);
      MBlob->maximum(2500);
      MBlob->step(10);
      MBlob->value(1000);
      MBlob->textsize(14);
      MBlob->align(FL_ALIGN_LEFT);
    } // Fl_Value_Slider* MBlob
    { Stype = new Fl_Counter(565, 34, 80, 26);
      Stype->tooltip("Blob Showing Type");
      Stype->type(1);
      Stype->box(FL_GTK_UP_BOX);
      Stype->color((Fl_Color)21);
      Stype->labelcolor(FL_BACKGROUND2_COLOR);
      Stype->minimum(1);
      Stype->maximum(5);
      Stype->step(1);
      Stype->value(1);
      Stype->align(FL_ALIGN_LEFT);
    } // Fl_Counter* Stype
    Win->end();
  } // Fl_Double_Window* Win
  return Win;
}

int main(int argc, char **argv) {
  Fl_Window  * window;
src=0;
window = make_window( );
Fl::set_atclose(Close);
window->show( argc, argv );
return ( Fl :: run( ) );
  return Fl::run();
}

void Open_CB(Fl_Widget*,void*) {
  char* file;

file = fl_file_chooser("Open", "Picture (*.{jpg,png,bmp,dib,sr,ras,pbm,pgm,ppm,tif,tiff})\t", 0);
if(file==NULL) return;

FName->value(file);

if(src)
 cvReleaseImage(&src);
 
blobs.ClearBlobs();
No->deactivate();

Pict->Load(file, 0);
Save->activate();
Find->activate();
src=cvCloneImage(Pict->image);
Board->redraw();
}

void Apply() {
  int nblobs;
IplImage* tmp = 0;
tmp = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U,1);
cvThreshold( src, tmp, Thresh->value(), 255, CV_THRESH_BINARY );

blobs = CBlobResult( tmp, NULL, 255);
blobs.Filter( blobs, B_INCLUDE, CBlobGetArea(), B_GREATER, MBlob->value());
//	blobs.Filter( blobs, B_EXCLUDE, CBlobGetArea(), B_LESS, param2 );
nblobs=blobs.GetNumBlobs();
if(nblobs){ 
  fl_message("%d Blobs Found ( Area >=  %.0f pixel )",nblobs,MBlob->value());
  No->maximum(blobs.GetNumBlobs() - 1);
  No->activate();
  No->value(0);
  ShowBlob();
}
else
  fl_message("Nothing Found !  :( ");
  
cvReleaseImage(&tmp);
}

void Close(Fl_Window*,void*) {
  if(src)
 cvReleaseImage(&src);
exit(0);
}

void Save_CB(Fl_Widget*,void*) {
  char* file=NULL;
file = fl_file_chooser("Save", "Blob List(*.{txt})\t", file);
if(file==NULL) return;
blobs.PrintBlobs(file);
}

void ShowBlob() {
  IplImage *outputImage;
outputImage = cvCreateImage( cvSize( src->width, src->height ), IPL_DEPTH_8U, 3 );
cvMerge( src, src, src, NULL, outputImage );
CBlob bl;
blobs.GetNthBlob( CBlobGetPerimeter(), No->value(), bl);

// CvBox2D el=bl.GetEllipse();
// cvEllipse(, CvPoint center, CvSize axes, double angle, 0, 0, CV_RGB( 255, 0, 0 ));

// bl.FillBlob( outputImage, CV_RGB( 255, 0, 0 ));

int st=Stype->value();
CvBox2D bx;
CvPoint center;
CvSize size;

switch(st){
    case 1 :
     bl.FillBlob( outputImage, CV_RGB( 255, 0, 0 ));
    break;
    case 2:
      cvRectangle(outputImage,cvPoint(bl.MinX(),bl.MinY() ),cvPoint(bl.MaxX(), bl.MaxY() ), CV_RGB( 0,0,255),2);
    break;
    case 3:
      bl.FillBlob( outputImage, CV_RGB( 255, 0, 0 ));
      cvRectangle(outputImage,cvPoint(bl.MinX(),bl.MinY() ),cvPoint(bl.MaxX(), bl.MaxY() ), CV_RGB( 0,0,255),2);
    break;
    case 4:

       bx=bl.GetEllipse();
       center.x = cvRound(bx.center.x);
       center.y = cvRound(bx.center.y);
       size.width = cvRound(bx.size.width*0.5);
       size.height = cvRound(bx.size.height*0.5);
       bx.angle = -bx.angle;
       cvEllipse(outputImage, center, size,bx.angle, 0, 360, CV_RGB(0,0,255),2);
    break;
    case 5:
       bl.FillBlob( outputImage, CV_RGB( 255, 0, 0 ));
       bx=bl.GetEllipse();
       center.x = cvRound(bx.center.x);
       center.y = cvRound(bx.center.y);
       size.width = cvRound(bx.size.width*0.5);
       size.height = cvRound(bx.size.height*0.5);
       bx.angle = -bx.angle;
       cvEllipse(outputImage, center, size,bx.angle, 0, 360, CV_RGB(0,0,255),2);
    break;
}


Pict->SetImage(outputImage);
Board->redraw();
}
