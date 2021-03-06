/*
  SenseTarget.cpp - Library for detecting target using Pixycam
  Created by Jai Patil, October 27, 2018.
  Edited by Robert Wechsler, November 14, 2018.
  Released for Olin Fun Robo students.
*/

#include "Arduino.h"
#include "SenseTarget.h"
#include "Pixy.h"
#include "SPI.h"

/*
  CONSTRUCTOR
*/
SenseTarget::SenseTarget()
{ 
}

/*
  PIXYCAM FUNCTION
  Function that fills the bearing array with a gaussian function mapped from -90deg to 90deg,
  with a peak at location of the target, a set amplitude, and a specified variance. 
*/
void SenseTarget::getTargetBearing(int bearing[],int len, Pixy pixy,int blocks, int range, int curvebroadness)
{
  int amplitude = 0;
  if (range>=5 && range<=150)
  {
    amplitude = map(range,5,150,0,100);
  } else if (range > 150)
  {
    amplitude = 100;
  }

  if (blocks)
  {
    //Serial.print("In the library: ");
    //Serial.println(blocks);
    for (int i=0;i<blocks;i++)
    {
      //Serial.print("The signature: ");
      //Serial.println(pixy.blocks[i].signature);
      if(pixy.blocks[i].signature)
      {
         //required array indices
         double arraymidpoint = (len-1)/2.0;
         double arrayhalfwidth = (double)len*37.5/180.0;
         //Serial.print("The arraymidpoint and arrayhalfwidth: ");
         //Serial.println(arraymidpoint);
	       //Serial.println(arrayhalfwidth);

         //use map function to convert pixel values to bearing[] indices
         double targetcenter = (double)(pixy.blocks[i].x)*(2.0*arrayhalfwidth)/(319.0)+(arraymidpoint-arrayhalfwidth);
		
         double targetwidth = (double)(pixy.blocks[i].width)*arrayhalfwidth/(160);
         //Serial.print("The targetcenter and targethalfwidth: ");
         //Serial.println(targetcenter);
	       //Serial.println(targetwidth);
		
         
         //gaussian function = a*exp(-pow(x-b,2)/(2*pow(c,2))) 
         //in bearing[] with amplitude a = amplitude, b = targetcenter, c = targetwidth/curvesharpness
         for(int j=0; j<len; j++)
         {
            bearing[j]= 1.0+(double(amplitude*exp(-pow(j-targetcenter,2)/(2*pow(targetwidth*curvebroadness/1.5,2)))));
	          //Serial.print(bearing[j]);
	          //Serial.print("*");
	    
         }
      }
    }
  }
}

/*
  PIXYCAM FUNCTION
  Function that returns range of detected target based on calibrated distance measurements (in mm) 
*/
int SenseTarget::getTargetRange(Pixy pixy, int blocks)
{
  //Pixy pixy;
  //pixy.init();
  double range;
  //blocks = pixy.getBlocks();
  if (blocks)
  {
    //Serial.print("In the library: ");
    //Serial.println(blocks);
    for (int i=0;i<blocks;i++)
    {
     range= 183*exp(-0.0234*(double)pixy.blocks[i].height);  
      
      
    }
  }
  return (int)range;
}
