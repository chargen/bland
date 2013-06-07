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

static __inline__ mp_limb_t
nmod_set_ui(ulong v, nmod_t mod)
{
    mp_limb_t u = n_mod2_preinv(v, mod.n, mod.ninv);
    return u;
}

void
elem_poly_set_ui(elem_poly_struct * poly, ulong value, const ring_t ring)
{
    elem_poly_fit_length(poly, 1, ring);
    elem_set_ui(poly->coeffs, value, ring->parent);
    elem_poly_set_length(poly, 1, ring);
    elem_poly_normalise(poly, ring);
}

void
elem_set_ui(elem_ptr elem, ulong v, const ring_t ring)
{
    switch (ring->type)
    {
        case TYPE_FMPZ:
            fmpz_set_ui(elem, v);
            break;

        case TYPE_LIMB:
            *((mp_ptr) elem) = v;
            break;

        case TYPE_POLY:
            elem_poly_set_ui(elem, v, ring);
            break;

        case TYPE_MOD:
            {
                switch (RING_PARENT(ring)->type)
                {
                    case TYPE_FMPZ:
                        fmpz_set_ui(elem, v);
                        fmpz_mod(elem, elem, RING_MODULUS(ring));
                        break;

                    case TYPE_LIMB:
                        *((mp_ptr) elem) = nmod_set_ui(v, ring->nmod);
                        break;

                    default:
                        NOT_IMPLEMENTED("set_ui (mod)", ring);
                }
            }
            break;

        case TYPE_FRAC:
            elem_set_ui(NUMER(elem, ring), v, RING_NUMER(ring));
            elem_one(DENOM(elem, ring), RING_DENOM(ring));
            break;

        case TYPE_COMPLEX:
            elem_set_ui(REALPART(elem, ring), v, ring->parent);
            elem_zero(IMAGPART(elem, ring), ring->parent);
            break;

        default:
            NOT_IMPLEMENTED("set_si", ring);
    }
}

