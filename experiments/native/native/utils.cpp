#include "utils.h"

#include "uiautomationclient.h"
#include <string>
#include <type_traits>
#include <algorithm>

namespace dbk {

std::string ToString(const BSTR& bstr) {
	// A BSTR is a composite data type that consists of a length prefix, a data string, and a terminator.
	//   -Length prefix: A four-byte integer that contains the number of bytes in the following data string.
	//    It appears immediately before the first character of the data string.  This value does not include
	//    the terminator.
	//   -Data string: A string of Unicode characters. May contain multiple embedded null characters.
	//   -Terminator: A NULL (0x0000) WCHAR.
	// A BSTR is a pointer. The pointer points to the first character of the data string, not to the length prefix.
	static_assert(std::is_same_v<WCHAR,wchar_t>);
	const void* p = static_cast<const void*>(&bstr);
	const int* pNBytes = static_cast<const int*>(p)-1;
	int nWchars = (*pNBytes)/sizeof(wchar_t);

	const wchar_t* pWchar = static_cast<const wchar_t*>(p);
	std::string s(nWchars,'\0');
	for (int i=0; i<nWchars; ++i) {
		s[i] = static_cast<char>(*pWchar);
		++pWchar;
	}

	return s;
}

std::string GetClassName2(IUIAutomationElement& p) {
	BSTR bstr;  // Do i have to delete this?
	HRESULT hr = p.get_CurrentClassName(&bstr);
	return ToString(bstr);
}



IUIAutomationTreeWalker* CreateTreeWalker(IUIAutomation& automation, IUIAutomationCondition& condition) {
	IUIAutomationTreeWalker* pWalker {nullptr};
	HRESULT hr = automation.CreateTreeWalker(&condition, &pWalker);
	return pWalker;
}


IUIAutomation* InitializeUIAutomation() {
	IUIAutomation *pAutomation {};
	CoInitialize(nullptr);
	[[maybe_unused]] HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), nullptr, CLSCTX_INPROC_SERVER,
		__uuidof(IUIAutomation), (void**)&pAutomation);
	return pAutomation;
}


IUIAutomationElement* FindChildByClassName(IUIAutomation& automation, IUIAutomationElement& root, std::wstring_view name) {
	VARIANT varProp;
	varProp.vt = VT_BSTR;
	varProp.bstrVal = SysAllocString(name.data());
	if (varProp.bstrVal == NULL) {
		return nullptr;
	}

	IUIAutomationCondition* pCondition;
	HRESULT hr = automation.CreatePropertyCondition(UIA_ClassNamePropertyId, varProp, &pCondition);
	if (FAILED(hr)) {
		if (pCondition) {
			pCondition->Release();
		}
		return nullptr;
	}

	IUIAutomationElement* pFound {};
	root.FindFirst(TreeScope_Children, pCondition, &pFound);
	if (pCondition != NULL) {
		pCondition->Release();
	}
	VariantClear(&varProp);
	return pFound;
}


IUIAutomationElement* GetRootElement(IUIAutomation& automation) {
	IUIAutomationElement* pRoot {};
	[[maybe_unused]] HRESULT hr = automation.GetRootElement(&pRoot);
	return pRoot;
}

}  // namespace dbk
