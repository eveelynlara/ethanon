#include "ETHEntityPieceRenderer.h"

ETHEntityPieceRenderer::ETHEntityPieceRenderer(ETHRenderEntity* entity) :
	m_entity(entity)
{
	m_entity->BREAK_ON_REF_CHANGE = false;
	m_entity->AddRef();
	m_entity->BREAK_ON_REF_CHANGE = true;
}

ETHEntityPieceRenderer::~ETHEntityPieceRenderer()
{
	m_entity->BREAK_ON_REF_CHANGE = false;
	m_entity->Release();
	m_entity->BREAK_ON_REF_CHANGE = true;
}

ETHRenderEntity* ETHEntityPieceRenderer::GetEntity()
{
	return m_entity;
}
