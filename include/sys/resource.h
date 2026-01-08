/*
 * Windows compatibility shim for sys/resource.h
 * Redirects to liquid_win32_compat.h on Windows platforms
 *
 * Copyright (c) 2007 - 2025 Joseph Gaeddert
 * MIT License
 */
#ifndef __LIQUID_SYS_RESOURCE_H__
#define __LIQUID_SYS_RESOURCE_H__

#ifdef _WIN32
/* Windows doesn't have sys/resource.h, use our compatibility layer */
#include "liquid_win32_compat.h"
#else
/* On other platforms, include the real sys/resource.h */
/* This should never be reached since this file is only in the include path on Windows */
#error "This shim should only be used on Windows platforms"
#endif

#endif /* __LIQUID_SYS_RESOURCE_H__ */
