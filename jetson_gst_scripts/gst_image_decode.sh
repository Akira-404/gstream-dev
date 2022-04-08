#!/bin/bash
gst-launch-1.0 filesrc location=image.jpg ! nvjpegdec ! \
imagefreeze ! xvimagesink -e