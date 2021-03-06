/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*---------------------------------------------------------------------------*/

#include "WLF.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
 namespace thermoFunctions 
 {
   defineTypeNameAndDebug(WLF, 0);
   addToRunTimeSelectionTable(thermoFunction, WLF, dictionary);
 }
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::thermoFunctions::WLF::WLF
(
  const word& name,
  const fvMesh& mesh,
  const dictionary& dict
)
:
  thermoFunction(name, mesh),
  c1_(dict.lookup("c1")),
  c2_(dict.lookup("c2")),
  T0_(dict.lookup("T0"))
{
   // Handle T
   T_ = &mesh.lookupObject<volScalarField>("T");
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
void Foam::thermoFunctions::WLF::multiply
(
  volScalarField& vf,
  const dimensionedScalar& ds
) const
{
  vf = ds*Foam::pow(10, -c1_ * (T() -T0_) / ( c2_ + (T() -T0_)) );  
}

void Foam::thermoFunctions::WLF::multiply
(
  volScalarField& vf
) const
{
  vf *= Foam::pow(10, -c1_ * (T() -T0_) / ( c2_ + (T() -T0_)) );  
}

Foam::tmp<Foam::volScalarField> Foam::thermoFunctions::WLF::createField
(
  const dimensionedScalar& ds
) const
{
  tmp<volScalarField> tvf
  (
   new volScalarField 
   (
     IOobject
     (
       "tmpField",
       mesh().time().timeName(),
       mesh(),
       IOobject::NO_READ,
       IOobject::NO_WRITE,
       false
     ),
     mesh(),
     ds,
     extrapolatedCalculatedFvPatchField<scalar>::typeName
   )
  );
  
  volScalarField& vf = tvf.ref(); 
  
  multiply(vf);
  
  return tvf; 
}

// ************************************************************************* //
