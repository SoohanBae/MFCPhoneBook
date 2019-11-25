#pragma once


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
	CStatic m_employeePicture;
};
