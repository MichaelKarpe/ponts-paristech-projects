#include <QtGui>
#include "plotviewer.h"

PlotViewer::PlotViewer(QWidget *pParent, std::vector<double> C)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), pParent)
{
	courbe = C;
	setAutoFillBackground(false);
}


void PlotViewer::initializeGL() {
	glClearColor(1., 1., 1., 0.);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);
}

void PlotViewer::paintGL() {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < courbe.size(); i++)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2d(i, courbe[i]);
	}
}