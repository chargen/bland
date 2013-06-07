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

static __inline__ int
elem_poly_equal(const elem_poly_struct * poly1, const elem_poly_struct * poly2, const ring_t ring)
{
    long size, i;

    if (poly1->length != poly2->length)
        return 0;

    size = RING_PARENT(ring)->size;

    for (i = 0; i < poly1->length; i++)
        if (!elem_equal(SRC_INDEX(poly1->coeffs, i, size),
                SRC_INDEX(poly2->coeffs, i, size), RING_PARENT(ring)))
            return 0;

    return 1;
}

int
elem_equal(elem_srcptr op1, elem_srcptr op2, const ring_t ring)
{
    switch (ring->type)
    {
        case TYPE_FMPZ:
            return fmpz_equal(op1, op2);

        case TYPE_LIMB:
            return *((mp_srcptr) op1) == *((mp_srcptr) op2);

        case TYPE_POLY:
            return elem_poly_equal(op1, op2, ring);

        case TYPE_MOD:
            return elem_equal(op1, op2, ring->parent);

        case TYPE_FRAC:
            return elem_equal(NUMER(op1, ring), NUMER(op2, ring), RING_NUMER(ring)) &&
                    elem_equal(DENOM(op1, ring), DENOM(op2, ring), RING_DENOM(ring));

        case TYPE_COMPLEX:
            return elem_equal(REALPART(op1, ring), REALPART(op2, ring), RING_PARENT(ring)) &&
                    elem_equal(IMAGPART(op1, ring), IMAGPART(op2, ring), RING_PARENT(ring));

        default:
            NOT_IMPLEMENTED("equal", ring);
    }
}

