/* mm.h - prototypes and declarations for memory manager */
/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2002,2007  Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GRUB_MM_H
#define GRUB_MM_H	1

#include <grub/types.h>
#include <grub/symbol.h>
#include <grub/err.h>
#include <config.h>

#ifndef NULL
# define NULL	((void *) 0)
#endif

void grub_mm_init_region (void *addr, grub_size_t size);
void *EXPORT_FUNC(grub_calloc) (grub_size_t nmemb, grub_size_t size);
void *EXPORT_FUNC(grub_malloc) (grub_size_t size);
void *EXPORT_FUNC(grub_zalloc) (grub_size_t size);
void EXPORT_FUNC(grub_free) (void *ptr);
void *EXPORT_FUNC(grub_realloc) (void *ptr, grub_size_t size);
#ifndef GRUB_MACHINE_EMU
void *EXPORT_FUNC(grub_memalign) (grub_size_t align, grub_size_t size);
#endif

#define GRUB_MEM_ATTR_R	0x0000000000000004LLU
#define GRUB_MEM_ATTR_W	0x0000000000000002LLU
#define GRUB_MEM_ATTR_X	0x0000000000000001LLU

#ifdef GRUB_MACHINE_EFI
grub_err_t EXPORT_FUNC(grub_get_mem_attrs) (grub_addr_t addr,
					    grub_size_t size,
					    grub_uint64_t *attrs);
grub_err_t EXPORT_FUNC(grub_update_mem_attrs) (grub_addr_t addr,
					       grub_size_t size,
					       grub_uint64_t set_attrs,
					       grub_uint64_t clear_attrs);
#else /* !GRUB_MACHINE_EFI */
static inline grub_err_t
grub_get_mem_attrs (grub_addr_t addr __attribute__((__unused__)),
		    grub_size_t size __attribute__((__unused__)),
		    grub_uint64_t *attrs __attribute__((__unused__)))
{
  return GRUB_ERR_NONE;
}

static inline grub_err_t
grub_update_mem_attrs (grub_addr_t addr __attribute__((__unused__)),
		       grub_size_t size __attribute__((__unused__)),
		       grub_uint64_t set_attrs __attribute__((__unused__)),
		       grub_uint64_t clear_attrs __attribute__((__unused__)))
{
  return GRUB_ERR_NONE;
}
#endif /* GRUB_MACHINE_EFI */

void grub_mm_check_real (const char *file, int line);
#define grub_mm_check() grub_mm_check_real (GRUB_FILE, __LINE__);

/* For debugging.  */
#if defined(MM_DEBUG) && !defined(GRUB_UTIL) && !defined (GRUB_MACHINE_EMU)
/* Set this variable to 1 when you want to trace all memory function calls.  */
extern int EXPORT_VAR(grub_mm_debug);

void grub_mm_dump_free (void);
void grub_mm_dump (unsigned lineno);

#define grub_calloc(nmemb, size)	\
  grub_debug_calloc (GRUB_FILE, __LINE__, nmemb, size)

#define grub_malloc(size)	\
  grub_debug_malloc (GRUB_FILE, __LINE__, size)

#define grub_zalloc(size)	\
  grub_debug_zalloc (GRUB_FILE, __LINE__, size)

#define grub_realloc(ptr,size)	\
  grub_debug_realloc (GRUB_FILE, __LINE__, ptr, size)

#define grub_memalign(align,size)	\
  grub_debug_memalign (GRUB_FILE, __LINE__, align, size)

#define grub_free(ptr)	\
  grub_debug_free (GRUB_FILE, __LINE__, ptr)

void *EXPORT_FUNC(grub_debug_calloc) (const char *file, int line,
				      grub_size_t nmemb, grub_size_t size);
void *EXPORT_FUNC(grub_debug_malloc) (const char *file, int line,
				      grub_size_t size);
void *EXPORT_FUNC(grub_debug_zalloc) (const char *file, int line,
				       grub_size_t size);
void EXPORT_FUNC(grub_debug_free) (const char *file, int line, void *ptr);
void *EXPORT_FUNC(grub_debug_realloc) (const char *file, int line, void *ptr,
				       grub_size_t size);
void *EXPORT_FUNC(grub_debug_memalign) (const char *file, int line,
					grub_size_t align, grub_size_t size);
#endif /* MM_DEBUG && ! GRUB_UTIL */

#endif /* ! GRUB_MM_H */
