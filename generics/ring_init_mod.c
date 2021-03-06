/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Fredrik Johansson

******************************************************************************/

#include "generics.h"

void
ring_init_mod(ring_t ring, const ring_t elem_ring, elem_srcptr modulus)
{
    ring->type = TYPE_MOD;
    ring->size = elem_ring->size;
    ring->parent = (ring_struct *) elem_ring;

    ring->modulus = (elem_ptr) modulus;   /* should this make a copy? */
    if (elem_ring->type == TYPE_LIMB)
        nmod_init(&ring->nmod, *((mp_ptr) modulus));
}
