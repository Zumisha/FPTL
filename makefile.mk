PROJECT_DIR:=/home/ubuntu/Developer/pshamal-fptl

BOOST_DIR:=/home/ubuntu/Developer/boost_1_54_0


OBJDIR := build-linux

TARGET=fptl

CC=g++

#restrict stack size to 14 Mbytes with -Wl, --stack, size
CXX=-Wl,--stack,14680064 -std=c++11 #-Wc++11-extensions  -stdlib=libc++

# формируем множество исходников
SOURCES_TEMP=\
Runtime/Main.cpp\
Runtime/Run.cpp\
Runtime/ConstructorGenerator.cpp\
Runtime/FSchemeGenerator.cpp\
Runtime/StandartLibrary.cpp\
Runtime/Types.cpp\
Runtime/Data.cpp\
Runtime/DataTypes/String.cpp\
Runtime/FScheme.cpp\
Runtime/Functions.cpp\
Parser/Tokenizer.cpp\
Parser/AST.cpp\
Parser/Nodes.cpp\
Parser/NodeVisitor.cpp\
Parser/Semantic.cpp\
Parser/Support.cpp\
Parser/Generated/Flex/FlexScanner.cpp


# формируем на основе множества исходников - множество объектников
# и помещаем их в папку OBJDIR
OBJECTS_TEMP=$(SOURCES_TEMP:%.cpp=$(OBJDIR)/%.o)

# добавляем к иходникам Parser.tab.cc 
SOURCES =$(SOURCES_TEMP) Parser/Generated/Parser.tab.cc

# добавляем к иходникам Parser.tab.o 
OBJECTS =$(OBJECTS_TEMP) $(OBJDIR)/Parser/Generated/Parser.tab.o

# выводим список объектников на консоль
$(info ______________)
$(info   OBJECTS= $(OBJECTS) )	
$(info ______________)
$(info   SOURCES= $(SOURCES) )	
$(info )


LIBS_DIR =-L$(BOOST_DIR)/stage/lib 


LIDS = -lboost_regex -lboost_thread -lboost_system -pthread -lrt -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -ltcmalloc

HEADER_PATH =\
-I$(PROJECT_DIR)/Parser/Generated/Flex \
-I$(PROJECT_DIR)/Parser/Generated \
-I$(BOOST_DIR) 


CFLAGS=-c -Wall -v

all: $(OBJDIR)/$(TARGET)
	$(info ___ finish all)	
    
$(OBJDIR)/$(TARGET): $(OBJECTS) 
	$(info )
	$(info ________________ start linking: $(OBJDIR)/$(TARGET))	
	$(CC) $(HEADER_PATH) $(OBJECTS)  $(LIDS) $(LIBS_DIR) -o $@ -v
	
	

# $(OBJECTS): 
$(OBJDIR)/Parser/Generated/Parser.tab.o: Parser/Generated/Parser.tab.cc
	-mkdir -p $(dir $(dir $(dir $@)))
	-mkdir -p $(dir $(dir $@))
	-mkdir -p $(dir $@)
	$(CC) $(CXX) $(CFLAGS) $(HEDER_PATH) $< -o $@

$(OBJDIR)/%.o: %.cpp
	-mkdir -p $(dir $(dir $(dir $@)))
	-mkdir -p $(dir $(dir $@))
	-mkdir -p $(dir $@)
	$(CC) $(CXX) $(CFLAGS) $(HEADER_PATH) $< -o $@

