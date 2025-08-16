#include "uiautomationclient.h"
#include "utils.h"
#include "structure_changed_handler.h"
#include <iostream>

int main(int argc, char* argv[]) {
	std::vector<std::string> events;
	dbk::StructureChangedHandler strucChHandler(events);
	//dbk::EventHandler evHandler {};

	IUIAutomation* pAutomation = dbk::InitializeUIAutomation();
	if (!pAutomation) {
		std::cout << "Unable to init automation!" << std::endl;
			return 1;
	}

	IUIAutomationElement* destopRoot = dbk::GetRootElement(*pAutomation);
	IUIAutomationElement* window = dbk::FindChildByClassName(*pAutomation, *destopRoot, L"Framework::CFrame");
	IUIAutomationElement* mainWindow = dbk::FindChildByClassName(*pAutomation, *window, L"OneNote::MainWindow");
	IUIAutomationElement* workspace = dbk::FindChildByClassName(*pAutomation, *mainWindow, L"OneNote::CWorkspace");
	IUIAutomationElement* canvas = dbk::FindChildByClassName(*pAutomation, *workspace, L"OneNote::Canvas");
	IUIAutomationElement* pageSurf = dbk::FindChildByClassName(*pAutomation, *canvas, L"OneNote::PageSurface");

	HRESULT hr1 = pAutomation->AddStructureChangedEventHandler(window, TreeScope_Subtree, NULL, &strucChHandler);
	HRESULT hr2 = pAutomation->AddStructureChangedEventHandler(mainWindow, TreeScope_Element, NULL, &strucChHandler);
	HRESULT hr3 = pAutomation->AddStructureChangedEventHandler(workspace, TreeScope_Element, NULL, &strucChHandler);
	HRESULT hr4 = pAutomation->AddStructureChangedEventHandler(canvas, TreeScope_Element, NULL, &strucChHandler);
	HRESULT hr5 = pAutomation->AddStructureChangedEventHandler(pageSurf, TreeScope_Element, NULL, &strucChHandler);
	//HRESULT hr = pAutomation->AddAutomationEventHandler(UIA_StructureChangedEventId, destopRoot, TreeScope_Subtree, NULL, &evHandler);
	getchar();

	return 0;
}

