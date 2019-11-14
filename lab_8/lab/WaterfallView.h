
// WaterfallView.h : CWaterfallView Ŭ������ �������̽�
//

#pragma once


class CWaterfallView : public CView
{
protected: // serialization������ ��������ϴ�.
	CWaterfallView();
	DECLARE_DYNCREATE(CWaterfallView)

// Ư���Դϴ�.
public:
	CWaterfallDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CWaterfallView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // WaterfallView.cpp�� ����� ����
inline CWaterfallDoc* CWaterfallView::GetDocument() const
   { return reinterpret_cast<CWaterfallDoc*>(m_pDocument); }
#endif

