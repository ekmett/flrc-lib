/*
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 1.   Redistributions of source code must retain the above copyright notice, this list of 
 * conditions and the following disclaimer.
 * 2.   Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "pgc/pgc.h"
#include <stddef.h>

unsigned g_tls_offset_bytes = 0;
unsigned local_nursery_size = 0;
unsigned g_use_pub_priv     = 0;

void STDCALL_FUNC_OUT (STDCALL_FUNC_IN *gc_heap_slot_write_barrier_indirect)(
			Managed_Object_Handle p_base_of_object_with_slot,
            Managed_Object_Handle *p_slot,
            Managed_Object_Handle value);
void STDCALL_FUNC_OUT (STDCALL_FUNC_IN *gc_heap_slot_write_interior_indirect)(
			Managed_Object_Handle *p_slot,
            Managed_Object_Handle value,
			unsigned offset);
void STDCALL_FUNC_OUT (STDCALL_FUNC_IN *gc_heap_slot_write_barrier_indirect_prt)(
			Managed_Object_Handle p_base_of_object_with_slot,
            Managed_Object_Handle *p_slot,
            Managed_Object_Handle value,
#ifndef NO_P2C_TH
            PrtTaskHandle taskHandle,
#endif  // NO_P2C_TH
            void *prev_frame);
void STDCALL_FUNC_OUT (STDCALL_FUNC_IN *gc_heap_slot_write_interior_indirect_prt)(
			Managed_Object_Handle *p_slot,
            Managed_Object_Handle value,
			unsigned offset,
#ifndef NO_P2C_TH
            PrtTaskHandle taskHandle,
#endif  // NO_P2C_TH
            void *prev_frame);

// CAS versions
Managed_Object_Handle STDCALL_FUNC_OUT (STDCALL_FUNC_IN *gc_cas_write_barrier_indirect)(
			Managed_Object_Handle p_base_of_object_with_slot,
            Managed_Object_Handle *p_slot,
            Managed_Object_Handle value,
            Managed_Object_Handle cmp);
Managed_Object_Handle STDCALL_FUNC_OUT (STDCALL_FUNC_IN *gc_cas_write_interior_indirect)(
			Managed_Object_Handle *p_slot,
            Managed_Object_Handle value,
			unsigned offset,
            Managed_Object_Handle cmp);
Managed_Object_Handle STDCALL_FUNC_OUT (STDCALL_FUNC_IN *gc_cas_write_barrier_indirect_prt)(
			Managed_Object_Handle p_base_of_object_with_slot,
            Managed_Object_Handle *p_slot,
            Managed_Object_Handle value,
            Managed_Object_Handle cmp,
#ifndef NO_P2C_TH
            PrtTaskHandle taskHandle,
#endif  // NO_P2C_TH
            void *prev_frame);
Managed_Object_Handle STDCALL_FUNC_OUT (STDCALL_FUNC_IN *gc_cas_write_interior_indirect_prt)(
			Managed_Object_Handle *p_slot,
            Managed_Object_Handle value,
			unsigned offset,
            Managed_Object_Handle cmp,
#ifndef NO_P2C_TH
            PrtTaskHandle taskHandle,
#endif  // NO_P2C_TH
            void *prev_frame);

void CDECL_FUNC_OUT (CDECL_FUNC_IN *gc_mark_profiler)(unsigned gc_num, unsigned gc_thread_id, void * live_object) = NULL;
