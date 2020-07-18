#ifndef _volumeshow
#define _volumeshow

class Matrix;
class Vect;

class VolumeShow
{
public:
	VolumeShow() = default;
	VolumeShow(const VolumeShow&) = delete;
	virtual ~VolumeShow() = default;

	virtual const void ShowCollisionVolume(Matrix&, const Vect&) const = 0;
};

#endif _volumeshow
#pragma once
