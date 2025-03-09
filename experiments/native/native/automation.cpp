#include "automation.h"
#include "UIAutomationClient.h"


namespace dbk::priv {

class Accessor {
public:
	static dbk::AutomationElement Make(IUIAutomationElement* p) noexcept {
		return dbk::AutomationElement(p);
	}
};

::TreeScope ToUia(::dbk::TreeScope scope) {
	static_assert(static_cast<int>(::dbk::TreeScope::None) == static_cast<int>(::TreeScope_None));
	static_assert(static_cast<int>(::dbk::TreeScope::Element) == static_cast<int>(::TreeScope_Element));
	static_assert(static_cast<int>(::dbk::TreeScope::Children) == static_cast<int>(::TreeScope_Children));
	static_assert(static_cast<int>(::dbk::TreeScope::Descendants) == static_cast<int>(::TreeScope_Descendants));
	static_assert(static_cast<int>(::dbk::TreeScope::Parent) == static_cast<int>(::TreeScope_Parent));
	static_assert(static_cast<int>(::dbk::TreeScope::Ancestors) == static_cast<int>(::TreeScope_Ancestors));
	static_assert(static_cast<int>(::dbk::TreeScope::Subtree) == static_cast<int>(::TreeScope_Subtree));
	
	return static_cast<::TreeScope>(scope);
}

::StructureChangeType ToUia(::dbk::StructureChangeType type) {
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildAdded)
		== static_cast<int>(::StructureChangeType_ChildAdded));
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildRemoved)
		== static_cast<int>(::StructureChangeType_ChildRemoved));
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildrenInvalidated)
		== static_cast<int>(::StructureChangeType_ChildrenInvalidated));
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildrenBulkAdded)
		== static_cast<int>(::StructureChangeType_ChildrenBulkAdded));
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildrenBulkRemoved)
		== static_cast<int>(::StructureChangeType_ChildrenBulkRemoved));
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildrenReordered)
		== static_cast<int>(::StructureChangeType_ChildrenReordered));
	
	return static_cast<::StructureChangeType>(type);
}

dbk::StructureChangeType FromUia(::StructureChangeType type) {
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildAdded)
		== static_cast<int>(::StructureChangeType_ChildAdded));
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildRemoved)
		== static_cast<int>(::StructureChangeType_ChildRemoved));
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildrenInvalidated)
		== static_cast<int>(::StructureChangeType_ChildrenInvalidated));
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildrenBulkAdded)
		== static_cast<int>(::StructureChangeType_ChildrenBulkAdded));
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildrenBulkRemoved)
		== static_cast<int>(::StructureChangeType_ChildrenBulkRemoved));
	static_assert(static_cast<int>(::dbk::StructureChangeType::ChildrenReordered)
		== static_cast<int>(::StructureChangeType_ChildrenReordered));
	
	return static_cast<dbk::StructureChangeType>(type);
}

}  // namespace dbk::priv


namespace dbk {

class StructureChangedEventHandlerAdapter : public IUIAutomationStructureChangedEventHandler {
public:
	StructureChangedEventHandlerAdapter(dbk::IStructureChangedEventHandler& h) noexcept
		: _p {&h}, _refCount {1} {
		//...
	}

	ULONG STDMETHODCALLTYPE AddRef() override {
		ULONG ret = InterlockedIncrement(&_refCount);
		return ret;
	}

	ULONG STDMETHODCALLTYPE Release() override {
		ULONG ret = InterlockedDecrement(&_refCount);
		if (ret == 0) {
			delete this;
			return 0;
		}
		return ret;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppInterface) override {
		if (riid == __uuidof(IUnknown)) {
			*ppInterface=static_cast<IUIAutomationStructureChangedEventHandler*>(this);
		} else if (riid == __uuidof(IUIAutomationStructureChangedEventHandler)) {
			*ppInterface=static_cast<IUIAutomationStructureChangedEventHandler*>(this);
		} else {
			*ppInterface = NULL;
			return E_NOINTERFACE;
		}
		this->AddRef();
		return S_OK;
	}

	// IUIAutomationStructureChangedEventHandler methods
	HRESULT STDMETHODCALLTYPE HandleStructureChangedEvent(IUIAutomationElement* pUiaSender, ::StructureChangeType uiaChangeType,
															SAFEARRAY* pRuntimeID) {
		bool success = _p->HandleStructureChangedEvent(dbk::priv::Accessor::Make(pUiaSender),
			::dbk::priv::FromUia(uiaChangeType), nullptr);
		if (!success) {
			return E_FAIL;
		}
		return S_OK;
	}
private:
	dbk::IStructureChangedEventHandler* _p;
	LONG _refCount;
};

}  // namespace dbk::priv


namespace dbk {

//
// Utility
//
bool InitComMultithread() noexcept {
	HRESULT hr = CoInitializeEx(NULL,COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		return false;
	}
	return true;
}

void UninitCom() noexcept {
	CoUninitialize();
}


//
// Automation
//
std::optional<Automation> Automation::Make() noexcept {
	IUIAutomation *pAutomation {};
	HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), nullptr, CLSCTX_INPROC_SERVER,
		__uuidof(IUIAutomation), (void**)&pAutomation);
	if (FAILED(hr)) {
		return std::nullopt;
	}

	return Automation(pAutomation);
}

Automation::Automation(void* p) noexcept : _p(p) {
	//...
}

std::optional<AutomationElement> Automation::GetRootElement() noexcept {
	IUIAutomationElement* pRoot {};
	HRESULT hr = static_cast<IUIAutomation*>(_p)->GetRootElement(&pRoot);
	if (FAILED(hr)) {
		return std::nullopt;
	}

	return AutomationElement(pRoot);
}

/*HRESULT AddStructureChangedEventHandler(
  [in] IUIAutomationElement                      *element,
  [in] TreeScope                                 scope,
  [in] IUIAutomationCacheRequest                 *cacheRequest,
  [in] IUIAutomationStructureChangedEventHandler *handler
);*/

bool Automation::AddStructureChangedEventHandler(AutomationElement& ae, TreeScope ts, ICacheRequest& cr,
												IStructureChangedEventHandler& h) noexcept {
	
	// The user is expected to keep the adapted object alive somehow.  Uia expects it to manage
	// its own lifetime via AddRef/Release, which it does not do.  Only the wrapper is so-managed.
	// Perhaps the adapter should hold a weak_ptr to the user's handler.
	StructureChangedEventHandlerAdapter* adapter = new StructureChangedEventHandlerAdapter(h);
	HRESULT hr = static_cast<IUIAutomation*>(_p)->AddStructureChangedEventHandler(
		static_cast<IUIAutomationElement*>(ae.get()), dbk::priv::ToUia(ts), nullptr, adapter);

	if (FAILED(hr)) {
		return false;
	}
	return true;
}

Automation::~Automation() noexcept {
	static_cast<IUIAutomation*>(_p)->Release();
	CoUninitialize();
}



//
// AutomationElement
//
AutomationElement::AutomationElement(void* p) noexcept {
	_p = p;
}

AutomationElement::~AutomationElement() noexcept {
	static_cast<IUIAutomation*>(_p)->Release();
}

void* AutomationElement::get() noexcept {
	return _p;
}

}  // namespace dbk

