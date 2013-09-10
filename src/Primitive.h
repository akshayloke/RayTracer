#pragma once

#include "cinder\Vector.h"
#include "cinder\Ray.h"

#include "Material.h"

class Primitive {
public:
	Primitive();
	virtual ~Primitive();

	enum E_INTERSECT_RESULT {
		MISS, HIT, HIT_INSIDE
	};
	virtual E_INTERSECT_RESULT Intersect(const cinder::Ray& inRay, const float& inDist) {
		return MISS;
	}
	virtual ci::Vec3f GetNormal(const ci::Vec3f& inPoint) {
		return ci::Vec3f(0, 1, 0);
	}
	
	void SetName(const std::string& _name) {
		m_name= _name;
	}
	std::string GetName() {
		return m_name;
	}

	void SetIsLight(bool _isLight) {
		m_isLight = _isLight;
	}
	bool IsLight() {
		return m_isLight;
	}

	void SetMaterial(const Material& _material) {
		m_material = _material;
	}
	Material GetMaterial() {
		return m_material;
	}

protected:

private:
	std::string m_name;
	bool m_isLight;
	Material m_material;
};