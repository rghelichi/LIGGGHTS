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

#include "custom_value_tracker.h"

using namespace LAMMPS_NS;

  /* ----------------------------------------------------------------------
   constructor, destructor
  ------------------------------------------------------------------------- */

  CustomValueTracker::CustomValueTracker(LAMMPS *lmp,AbstractMesh *_ownerMesh)
   : Pointers(lmp),
     ownerMesh_(_ownerMesh),
     capacityElement_(0)
  {
  }

  CustomValueTracker::CustomValueTracker(LAMMPS *lmp)
   : Pointers(lmp),
     ownerMesh_(NULL),
     capacityElement_(0)
  {
  }

  CustomValueTracker::~CustomValueTracker()
  {
  }

  /* ----------------------------------------------------------------------
   memory management
  ------------------------------------------------------------------------- */

  int CustomValueTracker::getCapacity()
  {
    return capacityElement_;
  }

  /* ----------------------------------------------------------------------
   remove property
  ------------------------------------------------------------------------- */

  void CustomValueTracker::removeElementProperty(char *_id)
  {
     elementProperties_.remove(_id);
  }

  void CustomValueTracker::removeGlobalProperty(char *_id)
  {
     globalProperties_.remove(_id);
     globalProperties_orig_.remove(_id);
  }

  /* ----------------------------------------------------------------------
   store current values of global properties as orig
  ------------------------------------------------------------------------- */

  void CustomValueTracker::storeOrig()
  {
      
      globalProperties_.storeOrig(globalProperties_orig_);
      
  }

  /* ----------------------------------------------------------------------
   reset global properties to orig
  ------------------------------------------------------------------------- */

  void CustomValueTracker::resetToOrig()
  {
      
      globalProperties_.reset(globalProperties_orig_);
      
  }

  /* ----------------------------------------------------------------------
   rotate all properties, applies to vector and multivector only
  ------------------------------------------------------------------------- */

  void CustomValueTracker::rotate(double *totalQ,double *dQ)
  {
      
      elementProperties_.rotate(dQ);
      globalProperties_.rotate(totalQ);
  }

  void CustomValueTracker::rotate(double *dQ)
  {
      
      elementProperties_.rotate(dQ);
      globalProperties_.rotate(dQ);
  }

  /* ----------------------------------------------------------------------
   scale all properties, applies to vectors and multivectors only
  ------------------------------------------------------------------------- */

  void CustomValueTracker::scale(double factor)
  {
      
      elementProperties_.scale(factor);
      globalProperties_.scale(factor);
  }

  /* ----------------------------------------------------------------------
   move all properties
  ------------------------------------------------------------------------- */

  void CustomValueTracker::move(double *vecTotal, double *vecIncremental)
  {
      
      elementProperties_.move(vecIncremental);
      globalProperties_.move(vecTotal);
  }

  void CustomValueTracker::move(double *vecIncremental)
  {
      
      elementProperties_.move(vecIncremental);
      globalProperties_.move(vecIncremental);
  }

  /* ----------------------------------------------------------------------
   clear reverse properties, i.e. reset all of them to 0
  ------------------------------------------------------------------------- */

  void CustomValueTracker::clearReverse(bool scale,bool translate,bool rotate)
  {
      
      elementProperties_.clearReverse(scale,translate,rotate);
  }
