#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QGLWidget>
#include <QPaintEvent>
#include "scene.h"

class PlotViewer : public QGLWidget
{
	Q_OBJECT

private:
	std::vector<double> courbe;

public:
	PlotViewer(QWidget *parent, std::vector<double> C);

protected:
	// GL
	void paintGL();
	void initializeGL();
};

#endif