//
// Created by Saman Seifi Ph.D. on 5/16/21.
//

#ifndef SIMPLEBEAM_ENVIRONMENT_H
#include <cmath>
#include <cstring>
#include <iostream>	// define C++ stream I/O routines
#include <iomanip>
#include <cstdlib>
#include <cassert>

/* range of real numbers */
#define SMALLNUMBER	1.0e-5
#define HUGENUMBER	1.0e10

/* Miscellaneous Scalar Math */
#define Abs(x)		(((x) < 0) ? (-(x)) : (x))
#define Sqr(x)		((x) * (x))
#define Min(x1,x2)	((x1)<(x2)?(x1):(x2))
#define Max(x1,x2)	((x1)>(x2)?(x1):(x2))
#define Round(x, p)	(((int)((x)*pow(10.0,p)+((x)<0?-0.5:0.5)))/pow(10.0,p))
#define Sign(x)		((x)>=0? 1: -1)
#define Swap(x1, x2)	{int tmp=x1; x1=x2; x2=tmp}
#define ApplySign(x, y)	((y) >= 0? Abs(x): -Abs(x))

/* Angle Conversions & Constants */

#ifndef PI
#define PI 3.1415926535897
#endif

#define RAD2DEG (180/PI)
#define DEG2RAD (PI/180)

#define DegToRad(x) ((x)*DEG2RAD)
#define RadToDeg(x) ((x)*RAD2DEG)
#define SIMPLEBEAM_ENVIRONMENT_H

#endif //SIMPLEBEAM_ENVIRONMENT_H
