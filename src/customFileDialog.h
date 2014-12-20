//
// Declaration of customized file dialog class
//

/**********************************************************************
Copyright (C) 2001 - 2003  Geri Wagner

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

Contact address: Computational Physics Group, Dept. of Physics,
                 Technion. 32000 Haifa Israel
                 gery@tx.technion.ac.il
***********************************************************************/

#ifndef CUSTOM_FILE_DIALOG_H
#define CUSTOM_FILE_DIALOG_H

#include <QFileDialog>

/*! @class CustomFileDialog
    Custom file dialog to select an existing xyz file.  The dialog
    also includes a button to generate a text file containing a list
    of the xyz files in the current directory.
*/
class CustomFileDialog: public QFileDialog
{ 
	Q_OBJECT
public:
	CustomFileDialog();
	~CustomFileDialog();

private slots:
    /// generates a file ( ) containing a list of file names
    /// of all xyz files in current directory
	void generateFileList();
};

#endif // CFILEDI_H 
