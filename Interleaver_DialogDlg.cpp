// Interleaver_DialogDlg.cpp : implementation file

#include "stdafx.h"
#include "Interleaver_Dialog.h"
#include "Interleaver_DialogDlg.h"
//using namespace System;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CInterleaver_DialogDlg dialog
CInterleaver_DialogDlg::CInterleaver_DialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInterleaver_DialogDlg::IDD, pParent)
	, m_Num_String(_T(""))
	, m_Num_Column(_T(""))
	, StrDir(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInterleaver_DialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, IDC_PUSK);
	DDX_Text(pDX, IDC_EDIT1, m_Num_String);
	DDV_MaxChars(pDX, m_Num_String, 256);
	DDX_Text(pDX, IDC_EDIT2, m_Num_Column);
	DDV_MaxChars(pDX, m_Num_Column, 256);
	DDX_Control(pDX, IDC_PROGRESS2, m_Progress);
	DDX_Control(pDX, IDC_CHECK1, m_Del_File_BYTE);
}

BEGIN_MESSAGE_MAP(CInterleaver_DialogDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CInterleaver_DialogDlg::OnBnClickedPUSK)
	ON_COMMAND(ID_OnFile, &CInterleaver_DialogDlg::OnFile)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CInterleaver_DialogDlg message handlers
BOOL CInterleaver_DialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	UpdateData(TRUE);
	m_Num_String="2";
	m_Num_Column="2";
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	m_Color_Check_Del=RGB(160,16,16);
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CInterleaver_DialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInterleaver_DialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CInterleaver_DialogDlg::OnBnClickedPUSK() 
{
	// TODO: Add your control notification handler code here
	OnRabota(m_FileName);
	//exit(0);
}

void CInterleaver_DialogDlg::Func_FileIn_BYTE(void)	// ФУНКЦИЯ преобразования входного двоичного файла в файл с байтовым представлением
{
	BYTE *BYTE_FileTEMP,		// указатель на буфер, считываемый из входного двоичного файла
		*BYTE_FileIn;			// указатель на буфер, записываемый в файл с байтовым представлением
	int i,j,nCountBYTE;
	BYTE_FileTEMP=new BYTE[1024];
	BYTE_FileIn=new BYTE[8*1024]; // выходной буфер с байтовым представлением в 8 раз больше входного двоичного

	while(nCountBYTE=FileIn.Read(BYTE_FileTEMP,1024)) // считывание из входного двоичного файла порциями по 1024 байт
	{
		for(j=0;j<nCountBYTE;j++)
			for(i=0;i<8;i++)		// цикл в 8 бит (байт)
			{
				// проверяем значение каждого бита входного байта (0 или 1) с использованием операции сдвига и наложения маски 0x01
				if((BYTE_FileTEMP[j]>>i)&0x01)	// если бит равен 1
				{
					BYTE_FileIn[j*8+i]=0x01;	// байту присваиваем 1
				}
				else							// если бит равен 0
				{
					BYTE_FileIn[j*8+i]=0x00;	// байту присваиваем 0
				}
			}
			FileIn_BYTE.Write(BYTE_FileIn,nCountBYTE*8);	// запись в файл
	}
	delete BYTE_FileTEMP;
	delete BYTE_FileIn;
}

void CInterleaver_DialogDlg::OnRabota(CString m_FileIn_Name) // Основная рабочая функция
{
	CString StrPath,StrName;	// объект строки
	char* bufStr=new char[300];	// выделяем буфер для строки
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	// открывем входной файл
	FileIn.Open(m_FileIn_Name,CFile::modeRead|CFile::typeBinary,NULL);
    StrPath=FileIn.GetFilePath();
	StrName=FileIn.GetFileName();
	StrDir.SetString(StrPath,StrPath.GetLength()-StrName.GetLength());
	// открываем файлы для байтового представления
	FileIn_BYTE.Open((StrDir+(CString)"FileIn_BYTE.dat"),CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary,NULL);
	FileOut_BYTE.Open((StrDir+ (CString)"FileOut_BYTE_Perem.dat"),CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary,NULL);
	Func_FileIn_BYTE();			// вызов ФУНКЦИИ преобразования входного двоичного файла в файл с байтовым представлением
	Func_Perem();				// вызов ФУНКЦИИ перемежения в байтовом виде
	Func_FileOut_BIT();			// вызов ФУНКЦИИ преобразования перемеженного байтового файла в двоичный вид
	// закрываем файлы
	FileIn_BYTE.Close();
	FileOut_BYTE.Close();
	UpdateData(FALSE);
	if(m_Del_File_BYTE.GetCheck())
	{
		DeleteFile((StrDir+(CString)"FileIn_BYTE.dat"));
		DeleteFile((StrDir+(CString)"FileOut_BYTE_Perem.dat"));
	}
	FileIn.Close();
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
}

void CInterleaver_DialogDlg::Func_Perem(void) // ФУНКЦИЯ перемежения в байтовом представлении
{
	int i,j,k,nCountBYTE,nBlockSize,nString,nColumn;
	UpdateData(TRUE);
	nString = atoi(_T(m_Num_String));
	nColumn=atoi(_T(m_Num_Column));
	if((nString>=2)&&(nString<=256)) // проверяем диапазон допустимых значений кол-ва строк и столбцов - 256
		if((nColumn>=2)&&(nColumn<=256))
		{
			FileIn_BYTE.SeekToBegin();	// указатель на начало файла
			nBlockSize=nString*nColumn; // размер блока с учетом кол-ва строк и столбцов
			BYTE* Buf_nBlock=new BYTE[nBlockSize];	// буфер для блока

			// память для исходной MatrixIn и транспонированной MatrixT матриц
			BYTE **MatrixIn=new BYTE *[nString];
			for(i = 0; i < nString; i++) MatrixIn[i] = new BYTE[nColumn];
			BYTE **MatrixTr=new BYTE *[nColumn];
			for(i = 0; i < nColumn; i++) MatrixTr[i] = new BYTE[nString];

			for(i = 0; i < nBlockSize; i++) Buf_nBlock[i]=0x00; // обнуляем буфер (вдруг сразу неполный)
			k=0;
			while(nCountBYTE=FileIn_BYTE.Read(Buf_nBlock,nBlockSize))
			{
				for(i = 0; i < nString; i++)
					for(j = 0; j < nColumn; j++)
					{
						MatrixIn[i][j]=Buf_nBlock[k]; // заполняем исходную матрицу значениями байт считанного блока
						k++;
					}
					for(i = 0; i<nColumn; i++)
					{
						for(j = 0; j<nString; j++)
							MatrixTr[i][j]=MatrixIn[j][i]; // траспонирование матрицы
						FileOut_BYTE.Write(MatrixTr[i],nString);
					}
					for(i=0; i<nBlockSize; i++) Buf_nBlock[i]=0x00; // обнуляем буфер (если след-й блок неполный, остальное заполнится нулями)
					k=0;
			}
			delete Buf_nBlock;
			delete MatrixIn;
			delete MatrixTr;
		}
}

void CInterleaver_DialogDlg::Func_FileOut_BIT(void)	// переводим выходной файл из байтового представления в двоичный и записываем в файл
{
	int nCountBYTE;
	BYTE bBYTE,*Bufer_8BYTE=new BYTE[8]; // буфер для 8 байт, из 8-ми байт получится 1 байт bBYTE в двоичном представлении
	m_Progress.SetRange(0,FileOut_BYTE.GetLength()/1024);
	m_Progress.SetPos(0);
	UpdateData(FALSE);
	FileOut_BYTE.SeekToBegin();
	FileOut.Open(_T(StrDir+"File_BIT_PEREM.dat"),CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); // создаем и открываем выходной двоичный файл
	while(nCountBYTE=FileOut_BYTE.Read(Bufer_8BYTE,8))
	{
		bBYTE=0;			// обнуляем байт
		for(int j=0;j<nCountBYTE;j++)
		{
			if(Bufer_8BYTE[j]==0x01) bBYTE=bBYTE^(1<<j); // на цикле из 8-ми преобразуем массив из 8 входных байт в 1 выходной байт bBYTE 
		}
		FileOut.Write(&bBYTE,1);
		UpdateData(FALSE);
		m_Progress.SetPos(FileOut_BYTE.GetPosition()/1024);
		UpdateData(TRUE);
	}
	delete Bufer_8BYTE;
	FileOut.Close();
}

void CInterleaver_DialogDlg::OnFile()	// ФУНКЦИЯ выбора входного файла
{
	// TODO: Add your command handler code here
	CFileDialog m_File(TRUE);
	if(m_File.DoModal()==IDOK)
	{
		m_FileName=m_File.GetPathName();
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
}

// Обработка нажатия клавиши ESCAPE, чтобы не закрывалось основное диалоговое окно
BOOL CInterleaver_DialogDlg::PreTranslateMessage(MSG*pMsg) 
{
	if((pMsg->message==WM_KEYDOWN) && (pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

// Функция изменения цвета текста
HBRUSH CInterleaver_DialogDlg::OnCtlColor(CDC* pDC, CWnd* _pWnd, UINT nCtlColor)
{
HBRUSH m_hbr = CDialog::OnCtlColor(pDC, _pWnd, nCtlColor);
if (_pWnd==GetDlgItem(IDC_CHECK1)){
	{
	// Устанавливаем цвет статического текста
	pDC->SetTextColor(m_Color_Check_Del);
	//pDC->SetBkColor(RGB(32, 32, 255));	// цвет фона синий
	}
return m_hbr;
	}
}

