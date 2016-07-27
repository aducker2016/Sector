// DialogDraw.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sector.h"
#include "DialogDraw.h"
#include "afxdialogex.h"


// CDialogDraw �Ի���

IMPLEMENT_DYNAMIC(CDialogDraw, CDialogEx)

CDialogDraw::CDialogDraw(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogDraw::IDD, pParent)
{

}

CDialogDraw::~CDialogDraw()
{
}

void CDialogDraw::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogDraw, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDialogDraw ��Ϣ�������


BOOL CDialogDraw::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}


void CDialogDraw::OnPaint()
{
	CPaintDC dc(this); 

	CRect rc;
	GetClientRect(&rc);

	CDC memDc;
	memDc.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	memDc.SelectObject(&bmp);

	CPen pen(PS_SOLID, 1, RGB(100, 100, 100));
	memDc.SelectObject(&pen);

	CBrush bRed(RGB(255, 0, 0));
	CBrush bBlue(RGB(0, 0, 255));
	CBrush bGreen(RGB(0, 255, 0));
	CBrush bBackground(RGB(253, 245, 230));

	for (size_t x = 0; x < m_nodes.size(); x++)
	{
		for (size_t y = 0; y < m_nodes[x].size(); y++)
		{
			switch (m_nodes[x][y])
			{
			case 0:
				//����
				memDc.SelectObject(&bBackground);
				break;
			case 1:
				//��������
				memDc.SelectObject(&bGreen);
				break;
			case 2:
				//���
				memDc.SelectObject(&bRed);
				break;
			case 3:
				//�յ�
				memDc.SelectObject(&bBlue);
				break;
			}

			memDc.Rectangle(x * 10, y * 10, (x + 1) * 10 + 1, (y + 1) * 10 + 1);
		}
	}

	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDc, 0, 0, SRCCOPY);
}
