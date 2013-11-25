#pragma once

#include "cinder\Color.h"

class Material {
public:
	Material();
	virtual ~Material();

	void SetDiffuseColor(const cinder::ColorA& _diffuse)	{	m_diffuse = _diffuse;	}
	void SetSpecularColor(const cinder::ColorA& _specular)	{	m_specular = _specular;	}
	cinder::ColorA GetDiffuseColor()						{	return m_diffuse;		}
	cinder::ColorA GetSpecularColor()						{	return m_specular;		}

	void SetDiffuseCoefficient(const float _diffuseC)		{	m_diffuseCoefficient = _diffuseC;	}
	void SetSpecularCoefficient(const float _specularC)			{	m_specularCoefficient = _specularC;	}
	float GetDiffuseCoefficient()							{	return m_diffuseCoefficient;		}
	float GetSpecularCoefficient()							{	return m_specularCoefficient;		}

	void SetReflectionCoefficient(const float _reflectC)		{	m_reflectionCoefficient = _reflectC;	}
	float GetReflectionCoefficient()							{	return m_reflectionCoefficient;		}

	void SetRefractionCoefficient(const float _refractC)		{	m_refractionCoefficient = _refractC;	}
	float GetRefractionCoefficient()							{	return m_refractionCoefficient;		}
protected:

private:
	cinder::ColorA m_diffuse, m_specular;
	float m_diffuseCoefficient, m_specularCoefficient, m_reflectionCoefficient, m_refractionCoefficient;
};