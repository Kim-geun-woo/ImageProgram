
// ProgramView.cpp: CProgramView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Program.h"
#endif

#include "ProgramDoc.h"
#include "ProgramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProgramView

IMPLEMENT_DYNCREATE(CProgramView, CView)

BEGIN_MESSAGE_MAP(CProgramView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CProgramView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DOWN_SAMPLING, &CProgramView::OnDownSampling)
	ON_COMMAND(ID_UP_SAMPLING, &CProgramView::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CProgramView::OnQuantization)
	ON_COMMAND(ID_SUM_CONSTANT, &CProgramView::OnSumConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CProgramView::OnSubConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CProgramView::OnMulConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CProgramView::OnDivConstant)
	ON_COMMAND(ID_AND_OPERATE, &CProgramView::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CProgramView::OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, &CProgramView::OnXorOperate)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CProgramView::OnNegaTransform)
	ON_COMMAND(ID_GAMMA_CORRECTRION, &CProgramView::OnGammaCorrectrion)
	ON_COMMAND(ID_BINARIZATION, &CProgramView::OnBinarization)
	ON_COMMAND(ID_STRESS_TRANSFORM, &CProgramView::OnStressTransform)
	ON_COMMAND(ID_HISTO_STRETCH, &CProgramView::OnHistoStretch)
	ON_COMMAND(ID_END_IN_SEARCH, &CProgramView::OnEndInSearch)
	ON_COMMAND(ID_HISTOGRAM, &CProgramView::OnHistogram)
	ON_COMMAND(ID_HISTO_EQUAL, &CProgramView::OnHistoEqual)
	ON_COMMAND(ID_HISTO_SPEC, &CProgramView::OnHistoSpec)
	ON_COMMAND(ID_EMBOSSING, &CProgramView::OnEmbossing)
	ON_COMMAND(ID_BLURR, &CProgramView::OnBlurr)
	ON_COMMAND(ID_GAUSSIAN_FILTER, &CProgramView::OnGaussianFilter)
	ON_COMMAND(ID_SHARPENING, &CProgramView::OnSharpening)
	ON_COMMAND(ID_HPF_SHARP, &CProgramView::OnHpfSharp)
	ON_COMMAND(ID_LPF_SHARP, &CProgramView::OnLpfSharp)
	ON_COMMAND(ID_DIFF_OPERATOR_HOR, &CProgramView::OnDiffOperatorHor)
	ON_COMMAND(ID_HOMOGEN_OPERATOR, &CProgramView::OnHomogenOperator)
	ON_COMMAND(ID_LAPLACIAN, &CProgramView::OnLaplacian)
	ON_COMMAND(ID_NEAREST, &CProgramView::OnNearest)
	ON_COMMAND(ID_BILINEAR, &CProgramView::OnBilinear)
	ON_COMMAND(ID_MEDIAN_SUB, &CProgramView::OnMedianSub)
	ON_COMMAND(ID_MEAN_SUB, &CProgramView::OnMeanSub)
END_MESSAGE_MAP()

// CProgramView 생성/소멸

CProgramView::CProgramView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CProgramView::~CProgramView()
{
}

BOOL CProgramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CProgramView 그리기

void CProgramView::OnDraw(CDC* pDC)
{
	CProgramDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	int i, j;
	unsigned char R, G, B;
	// 입력 영상 출력
	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = pDoc->m_InputImage[i * pDoc->m_width + j];
			G = B = R;
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}

	// 축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}
}


// CProgramView 인쇄


void CProgramView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CProgramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CProgramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CProgramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CProgramView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CProgramView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CProgramView 진단

#ifdef _DEBUG
void CProgramView::AssertValid() const
{
	CView::AssertValid();
}

void CProgramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProgramDoc* CProgramView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProgramDoc)));
	return (CProgramDoc*)m_pDocument;
}
#endif //_DEBUG


// CProgramView 메시지 처리기


void CProgramView::OnDownSampling()
{
	CProgramDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnDownSampling(); // Doc 클래스에 OnDownSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신
}


void CProgramView::OnUpSampling()
{
	CProgramDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnUpSampling(); // Doc 클래스에 OnUpSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신
}


void CProgramView::OnQuantization()
{
	CProgramDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnQuantization(); // Doc 클래스에 OnQuantization 함수 호출

	Invalidate(TRUE); // 화면 갱신
}


void CProgramView::OnSumConstant()
{
	CProgramDoc* pDoc = GetDocument();
	// 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnSumConstant();

	Invalidate(TRUE);
}


void CProgramView::OnSubConstant()
{
	CProgramDoc* pDoc = GetDocument();// 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnSubConstant();

	Invalidate(TRUE);
}


void CProgramView::OnMulConstant()
{
	CProgramDoc* pDoc = GetDocument(); // 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnMulConstant();

	Invalidate(TRUE);
}


void CProgramView::OnDivConstant()
{
	CProgramDoc* pDoc = GetDocument(); // 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnDivConstant();

	Invalidate(TRUE);
}

void CProgramView::OnAndOperate()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate();

	Invalidate(TRUE);
}

void CProgramView::OnOrOperate()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrOperate();

	Invalidate(TRUE);
}



void CProgramView::OnXorOperate()
{
		CProgramDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnXorOperate();
		Invalidate(TRUE);
}


void CProgramView::OnNegaTransform()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();

	Invalidate(TRUE);
}

void CProgramView::OnGammaCorrectrion()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaCorrection();

	Invalidate(TRUE);
}


void CProgramView::OnBinarization()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization();

	Invalidate(TRUE);
}


void CProgramView::OnStressTransform()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnStressTransform();

	Invalidate(TRUE);
}


void CProgramView::OnHistoStretch()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();

	Invalidate(TRUE);
}


void CProgramView::OnEndInSearch()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndInSearch();

	Invalidate(TRUE);
}


void CProgramView::OnHistogram()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistogram();
	Invalidate(TRUE);
}


void CProgramView::OnHistoEqual()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();

	Invalidate(TRUE);
}


void CProgramView::OnHistoSpec()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoSpec();

		Invalidate(TRUE);
}


void CProgramView::OnEmbossing()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossing();

	Invalidate(TRUE);
}

void CProgramView::OnBlurr()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurr();

	Invalidate(TRUE);
}


void CProgramView::OnGaussianFilter()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGaussianFilter();

	Invalidate(TRUE);
}



void CProgramView::OnSharpening()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpening();

	Invalidate(TRUE);
}


void CProgramView::OnHpfSharp()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHpfSharp();

	Invalidate(TRUE);
}


void CProgramView::OnLpfSharp()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLpfSharp();

	Invalidate(TRUE);
}


void CProgramView::OnDiffOperatorHor()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDiffOperatorHor();

	Invalidate(TRUE);

}


void CProgramView::OnHomogenOperator()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHomogenOperator();

	Invalidate(TRUE);

}


void CProgramView::OnLaplacian()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLaplacian();

	Invalidate(TRUE);

}


void CProgramView::OnNearest()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNearest();

	Invalidate(TRUE);

}


void CProgramView::OnBilinear()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBilinear();

	Invalidate(TRUE);

}


void CProgramView::OnMedianSub()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMedianSub();

	Invalidate(TRUE);
}



void CProgramView::OnMeanSub()
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMeanSub();

	Invalidate(TRUE);

}
