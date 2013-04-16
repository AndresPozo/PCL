// ****************************************************************************
// PixInsight Class Library - PCL 02.00.02.0584
// Standard PixInsightINDI Process Module Version 01.00.02.0092
// ****************************************************************************
// PixInsightINDIProcess.cpp - Released 2013/03/24 18:42:27 UTC
// ****************************************************************************
// This file is part of the standard PixInsightINDI PixInsight module.
//
// Copyright (c) 2003-2013, Pleiades Astrophoto S.L. All Rights Reserved.
//
// Redistribution and use in both source and binary forms, with or without
// modification, is permitted provided that the following conditions are met:
//
// 1. All redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. All redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. Neither the names "PixInsight" and "Pleiades Astrophoto", nor the names
//    of their contributors, may be used to endorse or promote products derived
//    from this software without specific prior written permission. For written
//    permission, please contact info@pixinsight.com.
//
// 4. All products derived from this software, in any form whatsoever, must
//    reproduce the following acknowledgment in the end-user documentation
//    and/or other materials provided with the product:
//
//    "This product is based on software from the PixInsight project, developed
//    by Pleiades Astrophoto and its contributors (http://pixinsight.com/)."
//
//    Alternatively, if that is where third-party acknowledgments normally
//    appear, this acknowledgment must be reproduced in the product itself.
//
// THIS SOFTWARE IS PROVIDED BY PLEIADES ASTROPHOTO AND ITS CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PLEIADES ASTROPHOTO OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, BUSINESS
// INTERRUPTION; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; AND LOSS OF USE,
// DATA OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// ****************************************************************************

#include "PixInsightINDIInstance.h"
#include "PixInsightINDIInterface.h"
#include "PixInsightINDIParameters.h"
#include "PixInsightINDIProcess.h"

#include <pcl/Arguments.h>
#include <pcl/Console.h>
#include <pcl/Exception.h>
#include <pcl/View.h>

namespace pcl
{

// ----------------------------------------------------------------------------

//#include "PixInsightINDIIcon.xpm"

// ----------------------------------------------------------------------------

PixInsightINDIProcess* ThePixInsightINDIProcess = 0;

// ----------------------------------------------------------------------------

PixInsightINDIProcess::PixInsightINDIProcess() : MetaProcess()
{
   ThePixInsightINDIProcess = this;

   // Instantiate process parameters
   new INDIServerHostname(this);
   new INDIServerPort(this);


}

// ----------------------------------------------------------------------------

IsoString PixInsightINDIProcess::Id() const
{
   return "INDIClient";
}

// ----------------------------------------------------------------------------

IsoString PixInsightINDIProcess::Category() const
{
   return IsoString(); // No category
}

// ----------------------------------------------------------------------------

uint32 PixInsightINDIProcess::Version() const
{
   return 0x100; // required
}

// ----------------------------------------------------------------------------

String PixInsightINDIProcess::Description() const
{
   return
   "<html>"
   "<p>INDIclient is an INDI client for use in PixInsight.</p>"
   "</html>";
}

// ----------------------------------------------------------------------------

const char** PixInsightINDIProcess::IconImageXPM() const
{
   return 0; // PixInsightINDIIcon_XPM; ---> put a nice icon here
}
// ----------------------------------------------------------------------------

ProcessInterface* PixInsightINDIProcess::DefaultInterface() const
{
   return ThePixInsightINDIInterface;
}
// ----------------------------------------------------------------------------

ProcessImplementation* PixInsightINDIProcess::Create() const
{
   return new PixInsightINDIInstance( this );
}

// ----------------------------------------------------------------------------

ProcessImplementation* PixInsightINDIProcess::Clone( const ProcessImplementation& p ) const
{
   const PixInsightINDIInstance* instPtr = dynamic_cast<const PixInsightINDIInstance*>( &p );
   return (instPtr != 0) ? new PixInsightINDIInstance( *instPtr ) : 0;
}

// ----------------------------------------------------------------------------

bool PixInsightINDIProcess::CanProcessCommandLines() const
{
   return true;
}

// ----------------------------------------------------------------------------

static void ShowHelp()
{
   Console().Write(
"<raw>"
"Usage: INDIclient [<arg_list>] [<view_list>]"
"\n"
"\n -host=<name>       hostname of the INDI server"
"\n"
"\n -port=<port>       port of the INDI server"
"\n"
"\n--interface"
"\n"
"\n      Launches the interface of this process."
"\n"
"\n--help"
"\n"
"\n      Displays this help and exits."
"</raw>" );
}

int PixInsightINDIProcess::ProcessCommandLine( const StringList& argv ) const
{
   ArgumentList arguments =
      ExtractArguments( argv, ArgumentItemMode::AsViews, ArgumentOption::AllowWildcards );

   PixInsightINDIInstance instance( this );

   bool launchInterface = false;
   int count = 0;

   for ( ArgumentList::const_iterator i = arguments.Begin(); i != arguments.End(); ++i )
   {
      const Argument& arg = *i;

      if ( arg.IsNumeric() )
      {
		  if (arg.Id() == "port")
			  instance.p_port = arg.NumericValue();
	  }
      else if ( arg.IsString() )
      {
		  if (arg.Id() == "host")
			  instance.p_host = arg.StringValue();	
      }
      else if ( arg.IsSwitch() )
      {
         throw Error( "Unknown switch argument: " + arg.Token() );
      }
      else if ( arg.IsLiteral() )
      {
         // These are standard parameters that all processes should provide.
         if ( arg.Id() == "-interface" )
            launchInterface = true;
         else if ( arg.Id() == "-help" )
         {
            ShowHelp();
            return 0;
         }
         else
            throw Error( "Unknown argument: " + arg.Token() );
      }
      else if ( arg.IsItemList() )
      {
         ++count;

         if ( arg.Items().IsEmpty() )
            throw Error( "No view(s) found: " + arg.Token() );

         for ( StringList::const_iterator j = arg.Items().Begin(); j != arg.Items().End(); ++j )
         {
            View v = View::ViewById( *j );
            if ( v.IsNull() )
               throw Error( "No such view: " + *j );
            instance.LaunchOn( v );
         }
      }
   }

   if ( launchInterface )
      instance.LaunchInterface();
   else if ( count == 0 )
   {
	   instance.LaunchGlobal();
   }

   return 0;
}

// ----------------------------------------------------------------------------

} // pcl

// ****************************************************************************
// EOF PixInsightINDIProcess.cpp - Released 2013/03/24 18:42:27 UTC
