// DlgCommonProg.h : �w�b�_ �t�@�C��
// CG: ���̃t�@�C���́u�v���O���X �_�C�A���O�v�R���|�[�l���g�ɂ��ǉ�����Ă��܂��B

/////////////////////////////////////////////////////////////////////////////
// CDlgCommonProgress �_�C�A���O

#ifndef __DLGCOMMONPROG_H__
#define __DLGCOMMONPROG_H__

class CDlgCommonProgress : public CDialog
{
// �\�z/����
public:
    CDlgCommonProgress(UINT nCaptionID = 0);   // �W���R���X�g���N�^
    ~CDlgCommonProgress();

    BOOL Create(CWnd *pParent=NULL);

    // �v���O���X �_�C�A���O�̏���
    void SetRange(int nLower,int nUpper);
    int  SetStep(int nStep);
    int  SetPos(int nPos);
    int  OffsetPos(int nPos);
    int  StepIt();
	void EnableCancelButton(BOOL);
    BOOL IsCanceled(void){return m_bCanceled;}//�ǉ� by Kobarin    
    void SetCanceled(BOOL bCanceled){m_bCanceled = bCanceled;}//�ǉ� by Kobarin
        
// �_�C�A���O �f�[�^
    //{{AFX_DATA(CDlgCommonProgress)
    enum { IDD = CG_IDD_PROGRESS };
    CProgressCtrl	m_Progress;
    //}}AFX_DATA

// �I�[�o�[���C�h
    // ClassWizard �͉��z�֐��̃I�[�o���C�h�𐶐����܂��B
    //{{AFX_VIRTUAL(CDlgCommonProgress)
    public:
    virtual BOOL DestroyWindow();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
    //}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	UINT m_nCaptionID;
    int m_nLower;
    int m_nUpper;
    int m_nStep;
    BOOL m_bParentDisabled;
    BOOL m_bCanceled;// �ǉ� by Kobarin

    void ReEnableParent();

    virtual void OnCancel();
    virtual void OnOK() {}; 
    void UpdatePercent(int nCurrent);
    void PumpMessages();

    // �������ꂽ���b�Z�[�W �}�b�v�֐�
    //{{AFX_MSG(CDlgCommonProgress)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // __DLGCOMMONPROG_H__
