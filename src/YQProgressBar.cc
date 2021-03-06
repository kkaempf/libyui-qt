
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

  File:	      YQProgressBar.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#include <qprogressbar.h>
#include <QVBoxLayout>

#include <qlabel.h>
#define YUILogComponent "qt-ui"
#include "YUILog.h"

using std::max;

#include "utf8.h"
#include "YQUI.h"
#include "YQProgressBar.h"
#include "YQWidgetCaption.h"


YQProgressBar::YQProgressBar( YWidget * 	parent,
			      const std::string &	label,
			      int		maxValue )
    : QFrame( (QWidget *) parent->widgetRep() )
    , YProgressBar( parent, label, maxValue )
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    setLayout( layout );

    setWidgetRep( this );

    layout->setSpacing( YQWidgetSpacing );
    layout->setMargin ( YQWidgetMargin  );

    _caption = new YQWidgetCaption( this, label );
    YUI_CHECK_NEW( _caption );
    layout->addWidget( _caption );

    _qt_progressbar = new QProgressBar( this );
    _qt_progressbar->setRange(0, maxValue);
    YUI_CHECK_NEW( _qt_progressbar );
    layout->addWidget( _qt_progressbar );

    _caption->setBuddy( _qt_progressbar );
}


YQProgressBar::~YQProgressBar()
{
    // NOP
}


void YQProgressBar::setLabel( const std::string & label )
{
    _caption->setText( label );
    YProgressBar::setLabel( label );
}


void YQProgressBar::setValue( int newValue )
{
    YProgressBar::setValue( newValue );
    _qt_progressbar->setValue( value() );
}



void YQProgressBar::setEnabled( bool enabled )
{
    _caption->setEnabled( enabled );
    _qt_progressbar->setEnabled( enabled );
    YWidget::setEnabled( enabled );
}


int YQProgressBar::preferredWidth()
{
    int hintWidth = !_caption->isHidden() ?
      _caption->sizeHint().width() + layout()->margin() : 0;

    return max( 200, hintWidth );
}


int YQProgressBar::preferredHeight()
{
    return sizeHint().height();
}


void YQProgressBar::setSize( int newWidth, int newHeight )
{
    resize( newWidth, newHeight );
}


bool YQProgressBar::setKeyboardFocus()
{
    _qt_progressbar->setFocus();

    return true;
}


#include "YQProgressBar.moc"
