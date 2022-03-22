#filesrc读取文件
#
#oggdemux解析文件，分别提取audio，video数据，
#queue缓存数据，
#vorbisdec解码audio，
#autoaudiosink自动选择音频设备并输出，
#
#theoradec解码video，
#videoconvert转换video数据格式，
#autovideosink自动选择显示设备并输出。


gst-launch-1.0 filesrc location=/home/ubuntu/gstream_dev/test.mp4 ! \
  qtdemux name=demux demux.video_0 ! queue ! mpeg4videoparse ! \
  omxmpeg4videodec ! nveglglessink -e
