/*
 * GLCanvas.h
 *
 *   Created on: Mar 18, 2010
 *       Author: nikai
 *  Description: an OpenGL canvas
 */

#pragma once

#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <QGLWidget>

namespace sfmviewer {

	// the data structure for the view port
	struct ViewPort {
		float m_shift[3];  // translation
		float m_quat[4];   // orientation in quaternion format
		ViewPort() {}
		ViewPort(float x, float y, float z, float q1, float q2, float q3, float q4) {
			m_shift[0] = x; m_shift[1] = y; m_shift[2] = z;
			m_quat[0] = q1; m_quat[1] = q2; m_quat[2] = q3; m_quat[3] = q4;
		}
	};

	class GLCanvas : public QGLWidget
	{
		Q_OBJECT

	public:

		// callback function types
		typedef boost::function<void (GLCanvas&)> Callback;

		// constructor
		GLCanvas(QWidget *parent = 0);

		// destructor
		~GLCanvas();

		// return the minimal size of the window
		QSize minimumSizeHint() const;

		// Used by windowing system, uses globals set by size
		QSize sizeHint() const;

		// Called from window.cpp to set default size
		void setSizeHint(int w, int h);

		// set up users' callback functions
		void setCallback(const Callback& fun_draw) { fun_draw_ = fun_draw; }

		void setViewPort(const ViewPort& port) { viewPort_ = port; }

	protected:
		// intialize the opengl canvas
		void initializeGL();

		// paint function
		void paintGL();

		// callback when the window is resized
		void resizeGL(int width, int height);

		// record the last mouse position
		void mousePressEvent(QMouseEvent *event);

		// mouse click and drag
		void mouseMoveEvent(QMouseEvent *event);

		// record the last mouse position
		void mouseReleaseEvent(QMouseEvent *event);

		// create actions for events
		void createActions();

		// context menu event
		void contextMenuEvent(QContextMenuEvent *event);

	private slots:

		// change the speed of mouse operations
		void changeMouseSpeed();

	private:
		QPoint lastPos_;

		int hintWidth_;
		int hintHeight_;

		// the current opengl viewport
		ViewPort viewPort_;

		// the pointers of callback functions
		Callback fun_draw_;

		QAction* changeMouseSpeedAct;
	};
} // namespace sfmviewer