/* ============================================================================
Copyright (c) 2008-2014, Broadcom Corporation
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
============================================================================ */

#ifndef VCOS_GENERIC_QUICKSLOW_MUTEX_H
#define VCOS_GENERIC_QUICKSLOW_MUTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "interface/vcos/vcos_types.h"
#include "vcos_platform.h"

/**
 * \file
 *
 * Quickslow Mutexes implemented as regular ones (i.e. quick and slow modes are the same).
 *
 */

typedef VCOS_MUTEX_T VCOS_QUICKSLOW_MUTEX_T;

#if defined(VCOS_INLINE_BODIES)
VCOS_INLINE_IMPL
VCOS_STATUS_T vcos_quickslow_mutex_create(VCOS_QUICKSLOW_MUTEX_T *m, const char *name)
{
   return vcos_mutex_create(m, name);
}

VCOS_INLINE_IMPL
void vcos_quickslow_mutex_delete(VCOS_QUICKSLOW_MUTEX_T *m)
{
   vcos_mutex_delete(m);
}

VCOS_INLINE_IMPL
void vcos_quickslow_mutex_lock(VCOS_QUICKSLOW_MUTEX_T *m)
{
   while (vcos_mutex_lock(m) == VCOS_EAGAIN);
}

VCOS_INLINE_IMPL
void vcos_quickslow_mutex_unlock(VCOS_QUICKSLOW_MUTEX_T *m)
{
   vcos_mutex_unlock(m);
}

VCOS_INLINE_IMPL
void vcos_quickslow_mutex_lock_quick(VCOS_QUICKSLOW_MUTEX_T *m)
{
   while (vcos_mutex_lock(m) == VCOS_EAGAIN);
}

VCOS_INLINE_IMPL
void vcos_quickslow_mutex_unlock_quick(VCOS_QUICKSLOW_MUTEX_T *m)
{
   vcos_mutex_unlock(m);
}

#endif


#ifdef __cplusplus
}
#endif
#endif


