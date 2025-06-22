PROJECT:=go-admin
BUILD_DIR:=build

.PHONY: build clean

rebuild: clean build 	

build:
	cmake -S. -B$(BUILD_DIR)
	cmake --build $(BUILD_DIR)


clean:	
	# @rm -f $(BUILD_DIR)
	rm -fr $(BUILD_DIR)

