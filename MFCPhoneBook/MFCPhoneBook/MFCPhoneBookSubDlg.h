#pragma once
#include <vector>
#include <iostream>

// MFCPhoneBookSubDlg 대화 상자

class MFCPhoneBookSubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MFCPhoneBookSubDlg)

public:
	MFCPhoneBookSubDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MFCPhoneBookSubDlg();


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPHONEBOOK_SUB_DLALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedFileChooseBtn();
	
	void EmployeePicutrePrint(const CString& filePath);
	void EmployeePicutreCopyResource(const CString& inputFilePath);
	void ShowSelectMode();
	void ShowEditMode();
	void ShowAddMode();
	void Repaint();
	bool Repaint(const int& modeNumber);
	void ShowSelectEmployee();
	void AddEmployee();
	void EditEmployee();

	
	CMFCButton m_prevBtn;
	CMFCButton m_nextBtn;
	CEdit m_numberEdit;
	CEdit m_nameEdit;
	CEdit m_phoneEdit;
	CEdit m_rankEdit;
	CEdit m_DepartmentEdit;
	CMFCButton m_undoBtn;
	CMFCButton m_deleteBtn;
	CMFCButton m_editBtn;
	CMFCButton m_fileChooseBtn;
	CImage m_employeeImage;


	const int SELECT_MODE = 1;
	const int EDIT_MODE = 2;
	const int ADD_MODE = 3;

	std::vector<std::vector<CString>>* m_employeeOriginal;
	std::vector<std::vector<CString>> m_employeeTmp;
	int m_employeeIndex = 0;
	int m_modeNumber = 1;
	CString m_employeePicturePath = TEXT("");

private:
	
public:
	afx_msg void OnBnClickedPrevEmployeeBtn();
	afx_msg void OnBnClickedNextEmployeeBtn();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedEditBtn();
	afx_msg void OnBnClickedDeleteBtn();
	CStatic m_noticeText;
	afx_msg void OnBnClickedUndoBtn();
};
