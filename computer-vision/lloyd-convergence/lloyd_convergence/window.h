#ifndef _WINDOW_
#define _WINDOW_

// std
#include <list>
#include <QWidget>

// Qt
#include <QString>
#include "scene.h"
#include "ui_lloyd.h"

class MainWindow : public QMainWindow, public Ui_MainWindow
{
	Q_OBJECT

private:
	Scene* m_scene;

	unsigned int maxNumRecentFiles;
	QAction* recentFilesSeparator;
	QVector<QAction*> recentFileActs;

    // parameters
    double m_sandglass;
    double m_overshooting;
    int m_inertia;

public:
	MainWindow();
	~MainWindow();

	void update();

protected:
	void addRecentFiles(QMenu* menu, QAction* insertBefore = 0);    
	unsigned int maxNumberOfRecentFiles() const {return maxNumRecentFiles;}

	protected slots:

		// drag & drop
		void dropEvent(QDropEvent *event);
		void closeEvent(QCloseEvent *event);
		void dragEnterEvent(QDragEnterEvent *event);

		// recent files
		void openRecentFile_aux();
		void updateRecentFileActions();
		void addToRecentFiles(QString fileName);

		// io
		void on_actionLoad_triggered();
		void open(const QString& file);

        // algorithms menu
        void on_actionParameters_triggered();

public slots:

	    // Data
			void on_actionBox_triggered();
			void on_actionCircle_triggered();
            void on_actionSandglass_triggered();
			void on_actionClear_triggered();
			void on_actionRandom_vertices_triggered();

			// algorithms
			void on_actionLloyd_triggered();

			// view
			void on_actionView_edges_toggled();
			void on_actionView_relocation_toggled();
            void on_actionView_sampling_toggled();

			// plot
			void on_actionPlot_convergence_triggered();
            void on_actionActivate_sandglass_triggered();
            void on_actionActivate_overshooting_triggered();
            void on_actionActivate_inertia_triggered();

signals:
			void openRecentFile(QString filename);
};

#endif // _WINDOW_
