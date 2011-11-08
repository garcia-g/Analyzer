// -*-C++-*-
/*!
 * @file  AnalyzerServiceSVC_impl.h
 * @brief Service implementation header of AnalyzerService.idl
 *
 */

#include "AnalyzerServiceSkel.h"

#ifndef ANALYZERSERVICESVC_IMPL_H
#define ANALYZERSERVICESVC_IMPL_H

// my adds
class Analyzer;
///////////////////////////

/*!
 * @class AnalyzerServiceSVC_impl
 * Example class implementing IDL interface OpenHRP::AnalyzerService
 */
class AnalyzerServiceSVC_impl
 : public virtual POA_OpenHRP::AnalyzerService,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~AnalyzerServiceSVC_impl();

   //my adds
   Analyzer *parent;
   bool allFlag;
   bool manipFlag;
   bool walkFlag;   
   ////////////
   
 public:
  /*!
   * @brief standard constructor
   */
   AnalyzerServiceSVC_impl();
   
   //my adds
   AnalyzerServiceSVC_impl(Analyzer *p);
   /////////////////////
   
  /*!
   * @brief destructor
   */
   virtual ~AnalyzerServiceSVC_impl();

   // attributes and operations
   CORBA::Short analyze(const char* fileName, const char* runMode);

};



#endif // ANALYZERSERVICESVC_IMPL_H


