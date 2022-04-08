#!/bin/bash
gst-launch-1.0 filesrc location=/home/ubuntu/gstream_dev/test.mp4 ! \
oggdemux name=demux ! queue ! vorbisdec ! autoaudiosink demux. ! \
queue ! theoradec ! videoconvert ! autovideosink