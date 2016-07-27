
// SectorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sector.h"
#include "SectorDlg.h"
#include "afxdialogex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSectorDlg �Ի���



CSectorDlg::CSectorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSectorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSectorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CSectorDlg::OnBnClickedButtonGenerate)
END_MESSAGE_MAP()


// CSectorDlg ��Ϣ�������

BOOL CSectorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CRect rcW;
	GetWindowRect(&rcW);
	CRect rcC;
	GetClientRect(&rcC);
	MoveWindow(0, 0, 800 + rcW.Width() - rcC.Width(), 800 + 30 + rcW.Height() - rcC.Height());

	ModifyStyle(0, WS_CLIPCHILDREN);

	m_draw.Create(IDD_DIALOG_DRAW);
	m_draw.MoveWindow(0, 30, 800, 800);

	GetDlgItem(IDC_STATIC_1)->MoveWindow(208, 6, 60, 22);
	GetDlgItem(IDC_EDIT_X)->MoveWindow(270, 4, 50, 22);
	GetDlgItem(IDC_STATIC_2)->MoveWindow(335, 6, 15, 22);
	GetDlgItem(IDC_EDIT_Y)->MoveWindow(350, 4, 50, 22);
	GetDlgItem(IDC_STATIC_3)->MoveWindow(415, 6, 30, 22);
	GetDlgItem(IDC_EDIT_RANGE)->MoveWindow(445, 4, 50, 22);
	GetDlgItem(IDC_STATIC_4)->MoveWindow(510, 6, 30, 22);
	GetDlgItem(IDC_EDIT_ANGLE)->MoveWindow(540, 4, 50, 22);
	GetDlgItem(IDC_BUTTON_GENERATE)->MoveWindow(600, 2, 198, 26);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSectorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSectorDlg::OnBnClickedButtonGenerate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int MAX_X = 80, MAX_Y = 80;
	std::vector<std::vector<int> >& nodes = m_draw.m_nodes;
	nodes.resize(MAX_X);
	for (int x = 0; x < MAX_X; x++)
	{
		nodes[x].resize(MAX_Y);
	}

	//��֪��
	CString str;
	GetDlgItem(IDC_EDIT_X)->GetWindowText(str);
	double targetX = _ttoi(str.GetBuffer());
	GetDlgItem(IDC_EDIT_Y)->GetWindowText(str);
	double targetY = _ttoi(str.GetBuffer());
	GetDlgItem(IDC_EDIT_RANGE)->GetWindowText(str);
	double range = _ttoi(str.GetBuffer());
	GetDlgItem(IDC_EDIT_ANGLE)->GetWindowText(str);
	double angle = _ttoi(str.GetBuffer());

	if ((targetX == 0 && targetY == 0) || range <= 0 || angle <= 0)
	{
		return;
	}

	double PI = 3.14159265358979323846;

	//�жϵ��Ƿ��������ڲ��������е����е㣬ÿ�����жϣ�
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			//�жϵ�
			double checkX = x - MAX_X / 2;
			double checkY = -y + MAX_Y / 2;

			if (pow(checkX, 2) + pow(checkY, 2) <= pow(range, 2) &&
				(checkX * targetX + checkY * targetY) >= sqrt(pow(checkX, 2) + pow(checkY, 2)) * sqrt(pow(targetX, 2) + pow(targetY, 2)) * cos(angle * PI / 180))
			{
				//������
				nodes[x][y] = 1;
			}
			else
			{
				//������
				nodes[x][y] = 0;
			}

			if (checkX == 0 && checkY == 0)
			{
				//ԭ��
				nodes[x][y] = 2;
			}
			else if (checkX == targetX && checkY == targetY)
			{
				//Ŀ���
				nodes[x][y] = 3;
			}
		}
	}

	m_draw.Invalidate();
}
