//=============================================================================
//
//                   Copyright (c) 2012 Siemens PLM Solutions
//                    Unpublished - All rights reserved
//===============================================================================
// This program creates a very simple UDO example. 
// 
// It demonstrates each of the following callbacks: 
// * Display 
// * Selection 
// * Attention Point 
// * Fit 
// * Edit 
// * Information 
// 
// In NX execute this program via: File -> Execute -> NX Open... 
// This program begins by opening a new part (if there were no open parts). 
// Next it will prompt you to select a position on the screen. 
// The screen position will be used as a reference point for the UDO. 
// The UDO will display as a triangle on that point with a name 
// "C++ UDO" next to the triangle. 
// 
// This UDO is selectable. If you go to Information->Object and select
// the UDO you will see custom information output to the listing window from 
// the function myInfoCB defined in this program. 
// 
// You can also edit the location of the UDO. Start by right-clicking 
// on the UDO and selecting "Edit User Defined Object" from the MB3 popup menu. 
// Editing the UDO will invoke the myEditCB function defined in this program. 
// You will be prompted to select a new screen position, and after you make 
// the selection the UDO will move to the new location. 
//=============================================================================
//
//=============================================================================
/* Include files */ 
#define FOLD_APP
//#define FOLD_UDO

#include <sstream>
#include <iostream>

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
#include "triangleUDO.h"

using namespace std;
using namespace NXOpen; 
using namespace NXOpen::UserDefinedObjects;
using namespace NXOpen::Features;
//static variables 
static NXOpen::Session* theSession = NULL; 
static UI* theUI = NULL; 
static UserDefinedClass* myUDO = NULL;


//------------------------------------------------------------------------------ 
// ufusr (Explicit Activation) 
// This entry point is used to activate the application explicitly, as in 
// "File->Execute UG/Open->NX Open..." 
//------------------------------------------------------------------------------ 
#ifdef FOLD_APP
extern void ufusr( char *parm, int *returnCode, int rlen ) 
{ 

    try 
    { 
        // required for calls to legacy UF routines 
        // such as UF_DISP_add_item_to_display 
        UF_initialize(); 
		theSession = Session::GetSession();
		theUI = UI::GetUI();

		myUDO = TriangleUDO::GetClassUDO();
		ListingWindow* lw = theSession->ListingWindow();
		
        // if we don't have any parts open create one 
        BasePart* myBasePart = theSession->Parts()->BaseDisplay(); 
        if( myBasePart == NULL) 
        { 
            myBasePart = theSession->Parts()->NewBaseDisplay("test_cpp_udo1.prt", BasePart::UnitsMillimeters); 
        } 
		Part* workPart = dynamic_cast<Part*>(myBasePart);
        
        View* myView = NULL; 
        Point3d myCursor(0,0,0); 
        
        // ask the user to select an origin for this UDO 
        Selection::DialogResponse myResponse = theUI->SelectionManager()->SelectScreenPosition("Select Origin of C++ UDO", &myView, &myCursor); 
        if( myResponse == Selection::DialogResponsePick ) 
        { 
			
			ListingWindow*
				theLW = theSession->ListingWindow();
			theLW->Open();
			theLW->WriteLine("Выполняется тело из ufusr");

            // The user selected a point - go ahead and create the udo 
            UserDefinedObjectManager* myUDOmanager = myBasePart->UserDefinedObjectManager(); 
            UserDefinedObject* firstUDO = myUDOmanager->CreateUserDefinedObject(myUDO);
            // set the color property of the udo - just for fun :) 

            firstUDO->SetColor(36); 
            // store the origin selected by the user with the udo 
            std::vector<double> myUDOdoubles(3); 
            myUDOdoubles[0] = myCursor.X; 
            myUDOdoubles[1] = myCursor.Y; 
            myUDOdoubles[2] = myCursor.Z; 
            firstUDO->SetDoubles(myUDOdoubles); 

            // add the udo to the display list manually 
            // this will force the udo to display immediately 
			Feature* udoFeature(NULL);
			UserDefinedObjectFeatureBuilder* userDefineFeauture = workPart->Features()->CreateUserDefinedObjectFeatureBuilder(udoFeature);
			userDefineFeauture->SetUserDefinedClass(myUDO);
			userDefineFeauture->SetUserDefinedObject(firstUDO);
			bool isVali;
			isVali = userDefineFeauture->Validate();
			if (isVali) {
				UserDefinedObjectFeature* objFeature = NULL;
				objFeature = dynamic_cast<decltype(objFeature)>(userDefineFeauture->Commit());
			}
            UF_DISP_add_item_to_display(firstUDO->Tag()); 
			stringstream str;
			auto allUdoObj = myUDOmanager->GetUdosOfClass(myUDO);
			str << "Всего UDO обьектов в детали  : " << allUdoObj.size() << endl;
			theLW->WriteLine(str.str().c_str());
        } 

        UF_terminate(); 
    } 
    catch (const NXOpen::NXException& ex) 
    { 
		ListingWindow*
			theLW = theSession->ListingWindow();
		theLW->Open();
		theLW->WriteLine(ex.Message());
    } 
} 
#endif
//------------------------------------------------------------------------------ 
// ufsta 
// Entrypoint used when program is loaded automatically 
// as NX starts up. Note this application must be placed in a 
// special folder for NX to find and load it during startup. 
// Refer to the NX Open documentation for more details on how 
// NX finds and loads applications during startup. 
//------------------------------------------------------------------------------ 
#ifdef FOLD_UDO
extern void ufsta( char *param, int *returnCode, int rlen ) 
{ 
    try 
    { 
        initUDO(false); 

    } 
    catch (const NXOpen::NXException& ex) 
    { 
        cerr << "Caught exception: " << ex.Message() << endl; 
    } 
}
#endif
//------------------------------------------------------------------------------ 
// ufusr_ask_unload 
// Make sure you specify AtTermination for the unload option. 
// If you unload the library before the NX Session Terminates 
// bad things could happen when we try to execute a udo 
// callback that no longer exists in the session. 
//------------------------------------------------------------------------------ 
extern int ufusr_ask_unload( void ) 
{ 
    //return (int)Session::LibraryUnloadOptionExplicitly; 
     return (int)Session::LibraryUnloadOptionImmediately; 
   // return (int)Session::LibraryUnloadOptionAtTermination; 
}
