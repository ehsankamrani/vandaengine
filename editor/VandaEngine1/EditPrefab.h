//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CEditPrefab dialog

class CEditPrefab : public CDialog
{
	DECLARE_DYNAMIC(CEditPrefab)

public:
	CEditPrefab(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditPrefab();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_PREFAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listPrefabInstanceAnimationNames;
	CListCtrl m_listPrefabInstanceCameraNames;
	afx_msg void OnBnClickedButtonCopyPrefabInstanceCameraName();
	CStatic m_imageCtrl;
	afx_msg void OnBnClickedButtonCopyPrefabInstanceAnimationName();
	CRichEditCtrl m_richSelectedAnimationName;
	CRichEditCtrl m_richSelectedCameraName;

	CEdit m_editPosX;
	CEdit m_editPosY;
	CEdit m_editPosZ;
	CString m_strPosX;
	CString m_strPosY;
	CString m_strPosZ;
	CFloat m_fPosX;
	CFloat m_fPosY;
	CFloat m_fPosZ;

	CEdit m_editRotX;
	CEdit m_editRotY;
	CEdit m_editRotZ;
	CString m_strRotX;
	CString m_strRotY;
	CString m_strRotZ;
	CFloat m_fRotX;
	CFloat m_fRotY;
	CFloat m_fRotZ;

	CEdit m_editScaleX;
	CEdit m_editScaleY;
	CEdit m_editScaleZ;
	CString m_strScaleX;
	CString m_strScaleY;
	CString m_strScaleZ;
	CFloat m_fScaleX;
	CFloat m_fScaleY;
	CFloat m_fScaleZ;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CStatic m_textPrefabInstanceName;
	afx_msg void OnBnClickedButtonCopyPrefabInstanceName();
	CRichEditCtrl m_richPrefabInstanceName;
	CVoid SetPrefabInstance(CInstancePrefab* instance_prefab);

private:
	CInstancePrefab* m_instancePrefab;
	HBITMAP m_hBitmap;

public:
	afx_msg void OnLvnItemchangedListPrefabInstanceAnimations(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListPrefabInstanceCameras(NMHDR *pNMHDR, LRESULT *pResult);
	CVoid UpdatePreview();
	afx_msg void OnEnChangeEditPosX();
	afx_msg void OnEnChangeEditPosY();
	afx_msg void OnEnChangeEditPosZ();
	afx_msg void OnEnChangeEditRotX();
	afx_msg void OnEnChangeEditRotY();
	afx_msg void OnEnChangeEditRotZ();
	afx_msg void OnEnChangeEditScaleX();
	afx_msg void OnEnChangeEditScaleY();
	afx_msg void OnEnChangeEditScaleZ();
	afx_msg void OnBnClickedButtonAmbient();
	afx_msg void OnBnClickedButtonDiffuse();
	afx_msg void OnBnClickedButtonSpecular();
	afx_msg void OnBnClickedButtonEmission();
	afx_msg void OnEnChangeEditShininess();
	afx_msg void OnEnChangeEditTransparency();
	CEdit m_editBoxAmbientColor;
	CEdit m_editBoxDiffuseColor;
	CEdit m_editBoxSpecularColor;
	CEdit m_editBoxEmissionColor;
	CEdit m_editBoxShininess;
	CEdit m_editBoxTransparency;

private:
	CFloat m_fAmbientColor[4];
	CFloat m_fDiffuseColor[4];
	CFloat m_fSpecularColor[4];
	CFloat m_fEmissionColor[4];
	CFloat m_fShininess;
	CFloat m_fTransparency;
	CBool m_bEnableMaterial;
	CBool m_updateAmbient, m_updateDiffuse, m_updateSpecular, m_updateEmission;
	COLORREF m_ambientColor, m_diffuseColor, m_specularColor, m_emissionColor;
	CBrush m_ambientBrush, m_diffuseBrush, m_specularBrush, m_emissionBrush;
	CString m_strShininess, m_strTransparency;

public:
	CFloat* GetAmbientColor() { return m_fAmbientColor; }
	CFloat* GetDiffuseColor() { return m_fDiffuseColor; }
	CFloat* GetSpecularColor() { return m_fSpecularColor; }
	CFloat* GetEmissionColor() { return m_fEmissionColor; }
	CFloat GetShininess() { return m_fShininess; }
	CFloat GetTransparency() { return m_fTransparency; }

	CVoid SetAmbientColor(CFloat* color)
	{
		for (CUInt i = 0; i < 4; i++)
		{
			m_fAmbientColor[i] = color[i];
		}
	}

	CVoid SetDiffuseColor(CFloat* color)
	{
		for (CUInt i = 0; i < 4; i++)
		{
			m_fDiffuseColor[i] = color[i];
		}
	}

	CVoid SetSpecularColor(CFloat* color)
	{
		for (CUInt i = 0; i < 4; i++)
		{
			m_fSpecularColor[i] = color[i];
		}
	}

	CVoid SetEmissionColor(CFloat* color)
	{
		for (CUInt i = 0; i < 4; i++)
		{
			m_fEmissionColor[i] = color[i];
		}
	}

	CVoid SetShininess(CFloat shininess)
	{
		m_fShininess = shininess;
		m_strShininess.Format("%.3f", m_fShininess);
	}

	CVoid SetTransparency(CFloat transparency)
	{
		m_fTransparency = transparency;
		m_strTransparency.Format("%.3f", m_fTransparency);
	}

	CVoid SetEnableMaterial(CBool state)
	{
		m_bEnableMaterial = state;
	}

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton m_checkboxEnableMaterial;
	afx_msg void OnBnClickedButtonCopyPrefabName();
	CRichEditCtrl m_richPrefabName;
	CStatic m_textPrefabName;
};
