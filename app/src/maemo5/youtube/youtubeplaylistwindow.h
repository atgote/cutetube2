/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef YOUTUBEPLAYLISTWINDOW_H
#define YOUTUBEPLAYLISTWINDOW_H

#include "stackedwindow.h"
#include "youtubeplaylist.h"

class VideoDelegate;
class YouTubeUser;
class YouTubeVideoModel;
class Image;
class ImageCache;
class ListView;
class TextBrowser;
class PlaylistThumbnail;
class QLabel;
class QScrollArea;
class QHBoxLayout;
class QModelIndex;

class YouTubePlaylistWindow : public StackedWindow
{
    Q_OBJECT
    
public:
    explicit YouTubePlaylistWindow(const QString &id, StackedWindow *parent = 0);
    explicit YouTubePlaylistWindow(const YouTubePlaylist *playlist, StackedWindow *parent = 0);
    ~YouTubePlaylistWindow();
    
private:
    void loadBaseUi();
    void loadPlaylistUi();
    void loadUserUi();
    
private Q_SLOTS:
    void getVideos();
    
    void playPlaylist();
    
    void addVideoToPlaylist();
    void downloadVideo();
    void playVideo(const QModelIndex &index);
    void removeVideo();
    void setVideoFavourite();
    void shareVideo();
    void showVideo(const QModelIndex &index);
    
    void showContextMenu(const QPoint &pos);
    
    void showResource(const QUrl &url);
    void showUser();
    
    void onImageReady();
    void onModelStatusChanged(QYouTube::ResourcesRequest::Status status);
    void onPlaylistStatusChanged(QYouTube::ResourcesRequest::Status status);
    void onPlaylistUpdateStatusChanged(QYouTube::ResourcesRequest::Status status);
    void onUserStatusChanged(QYouTube::ResourcesRequest::Status status);
    void onVideoUpdateStatusChanged(QYouTube::ResourcesRequest::Status status);
    
private:
    YouTubePlaylist *m_playlist;
    YouTubeUser *m_user;
    YouTubeVideoModel *m_model;
    ImageCache *m_cache;
    
    PlaylistThumbnail *m_thumbnail;
    Image *m_avatar;
    ListView *m_view;
    VideoDelegate *m_delegate;
    QScrollArea *m_scrollArea;
    QLabel *m_titleLabel;
    TextBrowser *m_descriptionLabel;
    QLabel *m_dateLabel;
    QLabel *m_userLabel;
    QLabel *m_noVideosLabel;
    QAction *m_reloadAction;
    QMenu *m_contextMenu;
    QAction *m_downloadAction;
    QAction *m_shareAction;
    QAction *m_favouriteAction;
    QAction *m_playlistAction;
    QAction *m_removeAction;
    QHBoxLayout *m_layout;
};
    
#endif // YOUTUBEPLAYLISTWINDOW_H
