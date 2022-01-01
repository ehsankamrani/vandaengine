//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddEngineCamera dialog

class CAddEngineCamera : public CDialog
{
	DECLARE_DYNAMIC(CAddEngineCamera)

public:
	CAddEngineCamera(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddEngineCamera();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CBool m_create;
	CBool m_isActive;
public:
	CEdit m_editBoxPosX;
	CEdit m_editBoxPosY;
	CEdit m_editBoxPosZ;

	CEdit m_editBoxNCP;
	CEdit m_editBoxFCP;

	CString m_strName;
	CString m_strTempName;
	CString m_strPosX, m_strPosY, m_strPosZ;
	CString m_strPan, m_strTilt;
	CString m_strFOV;
	CString m_strNCP, m_strFCP;

	CFloat m_posX, m_posY, m_posZ;
	CFloat m_pan, m_tilt;
	CFloat m_fov;
	CFloat m_ncp, m_fcp;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit m_editBoxCameraName;

	CVoid SetCreate(CBool set) { m_create = set; }

	CChar* GetName() { return (CChar*)m_strName.GetBuffer(m_strName.GetLength()); m_strName.ReleaseBuffer(); }
	CChar* GetTempName() { return (CChar*)m_strTempName.GetBuffer(m_strTempName.GetLength()); m_strTempName.ReleaseBuffer(); }

	CFloat GetPosX() { return m_posX; }
	CFloat GetPosY() { return m_posY; }
	CFloat GetPosZ() { return m_posZ; }

	CFloat GetPan() { return m_pan; }
	CFloat GetTilt() { return m_tilt; }
	
	CFloat GetFOV() { return m_fov; }
	CFloat GetNCP() { return m_ncp; }
	CFloat GetFCP() { return m_fcp; }
	afx_msg void OnEnChangeEditCameraName();
	afx_msg void OnEnChangePosX();
	afx_msg void OnEnChangePosY();
	afx_msg void OnEnChangePosZ();

	afx_msg void OnEnChangeNcp();
	afx_msg void OnEnChangeFcp();
	afx_msg void OnEnChangeFov();
	CEdit m_editBoxFOV;

	CVoid SetName(CChar* name)
	{
		m_strName = name;
	}

	CVoid SetPosX(CFloat pos)
	{
		CChar posX[MAX_NAME_SIZE];
		sprintf(posX, "%.3f", pos);
		m_strPosX = posX;
		m_posX = pos;
	}

	CVoid SetPosY(CFloat pos)
	{
		CChar posY[MAX_NAME_SIZE];
		sprintf(posY, "%.3f", pos);
		m_strPosY = posY;
		m_posY = pos;
	}

	CVoid SetPosZ(CFloat pos)
	{
		CChar posZ[MAX_NAME_SIZE];
		sprintf(posZ, "%.3f", pos);
		m_strPosZ = posZ;
		m_posZ = pos;
	}

	CVoid SetPan(CFloat pan)
	{
		CChar Pan[MAX_NAME_SIZE];
		sprintf(Pan, "%.3f", pan);
		m_strPan = Pan;
		m_pan = pan;
	}

	CVoid SetTilt(CFloat tilt)
	{
		CChar Tilt[MAX_NAME_SIZE];
		sprintf(Tilt, "%.3f", tilt);
		m_strTilt = Tilt;
		m_tilt = tilt;
	}
	CVoid SetFOV(CFloat fov)
	{
		CChar FOV[MAX_NAME_SIZE];
		sprintf(FOV, "%.3f", fov);
		m_strFOV = FOV;
		m_fov = fov;
	}

	CVoid SetNCP(CFloat ncp)
	{
		CChar NCP[MAX_NAME_SIZE];
		sprintf(NCP, "%.3f", ncp);
		m_strNCP = NCP;
		m_ncp = ncp;
	}

	CVoid SetFCP(CFloat fcp)
	{
		CChar FCP[MAX_NAME_SIZE];
		sprintf(FCP, "%.3f", fcp);
		m_strFCP = FCP;
		m_fcp = fcp;
	}

	CBool IsActive() { return m_isActive; }
	afx_msg void OnBnClickedButtonActivate();
	CEdit m_editBoxPan;
	CEdit m_editBoxTilt;
	afx_msg void OnEnChangePan();
	afx_msg void OnEnChangeTilt();
};
