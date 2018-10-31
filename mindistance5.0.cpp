#include <stdio.h> 
#include <float.h> 
#include <stdlib.h> 
#include <math.h> 

//define a data structure to present a plean
struct Points
{
	double x, y;
};

//we use qsort to do sortworks
//void qsort(void*base,size_t num,size_t width,int(__cdecl*compare)(const void*,const void*));
int cmpx(const void* a, const void* b)
{
	Points *p1 = (Points *)a, *p2 = (Points *)b;
	return (p1->x - p2->x);
}
int cmpy(const void* a, const void* b)
{
	Points *p1 = (Points *)a, *p2 = (Points *)b;
	return (p1->y - p2->y);
}
double dist(Points p1, Points p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y));
}
double bruteForce(Points P[], int n)
{
	double min = FLT_MAX;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (dist(P[i], P[j]) < min)
				min = dist(P[i], P[j]);
	return min;
}
// a funtion to find the smaller onr of two value
double min(double x, double y)
{
	return (x < y) ? x : y;
}

double stripClosest(Points strip[], int size, double d)
{
	double min = d; // Initialize the minimum distance as d 
	qsort(strip, size, sizeof(Points), cmpy);
	for (int i = 0; i < size; ++i)
		for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
			if (dist(strip[i], strip[j]) < min)
				min = dist(strip[i], strip[j]);

	return min;
}

double closestUtil(Points P[], int n)
{
	if (n <= 3)
		return bruteForce(P, n);

	int mid = n>>1;
	Points midPoint = P[mid];
	
	//dl is the smallest distance in the left part
	//dr is the smallest distance in the right part
	double dl = closestUtil(P, mid);
	double dr = closestUtil(P + mid, n - mid);

	// Pick the smaller one as min
	double d = min(dl, dr);

	// Build an array strip[] that contains points close (closer than d) 
	// to the line passing through the middle point 
	Points *strip = new Points[n];
	int j = 0;
	for (int i = 0; i < n; i++)
		if (fabs(P[i].x - midPoint.x) < d)
			strip[j] = P[i], j++;

	return min(d, stripClosest(strip, j, d));
}

//main function
int main()
{
	int N;
	double x, y;
	scanf("%d", &N);
	Points *P = new Points[N];
	for (int i = 0; i < N; i++)
	{
		scanf("%lf %lf", &x, &y);
		P[i].x = x;
		P[i].y = y;
	}

	qsort(P, N, sizeof(Points), cmpx);
	double reslut=closestUtil(P, N);
	printf("%.2f\n", reslut);
	return 0;
}
