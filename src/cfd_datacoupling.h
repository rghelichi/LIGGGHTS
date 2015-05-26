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

#ifndef LMP_CFD_DATACOUPLING_H
#define LMP_CFD_DATACOUPLING_H

#include "pointers.h"

namespace LAMMPS_NS {

class CfdDatacoupling : protected Pointers {
 public:

  CfdDatacoupling(class LAMMPS *,int,int, char **,class FixCfdCoupling*);
  ~CfdDatacoupling();

  int get_iarg() {return iarg_;}

  void add_pull_property(char*, char*);
  void add_push_property(char*, char*);

  virtual void pull(char *,char *,void *&, char*);
  virtual void push(char *,char *,void *&, char*);

  virtual void allocate_external(int    **&data, int len2,int len1,int    initvalue);
  virtual void allocate_external(double **&data, int len2,int len1,double initvalue);
  virtual void allocate_external(int    **&data, int len2,char *keyword,int initvalue);
  virtual void allocate_external(double **&data, int len2,char *keyword,double initvalue);

  void init();
  virtual void post_create() {}

  virtual bool error_push()
  { return true;}

  // exchange data with OF
  // does nothing in case of MPI coupling
  // for the MPI case, this is done withing the OF solver
  virtual void exchange() = 0;
  void check_datatransfer();

 protected:

  void grow_();

  // used to find properties
  void* find_pull_property(char *name,char *type,int &len1,int &len2);
  void* find_push_property(char *name,char *type,int &len1,int &len2);
  void* find_property(int, char*, char*, int&, int&);

  // data members

  bool liggghts_is_active;
  bool is_parallel;

  // max # of values stored in pull/push lists
  int nvalues_max_;

  // ------------------------------------
  // per atom or global values stored inchar
  // property fixes used in this fix
  // they are pulled from OF each coupling ts
  // ------------------------------------

  // number of values stored/used in this fix
  int npull_;
  // types can be scalar, vector
  char **pullnames_;
  char **pulltypes_;
  // flag used to check if transfer invoked - only if liggghts is not active
  int *pullinvoked_;

  // ------------------------------------
  // values stored in atom or a fix property
  // that are pushed to OF each coupling ts
  // ------------------------------------

  int npush_;
  char **pushnames_;
  char **pushtypes_;
  // flag used to check if transfer invoked - only if liggghts is not active
  int *pushinvoked_;

  int iarg_;
  class FixCfdCoupling *fc_;

  // multisphere
  class FixMultisphere *ms_;
  class MultisphereParallel *ms_data_;
};

}

#endif
