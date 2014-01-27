#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Light.h"
#include "cinder/gl/Texture.h"
#include "cinder/MayaCamUI.h"
#include "cinder/params/Params.h"
#include "Scene.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RayTracerApp : public AppNative {
  public:
	RayTracerApp() : m_scene(&m_mayaCam.getCamera())  {}

	void prepareSettings( Settings* settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void mouseDrag( MouseEvent event );	
	void update();
	void draw();

	MayaCamUI m_mayaCam;
	Scene	m_scene;
	std::shared_ptr<Surface8u> m_imageSurface;
	gl::Texture m_imageTexture;

	params::InterfaceGlRef	m_params;
};

void RayTracerApp::prepareSettings( Settings* settings ) {
	settings->setWindowSize(800, 800);
}

void RayTracerApp::setup()
{
	CameraPersp cam;
	Vec3f startEyePoint(0, 0, 25);
	cam.lookAt(startEyePoint, Vec3f::zero(), Vec3f::yAxis());
	cam.setCenterOfInterest(startEyePoint.distance(Vec3f::zero()));
	cam.setFov(75);
	m_mayaCam.setCurrentCam(cam);

	m_params = ci::params::InterfaceGl::create("RayTracer", Vec2i(200, 200));
	m_params->addText("Hello there");
	m_params->addSeparator();

	m_imageSurface = std::shared_ptr<Surface8u>(new Surface8u(getWindowWidth(), getWindowHeight(), false));
	m_imageTexture = gl::Texture(*m_imageSurface);
	m_scene.Setup(m_params);
}

void RayTracerApp::mouseDown( MouseEvent event )
{
	m_mayaCam.mouseDown(event.getPos());
}

void RayTracerApp::mouseDrag( MouseEvent event )
{
	m_mayaCam.mouseDrag(event.getPos(), event.isLeftDown(), event.isMiddleDown(), event.isRightDown());
}

void RayTracerApp::update()
{
	m_scene.Render(m_imageSurface.get());
	m_imageTexture.update(*m_imageSurface);
}

void RayTracerApp::draw()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
	glDisable(GL_TEXTURE_2D);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	gl::setMatrices(m_mayaCam.getCamera());
	//render sceneGL
	m_scene.RenderGL();

	gl::setMatricesWindow( getWindowSize() );//set to ortho

	// draw as much of the texture as we've rendered
	glDisable( GL_LIGHTING );
	glDepthMask( GL_TRUE );
	glDisable( GL_DEPTH_TEST );
	
	glColor3f( 1, 1, 1 );
	m_imageTexture.enableAndBind();
	glBegin( GL_QUADS );
		glTexCoord2f( m_imageTexture.getLeft(), m_imageTexture.getBottom() );
		glVertex2f( 0, 0 );

		glTexCoord2f( m_imageTexture.getLeft(), m_imageTexture.getTop() );
		glVertex2f( 0, m_imageTexture.getHeight() );

		glTexCoord2f( m_imageTexture.getRight(), m_imageTexture.getTop() );
		glVertex2f( m_imageTexture.getWidth(), m_imageTexture.getHeight() );

		glTexCoord2f( m_imageTexture.getRight(), m_imageTexture.getBottom() );
		glVertex2f( m_imageTexture.getWidth(), 0 );
	glEnd();

	m_params->draw();
}

CINDER_APP_NATIVE( RayTracerApp, RendererGl )