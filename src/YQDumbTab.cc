
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

  File:	      YQDumbTab.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#define YUILogComponent "qt-ui"
#include "YUILog.h"
#include <qtabbar.h>
#include <qevent.h>
#include <qpainter.h>
#include <qdrawutil.h>
#include <algorithm>

#include "YQSignalBlocker.h"
#include "utf8.h"
#include "YQUI.h"
#include "YQDumbTab.h"
#include "YQAlignment.h"
#include "YEvent.h"

#define YQDumbTabSpacing	2
#define YQDumbTabFrameMargin	2


YQDumbTab::YQDumbTab( YWidget *	parent )
    : QWidget( (QWidget *) parent->widgetRep() )
    , YDumbTab( parent )
{
    setWidgetRep( this );

    //
    // Tab bar
    //

    _tabBar = new QTabBar( this );
    Q_CHECK_PTR( _tabBar );

    _tabBar->setSizePolicy( QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred ) ); // hor/vert
    setFocusProxy( _tabBar );
    setFocusPolicy( Qt::TabFocus );

    connect( _tabBar, SIGNAL( selected    ( int ) ),
	     this,    SLOT  ( slotSelected( int ) ) );
}


YQDumbTab::~YQDumbTab()
{
    // NOP
}


void
YQDumbTab::addItem( YItem * item )
{
    YQSignalBlocker sigBlocker( _tabBar );
    YDumbTab::addItem( item );

    _tabBar->insertTab( item->index(), fromUTF8( item->label() ) );
    yuiDebug() << "Adding tab page [" << item->label() << "]" << std::endl;

    if ( item->selected() )
	_tabBar->setCurrentIndex( item->index() );
}


void
YQDumbTab::selectItem( YItem * item, bool selected )
{
    if ( selected )
    {
	// Don't try to suppress any signals sent here with a YQSignalBlocker,
	// otherwise the application code that handles the event will never be executed.

        _tabBar->setCurrentIndex( item->index() );
    }

    YDumbTab::selectItem( item, selected );
}


void
YQDumbTab::deleteAllItems()
{
    for ( YItemConstIterator it = itemsBegin();
	  it != itemsEnd();
	  ++it )
    {
        _tabBar->removeTab( ( *it )->index() );
    }

    YDumbTab::deleteAllItems();
}


void
YQDumbTab::deselectAllItems()
{
    YDumbTab::deselectAllItems();
}


void
YQDumbTab::slotSelected( int index )
{
    YItem * item = itemAt( index );
    YUI_CHECK_PTR( item );
    yuiDebug() << "Tab [" << item->label() << "] selected" << std::endl;
    YDumbTab::selectItem( item );

    YQUI::ui()->sendEvent( new YMenuEvent( item ) );
}


void
YQDumbTab::shortcutChanged()
{
    // Any of the items might have its keyboard shortcut changed, but we don't
    // know which one. So let's simply set all tab labels again.
    
    for ( YItemConstIterator it = itemsBegin();
	  it != itemsEnd();
	  ++it )
    {
	YItem * item = *it;
	_tabBar->setTabText( item->index(), fromUTF8( item->label() ) );
    }
}


void
YQDumbTab::setEnabled( bool enabled )
{
    _tabBar->setEnabled( enabled );
    YWidget::setEnabled( enabled );
}


int
YQDumbTab::preferredWidth()
{
    int tabBarWidth = _tabBar->sizeHint().width();
    int childWidth  = hasChildren() ? firstChild()->preferredWidth() : 0;

    return std::max( tabBarWidth, childWidth );
}


int
YQDumbTab::preferredHeight()
{
    int tabBarHeight = _tabBar->sizeHint().height();
    int childHeight  = hasChildren() ? firstChild()->preferredHeight() : 0;

    return tabBarHeight + YQDumbTabSpacing + childHeight;
}


void
YQDumbTab::setSize( int newWidth, int newHeight )
{
    QWidget::resize( newWidth, newHeight );
    int remainingHeight = newHeight;
    int remainingWidth  = newWidth;
    int x_offset	= 0;
    int y_offset	= 0;

    //
    // _tabBar (fixed height)
    //

    int tabBarHeight = _tabBar->sizeHint().height();

    if ( remainingHeight < tabBarHeight )
	tabBarHeight = remainingHeight;

    _tabBar->resize( newWidth, tabBarHeight );
    remainingHeight -= tabBarHeight;

    if ( hasChildren() )
    {
	//
	// Spacing between tabBar and client area
	//

	remainingHeight -= YQDumbTabSpacing;
	y_offset = newHeight - remainingHeight;

	//
	// 3D border
	//

	remainingHeight -= 2 * YQDumbTabFrameMargin;
	remainingWidth  -= 2 * YQDumbTabFrameMargin;
	x_offset += YQDumbTabFrameMargin;
	y_offset += YQDumbTabFrameMargin;

	if ( remainingHeight < 0 )
	    remainingHeight = 0;

	if ( remainingWidth < 0 )
	    remainingWidth = 0;

	//
	// Client area
	//


	firstChild()->setSize( remainingWidth, remainingHeight );

	QWidget * qChild = (QWidget *) firstChild()->widgetRep();
	qChild->move( x_offset, y_offset );
    }
}



#include "YQDumbTab.moc"
