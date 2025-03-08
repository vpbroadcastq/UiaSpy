#pragma once
#include <windows.h>
#include "uiautomationclient.h"
#include <vector>
#include <string>
#include <format>
#include <atomic>

namespace dbk {

std::string_view ToString(StructureChangeType t);


class StructureChangedHandler : public IUIAutomationStructureChangedEventHandler {
private:
	std::atomic<int> _refCount;
	std::vector<std::string>& _dest;

public:
	StructureChangedHandler(std::vector<std::string>& pdest) : _refCount(1), _dest(pdest) {
		//...
	}

	// IUnknown
	ULONG STDMETHODCALLTYPE AddRef() override {
		++_refCount;
		return _refCount;
	}

	ULONG STDMETHODCALLTYPE Release() override {
		--_refCount;
		if (_refCount == 0) {
			delete this;
			return 0;
		}
		return _refCount;
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
	HRESULT STDMETHODCALLTYPE HandleStructureChangedEvent(IUIAutomationElement* pSender,
														StructureChangeType changeType,
														SAFEARRAY* pRuntimeID) override;
};








class EventHandler:
    public IUIAutomationEventHandler
{
private:
    LONG _refCount;

public:
    int _eventCount;

    // Constructor.
    EventHandler();
    // IUnknown methods.
    ULONG STDMETHODCALLTYPE AddRef() override;
    ULONG STDMETHODCALLTYPE Release() override;
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppInterface) override;

    // IUIAutomationEventHandler methods
    HRESULT STDMETHODCALLTYPE HandleAutomationEvent(IUIAutomationElement * pSender, EVENTID eventID) override;
};






} // namespace dbk

