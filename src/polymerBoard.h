//
// Declaration of polymer board class (like atom board class)
//

/**********************************************************************
Copyright (C) 2001  Geri Wagner

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

#ifndef POLYMB_H
#define POLYMB_H 

#include <QDialog>

#include "data.h"

class QGridLayout;
class QGroupBox;
class QLabel;
class QRadioButton;
class QPushButton;
class QComboBox;
class QCheckBox;
class QWidget;

class MainForm;
class ColorLabel;
class ColorBoard;
class CodeBox;
class SizeBox;
class PositionBox;
class PropertyBox;

// Polymer board dialog widget
class PolymerBoard: public QDialog
{
    Q_OBJECT
public:
    PolymerBoard(QWidget * parent=0);

public slots:
    void setMainFormAddress( MainForm * );
    void setData();
    void getColors( float, float, float, float, float, float );
    void getColorBoardPos( int, int );
    void setDotStyle();
    void setLineStyle();
    void setCubeStyle();
    void setCylinderStyle();
    void setConeStyle();
    void setSphereStyle();
    void setLowQuality();
    void setHighQuality();
    void setFinalQuality();
    void closeColorBoard();

private slots:
    void buildLayout( colorCriterion );
    void setPolymerAtom();
    void adjustPolymer();
    void adjustCriterion();
    void setColorCb();
    void setColors();
    void readToggles();
    void bbonds();
    void bdone();
    void bapply();
    void bcancel();

private:
    MainForm * mainForm;
    CodeBox * codeBox;
    PositionBox * positionBox;
    PropertyBox * propertyBox;
    SizeBox * sizeBox;
    QGridLayout * polymerBox;
    QWidget * hb1;
    QWidget * hb2;
    QWidget * hb3;
    QWidget * hb4;
    QWidget * hb5;
    QComboBox * atomCob;
    QComboBox * styleCob;
    QCheckBox * showPolymerAtomCb;
    QLabel * modeL;
    QGroupBox * colorMode;
    QRadioButton * colorMode0;
    QRadioButton * colorMode1;
    QRadioButton * colorMode2;
    QRadioButton * colorMode3;
    ColorLabel * colorLabel0;
    ColorLabel * colorLabel1;
    ColorLabel * colorLabel2;
    ColorLabel * colorLabel3;
    ColorLabel * colorLabel4;
    ColorLabel * colorLabel5;
    QPushButton * colorButton;
    ColorBoard * cb;
    particleData * thisPd;
    int thisPolymerAtomIndex;
    char colors;
    int colorPosX, colorPosY;
    polymerAtomRStyle polymerAtomRenderStyle;
    quality renderQuality;
    bool showColorBoard;
};

#endif // POLYMB_H
