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

#ifndef LMP_INPUT_MULTISPHERE_H
#define LMP_INPUT_MULTISPHERE_H

#include "stdio.h"
#include "input.h"

namespace LAMMPS_NS {

class InputMultisphere : protected Input {
 public:

  InputMultisphere(class LAMMPS *, int, char **);
  ~InputMultisphere();

  int clmpfile(double **,double*,int);
  void clmpfile(const char *,double **,double*,int);

};
}

#endif
