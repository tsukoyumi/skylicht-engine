#include "pch.h"
#include "CEntityPrefab.h"
#include "Transform/CWorldTransformData.h"

namespace Skylicht
{
	CEntityPrefab::CEntityPrefab()
	{

	}

	CEntityPrefab::~CEntityPrefab()
	{
		releaseAllEntities();
	}

	CEntity* CEntityPrefab::createEntity()
	{
		CEntity *entity = new CEntity(this);
		m_entities.push_back(entity);
		return entity;
	}

	void CEntityPrefab::releaseAllEntities()
	{
		CEntity** entities = m_entities.pointer();
		for (u32 i = 0, n = m_entities.size(); i < n; i++)
		{
			delete entities[i];
			entities[i] = NULL;
		}

		m_entities.set_used(0);
	}

	void CEntityPrefab::addTransformData(CEntity* entity, CEntity* parent, const core::matrix4& transform, const char *name)
	{
		CWorldTransformData *transformData = entity->addData<CWorldTransformData>();
		transformData->Relative = transform;
		transformData->Name = name;

		// add parent relative
		if (parent != NULL)
		{
			transformData->ParentIndex = parent->getIndex();
			transformData->Depth = parent->getData<CWorldTransformData>()->Depth + 1;
		}
	}
}