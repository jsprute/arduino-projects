// 
// 
// 

#include "ObjectList.h"


void ObjectList::reset() {
	current = root;
	previous = 0;
}

ObjectList::ObjectList() {
	this->root = 0;
	this->current = 0;
	this->previous = 0;
}

void ObjectList::addObject(Object *object) {
	if (object) {
		if (this->current) {
			Object *temp = this->current->nextObject;
			object->nextObject = temp;
			this->current->nextObject = object;
		}
		else {
			this->root = object;
			this->current = object;
			this->previous = 0;
		}
	}
}

Object* ObjectList::removeObject() {

	Object *temp = 0;
	if (current) {
		if (previous) {
			previous->nextObject = current->nextObject;
			temp = current;
			current = previous->nextObject;
			temp->nextObject = 0;
		}
		else {
			root = current->nextObject;
			temp = current;
			current = root;
			temp->nextObject = 0;
			previous = 0;
		}
	}
	return temp;
}

Object* ObjectList::peekObject() {
	return current;
}

Object* ObjectList::nextObject() {
	if (current) {
		previous = current;
		current = current->nextObject;
		return previous;
	}
	return 0;
}

Object* ObjectList::getObject(String name) {
	
	Object* keepPlace = current;
	current = root;

	Object* toReturn = 0;

	while (toReturn = nextObject()) {
		if (toReturn->isName(name))
			break;
	}
	current = keepPlace;
	return toReturn;
}