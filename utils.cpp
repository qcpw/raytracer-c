
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# include "utils.h"

# ifdef WIN32
# include <Windows.h>
# include <sys/timeb.h>
# include <io.h>
# else
# include <unistd.h>
# include <sys/time.h>
# endif

# if defined(_WIN32) || defined(WINDOWS) || defined(WIN32)
# define GS_WINDOWS  //!< Defined if compiled for windows
# ifndef __CYGWIN32__
# pragma warning(disable : 4996) // for vc8 secure functions warning
# endif
# else
# define GS_LINUX    //!< Defined if not compiled in windows
# endif

double gs_time()
 {
   #ifdef GS_WINDOWS
   static bool first=true;
   static double _perf_freq = 0.0;
   static double _utc_origin = 0.0;

   if ( first )
    { first = false;
      LARGE_INTEGER lpFrequency;
      LARGE_INTEGER lpPerformanceCount;
      struct _timeb tbuf;
      if ( QueryPerformanceFrequency(&lpFrequency)==false )
       { printf("GsTimer: WIN32 High Resolution Performance Counter not supported.\n");
         // you may also use cout or any other print method
       }
      else
       { _perf_freq = (double)lpFrequency.QuadPart;
         QueryPerformanceCounter ( &lpPerformanceCount );
         _ftime( &tbuf ); // get UTC time in seconds from Jan 1, 1970
         double hrcTime = double(lpPerformanceCount.QuadPart) / double(lpFrequency.QuadPart);
         double utcTime = double(tbuf.time) + double(tbuf.millitm)*1.0E-3;
         _utc_origin = utcTime - hrcTime;
       }
    }

   if ( _perf_freq==0 ) // not available
    { _timeb tp;
      _ftime(&tp);
      return 0.001*(double)tp.millitm + (double)tp.time;
    }
   else
    { LARGE_INTEGER lpPerformanceCount;
      QueryPerformanceCounter (&lpPerformanceCount);
      return _utc_origin + double(lpPerformanceCount.QuadPart) / _perf_freq;
    }
   # endif // GS_WINDOWS

   # ifdef GS_LINUX
   timeval tp;
   if ( gettimeofday(&tp,0)==-1 ) return 0;
   return 0.000001*(double)tp.tv_usec + (double)tp.tv_sec;
   # endif // GS_LINUX
 }


