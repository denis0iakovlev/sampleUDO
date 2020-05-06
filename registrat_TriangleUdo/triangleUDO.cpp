#include "triangleUDO.h"

Session *(TriangleUDO::theSession) = NULL;
UI* (TriangleUDO::theUI) = NULL;
UserDefinedClass* (TriangleUDO::staticClass) = NULL;

UserDefinedClass* TriangleUDO::GetClassUDO()
{

	if (staticClass == NULL)
	{
		TriangleUDO();
	}
	return staticClass;
}

TriangleUDO::TriangleUDO()
{
	theSession = Session::GetSession();
	theUI = UI::GetUI();
	inizialize();
}

int TriangleUDO::myDisplayCB(UserDefinedDisplayEvent * displayEvent)
{
	try
	{
		// Get the doubles used to define the selected screen position for this UDO. 
		std::vector<double> myUDOdoubles = displayEvent->UserDefinedObject()->GetDoubles();

		// Use the doubles to define points of a triangle 
		std::vector<Point3d> myPoints(4);

		myPoints[0].X = myUDOdoubles[0] + 0;
		myPoints[0].Y = myUDOdoubles[1] + 0;
		myPoints[0].Z = myUDOdoubles[2] + 0;

		myPoints[1].X = myUDOdoubles[0] + 100;
		myPoints[1].Y = myUDOdoubles[1] + 0;
		myPoints[1].Z = myUDOdoubles[2] + 0;

		myPoints[2].X = myUDOdoubles[0] + 0;
		myPoints[2].Y = myUDOdoubles[1] + 100;
		myPoints[2].Z = myUDOdoubles[2] + 0;

		myPoints[3].X = myUDOdoubles[0] + 0;
		myPoints[3].Y = myUDOdoubles[1] + 0;
		myPoints[3].Z = myUDOdoubles[2] + 0;

		// Display the triangle 
		displayEvent->DisplayContext()->DisplayPolyline(myPoints);

		// Display the text next to the triangle 
		Point3d myPt = Point3d(myUDOdoubles[0] + 100, myUDOdoubles[1], myUDOdoubles[2]);
		displayEvent->DisplayContext()->DisplayText("C++ UDO", myPt, UserDefinedObjectDisplayContext::TextRefBottomLeft);
	}
	catch (NXException ex)
	{
		// ---- Enter your exception handling code here ----- 
		cerr << "Caught exception: " << ex.Message() << endl;
	}
	return 0;
}

int TriangleUDO::myEditCB(UserDefinedEvent * editEvent)
{
	try
	{
		// required for calls to legacy UF routines 
		// such as UF_DISP_add_item_to_display 
		UF_initialize();

		View* myView = NULL;
		Point3d myCursor(0, 0, 0);

		// highlight the current udo we are about to edit 
		// this is helpful if multiple udo's were on the selection 
		// list when the user decided to edit them 
		editEvent->UserDefinedObject()->Highlight();

		// ask the user to select a new origin for this UDO 
		Selection::DialogResponse myResponse = theUI->SelectionManager()->SelectScreenPosition("Select New Origin for C++ UDO", &myView, &myCursor);
		// we are done asking the user for input... unhighlight the udo 
		editEvent->UserDefinedObject()->Unhighlight();

		// use the new screen position (if the user picked one)

		if (myResponse == Selection::DialogResponsePick)
		{
			std::vector<double> myUDOdoubles(3);
			myUDOdoubles[0] = myCursor.X;
			myUDOdoubles[1] = myCursor.Y;
			myUDOdoubles[2] = myCursor.Z;
			// store the newly selected origin with the udo 
			editEvent->UserDefinedObject()->SetDoubles(myUDOdoubles);
			// add the udo to the display list manually 
			// this will force the udo display to regenerate 
			// immediately and show the changes we just made 
			UF_DISP_add_item_to_display(editEvent->UserDefinedObject()->Tag());
		}
		UF_terminate();
	}
	catch (NXException ex)
	{
		// ---- Enter your exception handling code here ----- 
		cerr << "Caught exception: " << ex.Message() << endl;
	} return 0;
}

int TriangleUDO::myInfoCB(UserDefinedEvent * infoEvent)
{
	try
	{
		ListingWindow* theLW = theSession->ListingWindow();
		char msg[256];
		theLW->Open();
		theLW->WriteLine(" ");
		theLW->WriteLine("------------------------------------------------------------");
		theLW->WriteLine("Begin Custom Information");
		theLW->WriteLine(" ");
		NXOpen::NXString formattedMessage;
		formattedMessage = "UDO Class Name: " + (infoEvent->UserDefinedObject()->UserDefinedClass()->ClassName());
		theLW->WriteLine(formattedMessage);
		formattedMessage = "UDO Friendly Name: " + infoEvent->UserDefinedObject()->UserDefinedClass()->FriendlyName();
		theLW->WriteLine(formattedMessage);
		std::vector<double> myUDOdoubles = infoEvent->UserDefinedObject()->GetDoubles();
		std::ostringstream DoubleBuffer;
		DoubleBuffer << myUDOdoubles[0];
		formattedMessage = DoubleBuffer.str();
		theLW->WriteLine(formattedMessage);
		DoubleBuffer.str("");
		DoubleBuffer.clear();
		DoubleBuffer << myUDOdoubles[1];
		formattedMessage = DoubleBuffer.str();
		theLW->WriteLine(formattedMessage);
		DoubleBuffer.str("");
		DoubleBuffer.clear();
		DoubleBuffer << myUDOdoubles[2];
		formattedMessage = DoubleBuffer.str();
		theLW->WriteLine(formattedMessage);
		theLW->WriteLine(" ");
		theLW->WriteLine("End Custom Information");
	}
	catch (NXException ex)
	{
		// ---- Enter your exception handling code here ----- 
		cerr << "Caught exception: " << ex.Message() << endl;
	}
	return 0;
}

int TriangleUDO::inizialize()
{
	if (staticClass == NULL)
	{
		// Define your custom UDO class 
		staticClass = theSession->UserDefinedClassManager()->CreateUserDefinedObjectClass("trinagleUDO", "Sample C++ UDO");
		// Setup properties on the custom UDO class 
		staticClass->SetAllowQueryClassFromName(UserDefinedClass::AllowQueryClass::AllowQueryClassOn);
		// Register callbacks for the UDO class 
		staticClass->AddDisplayHandler(make_callback(&myDisplayCB));
		staticClass->AddAttentionPointHandler(make_callback(&myDisplayCB));
		staticClass->AddFitHandler(make_callback(&myDisplayCB));
		staticClass->AddSelectionHandler(make_callback(&myDisplayCB));

		staticClass->AddEditHandler(make_callback(&myEditCB));
		staticClass->AddInformationHandler(make_callback(&myInfoCB));
		// Add this class to the list of object types available for selection in NX. 
		// If you skip this step you won't be able to select UDO's of this class, 
		// even though you registered a selection callback. 
		theUI->SelectionManager()->SetSelectionStatusOfUserDefinedClass(staticClass, true);
	}
	return 0;
}


