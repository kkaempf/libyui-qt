
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

  File:	 	YQDateField.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/


#ifndef YQDateField_h
#define YQDateField_h

#include <QFrame>
#include <QDateEdit>

#include "YDateField.h"

class YQWidgetCaption;


class YQDateField : public QFrame, public YDateField
{
    Q_OBJECT

public:

    /**
     * Constructor.
     **/
    YQDateField( YWidget *	parent,
		 const std::string & label );

    /**
     * Destructor.
     **/
    virtual ~YQDateField();

    /**
     * Get the current value (the text entered by the user or set from the
     * outside) of this input field.
     *
     * Implemented from YSimpleInputField.
     **/
    virtual std::string value();

    /**
     * Set the current value (the text entered by the user or set from the
     * outside) of this input field.
     *
     * Implemented from YSimpleInputField.
     **/
    virtual void setValue( const std::string & newValue );

    /**
     * Set the label (the caption above the input field).
     *
     * Reimplemented from YSimpleInputField.
     **/
    virtual void setLabel( const std::string & label );

    /**
     * Set enabled/disabled state.
     *
     * Reimplemented from YWidget.
     **/
    virtual void setEnabled( bool enabled );

    /**
     * Preferred width of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual int preferredWidth();

    /**
     * Preferred height of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual int preferredHeight();

    /**
     * Set the new size of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual void setSize( int newWidth, int newHeight );

    /**
     * Accept the keyboard focus.
     *
     * Reimplemented from YWidget.
     **/
    virtual bool setKeyboardFocus();


protected:

    YQWidgetCaption *	_caption;
    QDateEdit *		_qt_dateEdit;
};


#endif // YQDateField_h
