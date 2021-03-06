
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

  File:	      YQInputField.h

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#ifndef YQInputField_h
#define YQInputField_h

#include <QFrame>
#include <qlineedit.h>

#include "YInputField.h"

class QString;
class QY2CharValidator;
class YQWidgetCaption;
class YQRawLineEdit;

using std::string;


class YQInputField : public QFrame, public YInputField
{
    Q_OBJECT

public:
    /**
     * Constructor.
     **/
    YQInputField( YWidget *		parent,
		  const std::string & 	label,
		  bool			passwordMode = false );

    /**
     * Get the current value (the text entered by the user or set from the
     * outside) of this input field.
     *
     * Reimplemented from YInputField.
     **/
    virtual std::string value();

    /**
     * Set the current value (the text entered by the user or set from the
     * outside) of this input field.
     *
     * Reimplemented from YInputField.
     **/
    virtual void setValue( const std::string & text );

    /**
     * Set the label (the caption above the input field).
     *
     * Reimplemented from YInputField.
     **/
    virtual void setLabel( const std::string & label );

    /**
     * Set the valid input characters. No input validation is performed (i.e.,
     * the user can enter anything) if this is empty.
     *
     * Reimplemented from YInputField.
     **/
    virtual void setValidChars( const std::string & validChars );

    /**
     * Specify the amount of characters which can be inserted.
     *
     * Reimplemented from YInputField.
     **/
    virtual void setInputMaxLength( int numberOfChars );

    /**
     * Returns 'true' if a given text is valid according to ValidChars.
     **/
    bool isValidText( const QString & text ) const;

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


protected slots:
    /**
     * Triggered when the text in the InputField changes.
     * This _may_ be of interest to the module.
     **/
    void changed( const QString & );

    /**
     * Display a warning that CapsLock is active:
     * Replace the label with "CapsLock!"
     **/
    void displayCapsLockWarning();

    /**
     * Clear the CapsLock warning: Restore old label
     **/
    void clearCapsLockWarning();


protected:

    YQWidgetCaption *	_caption;
    YQRawLineEdit *	_qt_lineEdit;
    QY2CharValidator *	_validator;
    bool		_shrinkable;
    bool		_displayingCapsLockWarning;
};


/**
 * Helper class that can obtain the CapsLock status, too.
 * For some reason, Qt does not propagate that information from X11.
 **/
class YQRawLineEdit: public QLineEdit
{
    Q_OBJECT

public:

    /**
     * Constructor
     **/
    YQRawLineEdit( QWidget * parent )
	: QLineEdit( parent )
	, _capsLockActive( false )
	{}

    /**
     * Destructor
     **/
    virtual ~YQRawLineEdit() {};

    /**
     * Check if CapsLock is active
     * (rather: was active at the time of the last key or focus event)
     **/
    bool isCapsLockActive() const { return _capsLockActive; }


signals:
    void capsLockActivated();
    void capsLockDeactivated();

protected:

    /**
     * X11 raw event handler. Propagates all events to the Qt event handlers,
     * but updates _capsLockActive for key events.
     *
     * Reimplemented from QWidget.
     **/
    bool x11Event( XEvent * event ) ;

private:

    bool _capsLockActive;
};

#endif // YQInputField_h
