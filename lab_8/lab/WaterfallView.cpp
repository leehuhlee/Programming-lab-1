
// WaterfallView.cpp : CWaterfallView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Waterfall.h"
#endif

#include "WaterfallDoc.h"
#include "WaterfallView.h"
#include "Waterfallsolver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWaterfallView

IMPLEMENT_DYNCREATE(CWaterfallView, CView)

BEGIN_MESSAGE_MAP(CWaterfallView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CWaterfallView ����/�Ҹ�

CWaterfallView::CWaterfallView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CWaterfallView::~CWaterfallView()
{
}

BOOL CWaterfallView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CWaterfallView �׸���

void CWaterfallView::OnDraw(CDC* pDC)
{
	CWaterfallDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	F4(pDC);
	F5(pDC);
	F6(pDC);

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CWaterfallView �μ�

BOOL CWaterfallView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CWaterfallView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CWaterfallView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CWaterfallView ����

#ifdef _DEBUG
void CWaterfallView::AssertValid() const
{
	CView::AssertValid();
}

void CWaterfallView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWaterfallDoc* CWaterfallView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWaterfallDoc)));
	return (CWaterfallDoc*)m_pDocument;
}
#endif //_DEBUG


// CWaterfallView �޽��� ó����
