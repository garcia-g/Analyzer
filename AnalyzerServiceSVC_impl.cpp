// -*-C++-*-
/*!
 * @file  AnalyzerServiceSVC_impl.cpp
 * @brief Service implementation code of AnalyzerService.idl
 * @date Nov 8, 2011
 *
 * Written by Gustavo Garcia
 * Robotics Lab @ NAIST
 * 
 */

#include "AnalyzerServiceSVC_impl.h"

//my adds
#include "Analyzer.h"

#include <string>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <vector>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;
////////////////////////

/*
 * Example implementational code for IDL interface OpenHRP::AnalyzerService
 */
AnalyzerServiceSVC_impl::AnalyzerServiceSVC_impl()
{
  // Please add extra constructor code here.
}

//my adds
AnalyzerServiceSVC_impl::AnalyzerServiceSVC_impl(Analyzer *p)
    :parent(p)
{
  allFlag = false;
  manipFlag = false;
  walkFlag = false;
}
///////////////////


AnalyzerServiceSVC_impl::~AnalyzerServiceSVC_impl()
{
  // Please add extra destructor code here.
}

//my adds
//Sleep in miliseconds
inline void Sleep(unsigned int time)
{
    struct timespec t,r;

    t.tv_sec    = time / 1000;
    t.tv_nsec   = (time % 1000) * 1000000;

    while(nanosleep(&t,&r)==-1)
        t = r;
}
//Splits strings
inline std::vector<std::string> splitString(const std::string& word, const std::string& split) {
    std::vector<std::string> result;
    boost::char_separator<char> pipe(split.c_str(), "", boost::keep_empty_tokens);
    boost::tokenizer<boost::char_separator<char> > tokens(word, pipe);

    for (boost::tokenizer<boost::char_separator<char> >::iterator i = tokens.begin(); i != tokens.end(); i++) {
        if (!(*i).empty())
            result.push_back(*i);
    }

    return result;
}
///////////


/*
 * Methods corresponding to IDL attributes and operations
 */
CORBA::Short AnalyzerServiceSVC_impl::analyze(const char* fileName, const char* runMode)
{
  //my adds  
  string impl_runMode(runMode);
  if(impl_runMode.compare("all")==0)
      allFlag = true;
  if(impl_runMode.compare("manipulationOnly")==0)
      manipFlag = true;
  if(impl_runMode.compare("walkingOnly")==0)
      walkFlag = true;
  OpenHRP::dSequence_var angleValues = new OpenHRP::dSequence;
  angleValues->length(34);
  for(int i(0);i<34;i++)  
      angleValues[i] = (CORBA::Double)0.0;
  string buf;
  vector<string> splitValues;
  ifstream myFile(fileName); 
  if(!myFile)
  {
    return 444;
  }
  else
  {
    while(getline(myFile,buf))
    {
	splitValues = splitString(buf," ");
	if(splitValues[0].compare("I") == 0)  //Initial pose
	{
	  splitValues.erase(splitValues.begin());
	  
	  angleValues[1] = (CORBA::Double)strtod(splitValues[1].c_str(),NULL);//  1 R_HIP_R
	  angleValues[2] = (CORBA::Double)strtod(splitValues[2].c_str(),NULL);//  2 R_HIP_P
	  angleValues[3] = (CORBA::Double)strtod(splitValues[3].c_str(),NULL);//  3 R_KNEE_P  
	  angleValues[4] = (CORBA::Double)strtod(splitValues[4].c_str(),NULL);//  4 R_ANKLE_P 
	  angleValues[5] = (CORBA::Double)strtod(splitValues[5].c_str(),NULL);//  5 R_ANKLE_R  
	  angleValues[7] = (CORBA::Double)strtod(splitValues[7].c_str(),NULL);//  7 L_HIP_R
	  angleValues[8] = (CORBA::Double)strtod(splitValues[8].c_str(),NULL);//  8 L_HIP_P
	  angleValues[9] = (CORBA::Double)strtod(splitValues[9].c_str(),NULL);//  9 L_KNEE_P
	  angleValues[10] = (CORBA::Double)strtod(splitValues[10].c_str(),NULL);// 10 L_ANKLE_P
	  angleValues[11] = (CORBA::Double)strtod(splitValues[11].c_str(),NULL);// 11 L_ANKLE_R
	  angleValues[12] = (CORBA::Double)strtod(splitValues[12].c_str(),NULL);// 12 CHEST_P    	      	      
	  //Right arm
	  angleValues[16] = (CORBA::Double)strtod(splitValues[16].c_str(),NULL);//R_SHOULDER_P = 16
	  angleValues[17] = (CORBA::Double)strtod(splitValues[17].c_str(),NULL);//R_SHOULDER_R = 17	      
	  angleValues[19] = (CORBA::Double)strtod(splitValues[19].c_str(),NULL);//R_ELBOW_P = 19	      
	  //Left arm
	  angleValues[25] = (CORBA::Double)strtod(splitValues[33].c_str(),NULL);//L_SHOULDER_P = 25
	  angleValues[26] = (CORBA::Double)strtod(splitValues[34].c_str(),NULL);//L_SHOULDER_R = 26	      
	  angleValues[28] = (CORBA::Double)strtod(splitValues[36].c_str(),NULL);//L_ELBOW_P = 28	      	      
	}
	else if(splitValues[0].compare("W") == 0)
	{
	  if(allFlag || walkFlag)
	  {
	    parent->m_service3->stabilizerOn();
	    parent->m_service0->setTargetPos(atof(splitValues[1].c_str()),0.0,atof(splitValues[2].c_str()));
	    Sleep(1000); //Pauses the robot motion
	    //parent->m_service3->stabilizerOff();
	    //Sleep(1000); //Pauses the robot motion
	  }
	}
	else if(splitValues[0].compare("M") == 0)
	{  
	  if(allFlag || manipFlag)
	  {
	    splitValues.erase(splitValues.begin());	  
	    //Left arm
	    angleValues[25] = (CORBA::Double)strtod(splitValues[33].c_str(),NULL); //L_SHOULDER_P = 25
	    angleValues[26] = (CORBA::Double)strtod(splitValues[34].c_str(),NULL); //L_SHOULDER_R = 26
	    angleValues[27] = (CORBA::Double)strtod(splitValues[35].c_str(),NULL); //L_SHOULDER_Y = 27
	    angleValues[28] = (CORBA::Double)strtod(splitValues[36].c_str(),NULL); //L_ELBOW_P = 28
	    angleValues[29] = (CORBA::Double)strtod(splitValues[37].c_str(),NULL); //L_WRIST_Y = 29
	    angleValues[30] = (CORBA::Double)strtod(splitValues[38].c_str(),NULL); //L_WRIST_P = 30
	    angleValues[31] = (CORBA::Double)strtod(splitValues[39].c_str(),NULL); //L_WRIST_R = 31
	    angleValues[32] = (CORBA::Double)strtod(splitValues[40].c_str(),NULL); //L_HAND_J0 = 32
	    angleValues[33] = (CORBA::Double)strtod(splitValues[41].c_str(),NULL); //L_HAND_J1 = 33	  
	    //Right arm
	    angleValues[16] = (CORBA::Double)strtod(splitValues[16].c_str(),NULL); //R_SHOULDER_P = 16
	    angleValues[17] = (CORBA::Double)strtod(splitValues[17].c_str(),NULL); //R_SHOULDER_R = 17
	    angleValues[18] = (CORBA::Double)strtod(splitValues[18].c_str(),NULL); //R_SHOULDER_Y = 18
	    angleValues[19] = (CORBA::Double)strtod(splitValues[19].c_str(),NULL); //R_ELBOW_P = 19
	    angleValues[20] = (CORBA::Double)strtod(splitValues[20].c_str(),NULL); //R_WRIST_Y = 20
	    angleValues[21] = (CORBA::Double)strtod(splitValues[21].c_str(),NULL); //R_WRIST_P = 21
	    angleValues[22] = (CORBA::Double)strtod(splitValues[22].c_str(),NULL); //R_WRIST_R = 22
	    angleValues[23] = (CORBA::Double)strtod(splitValues[23].c_str(),NULL); //R_HAND_J0 = 23
	    angleValues[24] = (CORBA::Double)strtod(splitValues[24].c_str(),NULL); //R_HAND_J1 = 24
	    
	    parent->m_service3->stabilizerOff();
	    Sleep(1000); //Pauses the robot motion
	    
	    //parent->m_service1->setJointAngles(angleValues,1.0); //fast for debugging
	    parent->m_service1->setJointAngles(angleValues,3.0); //normal for real robot
	    parent->m_service1->waitInterpolation();	  
	  }
	}
	else if(splitValues[0].compare("P") == 0)
	{ 	  
	  double timeToSleep = strtod(splitValues[1].c_str(),NULL);
	  Sleep(timeToSleep*1000.0); //Pauses the robot motion
	}    
    }
    myFile.close();
  }  
  ///////////////////////////////////
  return 0;
}



// End of example implementational code



