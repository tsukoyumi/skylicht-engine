/*
!@
MIT License

Copyright (c) 2019 Skylicht Technology CO., LTD

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This file is part of the "Skylicht Engine".
https://github.com/skylicht-lab/skylicht-engine
!#
*/

#include "pch.h"
#include "CMeshRenderer.h"

#include "Culling/CCullingData.h"
#include "Entity/CEntityManager.h"

#include "Material/Shader/ShaderCallback/CShaderSH.h"

namespace Skylicht
{
	CMeshRenderer::CMeshRenderer()
	{
		m_pipelineType = IRenderPipeline::Mix;
	}

	CMeshRenderer::~CMeshRenderer()
	{

	}

	void CMeshRenderer::beginQuery(CEntityManager* entityManager)
	{
		m_meshs.set_used(0);
		m_transforms.set_used(0);
		m_indirectLightings.set_used(0);
	}

	void CMeshRenderer::onQuery(CEntityManager *entityManager, CEntity *entity)
	{
		CRenderMeshData *meshData = entity->getData<CRenderMeshData>();
		if (meshData != NULL)
		{
			if (meshData->getMesh() == NULL)
				return;

			// do not render gpu skinning, pass for CSkinMeshRenderer
			if (meshData->isSkinnedMesh() == true && meshData->isSoftwareSkinning() == false)
				return;

			bool cullingVisible = true;

			// get culling result from CCullingSystem
			CCullingData *cullingData = entity->getData<CCullingData>();
			if (cullingData != NULL)
				cullingVisible = cullingData->Visible;

			// only render visible culling mesh
			if (cullingVisible == true)
			{
				CWorldTransformData *transform = entity->getData<CWorldTransformData>();
				CIndirectLightingData *indirect = entity->getData<CIndirectLightingData>();

				if (transform != NULL)
				{
					m_meshs.push_back(meshData);
					m_transforms.push_back(transform);
					m_indirectLightings.push_back(indirect);
				}
			}
		}
	}

	void CMeshRenderer::init(CEntityManager *entityManager)
	{

	}

	void CMeshRenderer::update(CEntityManager *entityManager)
	{

	}

	void CMeshRenderer::render(CEntityManager *entityManager)
	{
		IVideoDriver *driver = getVideoDriver();

		CRenderMeshData** meshs = m_meshs.pointer();
		CWorldTransformData** transforms = m_transforms.pointer();
		CIndirectLightingData** indirectLighting = m_indirectLightings.pointer();

		IRenderPipeline *rp = entityManager->getRenderPipeline();

		for (u32 i = 0, n = m_meshs.size(); i < n; i++)
		{
			CRenderMeshData *meshData = m_meshs[i];
			CMesh *mesh = meshData->getMesh();

			CIndirectLightingData *lightingData = indirectLighting[i];
			if (lightingData != NULL)
			{
				if (lightingData->Type == CIndirectLightingData::SH9)
					CShaderSH::setSH9(lightingData->SH);
				else if (lightingData->Type == CIndirectLightingData::SH4)
					CShaderSH::setSH4(lightingData->SH);
			}

			driver->setTransform(video::ETS_WORLD, transforms[i]->World);

			for (u32 j = 0, m = mesh->getMeshBufferCount(); j < m; j++)
				rp->drawMeshBuffer(mesh, j, entityManager, meshData->EntityIndex);
		}
	}
}