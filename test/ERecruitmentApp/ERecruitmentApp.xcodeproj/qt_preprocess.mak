#############################################################################
# Makefile for building: ERecruitmentApp.app/Contents/MacOS/ERecruitmentApp
# Generated by qmake (2.01a) (Qt 4.8.4) on: Thu Feb 7 11:10:13 2013
# Project:  ERecruitmentApp.pro
# Template: app
# Command: /usr/bin/qmake -o ERecruitmentApp.xcodeproj/project.pbxproj ERecruitmentApp.pro
#############################################################################

MOC       = /Developer/Tools/Qt/moc
UIC       = /Developer/Tools/Qt/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_WEBKIT_LIB -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/local/Qt4.8/mkspecs/macx-xcode -I. -I/usr/include/QtUiTools -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtNetwork.framework/Versions/4/Headers -I/usr/include/QtNetwork -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/Library/Frameworks/QtXml.framework/Versions/4/Headers -I/usr/include/QtXml -I/Library/Frameworks/QtWebKit.framework/Versions/4/Headers -I/usr/include/QtWebKit -I/usr/include -I. -Isrc -I../../../projects/development/github/Evimed-connect-cpp/src -I/usr/lib -I. -I/usr/local/include -I/System/Library/Frameworks/CarbonCore.framework/Headers -F/Library/Frameworks
DEL_FILE  = rm -f
MOVE      = mv -f

IMAGES = 
PARSERS =
preprocess: $(PARSERS) compilers
clean preprocess_clean: parser_clean compiler_clean

parser_clean:
check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compilers: ./moc_ERecruitmentView.cpp
compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_ERecruitmentView.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_ERecruitmentView.cpp
moc_ERecruitmentView.cpp: src/ERecruitmentView.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/ERecruitmentView.h -o moc_ERecruitmentView.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

