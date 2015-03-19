CPP        = latex 
CXX        = latex 
LINK       = dvips 
LD         = dvips 
# 
CCFLAGS  = 
DEBUG    = 
PREPRO   = 
LFLAGS   =
INCPATH  = 
LIBS     = 
GLIBS    = 
#
AR       = ar cqs
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p
####### Output directory
OBJECTS_DIR = ./
####### Files
HEADERS =
SOURCES1= notice.tex output/mclist*.tex 
OBJECTS1= notice.dvi 
SOURCES2= 
OBJECTS2= 
SOURCES3= 
OBJECTS3= 
SOURCES4= 
OBJECTS4= 
FORMS = 
DESTDIR  = 
TARGET1  = notice.ps 

####### Implicit rules
# compiling c++ code, for root
%.dvi: %.tex
	@echo  $^
	$(CPP) $< 
	$(CPP) $< 
first: all
####### Build rules
all: Makefile $(TARGET1)
$(TARGET1):   $(OBJECTS1) 
	$(LINK) -o $(TARGET1) $(OBJECTS1) 
dist: 
	@mkdir -p .tmp/fitgo && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) Makefile .tmp/fitgo/ && ( cd `dirname .tmp/fitgo` && $(TAR1) fitgo.tar fitgo && $(GZIP) fitgo.tar ) && $(MOVE) `dirname .tmp/fitgo`/fitgo.tar.gz . && $(DEL_FILE) -r .tmp/fitgo

clean:
	-$(DEL_FILE) $(OBJECTS1) 
	-$(DEL_FILE) *.toc *core* *.log *.aux *~ output/*.aux
####### Sub-libraries
distclean: clean
	-$(DEL_FILE) $(TARGET1) $(TARGET2) 
FORCE:
####### Compile
notice.dvi          : notice.tex output/mclist*.tex
####### Install
install:  
uninstall:  
