#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Light.h"
#include "cinder/gl/Texture.h"
#include "cinder/MayaCamUI.h"
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
};

void RayTracerApp::prepareSettings( Settings* settings ) {
	settings->setWindowSize(400, 300);
}

void RayTracerApp::setup()
{
	CameraPersp cam;
	Vec3f startEyePoint(25, 25, 25);
	cam.lookAt(startEyePoint, Vec3f::zero(), Vec3f::yAxis());
	cam.setCenterOfInterest(startEyePoint.distance(Vec3f::zero()));
	m_mayaCam.setCurrentCam(cam);

	m_imageSurface = std::shared_ptr<Surface8u>(new Surface8u(getWindowWidth(), getWindowHeight(), false));
	m_imageTexture = gl::Texture(*m_imageSurface);
	m_scene.Setup();
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
	
	//gl::setMatricesWindow(getWindowSize()); //sets to ortho
}

CINDER_APP_NATIVE( RayTracerApp, RendererGl )
