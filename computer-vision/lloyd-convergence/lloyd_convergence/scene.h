#ifndef _SCENE_H_
#define _SCENE_H_

// std
#include <fstream>
#include <algorithm>

// Qt
#include <QtOpenGL>

// CGAL
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/Delaunay_mesh_face_base_2.h>

#include "include/cdt.h"
#include "include/dt.h"
#include "plotviewer.h"
 
#undef min
#undef max

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

class Scene
{
public:
	//typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

	typedef Kernel::FT FT;
	typedef Kernel::Point_2 Point;
	typedef Kernel::Vector_2 Vector;
	typedef Kernel::Triangle_2 Triangle;

	// Constrained Delaunay triangulation
	typedef CGAL::Triangulation_vertex_base_2<Kernel> Vb;
	typedef CGAL::Delaunay_mesh_face_base_2<Kernel> Fb;
	typedef My_vertex_base<Kernel,Vb> MVb;
	typedef My_face_base<Kernel,Fb> MFb;
	typedef CGAL::Triangulation_data_structure_2<MVb,MFb> MTDS;
	typedef CGAL::Exact_intersections_tag Itag;
	typedef CGAL::Constrained_Delaunay_triangulation_2<Kernel,MTDS,Itag> MCDT;
	typedef CGAL::Constrained_triangulation_plus_2<MCDT> MCDTP;
	typedef CCDT<MCDTP> CDT;

	// Delaunay triangulation
	typedef CGAL::Triangulation_vertex_base_2<Kernel> Vertex_base;
	typedef Dvertex_base<Vertex_base> DVb;
	typedef CGAL::Triangulation_face_base_2<Kernel> DFb;
	typedef CGAL::Triangulation_data_structure_2<DVb, DFb> TDS;
	typedef MDT<Kernel, TDS> DT;
	typedef typename CGAL::Delaunay_triangulation_2<Kernel, TDS> Dt2;


private:
	CDT m_cdt; // Domain
	DT m_dt; // triangulation
	DT m_dt_previous;
	std::list<Triangle> m_triangles; // inside triangles of domain
	std::vector<double> average_length;

	// Energy of the mesh : points used to discretize the calculus
	std::vector<Point> points_alea;
	std::vector<double> energies;

	// To compute the overshooting
    std::vector< std::vector<Point> > past_points;
    std::vector<FT> coefs_temporal;
	int inertia_param;
    int nb_temporal_iter; // current number of saved iterations of points <= inertia_param
	FT overshooting_param; // if inertia_param = 1, easy to change it directly in the gui

	// Parameters in the gui
	bool m_view_relocation;
	bool m_view_edges;
    bool m_sandglass;
	bool m_overshooting;
    bool m_inertia;
    bool m_view_sampling;

	// Position of the mouse
	Point m_mouse_pos;

    // How high are the points generated in the sandglass test. 
	double sandglass_param;

	// Display relocalization
	std::vector< std::pair<Point, Point> > prev_next;

public:    
	Scene()
	{
        sandglass_param = 0.1;
        inertia_param = 1;		
		nb_temporal_iter = 0;
		overshooting_param = (FT)0.1;
		m_view_relocation = true;
		m_view_edges = true;
        m_view_sampling = false;
        m_sandglass = false;
		m_overshooting = false;
        m_inertia = false;
		m_cdt.add_box();
		this->update_domain();
		coefs_temporal.push_back(overshooting_param);
        /*for (int i = 0; i < inertia_param; i++)
		{
            coefs_temporal.push_back(FT(1.0/inertia_param));
            //coefs_temporal.push_back(FT(double(rand()) / double(RAND_MAX)));
            //std::cout << double(rand()) / double(RAND_MAX) << std::endl;
		}*/
	}

	~Scene()
	{
		clear();
	}    

    void toggle_view_inertia() { m_inertia = !m_inertia; }

    void toggle_view_overshooting() { m_overshooting = !m_overshooting; }

    void toggle_view_sandglass() { m_sandglass = !m_sandglass;  }

	void toggle_view_edges() { m_view_edges = !m_view_edges;  }

	void toggle_view_relocation() { m_view_relocation = !m_view_relocation;  }

    void toggle_view_sampling() { m_view_sampling = !m_view_sampling;  }

	void clear()
	{
		std::ofstream ofs;
		ofs.open("energies.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		std::ofstream ofs2;
		ofs2.open("length.txt", std::ofstream::out | std::ofstream::trunc);
		ofs2.close();
		energies.clear();
		points_alea.clear();
		average_length.clear();
        past_points.clear();
		m_dt.clear();
		m_dt_previous.clear();
		nb_temporal_iter = 0;
		prev_next.clear();
	}

	void add_vertex(const Point& p)
	{
		if (m_cdt.inside(p))
		{
			std::cout << p.x() << " " << p.y() << std::endl;
			m_dt.insert(p);
		}
			
		else
			std::cout << "outside point" << std::endl;
	}

	void set_mouse_pos(const Point& pos) {  m_mouse_pos = pos; }

	void load(const QString& filename)
	{
		if (filename.contains(".edg", Qt::CaseInsensitive))
		{
			m_dt.clear();
			m_dt_previous.clear();
			m_cdt.clear();
			m_cdt.read_pslg(qPrintable(filename));
			update_domain();
		}
	}

	void add_box()
	{
		average_length.clear();
		m_dt.clear();
		m_dt_previous.clear();
		m_cdt.clear();
		m_cdt.add_box();
		update_domain();
	}

	void add_circle()
	{
		average_length.clear();
		m_dt.clear();
		m_dt_previous.clear();
		m_cdt.clear();
		m_cdt.add_circle();
		update_domain();
	}

    void add_sandglass()
    {
        average_length.clear();
        m_dt.clear();
        m_dt_previous.clear();
        m_cdt.clear();
        m_cdt.add_sandglass(sandglass_param);
        update_domain();
    }


	void update_domain()
	{
		m_cdt.tag_faces_inside_outside();
		m_triangles.clear();
		m_cdt.inside_triangles(std::back_inserter(m_triangles));
	}

	void add_random_vertices(const int nb)
	{
		std::list<Point> points;
        m_cdt.generate_random_points(std::back_inserter(points), nb, m_sandglass, sandglass_param);
		m_dt.insert(points.begin(), points.end());
	}

	void render()
	{
		m_cdt.gl_draw_inside_faces(200,200,255);
	
		if (m_view_edges)
			m_cdt.gl_draw_constrained_edges(200, 0, 0);


		m_dt.draw_cvt_centroids_intersect(m_triangles.begin(), m_triangles.end());

		m_dt.gl_draw_generators(2.0f, 0, 0, 0);
		if (m_view_relocation)
		{
            //std::cout << "RELOCATION" << std::endl;
			m_dt_previous.gl_draw_generators(2.0f, 255, 0, 0);
			::glColor3ub(0, 0, 0);
			::glPointSize(2.0f);
			::glBegin(GL_LINES);
			for (std::vector< std::pair<Point, Point> >::iterator it = prev_next.begin();
				it != prev_next.end(); it++)
			{
				::glVertex2d(it->first.x(), it->first.y());
				::glVertex2d(it->second.x(), it->second.y());
			}
			::glEnd();
		}

		// Renders points used to generate energy
        if (m_view_sampling)
		{
            //std::cout << "SAMPLING" << std::endl;
			::glColor3ub(0, 0, 255);
			::glPointSize(1);
			::glBegin(GL_POINTS);
			for (std::vector<Point>::iterator it = points_alea.begin();
				it != points_alea.end();
				it++)
			{
				const Point& p = *it;
				::glVertex2f(p.x(), p.y());
			}
			::glEnd();
		}
	}


	void lloyd()
	{
		m_dt_previous = m_dt;
		energy();
		std::cout << "Energy of the cells : " << energies[0] << std::endl;
		std::cout << "Lloyd iteration...";
        const double av_len = m_dt.lloyd(m_triangles.begin(),
                                         m_triangles.end(),
                                         m_view_relocation,
                                         m_view_sampling,
                                         m_overshooting,
                                         overshooting_param,
                                         m_inertia,
                                         past_points,
                                         coefs_temporal,
                                         inertia_param,
										 nb_temporal_iter,
										 prev_next);
		std::ofstream log("length.txt", std::ios_base::app | std::ios_base::out);
		log << av_len << ", \n";
		average_length.push_back(av_len);
		std::cout << "done (average len: " << av_len << ")" << std::endl;
	}


	void energy()
	{
		points_alea.clear();
		energies.clear();
		std::vector<Point> points; // store centroids
		FT ener = (FT)0.0;

		typename Dt2::Finite_vertices_iterator v;
		for (v = m_dt.finite_vertices_begin();
			v != m_dt.finite_vertices_end();
			v++)
		{
			// compute clipped cells as triangles
			std::list<Triangle> triangles;
			m_dt.cvt_intersect(v, m_triangles.begin(), m_triangles.end(), std::back_inserter(triangles));

			// compute and store centroid
			const Point cc = m_dt.centroid_from_triangles(triangles.begin(), triangles.end());
			points.push_back(cc);
		}


		for (int i = 0; i < points.size(); i++)
		{
			energies.push_back(0);
		}

		std::vector<double> nb_alea_cell(points.size(), 0);

        int nb_points = 100000;
		for (int i = 0; i < nb_points; i++) 
		{
			double x = double(rand()) / double(RAND_MAX);
			double y = double(rand()) / double(RAND_MAX);
			Point pi(x, y);
			if (m_cdt.inside(pi))
			{
				points_alea.push_back(pi);
				FT lenmin = 10;
				int jmin = 0;
				FT len;
				for (int j = 0;
					j != points.size(); j++)
				{
					len = CGAL::squared_distance(points[j], pi);
					if (lenmin > len)
					{
						jmin = j;
						lenmin = len;
					}
				}
				energies[jmin] += lenmin;
				nb_alea_cell[jmin] ++;
			}
		}
		// returns average energy of Voronoi cells
		for (int i = 0; i < nb_alea_cell.size(); i++)
		{
			energies[i] /= nb_alea_cell[i];
		}

		std::ofstream log("energies.txt", std::ios_base::app | std::ios_base::out);
		for (int i = 0; i < nb_alea_cell.size(); i++)
		{
			log << energies[i] <<", ";
		}
		log << " \n";
	}

    void change_sandglass_param(double param_sandglass)
    {
        sandglass_param = param_sandglass;
    }

	void change_overshooting_param(double param_overshooting)
	{
		overshooting_param = param_overshooting;
	}

    void change_inertia_param(int param_inertia)
	{
        std::cout << inertia_param << " ; " << param_inertia << std::endl;
        if (inertia_param != param_inertia && param_inertia>1)
		{
            inertia_param = param_inertia;
			coefs_temporal.clear();
			double coef_i;
			for (int i = 0 ; i < inertia_param; i++)
			{
                std::cout << "Enter the coefficient " << i+1 << " : ";
				std::cin >> coef_i;
				coefs_temporal.push_back(FT(coef_i));
			}
			std::cout << "Initialization of coefficients done" << std::endl;
		}
        else
            inertia_param = param_inertia;
	}

    double get_sandglass_param() {
        return sandglass_param;
    }

	void plot_convergence() {}
	
};


#endif // _SCENE_H_
