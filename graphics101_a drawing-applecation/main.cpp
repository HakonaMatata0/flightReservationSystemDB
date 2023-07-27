#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <windowsx.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <tchar.h>
#include <stack>
#include <cmath>
#include <imagehlp.h>
#include <conio.h>
#include <stack>
#include<list>
using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_CROSS);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

     /*DialogBox((HANDLE)GetModuleHandle(NULL),
        (LPTSTR)"CustBrush",
        hWnd,
        (DLGPROC) BrushDlgProc);*/



    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


void SetPixel_with_brush(HDC hdc,int x,int y,COLORREF c)
{

    SetPixel(hdc, x+3, y, c);
    SetPixel(hdc, x-3, y, c);
    SetPixel(hdc, x, y+3, c);
    SetPixel(hdc, x, y-3, c);

    SetPixel(hdc, x+3, y+3, c);
    SetPixel(hdc, x-3, y-3, c);
    SetPixel(hdc, x-3, y+3, c);
    SetPixel(hdc, x+3, y-3, c);

}





int Round(double x)
{
	return (int)(x + 0.5);
}

/*saving functions*/
static vector <int> AllPoints;
static vector <int> savedPoints;
static int pointRED = 0;
static int pointBLUE = 0;
static int pointGREEN = 0;
void savePoints(int x,int y)
{
    AllPoints.push_back(x);
    AllPoints.push_back(y);
    AllPoints.push_back(pointRED);
    AllPoints.push_back(pointGREEN);
    AllPoints.push_back(pointBLUE);

}
void ExtractToFile(vector <int> &vec)
{
    ofstream out;
    out.open("saved points.txt");

    for(int i = 0; i<vec.size(); i+=5)
        {
            out << vec[i] << "," << vec[i+1] << "," << vec[i+2] << "," << vec[i+3] << "," << vec[i+4] << ",";
            savedPoints.push_back(vec[i]);
            savedPoints.push_back(vec[i+1]);
            savedPoints.push_back(vec[i+2]);
            savedPoints.push_back(vec[i+3]);
            savedPoints.push_back(vec[i+4]);
        }
    out.close();
    vec.clear();
}
/*_________________________________________*/



// Load data from a file and push it into a vector then draw this vector
void loadPoints(HDC hdc ,vector<int> &vec)
{
// load data
    string line;
    ifstream in;
    in.open("saved points.txt");
    getline(in, line);
    stringstream ss(line);
    in.close();
// push the data into the vector
    for (int i; ss >> i;)
    {
        vec.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
// draw the points from the vector
    for(int i = 0; i<vec.size(); i+=5)
    {
        SetPixel(hdc,vec[i],vec[i+1],COLORREF RGB(vec[i+2],vec[i+3],vec[i+4]));
    }
}





////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
//LINE
void DDALine(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    int dx=xe-xs;
    int dy=ye-ys;
    if(abs(dy)<=abs(dx))
    {
        double slope=(double)dy/dx;
        if(xs>xe)
        {
            swap(xs,xe);
            swap(ys,ye);
        }
        for(int x=xs;x<=xe;x++)
        {
            int y=round(ys+(x-xs)*slope);
            SetPixel(hdc,x,y,color);
            savePoints(x,y);
        }
    } else
    {
        double islope=(double)dx/dy;
        if(ys>ye)
        {
            swap(xs,xe);
            swap(ys,ye);
        }
        for(int y=ys;y<=ye;y++)
        {
            int x=round(xs+(y-ys)*islope);
            SetPixel(hdc,x,y,color);
            savePoints(x,y);
        }
    }
}


void midpointLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int x = x1, y = y1;
    double dx = x2 - x1, dy = y2 - y1;
    SetPixel(hdc, x, y, c);
    if ((dx == 0 || dy / dx > 1) && dy > 0 && dx >= 0)
    {
        int d = 2 * dx - dy, d1 = 2 * dx, d2 = 2 * dx - 2 * dy;
        while (y != y2)
        {
            if (d <= 0)
            {
                y++;
                d += d1;
            }
            else
            {
                x++;
                y++;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if (dy / dx >= 0 && dy / dx <= 1 && dy >= 0 && dx > 0)
    {
        int d = dx - 2 * dy, d1 = -2 * dy, d2 = 2 * dx - 2 * dy;
        while (x != x2)
        {
            if (d > 0)
            {
                x++;
                d += d1;
            }
            else
            {
                x++;
                y++;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if (dy / dx < 0 && dy / dx >= -1 && dy <= 0 && dx>0)
    {
        int d = -dx - 2 * dy, d1 = -2 * dy, d2 = -2 * dx - 2 * dy;
        while (x != x2)
        {
            if (d <= 0)
            {
                x++;
                d += d1;
            }
            else
            {
                x++;
                y--;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if ((dx == 0 || dy / dx < -1) && dy < 0 && dx >= 0)
    {
        int d = -2 * dx - dy, d1 = -2 * dx, d2 = -2 * dx - 2 * dy;
        while (y != y2)
        {
            if (d > 0)
            {
                y--;
                d += d1;
            }
            else
            {
                x++;
                y--;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if ((dx == 0 || dy / dx > 1) && dy < 0 && dx <= 0)
    {
        int d = -2 * dx + dy, d1 = -2 * dx, d2 = -2 * dx + 2 * dy;
        while (y != y2)
        {
            if (d <= 0)
            {
                y--;
                d += d1;
            }
            else
            {
                x--;
                y--;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if (dy / dx >= 0 && dy / dx <= 1 && dy <= 0 && dx < 0)
    {
        int d = -dx + 2 * dy, d1 = 2 * dy, d2 = -2 * dx + 2 * dy;
        while (x != x2)
        {
            if (d > 0)
            {
                x--;
                d += d1;
            }
            else
            {
                x--;
                y--;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if (dy / dx < 0 && dy / dx >= -1 && dy >= 0 && dx < 0)
    {
        int d = dx + 2 * dy, d1 = 2 * dy, d2 = 2 * dx + 2 * dy;
        while (x != x2)
        {
            if (d <= 0)
            {
                x--;
                d += d1;
            }
            else
            {
                x--;
                y++;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if ((dx == 0 || dy / dx < -1) && dy > 0 && dx <= 0)
    {
        int d = 2 * dx + dy, d1 = 2 * dx, d2 = 2 * dx + 2 * dy;
        while (y != y2)
        {
            if (d > 0)
            {
                y++;
                d += d1;
            }
            else
            {
                x--;
                y++;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
}

void ParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    double dt = (double)1.0 / max(abs(x2 - x1), abs(y2 - y1));
    for (double t = 0; t <= 1; t += dt)
    {
        double x = x1 + t * (x2 - x1);
        double y = y1 + t * (y2 - y1);
        SetPixel(hdc, Round(x), Round(y), color);
    }
}




////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
//CIRCLE
void draw8points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{
	SetPixel(hdc, xc + x, yc + y, c);
	savePoints(xc + x,yc + y);
	SetPixel(hdc, xc - x, yc + y, c);
	savePoints(xc - x,yc + y);
	SetPixel(hdc, xc - x, yc - y, c);
	savePoints(xc - x,yc - y);
	SetPixel(hdc, xc + x, yc - y, c);
	savePoints(xc + x, yc - y);
	SetPixel(hdc, xc + y, yc + x, c);
	savePoints(xc + y,yc + x);
	SetPixel(hdc, xc - y, yc + x, c);
	savePoints(xc - y,yc + x);
	SetPixel(hdc, xc - y, yc - x, c);
	savePoints(xc - y,yc - x);
	SetPixel(hdc, xc + y, yc - x, c);
	savePoints(xc + y,yc - x);

}

void directCircle(HDC hdc, int xc, int yc, int R, COLORREF c)
{
	double x = 0, y = R;
	while (x < y)
	{
		y = sqrt(pow(R,2) - pow(x , 2));
		draw8points(hdc, xc, yc, x, y, c);
		x++;
	}
}

void circlepolar8points(HDC hdc, int xc, int yc, int R, COLORREF c)
{
	double dtheta = 1.0 / R, theta = 0;
	double x = R, y = 0;
	draw8points(hdc, xc, yc, x, y, c);
	while (x > y)
	{
		theta += dtheta;
		y = R * sin(theta);
		x = R * cos(theta);
		draw8points(hdc, xc, yc, x, y, c);
	}
}
void circle_itirative_polar(HDC hdc, int xc, int yc, int R, COLORREF c)
{
	double dtheta = 1.0 / R;
	double x = R, y = 0;
	double ct = cos(dtheta), st = sin(dtheta);
	draw8points(hdc, xc, yc, x, y, c);
	while (x > y)
	{
		double x1 = x * ct - y * st;
		y = x * st + y * ct;
		x = x1;
		draw8points(hdc, xc, yc, x, y, c);
	}
}
void Circlemidpoint(HDC hdc, int xc, int yc, int R, COLORREF c)
{
	int x = 0, y = R;
	int d = 1 - R;
	draw8points(hdc, xc, yc, x, y, c);
	while (x < y)
	{
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		draw8points(hdc, xc, yc, x, y, c);
	}
}
void CircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF color)
{
	int x = 0, y = R;
	int d = 1 - R;
	int c1 = 3, c2 = 5 - 2 * R;
	draw8points(hdc, xc, yc, x, y, color);
	while (x < y)
	{
		if (d < 0)
		{
			d += c1;
			c2 += 2;
		}
		else
		{
			d += c2;
			c2 += 4;
			y--;
		}
		c1 += 2;
		x++;
		draw8points(hdc, xc, yc, x, y, color);
	}
}



////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
//       ELLIPSE

void draw4points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{
	SetPixel(hdc, xc + x, yc + y, c);
	savePoints(xc + x, yc + y);
	SetPixel(hdc, xc - x, yc + y, c);
	savePoints(xc - x, yc + y);
	SetPixel(hdc, xc - x, yc - y, c);
	savePoints(xc - x, yc - y);
	SetPixel(hdc, xc + x, yc - y, c);
	savePoints(xc + x, yc - y);
}
void ellipespolar(HDC hdc, int xc, int yc, int A, int B, COLORREF c)
{
	double dtheta = 1.0 / max(A, B), theta = 0.0;
	double x = A;
	double y = 0;
	draw4points(hdc, xc, yc, x, y, c);
	while (theta <= 6.28/*py*/)
	{
		theta += dtheta;
		x = A * cos(theta);
		y = B * sin(theta);
		draw4points(hdc, xc, yc, x, y, c);
	}
}

void  directellipse(HDC hdc, int xc, int yc, int A, int B, COLORREF c)
{
	double x = 0;
	double y = B;
	double p = pow(B, 2) - pow(A, 2) * B + pow(A, 2) / 4;

	while (2 * pow(B, 2) * x < 2 * pow(A, 2) * y)
    {
		draw4points(hdc, xc, yc, x, y, c);
		if (p < 0) {
			p = p + 2 * pow(B, 2) * x + pow(B, 2);
		}
		else {
			y--;
			p = p + 2 * pow(B, 2) * x - 2 * pow(A, 2) * y + pow(B, 2);
		}
		x++;
	}

	p = pow(B, 2) * pow(x + 0.5, 2) + pow(A, 2) * pow(y - 1, 2) - pow(A, 2) * pow(B, 2);

	while (y >= 0)
    {
		draw4points(hdc, xc, yc, x, y, c);
		if (p > 0) {
			p = p - 2 * pow(A, 2) * y + pow(A, 2);
		}
		else {
			x++;
			p = p + 2 * pow(B, 2) * x - 2 * pow(A, 2) * y + pow(A, 2);
		}
		y--;
	}

}

void  midpointellipse(HDC hdc, int xc, int yc, int rx, int ry, COLORREF c)
{
	double x = 0, y = max(rx, ry);

	double dx, dy, d1, d2;
	// Initial decision parameter of region 1
	d1 = (ry * ry) - (rx * rx * ry) +
		(0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;

	// For region 1
	while (dx < dy)
	{
		draw4points(hdc, xc, yc, x, y,c);
		// Checking and updating value of
		// decision parameter based on algorithm
		if (d1 < 0)
		{
			x++;
			dx = dx + (2 * ry * ry);
			d1 = d1 + dx + (ry * ry);
		}
		else
		{
			x++;
			y--;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d1 = d1 + dx - dy + (ry * ry);
		}
	}
	// Decision parameter of region 2
	d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
		((rx * rx) * ((y - 1) * (y - 1))) -
		(rx * rx * ry * ry);

	// Plotting points of region 2
	while (y >= 0)
	{

		draw4points(hdc, xc, yc, x, y, c);

		// Checking and updating parameter
		// value based on algorithm
		if (d2 > 0)
		{
			y--;
			dy = dy - (2 * rx * rx);
			d2 = d2 + (rx * rx) - dy;
		}
		else
		{
			y--;
			x++;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d2 = d2 + dx - dy + (rx * rx);
		}
	}

}

////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
//filing

struct Vector2
{
double x,y;
Vector2(double a=0,double b=0)
{
x=a; y=b;
}
};

class Vector4
{
public:
double v[4];
Vector4(double a=0,double b=0,double c=0,double d=0)
{
v[0]=a; v[1]=b; v[2]=c; v[3]=d;
}

Vector4(double a[])
{
memcpy(v,a,4*sizeof(double));
}
double& operator[](int i)
{
return v[i];
}
};

class Matrix4
{
public:
Vector4 M[4];
Matrix4(double A[])
{
memcpy(M,A,16*sizeof(double));
}
Vector4 operator[](int i)
{
return M[i];
}

Vector4 &operator * (Vector4 &vec)
{
    Vector4 myvec(0,0,0,0);
    myvec.v[0] = vec.v[0] * M[0].v[0] + vec.v[1] * M[0].v[1] + vec.v[2] * M[0].v[2] + vec.v[3] * M[0].v[3];
    myvec.v[1] = vec.v[0] * M[1].v[0] + vec.v[1] * M[1].v[1] + vec.v[2] * M[1].v[2] + vec.v[3] * M[1].v[3];
    myvec.v[2] = vec.v[0] * M[2].v[0] + vec.v[1] * M[2].v[1] + vec.v[2] * M[2].v[2] + vec.v[3] * M[2].v[3];
    myvec.v[3] = vec.v[0] * M[3].v[0] + vec.v[1] * M[3].v[1] + vec.v[2] * M[3].v[2] + vec.v[3] * M[3].v[3];
    return myvec;
}

};

struct Entry {
    int xMin, xMax;
};

void draw8_line(HDC hdc , int xc , int yc ,int r, COLORREF c)
{
    DDALine(hdc , xc  , yc - r ,xc, yc + r , c);
    DDALine(hdc , xc - r , yc,xc + r , yc , c);
}

void drawPolygon(HDC hdc , POINT *p , int n , COLORREF c)
{
    int xs = p[0].x , ys = p[0].y , xe , ye;
    for(int i = 1 ; i < n ; i++)
    {
        xe = p[i].x;
        ye = p[i].y;
        DDALine(hdc , xs , ys , xe , ye , c);
        xs = xe;
        ys = ye;
    }
    DDALine(hdc , xs , ys , p[0].x , p[0].y , c);

}

void RecursiveFloodFill(HDC hdc,int x,int y,COLORREF Cb,COLORREF Cf)
{
    COLORREF C=GetPixel(hdc,x,y);
    if(C==Cb || C==Cf)return;
    SetPixel(hdc,x,y,Cf);
    savePoints(x,y);
    RecursiveFloodFill(hdc,x-1,y,Cb,Cf);
    RecursiveFloodFill(hdc,x+1,y,Cb,Cf);
    RecursiveFloodFill(hdc,x,y-1,Cb,Cf);
    RecursiveFloodFill(hdc,x,y+1,Cb,Cf);
}

void NonRecursiveFloodFill(HDC hdc , int &x , int &y , COLORREF bc , COLORREF fc)
{
    stack<Vector2> s;
    Vector2 v(x, y);
    //s.push(v(x,y));
    s.push(v);
    while (!s.empty())
    {
        Vector2 p = s.top();
        s.pop();
        COLORREF c = GetPixel(hdc, p.x, p.y);
        if (c == bc || c == fc) continue;
        else
        {
            SetPixel(hdc, p.x, p.y, fc);
            Vector2 p2(p.x, p.y - 1);
            s.push(p2);
            Vector2 p3(p.x, p.y + 1);
            s.push(p3);
            Vector2 p4(p.x + 1, p.y);
            s.push(p4);
            Vector2 p5(p.x - 1, p.y);
            s.push(p5);

        }
    }
}

void SWaaap(POINT &v1 , POINT &v2)
{
    int temp = v2.x;
    v2.x = v1.x;
    v1.x = temp;
    temp = v2.y;
    v2.y = v1.y;
    v1.y = temp;
}
void Swap (int &x,int &y)
{
    int temp=x;
    x=y;
    y=temp;
}


void InitEntries(Entry table[])
{
    for (int i = 0; i < 1000; i++) {
        table[i].xMin = INT_MAX;
        table[i].xMax = INT_MIN;
    }
}

void ScanEdge(POINT v1, POINT v2, Entry table[])
{
    if (v1.y == v2.y)return;
    if (v1.y > v2.y)SWaaap(v1, v2);
    double minv = (double) (v2.x - v1.x) / (v2.y - v1.y);
    double x = v1.x;
    int y = v1.y;
    while (y < v2.y) {
        if (x < table[y].xMin)table[y].xMin = (int) ceil(x);
        if (x > table[y].xMax)table[y].xMax = (int) floor(x);
        y++;
        x += minv;
    }
}

void DrawScanLines(HDC hdc, Entry table[], COLORREF color)
{
    for (int y = 0; y < 1000; y++)
        if (table[y].xMin < table[y].xMax)
            for (int x = table[y].xMin; x <= table[y].xMax; x++)
                {
                    SetPixel(hdc, x, y, color);
                    savePoints(x,y);
                }

}

void ConvexFill(HDC hdc, POINT p[], int n, COLORREF color)
{
    Entry *table = new Entry[1000];
    InitEntries(table);
    POINT v1 = p[n - 1];
    for (int i = 0; i < n; i++) {
        POINT v2 = p[i];
        ScanEdge(v1, v2, table);
        v1 = p[i];
    }
    DrawScanLines(hdc, table, color);
    delete table;
}


void circle_lineFill(HDC hdc,int xa ,int ya ,int r , int quarter, COLORREF color)// convex
{
    int x;
    int y;
    switch(quarter)
    {
    case 1:
        y = r;
        while(y > 0)
        {
            x = sqrt(pow(r,2) - pow(y , 2));
            DDALine(hdc, xa , ya - y, xa + x , ya - y , color);
            y--;
        }
        break;
    case 2:
        y = 0;
        while(y < r)
        {
            x = sqrt(pow(r,2) - pow(y , 2));
            DDALine(hdc, xa , ya + y, xa + x , ya + y , color);
            y++;
        }
        break;
    case 3:
        y = 0;
        while(y < r)
        {
            x = sqrt(pow(r,2) - pow(y , 2));
            DDALine(hdc, xa , ya + y, xa - x , ya + y , color);
            y++;
        }
        break;
    case 4:
        y = r;
        while(y > 0)
        {
            x = sqrt(pow(r,2) - pow(y , 2));
            DDALine(hdc, xa , ya - y, xa - x , ya - y , color);
            y--;
        }
        break;
    }
}

void circle_circleFill(HDC hdc,int xa ,int ya ,int R , int quarter, COLORREF color)// non recursive
{
    int x , y , d , c1 , c2;
    switch(quarter)
    {
    case 1:
        while(R > 0)
        {
            x = 0;
            y = R;
            d = 1 - R;
            c1 = 3;
            c2 = 5 - 2 * R;
            while (x < y)
            {
                if (d < 0)
                {
                    d += c1;
                    c2 += 2;
                }
                else
                {
                    d += c2;
                    c2 += 4;
                    y--;
                }
                c1 += 2;
                x++;
                SetPixel(hdc, xa + x, ya - y, color);
                savePoints(xa + x, ya - y );
                SetPixel(hdc, xa + y, ya - x, color);
                savePoints(xa + y, ya - x );
            }
            R--;
        }
        break;
    case 2:
        while(R > 0)
        {
            x = 0;
            y = R;
            d = 1 - R;
            c1 = 3;
            c2 = 5 - 2 * R;
            while (x < y)
            {
                if (d < 0)
                {
                    d += c1;
                    c2 += 2;
                }
                else
                {
                    d += c2;
                    c2 += 4;
                    y--;
                }
                c1 += 2;
                x++;
                SetPixel(hdc, xa + x, ya + y, color);
                savePoints(xa + x, ya + y );
                SetPixel(hdc, xa + y, ya + x, color);
                savePoints(xa + y, ya + x);
            }
            R--;
        }
        break;
    case 3:
        while(R > 0)
        {
            x = 0;
            y = R;
            d = 1 - R;
            c1 = 3;
            c2 = 5 - 2 * R;
            while (x < y)
            {
                if (d < 0)
                {
                    d += c1;
                    c2 += 2;
                }
                else
                {
                    d += c2;
                    c2 += 4;
                    y--;
                }
                c1 += 2;
                x++;
                SetPixel(hdc, xa - x, ya + y, color);
                savePoints(xa - x, ya + y);
                SetPixel(hdc, xa - y, ya + x, color);
                savePoints(xa - y, ya + x);
            }
            R--;
        }
        break;
    case 4:
        while(R > 0)
        {
            x = 0;
            y = R;
            d = 1 - R;
            c1 = 3;
            c2 = 5 - 2 * R;
            while (x < y)
            {
                if (d < 0)
                {
                    d += c1;
                    c2 += 2;
                }
                else
                {
                    d += c2;
                    c2 += 4;
                    y--;
                }
                c1 += 2;
                x++;
                SetPixel(hdc, xa - x, ya - y, color);
                savePoints(xa - x, ya - y );
                SetPixel(hdc, xa - y, ya - x, color);
                savePoints(xa - y, ya - x );
            }
            R--;
        }
            break;
        }
}

void drawSquare(HDC hdc, int xa , int ya , int l , COLORREF color)
{
    DDALine(hdc , xa , ya , xa+l , ya , color);
    DDALine(hdc , xa + l , ya , xa + l , ya + l , color);
    DDALine(hdc , xa + l , ya + l , xa , ya + l , color);
    DDALine(hdc , xa , ya + l , xa , ya , color);
}

void drawRectangle(HDC hdc, int xa , int ya , int l ,int w, COLORREF color)
{
    DDALine(hdc , xa , ya , xa+l , ya , color);
    DDALine(hdc , xa + l , ya , xa + l , ya + w , color);
    DDALine(hdc , xa + l , ya + w , xa , ya + w , color);
    DDALine(hdc , xa , ya + w , xa , ya , color);
}

Vector4 GetHermiteCoeff(double x0,double s0,double x1,double s1)
{
static double H[16]={2,1,-2,1,-3,-2,3,-1,0,1,0,0,1,0,0,0};
static Matrix4 basis(H);
Vector4 v(x0,s0,x1,s1);
return basis*v;
}

int DotProduct(Vector4 vect_A, Vector4 vect_B)
{

    int product = 0;

    // Loop for calculate dot product
    for (int i = 0; i < 4; i++)

        product = product + vect_A[i] * vect_B[i];
    return product;
}

void DrawHermiteCurve(HDC hdc ,int xa ,int ya ,int xb ,int yb ,int xc ,int yc ,int xd ,int yd ,int l,int w,int xs,int ys ,COLORREF c)
{
    int x, y , a1 , b1, c1 , d1 , a2 , b2, c2 , d2;
    a1 = 2*xa + xb - 2 *xd + xc;
    b1 = -3 * xa - 2 * xb + 3 * xd - xc;
    c1 = xb;
    d1 = xa;
    a2 = 2*ya + yb - 2 *yd + yc;
    b2 = -3 * ya - 2 * yc + 3 * yd - yc;
    c2 = yb;
    d2 = ya;
    for(float t = 0 ; t <= 1 ; t+=0.001)
    {
        x = a1* pow(t,3) + b1 * pow(t , 2) + c1 * t + d1;
        y = a2* pow(t,3) + b2 * pow(t , 2) + c2 * t + d2;

        if(x >= xs && y >= ys && x <= xs + l && y <= ys + w)
        {
          SetPixel(hdc , x , y , c);
          savePoints(x,y);
        }
    }
}


void DrawBezierCurve(HDC hdc,int xa ,int ya ,int xb ,int yb ,int xc ,int yc ,int xd ,int yd,int l,int w, int xs , int ys ,COLORREF c)
{
    //cout << xa << "\t" << ya << "\t" << xb << "\t" << yb << "\t" << xc << "\t" << yc << "\t" << xd << "\t" << yd << endl;
    Vector2 P0(xa , ya), P1(xb , yb), P2(xc , yc) , P3(xd , yd);
Vector2 T0(3*(P1.x-P0.x),3*(P1.y-P0.y));
Vector2 T1(3*(P3.x-P2.x),3*(P3.y-P2.y));
//cout << P0.x << "\t" << P0.y << "\t" << T0.x << "\t" << T0.y << "\t" << P3.x << "\t" << P3.y << "\t" << T1.x << "\t" << T1.y << endl;
DrawHermiteCurve(hdc,P0.x,P0.y,T0.x,T0.y,P3.x,P3.y,T1.x,T1.y ,l,w,xs,ys, c);
}

void square_hermitFill(HDC hdc, int xa , int ya , int l ,int w, COLORREF c)
{
    int counter = 0 ;
    Vector2 v[4] ;
    for(int j = xa - 5 ; j < xa+l ; j+=2)//  x
    {
        for(int i = ya - 5 ; i < ya+l ; i+=2)//  y
        {
            while(counter <= 3)
            {
                v[counter].y = i + (l/3) * counter;
                //if(counter%2 == 1)
                  //  v[counter].x = j+(l/10);
                //else
                    v[counter].x = j;
                counter++;
            }
            DrawHermiteCurve(hdc , v[0].x , v[0].y , v[1].x , v[1].y , v[2].x , v[2].y , v[3].x , v[3].y, l ,w, xa , ya , c);
            //DrawHermiteCurve(hdc , v[0], v[1], v[2], v[3], 10000 , c);
            counter = 0;
        }
    }
}


void rectangle_bezierFill(HDC hdc, int xa , int ya , int l ,int w , COLORREF c)
{
    int counter = 0 ;
    Vector2 v[4] ;
    for(int i = ya ; i < ya+w+(w/5) ; i+=5)//  y
    {
        for(int j = xa - 5 ; j < xa+l+(l/5) ; j+=5)//  x
        {
            while(counter <= 3)
            {
                v[counter].x = j + 5 * counter;
                if(counter%2 == 1)
                {
                    v[counter].y = i+ 5;
                }
                else
                    v[counter].y = i;
                counter++;
            }
            DrawBezierCurve(hdc , v[0].x , v[0].y , v[1].x , v[1].y , v[2].x , v[2].y , v[3].x , v[3].y ,l,w,xa,ya, c);
            //DrawBezierCurve(hdc , v[0], v[1], v[2], v[3], 1000 , c);
            counter = 0;
        }
    }
}




////////////////////////
///////////////////////


struct Edgerec {
    double x, ymax, minv;
    Edgerec(double x = 0.0, double ymax = 0.0, double minv = 0.0) :x(x), ymax(ymax), minv(minv) {}
};
typedef list<Edgerec> EdgeTable[1000];

void scanEdge(POINT v1, POINT v2, EdgeTable tbl) {
    if (v1.y == v2.y) return;
    if (v1.y > v2.y) swap(v1, v2);
    Edgerec rec(v1.x, v2.y, (double)(v2.x - v1.x) / (v2.y - v1.y));
    tbl[v1.y].push_back(rec);
}

void polygon2table(POINT p[], int n, EdgeTable tbl) {
    POINT v1 = p[n - 1];
    for (int i = 0; i < n; i++) {
        POINT v2 = p[i];
        scanEdge(v1, v2, tbl);
        v1 = v2;
    }
}
void table2screen(HDC hdc, EdgeTable tbl, COLORREF c) {
    int y = 0;


    list<Edgerec>::iterator it;

    while (tbl[y].size() == 0) y++;
    list<Edgerec> activeList = tbl[y];
    while (activeList.size() != 0) {

        activeList.sort([](Edgerec& a, Edgerec& b) {return a.x < b.x; });

        for (it = activeList.begin(); it != activeList.end(); it++) {
            Edgerec& node1 = *it;
            it++;
            if (it == activeList.end()) break;
            Edgerec& node2 = *it;
            DDALine(hdc, ceil(node1.x), y, floor(node2.x), y, c);
        }

        y++;

        for (it = activeList.begin(); it != activeList.end();) {
            if (it->ymax == y) {
                it = activeList.erase(it);
            }
            else it++;
        }

        for (it = activeList.begin(); it != activeList.end(); it++) {
            it->x = it->x + it->minv;
        }

        if (tbl[y].size() != 0) {
            activeList.splice(activeList.end(), tbl[y]);
        }
    }
}

void NonConvexFill(HDC hdc, POINT p[], int n, COLORREF c)
{
    EdgeTable tbl;

    polygon2table(p, n, tbl);
    table2screen(hdc, tbl, c);

}




////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
//          spline curve

void HermiteCurve(HDC hdc, Vector2& p1, Vector2& T1, Vector2& p2, Vector2& T2, COLORREF c)
{
    double a0 = p1.x, a1 = T1.x,
        a2 = -3 * p1.x - 2 * T1.x + 3 * p2.x - T2.x,
        a3 = 2 * p1.x + T1.x - 2 * p2.x + T2.x;
    double b0 = p1.y, b1 = T1.y,
        b2 = -3 * p1.y - 2 * T1.y + 3 * p2.y - T2.y,
        b3 = 2 * p1.y + T1.y - 2 * p2.y + T2.y;
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t * t, t3 = t2 * t;
        double x = a0 + a1 * t + a2 * t2 + a3 * t3;
        double y = b0 + b1 * t + b2 * t2 + b3 * t3;
        SetPixel(hdc, Round(x), Round(y), c);
        savePoints(Round(x), Round(y));
    }
}


void DrawCardinalSpline(HDC hdc, Vector2 P[], int n, double c, COLORREF C)
{
    double c1 = 1 - c;
    Vector2 T0 = c1 * ((P[2].x - P[0].x), (P[2].y - P[0].y));
    for (int i = 0; i < n - 1; i++)
    {
        Vector2 T1 = c1 * ((P[i + 1].x - P[i - 1].x), (P[i + 1].y - P[i - 1].y));
        HermiteCurve(hdc,  P[i] , T0 , P[i + 1] , T1 , c);
        T0 = T1;
    }

}



////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////

/////  clipping
union outCode
{
      unsigned all:4;
      struct{unsigned left:1, right:1, bottom:1, top:1;};
};

outCode getOutCode(double x , double y , double xleft ,double xright ,double ybottom ,double ytop)
{
    outCode r;
    r.all = 0;
    if (x < xleft)
    {
        r.left = 1;
    }else if(x > xright)
    {
        r.right= 1;
    }else if(y < ytop)
    {
        r.top= 1;
    }else if(y > ybottom)
    {
        r.bottom= 1;
    }
    return r;
}

void VIntersect (double xs , double ys ,double xe , double ye ,double xedge ,double * xin ,double * yin)
{
    *xin = xedge;
    *yin = ys + (ye - ys) * (xedge - xs) / (xe - xs);
}

void HIntersect (double xs , double ys ,double xe , double ye ,double yedge ,double * xin ,double * yin)
{
    *yin = yedge;
    *xin = xs + (xe - xs) * (yedge - ys) / (ye - ys);
}

void cohenSuth(HDC hdc ,double xs ,double ys ,double xe ,double ye ,double xleft  ,double ytop ,double xright,double ybottom , COLORREF color)
{
    double x1 = xs, y1 = ys , x2 = xe , y2 = ye;
    outCode out1 = getOutCode(x1 ,y1 ,xleft ,xright, ybottom , ytop);
    outCode out2 = getOutCode(x2 ,y2 ,xleft ,xright, ybottom , ytop);
    while((out1.all || out2.all) && !(out1.all & out2.all))
    {
        double xi , yi;
        if(out1.all)
        {
            if(out1.left)
                VIntersect(x1 , y1 , x2 ,y2 , xleft , &xi , &yi);
            else if(out1.top)
                HIntersect(x1 , y1 , x2 ,y2 , ytop , &xi , &yi);
            else if(out1.right)
                VIntersect(x1 , y1 , x2 ,y2 , xright , &xi , &yi);
            else HIntersect(x1 , y1 , x2 ,y2 , ybottom , &xi , &yi);

            x1 = xi;
            y1 = yi;
            out1 = getOutCode(x1, y1, xleft , xright , ybottom , ytop);
        }else
        {
            if(out2.left)
                VIntersect(x1 , y1 , x2 ,y2 , xleft , &xi , &yi);
            else if(out2.top)
                HIntersect(x1 , y1 , x2 ,y2 , ytop , &xi , &yi);
            else if(out2.right)
                VIntersect(x1 , y1 , x2 ,y2 , xright , &xi , &yi);
            else HIntersect(x1 , y1 , x2 ,y2 , ybottom , &xi , &yi);

            x2 = xi;
            y2 = yi;
            out2 = getOutCode(x2, y2, xleft , xright , ybottom , ytop);
        }
    }
    if(!out1.all && !out2.all)
    {
        DDALine(hdc , x1 , y1 , x2 , y2 , color);
    }
}

void clipping_ciclePoint(HDC hdc , int xc , int yc , int r , int x , int y , COLORREF c)
{
    int rb = sqrt(pow(xc-x , 2) + pow(yc-y , 2));
    if(rb <= r)
    {
        SetPixel(hdc , x , y , c);
        savePoints(x,y);
    }
}

void clipping_cicleLine(HDC hdc , int xc , int yc , int r , int xa , int ya , int xb , int yb , COLORREF c)
{
    for (double t = 0; t < 1; t += 0.001)
    {
        double x = xa + (xb - xa) * t;
        double y = ya + (yb - ya) * t;

        int rb = Round(sqrt(pow(x - xc, 2) + pow(y - yc, 2)));
        if (rb <= r)
            SetPixel(hdc, Round(x), Round(y), c);
            savePoints(Round(x), Round(y));
    }
}


/*  This function is called by the Windows function DispatchMessage()  */

static int tmp = 0, counter = 0, xc , yc , xa , ya , xb , yb , xd , yd , xe , ye, xf , yf, xg , yg , r , l;static POINT p[5];
Vector2 v[4];
static int oldPointRED = 0;
static int oldPointGREEN = 0;
static int oldPointBLUE = 0;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc=GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
            HMENU hmenu=CreateMenu();
            HMENU COLOR=CreateMenu();
            HMENU LINE=CreateMenu();
            HMENU circle=CreateMenu();
            HMENU ellipse=CreateMenu();

            HMENU FILLING=CreateMenu();
            HMENU FILLING_CIRCLE_LINE=CreateMenu();
            HMENU FILLING_CIRCLE_CIRCLE=CreateMenu();

            HMENU CLIPPING_Rectangle=CreateMenu();
            HMENU CLIPPING_SQUARE=CreateMenu();
            HMENU CLIPPING_CIRCLE=CreateMenu();
            AppendMenu(hmenu,MF_POPUP,(UINT_PTR)COLOR,"COLOR");
            AppendMenu(hmenu,MF_POPUP,(UINT_PTR)LINE,"LINE");
            AppendMenu(hmenu,MF_POPUP,(UINT_PTR)circle,"CIRCLE");
            AppendMenu(hmenu,MF_POPUP,(UINT_PTR)ellipse,"ELLIPSE");
            AppendMenu(hmenu,MF_POPUP,(UINT_PTR)FILLING,"FILLING");
            AppendMenu(hmenu,MF_POPUP,(UINT_PTR)CLIPPING_Rectangle,"CLIPPING Rectangle");
            AppendMenu(hmenu,MF_POPUP,(UINT_PTR)CLIPPING_SQUARE,"CLIPPING SQUARE");
            AppendMenu(hmenu,MF_POPUP,(UINT_PTR)CLIPPING_CIRCLE,"CLIPPING CIRCLE");

            AppendMenu(COLOR,MF_STRING,24,"Red");
            AppendMenu(COLOR,MF_STRING,25,"Orange");
            AppendMenu(COLOR,MF_STRING,26,"Yellow");
            AppendMenu(COLOR,MF_STRING,27,"Green");
            AppendMenu(COLOR,MF_STRING,28,"Sky blue");
            AppendMenu(COLOR,MF_STRING,29,"Blue");
            AppendMenu(COLOR,MF_STRING,30,"Purple");
            AppendMenu(COLOR,MF_STRING,31,"Black");

            AppendMenu(LINE,MF_STRING,1,"line of PARAMETRIC");
            AppendMenu(LINE,MF_STRING,2,"line of DDA");
            AppendMenu(LINE,MF_STRING,3,"line of midpoint");

            AppendMenu(circle,MF_STRING,4,"Circle of direct");
            AppendMenu(circle,MF_STRING,5,"Circle of polar");
            AppendMenu(circle,MF_STRING,6,"Circle of iterative polar");
            AppendMenu(circle,MF_STRING,7,"Circle of midpoint");
            AppendMenu(circle,MF_STRING,8,"Circle of modified midpoint");

            AppendMenu(ellipse,MF_STRING,32,"ellipse of polar");
            AppendMenu(ellipse,MF_STRING,33,"ellipse of direct");
            AppendMenu(ellipse,MF_STRING,34,"ellipse of midpoint");

            AppendMenu(FILLING,MF_POPUP,(UINT_PTR)FILLING_CIRCLE_LINE,"Filling Circle with lines");
            AppendMenu(FILLING_CIRCLE_LINE,MF_STRING,35,"Top right");
            AppendMenu(FILLING_CIRCLE_LINE,MF_STRING,36,"Bottom right");
            AppendMenu(FILLING_CIRCLE_LINE,MF_STRING,37,"Bottom left");
            AppendMenu(FILLING_CIRCLE_LINE,MF_STRING,38,"Top left");

            AppendMenu(FILLING,MF_POPUP,(UINT_PTR)FILLING_CIRCLE_CIRCLE,"Filling Circle with other circles");
            AppendMenu(FILLING_CIRCLE_CIRCLE,MF_STRING,39,"Top right");
            AppendMenu(FILLING_CIRCLE_CIRCLE,MF_STRING,40,"Bottom right");
            AppendMenu(FILLING_CIRCLE_CIRCLE,MF_STRING,41,"Bottom left");
            AppendMenu(FILLING_CIRCLE_CIRCLE,MF_STRING,42,"Top left");

            AppendMenu(FILLING,MF_STRING,11,"Filling Square with Hermit Curve");
            AppendMenu(FILLING,MF_STRING,12,"Filling Rectangle with Bezier Curve");

            AppendMenu(FILLING,MF_STRING,43,"Recursive flood fill");
            AppendMenu(FILLING,MF_STRING,44,"Non recursive flood fill");

            AppendMenu(FILLING,MF_STRING,45,"Convex filling");
            AppendMenu(FILLING,MF_STRING,46,"Non convex filling");

            AppendMenu(CLIPPING_Rectangle,MF_STRING,13,"Clipping rectangle point");
            AppendMenu(CLIPPING_Rectangle,MF_STRING,14,"Clipping rectangle line");
            AppendMenu(CLIPPING_Rectangle,MF_STRING,15,"Clipping rectangle polygon");

            AppendMenu(CLIPPING_SQUARE,MF_STRING,16,"Clipping square point");
            AppendMenu(CLIPPING_SQUARE,MF_STRING,17,"Clipping square line");

            AppendMenu(CLIPPING_CIRCLE,MF_STRING,18,"Clipping circle point");
            AppendMenu(CLIPPING_CIRCLE,MF_STRING,19,"Clipping circle line");

            AppendMenu(hmenu,MF_STRING,47,"Spline curve");

            AppendMenu(hmenu,MF_STRING,20,"Save");
            AppendMenu(hmenu,MF_STRING,21,"Load");
            AppendMenu(hmenu,MF_STRING,22,"Clean screen");
            AppendMenu(hmenu,MF_STRING,23,"Exit");

            SetMenu(hwnd,hmenu);

            SetBkColor(hdc , RGB(255,255,255));
            break;
        }
        case WM_COMMAND:
            switch(wParam)
            {
                ////////////      LINE      //////////
                case 1:
                    tmp =1;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"line of PARAMETRIC"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 2:
                    tmp =2;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"line of DAA"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 3:
                    tmp =3;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"line of midpoint"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                ////////////      CIRCLE      //////////
                case 4:
                    tmp =4;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Circle of direct"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 5:
                    tmp = 5;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Circle of polar"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 6:
                    tmp = 6;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Circle of iterative polar"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 7:
                    tmp =7;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Circle of midpoint"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 8:
                    tmp =8;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Circle of modified midpoint"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                ////////////      ELLIPSE      //////////
                case 32:
                    tmp =32;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"ellipse of polar"<<endl;
                    cout<<"Choose three points"<<endl;
                    break;
                case 33:
                    tmp =33;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"ellipse of direct"<<endl;
                    cout<<"Choose three points"<<endl;
                    break;
                case 34:
                    tmp =34;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"ellipse of midpoint"<<endl;
                    cout<<"Choose three points"<<endl;
                    break;
                ////////////      FILLING      //////////

                // circle with lines
                case 35:
                    tmp =35;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling Circle with lines (top right)"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 36:
                    tmp =36;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling Circle with lines (bottom right)"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 37:
                    tmp =37;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling Circle with lines (bottom left)"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 38:
                    tmp =38;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling Circle with lines (top left)"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                //  circle with circles
                case 39:
                    tmp =39;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling Circle with other circles (top right)"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 40:
                    tmp =40;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling Circle with other circles (bottom right)"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 41:
                    tmp =41;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling Circle with other circles (bottom left)"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 42:
                    tmp =42;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling Circle with other circles (top left)"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                //  square with hermit
                case 11:
                    tmp =11;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling Square with Hermit Curve"<<endl;
                    cout<<"Choose three points"<<endl;
                    break;
                case 12:
                    tmp =12;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling Rectangle with Bezier Curve"<<endl;
                    cout<<"Choose four points"<<endl;
                    break;
                //  flood fill recursive and non recursive
                case 43:
                    tmp =43;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling circle with recursive flood fill algorithm"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 44:
                    tmp =44;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Filling circle with non recursive flood fill algorithm"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                //  filling polygon convex and non convex
                case 45:
                    tmp =45;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Polygon convex filling"<<endl;
                    cout<<"Choose five points"<<endl;
                    break;
                case 46:
                    tmp =46;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Polygon non convex filling"<<endl;
                    cout<<"Choose five points"<<endl;
                    break;
                ////////////      CLIPPING_Rectangle     //////////
                case 13:
                    tmp =13;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Clipping rectangle point"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 14:
                    tmp =14;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Clipping rectangle line"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                case 15:
                    tmp =15;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Clipping rectangle polygon"<<endl;
                    cout<<"Choose four points"<<endl;
                    break;
                ////////////        CLIPPING_SQUARE      /////////////
                case 16:
                    tmp =16;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Clipping square point"<<endl;
                    cout<<"Choose one points"<<endl;
                    break;
                case 17:
                    tmp =17;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Clipping square line"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                ////////////        CLIPPING_CIRCLE     /////////////
                case 18:
                    tmp =18;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Clipping circle point"<<endl;
                    cout<<"Choose one points"<<endl;
                    break;
                case 19:
                    tmp =19;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Clipping circle line"<<endl;
                    cout<<"Choose two points"<<endl;
                    break;
                /////////////      spline curve    //////////////
                case 47:
                    tmp = 47;
                    counter = 0;
                    MessageBeep(MB_OK);
                    cout<<"Spline curve"<<endl;
                    cout<<"Choose four points"<<endl;
                /////////////         Save         //////////////
                case 20:
                    MessageBeep(MB_OK);
                    ExtractToFile(AllPoints);
                    cout<<"Saving"<<endl;
                    break;
                /////////////         load         //////////////
                case 21:
                    MessageBeep(MB_OK);
                    loadPoints(hdc ,AllPoints);
                    cout<<"Loading"<<endl;
                    break;
                /////////////         clear         //////////////
                case 22:
                    MessageBeep(MB_OK);
                    ShowWindow(hwnd, SW_HIDE);

                    MessageBeep(MB_OK);
                    ShowWindow(hwnd, SW_SHOW);

                    for(int i = 0; i<savedPoints.size(); i+=5)
                    {
                        SetPixel(hdc,savedPoints[i],savedPoints[i+1], RGB(savedPoints[i+2],savedPoints[i+3],savedPoints[i+4]));
                    }

                    cout<<"Clear"<<endl;
                    break;
                /////////////         Exit         //////////////
                case 23:
                    DestroyWindow(hwnd);
                    MessageBeep(MB_OK);
                    cout<<"Exit"<<endl;
                    break;
                /////////////         COLORS         //////////////
                case 24:
                    MessageBeep(MB_OK);
                    pointRED = 255;
                    pointGREEN = 0;
                    pointBLUE = 0;
                    cout<<"Choose color red"<<endl;
                    break;
                case 25:
                    MessageBeep(MB_OK);
                    pointRED = 255;
                    pointGREEN = 165;
                    pointBLUE = 0;
                    cout<<"Choose color orange"<<endl;
                    break;
                case 26:
                    MessageBeep(MB_OK);
                    pointRED = 255;
                    pointGREEN = 255;
                    pointBLUE = 0;
                    cout<<"Choose color yellow"<<endl;
                    break;
                case 27:
                    counter = 0;
                    MessageBeep(MB_OK);
                    pointRED = 0;
                    pointGREEN = 255;
                    pointBLUE = 0;
                    cout<<"Choose color green"<<endl;
                    break;
                case 28:
                    MessageBeep(MB_OK);
                    pointRED = 0;
                    pointGREEN = 255;
                    pointBLUE = 255;
                    cout<<"Choose color sky blue"<<endl;
                    break;
                case 29:
                    counter = 0;
                    MessageBeep(MB_OK);
                    pointRED = 0;
                    pointGREEN = 0;
                    pointBLUE = 255;
                    cout<<"Choose color blue"<<endl;
                    break;
                case 30:
                    MessageBeep(MB_OK);
                    pointRED = 255;
                    pointGREEN = 0;
                    pointBLUE = 255;
                    cout<<"Choose color purple"<<endl;
                    break;
                case 31:
                    MessageBeep(MB_OK);
                    pointRED = 0;
                    pointBLUE = 0;
                    pointGREEN = 0;
                    cout<<"Choose color black"<<endl;
                    break;
            }
            break;
        case WM_LBUTTONDOWN:
            if(tmp == 0)
            {
                cout << "Choose an algorithm to draw" << endl;
            }else if(tmp <= 8)// line, circle
            {
                if(counter == 0)
                {
                    xa = LOWORD(lParam);
                    ya = HIWORD( lParam);
                    counter++;
                }else if(counter == 1)
                {
                    xb = LOWORD(lParam);
                    yb = HIWORD( lParam);
                    if(tmp == 1)
                        ParametricLine(hdc,xa,ya,xb,yb, RGB(pointRED,pointGREEN,pointBLUE));
                    else if(tmp == 2)
                        {
                            HBRUSH hbrush;
                            hbrush = CreateHatchBrush(100 , RGB(pointRED,pointGREEN,pointBLUE));
                            SelectObject(hdc, hbrush);
                            DDALine(hdc,xa,ya,xb,yb, RGB(pointRED,pointGREEN,pointBLUE));
                            DeleteObject(hbrush);
                        }
                    else if(tmp == 3)
                        midpointLine(hdc,xa,ya,xb,yb, RGB(pointRED,pointGREEN,pointBLUE));
                    else if(tmp == 4)
                    {
                        int r = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                        directCircle(hdc,xa,ya,r, RGB(pointRED,pointGREEN,pointBLUE));
                    }
                    else if(tmp == 5)
                    {
                        int r = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                        circlepolar8points(hdc,xa,ya,r, RGB(pointRED,pointGREEN,pointBLUE));
                    }
                    else if(tmp == 6)
                    {
                        int r = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                        circle_itirative_polar(hdc,xa,ya,r, RGB(pointRED,pointGREEN,pointBLUE));
                    }
                    else if(tmp == 7)
                    {
                        int r = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                        Circlemidpoint(hdc,xa,ya,r, RGB(pointRED,pointGREEN,pointBLUE));
                    }
                    else if(tmp == 8)
                    {
                        int r = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                        CircleModifiedMidpoint(hdc,xa,ya,r, RGB(pointRED,pointGREEN,pointBLUE));
                    }
                    counter = 0;
                }
            }else if((tmp >= 32 && tmp <= 44) || tmp == 11)// ellipse, circle filling and square filling
            {
                if(counter == 0)
                {
                    xa = LOWORD(lParam);
                    ya = HIWORD( lParam);
                    counter++;
                }else if(counter == 1)
                {
                    xb = LOWORD(lParam);
                    yb = HIWORD( lParam);
                    if(tmp >= 35 && tmp <= 44)
                    {
                        r = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                        CircleModifiedMidpoint(hdc,xa,ya,r, RGB(pointRED,pointGREEN,pointBLUE));
                        if(tmp <= 42)
                        {
                            draw8_line(hdc , xa ,ya , r , RGB(pointRED,pointGREEN,pointBLUE));
                        }else if(tmp == 43 || tmp == 44){
                            oldPointRED = pointRED;
                            oldPointGREEN = pointGREEN;
                            oldPointBLUE = pointBLUE;
                        }
                        cout << "Click to fill" <<endl;
                    }else if(tmp == 11)
                    {
                        if(xa > xb)
                            {swap(xa , xb);swap(ya , yb);}
                        r = xb - xa;
                        drawSquare(hdc,xa,ya,r, RGB(pointRED,pointGREEN,pointBLUE));
                        cout << "Click to fill" << endl;
                    }
                    counter++;
                }else if(counter == 2)
                {
                    xc = LOWORD(lParam);
                    yc = HIWORD( lParam);
                    if(tmp == 32)
                    {
                        int a = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                        int b = sqrt(pow(xa-xc , 2) + pow(ya-yc , 2));
                        ellipespolar(hdc,xa,ya,a,b, RGB(pointRED,pointGREEN,pointBLUE));
                    }
                    else if(tmp == 33)
                    {
                        int a = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                        int b = sqrt(pow(xa-xc , 2) + pow(ya-yc , 2));
                        directellipse(hdc,xa,ya,a,b, RGB(pointRED,pointGREEN,pointBLUE));
                    }
                    else if(tmp == 34)
                    {
                        int a = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                        int b = sqrt(pow(xa-xc , 2) + pow(ya-yc , 2));
                        midpointellipse(hdc,xa,ya,a,b,RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 35)
                    {
                        circle_lineFill(hdc,xa ,ya ,r ,1,RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 36)
                    {
                        circle_lineFill(hdc,xa ,ya ,r ,2, RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 37)
                    {
                        circle_lineFill(hdc,xa ,ya ,r ,3, RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 38)
                    {
                        circle_lineFill(hdc,xa ,ya ,r ,4, RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 39)
                    {
                        circle_circleFill(hdc,xa ,ya ,r ,1, RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 40)
                    {
                        circle_circleFill(hdc,xa ,ya ,r ,2, RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 41)
                    {
                        circle_circleFill(hdc,xa ,ya ,r ,3, RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 42)
                    {
                        circle_circleFill(hdc,xa ,ya ,r ,4, RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 11)
                    {
                        square_hermitFill(hdc , xa , ya , r ,r, RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 43)
                    {
                        RecursiveFloodFill(hdc , xa , ya , RGB(oldPointRED,oldPointGREEN,oldPointBLUE) , RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 44)
                    {
                        NonRecursiveFloodFill(hdc , xa , ya , RGB(oldPointRED,oldPointGREEN,oldPointBLUE) , RGB(pointRED,pointGREEN,pointBLUE));
                    }
                    counter = 0;
                }
            }else if(tmp == 12)
            {
                if(counter == 0)
                {
                    xa = LOWORD(lParam);
                    ya = HIWORD( lParam);
                    counter++;
                }else if(counter == 1)
                {
                    xb = LOWORD(lParam);
                    yb = HIWORD( lParam);
                    counter++;
                }else if(counter == 2)
                {
                    xc = LOWORD(lParam);
                    yc = HIWORD( lParam);
                    l = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                    r = sqrt(pow(xb-xc , 2) + pow(yb-yc , 2));
                    drawRectangle(hdc , xa , ya , l , r , RGB(pointRED,pointGREEN,pointBLUE));
                    cout << "Click to fill" << endl;
                    counter++;
                }else if(counter == 3)
                {
                    xd = LOWORD(lParam);
                    yd = HIWORD( lParam);
                    rectangle_bezierFill(hdc , xa , ya , l , r , RGB(pointRED,pointGREEN,pointBLUE));
                    counter = 0;
                }
            }else if(tmp == 14 || tmp == 13 || tmp == 18 || tmp == 19)
            {
                if(counter == 0)
                {
                    xa = LOWORD(lParam);
                    ya = HIWORD( lParam);
                    counter++;
                }else if(counter == 1)
                {
                    xb = LOWORD(lParam);
                    yb = HIWORD( lParam);
                    if(tmp == 18 || tmp == 19)
                    {
                        r = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                        CircleModifiedMidpoint(hdc , xa , ya , r , RGB(pointRED,pointGREEN,pointBLUE));
                    }else if(tmp == 14 || tmp == 13)
                    {
                        if(xa > xb)
                            swap(xa , xb);
                        if(ya > yb)
                            swap(xa , xb);
                        l = xb - xa;
                        r = yb - ya;
                        drawRectangle(hdc , xa , ya , l , r , RGB(pointRED,pointGREEN,pointBLUE) );
                    }
                    if(tmp == 14 || tmp == 19)
                        cout << "Select two points to draw a line" << endl;
                    else if(tmp == 13 || tmp == 18)
                        cout << "Select one points to draw" << endl;
                    counter++;
                }else if(counter == 2)
                {
                    xc = LOWORD(lParam);
                    yc = HIWORD( lParam);
                    if(tmp == 13 )
                    {
                        if( xc >= xa && yc >= ya && xc <= xa + l && yc <= ya + r)
                        {
                          SetPixel(hdc , xc , yc , RGB(pointRED,pointGREEN,pointBLUE));
                          savePoints(xc,yc);
                        }
                    }else if(tmp == 18)
                    {
                        clipping_ciclePoint(hdc , xa , ya , r , xc , yc ,RGB(pointRED,pointGREEN,pointBLUE));
                    }else counter++;

                }else if(counter == 3)
                {
                    xd = LOWORD(lParam);
                    yd = HIWORD( lParam);
                    if(tmp == 14)
                        cohenSuth(hdc , xc , yc , xd , yd , xa , ya , xb , yb , RGB(pointRED,pointGREEN,pointBLUE));
                    if(tmp == 19)
                        clipping_cicleLine(hdc , xa , ya , r , xc , yc , xd, yd , RGB(pointRED,pointGREEN,pointBLUE));
                    counter = 2;
                }
            }else if(tmp == 16 || tmp == 17)
            {
                if(counter == 0)
                {
                    xa = LOWORD(lParam);
                    ya = HIWORD( lParam);
                    counter++;
                }else if(counter == 1)
                {
                    xb = LOWORD(lParam);
                    yb = HIWORD( lParam);
                    if(xa > xb)
                        {swap(xa , xb);swap(ya , yb);}
                    r = sqrt(pow(xa-xb , 2) + pow(ya-yb , 2));
                    drawSquare(hdc,xa,ya,r, RGB(pointRED,pointGREEN,pointBLUE));
                    if(tmp == 17)
                        cout << "Select two points to draw a line" << endl;
                    else if(tmp == 16)
                        cout << "Select one points to draw" << endl;
                    counter++;
                }else if(counter == 2)
                {
                    xc = LOWORD(lParam);
                    yc = HIWORD( lParam);
                    if(tmp == 16)
                    {
                        if( xc >= xa && yc >= ya && xc <= xa + r && yc <= ya + r)
                        {
                          SetPixel(hdc , xc , yc , RGB(pointRED,pointGREEN,pointBLUE));
                          savePoints(xc,yc);
                        }
                    }else counter++;

                }else if(counter == 3)
                {
                    xd = LOWORD(lParam);
                    yd = HIWORD( lParam);
                    cohenSuth(hdc , xc , yc , xd , yd , xa , ya , xa+r , ya + r , RGB(pointRED,pointGREEN,pointBLUE));
                    counter = 2;
                }
            }else if(tmp == 15)
            {
                if(counter == 0)
                {
                    xa = LOWORD(lParam);
                    ya = HIWORD( lParam);
                    counter++;
                }else if(counter == 1)
                {
                    xb = LOWORD(lParam);
                    yb = HIWORD( lParam);
                    if(xa > xb)
                        swap(xa , xb);
                    if(ya > yb)
                        swap(xa , xb);
                    l = xb - xa;
                    r = yb - ya;
                    drawRectangle(hdc , xa , ya , l , r , RGB(pointRED,pointGREEN,pointBLUE) );
                    cout << "Select five points to draw a polygon" << endl;
                    counter++;
                }else if(counter == 2)
                {
                    xc = LOWORD(lParam);
                    yc = HIWORD( lParam);
                    counter++;
                }else if(counter == 3)
                {
                    xd = LOWORD(lParam);
                    yd = HIWORD( lParam);
                    counter++;
                }else if(counter == 4)
                {
                    xe = LOWORD(lParam);
                    ye = HIWORD( lParam);
                    counter++;
                }else if(counter == 5)
                {
                    xf = LOWORD(lParam);
                    yf = HIWORD( lParam);
                    counter++;
                }else if(counter == 6)
                {
                    xg = LOWORD(lParam);
                    yg = HIWORD( lParam);
                    cohenSuth(hdc , xc , yc , xd , yd , xa , ya , xa + l , ya + r , RGB(pointRED,pointGREEN,pointBLUE));
                    cohenSuth(hdc , xd , yd , xe , ye , xa , ya , xa + l , ya + r , RGB(pointRED,pointGREEN,pointBLUE));
                    cohenSuth(hdc , xe , ye , xf , yf , xa , ya , xa + l , ya + r , RGB(pointRED,pointGREEN,pointBLUE));
                    cohenSuth(hdc , xf , yf , xg , yg , xa , ya , xa + l , ya + r , RGB(pointRED,pointGREEN,pointBLUE));
                    cohenSuth(hdc , xg , yg , xc , yc , xa , ya , xa + l , ya + r , RGB(pointRED,pointGREEN,pointBLUE));
                    counter = 2;
                }
            }else if(tmp == 45 || tmp == 46)
            {
                if(counter == 0)
                {
                    p[counter].x = LOWORD(lParam);
                    p[counter].y = HIWORD( lParam);
                    counter++;
                }else if(counter == 1)
                {
                    p[counter].x = LOWORD(lParam);
                    p[counter].y = HIWORD( lParam);
                    counter++;
                }else if(counter == 2)
                {
                    p[counter].x = LOWORD(lParam);
                    p[counter].y = HIWORD( lParam);
                    counter++;
                }else if(counter == 3)
                {
                    p[counter].x = LOWORD(lParam);
                    p[counter].y = HIWORD( lParam);
                    counter++;
                }else if(counter == 4)
                {
                    p[counter].x = LOWORD(lParam);
                    p[counter].y = HIWORD( lParam);
                    drawPolygon(hdc , p , 5 , RGB(pointRED,pointGREEN,pointBLUE));
                    cout << "Click to fill" << endl;
                    counter++;
                }else if(counter == 5)
                {
                    if(tmp == 45)
                        ConvexFill(hdc , p , 5 , RGB(pointRED,pointGREEN,pointBLUE));
                    else NonConvexFill(hdc , p , 5 , RGB(pointRED,pointGREEN,pointBLUE));
                    counter = 0;
                }
            }else if(tmp == 47)
            {
                v[counter] = Vector2(LOWORD(lParam) , HIWORD( lParam));
                if(counter == 3)
                {
                    DrawCardinalSpline(hdc, v, 4, 0.5, RGB(pointRED,pointGREEN,pointBLUE));
                    swap(v[3], v[0]);
                    counter = 1;
                }else counter++;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0);
            break;      /* send a WM_QUIT to the message queue */
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
