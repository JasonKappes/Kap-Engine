#ifndef _serializableattorney
#define _serializableattorney
#include "jsonData.h"
#include "JsonHandler.h"

class Serializable;

class SerializableAttorney
{
	friend class SerializableManager;

public:

	class Data
	{
		friend class JsonHandler;
		friend class SerializableManager;
	private:
		static void Serialize(Serializable&, int);

		static void DeSerialize(Serializable*, jsonData*);

		static void SetSerializableInformation(Serializable* t_serializable, jsonData::UserType type);

		static void SetDelIterator(Serializable* t_serializable, std::multimap<JsonHandler::UserType, Serializable*>::iterator&);

	private:
		Data() = delete;
		Data(const Data&) = delete;
		Data operator=(const Data&) = delete;
		~Data() = delete;
	};

	class GameLoop
	{
		friend class ActiveObject;
		friend class SerializableManager;
		friend class ActiveObject;
		friend class OldScaleCommand;
		friend class xPosUI;
		friend class yPosUI;
		friend class zPosUI;
		friend class zRotUI;
		friend class yRotUI;
		friend class xRotUI;
		friend class xyzScaleUI;
		friend class OldRotationCommand;
		friend class OldPositionCommand;
		friend class ReviveSerializableCommand;
	private:
		static void EditorRender(const Serializable&);

		static void Duplicate(const Serializable&);

		static void Remove(Serializable*);

		static Transform* GetTransform(Serializable*);

	private:
		GameLoop() = delete;
		GameLoop(const GameLoop&) = delete;
		GameLoop operator=(const GameLoop&) = delete;
		~GameLoop() = delete;
	};

private:
	SerializableAttorney() = delete;
	SerializableAttorney(const SerializableAttorney&) = delete;
	SerializableAttorney operator=(const SerializableAttorney&) = delete;
	~SerializableAttorney() = delete;
};

#endif _serializableattorney
#pragma once
