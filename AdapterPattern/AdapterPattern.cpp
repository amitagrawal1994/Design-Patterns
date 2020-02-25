#include <iostream>
#include <string>
using namespace std;

#define interface struct

/* this is the legacy class which was there before also */
interface MediaPlayer
{
    virtual void playMedia(string mediaType, string mediaFile) = 0;
};

/* this is new functionalities (like mp4 and vlc) interface */
interface AdvancedMediaPlayer
{
    virtual void playMedia(string filename) = 0;
};

struct vlcMediaPlayer : public AdvancedMediaPlayer
{
    void playMedia(string filename)
    {
        cout<<"Playing vlc media : "<<filename<<endl;
    }
};

struct mp4MediaPlayer : public AdvancedMediaPlayer
{
    void playMedia(string filename)
    {
        cout<<"Playing mp4 media : "<<filename<<endl;
    }
};

/* the adapter class */
class MediaAdapter : public MediaPlayer
{
    AdvancedMediaPlayer* advancedMediaPlayer;
    public:
        void playMedia(string mediaType, string mediaFile)
        {
            if(mediaType == "vlc")
            {
                advancedMediaPlayer = new vlcMediaPlayer();
                advancedMediaPlayer->playMedia(mediaFile);
            }
            else if(mediaType == "mp4")
            {
                advancedMediaPlayer = new mp4MediaPlayer();
                advancedMediaPlayer->playMedia(mediaFile);
            }
        }
};

/* This is the legacy concrete class */
class AudioPlayer : public MediaPlayer
{
    public:
        void playMedia(string mediaType, string mediaFile)
        {
            if(mediaType == "mp3") //mp3 is legacy type
                cout<<"Playing mp3 media : "<<mediaFile<<endl;
            else // new adapter's code
            {
                MediaAdapter* mediaAdapter = new MediaAdapter();
                mediaAdapter->playMedia(mediaType, mediaFile);
            }
        }
};

int main()
{
    MediaPlayer* mediaPlayer = new AudioPlayer();
    mediaPlayer->playMedia("mp3","Media1.mp3");
    mediaPlayer->playMedia("vlc","Media2.vlc");
    mediaPlayer->playMedia("mp4","Media3.mp4");
    return 0;
}