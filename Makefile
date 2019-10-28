###
#
.PHONY: all lib print test data_classes build_dir

# Directories
test_dir = ./test
build_dir = ./build

test_app = test_app

# Options for opencv
CFLAGS=`pkg-config --cflags opencv`
LIBS=`pkg-config --libs opencv`

cab_lib_files = $(wildcard cab.cpp)
cab_obj = $(patsubst %, $(build_dir)/%, $(cab_lib_files:.cpp=.o))

data_class_files = $(wildcard datastorage.cpp)
data_class_obj = $(patsubst %, $(build_dir)/%, $(data_class_files:.cpp=.o))

test_files = $(wildcard ./test/*.cpp)

inc_dir = ./

all: lib 

test: $(test_app)

lib: $(cab_obj) $(data_class_obj) $(build_dir)
	@echo "Library compiled!"

data_classes: $(data_class_obj) $(build_dir)
	@echo "Data Structures compiled!"

${test_app}: $(test_files) $(cab_obj) $(data_class_obj)
	g++ $^ -I ${inc_dir} -g -o $@ `pkg-config --libs --cflags opencv` 

$(cab_obj): $(cab_lib_files)
	printf "Compiling library...\n"
	g++ -c $^ -g `pkg-config --libs --cflags opencv` -o $@

$(data_class_obj): $(data_class_files)
	printf "Compiling data structures...\n"
	g++ -c $^ -g `pkg-config --libs --cflags opencv` -o $@


$(build_dir):
	@mkdir -p $@

print:
	@echo "CAB source files: $(cab_lib_files)\n"
	@echo "CAB object files: $(cab_obj)\n"
	@echo "Data class source files: $(data_class_files)\n"
	@echo "Data class object files: $(data_class_obj)\n"
