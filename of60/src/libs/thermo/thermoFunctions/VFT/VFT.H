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

Class
    VFT

Description
    Implements Vogel–Fulcher–Tammann (VFT) function.
    This file is part of rheoTool.
     

\*---------------------------------------------------------------------------*/

#ifndef VFT_H
#define VFT_H

#include "thermoFunction.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace thermoFunctions
{ 

/*---------------------------------------------------------------------------*\
                           Class VFT Declaration
\*---------------------------------------------------------------------------*/

class VFT
:
    public thermoFunction
{
    // Private data

         // Model VFTs

           //- Scaling factor
           dimensionedScalar A_;
           
           //- Additive constant
           dimensionedScalar B_;

           //- Reference temperature 
           dimensionedScalar T0_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        VFT(const VFT&);

        //- Disallow default bitwise assignment
        void operator=(const VFT&);

protected:
   
    
      
public:

    //- Runtime type information
    TypeName("VFT");

    // Constructors

        //- Construct from components
        VFT
        (
            const word& name,
            const fvMesh& mesh,
            const dictionary& dict
        );


    // Destructor

        virtual ~VFT()
        {}

    // Member Functions

        //- Given the field for a physical parameter, make it equal to the 
        // dimensionedScalar multiplied by the scaling function
        virtual void multiply
        (
          volScalarField&,
          const dimensionedScalar&
        ) const;
        
        //- Multiply the given field by the scaling function
        virtual void multiply
        (
          volScalarField&
        ) const;
        
        //- Create a field with its internal and boundary fields set equal to the 
        // dimensionedScalar passed and multiply it by the scaling function
        virtual tmp<volScalarField> createField
        (
          const dimensionedScalar&
        ) const;
        
        //- Compare two thermoFunctions for equality 
        virtual bool isItEqualTo
        (
          const thermoFunction& tf
        ) const
        {
           bool fl(false);
           
           if ( isType<VFT>(tf) )
           {
             const VFT& ar = refCast<const VFT>(tf);
             fl = (this->A_.value() == ar.A_.value() && this->B_.value() == ar.B_.value() && this->T0_.value() == ar.T0_.value());     
           } 
                       
           return fl;     
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace thermoFunctions 
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
