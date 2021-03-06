//
// Implementation of slice board dialog widget class
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

#include "sliceBoard.h"

#include <cmath>

#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>

#include "mainForm.h"
#include "floatSpin.h"
#include "parameterLimits.h"
#include "widgets/doneapplycancelwidget.h"

// Make a popup dialog box 
SliceBoard::SliceBoard(MainForm *mainForm, QWidget * parent)
    : QDialog(parent), mainForm(mainForm)
{
    setWindowTitle( "AViz: Set Clipping" );

    // Insert a grid that will hold spin boxes
    // plus a row of control buttons
    QGridLayout * sliceBox = new QGridLayout(this);
    sliceBox->setHorizontalSpacing(SPACE);
    sliceBox->setVerticalSpacing(SPACE);

    // Create a check box
    sliceCb = new QCheckBox("Slicing On");
    sliceBox->addWidget( sliceCb, 0, 0 );

    // Create a pushbutton to adjust to boundaries
    QPushButton * boundaryPb = new QPushButton("Set to Contour");
    sliceBox->addWidget( boundaryPb, 0, 4 );

    // Define a callback for that button
    connect( boundaryPb, SIGNAL(clicked()), this, SLOT(autoSlice()) );

    // Create spin boxes, labels and check boxes
    sliceBox->addWidget(new QLabel(" Slice X From: "), 1, 0 );

    sliceSbX1 = new QFSpinBox( this );
    sliceSbX1->setMinimum( MINSLI );
    sliceSbX1->setMaximum( MAXSLI );
    sliceBox->addWidget( sliceSbX1, 1, 1 );

    sliceBox->addWidget(new QLabel(" To: "), 1, 2 );

    sliceSbX2 = new QFSpinBox( this );
    sliceSbX2->setMinimum( MINSLI );
    sliceSbX2->setMaximum( MAXSLI );
    sliceBox->addWidget( sliceSbX2, 1, 3 );

    sliceBox->addWidget(new QLabel(" Slice Y From: "), 2, 0 );

    sliceSbY1 = new QFSpinBox( this );
    sliceSbY1->setMinimum( MINSLI );
    sliceSbY1->setMaximum( MAXSLI );
    sliceBox->addWidget( sliceSbY1, 2, 1 );

    sliceBox->addWidget(new QLabel(" To: "), 2, 2 );

    sliceSbY2 = new QFSpinBox( this );
    sliceSbY2->setMinimum( MINSLI );
    sliceSbY2->setMaximum( MAXSLI );
    sliceBox->addWidget( sliceSbY2, 2, 3 );

    sliceBox->addWidget(new QLabel(" Slice Z From: "), 3, 0 );

    sliceSbZ1 = new QFSpinBox( this );
    sliceSbZ1->setMinimum( MINSLI );
    sliceSbZ1->setMaximum( MAXSLI );
    sliceBox->addWidget( sliceSbZ1, 3, 1 );

    sliceBox->addWidget(new QLabel(" To: "), 3, 2 );

    sliceSbZ2 = new QFSpinBox( this );
    sliceSbZ2->setMinimum( MINSLI );
    sliceSbZ2->setMaximum( MAXSLI );
    sliceBox->addWidget( sliceSbZ2, 3, 3 );

    // Define a callback for the spin boxes
    connect( sliceSbX1, SIGNAL(valueChanged(int)), this, SLOT(sliceChanged()) );
    connect( sliceSbX2, SIGNAL(valueChanged(int)), this, SLOT(sliceChanged()) );
    connect( sliceSbY1, SIGNAL(valueChanged(int)), this, SLOT(sliceChanged()) );
    connect( sliceSbY2, SIGNAL(valueChanged(int)), this, SLOT(sliceChanged()) );
    connect( sliceSbZ1, SIGNAL(valueChanged(int)), this, SLOT(sliceChanged()) );
    connect( sliceSbZ2, SIGNAL(valueChanged(int)), this, SLOT(sliceChanged()) );

    // Create check boxes
    indicateXCb = new QCheckBox("Indicate Only");
    sliceBox->addWidget( indicateXCb, 1, 4 );

    indicateYCb = new QCheckBox("Indicate Only");
    sliceBox->addWidget( indicateYCb, 2, 4 );

    indicateZCb = new QCheckBox("Indicate Only");
    sliceBox->addWidget( indicateZCb, 3, 4 );

    // Define a callback for these check boxes
    connect( indicateXCb, SIGNAL(clicked()), this, SLOT(sliceChangedX()) );
    connect( indicateYCb, SIGNAL(clicked()), this, SLOT(sliceChangedY()) );
    connect( indicateZCb, SIGNAL(clicked()), this, SLOT(sliceChangedZ()) );

    DoneApplyCancelWidget *doneApplyCancel = new DoneApplyCancelWidget(this);
    connect(doneApplyCancel, SIGNAL(done()), this, SLOT(bdone()) );
    connect(doneApplyCancel, SIGNAL(applied()), this, SLOT(bapply()) );
    connect(doneApplyCancel, SIGNAL(canceled()), this, SLOT(bcancel()));

    sliceBox->addWidget(doneApplyCancel, 4/*fromRow*/, 0 /*fromCol*/, 1 /*rowSpan*/, -1/*colSpan*/);
}

// Get the current settings from the main form
void SliceBoard::setSlice( viewParam vp )
{
    // Update the controls
    sliceCb->setChecked( vp.slicing );

    indicateXCb->setChecked( vp.showSlicePlaneX );
    indicateYCb->setChecked( vp.showSlicePlaneY );
    indicateZCb->setChecked( vp.showSlicePlaneZ );

    sliceSbX1->setValue( (int)floor(10.0*vp.sliceXMin+0.5) );
    sliceSbX2->setValue( (int)floor(10.0*vp.sliceXMax+0.5) );
    sliceSbY1->setValue( (int)floor(10.0*vp.sliceYMin+0.5) );
    sliceSbY2->setValue( (int)floor(10.0*vp.sliceYMax+0.5) );
    sliceSbZ1->setValue( (int)floor(10.0*vp.sliceZMin+0.5) );
    sliceSbZ2->setValue( (int)floor(10.0*vp.sliceZMax+0.5) );
}


// Fill in slice values corresponding to viewing the entire set
void SliceBoard::autoSlice()
{
    // Get the current settings
    viewParam thisVp = (*mainForm->getViewParam());
    viewObject thisVo = (*mainForm->getViewObject());

    thisVp.sliceXMin = thisVo.xmin-SLICEEPS;
    thisVp.sliceXMax = thisVo.xmax+SLICEEPS;
    thisVp.sliceYMin = thisVo.ymin-SLICEEPS;
    thisVp.sliceYMax = thisVo.ymax+SLICEEPS;
    thisVp.sliceZMin = thisVo.zmin-SLICEEPS;
    thisVp.sliceZMax = thisVo.zmax+SLICEEPS;

    this->setSlice( thisVp );
}


// Respond to changes of the boundary values
void SliceBoard::sliceChanged()
{
    // Always activate the slicing-on toggle when values change
    sliceCb->setChecked(true);
}


// Respond to changes of the boundary values
void SliceBoard::sliceChangedX()
{
    // Always activate the slicing-on toggle when values change
    sliceCb->setChecked(true);
}


// Respond to changes of the boundary values
void SliceBoard::sliceChangedY()
{
    // Always activate the slicing-on toggle when values change
    sliceCb->setChecked(true);
}


// Respond to changes of the boundary values
void SliceBoard::sliceChangedZ()
{
    // Always activate the slicing-on toggle when values change
    sliceCb->setChecked(true);
}


// Read the current clip settings
void SliceBoard::registerSettings()
{
    // Get the current settings
    viewParam * vp = mainForm->getViewParam( );

    (*vp).slicing = sliceCb->isChecked();

    (*vp).showSlicePlaneX = indicateXCb->isChecked();
    (*vp).showSlicePlaneY = indicateYCb->isChecked();
    (*vp).showSlicePlaneZ = indicateZCb->isChecked();

    (*vp).sliceXMin = (float)sliceSbX1->value()/10.0;
    (*vp).sliceXMax = (float)sliceSbX2->value()/10.0;
    (*vp).sliceYMin = (float)sliceSbY1->value()/10.0;
    (*vp).sliceYMax = (float)sliceSbY2->value()/10.0;
    (*vp).sliceZMin = (float)sliceSbZ1->value()/10.0;
    (*vp).sliceZMax = (float)sliceSbZ2->value()/10.0;

    (*vp).slicingSet = true;
}


// Accept the setting: update the rendering and hide the board
void SliceBoard::bdone()
{
    this->registerSettings();

    // Re-do the graphics, using the new view settings
    // Re-define the view object and re-draw
    mainForm->updateView();
    mainForm->updateRendering();

    // Hide now
    hide();
}


// Accept the setting: update the rendering 
void SliceBoard::bapply()
{
    this->registerSettings();

    // Re-do the graphics, using the new view settings
    // Re-define the view object and re-draw
    mainForm->updateView();
    mainForm->updateRendering();
}


// Cancel the setting: hide the board
void SliceBoard::bcancel()
{
    // Hide now
    hide();
}
