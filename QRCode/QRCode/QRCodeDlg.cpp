
// QRCodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QRCode.h"
#include "QRCodeDlg.h"
#include "afxdialogex.h"

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


// CQRCodeDlg �Ի���




CQRCodeDlg::CQRCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQRCodeDlg::IDD, pParent)
	, encodeData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQRCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, encodeData);
}

BEGIN_MESSAGE_MAP(CQRCodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CQRCodeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CQRCodeDlg ��Ϣ�������

BOOL CQRCodeDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQRCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQRCodeDlg::OnPaint()
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
HCURSOR CQRCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQRCodeDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(encodeData.IsEmpty())
	{
		AfxMessageBox(_T("����Ϊ��"));
		return;
	}
		
	const char* data=NULL;
	int len = WideCharToMultiByte( CP_UTF8 , 0 , encodeData , encodeData.GetLength() , NULL , 0 , NULL , NULL );
    char* pAscii =new char[len+1];
    len = WideCharToMultiByte(  CP_UTF8 , 0 , encodeData , encodeData.GetLength() , pAscii , len +1 , NULL ,NULL );
    pAscii[len] = 0; 
	data = (const char*)pAscii;

	mainrun(data);
	//��ʾͼ��
	CImage image;
	CRect rect;
	//����·������ͼƬ
	image.Load(_T("d:\\test.bmp"));
	//��ȡPicture Control�ؼ��Ĵ�С
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);
	//���ͻ���ѡ�е��ؼ���ʾ�ľ���������
	ScreenToClient(&rect);
	//�����ƶ����ؼ���ʾ������
	//GetDlgItem(IDC_QRCODE_STATIC)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);
	CWnd *pWnd = NULL;
	pWnd	= GetDlgItem(IDC_STATIC);//��ȡ�ؼ����
	pWnd->GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С

	CDC *pDc = NULL;
	pDc	= pWnd->GetDC();//��ȡpicture��DC

	image.Draw(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������

	ReleaseDC(pDc);
	UpdateData(FALSE);


}
