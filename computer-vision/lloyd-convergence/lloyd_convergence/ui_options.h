/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Dialog_options
{
public:
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *overshooting_spinbox;
    QLabel *label;
    QDoubleSpinBox *inertia_spinbox;
    QLabel *label_2;
    QDoubleSpinBox *sandglass_spinbox;
    QLabel *label_3;

    void setupUi(QDialog *Dialog_options)
    {
        if (Dialog_options->objectName().isEmpty())
            Dialog_options->setObjectName(QStringLiteral("Dialog_options"));
        Dialog_options->resize(368, 169);
        buttonBox = new QDialogButtonBox(Dialog_options);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(160, 120, 181, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        overshooting_spinbox = new QDoubleSpinBox(Dialog_options);
        overshooting_spinbox->setObjectName(QStringLiteral("overshooting_spinbox"));
        overshooting_spinbox->setGeometry(QRect(210, 60, 91, 20));
        overshooting_spinbox->setDecimals(2);
        overshooting_spinbox->setMaximum(100);
        overshooting_spinbox->setSingleStep(0.01);
        overshooting_spinbox->setValue(0.1);
        label = new QLabel(Dialog_options);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 60, 81, 20));
        inertia_spinbox = new QDoubleSpinBox(Dialog_options);
        inertia_spinbox->setObjectName(QStringLiteral("inertia_spinbox"));
        inertia_spinbox->setGeometry(QRect(210, 90, 91, 22));
        inertia_spinbox->setDecimals(0);
        inertia_spinbox->setMaximum(20);
        inertia_spinbox->setValue(1);
        label_2 = new QLabel(Dialog_options);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 90, 71, 21));
        sandglass_spinbox = new QDoubleSpinBox(Dialog_options);
        sandglass_spinbox->setObjectName(QStringLiteral("sandglass_spinbox"));
        sandglass_spinbox->setGeometry(QRect(210, 30, 91, 20));
        sandglass_spinbox->setDecimals(2);
        sandglass_spinbox->setMaximum(0.3);
        sandglass_spinbox->setSingleStep(0.01);
        sandglass_spinbox->setValue(0.1);
        label_3 = new QLabel(Dialog_options);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(70, 30, 81, 20));

        retranslateUi(Dialog_options);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_options, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_options, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_options);
    } // setupUi

    void retranslateUi(QDialog *Dialog_options)
    {
        Dialog_options->setWindowTitle(QApplication::translate("Dialog_options", "Options", 0));
        label->setText(QApplication::translate("Dialog_options", "Overshooting", 0));
        label_2->setText(QApplication::translate("Dialog_options", "Inertia", 0));
        label_3->setText(QApplication::translate("Dialog_options", "Sandglass", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_options: public Ui_Dialog_options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
