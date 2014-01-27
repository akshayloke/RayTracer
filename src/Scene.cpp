#include "Scene.h"
#include "PlanePrimitive.h"
#include "SpherePrimitive.h"
#include "Material.h"
#include "cinder\gl\Light.h"
#include "cinder\Surface.h"
#include "cinder\app\App.h"

using namespace ci;

Scene::Scene(const CameraPersp* _cam) : 
	m_camera(_cam) {
}

Scene::~Scene() {
}

void Scene::Setup(params::InterfaceGlRef _params) {
	Primitive* primitive;
	float planeDist = 25;
	//ground plane
	primitive = new PlanePrimitive(ci::Vec3f(0, -planeDist, 0), ci::Vec3f(0, 1, 0));
	primitive->SetName("GroundPlane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(1.0f, 0.2f, 0.2f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);
	//top plane
	primitive = new PlanePrimitive(ci::Vec3f(0, planeDist, 0), ci::Vec3f(0, -1, 0));
	primitive->SetName("TopPlane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.2f, 1.0f, 0.2f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);

	//side plane
	primitive = new PlanePrimitive(ci::Vec3f(planeDist, 0, 0), ci::Vec3f(-1, 0, 0));
	primitive->SetName("RightPlane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.2f, 0.2f, 1.0f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);
	//side plane
	primitive = new PlanePrimitive(ci::Vec3f(-planeDist, 0, 0), ci::Vec3f(1, 0, 0));
	primitive->SetName("LeftPlane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(1.0f, 1.0f, 0.2f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);

	//side plane
	primitive = new PlanePrimitive(ci::Vec3f(0, 0, planeDist), ci::Vec3f(0, 0, -1));
	primitive->SetName("FrontPlane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(1.0f, 0.2f, 1.0f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);
	//side plane
	primitive = new PlanePrimitive(ci::Vec3f(0, 0, -planeDist), ci::Vec3f(0, 0, 1));
	primitive->SetName("BackPlane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.2f, 1.0f, 1.0f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);


	//big sphere
	primitive = new SpherePrimitive(ci::Vec3f(5, 7, 0), 7);
	primitive->SetName("BigSphere");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	primitive->GetMaterial().SetReflectionCoefficient(0.0f);
	primitive->GetMaterial().SetRefractionCoefficient(1.1f);
	m_primitives.push_back(primitive);
	//small sphere
	primitive = new SpherePrimitive(ci::Vec3f(-5, -5, -10), 5);
	primitive->SetName("SmallSphere");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.5f, 0.1f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	primitive->GetMaterial().SetReflectionCoefficient(0.1f);
	primitive->GetMaterial().SetRefractionCoefficient(0.0f);
	m_primitives.push_back(primitive);
	//light1
	primitive = new SpherePrimitive(ci::Vec3f(10, 24, 0), 2);
	primitive->SetName("Light1");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->SetIsLight(true);
	m_primitives.push_back(primitive);
	////light2
	/*primitive = new SpherePrimitive(ci::Vec3f(-10, 10, -10), 1);
	primitive->SetName("Light 2");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.7f, 0.7f, 0.7f));
	primitive->SetIsLight(true);
	m_primitives.push_back(primitive);*/

	for (int i=0; i<m_primitives.size(); i++)
		m_primitives[i]->AddParams(_params);	
}

void Scene::RenderGL() {
	gl::Light light( gl::Light::DIRECTIONAL, 0 );
	light.setDirection( Vec3f( 1, 1, 1 ).normalized() );
	light.update( *m_camera );
	light.setDiffuse(ci::ColorAf(0, 1, 0));
	light.enable();

	glColor3f( 1, 1, 1 );
	for (int i=0; i<m_primitives.size(); i++) {
		m_primitives[i]->RenderGL();
	}

	light.disable();
}

void Scene::Render(ci::Surface8u *surface) {
	Surface8u::Iter iter = surface->getIter();
	int width = surface->getWidth();
	int height = surface->getHeight();
	float aspectRatio = width / (float)height;
	Color8u bgColor(25, 25, 25);
	while (iter.line()) {
		while (iter.pixel()) {
			ColorA aaColor(0, 0, 0);
			int count = 0;
			int numSamples = 4;
			float deltaX = 1.0f / (width * numSamples);
			float deltaY = 1.0f / (height * numSamples);

			for (int i = 0; i < numSamples; i++) {
				for (int j = 0; j < numSamples; j++) {
					float inDist = 10000.0f;
					float u = iter.x()/(float)width + deltaX * i;
					float v = iter.y()/(float)height + deltaY * j;
					ci::Ray ray = m_camera->generateRay(u, v, aspectRatio);
					aaColor += Raytrace(ray, 0, inDist, 1.0f);
					count++;
				}
			}

			ColorA color = aaColor / (float)count;

			iter.r() = ci::math<float>::clamp(bgColor.r * (1.0f - color.a) + color.r * 255.0f, 0.0f, 255.0f);
			iter.g() = ci::math<float>::clamp(bgColor.g * (1.0f - color.a) + color.g * 255.0f, 0.0f, 255.0f);
			iter.b() = ci::math<float>::clamp(bgColor.b * (1.0f - color.a) + color.b * 255.0f, 0.0f, 255.0f);
		}
		//iter.line();
	}
}

ci::ColorA Scene::Raytrace(const ci::Ray& inRay, int inDepth, float& inDist, const float inRefractIndex) {
	if (inDepth > 3)
		return ci::ColorA::black();

	Primitive* hitPrim = NULL;
	Primitive::E_INTERSECT_RESULT result;
	float currentInDist = inDist;
	for (int i=0; i<m_primitives.size(); i++) {
		Primitive* prim = m_primitives[i];
		Primitive::E_INTERSECT_RESULT res = prim->Intersect(inRay, inDist);
		if (res != Primitive::MISS) {
			if (inDist <= currentInDist) {
				hitPrim = prim;
				result = res;
			}
		}
	}

	if (!hitPrim)
		return ci::ColorA::black();

	if (hitPrim->IsLight()) 
		return hitPrim->GetMaterial().GetDiffuseColor();
	else {
		ci::Vec3f hitPoint = inRay.getOrigin() + inRay.getDirection() * inDist;
		ci::ColorA accumColor(0, 0, 0, 0);
		{//shading
			for (int i=0; i<m_primitives.size(); i++) {
				Primitive* prim = m_primitives[i];
				if (prim->IsLight()) {
					Primitive* light = prim;
					//shadow feeler
					float shade = 1.0f;
					//get shadow feeler ray in direction of light
					ci::Vec3f L = (((SpherePrimitive*)light)->getCenter() - hitPoint).normalized();
					float lightToHitPointDist = (((SpherePrimitive*)light)->getCenter() - hitPoint).length();
					ci::Ray shadowFeelerRay(hitPoint + L * ci::EPSILON_VALUE, L);
					float LDist = 1000.0f;
					for (int j = 0; j<m_primitives.size(); j++) {
						Primitive* primJ = m_primitives[j];
						if (primJ->IsLight())
							break;
						else {
							Primitive::E_INTERSECT_RESULT result = primJ->Intersect(shadowFeelerRay, LDist);
							if (result == Primitive::HIT && LDist <= lightToHitPointDist) {
								shade = 0.0f;
								break;
							}
						}
					}

					ci::Vec3f N = hitPrim->GetNormal(hitPoint);
					float dotLN = L.dot(N);
					ci::Vec3f R = (L - 2.0f * dotLN * N).normalized();
					ci::Vec3f V = inRay.getDirection().normalized();
					if (dotLN > 0) {
						//calculate diffuse component
						float diffuseC = dotLN * hitPrim->GetMaterial().GetDiffuseCoefficient();
						accumColor += diffuseC 
										* hitPrim->GetMaterial().GetDiffuseColor() 
										* light->GetMaterial().GetDiffuseColor()
										* shade;

						float dotVR = V.dot(R);
						if (dotVR > 0) {
							//calculate specular component
							float specularC = ci::math<float>::pow(dotVR, 20) * hitPrim->GetMaterial().GetSpecularCoefficient();
							accumColor += specularC 
											* hitPrim->GetMaterial().GetSpecularColor() 
											* light->GetMaterial().GetDiffuseColor() 
											* shade;
						}
					}
				}
			}
		}

		{//reflection
			if (hitPrim->GetMaterial().GetReflectionCoefficient() > 0.0f) {
				ci::Vec3f N = hitPrim->GetNormal(hitPoint);
				ci::Vec3f V = inRay.getDirection().normalized();
				float dotVN = V.dot(N);
				ci::Vec3f R = (V - 2.0f * dotVN * N).normalized();
				float reflectDist = 10000.0f;
				ci::ColorA reflectedColor = Raytrace(ci::Ray(hitPoint + R * ci::EPSILON_VALUE * 2, R), inDepth + 1, reflectDist, inRefractIndex);
				accumColor += reflectedColor * hitPrim->GetMaterial().GetDiffuseColor() * hitPrim->GetMaterial().GetReflectionCoefficient();
			}
		}

		{//refraction
			if (hitPrim->GetMaterial().GetRefractionCoefficient() > 0.0f) {
				float refractIndex = hitPrim->GetMaterial().GetRefractionCoefficient();
				float n = inRefractIndex / refractIndex;
				ci::Vec3f N = hitPrim->GetNormal(hitPoint) * (int)result;
				float cosI = N.dot(inRay.getDirection());
				//float I = acos(cosI);
				float cosT2 = 1.0f - n * n * (1.0f - cosI * cosI);
				//float sinT2 = n * n * (1.0f - cosI * cosI);
				if (cosT2 >= 0.0f) {
				//if (sinT2 <= 1.0f) {
					//Vec3f T = ((n * inRay.getDirection()) - (n + sqrtf(1 - sinT2)) * N).normalized();
					float cosT = sqrtf(cosT2);
					Vec3f T = ((n * inRay.getDirection()) - (n * cosI + sqrtf(cosT2)) * N).normalized();
					float refractDist = 10000.0f;
					ci::ColorA refractedColor = Raytrace(ci::Ray(hitPoint + T * ci::EPSILON_VALUE * 1, T), inDepth + 1, refractDist, refractIndex);
					accumColor += refractedColor * hitPrim->GetMaterial().GetDiffuseColor() * hitPrim->GetMaterial().GetRefractionCoefficient();
				}
			}
		}

		{//diffuse reflection - for color bleeding, ambient occlusion
		}

		{//soft shadows
		}

		{//anti-aliasing my multi-sampling
		}

		return accumColor;
	}
}