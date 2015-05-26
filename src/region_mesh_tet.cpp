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

#include "stdlib.h"
#include "string.h"
#include "region_mesh_tet.h"
#include "lammps.h"
#include "memory.h"
#include "error.h"
#include "domain.h"
#include "vector_liggghts.h"
#include "mpi_liggghts.h"
#include "math.h"
#include "math_extra_liggghts.h"
#include "random_park.h"
#include "input_mesh_tet.h"

#define DELTA_TET 1000
#define BIG 1.e20

using namespace LAMMPS_NS;

/* ---------------------------------------------------------------------- */

RegTetMesh::RegTetMesh(LAMMPS *lmp, int narg, char **arg) :
  Region(lmp, narg, arg)
{
  if(narg < 14) error->all(FLERR,"Illegal region mesh/tet command");
  options(narg-14,&arg[14]);

  if(scaleflag) error->all(FLERR,"Lattice scaling not implemented for region mesh/tet, please use 'units box'");

  if(strcmp(arg[2],"file"))
    error->all(FLERR,"Illegal region mesh/tet command, expecting keyword 'scale'");
  char *filename = arg[3];

  if(strcmp(arg[4],"scale"))
    error->all(FLERR,"Illegal region mesh/tet command, expecting keyword 'scale'");
  scale_fact = atof(arg[5]);
  if(strcmp(arg[6],"move"))
    error->all(FLERR,"Illegal region mesh/tet command, expecting keyword 'move'");
  off_fact[0] = atof(arg[7]);
  off_fact[1] = atof(arg[8]);
  off_fact[2] = atof(arg[9]);
  if(strcmp(arg[10],"rotate"))
    error->all(FLERR,"Illegal region mesh/tet command, expecting keyword 'rotate'");
  rot_angle[0] = atof(arg[11]);
  rot_angle[1] = atof(arg[12]);
  rot_angle[2] = atof(arg[13]);

  node = NULL;
  volume = NULL;
  acc_volume = NULL;
  nTet = 0;
  nTetMax = 0;
  total_volume = 0.;

  // manage input
  InputMeshTet *my_input = new InputMeshTet(lmp, 0, NULL);
  my_input->meshtetfile(filename,this,true);
  delete my_input;

  // extent of sphere

  if (interior) {
    bboxflag = 1;
    set_extent();
  } else bboxflag = 0;

  cmax = 1;
  contact = new Contact[cmax];
}

/* ---------------------------------------------------------------------- */

RegTetMesh::~RegTetMesh()
{
  delete [] contact;

  memory->destroy(node);
  memory->sfree(volume);
  memory->sfree(acc_volume);
}

/* ----------------------------------------------------------------------
   inside = 1 if x,y,z is inside or on surface
   inside = 0 if x,y,z is outside and not on surface
------------------------------------------------------------------------- */

int RegTetMesh::inside(double x, double y, double z)
{
   double pos[3];
   pos[0] = x; pos[1] = y; pos[2] = z;

   // check subdomain
   if(!domain->is_in_subdomain(pos)) return 0;

   // check bbox, only if exists
   if(bboxflag)
   {
       if(pos[0] < extent_xlo || pos[0] > extent_xhi) return 0;
       if(pos[1] < extent_ylo || pos[1] > extent_yhi) return 0;
       if(pos[2] < extent_zlo || pos[2] > extent_zhi) return 0;
   }

   // brute force naive search
   int inside_mesh = 0;
   for(int i = 0; i < nTet; i++)
   {
        inside_mesh = inside_mesh + is_inside_tet(i,pos);
        if(inside_mesh) break;
   }

   //fprintf(screen,"checking pos %f %f %f, result %d; ntet %d\n",x,y,z,inside_mesh,nTet);

   return inside_mesh;
}

/* ---------------------------------------------------------------------- */

int RegTetMesh::surface_interior(double *x, double cutoff)
{
  error->one(FLERR,"This feature is not available for tet mesh regions");
  return 0;
}

/* ---------------------------------------------------------------------- */

int RegTetMesh::surface_exterior(double *x, double cutoff)
{
  error->one(FLERR,"This feature is not available for tet mesh regions");
  return 0;
}

/* ---------------------------------------------------------------------- */

void RegTetMesh::generate_random(double *pos)
{
    if(!interior) error->all(FLERR,"Impossible to generate random points on tet mesh region with side = out");
    mesh_randpos(pos);
}

/* ---------------------------------------------------------------------- */

void RegTetMesh::generate_random_cut(double *pos,double cut)
{
    if(!interior) error->all(FLERR,"Impossible to generate random points on tet mesh region with side = out");
    error->all(FLERR,"This feature is not available for tet mesh regions");

}

/* ---------------------------------------------------------------------- */

void RegTetMesh::add_tet(double **n)
{
    if(nTet == nTetMax) grow_arrays();

    for(int i=0;i<4;i++)
        vectorCopy3D(n[i],node[nTet][i]);

    double vol = volume_of_tet(nTet);
    if(vol < 0.)
    {
        // flip nodes 0 and 3
        double node0[3];
        vectorCopy3D(node[nTet][0],node0);
        vectorCopy3D(node[nTet][3],node[nTet][0]);
        vectorCopy3D(node0,node[nTet][3]);
    }

    vol = volume_of_tet(nTet);
    if(vol < 0.) error->all(FLERR,"Fatal error: RegTetMesh::add_tet: vol < 0");

    volume[nTet] = vol;
    total_volume += volume[nTet];
    acc_volume[nTet] = volume[nTet];
    if(nTet > 0) acc_volume[nTet] += acc_volume[nTet-1];
    nTet++;
}

/* ---------------------------------------------------------------------- */

void RegTetMesh::grow_arrays()
{
    nTetMax += DELTA_TET;
    node = (double***)(memory->grow(node,nTetMax, 4 , 3, "vtk_tet_node"));
    volume = (double*)(memory->srealloc(volume,nTetMax*sizeof(double),"vtk_tet_volume"));
    acc_volume = (double*)(memory->srealloc(acc_volume,nTetMax*sizeof(double),"vtk_tet_acc_volume"));
}

/* ---------------------------------------------------------------------- */

int RegTetMesh::n_tet()
{
    return nTet;
}

/* ---------------------------------------------------------------------- */

double RegTetMesh::total_vol()
{
    return total_volume;
}

/* ---------------------------------------------------------------------- */

double RegTetMesh::tet_vol(int i)
{
    return volume[i];
}

/* ---------------------------------------------------------------------- */

double RegTetMesh::tet_acc_vol(int i)
{
    return acc_volume[i];
}

/* ---------------------------------------------------------------------- */

inline double RegTetMesh::volume_of_tet(int iTet)
{
    return volume_of_tet(node[iTet][0],node[iTet][1],node[iTet][2],node[iTet][3]);
}

/* ---------------------------------------------------------------------- */

inline int RegTetMesh::is_inside_tet(int iTet,double *pos)
{
    double vol1,vol2,vol3,vol4;

    vol1 = volume_of_tet(node[iTet][0], node[iTet][1], node[iTet][2], pos          );
    vol2 = volume_of_tet(node[iTet][0], node[iTet][1], pos,           node[iTet][3]);
    vol3 = volume_of_tet(node[iTet][0], pos,           node[iTet][2], node[iTet][3]);
    vol4 = volume_of_tet(pos          , node[iTet][1], node[iTet][2], node[iTet][3]);

    if(vol1 > 0. && vol2 > 0. && vol3 > 0. && vol4 > 0.) return 1;
    return 0;
}

/* ---------------------------------------------------------------------- */

double RegTetMesh::volume_of_tet(double* v0, double* v1, double* v2, double* v3)
{
   double A[3];
   A[0] = v3[0] - v1[0];
   A[1] = v3[1] - v1[1];
   A[2] = v3[2] - v1[2];

   double B[3];
   B[0] = v2[0] - v1[0];
   B[1] = v2[1] - v1[1];
   B[2] = v2[2] - v1[2];

   double C[3];
   C[0] = v0[0] - v1[0];
   C[1] = v0[1] - v1[1];
   C[2] = v0[2] - v1[2];

   // cross product A x B
   double cp[] = {
       A[1]*B[2] - A[2]*B[1],
      -A[0]*B[2] + A[2]*B[0],
       A[0]*B[1] - A[1]*B[0]
   };

   // dot with C
   double volume = cp[0] * C[0] + cp[1] * C[1] + cp[2] * C[2];
   volume /= 6.;
   return volume;
}

/* ---------------------------------------------------------------------- */

inline void RegTetMesh::set_extent()
{
    extent_xlo = extent_ylo = extent_zlo =  BIG;
    extent_xhi = extent_yhi = extent_zhi = -BIG;

    for(int i = 0; i < nTet; i++)
        for(int j=0;j<4;j++)
        {
            if(node[i][j][0] < extent_xlo) extent_xlo = node[i][j][0];
            if(node[i][j][1] < extent_ylo) extent_ylo = node[i][j][1];
            if(node[i][j][2] < extent_zlo) extent_zlo = node[i][j][2];

            if(node[i][j][0] > extent_xhi) extent_xhi = node[i][j][0];
            if(node[i][j][1] > extent_yhi) extent_yhi = node[i][j][1];
            if(node[i][j][2] > extent_zhi) extent_zhi = node[i][j][2];
        }
}

/* ---------------------------------------------------------------------- */

void RegTetMesh::volume_mc(int n_test,double &vol_global, double &vol_local)
{
    double pos[3],  vol_local_all;
    int n_in_local = 0, n_in_global = 0, n_in_global_all;

    if(total_volume == 0.) error->all(FLERR,"mesh/tet region has zero volume, cannot continue");

    vol_global = total_volume;

    for(int i = 0; i < n_test; i++)
    {
        pos[0] = extent_xlo + random->uniform() * (extent_xhi - extent_xlo);
        pos[1] = extent_ylo + random->uniform() * (extent_yhi - extent_ylo);
        pos[2] = extent_zlo + random->uniform() * (extent_zhi - extent_zlo);

        if(!domain->is_in_domain(pos)) continue;

        // point is in region
        // assume every proc can evaluate this
        
        if(match(pos[0],pos[1],pos[2]))
        {
            n_in_global++;
            if(domain->is_in_subdomain(pos))
                n_in_local++;
        }
    }

    MPI_Sum_Scalar(n_in_global,n_in_global_all,world);
    if(n_in_global_all == 0)
        error->all(FLERR,"Unable to calculate region volume - are you operating on a 2d region?");

    // return calculated values
    if(n_in_global == 0)
        vol_local = 0.;
    else
        vol_local  = static_cast<double>(n_in_local )/static_cast<double>(n_in_global) * vol_global;

    // sum of local volumes will not be equal to global volume because of
    // different random generator states - correct this now
    MPI_Sum_Scalar(vol_local,vol_local_all,world);
    vol_local *= (vol_global/vol_local_all);

}

/* ---------------------------------------------------------------------- */

inline void RegTetMesh::mesh_randpos(double *pos)
{
    tet_randpos(tet_rand_tri(),pos);
    if(pos[0] == 0. && pos[1] == 0. && pos[2] == 0.) error->all(FLERR,"illegal RegTetMesh::mesh_randpos");
}

/* ---------------------------------------------------------------------- */

inline int RegTetMesh::tet_rand_tri()
{

    double rd = total_volume * random->uniform();
    int chosen = 0;
    while (rd > acc_volume[chosen] && chosen < nTet-1) chosen++;
    return chosen;
}

/* ---------------------------------------------------------------------- */

inline void RegTetMesh::tet_randpos(int iTet,double *pos)
{

    double bary_coo[4];

    double s = random->uniform();
    double t = random->uniform();
    double u = random->uniform();

    if(s+t > 1.)
    {
        s = 1.-s;
        t = 1.-t;
    }
    if(t+u > 1.)
    {
        double tmp = u;
        u = 1.-s-t;
        t = 1.-tmp;
    }
    else if(s+t+u > 1.)
    {
        double tmp = u;
        u = s+t+u-1.;
        s = 1.-t-tmp;
    }
    bary_coo[0] = 1.-s-t-u;
    bary_coo[1] = s;
    bary_coo[2] = t;
    bary_coo[3] = u;

    bary_to_cart(iTet,bary_coo,pos);

}

/* ---------------------------------------------------------------------- */

inline void RegTetMesh::bary_to_cart(int iTet,double *bary_coo,double *pos)
{
    for(int i=0;i<3;i++)
       pos[i] = bary_coo[0] * node[iTet][0][i] + bary_coo[1] * node[iTet][1][i] + bary_coo[2] * node[iTet][2][i] + bary_coo[3] * node[iTet][3][i];
}
