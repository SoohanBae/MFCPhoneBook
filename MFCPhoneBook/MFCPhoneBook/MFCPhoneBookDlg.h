
// MFCPhoneBookDlg.h: 헤더 파일
//

#pragma once
#include <iostream>
#include "FileManager.h"
#include "MFCPhoneBookSubDlg.h"
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

	//사용자 생성 함수
	void csvToListControl(const CString& fileName);
	void ListControlToCsv(const CString& fileName);
	void OriginalToCsv(const CString& fileName);
	vector<bool> GetMatchSearchTextRow();
	void RePaint();

	//이벤트 처리
	afx_msg void OnBnClickedAddElementBtn();
	afx_msg void OnBnClickedSaveCsvBtn();
	afx_msg void OnBnClickedSaveSearchCsvBtn();
	afx_msg void OnBnClickedOepnCsvBtn();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnNMDblclkEmployeeList(NMHDR *pNMHDR, LRESULT *pResult);

	CString m_employeeColumn[5] = { TEXT("부서"), TEXT("직함"), TEXT("휴대전화"), TEXT("이름"), TEXT("아이디") };//역순 입력
	vector<vector<CString>> m_employeeOriginal = {};
	CListCtrl m_employeeList;
	CEdit m_searchEdit;
};
