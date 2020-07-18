#ifndef _kapsprite
#define _kapsprite
#include "Matrix.h"
#include "Rect.h"

class GraphicsObject_Sprite;
class ShaderObject;
class Model;
class Image;
class Camera;

class KapSprite
{
public: // ----> USER METHODS

	/// <summary>
	/// This method should be called on a KapSprite object from Draw2D() to show this sprite on screen.
	/// </summary> 
	/// \ingroup KapSprite
	void Render();

	/// <summary>
	/// This method sets the rotation, or angle, of a KapSprite.
	/// </summary> 
	/// \ingroup KapSprite
	void SetAngle(float angle);

	/// <summary>
	/// This method sets the pixel center, rotation point, of a KapSprite.
	/// </summary> 
	/// \ingroup KapSprite
	void SetCenter(float centerX, float centerY);

	/// <summary>
	/// This method sets the position on screen where the KapSprite object will be rendered.
	/// </summary> 
	/// \ingroup KapSprite
	void SetPosition(float positionX, float positionY);

	/// <summary>
	/// This method multiplies the size of the KapSprite by scale input given.
	/// </summary> 
	/// \ingroup KapSprite
	void SetScaleFactor(float scalex, float scaley);

	/// <summary>
	/// This method sets the exact pixel width and height of the KapSprite.
	/// </summary> 
	/// \ingroup KapSprite
	void SetScalePixel(float width, float height);

	/// <summary>
	/// Returns the angle at which the KapSprite is rotated at.
	/// </summary> 
	/// \ingroup KapSprite
	float GetAngle();

	/// <summary>
	/// Returns the horizontal (x) position of the KapSprite.
	/// </summary> 
	/// \ingroup KapSprite
	float GetX();

	/// <summary>
	/// Returns the vertical (y) position of the KapSprite.
	/// </summary> 
	/// \ingroup KapSprite
	float GetY();

	/// <summary>
	/// Returns the pixel width of the KapSprite.
	/// </summary> 
	/// \ingroup KapSprite
	float GetWidth();

	/// <summary>
	/// Returns the pixel height of the KapSprite.
	/// </summary> 
	/// \ingroup KapSprite
	float GetHeight();

public:
	KapSprite() = delete;
	KapSprite(std::string);
	KapSprite(std::string, float x, float y, float w, float h);
	KapSprite(const KapSprite&) = delete;
	KapSprite operator=(const KapSprite&) = delete;
	~KapSprite();

private:
	GraphicsObject_Sprite* m_sprite;
	ShaderObject* m_shader;
	Rect* m_rectPosSize;
	Model* m_model;
	Image* m_image;

	float m_rotAngle;
	float m_centerX;
	float m_centerY;
	float m_scaleX;
	float m_scaleY;
	float m_width;
	float m_height;

	Matrix m_worldScale;
	Matrix m_rotZ;
	Matrix m_world;
	Matrix m_trans;

};

#endif _kapsprite
#pragma once
