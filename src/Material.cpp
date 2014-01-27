#include "Material.h"

Material::Material() 
	: m_diffuse(ci::ColorA(1, 1, 1, 1)), 
	m_specular(ci::ColorA(1, 1, 1, 1)), 
	m_diffuseCoefficient(1), 
	m_specularCoefficient(1),
	m_reflectionCoefficient(0),
	m_refractionCoefficient(0) {
}

Material::~Material() {
}

void Material::AddParams(ci::params::InterfaceGlRef _params, std::string name) {
	_params->addParam(name + "::DiffuseColor", &m_diffuse, "group=" + name + " label='DiffuseColor'");
	_params->addParam(name + "::DiffuseCoeff", &m_diffuseCoefficient, "group=" + name + " label='DiffuseCoeff'");
	_params->addParam(name + "::SpecularColor", &m_specular, "group=" + name + " label='SpecularColor'");
	_params->addParam(name + "::SpecularCoeff", &m_specularCoefficient, "group=" + name + " label='SpecularCoeff'");
	_params->addParam(name + "::ReflectionCoeff", &m_reflectionCoefficient, "group=" + name + " label='ReflectionCoeff'");
	_params->addParam(name + "::RefractionCoeff", &m_refractionCoefficient, "group=" + name + " label='RefractionCoeff'");
}