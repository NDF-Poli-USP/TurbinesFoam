 
 #ifndef CustomProbes_H
 #define CustomProbes_H
 
#include "stateFunctionObject.H"
 #include "HashPtrTable.H"
 #include "OFstream.H"
 #include "polyMesh.H"
 #include "pointField.H"
 #include "volFieldsFwd.H"
 #include "surfaceFieldsFwd.H"
 #include "surfaceMesh.H"
 #include "wordRes.H"
  
 using namespace Foam::functionObjects;
  
 // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
  
 namespace Foam
 {
  
 // Forward declaration of classes
 class Time;
 class objectRegistry;
 class dictionary;
 class fvMesh;
 class mapPolyMesh;
  
 /*---------------------------------------------------------------------------*\
                           Class probes Declaration
 \*---------------------------------------------------------------------------*/
  
 class CustomProbes
 :
     public stateFunctionObject,
     public pointField
 {
 protected:
  
     // Protected classes
  
         //- Class used for grouping field types
         template<class Type>
         class fieldGroup
         :
             public DynamicList<word>
         {
         public:
             //- Construct null
             fieldGroup()
             :
                 DynamicList<word>(0)
             {}
         };
  
  
     // Protected data
  
         //- Const reference to fvMesh
         const fvMesh& mesh_;
  
         //- Load fields from files (not from objectRegistry)
         bool loadFromFiles_;
  
  
       // Read from dictionary
  
         //- Names of fields to probe
         wordRes fieldSelection_;
  
         //- Fixed locations, default = yes
         //  Note: set to false for moving mesh calculations where locations
         //        should move with the mesh
         bool fixedLocations_;
  
         //- Interpolation scheme name
         //  Note: only possible when fixedLocations_ is true
         word interpolationScheme_;
  
         //- Include probes that were not found
         bool includeOutOfBounds_;
  
  
       // Calculated
  
         //- Categorized scalar/vector/tensor vol fields
         fieldGroup<scalar> scalarFields_;
         fieldGroup<vector> vectorFields_;
         fieldGroup<sphericalTensor> sphericalTensorFields_;
         fieldGroup<symmTensor> symmTensorFields_;
         fieldGroup<tensor> tensorFields_;
  
         //- Categorized scalar/vector/tensor surf fields
         fieldGroup<scalar> surfaceScalarFields_;
         fieldGroup<vector> surfaceVectorFields_;
         fieldGroup<sphericalTensor> surfaceSphericalTensorFields_;
         fieldGroup<symmTensor> surfaceSymmTensorFields_;
         fieldGroup<tensor> surfaceTensorFields_;
  
         //- Cells to be probed (obtained from the locations)
         labelList elementList_;
  
         //- Faces to be probed
         labelList faceList_;
  
         //- Processor holding the cell or face (-1 if point not found
         //  on any processor)
         labelList processor_;
  
         //- Current open files
         HashPtrTable<OFstream> CustomProbesFilePtrs_; //alterado!
  
         // Additional fields for patchProbes
  
             //- Patch IDs on which the new probes are located
             labelList patchIDList_;
  
             //- Original probes location (only used for patchProbes)
             pointField oldPoints_;
  
  
     // Protected Member Functions
  
         //- Clear old field groups
         void clearFieldGroups();
  
         //- Classify field types, returns the number of fields
         label classifyFields();
  
         //- Find cells and faces containing probes
         virtual void findElements(const fvMesh& mesh);
  
         //- Classify field type and open/close file streams,
         //  returns number of fields to sample
         label prepare();
  
  
 private:
  
         //- Sample and write a particular volume field
         template<class Type>
         void sampleAndWrite
         (
             const GeometricField<Type, fvPatchField, volMesh>&
         );
  
  
         //- Sample and write a particular surface field
         template<class Type>
         void sampleAndWrite
         (
             const GeometricField<Type, fvsPatchField, surfaceMesh>&
         );
  
         //- Sample and write all the fields of the given type
         template<class Type>
         void sampleAndWrite(const fieldGroup<Type>&);
  
         //- Sample and write all the surface fields of the given type
         template<class Type>
         void sampleAndWriteSurfaceFields(const fieldGroup<Type>&);
  
         //- No copy construct
         CustomProbes(const CustomProbes&) = delete;
  
         //- No copy assignment
         void operator=(const CustomProbes&) = delete;
  
  
 public:
  
     //- Runtime type information
     TypeName("CustomProbes");
  
  
     // Constructors
  
         //- Construct from Time and dictionary
         CustomProbes
         (
             const word& name,
             const Time& runTime,
             const dictionary& dict,
             const bool loadFromFiles = false,
             const bool readFields = true
         );
  
  
     //- Destructor
     virtual ~CustomProbes() = default;
  
  
     // Member Functions
  
         //- Return names of fields to probe
         virtual const wordRes& fieldNames() const
         {
             return fieldSelection_;
         }
  
         //- Return locations to probe
         virtual const pointField& CustomProbesLocations() const
         {
             return *this;
         }
  
         //- Return location for probe i
         virtual const point& customprobes(const label i) const
         {
             return operator[](i);
         }
  
         //- Cells to be probed (obtained from the locations)
         const labelList& elements() const
         {
             return elementList_;
         }
  
         //- Read the probes
         virtual bool read(const dictionary&);
  
         //- Execute, currently does nothing
         virtual bool execute();
  
         //- Sample and write
         virtual bool write();
  
         //- Update for changes of mesh
         virtual void updateMesh(const mapPolyMesh&);
  
         //- Update for changes of mesh
         virtual void movePoints(const polyMesh&);
  
         //- Update for changes of mesh due to readUpdate
         virtual void readUpdate(const polyMesh::readUpdateState state)
         {}
  
         //- Sample a volume field at all locations
         template<class Type>
         tmp<Field<Type>> sample
         (
             const GeometricField<Type, fvPatchField, volMesh>&
         ) const;
  
         //- Sample a single vol field on all sample locations
         template<class Type>
         tmp<Field<Type>> sample(const word& fieldName) const;
  
         //- Sample a single scalar field on all sample locations
         template<class Type>
         tmp<Field<Type>> sampleSurfaceFields(const word& fieldName) const;
  
         //- Sample a surface field at all locations
         template<class Type>
         tmp<Field<Type>> sample
         (
             const GeometricField<Type, fvsPatchField, surfaceMesh>&
         ) const;
 };
  
  
 // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
  
 } // End namespace Foam
  
 // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
  
  #ifdef NoRepository
     #include "CustomProbesTemplates.C"
 #endif
  
 // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
  
 #endif
  
 // ************************************************************************* //
 
 
 
 
 
