#include <gst/gst.h>


//pipeline:[source->filter->sink]

// 手动构建pipeline
int main(int argc, char *argv[])
{
    GstElement *pipeline;
    GstElement *source, *sink;

    GstBus *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;

    gst_init(&argc, &argv);

    // vieotestsrc是一个source element（生产数据），会创建一个video模式。
    source = gst_element_factory_make("videotestsrc", "source");

    // autovideosink是一个sink element（消费数据），会在一个窗口显示收到的图像。
    sink = gst_element_factory_make("autovideosink", "sink");

    // GStreamer中的所有elements都必须在使用之前包含到pipeline中。
    pipeline = gst_pipeline_new("test-pipeline");

    if (!pipeline || !source || !sink)
    {
        g_printerr("Not all elements could be created.\n");
        return -1;
    }

    // build the pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, sink, NULL);
    if (gst_element_link(source, sink) != TRUE)
    {
        g_printerr("elements could not be linked.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    // modify the source properties
    g_object_set(source, "pattern", 0, NULL);

    // start playing
    ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE)
    {
        g_printerr("ubable to set the pipeline to the playing state.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    // wait until error or eos
    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    /* Parse message */
    if (msg != NULL)
    {
        GError *err;
        gchar *debug_info;

        switch (GST_MESSAGE_TYPE(msg))
        {
        case GST_MESSAGE_ERROR:
            gst_message_parse_error(msg, &err, &debug_info);
            g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
            g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
            g_clear_error(&err);
            g_free(debug_info);
            break;
        case GST_MESSAGE_EOS:
            g_print("End-Of-Stream reached.\n");
            break;
        default:
            /* We should not reach here because we only asked for ERRORs and EOS */
            g_printerr("Unexpected message received.\n");
            break;
        }
        gst_message_unref(msg);
    }

    // free resources
    gst_object_unref(bus);

    // set pipeline state
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}