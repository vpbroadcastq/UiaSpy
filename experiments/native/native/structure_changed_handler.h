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



//
// From example
//

class EventHandler : public IUIAutomationEventHandler {
private:
	std::atomic<int> _refCount;
	int _eventCount;
	std::vector<std::string>& _dest;

public:
    EventHandler(std::vector<std::string>&);
    
	// IUnknown
    ULONG STDMETHODCALLTYPE AddRef() override;
    ULONG STDMETHODCALLTYPE Release() override;
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppInterface) override;

    // IUIAutomationEventHandler
    HRESULT STDMETHODCALLTYPE HandleAutomationEvent(IUIAutomationElement* pSender, EVENTID eventID) override;
};


//
// From example
//
class StructureEventHandler:
    public IUIAutomationStructureChangedEventHandler
{
private:
    LONG _refCount;

public:
    int _eventCount;

    // Constructor.
    StructureEventHandler(): _refCount(1), _eventCount(0) 
    {
    }

    // IUnknown methods.
    ULONG STDMETHODCALLTYPE AddRef() 
    {
        ULONG ret = InterlockedIncrement(&_refCount);
        return ret;
    }

    ULONG STDMETHODCALLTYPE Release() 
    {
        ULONG ret = InterlockedDecrement(&_refCount);
        if (ret == 0) 
        {
            delete this;
            return 0;
        }
        return ret;
    }

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppInterface) 
    {
        if (riid == __uuidof(IUnknown))
            *ppInterface=static_cast<IUIAutomationStructureChangedEventHandler*>(this);
        else if (riid == __uuidof(IUIAutomationStructureChangedEventHandler)) 
            *ppInterface=static_cast<IUIAutomationStructureChangedEventHandler*>(this);
        else 
        {
            *ppInterface = NULL;
            return E_NOINTERFACE;
        }
        this->AddRef();
        return S_OK;
    }

    // IUIAutomationStructureChangedEventHandler methods
    HRESULT STDMETHODCALLTYPE HandleStructureChangedEvent(IUIAutomationElement* pSender, StructureChangeType changeType, SAFEARRAY* pRuntimeID) {
        _eventCount++;
        switch (changeType) 
        {
            case StructureChangeType_ChildAdded:
                wprintf(L">> Structure Changed: ChildAdded! (count: %d)\n", _eventCount);
                break;
            case StructureChangeType_ChildRemoved:
                wprintf(L">> Structure Changed: ChildRemoved! (count: %d)\n", _eventCount);
                break;
            case StructureChangeType_ChildrenInvalidated:
                wprintf(L">> Structure Changed: ChildrenInvalidated! (count: %d)\n", _eventCount);
                break;
            case StructureChangeType_ChildrenBulkAdded:
                wprintf(L">> Structure Changed: ChildrenBulkAdded! (count: %d)\n", _eventCount);
                break;
            case StructureChangeType_ChildrenBulkRemoved:
                wprintf(L">> Structure Changed: ChildrenBulkRemoved! (count: %d)\n", _eventCount);
                break;
            case StructureChangeType_ChildrenReordered:
                wprintf(L">> Structure Changed: ChildrenReordered! (count: %d)\n", _eventCount);
                break;
        }
        return S_OK;
    }
};


} // namespace dbk

