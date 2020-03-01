#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <CGAL/basic.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Cartesian_converter.h>

//#include <CGAL/Delaunay_triangulation_euclidean_traits_2.h>

#include "console_color.h"

// a base vertex with attributes
template <class Vbb>
class Dvertex_base : public Vbb
{
public:
	typedef Vbb Vertex_base;
	typedef typename Vertex_base::Point Point;

private:

public:

public:
	Dvertex_base()
		: Vertex_base()
	{
	}
	Dvertex_base(const Point & p, void* f)
		: Vertex_base(p,f)
	{
	}
	Dvertex_base(const Point & p)
		: Vertex_base(p)
	{
	}
};


template <class Kernel, class TDS>
class MDT : public CGAL::Delaunay_triangulation_2<Kernel,TDS>
{
public:

	// typedefs for basic primitives
	typedef typename Kernel::FT FT;
	typedef typename Kernel::Ray_2      Ray;
	typedef typename Kernel::Line_2     Line;
	typedef typename Kernel::Point_2    Point;
	typedef typename Kernel::Vector_2   Vector;
	typedef typename Kernel::Segment_2  Segment;
	typedef typename Kernel::Triangle_2 Triangle;

	typedef typename CGAL::Delaunay_triangulation_2<Kernel,TDS> Dt2;

	// handles
	typedef typename Dt2::Face_handle         Face_handle;
	typedef typename Dt2::Vertex_handle       Vertex_handle;
	typedef typename Dt2::Edge       Edge;

	// iterators
	typedef typename Dt2::Face_iterator       Face_iterator;
	typedef typename Dt2::Edge_iterator       Edge_iterator;
	typedef typename Dt2::Finite_vertices_iterator Vertex_iterator; // 

	// circulators
	typedef typename Dt2::Edge_circulator      Edge_circulator;
	typedef typename Dt2::Vertex_circulator    Vertex_circulator;
	typedef typename Dt2::Face_circulator      Face_circulator;
	typedef typename Dt2::Line_face_circulator Line_face_circulator;


private:

public:
	MDT() 
	{
	}

	virtual ~MDT() 
	{
		Dt2::clear();
	}

public:

	// OPENGL DRAWINGS FUNCTIONS

	// draw generators
	void gl_draw_generators(const float point_size,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue)
	{
		::glColor3ub(red, green, blue);
		::glPointSize(point_size);

		::glBegin(GL_POINTS);
		typename Dt2::Point_iterator it;
		for(it = Dt2::points_begin(); 
			it != Dt2::points_end(); 
			it++)
		{
			const Point& p = *it;
			::glVertex2f(p.x(), p.y());
		}
		::glEnd();
	}

	// draw delaunay edges
	void gl_draw_delaunay_edges(const float line_width,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue)
	{
		::glColor3ub(red, green, blue);
		::glLineWidth(line_width);

		::glBegin(GL_LINES);
		Edge_iterator hEdge;
		for(hEdge  = Dt2::edges_begin(); 
			hEdge != Dt2::edges_end(); 
			hEdge++) 
		{
			const Point& p1 = (*hEdge).first->vertex(Dt2::ccw((*hEdge).second))->point();
			const Point& p2 = (*hEdge).first->vertex(Dt2::cw((*hEdge).second))->point();
			::glVertex2d(p1.x(), p1.y());
			::glVertex2d(p2.x(), p2.y());
		}
		::glEnd();
	}

	// compute centroid of triangles
	template <class InputIterator>
	Point centroid_from_triangles(InputIterator begin, InputIterator end)
	{
		FT sum_areas = 0.0;
		Vector vec = CGAL::NULL_VECTOR;
		for (InputIterator it = begin; it != end; it++)
		{
			Triangle& triangle = *it;
			const FT area = std::fabs(CGAL::to_double(triangle.area()));
			vec = vec + area * (CGAL::centroid(triangle) - CGAL::ORIGIN);
			sum_areas += area;
		}
		if (sum_areas > 0.0)
			return CGAL::ORIGIN + vec / sum_areas;
		else
			return CGAL::ORIGIN;
	}

	// Lloyd iteration
	// returns average length of relocation vectors
	template <class InputIterator>
	double lloyd(InputIterator begin, // inside triangles
		InputIterator end,
        bool m_view_relocation,
        bool m_view_sampling,
		bool overshooting,
		FT overshooting_param,
		bool temporal,
        std::vector< std::vector<Point> > & past_points,
        std::vector<FT> & coefs_temporal,
        int inertia_param,
		int & nb_temporal_iter,
		std::vector< std::pair<Point, Point> > & prev_next)
	{
		if (Dt2::dimension() != 2)
			return 0.0;

		std::vector<Point> points; // store centroids
        //std::map<Vertex_handle, int> vertex_to_id;
		prev_next.clear();

		FT sum_len = (FT)0.0;

        int nb_vertices_done = 0;
		int vertex_id = 0;
		typename Dt2::Finite_vertices_iterator v;
		for (v = Dt2::finite_vertices_begin();
			v != Dt2::finite_vertices_end();
			v++)
		{
			// compute clipped cells as triangles
			std::list<Triangle> triangles;
			this->cvt_intersect(v, begin, end, std::back_inserter(triangles));

			// compute and store centroid
			const Point cc = this->centroid_from_triangles(triangles.begin(), triangles.end());
			Point cci = cc;
			// overshooting
            if (overshooting && !temporal)
			{
                cci = cci + overshooting_param * (cc - v->point());
			}

            //	temporal
            else if (temporal) {
                if (past_points.empty()) {}
				if (past_points.size() == 1) 
				{
                    cci = cci + overshooting_param * (cc - past_points.at(0).at(vertex_id));
				}
                if (!past_points.empty() && past_points.size() > 1)
				{
					Vector moving_vector(0.0, 0.0);
                    moving_vector = moving_vector + coefs_temporal.at(0) * (cc - past_points.at(0).at(vertex_id));
					for (int i = 0; i < past_points.size() - 1; i++)
					{
                        moving_vector = moving_vector + coefs_temporal.at(i+1) * (past_points.at(i).at(vertex_id) - past_points.at(i+1).at(vertex_id));
					}

					if (overshooting) {
						moving_vector = (1 + overshooting_param) * moving_vector;
					}
					cci = cci + moving_vector;
                }
            }
			//
			prev_next.push_back(std::pair<Point, Point>(cci, v->point()));
            vertex_id++;

            //neither overshooting nor temporal
			points.push_back(cci);

			::glColor3ub(0, 0, 0);
			::glPointSize(2.0f);
			::glBegin(GL_LINES);
			::glVertex2d(v->point().x(), v->point().y());
			::glVertex2d(cci.x(), cci.y());
			::glEnd();

            nb_vertices_done+=1;

			// measure relocation distance
			const FT len = std::sqrt(CGAL::squared_distance(v->point(), cc));
			sum_len += len;

			// display relocation
			if (m_view_relocation)
			{
				::glBegin(GL_LINES);
				gl_vertex(cc);
				gl_vertex(v->point());
				::glEnd();
			}

			// append to list of centroids

		}

		// Save centroids' history.
		past_points.insert(past_points.begin(), points);
		nb_temporal_iter++;
		if (nb_temporal_iter > inertia_param)
		{
			past_points.pop_back();
			nb_temporal_iter--;
		}

		// clear generators and insert centroids
		this->clear();

		for (typename std::vector<Point>::iterator it = points.begin(); it != points.end(); it++)
			this->insert(*it);

		// returns average len of relocation vectors
		return (double)(sum_len / (FT)points.size());
	}

	double random_double(const double min, const double max)
	{
		double range = max - min;
		return min + (double(rand()) / double(RAND_MAX)) * range;
	}

	template <class InputIterator>
	void draw_cvt_centroids_intersect(InputIterator begin, // inside triangles
		InputIterator end)
	{
		if (Dt2::dimension() != 2)
			return;

		srand(0);

		typename Dt2::Finite_vertices_iterator v;
		for (v = Dt2::finite_vertices_begin();
			v != Dt2::finite_vertices_end();
			v++)
		{
			std::list<Triangle> triangles;
			this->cvt_intersect(v, begin, end, std::back_inserter(triangles));

			this->random_gl_color();

			if (triangles.empty())
				continue;

			typename std::list<Triangle>::iterator it;
			for (it = triangles.begin(); it != triangles.end(); it++)
				draw_triangle(*it);
		}
	}

	// draw triangle
	void draw_triangle(Triangle& triangle)
	{
		::glBegin(GL_TRIANGLES);
			this->gl_vertex(triangle[0]);
			this->gl_vertex(triangle[1]);
			this->gl_vertex(triangle[2]);
		::glEnd();
	}

	void gl_vertex(const Point& p)
	{
		::glVertex2d(p.x(), p.y());
	}

	template <class InputIterator, class OutputIterator>
	void cvt_intersect(Vertex_handle v,
		InputIterator begin, // inside triangles
		InputIterator end,
		OutputIterator out)
	{
		// get halfspaces of dual cell (as oriented lines)
		typename std::list<Line> lines;
		this->get_halfspace_from_dual(v, std::back_inserter(lines));
		this->do_cvt_intersect(begin, end, lines, out);
	}

	template <class InputIterator, class OutputIterator>
	void do_cvt_intersect(InputIterator begin, // inside triangles
		InputIterator end,
		std::list<Line>& lines,
		OutputIterator out)
	{
		InputIterator it;
		for (it = begin; it != end; it++) // for each triangle
		{
			// use stack as triangles may split
			std::stack<Triangle> triangles;
			triangles.push(*it);

			// iterate over half-planes
			typename std::list<Line>::iterator line_it;
			for (line_it = lines.begin(); line_it != lines.end(); line_it++)
			{
				Line& line = *line_it;

				// intersect triangles with current halfspace
				std::list<Triangle> split_triangles;
				while (!triangles.empty())
				{
					// pop triangle
					Triangle t = triangles.top();
					triangles.pop();

					this->clip_triangle(t, line, std::back_inserter(split_triangles));
				} // end while 

				// re-fill triangles, possibly split
				typename std::list<Triangle>::iterator split_it;
				for (split_it = split_triangles.begin(); split_it != split_triangles.end(); split_it++)
				{
					Triangle& triangle = *split_it;
					if (triangle.area() > 0.0)
						triangles.push(triangle);
				}

			} // end lines

			// add triangles that survived the intersection until the end
			while (!triangles.empty())
			{
				// pop triangle and add it to output
				Triangle t = triangles.top();
				triangles.pop();
				*out++ = t;
			}

		} // end for
	}

	// clip one triangle with halfplane
	// returns 0, one or 2 triangles in out
	template <class OutputIterator>
	void clip_triangle(Triangle& t, Line& line, OutputIterator out)
	{
		const Point& p0 = t.vertex(0);
		const Point& p1 = t.vertex(1);
		const Point& p2 = t.vertex(2);

		if (!CGAL::do_intersect(t, line))
		{
			if (line.has_on_positive_side(p0))
				*out++ = t; // entire triangle on good side
		}
		else
		{
			Segment s01(p0, p1);
			Segment s12(p1, p2);
			Segment s20(p2, p0);

			bool doi_s01 = CGAL::do_intersect(s01, line); // exact if EPIC kernel
			bool doi_s12 = CGAL::do_intersect(s12, line); // exact if EPIC kernel
			bool doi_s20 = CGAL::do_intersect(s20, line); // exact if EPIC kernel

			if (doi_s01 && doi_s12)
			{
				Point i01 = exact_intersection_point(s01, line);
				Point i12 = exact_intersection_point(s12, line);

				if (line.has_on_positive_side(p1))
					*out++ = Triangle(i01, p1, i12);
				else
				{
					*out++ = Triangle(i01, i12, p2);
					*out++ = Triangle(i01, p2, p0);
				}
			}
			else
			if (doi_s01 && doi_s20)
			{
				Point i01 = exact_intersection_point(s01, line);
				Point i20 = exact_intersection_point(s20, line);

				if (line.has_on_positive_side(p0))
					*out++ = Triangle(i01, i20, p0);
				else
				{
					*out++ = Triangle(i01, p1, p2);
					*out++ = Triangle(i01, p2, i20);
				}
			}
			else
			if (doi_s12 && doi_s20)
			{
				Point i12 = exact_intersection_point(s12, line);
				Point i20 = exact_intersection_point(s20, line);

				if (line.has_on_positive_side(p2))
					*out++ = Triangle(i20, i12, p2);
				else
				{
					*out++ = Triangle(i12, i20, p0);
					*out++ = Triangle(p0, p1, i12);
				}
			}
			else
				std::cerr << "invalid case in clip_triangle()" << std::endl;
		}
	}

	Point exact_intersection_point(Segment& segment, Line& line)
	{
		// functors required to conversion from exact 
		// to inexact and vice-versa

		// exact computation business
		typedef typename CGAL::Exact_predicates_exact_constructions_kernel EK;
		typedef typename CGAL::Cartesian_converter<Kernel, EK> IK_to_EK;
		typedef typename CGAL::Cartesian_converter<EK, Kernel> EK_to_IK;

		IK_to_EK to_exact;
		EK_to_IK to_inexact;

		EK::Intersect_2 intersection = EK().intersect_2_object();

		EK::Line_2 exact_line = to_exact(line);
		EK::Segment_2 exact_segment = to_exact(segment);

		CGAL::cpp11::result_of<EK::Intersect_2(EK::Line_2, EK::Segment_2)>::type
			v = intersection(exact_line, exact_segment); // variant

		if (v) // not empty
		{
			if (const EK::Point_2 *exact_point = boost::get<EK::Point_2>(&*v))
			{
				Point from_exact_point = to_inexact(*exact_point);
				return from_exact_point;
			}
			else
			{
				const EK::Segment_2 *exact_segment = boost::get<EK::Segment_2>(&*v);
				Segment seg = to_inexact(*exact_segment);
				return seg.source();
			}
		}
		else
			std::cout << red << " ** no intersection in exact_intersection_point** " <<
			white << std::endl;

		return segment.source();
	}




	// record all supporting (oriented) lines of primitives of 
	// dual Voronoi cell (segments, rays or lines)
	// return true if cell is bounded
	template <class OutputIterator>
	bool get_halfspace_from_dual(Vertex_handle v,
		OutputIterator out)
	{
		// get primitives of dual Voronoi cell of v (made of segments, lines or rays)
		typename Dt2::Edge_circulator circ = Dt2::incident_edges(v);
		typename Dt2::Edge_circulator end = circ;

		bool bounded = true;
		CGAL_For_all(circ, end)
		{
			Edge edge = *circ;
			if (this->is_infinite(edge))
				continue;

			CGAL::Object object = this->exact_edge_dual(edge, v);

			Segment segment;
			if (CGAL::assign(segment, object))
				*out++ = segment.supporting_line();
			else
			{
				Ray ray;
				if (CGAL::assign(ray, object))
				{
					*out++ = ray.supporting_line();
					bounded = false;
				}
				else
				{
					Line line;
					if (CGAL::assign(line, object))
					{
						*out++ = line;
						bounded = false;
					}
				}
			}
		}

		return bounded;
	}

	// computes the dual of edge, and make sure that the 
	// supporting lines of segment or ray or lines are
	// oriented consistently.
	CGAL::Object exact_edge_dual(Edge& edge,
		Vertex_handle v)
	{
		const Point& p = v->point();
		Vertex_handle v1 = edge.first->vertex(this->cw(edge.second));
		Vertex_handle v2 = edge.first->vertex(this->ccw(edge.second));

		// pick adjacent point
		const Point& n = (v1 == v) ? v2->point() : v1->point();
		Vector pn = n - p;
		Vector pn90(-pn.y(), pn.x()); // rotate 90

		Face_handle f = edge.first;
		Face_handle nf = f->neighbor(edge.second);

		bool finite_f = !this->is_infinite(f);
		bool finite_nf = !this->is_infinite(nf);

		if (finite_f && finite_nf)
		{ // dual is a segment
			Point source = this->exact_face_dual(f);
			Point target = this->exact_face_dual(nf);
			Segment segment(source, target);
			return CGAL::make_object(segment);
		}

		if (finite_f)
		{ // dual is a ray
			Point source = this->exact_face_dual(f);
			return CGAL::make_object(Ray(source, pn90));
		}

		if (finite_nf)
		{ // dual is a ray
			Point source = this->exact_face_dual(nf);
			return CGAL::make_object(Ray(source, pn90));
		}

		// dual is a line -> INEXACT
		return this->dual(edge);
	}

	Point exact_face_dual(Face_handle f)
	{
		// exact computation business
		typedef typename CGAL::Exact_predicates_exact_constructions_kernel EK;
		// typedef CGAL::Delaunay_triangulation_euclidean_traits_2<EK2> EK;

		typedef typename CGAL::Cartesian_converter<Kernel, EK> IK_to_EK;
		typedef typename CGAL::Cartesian_converter<EK, Kernel> EK_to_IK;

		IK_to_EK to_exact;
		EK_to_IK to_inexact;

		EK::Construct_circumcenter_2 exact_circumcenter =
			EK().construct_circumcenter_2_object();

		// get point
		const Point& p0 = f->vertex(0)->point();
		const Point& p1 = f->vertex(1)->point();
		const Point& p2 = f->vertex(2)->point();

		typedef typename EK::Point_2 Exact_point;
		Exact_point ep0 = to_exact(p0);
		Exact_point ep1 = to_exact(p1);
		Exact_point ep2 = to_exact(p2);

		return to_inexact(exact_circumcenter(ep0, ep1, ep2));
	}

	void random_gl_color()
	{
		const double r = random_double(0.5, 1.0);
		const double g = random_double(0.5, 1.0);
		const double b = random_double(0.5, 1.0);
		::glColor3d(r, g, b);
	}


};

#endif // TRIANGULATION_H
