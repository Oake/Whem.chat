#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QLineEdit>
#include <QFile>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <QHBoxLayout>

using namespace std;

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget();

public slots:
    void replyFinished();
    void Actualiser();
    void sendMessage();

private:
    QFile *fichier;
    QNetworkAccessManager *manager;
    QLabel *texte;
    QVBoxLayout *vBoxL;
    QUrl *a_url;
    QPushButton *b_quitter;
    QTimer *t_timer;
    QPushButton *b_send;
    QLineEdit *l_line;
    QLineEdit *l_username;
    QHBoxLayout *hBoxL;
};

#endif // WIDGET_H
