# Define the files we need to compile.
# Anything not in this list will not be compiled into mlpack.
set(SOURCES
    kcentre_helper.hpp
    sample_initialization.hpp
    gonzalez_kcentre.hpp
    gonzalez_kcentre_impl.hpp
    gonzalez_kcentre_rules.hpp
    gonzalez_kcentre_rules_impl.hpp
    gonzalez_kcentre_statistic.hpp
    kcentre.hpp
    kcentre_impl.hpp
)

# Add directory name to sources.
set(DIR_SRCS)
foreach(file ${SOURCES})
  set(DIR_SRCS ${DIR_SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/${file})
endforeach()
# Append sources (with directory name) to list of all mlpack sources (used at
# the parent scope).
set(MLPACK_SRCS ${MLPACK_SRCS} ${DIR_SRCS} PARENT_SCOPE)

add_cli_executable(kcentre)
