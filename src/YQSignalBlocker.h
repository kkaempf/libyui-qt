
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

  File:	      YQSignalBlocker.h

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YQSignalBlocker_h
#define YQSignalBlocker_h

class QObject;

/**
 * Helper class to block Qt signals for QWidgets or QObjects as long as this
 * object exists. 
 *
 * This object will restore the old blocked state when it goes out of scope. 
 **/
class YQSignalBlocker
{
public:

    /**
     * Constructor.
     *
     * Qt signals for 'qobject' will be blocked as long as this object exists.
     * Remember that a QWidget is also a QObject.
     **/
    YQSignalBlocker( QObject * qobject );

    /**
     * Destructor.
     *
     * This will restore the old signal state.
     **/
    ~YQSignalBlocker();


private:

    QObject *	_qobject;
    bool	_oldBlockedState;
};


#endif // ifndef YQSignalBlocker_h
