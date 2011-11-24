// -*- C++ -*-
/*!
 * @file  Analyzer.cpp
 * @brief Retrieves and processes a motion script
 * @date Nov 8, 2011
 *
 * Written by Gustavo Garcia
 * Robotics Lab @ NAIST 
 * 
 */

#include "Analyzer.h"

//my adds
#include <iostream>
using namespace std;
/////////////

// Module specification
// <rtc-template block="module_spec">
static const char* analyzer_spec[] =
  {
    "implementation_id", "Analyzer",
    "type_name",         "Analyzer",
    "description",       "Retrieves and processes a motion script",
    "version",           "0.1.0",
    "vendor",            "RoboticsLab@NAIST",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Manager Object
 */
Analyzer::Analyzer(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_WalkGeneratorServicePort("WalkGeneratorService"),
    m_SequencePlayerServicePort("SequencePlayerService"),
    m_AnalyzerServicePort("AnalyzerService"),
    m_stInhibitServicePort("stInhibitService"),
    m_service2(this)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Analyzer::~Analyzer()
{
}



RTC::ReturnCode_t Analyzer::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_AnalyzerServicePort.registerProvider("service2", "OpenHRP::AnalyzerService", m_service2);
  
  // Set service consumers to Ports
  m_WalkGeneratorServicePort.registerConsumer("service0", "WalkGeneratorService", m_service0);
  m_SequencePlayerServicePort.registerConsumer("service0", "SequencePlayerService", m_service1);
  m_stInhibitServicePort.registerConsumer("service0", "OpenHRP::stInhibitService", m_service3);
  
  // Set CORBA Service Ports
  addPort(m_WalkGeneratorServicePort);
  addPort(m_SequencePlayerServicePort);
  addPort(m_AnalyzerServicePort);
  addPort(m_stInhibitServicePort);
  
  // </rtc-template>

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Analyzer::onFinalize()
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Analyzer::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Analyzer::onActivated(RTC::UniqueId ec_id)
{
  cout << "Activated" << endl;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Analyzer::onDeactivated(RTC::UniqueId ec_id)
{
  cout << "Deactivated" << endl;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Analyzer::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Analyzer::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Analyzer::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Analyzer::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void AnalyzerInit(RTC::Manager* manager)
  {
    coil::Properties profile(analyzer_spec);
    manager->registerFactory(profile,
                             RTC::Create<Analyzer>,
                             RTC::Delete<Analyzer>);
  }
  
};


