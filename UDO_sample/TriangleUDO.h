#pragma once
#include <uf.h>
#include <uf_ui.h>
#include <uf_exit.h> 
#include <uf_disp.h>  
#include <vector>
#include <iostream>
#include <sstream>

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


class TriangleUDO {
public:
	TriangleUDO();

	static NXOpen::Session* theSession ;
	static NXOpen::UI* theUI;
	static NXOpen::UserDefinedObjects::UserDefinedClass* myUDOclass;
private:
	int iniUDO();

};

NXOpen::Session* (TriangleUDO::theSession) = NULL;
NXOpen::UI* (TriangleUDO::theUI) = NULL;
NXOpen::UserDefinedObjects::UserDefinedClass* (TriangleUDO::myUDOclass) = NULL;


