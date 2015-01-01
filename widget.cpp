#include "widget.h"



Widget::Widget()
{

    texte = new QLabel(this);
    manager = new QNetworkAccessManager(this);    
    vBoxL = new QVBoxLayout(this);
    a_url = new QUrl();
    b_quitter = new QPushButton("Quitter");
    t_timer = new QTimer(this);
    l_line = new QLineEdit(this);
    b_send = new QPushButton("Envoyer");
    fichier = new QFile("Chat.txt");
    l_username = new QLineEdit("Anonyme");
    hBoxL = new QHBoxLayout();

    texte->setWordWrap(1);

    a_url->setScheme("FTP");
    a_url->setHost("ftp.olympe.in");
    a_url->setPort(21);
    a_url->setUserName("darksasuke");
    a_url->setPassword("**********");
    a_url->setPath("/Messages/msg.txt");

    hBoxL->addWidget(l_username);
    hBoxL->addWidget(b_send);

    vBoxL->addWidget(texte);
    vBoxL->addWidget(l_line);
    vBoxL->addLayout(hBoxL);
    vBoxL->addWidget(b_quitter);

    this->setLayout(vBoxL);

    Actualiser();
    t_timer->start(2000);

    connect(b_quitter, SIGNAL(clicked()), this, SLOT(close()));
    connect(t_timer, SIGNAL(timeout()), this, SLOT(Actualiser()));
    connect(b_send, SIGNAL(clicked()), this, SLOT(sendMessage()));

}

void Widget::replyFinished()
{
    QNetworkReply *t = qobject_cast<QNetworkReply*>(sender());
    QFile fichier("Chat.txt");

    if (fichier.open(QIODevice::WriteOnly))
    {
        fichier.write(t->readAll());
        fichier.close();
        t->deleteLater();

    }

    if (fichier.open(QIODevice::ReadOnly))
    {
        texte->setText(fichier.readAll());
        texte->wordWrap();
        texte->show();
        fichier.close();
    }
}

void Widget::Actualiser()
{
    QNetworkRequest request(*a_url);
    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(finished()),this, SLOT(replyFinished()));
}

void Widget::sendMessage()
{
    t_timer->stop();
    QNetworkRequest request(*a_url);
    QString texte(l_line->text());

    QFile *envoi = new QFile("upload.txt");
    envoi->remove();
    fichier->copy("upload.txt");

    if (fichier->size() > 1000)
        envoi->remove();

    ofstream fichierRE("upload.txt", ios::out | ios::app);
    if (fichierRE)
    {
        fichierRE << l_username->text().toStdString() << " : " << texte.toStdString() << endl;
    }

    if (envoi->open(QIODevice::ReadOnly))
    {
        manager->put(request, envoi);
    }

    l_line->clear();

    t_timer->start(2000);
}
