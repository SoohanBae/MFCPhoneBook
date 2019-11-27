#include "stdafx.h"
#include "MFCPhoneBook.h"
#include "MFCPhoneBookSubDlg.h"
#include "afxdialogex.h"
#include <fstream>

IMPLEMENT_DYNAMIC(MFCPhoneBookSubDlg, CDialogEx)

MFCPhoneBookSubDlg::MFCPhoneBookSubDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPHONEBOOK_SUB_DLALOG, pParent)
{
}

MFCPhoneBookSubDlg::~MFCPhoneBookSubDlg()
{
}

void MFCPhoneBookSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PREV_EMPLOYEE_BTN, m_prevBtn);
	DDX_Control(pDX, IDC_NEXT_EMPLOYEE_BTN, m_nextBtn);
	DDX_Control(pDX, IDC_Number_EDITTEEXT, m_numberEdit);
	DDX_Control(pDX, IDC_NAME_EDITTEXT, m_nameEdit);
	DDX_Control(pDX, IDC_PHONE_EDITTEXT, m_phoneEdit);
	DDX_Control(pDX, IDC_RANK_EDITTEXT, m_rankEdit);
	DDX_Control(pDX, IDC_DEPARTMENT_EDITTEXT, m_DepartmentEdit);
	DDX_Control(pDX, IDC_UNDO_BTN, m_undoBtn);
	DDX_Control(pDX, IDC_DELETE_BTN, m_deleteBtn);
	DDX_Control(pDX, IDC_EDIT_BTN, m_editBtn);
	DDX_Control(pDX, IDC_FILE_CHOOSE_BTN, m_fileChooseBtn);
	DDX_Control(pDX, IDC_NOTICE_TEXT, m_noticeText);
	Repaint();
}


BEGIN_MESSAGE_MAP(MFCPhoneBookSubDlg, CDialogEx)
	ON_BN_CLICKED(IDC_FILE_CHOOSE_BTN, &MFCPhoneBookSubDlg::OnBnClickedFileChooseBtn)
	ON_BN_CLICKED(IDC_PREV_EMPLOYEE_BTN, &MFCPhoneBookSubDlg::OnBnClickedPrevEmployeeBtn)
	ON_BN_CLICKED(IDC_NEXT_EMPLOYEE_BTN, &MFCPhoneBookSubDlg::OnBnClickedNextEmployeeBtn)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_EDIT_BTN, &MFCPhoneBookSubDlg::OnBnClickedEditBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN, &MFCPhoneBookSubDlg::OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDC_UNDO_BTN, &MFCPhoneBookSubDlg::OnBnClickedUndoBtn)
END_MESSAGE_MAP()


// MFCPhoneBookSubDlg 메시지 처리기


void MFCPhoneBookSubDlg::OnBnClickedFileChooseBtn()
{
	const TCHAR szFilter[] = TEXT("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |");
	CFileDialog dlg(TRUE, NULL,NULL, OFN_HIDEREADONLY + OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		EmployeePicutrePrint(filePath);
		EmployeePicutreCopyResource(filePath);
	}
}


void MFCPhoneBookSubDlg::EmployeePicutrePrint(const CString& filePath) 
{
	CClientDC dc(this);
	m_employeeImage.Destroy();
	HRESULT a = m_employeeImage.Load(filePath);
	if(a == S_OK)
		m_employeeImage.Draw(dc, 341, 33, 100, 130);
	else {
		m_employeeImage.Load(TEXT("resource\\empty.jpg"));
		m_employeeImage.Draw(dc, 341, 33, 100, 130);
	}
}

void MFCPhoneBookSubDlg::EmployeePicutreCopyResource(const CString& inputFilePath) 
{
	SYSTEMTIME cur_time;
	GetLocalTime(&cur_time);

	CString strTime;
	strTime.Format(TEXT("%02d%02d%02d%03d"), cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);

	std::wstring inputFile = inputFilePath.operator LPCWSTR();
	CString inputFileName = inputFilePath.Right(inputFilePath.GetLength() - inputFilePath.ReverseFind('\\') - 1);

	m_employeePicturePath = TEXT("resource\\") + strTime + inputFileName;

	std::ifstream  src(inputFile, std::ios::binary);
	std::ofstream  dst(m_employeePicturePath, std::ios::binary);
	dst << src.rdbuf();
}

void MFCPhoneBookSubDlg::ShowSelectMode()
{
	m_numberEdit.EnableWindow(false);
	m_nameEdit.EnableWindow(false);
	m_phoneEdit.EnableWindow(false);
	m_rankEdit.EnableWindow(false);
	m_DepartmentEdit.EnableWindow(false);

	m_undoBtn.EnableWindow(false);
	m_fileChooseBtn.ShowWindow(false);
	m_deleteBtn.ShowWindow(true);
	m_editBtn.SetWindowTextW(TEXT("수정"));

	m_prevBtn.ShowWindow(true);
	m_nextBtn.ShowWindow(true);
	m_noticeText.SetWindowTextW(TEXT(""));

	ShowSelectEmployee();
}


void MFCPhoneBookSubDlg::ShowEditMode()
{
	m_numberEdit.EnableWindow(true);
	m_nameEdit.EnableWindow(true);
	m_phoneEdit.EnableWindow(true);
	m_rankEdit.EnableWindow(true);
	m_DepartmentEdit.EnableWindow(true);

	m_undoBtn.EnableWindow(false);
	m_fileChooseBtn.ShowWindow(true);
	m_deleteBtn.ShowWindow(true);
	m_editBtn.SetWindowTextW(TEXT("저장"));

	m_prevBtn.ShowWindow(false);
	m_nextBtn.ShowWindow(false);
	m_noticeText.SetWindowTextW(TEXT(""));
}


void MFCPhoneBookSubDlg::ShowAddMode()
{
	m_numberEdit.EnableWindow(true);
	m_nameEdit.EnableWindow(true);
	m_phoneEdit.EnableWindow(true);
	m_rankEdit.EnableWindow(true);
	m_DepartmentEdit.EnableWindow(true);

	m_undoBtn.EnableWindow(false);
	m_fileChooseBtn.ShowWindow(true);
	m_deleteBtn.ShowWindow(false);
	m_editBtn.SetWindowTextW(TEXT("추가"));

	m_prevBtn.ShowWindow(false);
	m_nextBtn.ShowWindow(false);
	m_noticeText.SetWindowTextW(TEXT(""));

}

void MFCPhoneBookSubDlg::Repaint()
{
	if (m_modeNumber == SELECT_MODE)
		ShowSelectMode(); 
	else if (m_modeNumber == EDIT_MODE)
		ShowEditMode();
	else if (m_modeNumber == ADD_MODE)
		ShowAddMode();
}

bool MFCPhoneBookSubDlg::Repaint(const int & modeNumber)
{
	if(modeNumber < 1 || modeNumber > 3)
		return false;

	m_modeNumber = modeNumber;

	Repaint();
	Invalidate(true);
	return true;
}

void MFCPhoneBookSubDlg::ShowSelectEmployee()
{
	if (m_employeeIndex < 0) {
		m_employeeIndex = 0;
	}
	if (m_employeeIndex > m_employeeOriginal->size() - 1) {
		m_employeeIndex = m_employeeOriginal->size() - 1;
	}
	if (m_employeeIndex == -1) {
		return;
	}

	m_numberEdit.SetWindowTextW((*m_employeeOriginal)[m_employeeIndex][0]);
	m_nameEdit.SetWindowTextW((*m_employeeOriginal)[m_employeeIndex][1]);
	m_phoneEdit.SetWindowTextW((*m_employeeOriginal)[m_employeeIndex][2]);
	m_rankEdit.SetWindowTextW((*m_employeeOriginal)[m_employeeIndex][3]);
	m_DepartmentEdit.SetWindowTextW((*m_employeeOriginal)[m_employeeIndex][4]);

	if ((*m_employeeOriginal)[m_employeeIndex].size() == 6) {
		EmployeePicutrePrint((*m_employeeOriginal)[m_employeeIndex][5]);
	}

	m_prevBtn.EnableWindow(true);
	m_nextBtn.EnableWindow(true);

	if (m_employeeIndex == 0) {
		m_prevBtn.EnableWindow(false);
	}

	if (m_employeeIndex == (*m_employeeOriginal).size() - 1) {
		m_nextBtn.EnableWindow(false);
	}
}

void MFCPhoneBookSubDlg::OnBnClickedPrevEmployeeBtn()
{
	if (m_employeeIndex > 0) {
		m_employeeIndex--;
	}
	Repaint();
}


void MFCPhoneBookSubDlg::OnBnClickedNextEmployeeBtn()
{
	if (m_employeeIndex < m_employeeOriginal->size()-1) {
		m_employeeIndex++;
	}
	Repaint();
}


void MFCPhoneBookSubDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if(m_modeNumber == SELECT_MODE)
		EmployeePicutrePrint((*m_employeeOriginal)[m_employeeIndex][5]);
	else
		EmployeePicutrePrint(TEXT("resource\\empty.jpg"));
}


void MFCPhoneBookSubDlg::OnBnClickedEditBtn()
{
	if (m_modeNumber == ADD_MODE) {
		AddEmployee();
	}
	else if (m_modeNumber == EDIT_MODE) {
		EditEmployee();
	}
	else if (m_modeNumber == SELECT_MODE) {
		Repaint(EDIT_MODE);
	}
}


void MFCPhoneBookSubDlg::OnBnClickedDeleteBtn()
{
	m_employeeTmp = *m_employeeOriginal;
	m_employeeOriginal->erase(m_employeeOriginal->begin() + m_employeeIndex);

	Repaint(SELECT_MODE);
	m_noticeText.SetWindowTextW(TEXT("아이디 : ") + m_employeeTmp[m_employeeIndex][0] + TEXT(" 데이터가 삭제되었습니다."));
	m_undoBtn.EnableWindow(true);
}


void MFCPhoneBookSubDlg::OnBnClickedUndoBtn()
{
	*m_employeeOriginal = m_employeeTmp;
	Repaint();
}


void MFCPhoneBookSubDlg::AddEmployee()
{
	m_employeeTmp = *m_employeeOriginal;
	std::vector<CString> employee = {};
	CString textArray[5] = {};
	
	m_numberEdit.GetWindowTextW(textArray[0]);
	m_nameEdit.GetWindowTextW(textArray[1]);
	m_phoneEdit.GetWindowTextW(textArray[2]);
	m_rankEdit.GetWindowTextW(textArray[3]);
	m_DepartmentEdit.GetWindowTextW(textArray[4]);

	for (const auto& text : textArray)
	{
		employee.push_back(text);
	}
	employee.push_back(m_employeePicturePath);
	m_employeeOriginal->push_back(employee);
	
	m_employeePicturePath = TEXT("");
	m_employeeIndex = m_employeeOriginal->size() - 1;

	Repaint(SELECT_MODE);
	m_noticeText.SetWindowTextW(TEXT("아이디 : ") + (*m_employeeOriginal)[m_employeeIndex][0] + TEXT(" 데이터가 추가되었습니다."));
	m_undoBtn.EnableWindow(true);
}

void MFCPhoneBookSubDlg::EditEmployee()
{
	m_employeeTmp = *m_employeeOriginal;
	CString textArray[5] = {};

	m_numberEdit.GetWindowTextW(textArray[0]);
	m_nameEdit.GetWindowTextW(textArray[1]);
	m_phoneEdit.GetWindowTextW(textArray[2]);
	m_rankEdit.GetWindowTextW(textArray[3]);
	m_DepartmentEdit.GetWindowTextW(textArray[4]);

	for (int i = 0; i < 5; i ++)
	{
		(*m_employeeOriginal)[m_employeeIndex][i] = textArray[i];
	}

	if (m_employeePicturePath != TEXT("")) 
	{
		(*m_employeeOriginal)[m_employeeIndex][5] = m_employeePicturePath;
	}
	
	m_employeePicturePath = TEXT("");

	Repaint(SELECT_MODE);
	m_noticeText.SetWindowTextW(TEXT("아이디 : ") + m_employeeTmp[m_employeeIndex][0] + TEXT(" 데이터가 수정되었습니다."));
	m_undoBtn.EnableWindow(true);
}
