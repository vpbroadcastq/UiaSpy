#pragma once
#include "uiautomationclient.h"
#include <string>
#include <vector>

namespace dbk {

std::string ToString(const BSTR& bstr);
std::string GetClassName2(IUIAutomationElement&);

IUIAutomationTreeWalker* CreateTreeWalker(IUIAutomation& automation, IUIAutomationCondition& condition);
IUIAutomation* InitializeUIAutomation();
IUIAutomationElement* GetRootElement(IUIAutomation& automation);
IUIAutomationElement* FindChildByClassName(IUIAutomation& automation, IUIAutomationElement& root, std::wstring_view name);

template<typename T>
std::vector<T> ToVector(SAFEARRAY& a) {
	std::vector<T> v;
	HRESULT hr = SafeArrayLock(&a);
	if (!SUCCEEDED(hr)) {
		return v;
	}

	std::size_t count {0};
	{
		long lBound {};
		long uBound {};
		SafeArrayGetLBound(&a, 1, &lBound);
		SafeArrayGetUBound(&a, 1, &uBound);
		count = static_cast<std::size_t>(uBound - lBound + 1);  // bounds are inclusive
	}

	const T* pData;
	SafeArrayAccessData(&a, (void**)&pData);

	for (std::size_t i = 0; i<count; ++i) {
		v.push_back(*pData);
		++pData;
	}

	SafeArrayUnaccessData(&a);

	return v;
}





};





