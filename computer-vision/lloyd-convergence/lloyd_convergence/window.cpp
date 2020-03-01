// Qt
#include <QtGui>
#include <QActionGroup>
#include <QFileDialog>
#include <QInputDialog>
#include <QClipboard>

#include <QTextStream>
#include <QUrl>
#include <QSettings>
#include <QHeaderView>

#include "window.h"
#include "options.h"

#include <fstream>

MainWindow::MainWindow() : 
QMainWindow(), Ui_MainWindow(), 
maxNumRecentFiles(3), recentFileActs(3)
{
	setupUi(this);
    
	// init scene
	m_scene = new Scene;
	viewer->set_scene(m_scene);
    
    // default parameters
    m_sandglass = 0.1;
    m_overshooting = 0.1;
    m_inertia = 1;


	// accepts drop events
	setAcceptDrops(true);
    
	// Handling actions
	connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    
	addRecentFiles(menuFile, actionQuit);
	connect(this, SIGNAL(openRecentFile(QString)), this, SLOT(open(QString)));
}

MainWindow::~MainWindow()
{
	delete m_scene;
}

void MainWindow::update()
{
	viewer->repaint();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
	Q_FOREACH(QUrl url, event->mimeData()->urls())
	{
		QString filename = url.toLocalFile();
		if (!filename.isEmpty())
		{
			QTextStream(stderr) << QString("dropEvent(\"%1\")\n").arg(filename);
			open(filename);
		}
	}
	event->acceptProposedAction();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	event->accept();
}

void MainWindow::addToRecentFiles(QString fileName)
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > (int)maxNumRecentFiles)
        files.removeLast();
    settings.setValue("recentFileList", files);
    updateRecentFileActions();
}

void MainWindow::updateRecentFileActions()
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    
    int numRecentFiles = qMin(files.size(), (int)maxNumberOfRecentFiles());
    for (int i = 0; i < numRecentFiles; ++i) {
        QString strippedName = QFileInfo(files[i]).fileName();
        QString text = tr("&%1 %2").arg(i).arg(strippedName);
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (unsigned int j = numRecentFiles; j < maxNumberOfRecentFiles(); ++j)
        recentFileActs[j]->setVisible(false);
    
    recentFilesSeparator->setVisible(numRecentFiles > 0);
}

void MainWindow::addRecentFiles(QMenu* menu, QAction* insertBeforeAction)
{
    if (insertBeforeAction)
        recentFilesSeparator = menu->insertSeparator(insertBeforeAction);
    else 
        recentFilesSeparator = menu->addSeparator();
    recentFilesSeparator->setVisible(false);
    
    for (unsigned int i = 0; i < maxNumberOfRecentFiles(); ++i) {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i], SIGNAL(triggered()), this, SLOT(openRecentFile_aux()));
        if (insertBeforeAction)
            menu->insertAction(insertBeforeAction, recentFileActs[i]);
        else
            menu->addAction(recentFileActs[i]);
    }
    updateRecentFileActions();
}

void MainWindow::openRecentFile_aux()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action)
        emit openRecentFile(action->data().toString());
}

void MainWindow::open(const QString& filename)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	m_scene->load(filename);
	QApplication::restoreOverrideCursor();
	addToRecentFiles(filename);
	update();
}

void MainWindow::on_actionClear_triggered()
{
	m_scene->clear();
	update();
}

void MainWindow::on_actionLoad_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open PSLG"), ".");
	if (!fileName.isEmpty())
		open(fileName);
}

void MainWindow::on_actionBox_triggered()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	m_scene->add_box();
	QApplication::restoreOverrideCursor();
	update();
}

void MainWindow::on_actionCircle_triggered()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	m_scene->add_circle();
	QApplication::restoreOverrideCursor();
	update();
}

void MainWindow::on_actionSandglass_triggered()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    m_scene->add_sandglass();
    QApplication::restoreOverrideCursor();
    update();
}


// lloyd iteration
void MainWindow::on_actionLloyd_triggered()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	m_scene->lloyd();
	QApplication::restoreOverrideCursor();
	update();
}

// add 10 random vertices
void MainWindow::on_actionRandom_vertices_triggered()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	m_scene->add_random_vertices(10);
	QApplication::restoreOverrideCursor();
	update();
}




void MainWindow::on_actionView_edges_toggled()
{
	std::cout << "toggle view edges" << std::endl;
	m_scene->toggle_view_edges();
	update();
}


void MainWindow::on_actionView_relocation_toggled()
{
	std::cout << "toggle view relocation" << std::endl;
	m_scene->toggle_view_relocation();
	update();
}

void MainWindow::on_actionView_sampling_toggled()
{
    std::cout << "toggle sampling activation" << std::endl;
    m_scene->toggle_view_sampling();
    update();
}


void MainWindow::on_actionPlot_convergence_triggered()
{
	std::cout << "Plotting convergence" << std::endl;
	m_scene->plot_convergence();
	update();
}

void MainWindow::on_actionActivate_sandglass_triggered()
{
    std::cout << "toggle sandglass generation" << std::endl;
    m_scene->toggle_view_sandglass();
	update();
}

void MainWindow::on_actionActivate_overshooting_triggered()
{
    std::cout << "toggle overshooting activation" << std::endl;
    m_scene->toggle_view_overshooting();
	update();
}

void MainWindow::on_actionActivate_inertia_triggered()
{
        std::cout << "toggle inertia activation" << std::endl;
    m_scene->toggle_view_inertia();
	update();
}

void MainWindow::on_actionParameters_triggered()
{
    Dialog_options dlg;
    dlg.set_sandglass(m_sandglass);
    dlg.set_overshooting(m_overshooting);
    dlg.set_inertia(m_inertia);

    if(dlg.exec() == QDialog::Accepted)
    {
        m_sandglass = dlg.get_sandglass();
        m_scene->change_sandglass_param(m_sandglass);
        m_overshooting = dlg.get_overshooting();
        m_scene->change_overshooting_param(m_overshooting);
        m_inertia = dlg.get_inertia();
        m_scene->change_inertia_param(m_inertia);
    }
}
