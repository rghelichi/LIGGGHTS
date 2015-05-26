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

#ifdef REGION_CLASS

RegionStyle(mesh/tet,RegTetMesh)

#else

#ifndef LMP_REGION_TET_MESH_H
#define LMP_REGION_TET_MESH_H

#include "region.h"

namespace LAMMPS_NS {

class RegTetMesh : public Region {

 friend class InputMeshTet;

 public:

  RegTetMesh(class LAMMPS *, int, char **);
  ~RegTetMesh();
  int inside(double, double, double);
  int surface_interior(double *, double);
  int surface_exterior(double *, double);

  // volume calculation based on MC
  virtual void volume_mc(int,double&,double&);

  void add_tet(double **n);
  int n_tet();
  double total_vol();
  double tet_vol(int i);
  double tet_acc_vol(int i);

 protected:

   int is_inside_tet(int iTet,double *pos);

   virtual void generate_random(double *);
   virtual void generate_random_cut(double *,double);

   void grow_arrays();
   void set_extent();
   double volume_of_tet(double* v0, double* v1, double* v2, double* v3);
   double volume_of_tet(int iTet);

   void mesh_randpos(double *pos);
   int  tet_rand_tri();
   void tet_randpos(int iTet,double *pos);
   void bary_to_cart(int iTet,double *bary_coo,double *pos);

   char *filename;
   double scale_fact;
   double off_fact[3], rot_angle[3];

   int nTet,nTetMax;
   double ***node;
   double total_volume;
   double *volume;
   double *acc_volume;
};

}

#endif
#endif
