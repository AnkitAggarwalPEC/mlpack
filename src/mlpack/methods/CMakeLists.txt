# This macro adds a command-line executable with the given name.  It assumes
# that the file with main() is in <name>_main.cpp, and produces an output
# program with the name mlpack_<name>.
macro (add_cli_executable name)
if (BUILD_CLI_EXECUTABLES)
  add_executable(mlpack_${name}
    ${name}_main.cpp
  )
  target_link_libraries(mlpack_${name}
    mlpack
    ${COMPILER_SUPPORT_LIBRARIES}
  )
  # Make sure that we set BINDING_TYPE to cli so the command-line program is
  # compiled with the correct int main() call.
  set_target_properties(mlpack_${name} PROPERTIES COMPILE_FLAGS
      -DBINDING_TYPE=BINDING_TYPE_CLI)
  install(TARGETS mlpack_${name} RUNTIME DESTINATION bin)
endif ()
endmacro ()

# Recurse into each method mlpack provides.
set(DIRS
  preprocess
  adaboost
  approx_kfn
  amf
  ann
  block_krylov_svd
  cf
  dbscan
  decision_stump
  decision_tree
  det
  emst
  fastmks
  gmm
  hmm
  hoeffding_trees
  kernel_pca
  kmeans
  mean_shift
  lars
  linear_regression
  local_coordinate_coding
  logistic_regression
  lsh
#  mvu
  matrix_completion
  naive_bayes
  nca
  neighbor_search
  nmf
#  lmf
  pca
  perceptron
  quic_svd
  radical
  randomized_svd
  random_forest
  range_search
  rann
#  rmva
  regularized_svd
  softmax_regression
  sparse_autoencoder
  sparse_coding
  nystroem_method
  kcentre
)

foreach(dir ${DIRS})
    add_subdirectory(${dir})
endforeach()

set(MLPACK_SRCS ${MLPACK_SRCS} ${DIR_SRCS} PARENT_SCOPE)
set(MLPACK_PYXS ${MLPACK_PYXS} PARENT_SCOPE)
