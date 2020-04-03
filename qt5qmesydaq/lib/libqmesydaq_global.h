#ifndef LIBQMESYDAQ_GLOBAL_H
#define LIBQMESYDAQ_GLOBAL_H

#include <QtCore/qglobal.h>


#ifdef _WINDLL
#ifdef BUILD_STATIC
#undef BUILD_STATIC
#endif
#endif

#ifdef LIBQMESYDAQ_LIB
# define LIBQMESYDAQ_EXPORT Q_DECL_EXPORT
#else
# define LIBQMESYDAQ_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBQMESYDAQ_GLOBAL_H
