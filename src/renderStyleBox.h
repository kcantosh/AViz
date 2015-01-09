//
// Declaration of render quality box class
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

#ifndef RENBOX_H
#define RENBOX_H

#include "data.h"

#include <QWidget>

class QComboBox;
class QSpinBox;

class MainForm;

// Render quality box in main form
class RenderBox: public QWidget
{
    Q_OBJECT
public:
    RenderBox(MainForm * mainForm, QWidget * parent=0);

    void setValue( viewParam );

private:
    void getRenderMode( viewParam * );
    void getRenderStyle( viewParam * );
    float getRenderSize() const;
    void getRenderQuality( viewParam * );

private slots:
    void renderModeCb();
    void renderStyleCb();
    void renderQualityCb();
    void updateRendering();

private:
    MainForm * mainForm;
    QComboBox * modeCob;
    QComboBox * styleCob;
    QComboBox * qualityCob;
    QSpinBox * renderSSb;
    QSizePolicy sizePolicy() const;
    bool setValueFlag;
};


#endif // RENBOX_H
