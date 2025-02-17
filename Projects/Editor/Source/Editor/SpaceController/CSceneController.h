/*
!@
MIT License

Copyright (c) 2021 Skylicht Technology CO., LTD

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction, including without limitation the Rights to use, copy, modify,
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

#pragma once

#include "Utils/CGameSingleton.h"

#include "Scene/CScene.h"

#include "Editor/Space/Scene/CSpaceScene.h"
#include "Editor/Space/Hierarchy/CSpaceHierarchy.h"
#include "Editor/Space/Hierarchy/CHierachyNode.h"

#include "Editor/Gizmos/CGizmos.h"
#include "EditorComponents/SelectObject/CSelectObjectSystem.h"

#include "CContextMenuScene.h"

#include "Reactive/CObserver.h"
#include "Reactive/CSubject.h"

#include "Editor/Gizmos/Transform/CTransformGizmos.h"

namespace Skylicht
{
	namespace Editor
	{
		class CSceneController :
			public CGameSingleton<CSceneController>,
			public IObserver,
			public IFileLoader
		{
		protected:
			CSpaceScene* m_spaceScene;

			CSpaceHierarchy* m_spaceHierarchy;

			CHierachyNode* m_hierachyNode;

			CHierachyNode* m_contextNode;

			CHierachyNode* m_focusNode;

			CScene* m_scene;

			CZone* m_zone;

			CSceneHistory* m_history;

			GUI::CCanvas* m_canvas;

			CContextMenuScene* m_contextMenuScene;

			std::vector<CGizmos*> m_gizmos;

			CTransformGizmos* m_transformGizmos;

			std::string m_scenePath;

			bool m_modify;

		public:
			CSceneController();

			virtual ~CSceneController();

			void update();

			void refresh();

			inline CTransformGizmos* getTransformGizmos()
			{
				return m_transformGizmos;
			}

			void addGizmos(CGizmos* gizmos);

			void removeGizmos(CGizmos* gizmos);

			void initContextMenu(GUI::CCanvas* canvas);

			void setSpaceScene(CSpaceScene* scene);

			inline CSpaceScene* getSpaceScene()
			{
				return m_spaceScene;
			}

			CSelectObjectSystem* getSelectObjectSystem()
			{
				return m_spaceScene->getSelectObjectSystem();
			}

			void setSpaceHierarchy(CSpaceHierarchy* hierarchy);

			inline CSpaceHierarchy* getSpaceHierarchy()
			{
				return m_spaceHierarchy;
			}

			inline void modify()
			{
				m_modify = true;
			}

			bool needSave();

			void save(const char* path);

			virtual void loadFile(const std::string& path);

			void doLoadScene(const std::string& path);

			void doFinishLoadScene();

			const std::string& getScenePath()
			{
				return m_scenePath;
			}

			void setScene(CScene* scene);

			inline CScene* getScene()
			{
				return m_scene;
			}

			void setZone(CZone* zone);

			CZone* getZone()
			{
				return m_zone;
			}

			CSceneHistory* getHistory()
			{
				return m_history;
			}

			void buildHierarchyNodes();

			void onCommand(const std::wstring& objectType);

			void onContextMenu(CHierachyNode* node);

			void onUpdateNode(CHierachyNode* node);

			void onSelectNode(CHierachyNode* node, bool selected);

			void onObjectChange(CGameObject* object);

			virtual void onNotify(ISubject* subject, IObserver* from);

			void deselectAllOnHierachy();

			CHierachyNode* deselectOnHierachy(CGameObject* gameObject);

			CHierachyNode* selectOnHierachy(CGameObject* gameObject);

			inline CHierachyNode* getContextNode()
			{
				return m_contextNode;
			}

			inline void clearContextNode()
			{
				m_contextNode = NULL;
			}

			void createZone();

			CGameObject* createEmptyObject(CContainerObject* parent);

			CGameObject* createContainerObject(CContainerObject* parent);

			void createResourceComponent(const std::string& path, CGameObject* gameObject);

		protected:

			CHierachyNode* buildHierarchyNodes(CGameObject* object, CHierachyNode* parentNode);

			void setNodeEvent(CHierachyNode* node);
		};
	}
}