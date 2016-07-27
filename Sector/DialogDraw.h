#pragma once

#include <vector>

// CDialogDraw �Ի���

class CDialogDraw : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDraw)

public:
	CDialogDraw(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogDraw();

// �Ի�������
	enum { IDD = IDD_DIALOG_DRAW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();

	std::vector<std::vector<int> > m_nodes;
};
