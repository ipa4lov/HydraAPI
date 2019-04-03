#pragma once

#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <cstdint>


struct HydraGeomData
{
  HydraGeomData();
  ~HydraGeomData();

  //
  //
  void write(const std::string& a_fileName);
  void write(std::ostream& a_out);
  size_t writeCompressed(std::ostream& a_out);

  void read(const std::wstring& a_fileName);
  void read(const std::string& a_fileName);
  void read(std::istream& a_input);
  void readCompressed(std::istream& a_input, size_t a_compressedSize);

  void writeToMemory(char* a);
  size_t sizeInBytes();

  // common vertex attributes
  //
  uint32_t getVerticesNumber() const;
  const float* getVertexPositionsFloat4Array() const; 
  const float* getVertexNormalsFloat4Array()  const; 
  const float* getVertexTangentsFloat4Array()  const; 
  const float* getVertexTexcoordFloat2Array()  const; 

  // advanced attributes, for various types of lightmaps
  //
  const float* getVertexLightmapTexcoordFloat2Array()  const; 
  const float* getVertexSphericalHarmonicCoeffs()  const; 

  // per triangle data
  //
  uint32_t getIndicesNumber() const;                       // return 3*num_triangles
  const uint32_t* getTriangleVertexIndicesArray() const;   // 3*num_triangles
  const uint32_t* getTriangleMaterialIndicesArray() const; // 1*num_triangles 

  //
  //
  void setData(uint32_t a_vertNum, const float* a_pos, const float* a_norm, const float* a_tangent, const float* a_texCoord,
               uint32_t a_indicesNum, const uint32_t* a_triVertIndices, const uint32_t* a_triMatIndices);


  struct Header
  {
    uint64_t fileSizeInBytes;
    uint32_t verticesNum;
    uint32_t indicesNum;
    uint32_t materialsNum;
    uint32_t flags;
  };
  
  struct HeaderC // this header i used only fpr '.vsgfc', compressed format.
  {
    uint64_t compressedSizeInBytes;
    float    boxMin[3];
    float    boxMax[3];
    uint32_t batchListArraySize;
    uint32_t dummy;
  };

protected:

  enum GEOM_FLAGS{ HAS_TANGENT = 1, 
                   HAS_LIGHTMAP_TEXCOORDS = 2, 
                   HAS_HARMONIC_COEFFS = 4,
                   HAS_NO_NORMALS = 8};

  // size info
  //
  uint64_t fileSizeInBytes;
  uint32_t verticesNum;
  uint32_t indicesNum;
  uint32_t materialsNum;
  uint32_t flags;


  //
  //
  const float* m_positions;
  const float* m_normals;
  const float* m_tangents; 
  const float* m_texcoords;

  const uint32_t* m_triVertIndices;
  const uint32_t* m_triMaterialIndices;

  char*     m_materialNames;
  uint32_t  m_matNamesTotalStringSize;
  
  char*   m_data; // this is a full dump of the file

  //
  //
  void freeMemIfNeeded();
  bool m_ownMemory;
  
  // HashMapI                      m_matIndexByName;
  // std::vector<std::string>      m_matNameByIndex;

};


struct VSGFOffsets
{
  uint64_t offsetPos ;
  uint64_t offsetNorm;
  uint64_t offsetTang;
  uint64_t offsetTexc;
  uint64_t offsetInd ;
  uint64_t offsetMind;
};

VSGFOffsets CalcOffsets(int numVert, int numInd);


size_t HR_SaveVSGFCompressed(const void* vsgfData, size_t a_vsgfSize, const wchar_t* a_outfileName);

