#include <Windows.h>

#include <iostream>

#include "../UQCS_Menu/uqcm.h"
#include "../KBDHook_Lib/kbdhook.h"

HANDLE g_hExitEvent;

void key_event(BYTE key, void *pParam) {
	UQCM *menu = (UQCM*)pParam;
	
	if(!g_hExitEvent)
		return;

	if(!menu->input(key) && key == VK_ESCAPE) {
		SetEvent(g_hExitEvent);
		g_hExitEvent = 0;
		return;
	}

	//Clear screen, redraw menu
	//TODO: get rid of `system` call
	system("cls");
	
	for(auto item : menu->getItems()) {
		cout << item.m_selected ? '>' : ' ';
		cout << item.m_title << endl;
	}
}

int main() {
	UQCM menu("menu.txt");

	cout << "Hooking keyboard.." << endl;
	if(KBDHook_Start(key_event, &menu) > 0) {
		cout << "Successfully hooked." << endl;
	} else {
		cout << "Failed to hook." << endl;
		return 1;
	}

	g_hExitEvent = CreateEventA(NULL, 1, 0, NULL);
	
	//Signal initial key event to draw menu
	key_event(0, &menu);

	WaitForSingleObject(g_hExitEvent, INFINITE);

	cout << "Unhooking keyboard.." << endl;
	KBDHook_Stop();
	
	return 0;
}

