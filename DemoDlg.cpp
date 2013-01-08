#include "DemoDlg.h"
#include "resource.h"


CDemoDlg::CDemoDlg():CDialog(IDD_DLGDEMO){}

BOOL CDemoDlg::OnInitDialog()
{

	m_hIcon=LoadIcon(GetWindowInstance(m_hWnd),
	 	             MAKEINTRESOURCE(IDI_ICON));
    SetIcon(m_hIcon,true); 
    SetIcon(m_hIcon,false); 

	
	//Creating the menu
	mnuSideBar.CreatePopupMenu();
	mnuSideBar.AppendMenu(MF_STRING|MF_OWNERDRAW,10,"Item 1");
	mnuSideBar.AppendMenu(MF_SEPARATOR|MF_OWNERDRAW,0,"");
	mnuSideBar.AppendMenu(MF_STRING|MF_OWNERDRAW,11,"Item 2");
 	mnuSideBar.AppendMenu(MF_SEPARATOR|MF_OWNERDRAW,0,"");
	mnuSideBar.AppendMenu(MF_STRING|MF_OWNERDRAW,12,"Item 3 ");
	mnuSideBar.SetSideBarColor(RGB(0,0,255),RGB(0,0,0));
	mnuSideBar.AppendMenu(MF_STRING|MF_OWNERDRAW,13,"Item 4");
	mnuSideBar.AppendMenu(MF_STRING|MF_OWNERDRAW,14,"Item 5");
	mnuSideBar.AppendMenu(MF_STRING|MF_OWNERDRAW,15,"Item 6");
	mnuSideBar.AppendMenu(MF_STRING|MF_OWNERDRAW,16,"Item 7      ");
	return 1;

}


void CDemoDlg::OnRButtonDown(UINT nFlags, CPoint point)
{

	ClientToScreen(&point);
	mnuSideBar.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,
		this,NULL);


}

void CDemoDlg::MenuHandler(UINT id)
{

	switch(id)
	{

	case 10:
		MessageBox("Item 1","SideBarMenu Demo");
		break;
	case 11:
		MessageBox("Item 2","SideBarMenu Demo");
		break;
	case 12:
		MessageBox("Item 3","SideBarMenu Demo");
		break;
	case 13:
		MessageBox("Item 4","SideBarMenu Demo");
		break;
	case 14:
		MessageBox("Item 5","SideBarMenu Demo");
		break;
	case 15:
		MessageBox("Item 6","SideBarMenu Demo");
		break;
	case 16:
		MessageBox("Item 7","SideBarMenu Demo");
		break;

	}


}

BEGIN_MESSAGE_MAP(CDemoDlg,CDialog)

ON_WM_RBUTTONDOWN()
ON_COMMAND_RANGE(10,16,MenuHandler)

END_MESSAGE_MAP()



