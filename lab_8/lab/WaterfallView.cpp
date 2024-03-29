
// WaterfallView.cpp : CWaterfallView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CWaterfallView 생성/소멸

CWaterfallView::CWaterfallView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CWaterfallView::~CWaterfallView()
{
}

BOOL CWaterfallView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CWaterfallView 그리기

void CWaterfallView::OnDraw(CDC* pDC)
{
	CWaterfallDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	F4(pDC);
	F5(pDC);
	F6(pDC);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CWaterfallView 인쇄

BOOL CWaterfallView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWaterfallView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWaterfallView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CWaterfallView 진단

#ifdef _DEBUG
void CWaterfallView::AssertValid() const
{
	CView::AssertValid();
}

void CWaterfallView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWaterfallDoc* CWaterfallView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWaterfallDoc)));
	return (CWaterfallDoc*)m_pDocument;
}
#endif //_DEBUG


// CWaterfallView 메시지 처리기
