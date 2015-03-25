/* ============================================================================
Copyright (c) 2010-2014, Broadcom Corporation
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
============================================================================ */

#ifndef WFC_CLIENT_UTILS_H
#define WFC_CLIENT_UTILS_H

#include "interface/khronos/wf/wfc_int.h"

//==============================================================================

#define MAX_DISPLAYS 3

// Values for wfc_source_or_mask_create
#define WFC_IS_SOURCE   1
#define WFC_IS_MASK     0

//==============================================================================

typedef struct _WFC_LINK
{
   struct _WFC_LINK *prev;
   struct _WFC_LINK *next;
} WFC_LINK_T;

typedef void (*WFC_LINK_CALLBACK_T)(WFC_LINK_T *link);

typedef struct
{
   WFCErrorCode error;

   WFC_LINK_T contexts;
} WFC_DEVICE_T;

typedef struct
{
   WFC_LINK_T link;

   WFC_DEVICE_T *device;
   WFC_LINK_T sources;
   WFC_LINK_T masks;
   WFCNativeStreamType output_stream; // for off-screen targets only

   WFC_LINK_T elements_not_in_scene;
   WFC_LINK_T elements_in_scene;
   bool active;

   WFCContextType type;
   uint32_t height;
   uint32_t width;

   WFC_CONTEXT_ATTRIB_T attributes;
} WFC_CONTEXT_T;

typedef struct
{
   WFC_LINK_T link;
   bool is_source;

   WFC_CONTEXT_T *context;

   int refcount;

   WFCNativeStreamType stream;

   bool destroy_pending;
} WFC_SOURCE_OR_MASK_T;

typedef struct
{
   WFC_LINK_T link;
   WFC_CONTEXT_T *context;

   WFC_SOURCE_OR_MASK_T *source;
   WFC_SOURCE_OR_MASK_T *mask;

   WFCNativeStreamType old_source_stream;
   WFCNativeStreamType old_mask_stream;

   bool is_in_scene;

   WFC_ELEMENT_ATTRIB_T attributes;
} WFC_ELEMENT_T;

//==============================================================================

WFC_DEVICE_T *wfc_device_create();
void wfc_device_destroy(WFC_DEVICE_T *device);

WFC_CONTEXT_T *wfc_context_create
   (WFC_DEVICE_T *device_ptr, WFCContextType context_type,
      uint32_t screen_or_stream_num, WFCErrorCode *error);
void wfc_context_destroy(WFC_CONTEXT_T *context);

WFCHandle wfc_source_or_mask_create
   (bool is_source, WFCDevice dev, WFCContext ctx,
      WFCNativeStreamType stream, const WFCint *attribList);
void wfc_source_or_mask_destroy(WFCDevice dev, WFCHandle source_or_mask);
void wfc_source_or_mask_acquire(WFC_SOURCE_OR_MASK_T *source_or_mask_ptr);
void wfc_source_or_mask_release(WFC_SOURCE_OR_MASK_T *source_or_mask_ptr);

void wfc_element_destroy(WFC_ELEMENT_T *element_ptr);

void wfc_commit_callback(WFC_ELEMENT_T *element);

void wfc_set_error(WFC_DEVICE_T *device, WFCErrorCode error);

bool wfc_check_no_attribs(const WFCint *attribList);
bool wfc_device_check_filters(const WFCint *filterList);
bool wfc_is_rotation(WFCint value);
bool wfc_is_scale_filter(WFCint value);
bool wfc_are_transparency_types(WFCint value);

int32_t wfc_round(float f);

void wfc_link_detach(WFC_LINK_T *link);
void wfc_link_attach(WFC_LINK_T *link, WFC_LINK_T *prev);
void wfc_link_init_null(WFC_LINK_T *link);
void wfc_link_init_empty(WFC_LINK_T *link);
void wfc_link_iterate(WFC_LINK_T *link, WFC_LINK_CALLBACK_T func);

#endif /* WFC_CLIENT_UTILS_H */
