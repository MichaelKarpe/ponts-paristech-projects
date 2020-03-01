/********************************************************************************
** Form generated from reading UI file 'lloyd.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LLOYD_H
#define UI_LLOYD_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "glviewer.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionClear;
    QAction *actionLoad;
    QAction *actionBox;
    QAction *actionLloyd;
    QAction *actionCircle;
    QAction *actionDelaunay_conforming;
    QAction *actionGabriel_conforming;
    QAction *actionBatch_refine;
    QAction *actionView_edges;
    QAction *actionRandom_vertices;
    QAction *actionView_relocation;
    QAction *actionActivate_sandglass;
    QAction *actionActivate_overshooting;
    QAction *actionValue_overshooting;
    QAction *actionActivate_inertia;
    QAction *actionValue_inertia;
    QAction *actionParameters;
    QAction *actionSandglass;
    QAction *actionView_sampling;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    GlViewer *viewer;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuData;
    QMenu *menuAlgorithms;
    QMenu *menuView;
    QMenu *menuOptions;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(798, 629);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionBox = new QAction(MainWindow);
        actionBox->setObjectName(QStringLiteral("actionBox"));
        actionLloyd = new QAction(MainWindow);
        actionLloyd->setObjectName(QStringLiteral("actionLloyd"));
        actionCircle = new QAction(MainWindow);
        actionCircle->setObjectName(QStringLiteral("actionCircle"));
        actionDelaunay_conforming = new QAction(MainWindow);
        actionDelaunay_conforming->setObjectName(QStringLiteral("actionDelaunay_conforming"));
        actionGabriel_conforming = new QAction(MainWindow);
        actionGabriel_conforming->setObjectName(QStringLiteral("actionGabriel_conforming"));
        actionBatch_refine = new QAction(MainWindow);
        actionBatch_refine->setObjectName(QStringLiteral("actionBatch_refine"));
        actionView_edges = new QAction(MainWindow);
        actionView_edges->setObjectName(QStringLiteral("actionView_edges"));
        actionView_edges->setCheckable(true);
        actionView_edges->setChecked(true);
        actionRandom_vertices = new QAction(MainWindow);
        actionRandom_vertices->setObjectName(QStringLiteral("actionRandom_vertices"));
        actionView_relocation = new QAction(MainWindow);
        actionView_relocation->setObjectName(QStringLiteral("actionView_relocation"));
        actionView_relocation->setCheckable(true);
        actionView_relocation->setChecked(true);
        actionActivate_sandglass = new QAction(MainWindow);
        actionActivate_sandglass->setObjectName(QStringLiteral("actionActivate_sandglass"));
        actionActivate_sandglass->setCheckable(true);
        actionActivate_overshooting = new QAction(MainWindow);
        actionActivate_overshooting->setObjectName(QStringLiteral("actionActivate_overshooting"));
        actionActivate_overshooting->setCheckable(true);
        actionValue_overshooting = new QAction(MainWindow);
        actionValue_overshooting->setObjectName(QStringLiteral("actionValue_overshooting"));
        actionActivate_inertia = new QAction(MainWindow);
        actionActivate_inertia->setObjectName(QStringLiteral("actionActivate_inertia"));
        actionActivate_inertia->setCheckable(true);
        actionValue_inertia = new QAction(MainWindow);
        actionValue_inertia->setObjectName(QStringLiteral("actionValue_inertia"));
        actionParameters = new QAction(MainWindow);
        actionParameters->setObjectName(QStringLiteral("actionParameters"));
        actionSandglass = new QAction(MainWindow);
        actionSandglass->setObjectName(QStringLiteral("actionSandglass"));
        actionView_sampling = new QAction(MainWindow);
        actionView_sampling->setObjectName(QStringLiteral("actionView_sampling"));
        actionView_sampling->setCheckable(true);
        actionView_sampling->setChecked(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        viewer = new GlViewer(centralwidget);
        viewer->setObjectName(QStringLiteral("viewer"));
        viewer->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(viewer, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 798, 27));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuData = new QMenu(menubar);
        menuData->setObjectName(QStringLiteral("menuData"));
        menuAlgorithms = new QMenu(menubar);
        menuAlgorithms->setObjectName(QStringLiteral("menuAlgorithms"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuData->menuAction());
        menubar->addAction(menuAlgorithms->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuData->addAction(actionClear);
        menuData->addAction(actionRandom_vertices);
        menuData->addSeparator();
        menuData->addAction(actionBox);
        menuData->addAction(actionCircle);
        menuData->addAction(actionSandglass);
        menuData->addSeparator();
        menuAlgorithms->addAction(actionLloyd);
        menuView->addAction(actionView_edges);
        menuView->addAction(actionView_relocation);
        menuView->addAction(actionView_sampling);
        menuOptions->addAction(actionActivate_sandglass);
        menuOptions->addAction(actionActivate_overshooting);
        menuOptions->addAction(actionActivate_inertia);
        menuOptions->addSeparator();
        menuOptions->addAction(actionParameters);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CGAL - Lloyd iteration", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionClear->setText(QApplication::translate("MainWindow", "Clear vertices", 0));
#ifndef QT_NO_STATUSTIP
        actionClear->setStatusTip(QApplication::translate("MainWindow", "Clear", 0));
#endif // QT_NO_STATUSTIP
        actionClear->setShortcut(QApplication::translate("MainWindow", "C", 0));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0));
#ifndef QT_NO_STATUSTIP
        actionLoad->setStatusTip(QApplication::translate("MainWindow", "Load PSLG", 0));
#endif // QT_NO_STATUSTIP
        actionLoad->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionBox->setText(QApplication::translate("MainWindow", "Box domain", 0));
        actionLloyd->setText(QApplication::translate("MainWindow", "Lloyd", 0));
        actionLloyd->setShortcut(QApplication::translate("MainWindow", "L", 0));
        actionCircle->setText(QApplication::translate("MainWindow", "Circle domain", 0));
        actionDelaunay_conforming->setText(QApplication::translate("MainWindow", "Delaunay conforming", 0));
        actionGabriel_conforming->setText(QApplication::translate("MainWindow", "Gabriel conforming", 0));
        actionBatch_refine->setText(QApplication::translate("MainWindow", "Batch refine", 0));
        actionView_edges->setText(QApplication::translate("MainWindow", "Edges", 0));
        actionView_edges->setShortcut(QApplication::translate("MainWindow", "E", 0));
        actionRandom_vertices->setText(QApplication::translate("MainWindow", "Add random vertices", 0));
        actionRandom_vertices->setShortcut(QApplication::translate("MainWindow", "A", 0));
        actionView_relocation->setText(QApplication::translate("MainWindow", "Relocation", 0));
        actionView_relocation->setShortcut(QApplication::translate("MainWindow", "R", 0));
        actionActivate_sandglass->setText(QApplication::translate("MainWindow", "Sandglass", 0));
        actionActivate_sandglass->setShortcut(QApplication::translate("MainWindow", "S", 0));
        actionActivate_overshooting->setText(QApplication::translate("MainWindow", "Overshooting", 0));
        actionActivate_overshooting->setShortcut(QApplication::translate("MainWindow", "O", 0));
        actionValue_overshooting->setText(QApplication::translate("MainWindow", "Value", 0));
        actionActivate_inertia->setText(QApplication::translate("MainWindow", "Temporal inertia", 0));
        actionActivate_inertia->setShortcut(QApplication::translate("MainWindow", "T", 0));
        actionValue_inertia->setText(QApplication::translate("MainWindow", "Value", 0));
        actionParameters->setText(QApplication::translate("MainWindow", "Parameters", 0));
        actionParameters->setShortcut(QApplication::translate("MainWindow", "P", 0));
        actionSandglass->setText(QApplication::translate("MainWindow", "Sandglass domain", 0));
        actionView_sampling->setText(QApplication::translate("MainWindow", "Sampling", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuData->setTitle(QApplication::translate("MainWindow", "Data", 0));
        menuAlgorithms->setTitle(QApplication::translate("MainWindow", "Algorithms", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LLOYD_H
