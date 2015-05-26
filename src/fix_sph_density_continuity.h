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

/* ----------------------------------------------------------------------
Contributing author for SPH:
Andreas Aigner (CD Lab Particulate Flow Modelling, JKU)
andreas.aigner@jku.at
------------------------------------------------------------------------- */

#ifdef FIX_CLASS

FixStyle(sph/density/continuity,FixSphDensityContinuity)

#else

#ifndef LMP_FIX_SPH_DENSITY_CONTINUITY_H
#define LMP_FIX_SPH_DENSITY_CONTINUITY_H

#include "fix_sph.h"

namespace LAMMPS_NS {

class FixSphDensityContinuity : public FixSph {
 public:
  FixSphDensityContinuity(class LAMMPS *, int, char **);
  ~FixSphDensityContinuity();
  int setmask();
  void init();
  void pre_force(int);

 private:
  template <int> void pre_force_eval(int);
  double calcDensityDer(double, double, double);

};

}

#endif
#endif
