#ifndef LINK_LIST_CIRCLE_DETECTOR_H
#define LINK_LIST_CIRCLE_DETECTOR_H

#pragma once

class LinkListCircleDetector
{
public:
	LinkListCircleDetector();
	~LinkListCircleDetector();

	template<typename T>
	bool HasCircle(const T* root);
	template<typename T>
	size_t CheckCircleAndReturnCircleSize(const T* root);
	template<typename T>
	void RemoveCircleIfHasCircle(T* root);

private:
	template<typename T>
	const T* GetOneOfElementsIfHasCircle(const T* root);
};

#endif
