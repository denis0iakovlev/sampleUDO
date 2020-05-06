/*****************************************************************************
**
** registrat_TriangleUdo.cpp
**
** Description:
**     Contains Unigraphics entry points for the application.
**
*****************************************************************************/

/* Include files */
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
#include <strstream>
#include <iostream>
#include <vector>
#include "triangleUDO.h"
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

static void ECHO(char *format, ...)
{
	char msg[UF_UI_MAX_STRING_NCHARS + 1];
	va_list args;
	va_start(args, format);
	vsnprintf_s(msg, sizeof(msg), UF_UI_MAX_STRING_NCHARS, format, args);
	va_end(args);
	UF_UI_open_listing_window();
	UF_UI_write_listing_window(msg);
	UF_print_syslog(msg, FALSE);
}

#define UF_CALL(X) (report_error( __FILE__, __LINE__, #X, (X)))

static int report_error(char *file, int line, char *call, int irc)
{
	if (irc)
	{
		char err[133];

		UF_get_fail_message(irc, err);
		ECHO("*** ERROR code %d at line %d in %s:\n",
			irc, line, file);
		ECHO("+++ %s\n", err);
		ECHO("%s;\n", call);
	}

	return(irc);
}


/*****************************************************************************
**  Activation Methods
*****************************************************************************/
/*  Unigraphics Startup
**      This entry point activates the application at Unigraphics startup */
extern DllExport void ufsta(char *param, int *returnCode, int rlen)
{
	/* Initialize the API environment */
	if (UF_CALL(UF_initialize()))
	{
	}

	/* TODO: Add your application code here */
	UserDefinedClass* userClass = TriangleUDO::GetClassUDO();

	/* Terminate the API environment */
	UF_CALL(UF_terminate());
	return;
}

/*****************************************************************************
**  Utilities
*****************************************************************************/

/* Unload Handler
**     This function specifies when to unload your application from Unigraphics.
**     If your application registers a callback (from a MenuScript item or a
**     User Defined Object for example), this function MUST return
**     "UF_UNLOAD_UG_TERMINATE". */
extern int ufusr_ask_unload(void)
{
	return(UF_UNLOAD_UG_TERMINATE);
}

