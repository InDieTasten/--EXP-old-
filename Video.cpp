#include "Video.hpp"

//CONSTRUCTORS
Video::Video(std::string _id, std::string _path)
{
    id = _id;
    path = _path;
    *videofile_format_context = NULL;
    *videofile_codec_context_video = NULL;
    *videofile_codec_video = NULL;
    *options_dict = NULL;
    video_stream = -1;
    *videofile_video_frame = NULL;
    *videofile_video_frame_rgb = NULL;
    *sws_ctx = NULL;
}

//DESTRUCTORS

//METHODS
void Video::load()
{
    av_register_all();
    /*
    * Open video file:
    */
    if (avformat_open_input(&videofile_format_context, "test.avi", NULL, NULL) !=0)
    {
        std::cerr << "Error: avformat_open_input() failed! Maybe the file doesn't exist?" << std::endl;
        return 1;
    };
    /*
    * Get stream information:
    */
    if (av_find_stream_info(videofile_format_context) < 0)
    {
        std::cerr << "Error: avformat_find_stream_info() failed!" << std::endl;
        return 2;
    };
    /*
    * Dump file information:
    */
    av_dump_format(videofile_format_context, 0, argv[1], 0);
    /*
    * Find first video stream:
    */
    for (i=0; i < videofile_format_context->nb_streams; i++)
    {
        if (videofile_format_context->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            video_stream = i;
            break;
        };
    }
    if (video_stream == -1)
    {
        std::cerr << "Error: Couldn't find a video stream!" << std::endl;
        return 3;
    };
    videofile_codec_context_video = videofile_format_context->streams[video_stream]->codec;
    /*
    * Find a decoder:
    */
    videofile_codec_video = avcodec_find_decoder(videofile_codec_context_video->codec_id);
    if (videofile_codec_video == NULL)
    {
        std::cerr << "Error: Unsupported video codec!" << std::endl;
        return 4;
    };
    /*
    * Open codec:
    */
    //if (avformat_open_input(&videofile_format_context, "test.avi", NULL, NULL) < 0)
    if (avcodec_open(videofile_codec_context_video, videofile_codec_video) < 0)
    {
        std::cerr << "Error: Couldn't open video codec!" << std::endl;
        return 5;
    };
}
void Video::unload()
{

}

