#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RayTracerApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void RayTracerApp::setup()
{
	
}

void RayTracerApp::mouseDown( MouseEvent event )
{
}

void RayTracerApp::update()
{
}

void RayTracerApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( RayTracerApp, RendererGl )
