build_dir := build

.PHONY:all clean

all:$(build_dir) eigen3
	cd $(build_dir);cmake ../;make;make install
$(build_dir):
	mkdir $@;
	mkdir $@/third_party;

eigen3:$(build_dir)/third_party/eigen $(build_dir)/include/eigen3
$(build_dir)/include/eigen3:
	cd $(build_dir)/third_party/eigen;cmake ../../../third_party/eigen-323c052e1731 -DCMAKE_INSTALL_PREFIX=$(shell pwd)/build;make && make install

$(build_dir)/third_party/eigen:
	mkdir $(build_dir)/third_party/eigen;

clean:
	@echo "rm -rf $(build_dir)"
	@rm -rf $(build_dir)