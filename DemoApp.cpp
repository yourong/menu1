#include "DemoApp.h"



int CDemoApp::InitInstance()
{

 	m_pMainWnd = &dlgDemo;
	
	return dlgDemo.DoModal();

}


CDemoApp app;
