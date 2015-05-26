/* ----------------------------------------------------------------------
   LIGGGHTS - LAMMPS Improved for General Granular and Granular Heat
   Transfer Simulations

   LIGGGHTS is part of the CFDEMproject
   www.liggghts.com | www.cfdem.com

   Christoph Kloss, christoph.kloss@cfdem.com
   Copyright 2009-2012 JKU Linz
   Copyright 2012-     DCS Computing GmbH, Linz

   LIGGGHTS is based on LAMMPS
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   This software is distributed under the GNU General Public License.

   See the README file in the top-level directory.
------------------------------------------------------------------------- */

#ifndef LMP_COMM_I_H
#define LMP_COMM_I_H

#include "atom.h"
#include "domain_wedge.h"

using namespace LAMMPS_NS;

/* ----------------------------------------------------------------------
   decide if border element, optimization for granular
------------------------------------------------------------------------- */

inline bool Comm::decide(int i,int dim,double lo,double hi,int ineed)
{
    double **x = atom->x;
    double *radius = atom->radius;

    if( ((ineed % 2 == 0) && x[i][dim] >= lo && x[i][dim] <= (hi + (radius? (radius[i]) : 0.)) ) ||
        ((ineed % 2 == 1) && x[i][dim] >= (lo - (radius? radius[i] : 0.)) && x[i][dim] <= hi )   )
        return true;

    return false;
}

/* ----------------------------------------------------------------------
   decide if border element for wedge case, optimization for granular
------------------------------------------------------------------------- */

inline bool Comm::decide_wedge(int i,int dim,double lo,double hi,int ineed)
{
    double **x = atom->x;
    double *radius = atom->radius;
    double coo[2],d[2];
    coo[0] = x[i][iphi];
    coo[1] = x[i][(iphi+1)%3];

    if (ineed % 2 == 0)
    {
        vectorSubtract2D(coo,pleft,d);
        if(vectorDot2D(d,nleft) >= -(radius? radius[i] : 0.))
        {
            
            return true;
        }
    }
    
    else if (ineed % 2 == 1)
    {
        vectorSubtract2D(coo,pright,d);
        if(vectorDot2D(d,nright) >= -(radius? radius[i] : 0.))
        {
            
            return true;
        }
    }
    
    return false;
}

#endif
