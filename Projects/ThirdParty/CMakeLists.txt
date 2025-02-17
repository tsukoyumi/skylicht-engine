include_directories(
	${SKYLICHT_ENGINE_SOURCE_DIR}/Projects/ThirdParty/source
	${SKYLICHT_ENGINE_SOURCE_DIR}/Projects/ThirdParty/source/zlib
	${SKYLICHT_ENGINE_SOURCE_DIR}/Projects/ThirdParty/source/curl/include
	${SKYLICHT_ENGINE_SOURCE_DIR}/Projects/ThirdParty/source/curl/src
	${SKYLICHT_ENGINE_SOURCE_DIR}/Projects/ThirdParty/source/freetype2/include
	${SKYLICHT_ENGINE_SOURCE_DIR}/Projects/ThirdParty/source/libmpg123
)

if (BUILD_OPENSSL)
include_directories(${SKYLICHT_ENGINE_SOURCE_DIR}/Projects/ThirdPartySDK/boringssl/include)
endif()

#aesGladman
file(GLOB_RECURSE aes_gladman_source 
	./source/aesGladman/**.cpp 
	./source/aesGladman/**.hpp 
	./source/aesGladman/**.c 
	./source/aesGladman/**.h)
setup_project_group("${aes_gladman_source}" ${CMAKE_CURRENT_SOURCE_DIR})

#bzip2
file(GLOB_RECURSE bzip2_source 
	./source/bzip2/**.cpp 
	./source/bzip2/**.hpp 
	./source/bzip2/**.c 
	./source/bzip2/**.h)
setup_project_group("${bzip2_source}" ${CMAKE_CURRENT_SOURCE_DIR})

#curl
if (BUILD_CURL)
file(GLOB_RECURSE curl_source 
	./source/curl/**.cpp 
	./source/curl/**.hpp 
	./source/curl/**.c 
	./source/curl/**.h)
setup_project_group("${curl_source}" ${CMAKE_CURRENT_SOURCE_DIR})
endif()

#jpeglib
file(GLOB_RECURSE jpeglib_source 
	./source/jpeglib/**.cpp 
	./source/jpeglib/**.hpp 
	./source/jpeglib/**.c 
	./source/jpeglib/**.h)
setup_project_group("${jpeglib_source}" ${CMAKE_CURRENT_SOURCE_DIR})

#libpng
file(GLOB_RECURSE libpng_source 
	./source/libpng/**.cpp 
	./source/libpng/**.hpp 
	./source/libpng/**.c 
	./source/libpng/**.h)
setup_project_group("${libpng_source}" ${CMAKE_CURRENT_SOURCE_DIR})

#json
file(GLOB_RECURSE json_source 
	./source/json/**.cpp 
	./source/json/**.hpp 
	./source/json/**.c 
	./source/json/**.h)
setup_project_group("${json_source}" ${CMAKE_CURRENT_SOURCE_DIR})

#lzma
file(GLOB_RECURSE lzma_source 
	./source/lzma/**.cpp 
	./source/lzma/**.hpp 
	./source/lzma/**.c 
	./source/lzma/**.h)
setup_project_group("${lzma_source}" ${CMAKE_CURRENT_SOURCE_DIR})

#mpc
file(GLOB_RECURSE mpc_source 
	./source/mpc/**.cpp 
	./source/mpc/**.hpp 
	./source/mpc/**.c 
	./source/mpc/**.h)
setup_project_group("${mpc_source}" ${CMAKE_CURRENT_SOURCE_DIR})

#zlib
file(GLOB_RECURSE zlib_source 
	./source/zlib/**.cpp 
	./source/zlib/**.hpp 
	./source/zlib/**.c 
	./source/zlib/**.h)
setup_project_group("${zlib_source}" ${CMAKE_CURRENT_SOURCE_DIR})

#freetype2
set(freetype_source
	./source/freetype2/src/autofit/autofit.c
	./source/freetype2/src/base/basepic.c
	./source/freetype2/src/base/ftapi.c
	./source/freetype2/src/base/ftbase.c
	./source/freetype2/src/base/ftbbox.c
	./source/freetype2/src/base/ftbitmap.c
	./source/freetype2/src/base/ftdbgmem.c
	./source/freetype2/src/base/ftdebug.c
	./source/freetype2/src/base/ftglyph.c
	./source/freetype2/src/base/ftinit.c
	./source/freetype2/src/base/ftpic.c
	./source/freetype2/src/base/ftstroke.c
	./source/freetype2/src/base/ftsynth.c
	./source/freetype2/src/base/ftsystem.c
	./source/freetype2/src/cff/cff.c
	./source/freetype2/src/pshinter/pshinter.c
	./source/freetype2/src/psaux/psaux.c
	./source/freetype2/src/psnames/psnames.c
	./source/freetype2/src/raster/raster.c
	./source/freetype2/src/sfnt/sfnt.c
	./source/freetype2/src/smooth/smooth.c
	./source/freetype2/src/truetype/truetype.c)
add_source_group("${freetype_source}" "source\\freetype2")

#libmpg123
file(GLOB_RECURSE libmpg123_source 
	./source/libmpg123/**.cpp 
	./source/libmpg123/**.hpp 
	./source/libmpg123/**.c 
	./source/libmpg123/**.h
	./source/libmpg123/**.S)
setup_project_group("${libmpg123_source}" ${CMAKE_CURRENT_SOURCE_DIR})

add_library(ThirdParty STATIC
	${aes_gladman_source} 
	${bzip2_source}
	${curl_source}
	${jpeglib_source}
	${json_source}
	${libpng_source}
	${lzma_source}
	${mpc_source}
	${zlib_source}
	${freetype_source}
	${libmpg123_source}
)

set_target_properties(ThirdParty PROPERTIES VERSION ${SKYLICHT_VERSION})