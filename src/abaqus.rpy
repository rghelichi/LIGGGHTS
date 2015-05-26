# -*- coding: mbcs -*-
#
# Abaqus/CAE Release 6.14-2 replay file
# Internal Version: 2014_08_22-09.53.04 134497
# Run by ramin on Tue Apr 28 17:05:08 2015
#

# from driverUtils import executeOnCaeGraphicsStartup
# executeOnCaeGraphicsStartup()
#: Executing "onCaeGraphicsStartup()" in the site directory ...
from abaqus import *
from abaqusConstants import *
session.Viewport(name='Viewport: 1', origin=(0.0, 0.0), width=291.041656494141, 
    height=201.219039916992)
session.viewports['Viewport: 1'].makeCurrent()
session.viewports['Viewport: 1'].maximize()
from caeModules import *
from driverUtils import executeOnCaeStartup
executeOnCaeStartup()
session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
    referenceRepresentation=ON)
a = mdb.models['Model-1'].rootAssembly
session.viewports['Viewport: 1'].setValues(displayedObject=a)
mdb.ModelFromInputFile(name='3D-Beam', 
    inputFileName='/home/ramin/Dropbox/02Fretting/Beam Model/3D-Beam.inp')
#: The model "3D-Beam" has been created.
#: The part "PART-1" has been imported from the input file.
#: The section "ConnProp-1_DIMPLE_X_1_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-2_DIMPLE_X_2_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-3_DIMPLE_Y_1_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-4_DIMPLE_Y_2_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-5_SPRING_X_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-6_SPRING_Y_2" has been assigned to 1 wire or attachment line.
#: AbaqusException: The Time-Amplitude table should have at least two rows of data. This occurred while processing amplitude definition AMP-LOC1_X_SPAN1. Amplitude definition will be ignored. 
#: The model "3D-Beam" has been imported from an input file. 
#: Please scroll up to check for error and warning messages.
session.viewports['Viewport: 1'].assemblyDisplay.setValues(
    optimizationTasks=OFF, geometricRestrictions=OFF, stopConditions=OFF)
a = mdb.models['3D-Beam'].rootAssembly
session.viewports['Viewport: 1'].setValues(displayedObject=a)
session.viewports['Viewport: 1'].view.setValues(nearPlane=1.92329, 
    farPlane=2.75745, width=0.881588, height=0.495715, viewOffsetX=-0.021025, 
    viewOffsetY=0.0173647)
session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON, 
    predefinedFields=ON, connectors=ON)
mdb.ModelFromInputFile(name='Billlax', 
    inputFileName='/home/ramin/Dropbox/02Fretting/Beam Model/Billlax.inp')
#: The model "Billlax" has been created.
#: The part "PART-1" has been imported from the input file.
#: The section "ConnProp-1_DIMPLE_X_1_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-2_DIMPLE_X_2_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-3_DIMPLE_Y_1_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-4_DIMPLE_Y_2_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-5_SPRING_X_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-6_SPRING_Y_2" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-7_DIMPLE_X_1_3" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-8_DIMPLE_X_2_3" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-9_DIMPLE_Y_1_3" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-10_DIMPLE_Y_2_3" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-11_SPRING_X_3" has been assigned to 1 wire or attachment line.
#: The section "ConnProp-12_SPRING_Y_3" has been assigned to 1 wire or attachment line.
#: WARNING: Keyword *CONTROLS is not supported in perturbation steps or explicit dynamic steps. The controls definitions in step STEP-2 will be ignored. 
#: The model "Billlax" has been imported from an input file. 
#: Please scroll up to check for error and warning messages.
session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF, 
    predefinedFields=OFF, connectors=OFF)
a = mdb.models['Billlax'].rootAssembly
session.viewports['Viewport: 1'].setValues(displayedObject=a)
a = mdb.models['3D-Beam'].rootAssembly
session.viewports['Viewport: 1'].setValues(displayedObject=a)
del mdb.models['3D-Beam']
a = mdb.models['Model-1'].rootAssembly
session.viewports['Viewport: 1'].setValues(displayedObject=a)
a = mdb.models['Billlax'].rootAssembly
session.viewports['Viewport: 1'].setValues(displayedObject=a)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.87566, 
    farPlane=4.07135, width=1.16762, height=0.65655, viewOffsetX=0.0204279, 
    viewOffsetY=-0.00798562)
session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-2')
session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON, 
    predefinedFields=ON, connectors=ON)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.92447, 
    farPlane=4.02254, width=0.731205, height=0.411155, viewOffsetX=-0.0771902, 
    viewOffsetY=0.0551048)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.92304, 
    farPlane=4.02397, width=0.730846, height=0.410953, viewOffsetX=0.225754, 
    viewOffsetY=0.113187)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.92304, 
    farPlane=4.02397, width=0.730845, height=0.410952, viewOffsetX=0.275976, 
    viewOffsetY=0.136745)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.92304, 
    farPlane=4.02397, width=0.730844, height=0.410951, viewOffsetX=0.271267, 
    viewOffsetY=0.124704)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.92304, 
    farPlane=4.02397, width=0.730843, height=0.41095, viewOffsetX=-0.0117584, 
    viewOffsetY=-0.0857447)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.92304, 
    farPlane=4.02397, width=0.730842, height=0.41095, viewOffsetX=-0.242468, 
    viewOffsetY=-0.209815)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.92304, 
    width=0.730841, height=0.41095, viewOffsetX=-0.34919, 
    viewOffsetY=-0.275776)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.92304, 
    width=0.73084, height=0.41095, viewOffsetX=-0.207939, 
    viewOffsetY=-0.169505)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.92304, 
    width=0.730839, height=0.41095, viewOffsetX=0.012307, 
    viewOffsetY=-0.0611398)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.92878, 
    farPlane=4.01823, width=0.66192, height=0.372196, viewOffsetX=0.0176444, 
    viewOffsetY=-0.0544816)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.93014, 
    farPlane=4.01687, width=0.662227, height=0.372369, viewOffsetX=0.0337698, 
    viewOffsetY=0.0199669)
session.viewports['Viewport: 1'].view.setValues(nearPlane=2.94348, 
    farPlane=4.00352, width=0.522028, height=0.293535, viewOffsetX=0.037636, 
    viewOffsetY=0.0119112)
session.viewports['Viewport: 1'].assemblyDisplay.geometryOptions.setValues(
    datumAxes=OFF)
session.viewports['Viewport: 1'].assemblyDisplay.geometryOptions.setValues(
    datumCoordSystems=OFF)
session.viewports['Viewport: 1'].assemblyDisplay.geometryOptions.setValues(
    referencePointLabels=OFF)
session.viewports['Viewport: 1'].assemblyDisplay.geometryOptions.setValues(
    referencePointSymbols=OFF)
session.viewports['Viewport: 1'].assemblyDisplay.geometryOptions.setValues(
    datumPlanes=OFF)
session.viewports['Viewport: 1'].assemblyDisplay.geometryOptions.setValues(
    datumPoints=OFF)
session.viewports['Viewport: 1'].assemblyDisplay.geometryOptions.setValues(
    datumPoints=ON, datumAxes=ON, datumPlanes=ON, datumCoordSystems=ON)
session.viewports['Viewport: 1'].assemblyDisplay.geometryOptions.setValues(
    referencePointLabels=ON, referencePointSymbols=ON)
