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
   Contributing authors:
   Christoph Kloss (JKU Linz, DCS Computing GmbH, Linz)
   Philippe Seil (JKU Linz)
------------------------------------------------------------------------- */

#ifndef LMP_MULTI_VECTOR_CONTAINER
#define LMP_MULTI_VECTOR_CONTAINER

#include "general_container.h"

namespace LAMMPS_NS{
  template<typename T, int NUM_VEC, int LEN_VEC>
  class MultiVectorContainer : public GeneralContainer <T, NUM_VEC, LEN_VEC>
  {
      public:
          MultiVectorContainer(char *_id);
          MultiVectorContainer(char *_id, char *_comm, char *_ref, char *_restart, int _scalePower = 1);
          MultiVectorContainer(MultiVectorContainer<T,NUM_VEC,LEN_VEC> const &orig);
          virtual ~MultiVectorContainer();
  };

  /* ----------------------------------------------------------------------
   constructors
  ------------------------------------------------------------------------- */

  template<typename T, int NUM_VEC, int LEN_VEC>
  MultiVectorContainer<T,NUM_VEC,LEN_VEC>::MultiVectorContainer(char *_id)
  : GeneralContainer<T,NUM_VEC,LEN_VEC>(_id)
  {

  }

  template<typename T, int NUM_VEC, int LEN_VEC>
  MultiVectorContainer<T,NUM_VEC,LEN_VEC>::MultiVectorContainer(char *_id, char* _comm, char* _ref, char *_restart,int _scalePower)
  : GeneralContainer<T,NUM_VEC,LEN_VEC>(_id, _comm, _ref,_restart,_scalePower)
  {

  }

  template<typename T, int NUM_VEC, int LEN_VEC>
  MultiVectorContainer<T,NUM_VEC,LEN_VEC>::MultiVectorContainer(MultiVectorContainer<T,NUM_VEC,LEN_VEC> const &orig)
  : GeneralContainer<T,NUM_VEC,LEN_VEC>(orig)
  {

  }

  /* ----------------------------------------------------------------------
   destructor
  ------------------------------------------------------------------------- */

  template<typename T, int NUM_VEC, int LEN_VEC>
  MultiVectorContainer<T,NUM_VEC,LEN_VEC>::~MultiVectorContainer()
  {

  }

} /* LAMMPS_NS */
#endif /* MULTIVECTORCONTAINER_H_ */
