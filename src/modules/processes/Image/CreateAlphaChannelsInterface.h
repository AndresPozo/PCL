//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 02.01.03.0819
// ----------------------------------------------------------------------------
// Standard Image Process Module Version 01.02.09.0361
// ----------------------------------------------------------------------------
// CreateAlphaChannelsInterface.h - Released 2017-04-14T23:07:12Z
// ----------------------------------------------------------------------------
// This file is part of the standard Image PixInsight module.
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

#ifndef __CreateAlphaChannelsInterface_h
#define __CreateAlphaChannelsInterface_h

#include <pcl/CheckBox.h>
#include <pcl/Edit.h>
#include <pcl/GroupBox.h>
#include <pcl/NumericControl.h>
#include <pcl/ProcessInterface.h>
#include <pcl/Sizer.h>
#include <pcl/ToolButton.h>

#include "CreateAlphaChannelsInstance.h"

namespace pcl
{

// ----------------------------------------------------------------------------

class CreateAlphaChannelsInterface : public ProcessInterface
{
public:

   CreateAlphaChannelsInterface();
   virtual ~CreateAlphaChannelsInterface();

   virtual IsoString Id() const;
   virtual MetaProcess* Process() const;
   virtual const char** IconImageXPM() const;

   virtual void ApplyInstance() const;
   virtual void ResetInstance();

   virtual bool Launch( const MetaProcess&, const ProcessImplementation*, bool& dynamic, unsigned& /*flags*/ );

   virtual ProcessImplementation* NewProcess() const;

   virtual bool ValidateProcess( const ProcessImplementation&, pcl::String& whyNot ) const;
   virtual bool RequiresInstanceValidation() const;
   virtual bool ImportProcess( const ProcessImplementation& );

private:

   CreateAlphaChannelsInstance instance;

   struct GUIData
   {
      GUIData( CreateAlphaChannelsInterface& );

      VerticalSizer      Global_Sizer;
         GroupBox          FromImage_GroupBox;
         VerticalSizer     FromImage_Sizer;
            HorizontalSizer   ImageId_Sizer;
               Edit              ImageId_Edit;
               ToolButton        SelectSource_ToolButton;
            CheckBox          InvertSource_CheckBox;
            CheckBox          CloseSource_CheckBox;
         GroupBox          FromTransparency_GroupBox;
         HorizontalSizer   FromTransparency_Sizer;
            NumericControl    Transparency_NumericControl;
            Control           ColorSample_Control;
         CheckBox          Replace_CheckBox;
   };

   GUIData* GUI = nullptr;

   void UpdateControls();

   void __SourceMode_Check( GroupBox& sender, bool checked );
   void __ImageId_GetFocus( Control& sender );
   void __ImageId_EditCompleted( Edit& sender );
   void __SelectSource_Click( Button& sender, bool checked );
   void __SourceOption_Click( Button& sender, bool checked );
   void __Transparency_ValueUpdated( NumericEdit& sender, double value );
   void __ColorSample_Paint( Control& sender, const Rect& updateRect );
   void __Replace_Click( Button& sender, bool checked );
   void __ViewDrag( Control& sender, const Point& pos, const View& view, unsigned modifiers, bool& wantsView );
   void __ViewDrop( Control& sender, const Point& pos, const View& view, unsigned modifiers );

   friend struct GUIData;
};

// ----------------------------------------------------------------------------

PCL_BEGIN_LOCAL
extern CreateAlphaChannelsInterface* TheCreateAlphaChannelsInterface;
PCL_END_LOCAL

// ----------------------------------------------------------------------------

} // pcl

#endif   // __CreateAlphaChannelsInterface_h

// ----------------------------------------------------------------------------
// EOF CreateAlphaChannelsInterface.h - Released 2017-04-14T23:07:12Z
