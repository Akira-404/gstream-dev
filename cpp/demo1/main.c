#include <gst/gst.h>

int
main (int argc, char *argv[])
{
  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Build the pipeline */
  pipeline =gst_parse_launch("playbins uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm",NULL);
  
  /* Start playing */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  
  /* Wait until error or EOS */
  bus = gst_element_get_bus (pipeline);
  
  // gst_bus_timed_pop_filtered()会阻塞直到你遇到一个错误或者流播放结束。
  msg =gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

  /* Free resources */
  if (msg != NULL)
    // 释放资源
    gst_message_unref (msg);

  // st_element_get_bus()会对总线增加一个引用，所以也需要调用get_object_unref()来释放
  gst_object_unref (bus);
  
  // 设置pipeline为NULL状态会让它释放掉所有的资源，最后，释放掉pipeline自身。
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  
  return 0;
}
