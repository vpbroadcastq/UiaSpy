#include "uiautomationclient.h"
#include "utils.h"
#include "structure_changed_handler.h"
#include <iostream>

/*int main(int argc, char* argv[]) {
	std::vector<std::string> events;
	dbk::StructureChangedHandler strucChHandler(events);
	dbk::EventHandler evHandler {};

	IUIAutomation* pAutomation = dbk::InitializeUIAutomation();
	if (!pAutomation) {
		std::cout << "Unable to init automation!" << std::endl;
			return 1;
	}

	IUIAutomationElement* destopRoot = dbk::GetRootElement(*pAutomation);
	//IUIAutomationElement* window = dbk::FindChildByClassName(*pAutomation, *destopRoot, L"Framework::CFrame");
	//IUIAutomationElement* mainWindow = dbk::FindChildByClassName(*pAutomation, *window, L"OneNote::MainWindow");
	//IUIAutomationElement* workspace = dbk::FindChildByClassName(*pAutomation, *mainWindow, L"OneNote::CWorkspace");
	//IUIAutomationElement* canvas = dbk::FindChildByClassName(*pAutomation, *workspace, L"OneNote::Canvas");
	//IUIAutomationElement* pageSurf = dbk::FindChildByClassName(*pAutomation, *canvas, L"OneNote::PageSurface");

	//HRESULT hr = pAutomation->AddStructureChangedEventHandler(destopRoot, TreeScope_Subtree, NULL, &strucChHandler);
	HRESULT hr = pAutomation->AddAutomationEventHandler(UIA_StructureChangedEventId, destopRoot, TreeScope_Subtree, NULL, &evHandler);
	getchar();

	return 0;
}*/



int main(int argc, char* argv[])
{
    HRESULT hr;
    int ret = 0;
    IUIAutomationElement* pTargetElement = NULL;
    dbk::EventHandler* pEHTemp = NULL;

    CoInitializeEx(NULL,COINIT_MULTITHREADED);
    IUIAutomation* pAutomation = NULL;
    hr = CoCreateInstance(__uuidof(CUIAutomation), NULL,CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**)&pAutomation);
    if(FAILED(hr) || pAutomation==NULL) 
    {
        ret = 1;
        goto cleanup;
    }
    // Use root element for listening to window and tooltip creation and destruction.
    hr = pAutomation->GetRootElement(&pTargetElement);
    if (FAILED(hr) || pTargetElement==NULL) 
    {
        ret = 1;
        goto cleanup;
    }

    pEHTemp = new dbk::EventHandler();
    if (pEHTemp == NULL) 
    {
        ret = 1;
        goto cleanup;
    }

    wprintf(L"-Adding Event Handlers.\n");
    hr = pAutomation->AddAutomationEventHandler(UIA_ToolTipOpenedEventId, pTargetElement, TreeScope_Subtree, NULL, (IUIAutomationEventHandler*) pEHTemp);
    if (FAILED(hr)) 
    {
        ret = 1;
        goto cleanup;
    }
    hr = pAutomation->AddAutomationEventHandler(UIA_ToolTipClosedEventId, pTargetElement, TreeScope_Subtree, NULL, (IUIAutomationEventHandler*) pEHTemp);
    if (FAILED(hr)) 
    {
        ret = 1;
        goto cleanup;
    }
    hr = pAutomation->AddAutomationEventHandler(UIA_Window_WindowOpenedEventId, pTargetElement, TreeScope_Subtree, NULL, (IUIAutomationEventHandler*) pEHTemp);
    if (FAILED(hr)) 
    {
        ret = 1;
        goto cleanup;
    }
    hr = pAutomation->AddAutomationEventHandler(UIA_Window_WindowClosedEventId, pTargetElement, TreeScope_Subtree, NULL, (IUIAutomationEventHandler*) pEHTemp);
    if (FAILED(hr)) 
    {
        ret = 1;
        goto cleanup;
    }
    hr = pAutomation->AddAutomationEventHandler(UIA_StructureChangedEventId, pTargetElement, TreeScope_Subtree, NULL, (IUIAutomationEventHandler*) pEHTemp);
    if (FAILED(hr)) 
    {
        ret = 1;
        goto cleanup;
    }

    wprintf(L"-Press any key to remove event handlers and exit\n");
    getchar();

    wprintf(L"-Removing Event Handlers.\n");

cleanup:
    // Remove event handlers, release resources, and terminate
    if (pAutomation != NULL) 
    {
        hr = pAutomation->RemoveAllEventHandlers();
        if (FAILED(hr))
            ret = 1;
        pAutomation->Release();
    }

    if (pEHTemp != NULL) 
        pEHTemp->Release();

    if (pTargetElement != NULL) 
        pTargetElement->Release();

    CoUninitialize();
    return ret;
}



