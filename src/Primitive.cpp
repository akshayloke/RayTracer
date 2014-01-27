#include "Primitive.h"

Primitive::Primitive() 
	: m_name(""), m_isLight(false), m_material() {
}

Primitive::~Primitive() {

}

void Primitive::AddParams(ci::params::InterfaceGlRef _params) {
	_params->addParam(m_name + "::IsLight", &m_isLight, "group=" + m_name + " label='IsLight'");
	m_material.AddParams(_params, m_name);
}