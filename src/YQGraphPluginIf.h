
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
|						   (c) SuSE Linux GmbH |
\----------------------------------------------------------------------/

  File:		YQGraphPluginIf.h

  Author:	Arvin Schnell <aschnell@suse.de>

/-*/

#ifndef YQGraphPluginIf_h
#define YQGraphPluginIf_h

#include <YGraph.h>
#include <YGraphPlugin.h>


class YQGraphPluginIf
{

public:

    virtual ~YQGraphPluginIf() {}

    virtual YGraph *createGraph( YWidget *parent, const std::string & filename,
				 const std::string & layoutAlgorithm ) = 0;

    virtual YGraph *createGraph( YWidget *parent, graph_t * graph ) = 0;

};

#endif
