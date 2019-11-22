
// MFCPhoneBookDlg.h: 헤더 파일
//

#pragma once
#include <iostream>
#include "CFileManager.h"

// CMFCPhoneBookDlg 대화 상자
class CMFCPhoneBookDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCPhoneBookDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPHONEBOOK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	//역순 입력
	CString m_employeeColumn[5] = { TEXT("부서"), TEXT("직함"), TEXT("휴대전화"), TEXT("이름"), TEXT("번호") };
	
	void csvToListControl(const CString& fileName);
	void ListControlToCsv(const CString& fileName);

	CListCtrl m_employeeList;
	afx_msg void OnLvnItemchangedList6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSaveCsvBtn();
	afx_msg void OnBnClickedOepnCsvBtn();
};
