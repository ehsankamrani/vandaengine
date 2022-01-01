//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddTerrain dialog

class CAddTerrain : public CDialog
{
	DECLARE_DYNAMIC(CAddTerrain)

public:
	CAddTerrain(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddTerrain();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_TERRAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddHeightmap();
	afx_msg void OnBnClickedButtonAddBottomTexture();
	afx_msg void OnBnClickedButtonAddBottomNormalmap();
	afx_msg void OnBnClickedButtonAddSlopeTexture();
	afx_msg void OnBnClickedButtonAddSlopeNormalmap();
	afx_msg void OnBnClickedButtonAddTopTexture();
	afx_msg void OnBnClickedButtonAddTopNormalmap();
	afx_msg void OnBnClickedButtonAddAmbientColor();
	afx_msg void OnBnClickedButtonAddDiffuseColor();
	afx_msg void OnBnClickedButtonAddSpecularColor();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	virtual BOOL OnInitDialog();
	CEdit m_editBoxHeightMapPath;
	CEdit m_editBoxBottomTexturePath;
	CEdit m_editBoxBottomNormalMapPath;
	CEdit m_editBoxSlopeTexturePath;
	CEdit m_editBoxSlopeNormalMapPath;
	CEdit m_editBoxSlopeFactor;
	CEdit m_editBoxTopTexturePath;
	CEdit m_editBoxTopNormalMapPath;
	CEdit m_editBoxTopStartHeight;
	CEdit m_editBoxShininess;
	CEdit m_editBoxSmooth;
	CEdit m_editBoxScaleHeight;
	CEdit m_editBoxScaleWidth;
	CEdit m_editBoxAmbientColor;
	CEdit m_editBoxDiffuseColor;
	CEdit m_editBoxSpecularColor;

	COLORREF m_ambientColor, m_diffuseColor, m_specularColor;
	CBrush m_ambientBrush, m_diffuseBrush, m_specularBrush;

	CEdit m_editBoxName;

	CString m_strHeightMapPath;
	CString m_strBottomTexturePath;
	CString m_strBottomNormalMapPath;
	CString m_strSlopeTexturePath;
	CString m_strSlopeNormalMapPath;
	CString m_strSlopeFactor;
	CString m_strTopTexturePath;
	CString m_strTopNormalMapPath;
	CString m_strTopStartHeight;
	CString m_strShininess;
	CString m_strSmooth;
	CString m_strScaleHeight;
	CString m_strScaleWidth;
	CString m_strName;
	CString m_strTempName;

	CFloat m_fShininess;
	CInt m_smooth;
	CFloat m_fScaleHeight;
	CFloat m_fScaleWidth;
	CFloat m_fSlopeFactor;
	CFloat m_fTopStartHeight;
	CBool m_flatten;

	CFloat m_fAmbientColor[4];
	CFloat m_fDiffuseColor[4];
	CFloat m_fSpecularColor[4];

	CBool m_bFlatten;
	CBool m_create;
	CBool m_editMode;
	CBool m_changedHeightMap;

public:
	CVoid SetChangedHeightMap(CBool set) { m_changedHeightMap = set; }

	CVoid SetCreate(CBool create)
	{
		if (create)
			m_create = CTrue;
		else
			m_create = CFalse;
	}

	CVoid SetEditMode(CBool editMode)
	{
		m_editMode = editMode;
	}

	CVoid SetName(CChar* name)
	{
		m_strName = name;
	}

	CVoid SetHeightMapPath(CChar* path) { m_strHeightMapPath = path; }

	CVoid SetBottomTexturePath(CChar* path) { m_strBottomTexturePath = path; }
	CVoid SetBottomNormalMapPath(CChar* path) { m_strBottomNormalMapPath = path; }

	CVoid SetSlopeTexturePath(CChar* path) { m_strSlopeTexturePath = path; }
	CVoid SetSlopeNormalMapPath(CChar* path) { m_strSlopeNormalMapPath = path; }

	CVoid SetTopTexturePath(CChar* path) { m_strTopTexturePath = path; }
	CVoid SetTopNormalMapPath(CChar* path) { m_strTopNormalMapPath = path; }

	CVoid SetShininess(CFloat shininess)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.2f", shininess);
		m_strShininess = temp;
	}

	CVoid SetSmooth(CInt smooth)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.d", smooth);
		m_strSmooth = temp;
	}

	CVoid SetScaleHeight(CFloat scaleHeight)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.2f", scaleHeight);
		m_strScaleHeight = temp;
	}

	CVoid SetScaleWidth(CFloat scaleWidth)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.2f", scaleWidth);
		m_strScaleWidth = temp;
	}

	CVoid SetSlopeFactor(CFloat slopeFactor)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.2f", slopeFactor);
		m_strSlopeFactor = temp;
	}

	CVoid SetTopStartHeight(CFloat topStartHeight)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.2f", topStartHeight);
		m_strTopStartHeight = temp;
	}

	CVoid SetFlatten(CBool flatten) { m_flatten = flatten; }

	CVoid SetAmbientColor(CFloat* ambientColor) {
		for (CUInt i = 0; i < 4; i++)
		{
			m_fAmbientColor[i] = ambientColor[i];
		}
	}
	CVoid SetDiffuseColor(CFloat* diffuseColor)
	{
		for (CUInt i = 0; i < 4; i++)
		{
			m_fDiffuseColor[i] = diffuseColor[i];
		}
	}
	CVoid SetSpecularColor(CFloat* specularColor)
	{
		for (CUInt i = 0; i < 4; i++)
		{
			m_fSpecularColor[i] = specularColor[i];
		}
	}

	CButton m_checkBoxFlatten;
	afx_msg void OnEnChangeEditSlopeFactor();
	afx_msg void OnEnChangeEditStartHeight();
	afx_msg void OnEnChangeEditSmooth();
	afx_msg void OnEnChangeEditScaleHeight();
	afx_msg void OnEnChangeEditScaleWidth();
	afx_msg void OnEnChangeEditTerrainName();
	afx_msg void OnEnChangeEditShininess();
	afx_msg void OnBnClickedOk();

	CChar* GetName() { return (CChar*)m_strName.GetBuffer(m_strName.GetLength()); m_strName.ReleaseBuffer(); }
	CChar* GetTempName() { return (CChar*)m_strTempName.GetBuffer(m_strTempName.GetLength()); m_strTempName.ReleaseBuffer(); }

	CChar* GetHeightMapPath() { return (CChar*)m_strHeightMapPath.GetBuffer(m_strHeightMapPath.GetLength()); m_strHeightMapPath.ReleaseBuffer(); }

	CChar* GetBottomTexturePath() { return (CChar*)m_strBottomTexturePath.GetBuffer(m_strBottomTexturePath.GetLength()); m_strBottomTexturePath.ReleaseBuffer(); }
	CChar* GetBottomNormalMapPath() { return (CChar*)m_strBottomNormalMapPath.GetBuffer(m_strBottomNormalMapPath.GetLength()); m_strBottomNormalMapPath.ReleaseBuffer(); }

	CChar* GetSlopeTexturePath() { return (CChar*)m_strSlopeTexturePath.GetBuffer(m_strSlopeTexturePath.GetLength()); m_strSlopeTexturePath.ReleaseBuffer(); }
	CChar* GetSlopeNormalMapPath() { return (CChar*)m_strSlopeNormalMapPath.GetBuffer(m_strSlopeNormalMapPath.GetLength()); m_strSlopeNormalMapPath.ReleaseBuffer(); }

	CChar* GetTopTexturePath() { return (CChar*)m_strTopTexturePath.GetBuffer(m_strTopTexturePath.GetLength()); m_strTopTexturePath.ReleaseBuffer(); }
	CChar* GetTopNormalMapPath() { return (CChar*)m_strTopNormalMapPath.GetBuffer(m_strTopNormalMapPath.GetLength()); m_strTopNormalMapPath.ReleaseBuffer(); }

	CFloat GetShininess() { return m_fShininess; }
	CInt GetSmooth() { return m_smooth; }
	CFloat GetScaleHeight() { return m_fScaleHeight; }
	CFloat GetScaleWidth() { return m_fScaleWidth; }
	CFloat GetSlopeFactor() { return m_fSlopeFactor; }
	CFloat GetTopStartHeight() { return m_fTopStartHeight; }
	CBool GetFlatten() { return m_flatten; }

	CFloat* GetAmbientColor() { return m_fAmbientColor; }
	CFloat* GetDiffuseColor() { return m_fDiffuseColor; }
	CFloat* GetSpecularColor() { return m_fSpecularColor; }

	CBool GetChangedHeightMap() { return m_changedHeightMap; }

};
