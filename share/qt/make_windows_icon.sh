#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/mozocoin.ico

convert ../../src/qt/res/icons/mozocoin-16.png ../../src/qt/res/icons/mozocoin-32.png ../../src/qt/res/icons/mozocoin-48.png ${ICON_DST}
