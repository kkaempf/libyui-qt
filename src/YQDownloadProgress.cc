
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

  File:	      YQLogView.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#include <qlabel.h>
#include <qtimer.h>
#define YUILogComponent "qt-ui"
#include "YUILog.h"

#include "utf8.h"
#include "YQUI.h"
#include "YQDownloadProgress.h"
#include "YQWidgetCaption.h"
#include <QVBoxLayout>
#include <QProgressBar>

YQDownloadProgress::YQDownloadProgress( YWidget *	parent,
					const std::string & 	label,
					const std::string &	filename,
					YFileSize_t	expectedSize )
    : QFrame( (QWidget *) parent->widgetRep() )
    , YDownloadProgress( parent, label, filename, expectedSize )
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    setLayout( layout );

    setWidgetRep( this );
    layout->setMargin( YQWidgetMargin );

    _caption = new YQWidgetCaption( this, label );
    YUI_CHECK_NEW( _caption );
    layout->addWidget( _caption );

    _qt_progressBar = new QProgressBar( this );
    YUI_CHECK_NEW( _qt_progressBar );
    layout->addWidget( _qt_progressBar );

    _qt_progressBar->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed ) );
    _qt_progressBar->setRange( 0, 100 ); // Using percent
    _qt_progressBar->setValue( currentPercent() );

    _timer = new QTimer( this );

    connect( _timer, 	SIGNAL( timeout()      ),
	     this,	SLOT  ( pollFileSize() ) );

    _timer->setSingleShot(false);
    _timer->start( 250 );// millisec
}


YQDownloadProgress::~YQDownloadProgress()
{
    // NOP
}


void
YQDownloadProgress::setLabel( const std::string & label )
{
    _caption->setText( label );
    YDownloadProgress::setLabel( label );
}


void
YQDownloadProgress::setFilename( const std::string & filename )
{
    YDownloadProgress::setFilename( filename );
    _qt_progressBar->setValue( currentPercent() );
}


void
YQDownloadProgress::setExpectedSize( YFileSize_t expectedSize )
{
    _qt_progressBar->setValue( currentPercent() );
    YDownloadProgress::setExpectedSize( expectedSize );
}


void
YQDownloadProgress::pollFileSize()
{
    _qt_progressBar->setValue( currentPercent() );
}


void
YQDownloadProgress::setEnabled( bool enabled )
{
    _caption->setEnabled( enabled );
    _qt_progressBar->setEnabled( enabled );
    YWidget::setEnabled( enabled );
}


int
YQDownloadProgress::preferredWidth()
{
    return sizeHint().width();
}


int
YQDownloadProgress::preferredHeight()
{
    return sizeHint().height();
}


void
YQDownloadProgress::setSize( int newWidth, int newHeight )
{
    resize( newWidth, newHeight );
}


#include "YQDownloadProgress.moc"
