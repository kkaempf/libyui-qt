
/* ****************************************************************************
  |
  | Copyright (c) 2000 - 2010 Novell, Inc.
  | All Rights Reserved.
  |
  | This program is free software; you can redistribute it and/or
  | modify it under the terms of version 2 of the GNU General Public License as
  | published by the Free Software Foundation.
  |
  | This program is distributed in the hope that it will be useful,
  | but WITHOUT ANY WARRANTY; without even the implied warranty of
  | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
  | GNU General Public License for more details.
  |
  | You should have received a copy of the GNU General Public License
  | along with this program; if not, contact Novell, Inc.
  |
  | To contact Novell about this file by physical or electronic mail,
  | you may find current contact information at www.novell.com
  |
  |*************************************************************************** */

/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:	      YQWizardButton.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#include <qpushbutton.h>
#include <qsize.h>
#define YUILogComponent "qt-ui"
#include "YUILog.h"

#include "utf8.h"
#include "YQUI.h"
#include "YQWizardButton.h"
#include "YQWizard.h"


YQWizardButton::YQWizardButton( YQWizard *	wizard,
				QWidget *	buttonParent,
				const std::string &	label )
    : YQGenericButton( wizard, label )
    , _wizard( wizard )
{
    QPushButton * button = new QPushButton( fromUTF8( label ), buttonParent );
    Q_CHECK_PTR( button );

    setQPushButton( button );
    setWidgetRep( button );

    connect( button, SIGNAL( clicked() ),
	     this,   SIGNAL( clicked() ) );


    // This widget itself will never be visible, only its button - which is not
    // a child of this widget.
    QWidget::hide();
}


YQWizardButton::~YQWizardButton()
{
    // Don't delete qPushButton() here - its parent (buttonParent) will take
    // care of that!
}


void YQWizardButton::hide()
{
    if ( qPushButton() )
	qPushButton()->hide();
}


void YQWizardButton::show()
{
    if ( qPushButton() )
	qPushButton()->show();
}


bool YQWizardButton::isShown() const
{
    if ( qPushButton() )
	return !qPushButton()->isHidden();
    else
	return false;
}


bool YQWizardButton::isHidden() const
{
    return ! isShown();
}


int YQWizardButton::preferredWidth()
{
    // This widget doesn't have a YWidget-based visual representation, it's
    // only a YWidget for shortcut checking etc.

    return 0;
}


int YQWizardButton::preferredHeight()
{
    // This widget doesn't have a YWidget-based visual representation, it's
    // only a YWidget for shortcut checking etc.

    return 0;
}


void YQWizardButton::setSize( int newWidth, int newHeight )
{
    // NOP
}



#include "YQWizardButton.moc"
