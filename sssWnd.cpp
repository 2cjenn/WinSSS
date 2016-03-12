// sssWnd.cpp : implementation file
//

#include "stdafx.h"
#include "sss.h"
#include "sssWnd.h"
#include "sssDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// sssWnd

sssWnd::sssWnd()
{
	hDC = NULL;
	hRC = NULL;
	
}

sssWnd::~sssWnd()
{
}


BEGIN_MESSAGE_MAP(sssWnd, CStatic)
	//{{AFX_MSG_MAP(sssWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// sssWnd message handlers


CSize sssWnd::GetWnd()
{
	CRect rect;
	CSize size;

	GetClientRect(&rect);
	size = rect.Size();
	return size;
}

//#include "winuser.h"

void sssWnd::EnableOpenGL(/*HWND hWnd, HDC * hDC, HGLRC * hRC*/)
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	
	// get the device context (DC)
	hDC = ::GetDC( m_hWnd );
	
	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat( hDC, &pfd );
	SetPixelFormat( hDC, format, &pfd );
	
	// create and enable the render context (RC)
	hRC = wglCreateContext( hDC );
	wglMakeCurrent( hDC, hRC );

	CSize size = GetWnd();
	GLint width=size.cx;
	GLint height=size.cy ;

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.02f,1000.0f);	

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
	
}


void sssWnd::DisableOpenGL()
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( hRC );
	DeleteDC(hDC );

}



void sssWnd::Paint(void * pTemp, double dist)
{
	MSG msg;
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) DispatchMessage(&msg);
	ModelTemplate * pM = (ModelTemplate *) pTemp;
	int nRow = pM->nRow;
	int nCol = pM->nCol;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	
	CSize size = GetWnd();
	GLdouble rx = size.cx / (double)nRow;
	GLdouble ry = size.cy / (double)nCol;
	glTranslated(-size.cx/2, -size.cy / 2,-size.cx * dist / 1.331);

	bool point = false;
	if (nRow > 400) point = true;
	for (int i=0; i< nRow; i++)
		for (int j=0; j<nCol; j++)
		{
			int temp = pM->pStateArray[i+j*nCol];
			if(temp % 1 == 0)
				glColor3d(pM->dStateColors[temp][0],pM->dStateColors[temp][1],pM->dStateColors[temp][2]);
			else
				glColor3d(0.0f, 0.0f, 0.0f);
			if (point)
			{
				glBegin(GL_POINTS);
				glVertex3d(rx * i, ry * j, 0.0f);
				glEnd();
			}
			else
			{
			glBegin(GL_QUADS);													// Start Drawing Quads
				glVertex3d( rx*i, ry*j, 0.0f);			// Left And Up 1 Unit (Top Left)
				glVertex3d( rx*(i+1), ry*j, 0.0f);		// Right And Up 1 Unit (Top Right)
				glVertex3d( rx*(i+1), ry*(j+1), 0.0f);	// Right And Down One Unit (Bottom Right)
				glVertex3d( rx*i, ry*(j+1), 0.0f);		// Left And Down One Unit (Bottom Left)
			glEnd();  
			}
		//	glRectf(rx * i, ry * j, rx * (i+1), ry * (j+1));
		}
	

	glFlush();
	SwapBuffers(hDC);// Done Drawing The Quad

}






void sssWnd::Drawlines(void * pTemp, int nStep, int shift, double dist)
{	
	ModelTemplate *pM = (ModelTemplate *) pTemp;
	int nStates = pM->nStates;
	int i;

	CSize size = GetWnd();
	
	nStep = nStep % 400;
	static double lines[400][16];
	for (i = 0; i< nStates; i++)
		lines[nStep][i] = pM->dFreq[i] * size.cy;
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	

	GLdouble rx = (double)size.cx / 400.;
	glTranslated(-size.cx/2, (-size.cy/2 + shift * 10) , - size.cx / 3.0 * dist );

	GLdouble temp = (double)size.cy / 10.0;
	glLineWidth(.5);
	for (i = 0; i <= 10; i ++ )
	{
		glColor3f(.2f,.2f,.2f);
		glBegin(GL_LINES);
			glVertex3i(2, (int)(temp * i), 0);
			glVertex3i(size.cx-2, (int)(temp * i), 0);
		glEnd();

	}  // horizontal lines


	glLineWidth(2.0);
	rx = (size.cx - 4) / 400.0; 
	for(i = 1; i< __min(nStep, 400)-1; i++)
	{	
		for (int j = 0; j < nStates; j++)
		{
			glColor3d(pM->dStateColors[j][0],pM->dStateColors[j][1],pM->dStateColors[j][2]);
			
			glBegin(GL_LINES);
				glVertex3f(i* rx + 2, (int)lines[i][j], 0);
				glVertex3f((i+1) * rx + 2, (int)lines[i+1][j], 0);
			glEnd();
		
		}
	}

	glFlush();
	SwapBuffers(hDC);
}

void sssWnd::DrawPhasePortrait(void * pTemp, double dist, int steplength, int sp1, int sp2)
{
	MSG msg;
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) DispatchMessage(&msg);
	ModelTemplate * pM = (ModelTemplate *) pTemp;
	int nRow = pM->nRow;
	int nCol = pM->nCol;

	int i;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	static int nStep;
	
	CSize size = GetWnd();
//	GLdouble rx = size.cx / (double)nRow;
//	GLdouble ry = size.cy / (double)nCol;
	glTranslated(-size.cx/2, -size.cy/2,-size.cx * dist / 1.331);

	glLineWidth(.8f);
	glColor3f(.2f,.2f,.2f);
	glBegin(GL_LINES);
		glVertex3i(0, size.cy/2, 0);
		glVertex3i(size.cx, size.cy/2, 0);
	glEnd();

	glBegin(GL_LINES);
		glVertex3i(size.cx/2, 0, 0);
		glVertex3i(size.cx/2, size.cy, 0);
	glEnd();


/*	for (i = 0; i <= 10; i ++ )
	{
		glColor3f(.2f,.2f,.2f);
		glBegin(GL_LINES);
			glVertex3i(0, 10 * i, 0);
			glVertex3i(400, 10 * i, 0);
		glEnd();

	}  // horizontal lines
*/
		
	static double lines[2000][2];
	lines[nStep][0] = pM->dFreq[sp1] * size.cx/2 + size.cx/2;
	lines[nStep][1] = pM->dFreq[sp2] * size.cy/2 + size.cy/2;
	
	nStep ++;
	if (nStep >= steplength) nStep = 1;

	glLineWidth(2.0);
	for(i = 1; i< __min(nStep, steplength)-1; i++)
	{	
		if(i%2==0)
			glColor3d(pM->dStateColors[sp1][0],pM->dStateColors[sp1][1],pM->dStateColors[sp1][2]);
		else
			glColor3d(pM->dStateColors[sp2][0],pM->dStateColors[sp2][1],pM->dStateColors[sp2][2]);

		glBegin(GL_LINES);
			glVertex3i((int)lines[i][0], (int)lines[i][1], 0);
			glVertex3i((int)lines[i+1][0], (int)lines[i+1][1], 0);
		glEnd();
		
	
	}

	glFlush();
	SwapBuffers(hDC);

}




void sssWnd::DrawLegend(void * pTemp, int nStates)
{

	ModelTemplate * pM = (ModelTemplate *) pTemp;
	int i;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	static int nStep;
	
	CSize size = GetWnd();

	glTranslated(-size.cx/2, -size.cy/2,-size.cy / .8);

	glLineWidth(.8f);
	glColor3f(.2f,.2f,.2f);
	
	glBegin(GL_LINES);
		glVertex3i(size.cx/2, 0, 0);
		glVertex3i(size.cx/2, size.cy, 0);
	glEnd();

	GLdouble unit = size.cy / 10.0;
	for(i = 0; i < nStates; i++)
	{	
		glColor3d(pM->dStateColors[i][0],pM->dStateColors[i][1],pM->dStateColors[i][2]);
		glRectf(size.cx/3.-2., size.cy - (unit * i + 4), 
			size.cx/3.+2, size.cy - (unit * i + 9));
		
		glRectf(size.cx/1.5-2, size.cy - (unit * i + 4), 
			size.cx/1.5+2, size.cy - (unit * i + 9));
	
	}

	glFlush();
	SwapBuffers(hDC);


}