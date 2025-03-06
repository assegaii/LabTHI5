#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QDebug>

class AbstractTrack
{
protected:
    QString _title;
    QString _artist;
    double _duration;

public:
    AbstractTrack(const QString &title, const QString &artist, double duration)
        : _title(title), _artist(artist), _duration(duration) {}

    virtual void ShowInfo() const = 0;
    virtual double getDuration() const { return _duration; }

    virtual QString getTitle() const { return _title; }
    virtual QString getArtist() const { return _artist; }

    virtual ~AbstractTrack() {}
};

class MusicTrack : public AbstractTrack
{
private:
    QString _genre;

public:
    MusicTrack(const QString &title, const QString &artist, double duration, const QString &genre)
        : AbstractTrack(title, artist, duration), _genre(genre) {}

    void ShowInfo() const override
    {
        qDebug() << "Музыка: " << _title << " Автор: " << _artist << ", Жанр: " << _genre
                 << ", Продолжительность: " << _duration << " мин.";
    }

    QString getTitle() const { return _title; }
    QString getArtist() const { return _artist; }
    double getDuration() const { return _duration; }
    QString getGenre() const { return _genre; }

    QString getInfo() const
    {
        return _title + " - " + _artist + " (" + QString::number(_duration) + " мин) [" + _genre + "]";
    }
};

#endif // TRACK_H
