# - Find NSEngine
# Find the NSEngine includes
#
#   NSENGINE_FOUND       - True if NSEngine found.
#   NSENGINE_INCLUDE_DIR - where to find NSEngine.h, etc.
#

FIND_PATH(NSENGINE_INCLUDE_DIR NSEngine.h
  PATHS
  $ENV{TINYXMLDIR}
  NO_DEFAULT_PATH
  PATH_SUFFIXES include
)

FIND_PATH(NSENGINE_INCLUDE_DIR NSEngine.h
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/
  /usr/include/
  /usr/local/include
  /usr/include
  /sw/include/
  /sw/include
  /opt/local/include/
  /opt/csw/include/
  /opt/include/
)

SET(NSENGINE_FOUND "NO")
IF(NSENGINE_INCLUDE_DIR)
  SET(NSENGINE_FOUND "YES")
ENDIF(NSENGINE_INCLUDE_DIR)
