#!/bin/bash
gst-launch-1.0 filesrc location=/home/ubuntu/gstream_dev/test.mp4 ! \
qtdemux name=demux demux.video_0 ! queue ! h264parse ! omxh264dec ! \
nveglglessink -e
