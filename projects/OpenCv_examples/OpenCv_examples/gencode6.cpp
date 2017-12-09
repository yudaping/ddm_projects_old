/* This Code generated by cvPreprocessor ver 0.5 */
#include <cv.h>
#include <highgui.h>

IplImage* img,*pimg,*timg;
void Process();

int main( )
{
   Process();
   if(img){
     cvNamedWindow( "Source", 1 );
     cvShowImage( "Source", img );
   }
   if(pimg){
     cvNamedWindow( "Processed Image", 1 );
     cvShowImage( "Processed Image", pimg );
   }
   cvWaitKey(0);

   if(img)
     cvReleaseImage(&img);
   if(pimg)
     cvReleaseImage(&pimg);

}
void Process()
{

/* Loads Images */
  if(img)
    cvReleaseImage(&img);
  img=cvLoadImage( "03.jpg ", CV_LOAD_IMAGE_UNCHANGED );

/* Aplly Black Hat Morphological Operation */
{
  IplConvKernel *element;
  if(pimg)
    cvReleaseImage(&pimg);
  pimg= cvCloneImage (img);
  element = cvCreateStructuringElementEx (9,9,4,4,CV_SHAPE_RECT, NULL);
  timg= cvCloneImage (img);
  cvMorphologyEx (img, pimg, timg,element,CV_MOP_BLACKHAT , 1);
  cvReleaseImage (&timg);
  cvReleaseStructuringElement(&element );
}
}
