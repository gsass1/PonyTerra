# - Find TinyXML
# Find the native TinyXML includes and library
#
#   TINYXML_FOUND       - True if TinyXML found.
#   TINYXML_INCLUDE_DIR - where to find tinyxml.h, etc.
#   TINYXML_LIBRARIES   - List of libraries when using TinyXML.
#

FIND_PATH(TINYXML_INCLUDE_DIR tinyxml.h
  PATHS
  $ENV{TINYXMLDIR}
  NO_DEFAULT_PATH
  PATH_SUFFIXES include
)

FIND_PATH(TINYXML_INCLUDE_DIR tinyxml.h
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

FIND_LIBRARY(TINYXML_LIBRARIES 
  NAMES tinyxml
  PATHS
  $ENV{TINYXMLDIR}
  NO_DEFAULT_PATH
    PATH_SUFFIXES lib64 lib
)

FIND_LIBRARY(TINYXML_LIBRARIES 
  NAMES tinyxml
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
  C:/Libraries
    PATH_SUFFIXES lib64 lib
)

SET(TINYXML_FOUND "NO")
IF(TINYXML_LIBRARIES AND TINYXML_INCLUDE_DIR)
  SET(TINYXML_FOUND "YES")
ENDIF(TINYXML_LIBRARIES AND TINYXML_INCLUDE_DIR)
