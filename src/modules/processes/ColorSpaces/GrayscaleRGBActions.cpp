//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 02.01.03.0819
// ----------------------------------------------------------------------------
// Standard ColorSpaces Process Module Version 01.01.00.0307
// ----------------------------------------------------------------------------
// GrayscaleRGBActions.cpp - Released 2017-04-14T23:07:12Z
// ----------------------------------------------------------------------------
// This file is part of the standard ColorSpaces PixInsight module.
//
// Copyright (c) 2003-2017 Pleiades Astrophoto S.L. All Rights Reserved.
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
// ----------------------------------------------------------------------------

#include "GrayscaleRGBActions.h"
#include "GrayscaleRGBProcesses.h"
#include "GrayscaleRGBInstances.h"

#include <pcl/KeyCodes.h>
#include <pcl/ButtonCodes.h>

namespace pcl
{

// ----------------------------------------------------------------------------

#include "ConvertToGrayscaleActionIcon.xpm"

// ----------------------------------------------------------------------------

ConvertToGrayscaleAction::ConvertToGrayscaleAction() :
Action( "Image > Color Spaces > Convert to Grayscale", Bitmap( ConvertToGrayscaleActionIcon_XPM ), "Color Spaces" )
{
   SetToolTip( "Convert to Grayscale" );
}

// ----------------------------------------------------------------------------

void ConvertToGrayscaleAction::Execute()
{
   ConvertToGrayscaleInstance( TheConvertToGrayscaleProcess ).LaunchOnCurrentView();
}

// ----------------------------------------------------------------------------

bool ConvertToGrayscaleAction::IsEnabled( ActionInfo info ) const
{
   return info.isImage && info.isColor; // only RGB color view images can be converted to grayscale
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#include "ConvertToRGBColorActionIcon.xpm"

// ----------------------------------------------------------------------------

ConvertToRGBColorAction::ConvertToRGBColorAction() :
Action( "Image > Color Spaces > Convert to RGB Color", Bitmap( ConvertToRGBColorActionIcon_XPM ), "Color Spaces" )
{
   SetToolTip( "Convert to RGB Color" );
}

// ----------------------------------------------------------------------------

void ConvertToRGBColorAction::Execute()
{
   ConvertToRGBColorInstance( TheConvertToRGBColorProcess ).LaunchOnCurrentView();
}

// ----------------------------------------------------------------------------

bool ConvertToRGBColorAction::IsEnabled( ActionInfo info ) const
{
   return info.isImage && !info.isColor; // only grayscale view images can be converted to RGB color
}

// ----------------------------------------------------------------------------

} // pcl

// ----------------------------------------------------------------------------
// EOF GrayscaleRGBActions.cpp - Released 2017-04-14T23:07:12Z
