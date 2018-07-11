//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddLight dialog

class CAddLight : public CDialog
{
	DECLARE_DYNAMIC(CAddLight)

public:
	CAddLight(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddLight();

	//####public interface####	
	//The user just needs to use these functions
	virtual INT_PTR DoModal();
	CChar* GetName() { return (CChar*)m_strLightName.GetBuffer(m_strLightName.GetLength()); m_strLightName.ReleaseBuffer(); }
	CChar* GetTempName() { return (CChar*)m_strLightTempName.GetBuffer(m_strLightTempName.GetLength()); m_strLightTempName.ReleaseBuffer(); }

	CFloat* GetLightPos() { return m_fLightPos; }
	CFloat* GetAmbientColor() { return m_fAmbientColor; }
	CFloat* GetDiffuseColor() { return m_fDiffuseColor; }
	CFloat* GetSpecularColor() { return m_fSpecularColor; }
	CFloat GetConstantAttenuation() { return m_fConstantAttenuation; } 
	CFloat GetLinearAttenuation() { return m_fLinearAttenuation; }
	CFloat GetQuadAttenuation() { return m_fQuadAttenuation; }
	CFloat GetSpotCuttoff() { return m_fSpotCuttoff; }
	CFloat* GetSpotDirection() { return m_fSpotDirection; }
	CFloat GetSpotExponent() { return m_fSpotExponent; }
	CFloat GetShininess() { return m_fShininess; }
	CLightType GetType() { return m_lightType; }
	//#######################
	CVoid SetName( CChar* name )
	{
		m_strLightName = name;
	}
	CVoid SetPos(CFloat* pos)
	{
		CChar posX[MAX_NAME_SIZE];
		CChar posY[MAX_NAME_SIZE];
		CChar posZ[MAX_NAME_SIZE];
		sprintf( posX, "%f", pos[0] );
		sprintf( posY, "%f", pos[1] );
		sprintf( posZ, "%f", pos[2] );
		m_strLightPosX = posX;
		m_strLightPosY = posY;
		m_strLightPosZ = posZ;
	}
	CVoid SetAmbient (CFloat* ambient )
	{
		for( CInt i = 0; i < 4; i++ )
			m_fAmbientColor[i] = ambient[i];
	}
	CVoid SetDiffuse(CFloat* diffuse )
	{
		for( CInt i = 0; i < 4; i++ )
			m_fDiffuseColor[i] = diffuse[i];
	}	
	CVoid SetSpecular(CFloat* specular )
	{
		for( CInt i = 0; i < 4; i++ )
			m_fSpecularColor[i] = specular[i];
	}
	CVoid SetShininess( CFloat shininess )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%f", shininess );
		m_strShininess = temp;
	}
	CVoid SetConstantAttenuation( CFloat cAtt )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%f", cAtt );
		m_strConstantAttenuation = temp;
	}
	CVoid SetLinearAttenuation( CFloat lAtt )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%f", lAtt );
		m_strLinearAttenuation = temp;
	}
	CVoid SetQuadAttenuation( CFloat qAtt )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%f", qAtt );
		m_strQuadAttenuation = temp;
	}
	CVoid SetSpotDirection( CFloat* spotDirection )
	{
		CChar dirX[MAX_NAME_SIZE];
		CChar dirY[MAX_NAME_SIZE];
		CChar dirZ[MAX_NAME_SIZE];
		sprintf( dirX, "%f", spotDirection[0] );
		sprintf( dirY, "%f", spotDirection[1] );
		sprintf( dirZ, "%f", spotDirection[2] );
		m_strSpotDirectionX = dirX;
		m_strSpotDirectionY = dirY;
		m_strSpotDirectionZ = dirZ;
	}
	CVoid SetSpotCuttoff( CFloat spotCutoff )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%f", spotCutoff );
		m_strSpotCutoff = temp;
	}
	CVoid SetSpotExponent( CFloat spotExponent )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%f", spotExponent );
		m_strSpotExponent = temp;
	}
	CVoid SetType(CLightType lightType)
	{
		m_lightType = lightType;
	}
	CVoid SetCreate( CBool create )
	{
		if( create )
			m_create = CTrue;
		else
			m_create = CFalse;
	}

	CVoid SetEditMode( CBool editMode )
	{
		m_editMode = editMode;
	}

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_LIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	// Opens a color dialog to select the ambient light
	CButton m_btnAmbientLight;
	// Opens a color dialog to select the diffuse light
	CButton m_btnDiffuseLight;
	// Opens a color dialog to select the specular light
	CButton m_btnSpecularLight;

	CEdit m_editBoxLightPosX;
	CEdit m_editBoxLightPosY;
	CEdit m_editBoxLightPosZ;
	CEdit m_editBoxConstantAttenuation;
	CEdit m_editBoxLinearAttenuation;
	CEdit m_editBoxQuadAttenuation;
	CEdit m_editBoxSpotCutoff;
	CEdit m_editBoxSpotDirectionX;
	CEdit m_editBoxSpotDirectionY;
	CEdit m_editBoxSpotDirectionZ;
	CEdit m_editBoxSpotExponent;
	CEdit m_editBoxShininess;
	CEdit m_editBoxAmbientColor;
	CEdit m_editBoxDiffuseColor;
	CEdit m_editBoxSpecularColor;

	CString m_strLightName;
	CString m_strLightTempName;
	CString m_strLightPosX;
	CString m_strLightPosY;
	CString m_strLightPosZ;
	CString m_strConstantAttenuation;
	CString m_strLinearAttenuation;
	CString m_strQuadAttenuation;
	CString m_strSpotCutoff;
	CString m_strSpotDirectionX;
	CString m_strSpotDirectionY;
	CString m_strSpotDirectionZ;
	CString m_strSpotExponent;
	CString m_strShininess;

	//The above strings are converted to the following floating point values
	CFloat m_fLightPos[4];
	CFloat m_fConstantAttenuation;
	CFloat m_fLinearAttenuation;
	CFloat m_fQuadAttenuation;
	CFloat m_fSpotCuttoff;
	CFloat m_fSpotDirection[4];
	CFloat m_fSpotExponent;
	CFloat m_fShininess;
	CFloat m_fAmbientColor[4];
	CFloat m_fDiffuseColor[4];
	CFloat m_fSpecularColor[4];
	CLightType m_lightType;

	CBool m_create;
	CBool m_editMode;

	CButton m_btnOK;
	CButton m_btnCancel;
	CComboBox m_comboLightType;

	afx_msg void OnBnClickedButtonAmbientLight();
	afx_msg void OnBnClickedButtonDiffuseLight();
	afx_msg void OnBnClickedButtonSpecularLight();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	COLORREF m_ambientColor, m_diffuseColor, m_specularColor;
	CBrush m_ambientBrush, m_diffuseBrush, m_specularBrush;
	CFont m_font;
	
	afx_msg void OnEnChangeEditConstantAttenuation();
	afx_msg void OnEnChangeEditLinearAttenuation();
	afx_msg void OnEnChangeEditQuadAttenuation();
	afx_msg void OnEnChangeEditShininess();
	afx_msg void OnEnChangeEditSpotDirectionX();
	afx_msg void OnEnChangeEditSpotExponent();
	afx_msg void OnEnChangeEditSpotCutoff();
	afx_msg void OnEnChangeEditLightPosX();
	afx_msg void OnEnChangeEditLightPosY();
	afx_msg void OnEnChangeEditLightPosZ();
	afx_msg void OnEnChangeEditSpotDirectionY();
	afx_msg void OnEnChangeEditSpotDirectionZ();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombLightType();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOk();
	CEdit m_editBoxLightName;
	afx_msg void OnEnChangeEditLightName();
	afx_msg void OnBnClickedCancel();
};
