#pragma once
#include <NXOpen/Session.hxx>  
#include <NXOpen/Part.hxx> 
#include <NXOpen/PartCollection.hxx>  
#include <NXOpen/Callback.hxx>
#include <NXOpen/NXException.hxx> 
#include <NXOpen/UI.hxx> 
#include <NXOpen/Selection.hxx>
#include <NXOpen/LogFile.hxx>
#include <NXOpen/NXObjectManager.hxx>
#include <NXOpen/ListingWindow.hxx>
#include <NXOpen/View.hxx>

#include <NXOpen/UserDefinedObjects_UserDefinedClass.hxx>
#include <NXOpen/UserDefinedObjects_UserDefinedClassManager.hxx>
#include <NXOpen/UserDefinedObjects_UserDefinedObject.hxx>
#include <NXOpen/UserDefinedObjects_UserDefinedObjectManager.hxx>
#include <NXOpen/UserDefinedObjects_UserDefinedEvent.hxx>
#include <NXOpen/UserDefinedObjects_UserDefinedDisplayEvent.hxx>
#include <NXOpen/UserDefinedObjects_UserDefinedLinkEvent.hxx>
#include <NXOpen/Features_UserDefinedObjectFeatureBuilder.hxx> 
#include <NXOpen/Features_UserDefinedObjectFeature.hxx> 
#include <NXOpen/Features_FeatureCollection.hxx> 
#include <NXOpen/Features_Feature.hxx> 

#include <stdarg.h>
#include <iostream>
#include <strstream>
#include <sstream>
#include <vector>
using std::ostrstream;
using std::stringstream;
using std::vector;
using std::endl;
using std::ends;
using std::cerr;
#include <uf.h>
#include <uf_ui.h>
#include <uf_ui_types.h>
#include <uf_exit.h>

using namespace NXOpen;
using namespace NXOpen::UserDefinedObjects;
using namespace NXOpen::Features;

#define DLLImport __declspec(dllimport)
#define DllExport __declspec(dllexport)

extern "C" class DllExport TriangleUDO {
public:
	static UserDefinedClass* GetClassUDO();
private:
	TriangleUDO();
	static Session* theSession;
	static UI* theUI;
	static UserDefinedClass* triUdo_class;
	
	static int myDisplayCB(UserDefinedDisplayEvent*  displayEvent);
	static int myEditCB(UserDefinedEvent* editEvent);
	static int myInfoCB(UserDefinedEvent* infoEvent);
};


