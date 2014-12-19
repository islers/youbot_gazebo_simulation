cmake_minimum_required(VERSION 2.8.3)
project(yb_description)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)


catkin_package(
  CATKIN_DEPENDS
)

install(DIRECTORY controller meshes urdf
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})


