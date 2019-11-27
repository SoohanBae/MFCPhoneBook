#include "stdafx.h"
#include "MFCPhoneBook.h"
#include "MFCPhoneBookDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CMFCPhoneBookDlg::CMFCPhoneBookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPHONEBOOK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCPhoneBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EMPLOYEE_LIST, m_employeeList);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_searchEdit);
}

BEGIN_MESSAGE_MAP(CMFCPhoneBookDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE_CSV_BTN, &CMFCPhoneBookDlg::OnBnClickedSaveCsvBtn)
	ON_BN_CLICKED(IDC_OEPN_CSV_BTN, &CMFCPhoneBookDlg::OnBnClickedOepnCsvBtn)
	ON_BN_CLICKED(IDC_ADD_ELEMENT_BTN, &CMFCPhoneBookDlg::OnBnClickedAddElementBtn)
	ON_BN_CLICKED(IDC_SAVE_SEARCH_CSV_BTN, &CMFCPhoneBookDlg::OnBnClickedSaveSearchCsvBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CMFCPhoneBookDlg::OnEnChangeSearchEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_EMPLOYEE_LIST, &CMFCPhoneBookDlg::OnNMDblclkEmployeeList)
END_MESSAGE_MAP()


// CMFCPhoneBookDlg 메시지 처리기

BOOL CMFCPhoneBookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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


	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		


	CRect rect;
	m_employeeList.GetClientRect(&rect);
	
	for (const CString& column : m_employeeColumn)
	{
		m_employeeList.InsertColumn(0, column, LVCFMT_CENTER, rect.Width()/ (sizeof(m_employeeColumn) / sizeof(*m_employeeColumn)) - 3);
	}
	m_employeeList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCPhoneBookDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCPhoneBookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CMFCPhoneBookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCPhoneBookDlg::csvToListControl(const CString& fileName) 
{
	FileManager::CreateClass();
	FileManager* fileManager = FileManager::GetMgr();
	m_employeeOriginal = fileManager->CsvTo2dVectorCString(fileName);
	RePaint();
}

void CMFCPhoneBookDlg::ListControlToCsv(const CString& fileName) 
{
	vector<vector<CString>> listControlVector;

	for (int i = 0; i < m_employeeList.GetItemCount(); i++)
	{
		vector<CString> row;
		for (size_t j = 0; j < sizeof(m_employeeColumn) / sizeof(m_employeeColumn[0]); j++)
		{
			row.push_back(m_employeeList.GetItemText(i, j));
		}
		listControlVector.push_back(row);		
	}

	FileManager::CreateClass();
	FileManager* fileManager = FileManager::GetMgr();
	fileManager->TwoDVectorCStringToCsv(listControlVector, fileName);
}


void CMFCPhoneBookDlg::OriginalToCsv(const CString& fileName)
{
	FileManager::CreateClass();
	FileManager* fileManager = FileManager::GetMgr();
	fileManager->TwoDVectorCStringToCsv(m_employeeOriginal, fileName);
}


vector<bool> CMFCPhoneBookDlg::GetMatchSearchTextRow()
{
	vector<bool> isMatchSearchTextRow(m_employeeOriginal.size());

	for (size_t i = 0; i < m_employeeOriginal.size(); i++)
	{
		isMatchSearchTextRow[i] = false;

		for (size_t j = 0; j < m_employeeOriginal[i].size(); j++)
		{
			CString itemText = m_employeeOriginal[i][j];
			CString searchText = {};
			m_searchEdit.GetWindowTextW(searchText);

			int MatchSearchTextIndex = itemText.Find(searchText);
			
			if (MatchSearchTextIndex != -1) {
				isMatchSearchTextRow[i] = true;
				break;
			}
		}
	}

	return isMatchSearchTextRow;
}


void CMFCPhoneBookDlg::RePaint()
{
	m_employeeList.SetRedraw(false);

	vector<bool> isMatchSearchTextRow = GetMatchSearchTextRow();
	m_employeeList.DeleteAllItems();

	for (size_t i = 0; i < m_employeeOriginal.size(); i++)
	{
		if (!isMatchSearchTextRow[i])
			continue;

		int PillarIndex = m_employeeList.InsertItem(i,m_employeeOriginal[i][0]);

		for (size_t j = 1; j < m_employeeOriginal[i].size(); j++)
		{
			m_employeeList.SetItemText(PillarIndex, j, m_employeeOriginal[i][j]);
		}
	}

	m_employeeList.SetRedraw(true);

}


void CMFCPhoneBookDlg::OnBnClickedAddElementBtn()
{
	MFCPhoneBookSubDlg mfcPhoneBookSubDlg;
	mfcPhoneBookSubDlg.m_employeeOriginal = &m_employeeOriginal;
	mfcPhoneBookSubDlg.m_modeNumber = mfcPhoneBookSubDlg.ADD_MODE;
	mfcPhoneBookSubDlg.DoModal();
	RePaint();
}


void CMFCPhoneBookDlg::OnBnClickedSaveCsvBtn()
{
	const TCHAR szFilter[] = TEXT("All Files (*.*)|*.*|");
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY + OFN_FILEMUSTEXIST, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		ListControlToCsv(filePath + TEXT(".csv"));
	}
}


void CMFCPhoneBookDlg::OnBnClickedSaveSearchCsvBtn()
{
	const TCHAR szFilter[] = TEXT("All Files (*.*)|*.*|");
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY + OFN_FILEMUSTEXIST, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		OriginalToCsv(filePath + TEXT(".csv"));
	}
}



void CMFCPhoneBookDlg::OnBnClickedOepnCsvBtn()
{
	const TCHAR szFilter[] = TEXT("CSV Files (*.csv)|*.csv|");
	CFileDialog dlg(TRUE, TEXT("csv"), TEXT("*.csv"), OFN_HIDEREADONLY + OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		csvToListControl(filePath);
	}

}


void CMFCPhoneBookDlg::OnEnChangeSearchEdit()
{
	RePaint();
}


void CMFCPhoneBookDlg::OnNMDblclkEmployeeList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	int selectIndex = pNMItemActivate->iItem;
	int col = pNMItemActivate->iSubItem;


	MFCPhoneBookSubDlg mfcPhoneBookSubDlg;
	mfcPhoneBookSubDlg.m_employeeOriginal = &m_employeeOriginal;
	mfcPhoneBookSubDlg.m_employeeIndex = selectIndex;
	mfcPhoneBookSubDlg.m_modeNumber = mfcPhoneBookSubDlg.SELECT_MODE;
	mfcPhoneBookSubDlg.DoModal();
}
