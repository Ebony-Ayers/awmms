set(project_source_files
  awmms.hpp
  awmms.cpp
  chunkAllocator.hpp
  chunkAllocator.inl
  log2.hpp
  log2.inl
  accessParameterPack.hpp
  cumulativeSumParameterPack.hpp
  standardAllocatorInterface.hpp
)

add_library(${primary_target_name} ${project_source_files})