#ifndef DIALOG_OPTIONS
#define DIALOG_OPTIONS 1

#include "ui_options.h"

class Dialog_options : public QDialog, private Ui::Dialog_options
{
    Q_OBJECT
public:
    Dialog_options(QWidget *parent = 0)
    {
        setupUi(this);
    }
    
    double get_sandglass() const { return sandglass_spinbox->value(); }
    void set_sandglass(const double sandglass) { sandglass_spinbox->setValue(sandglass); }

    double get_overshooting() const { return overshooting_spinbox->value(); }
    void set_overshooting(const double overshooting) { overshooting_spinbox->setValue(overshooting); }

    int get_inertia() const { return (int)inertia_spinbox->value(); }
    void set_inertia(const double inertia) { inertia_spinbox->setValue(inertia); }
};

#endif
