#pragma once
#include <optional>
#include <vector>


//
// It's tricky to wrap com objects like this.  What you see below is not going to work out very well.
//


namespace dbk::priv {
	class Accessor;
}

namespace dbk {
class Automation;
class ICacheRequest;
class IStructureChangedEventHandler;

//
// Utility
//
bool InitComMultithread() noexcept;
void UninitCom() noexcept;

//
// Enums
//
enum class TreeScope {
	None=0,
	Element=1,
	Children=2,
	Descendants=4,
	Parent=8,
	Ancestors=16,
	Subtree=1|2|4
};

enum class StructureChangeType {
	ChildAdded,
	ChildRemoved,
	ChildrenInvalidated,
	ChildrenBulkAdded,
	ChildrenBulkRemoved,
	ChildrenReordered,
};


class AutomationElement {
	void* _p;
public:
	~AutomationElement() noexcept;
private:
	AutomationElement(void*) noexcept;
	void* get() noexcept;
	friend Automation;
	friend dbk::priv::Accessor;
};


class Automation {
	void* _p {};
public:
	static std::optional<Automation> Make() noexcept;
	std::optional<AutomationElement> GetRootElement() noexcept;
	bool AddStructureChangedEventHandler(AutomationElement&, TreeScope, ICacheRequest&, IStructureChangedEventHandler&) noexcept;
	~Automation() noexcept;
private:
	Automation(void*) noexcept;
	friend dbk::priv::Accessor;
};




//
// Interfaces
//
class IStructureChangedEventHandler {
public:
	virtual bool HandleStructureChangedEvent(AutomationElement&, StructureChangeType, std::vector<int>*) noexcept = 0;
private:
};

class ICacheRequest {
public:
private:
};











}  // namespace dbk
