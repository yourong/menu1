/*
********** Author : Mohammed Nisamudheen S.  **********
********** Email  : nizam_clt@rediffmail.com **********
********** Date   : 21.10.2004               **********
********** URL    : www.uslindia.com         **********
*/

#include "SideBarMenu.h"


CSideBarMenu::CSideBarMenu()
{
    lstrcpy(m_SideBarText, "SideBar"); 
	m_SideBarStartColor   = RGB(128,128,128);
	m_SideBarEndColor     = RGB(0,0,0);
	m_SideBarTextColor    = RGB(128,128,128);
	m_MenuBkgColor        = RGB(0,0,0);
	m_HiLitColor          = RGB(128,128,128);
	m_TextColor           = RGB(128,128,128);
	m_HiLitTextColor      = RGB(225,225,225);
	
}

CSideBarMenu::~CSideBarMenu()
{

	this->DestroyMenu();
	
}


void CSideBarMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
   // all items are of fixed size except menu separator
   LPCSTR itemData = (LPCSTR)lpMIS->itemData;
   static INT itemLen;
  
   if(lstrlen(itemData)==0)
	   lpMIS->itemHeight = 8;
   else
   	   lpMIS->itemHeight = 20;

   if(lstrlen(itemData) > itemLen)
   	   itemLen = lstrlen(itemData);
 
   lpMIS->itemWidth = itemLen * 10;
   
     
}

void CSideBarMenu::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{

   CDC dc;
   int oldMode;
   int oldTextColor;
   COLORREF cr;
   LPCTSTR lpszText = (LPCTSTR) lpDIS->itemData;


   CRect rectFull(lpDIS->rcItem); 
   CRect rectText(rectFull.left+30,rectFull.top,rectFull.right,rectFull.bottom);
   CRect rectHiLite =rectText;
   rectHiLite.left-=10;
   rectHiLite.right-=4;
   rectHiLite.bottom-=2;


    dc.Attach(lpDIS->hDC);
    oldMode=dc.SetBkMode(TRANSPARENT);
   
    
   if (lpDIS->itemAction & ODA_DRAWENTIRE)
   {
      // Paint the color item in the color requested
	   cr = m_TextColor;
       CBrush br(m_MenuBkgColor);
       dc.FillRect(&rectFull, &br);
   }

   if ((lpDIS->itemState & ODS_SELECTED) &&
      (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
   {
      // item has been selected - hilite frame

	   cr= m_HiLitTextColor;
       CBrush br(m_HiLitColor);
	   CBrush *old = dc.SelectObject(&br);
	   dc.FillRect(&rectHiLite, &br);
	   //dc.RoundRect(&rectHiLite,CPoint(16,16));
	   dc.SelectObject(old);
   }

   if (!(lpDIS->itemState & ODS_SELECTED) &&
      (lpDIS->itemAction & ODA_SELECT))
   {
      // Item has been de-selected 
	   cr = m_TextColor;
       CBrush br(m_MenuBkgColor);
       dc.FillRect(&rectHiLite, &br);
   }

   oldTextColor=dc.SetTextColor(cr);

    dc.DrawText(
      lpszText,
      strlen(lpszText),
      &rectText,
      DT_SINGLELINE|DT_VCENTER);

	//Generating the sidebar with gradient
   if (lpDIS->itemAction & ODA_DRAWENTIRE){

	   CRect rectG ;
       dc.GetClipBox(rectG);
	   

	   int p,q;
       int r1,g1,b1;
	   int r2,g2,b2;
       int r,g,b;
	   r1 = GetRValue(m_SideBarStartColor);
	   g1 = GetGValue(m_SideBarStartColor);
	   b1 = GetBValue(m_SideBarStartColor);

	   r2 = GetRValue(m_SideBarEndColor);
	   g2 = GetGValue(m_SideBarEndColor);
	   b2 = GetBValue(m_SideBarEndColor);
	   

   	   for(p=rectG.bottom; p>rectG.top; p--){
   
		   r = r2 + (p * (r1-r2) / rectG.Height());
      	   g = g2 + (p * (g1-g2) / rectG.Height());
      	   b = b2 + (p * (b1-b2) / rectG.Height());
	  	   for(q=0;q<20;q++)
			   dc.SetPixel(q,p,RGB(r,g,b));

	   }

       LOGFONT lf;
	   CFont font;

	   memset (&lf, 0, sizeof (LOGFONT));
	   lf.lfOrientation = lf.lfEscapement = 900;// 90 degree rotation
	   lstrcpy ( lf.lfFaceName, _T("Arial") );
	
	   lf.lfHeight = 14;
	   lf.lfWeight = FW_DEMIBOLD;
	
	   font.CreateFontIndirect ( &lf );
	   CFont * OldFont = dc.SelectObject ( &font );
	   COLORREF oldColor = dc.SetTextColor(RGB(128,128,128));
	   rectG.left+=3;
	   dc.SetTextColor(m_SideBarTextColor);
   	   dc.DrawText ( m_SideBarText, &rectG, DT_BOTTOM | DT_LEFT | DT_SINGLELINE );	
	   dc.SetTextColor(oldColor);
	   dc.SelectObject(OldFont);
   }

   dc.SetBkMode(oldMode);
   dc.SetTextColor(oldTextColor);

   //Handling the menu separators if any
   if(lstrlen(lpszText)==0 )
   {

	   CBrush b(RGB(255,0,0));
	   CPen p;

	   COLORREF color = RGB(255,255,255); //separator color

	   color -= m_MenuBkgColor;
	   p.CreatePen(PS_SOLID , 1, color);
	   CBrush *b1 = dc.SelectObject(&b);
       CPen *p1 = dc.SelectObject(&p);

	   dc.MoveTo(rectHiLite.left+2,rectHiLite.top+2);
	   dc.LineTo(rectHiLite.left+rectHiLite.Width(),
		         rectHiLite.top+2);

	   dc.SelectObject(b1);
	   dc.SelectObject(p1);
	   
   }


   dc.Detach();

        
}

void CSideBarMenu::SetSideBarText(LPCSTR text)
{

	lstrcpy(m_SideBarText,text);
}

void CSideBarMenu::SetSideBarTextColor(COLORREF color)
{

	m_SideBarTextColor = color;

}



void CSideBarMenu::SetHiLitColor(COLORREF color)
{
	m_HiLitColor = color;
}



void CSideBarMenu::SetMenuBkgColor(COLORREF color)
{
	m_MenuBkgColor = color;

}

void CSideBarMenu::SetSideBarColor(COLORREF start, COLORREF end)
{

	m_SideBarStartColor = start;
	m_SideBarEndColor  = end;


}


void CSideBarMenu::SetMenuTextColor(COLORREF color)
{
	m_TextColor = color;
}


void CSideBarMenu::SetTextHiLitColor(COLORREF color)
{
	m_HiLitTextColor= color;
}

