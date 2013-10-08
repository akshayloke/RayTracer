#include "Material.h"

Material::Material() 
	: m_diffuse(ci::ColorA(1, 1, 1, 1)), 
	m_specular(ci::ColorA(1, 1, 1, 1)), 
	m_diffuseCoefficient(1), 
	m_specularCoefficient(1),
	m_reflectionCoefficient(0) {
}

Material::~Material() {
}