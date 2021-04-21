
#ifndef DMXLSX_EXPORT_H
#define DMXLSX_EXPORT_H

#ifdef DMXLSX_STATIC_DEFINE
#  define DMXLSX_EXPORT
#  define DMXLSX_NO_EXPORT
#else
#  ifndef DMXLSX_EXPORT
#    ifdef dmxlsx_EXPORTS
        /* We are building this library */
#      define DMXLSX_EXPORT 
#    else
        /* We are using this library */
#      define DMXLSX_EXPORT 
#    endif
#  endif

#  ifndef DMXLSX_NO_EXPORT
#    define DMXLSX_NO_EXPORT 
#  endif
#endif

#ifndef DMXLSX_DEPRECATED
#  define DMXLSX_DEPRECATED __declspec(deprecated)
#endif

#ifndef DMXLSX_DEPRECATED_EXPORT
#  define DMXLSX_DEPRECATED_EXPORT DMXLSX_EXPORT DMXLSX_DEPRECATED
#endif

#ifndef DMXLSX_DEPRECATED_NO_EXPORT
#  define DMXLSX_DEPRECATED_NO_EXPORT DMXLSX_NO_EXPORT DMXLSX_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef DMXLSX_NO_DEPRECATED
#    define DMXLSX_NO_DEPRECATED
#  endif
#endif

#endif /* DMXLSX_EXPORT_H */
