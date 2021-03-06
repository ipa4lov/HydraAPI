cmake_minimum_required(VERSION 3.7)
project(hydra_api C CXX)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        alloc16.h
        cube2sphere.cpp
        HydraLegacyUtils.cpp
        HydraLegacyUtils.h
        HR_HDRImage.h
        HR_HDRImage4f.cpp
        HR_HDRImageTool.h
        HR_HDRImageTool.cpp
        HRMeshCommon.cpp
        HRTextureCommon.cpp
        HydraAPI.cpp
        HydraAPI.h
        HydraAPI_Camera.cpp
        HydraAPI_FrameBuffer.cpp
        HydraAPI_Geom.cpp
        HydraAPI_GBuffer.cpp
        HydraAPI_Light.cpp
        HydraAPI_LoadExistingLibrary.cpp
        HydraAPI_Material.cpp
        HydraAPI_Texture.cpp
        HydraAPI_TextureProcLex.cpp
        HydraDriverUpdate.cpp
        HydraInternal.h
        HydraObjectManager.cpp
        HydraObjectManager.h
        HydraRenderDriverAPI.h
        HydraVSGFExport.cpp
        HydraVSGFExport.h
        HydraVSGFCompress.h
        HydraVSGFCompress.cpp
        HydraXMLHelpers.h
        HydraXMLVerify.cpp
        HydraXMLVerify.h
        LiteMath.h
        pugiconfig.hpp
        pugixml.cpp
        pugixml.hpp
        RenderDriverDebugPrint.cpp
        RenderDriverOpenGL1.cpp
        RenderDriverOpenGL1.h
        RenderDriverOpenGL1_DelayedLoad.cpp
        RenderDriverOpenGL1_DrawBvhLevels.cpp
        RenderDriverOpenGL1_TestSplit.cpp
        RenderDriverOpenGL1Debug.cpp
        RenderDriverOpenGL1DebugDrawRays.cpp
        RenderDriverOpenGL1_TestCustomAttributes.cpp
        RenderDriverOpenGL3_Utility.h
        RenderDriverOpenGL3_Utility.cpp
        RenderDriverHydraConnection.cpp
        ssemath.cpp
        ssemath.h
        VirtualBuffer.cpp
        xxhash.c
        xxhash.h
        HydraXMLHelpers.cpp
        HydraTextureUtils.cpp
        HydraTextureUtils.h
        HydraAPI_GeomProcessing.cpp
        vfloat4_x64.h)


if (WIN32)
    set(SOURCE_FILES ${SOURCE_FILES} SystemWin.cpp HR_AccumImageWin.cpp)
    set(SOURCE_FILES ${SOURCE_FILES} HydraLaunchProcessWin32.cpp)
else()
	set(SOURCE_FILES ${SOURCE_FILES} SystemUnix.cpp
                                     HR_AccumImageLinux.cpp
                                     HydraLaunchProcessLinux.cpp)
endif()


set(HR_EXTENSIONS HRExtensions.cpp)

set(MODERN_GL_RENDER_DRIVER
        glad.c
        RenderDriverOpenGL32Forward.h RenderDriverOpenGL32Forward.cpp
        OpenGLCoreProfileUtils.h OpenGLCoreProfileUtils.cpp
        RenderDriverOpenGL32Deferred.h RenderDriverOpenGL32Deferred.cpp )

set(POST_PROC
        HydraPostProcessAPI.h
        HydraPostProcessAPI.cpp
        HydraPostProcessCommon.h
        HydraPostProcessCommon.cpp
        HydraPostProcessSpecial.h
        HydraPostProcessSpecial.cpp
        NonLocalMeans.cpp
        HydraVSGFCompress.h HydraVSGFCompress.cpp)



list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
find_package(FreeImage REQUIRED)
include_directories(${FREEIMAGE_INCLUDE_DIRS})
set(LIBS ${LIBS} ${FREEIMAGE_LIBRARIES})

find_package(OpenGL REQUIRED)
find_package (Threads REQUIRED)

include_directories(${ADDITIONAL_INCLUDE_DIRS})

if(WIN32)
else()
    find_package (Threads REQUIRED)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()


#build hydra API static library
add_library(hydra_api STATIC ${SOURCE_FILES} ${POST_PROC} ${MODERN_GL_RENDER_DRIVER} ${HR_EXTENSIONS})
target_include_directories (hydra_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${OPENGL_INCLUDE_DIR})


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DIN_DEBUG")

if(WIN32)
  add_definitions(-DUNICODE -D_UNICODE)
  target_link_libraries(hydra_api LINK_PUBLIC ${LIBS} ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY} corto ies_parser mikttspace)
else()
  set_property(TARGET hydra_api PROPERTY POSITION_INDEPENDENT_CODE ON)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1 -fopenmp")

  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang") # enable sanitize youself if needed
      #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory -fno-omit-frame-pointer -fsanitize=leak)
      #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined")
      MESSAGE( STATUS "WE USE CLANG(HydraAPI);")
  else()                                     # enable sanitize youself if needed
      #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds-strict")
      MESSAGE( STATUS "WE USE GCC  (HydraAPI);")
  endif()

  MESSAGE( STATUS "CMAKE_CXX_FLAGS(HydraAPI): " ${CMAKE_CXX_FLAGS} )
  target_link_libraries(hydra_api LINK_PUBLIC Threads::Threads ${LIBS} ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY}
                        ies_parser mikktspace corto
                        stdc++fs rt dl OpenCL)
endif()