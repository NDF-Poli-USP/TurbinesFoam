turbinesFoam
============

![OpenFOAM v2106](https://img.shields.io/badge/OpenFOAM-v2106-brightgreen.svg)
![OpenFOAM 8](https://img.shields.io/badge/OpenFOAM-8-brightgreen.svg)
![OpenFOAM 7](https://img.shields.io/badge/OpenFOAM-7-brightgreen.svg)

[turbinesFoam](https://github.com/turbinesFoam/turbinesFoam) is a library for simulating wind and marine hydrokinetic turbines
in OpenFOAM using the actuator line method. The NDF's version changes the points considered in the turbine blade discretization.


Contributing
------------

Pull requests are very welcome!
See the [issue tracker](https://github.com/NDF-Poli-USP/TurbinesFoam/issues)
for more details.


Features
--------

`fvOptions` classes for adding actuator lines and turbines constructed from
actuator lines to any compatible solver or turbulence model, e.g.,
`simpleFoam`, `pimpleFoam`, `interFoam`, etc.


Installation
------------


On a personal computer: 

```bash
cd $WM_PROJECT_USER_DIR
git clone https://github.com/NDF-Poli-USP/TurbinesFoam.git
cd turbinesFoam
./Allwmake
```

On the NDF machines:

```bash
cd $WM_PROJECT_USER_DIR
git clone https://github.com/NDF-Poli-USP/TurbinesFoam.git
cd turbinesFoam
```

change the file "Allwmake" to include: 

```bash
#!/usr/bin/env bash

source path_to_openfoam/etc/bashrc

# Parse arguments for library compilation without documentation by default
. $WM_PROJECT_DIR/wmake/scripts/AllwmakeParseArguments

wmake libso path_to_where_you_downloaded_the_turbinesfoam/turbinesFoam/src
```

An example of this file can be seen in the Allwmake_NDF .

After that, run:

```bash
./Allwmake
```

You also need to include the following in your .bashrc (located at /home/user directory) after the '# User specific aliases and functions' commentary :

```bash
source path_to_openfoam/etc/bashrc
```

On intel05 workstation, for example, it should be: 

```bash
source /opt/spack/opt/spack/linux-centos8-sandybridge/gcc-8.5.0/openfoam-2106-uwp244xqtbuttkntvxfohr5uanbkkono/etc/bashrc
```

Reread the '~/.bashrc' configuration using the source command:

```bash
source ~/.bashrc
```


Usage
-----

There are tutorials located in `turbinesFoam/tutorials`.


On the NDF machines:

You need to load the following modules before to use the OpenFOAM + turbinesFoam library:


```bash
module load openfoam-version
module load openmpi-version
module load paraview-version
```
To view the program's version available on each workstation:

```bash
module avail 
```

How to cite
-----------

The latest release of turbinesFoam can be cited via DOI thanks to Zenodo: [![DOI](https://zenodo.org/badge/4234/turbinesFoam/turbinesFoam.svg)](https://zenodo.org/badge/latestdoi/4234/turbinesFoam/turbinesFoam)


Acknowledgements
----------------

The original TurbinesFoam project was funded through a National Science Foundation CAREER award,
principal investigator Martin Wosnik ([NSF CBET
1150797](http://www.nsf.gov/awardsearch/showAward?AWD_ID=1150797), Energy for
Sustainability, original program manager Geoffrey A. Prentice, current program
manager Gregory L. Rorrer).

OpenFOAM is free, open source software for computational fluid dynamics (CFD),
developed primarily by [CFD Direct](http://cfd.direct), on behalf of the
[OpenFOAM](http://openfoam.org) Foundation.

Interpolation, Gaussian projection, and vector rotation functions adapted from
NREL's [SOWFA](https://github.com/NREL/SOWFA).
