/*
 * Hedgewars, a free turn based strategy game
 * Copyright (c) 2006-2011 Andrey Korotaev <unC0Rr@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>

#include "pagedrawmap.h"
#include "drawmapwidget.h"

PageDrawMap::PageDrawMap(QWidget* parent) : AbstractPage(parent)
{
    QGridLayout * pageLayout = new QGridLayout(this);

    QPushButton * pbUndo = addButton(tr("Undo"), pageLayout, 0, 0);
    QPushButton * pbClear = addButton(tr("Clear"), pageLayout, 1, 0);
    QPushButton * pbLoad = addButton(tr("Load"), pageLayout, 2, 0);
    QPushButton * pbSave = addButton(tr("Save"), pageLayout, 3, 0);

    BtnBack = addButton(":/res/Exit.png", pageLayout, 5, 0, true);

    drawMapWidget = new DrawMapWidget(this);
    pageLayout->addWidget(drawMapWidget, 0, 1, 5, 1);

    connect(pbUndo, SIGNAL(clicked()), drawMapWidget, SLOT(undo()));
    connect(pbClear, SIGNAL(clicked()), drawMapWidget, SLOT(clear()));
    connect(pbLoad, SIGNAL(clicked()), this, SLOT(load()));
    connect(pbSave, SIGNAL(clicked()), this, SLOT(save()));
}

void PageDrawMap::load()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load drawn map"), ".", tr("Drawn Maps (*.hwmap);;All files (*.*)"));

    if(!fileName.isEmpty())
        drawMapWidget->load(fileName);
}

void PageDrawMap::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save drawn map"), ".", tr("Drawn Maps (*.hwmap);;All files (*.*)"));

    if(!fileName.isEmpty())
        drawMapWidget->save(fileName);
}