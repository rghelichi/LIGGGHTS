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

#ifdef PAIR_CLASS

PairStyle(sph/artVisc/tensCorr,PairSphArtviscTenscorr)

#else

#ifndef LMP_PAIR_SPH_ARTVISC_TENSCORR_H
#define LMP_PAIR_SPH_ARTVISC_TENSCORR_H

#include "pair_sph.h"

namespace LAMMPS_NS {

class PairSphArtviscTenscorr : public PairSph {

 friend class FixSPH;

 public:

  PairSphArtviscTenscorr(class LAMMPS *);
  ~PairSphArtviscTenscorr();
  void compute(int, int);
  void settings(int, char **);
  void coeff(int, char **);
  void init_substyle();
  void write_restart(FILE *);
  void read_restart(FILE *);
  void write_restart_settings(FILE *);
  void read_restart_settings(FILE *);

 protected:
  void allocate();
//  void allocate_properties(int);
//  double artificialViscosity(int, int, int, int, double, double, double, double, double, double, double, double **);
//  template <int> void tensileCorrection(int, int, double, double, double, double, double, double, double, double &, double &);
  template <int> void compute_eval(int, int);

  class   FixPropertyGlobal* cs;
  double  **csmean;

  double  **wDeltaPTypeinv;

  int     artVisc_flag, tensCorr_flag; // flags for additional styles
  double  alpha,beta,eta; // coeffs for artifical viscosity
  double  epsilon,deltaP; // coeffs for tensile correction

};

}

#endif
#endif
