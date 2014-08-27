SDK_VERSION=2.4.1
SDK_ZIP_NAME=PebbleSDK-$SDK_VERSION.tar.gz

wget http://assets.getpebble.com.s3-website-us-east-1.amazonaws.com/sdk2/$SDK_ZIP_NAME
tar -zxf $SDK_ZIP_NAME
mkdir tests/include
mv PebbleSDK-$SDK_VERSION/Pebble/include/pebble.h tests/include/
mv PebbleSDK-$SDK_VERSION/Pebble/include/pebble_fonts.h tests/include/
mv PebbleSDK-$SDK_VERSION/Pebble/include/pebble_app_info.h tests/include/
touch tests/include/pebble_warn_unsupported_functions.h