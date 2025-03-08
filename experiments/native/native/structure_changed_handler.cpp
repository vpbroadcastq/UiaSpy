#include "structure_changed_handler.h"
#include "uiautomationclient.h"
#include "utils.h"


namespace dbk {


std::string_view ToString(StructureChangeType t) {
	switch (t) {
		case StructureChangeType_ChildAdded:
			return "ChildAdded";
		case StructureChangeType_ChildRemoved:
			return "ChildRemoved";
		case StructureChangeType_ChildrenInvalidated:
			return "ChildrenInvalidated";
		case StructureChangeType_ChildrenBulkAdded:
			return "ChildrenBulkAdded";
		case StructureChangeType_ChildrenBulkRemoved:
			return "ChildrenBulkRemoved";
		case StructureChangeType_ChildrenReordered:
			return "ChildrenReordered";
		default:
			return "Unknown";
	}
}

// https://learn.microsoft.com/en-us/windows/win32/api/uiautomationcore/ne-uiautomationcore-structurechangetype
// Except for ChildAdded, structure-change events are always associated with the container element that holds
// the children. The ChildAdded event is associated with the element that was just added.
// 
// https://learn.microsoft.com/en-us/windows/win32/api/uiautomationclient/nf-uiautomationclient-iuiautomationstructurechangedeventhandler-handlestructurechangedevent
// pRuntimeID receives the runtime identifier of the element. This parameter is used only when changeType is
// StructureChangeType_ChildRemoved; it is NULL for all other structure-change events.
HRESULT STDMETHODCALLTYPE StructureChangedHandler::HandleStructureChangedEvent(
													IUIAutomationElement* pSender,
													StructureChangeType changeType,
													SAFEARRAY* pRuntimeID) {
	std::string s;
	std::format_to(std::back_insert_iterator(s), "Type={} Sender={}", ToString(changeType), dbk::GetClassName(*pSender));
	this->_dest.push_back(s);

	return S_OK;
}








EventHandler::EventHandler(): _refCount(1), _eventCount(0) {
}

// IUnknown methods.
ULONG STDMETHODCALLTYPE EventHandler::AddRef() 
{
	ULONG ret = InterlockedIncrement(&_refCount);
	return ret;
}

ULONG STDMETHODCALLTYPE EventHandler::Release() 
{
	ULONG ret = InterlockedDecrement(&_refCount);
	if (ret == 0) 
	{
		delete this;
		return 0;
	}
	return ret;
}

HRESULT STDMETHODCALLTYPE EventHandler::QueryInterface(REFIID riid, void** ppInterface) 
{
	if (riid == __uuidof(IUnknown)) 
		*ppInterface=static_cast<IUIAutomationEventHandler*>(this);
	else if (riid == __uuidof(IUIAutomationEventHandler)) 
		*ppInterface=static_cast<IUIAutomationEventHandler*>(this);
	else 
	{
		*ppInterface = NULL;
		return E_NOINTERFACE;
	}
	this->AddRef();
	return S_OK;
}

// IUIAutomationEventHandler methods
HRESULT STDMETHODCALLTYPE EventHandler::HandleAutomationEvent(IUIAutomationElement * pSender, EVENTID eventID)
{
	_eventCount++;
	switch (eventID) 
	{
		case UIA_ToolTipOpenedEventId:
			wprintf(L">> Event ToolTipOpened Received! (count: %d)\n", _eventCount);
			break;
		case UIA_ToolTipClosedEventId:
			wprintf(L">> Event ToolTipClosed Received! (count: %d)\n", _eventCount);
			break;
		case UIA_Window_WindowOpenedEventId:
			wprintf(L">> Event WindowOpened Received! (count: %d)\n", _eventCount);
			break;
		case UIA_Window_WindowClosedEventId:
			wprintf(L">> Event WindowClosed Received! (count: %d)\n", _eventCount);
			break;
		case UIA_StructureChangedEventId:
			wprintf(L">> UIA_StructureChangedEventId! (count: %d)\n", _eventCount);
			break;
		default:
			wprintf(L">> Event (%d) Received! (count: %d)\n", eventID, _eventCount);
			break;
	}
	return S_OK;
}










}  // namespace dbk

