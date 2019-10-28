###
#
.PHONY: all lib print test

# Directories
test_dir = ./test
build_dir = ./build

test_app = test_app

# Options for opencv
CFLAGS=`pkg-config --cflags opencv`
LIBS=`pkg-config --libs opencv`

cab_lib_files = $(wildcard *.cpp)
cab_obj = $(patsubst %, $(build_dir)/%, $(cab_lib_files:.cpp=.o))

test_files = $(wildcard ./test/*.cpp)

inc_dir = ./

all: lib 

test: $(test_app)

lib: $(cab_obj) $(build_dir)
	@echo "Library compiled!"

${test_app}: $(test_files) $(cab_obj) 
	g++ $^ -I ${inc_dir} -g -o $@ `pkg-config --libs --cflags opencv` 

$(cab_obj): $(cab_lib_files)
	printf "Compiling library...\n"
	@mkdir -p $(build_dir)
	g++ -c $^ -g `pkg-config --libs --cflags opencv` -o $@


$(build_dir):
	@mkdir -p $@

print:
	@echo "CAB source files: $(cab_lib_files)\n"
	@echo "CAB object files: $(cab_obj)\n"
