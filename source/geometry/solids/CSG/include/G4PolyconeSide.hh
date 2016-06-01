//
// G4PolyconeSide
//
// Declaration of a face that represents one conical side of a polycone
//
#ifndef G4PolyconeSide_hh
#define G4PolyconeSide_hh

#include "G4VCSGface.hh"

class G4IntersectingCone;

typedef struct {
        G4double r, z;  // start of vector
} G4PolyconeSideRZ;
 
class G4PolyconeSide : public G4VCSGface {
	public:
	G4PolyconeSide( const G4PolyconeSideRZ *prevRZ,
                        const G4PolyconeSideRZ *tail,
                        const G4PolyconeSideRZ *head,
                        const G4PolyconeSideRZ *nextRZ,
			const G4double phiStart, const G4double deltaPhi, 
			const G4bool phiIsOpen );
	virtual ~G4PolyconeSide();
	
	G4bool Intersect( const G4ThreeVector &p, const G4ThreeVector &v,	
			  const G4bool outgoing, const G4double surfTolerance,
			  G4double &distance, G4double &distFromSurface,
			  G4ThreeVector &normal, G4bool &allBehind );

        G4double Distance( const G4ThreeVector &p, const G4bool outgoing );
	
	EInside Inside( const G4ThreeVector &p, const G4double tolerance, 
			G4double *bestDistance );
	
	G4ThreeVector Normal( const G4ThreeVector &p,  G4double *bestDistance );

	G4double Extent( const G4ThreeVector axis );

	void CalculateExtent( const EAxis axis, 
			      const G4VoxelLimits &voxelLimit,
			      const G4AffineTransform &tranform,
			      G4double &min, G4double &max        );
	
	protected:
	G4double r[2], z[2];	// r, z parameters, in specified order
	G4double startPhi,	// Start phi (0 to 2pi), if phiIsOpen
		 deltaPhi;	// Delta phi (0 to 2pi), if phiIsOpen
	G4bool	 phiIsOpen;	// True if there is a phi slice
	
	G4IntersectingCone *cone;	// Our intersecting utility class
	
	G4double rNorm, zNorm;	// Normal to surface in r,z space
	G4double rS, zS;	// Unit vector along surface in r,z space
	G4double length;	// Length of face in r,z space
	
	G4double rNormEdge[2],
		 zNormEdge[2];	// Normal to edges
				
	G4double DistanceAway( const G4ThreeVector &p, const G4bool opposite,
			       G4double &distOutside2, G4double *rzNorm );
			
	G4bool PointOnCone( const G4ThreeVector &p, G4ThreeVector &normal );
};


#endif