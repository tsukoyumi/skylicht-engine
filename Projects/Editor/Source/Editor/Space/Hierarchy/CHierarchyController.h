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

#include "GUI/GUI.h"
#include "CHierachyNode.h"
#include "Editor/CEditor.h"

namespace Skylicht
{
	namespace Editor
	{
		class CHierarchyController
		{
		protected:
			CEditor* m_editor;
			GUI::CCanvas* m_canvas;
			GUI::CTreeControl* m_tree;

			CHierachyNode* m_node;

			GUI::CTreeNode* m_renameNode;

		public:
			CHierarchyController(GUI::CCanvas* canvas, GUI::CTreeControl* tree, CEditor* editor);

			virtual ~CHierarchyController();

			void deleteHierarchyNode();

			void setHierarchyNode(CHierachyNode* node);

			GUI::CTreeNode* add(CHierachyNode* node);

			void rename(GUI::CTreeNode* node);

		protected:

			void OnKeyPress(GUI::CBase* control, int key, bool press);

			void OnRename(GUI::CBase* control);

			void OnCancelRename(GUI::CBase* control);

			void OnSelectChange(GUI::CBase* control);

			GUI::CTreeNode* buildHierarchyNode(GUI::CTreeNode* parentGuiNode, CHierachyNode* node);

			void initDragDrop(GUI::CTreeNode* guiNode, CHierachyNode* node);

			void move(CHierachyNode* from, CHierachyNode* target, bool behind);

			void moveToChild(CHierachyNode* from, CHierachyNode* target);

			CHierachyNode* createObjectAt(CHierachyNode* position, bool behind);

			CHierachyNode* createChildObject(CHierachyNode* parent);
		};
	}
}