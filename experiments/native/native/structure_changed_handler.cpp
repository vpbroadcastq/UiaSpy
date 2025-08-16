#include "structure_changed_handler.h"
#include "uiautomationclient.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <format>


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

std::string ToString(EVENTID e) {
	switch (e) {
		case UIA_ToolTipOpenedEventId:
			return "ToolTipOpened";
		case UIA_ToolTipClosedEventId:
			return "ToolTipClosed";
		case UIA_Window_WindowOpenedEventId:
			return "WindowOpened";
		case UIA_Window_WindowClosedEventId:
			return "WindowClosed";
		case UIA_StructureChangedEventId:
			return "UIA_StructureChangedEventId";
		default:
			return std::format("{}", static_cast<int>(e));
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
	//std::format_to(std::back_insert_iterator(s), "Type={} Sender={}", ToString(changeType), dbk::GetClassName2(*pSender));
	std::format_to(std::back_insert_iterator(s), "Type={}", ToString(changeType));
	std::cout << s << std::endl;
	this->_dest.push_back(s);

	return S_OK;
}


//
// Event Handler
//

EventHandler::EventHandler(std::vector<std::string>& v) : _refCount(1), _dest(v) {
	//...
}

ULONG STDMETHODCALLTYPE EventHandler::AddRef() {
	++_refCount;
	return _refCount;
}

ULONG STDMETHODCALLTYPE EventHandler::Release() {
	--_refCount;
	if (_refCount == 0) {
		delete this;
		return 0;
	}
	return _refCount;
}

HRESULT STDMETHODCALLTYPE EventHandler::QueryInterface(REFIID riid, void** ppInterface) {
	if (riid == __uuidof(IUnknown)) {
		*ppInterface = static_cast<IUIAutomationEventHandler*>(this);
	} else if (riid == __uuidof(IUIAutomationEventHandler)) {
		*ppInterface = static_cast<IUIAutomationEventHandler*>(this);
	} else {
		*ppInterface = nullptr;
		return E_NOINTERFACE;
	}
	this->AddRef();
	return S_OK;
}

HRESULT STDMETHODCALLTYPE EventHandler::HandleAutomationEvent(IUIAutomationElement* pSender, EVENTID eventID) {
	std::string s;
	//std::format_to(std::back_insert_iterator(s), "Type={} Sender (ClassName)={}",
	//	ToString(eventID), dbk::GetClassName2(*pSender));
	std::format_to(std::back_insert_iterator(s), "Type={}", ToString(eventID));
	this->_dest.push_back(s);
	std::cout << s << std::endl;
	return S_OK;
}



}  // namespace dbk

