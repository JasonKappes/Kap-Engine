#include "ScreenLog.h"
#include "SpriteFontManager.h"
#include "SpriteFont.h"
#include "SpriteString.h"
#include <DebugOut.h>

ScreenLog* ScreenLog::m_ptrInstance = nullptr;

ScreenLog::ScreenLog()
{
    this->m_font = SpriteFontManager::Get("Fonts/Dosis2");
    this->m_anchorX = 20;
    this->m_anchorY = 550;
    this->m_verticalLineSpacing = 25;
}

void ScreenLog::Add(char* A, ...)
{
    va_list args;

    va_start(args, A);
    vsprintf_s(Instance().m_DebugBuff, A, args);
    va_end(args);

    std::string s(Instance().m_DebugBuff);

    Instance().m_messageCollection.push_back(new SpriteString(Instance().m_font, s, Instance().m_anchorX, Instance().m_anchorY));
}

void ScreenLog::Delete()
{
	delete Instance().m_ptrInstance;
}

void ScreenLog::Render() { Instance().privRender(); }

void ScreenLog::privRender()
{
    std::list<SpriteString*>::iterator it;
    int y = this->m_anchorY;
    SpriteString* t_messageToRender;
    for (it = this->m_messageCollection.begin(); it != this->m_messageCollection.end(); ++it)
    {
        t_messageToRender = (*it);
        t_messageToRender->SetPosition(m_anchorX, y);
        t_messageToRender->Render();
        y += this->m_verticalLineSpacing;

        delete t_messageToRender;
    }
    this->m_messageCollection.clear();
}
