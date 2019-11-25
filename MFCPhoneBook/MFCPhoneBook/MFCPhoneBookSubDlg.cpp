// MFCPhoneBookSubDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCPhoneBook.h"
#include "MFCPhoneBookSubDlg.h"
#include "afxdialogex.h"


// MFCPhoneBookSubDlg 대화 상자

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
	DDX_Control(pDX, IDC_EMPLOYEE_PICTURE, m_employeePicture);
}


BEGIN_MESSAGE_MAP(MFCPhoneBookSubDlg, CDialogEx)
	ON_BN_CLICKED(IDC_FILE_CHOOSE_BTN, &MFCPhoneBookSubDlg::OnBnClickedFileChooseBtn)
END_MESSAGE_MAP()


// MFCPhoneBookSubDlg 메시지 처리기


void MFCPhoneBookSubDlg::OnBnClickedFileChooseBtn()
{
	const TCHAR szFilter[] = TEXT("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |");
	CFileDialog dlg(TRUE, NULL,NULL, OFN_HIDEREADONLY + OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		HBITMAP hBitmap = NULL;
		hBitmap = (HBITMAP)LoadImage(0, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		m_employeePicture.SetBitmap(hBitmap);


	}
}
