#include "KapSprite.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include <DebugOut.h>
#include <ShaderManager.h>

KapSprite::KapSprite(std::string t_name)
{
	this->m_model = ModelManager::Get(Model::PreMadeModels::UnitSquareXY);
	this->m_shader = ShaderManager::Get("spriteRender");

	this->m_image = ImageManager::Get(t_name);
	this->m_width = 10.0f;
	this->m_rectPosSize = new Rect(150.0f, 500.0f, 100.0f, 100.0f);
	this->m_sprite = new GraphicsObject_Sprite(m_model, m_shader, this->m_image, this->m_rectPosSize);

	this->m_rotZ.set(ROT_Z, 0.0f);

	this->SetAngle(0);
	this->SetScaleFactor(1.0f, 1.0f);
	this->SetPosition(150, 500);
}

KapSprite::KapSprite(std::string t_imageName, float x, float y, float w, float h)
{
	this->m_model = ModelManager::Get(Model::PreMadeModels::UnitSquareXY);
	this->m_shader = ShaderManager::Get("spriteRender");
	this->m_image = ImageManager::Get(t_imageName);
	this->m_rectPosSize = new Rect(x, y, w, h);

	this->m_image->pImageRect->x = x;
	this->m_image->pImageRect->y = y;
	this->m_image->pImageRect->width = w;
	this->m_image->pImageRect->height = h;

	this->m_sprite = new GraphicsObject_Sprite(m_model, m_shader, m_image, this->m_rectPosSize);

	this->m_width = w;
	this->m_height = h;
	this->m_rotZ.set(ROT_Z, 0.0f);
	this->SetAngle(0);
	this->SetScaleFactor(1.0f, 1.0f);
	//this->SetScalePixel(300, 300);
	this->SetPosition(150, 500);
	DebugMsg::out("    end of kap sprite font constructor ");
}

float KapSprite::GetAngle()
{
	return this->m_rotAngle;
}

float KapSprite::GetWidth()
{
	return this->m_width;
}

float KapSprite::GetHeight()
{
	return this->m_height;
}

void KapSprite::Render()
{
	this->m_sprite->Render(SceneManager::Get2DCamera());
}

void KapSprite::SetAngle(float t_newAngle)
{
	this->m_rotAngle = t_newAngle;
	this->m_rotZ.set(RotType::ROT_Z, this->m_rotAngle);
	this->m_world = m_worldScale * m_rotZ * m_trans;
	this->m_sprite->SetWorld(m_world);
}

void KapSprite::SetCenter(float t_offsetx, float t_offsety)
{
	this->m_centerX = t_offsetx;
	this->m_centerY = t_offsety;
}

void KapSprite::SetPosition(float t_newX, float t_newY)
{
	this->m_sprite->origPosX = t_newX;
	this->m_sprite->origPosY = t_newY;
	this->m_trans.set(TRANS, this->m_sprite->origPosX, this->m_sprite->origPosY, 0.0f);
	this->m_world = m_worldScale * m_rotZ * m_trans;
	this->m_sprite->SetWorld(m_world);
}

void KapSprite::SetScaleFactor(float t_scaleX, float t_scaleY)
{
	this->m_scaleX = t_scaleX;
	this->m_scaleY = t_scaleY;
	this->m_width *= m_scaleX;
	this->m_height *= m_scaleY;
	this->m_worldScale.set(SCALE, this->m_scaleX, this->m_scaleY, 1.0f);
	this->m_world = m_worldScale * m_rotZ * m_trans;
	this->m_sprite->SetWorld(m_world);
}

void KapSprite::SetScalePixel(float t_width, float t_height)
{
	this->m_scaleX = t_width / this->m_sprite->origWidth;
	this->m_scaleY = t_height / this->m_sprite->origHeight;
	this->m_width *= m_scaleX;
	this->m_height *= m_scaleY;
	this->m_worldScale.set(SCALE, this->m_scaleX, this->m_scaleY, 1.0f);
	this->m_world = m_worldScale * m_rotZ * m_trans;
	this->m_sprite->SetWorld(m_world);
}

float KapSprite::GetX() { return this->m_sprite->origPosX; }

float KapSprite::GetY() { return this->m_sprite->origPosY; }

KapSprite::~KapSprite()
{
	delete this->m_sprite;
	delete this->m_rectPosSize;
}

