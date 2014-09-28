#ifndef _Video_hpp_
#define _Video_hpp_

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
extern "C" {
#if __WORDSIZE == 64
# define INT64_C(c) c ## L
# define UINT64_C(c) c ## UL
#else
# define INT64_C(c) c ## LL
# define UINT64_C(c) c ## ULL
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
}

class Video
{
    //MEMBERS
private:
    AVFormatContext *videofile_format_context;
    AVCodecContext *videofile_codec_context_video;
    AVCodec *videofile_codec_video;
    AVDictionary *options_dict;
    int video_stream;
    int i;
    AVFrame *videofile_video_frame;
    AVFrame *videofile_video_frame_rgb;
    sf::Uint8 *videofile_buffer;
    AVPacket videofile_packet;
    int videofile_video_frame_finished;
    sf::Texture texture;
    sf::Sprite sprite;
    struct SwsContext *sws_ctx;

public:
    std::string id;
    std::string path;

    //CONSTRUCTORS
    Video(std::string _id, std::string _path);

    //DESTRUCTORS

    //METHODS


};

#endif
