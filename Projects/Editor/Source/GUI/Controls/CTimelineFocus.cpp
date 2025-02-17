/*
!@
MIT License

Copyright (c) 2020 Skylicht Technology CO., LTD

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
#include "CTimelineFocus.h"
#include "CTimeline.h"
#include "GUI/Theme/CThemeConfig.h"

namespace Skylicht
{
	namespace Editor
	{
		namespace GUI
		{
			CTimelineFocus::CTimelineFocus(CBase* base, CTimeline* timeline) :
				CDraggerLimit(base),
				m_timeline(timeline)
			{
				setWidth(3.0f);
				setTarget(this);

				enableRenderFillRect(true);
				setFillRectColor(CThemeConfig::White);
			}

			CTimelineFocus::~CTimelineFocus()
			{

			}

			void CTimelineFocus::postLayout()
			{
				CBase::postLayout();
				setHeight(m_timeline->height());
			}

			void CTimelineFocus::enableDrag(bool b)
			{
				CDraggerLimit::enableDrag(b);

				if (b)
					setCursor(ECursorType::SizeWE);
				else
					setCursor(ECursorType::Normal);
			}

			void CTimelineFocus::onMoved()
			{
				if (m_timeline->OnDragCursor != nullptr)
					m_timeline->OnDragCursor(this, m_timeline->getCursorPosition());
			}

			void CTimelineFocus::onEndMoved()
			{
				if (m_timeline->OnEndDragCursor != nullptr)
					m_timeline->OnEndDragCursor(this, m_timeline->getCursorPosition());
			}
		}
	}
}