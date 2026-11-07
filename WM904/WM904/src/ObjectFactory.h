#pragma once
#include "DStructures.h"
#include "Entity.h"
class ObjectFactory
{
protected:
	DataStructures::List<GameObject*>* _listRef;

public:
	ObjectFactory(DataStructures::List<GameObject*>* listToAdd){
		_listRef = listToAdd;
	}
	void AddObject(GameObject* obj) {
		if (obj == nullptr) return;
		_listRef->Add(obj);
	}
	void RemoveObject(GameObject* obj) {
		if (obj == nullptr) return;
		_listRef->Remove(obj);
	}
};