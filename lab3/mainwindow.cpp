#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    page("page.html")
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->horizontalLayout);
     m_pb=new QProgressBar(this);
    m_pb->hide();
    man=new QNetworkAccessManager(this);
    //запрос страницы
    request=new QNetworkRequest(QUrl("http://zaycev.net/"));
    reply=man->get(*request);
    connect(reply,SIGNAL(finished()),this,SLOT(onFinished()));
    connect(reply,SIGNAL(readyRead()),this,SLOT(readyRead()));
    if (!page.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {

    }
    else
    {
        page.close();
    }
}

MainWindow::~MainWindow()
{
    if (!items.empty())
    {
        QMutableVectorIterator<MusicItem*> it(items);
        while(it.hasNext())
        {
            MusicItem* item=it.next();
            delete item;
        }
        items.clear();
    }
    delete request;
    delete ui;
}

void MainWindow::parse(QFile *f)
{
    //QRegExp
    if (!f->open(QIODevice::ReadOnly))
    {
        qDebug()<<"Не открыли "<<f->fileName();
    }
    else
    {
        QString subjstr=f->readAll();
        //QRegularExpression re("<a.* id=\"audiotrack-download-link\" .*?>[^<>]+</a>");
        QRegularExpression ItemsRE("<a .*?class=(\"|')musicset-track__link\\1.*?>[^<>]+</a>");
        //QRegularExpression re("<div .*? class=(\"|')musicset-track__link\\1.*?>[^<>]+</div>");
        QRegularExpressionMatchIterator it=ItemsRE.globalMatch(subjstr);
        while (it.hasNext())
        {
            MusicItem* pItem=new MusicItem();
            items.append(pItem);
            QRegularExpressionMatch match=it.next();
            QString ItemStr(match.captured());
            QRegularExpression RE1(">[^<>]+<");
            QRegularExpression RE2("href=\".+?\"");
            match=RE1.match(ItemStr);
            QString str=match.captured();
            pItem->trackArtist=str.remove(QRegularExpression("[<>]"));
            //qDebug()<<"trackArtist: "<<str<<"\n";
            //-------------
            match=RE2.match(ItemStr);
            str=match.captured();
            str.remove(0,6);
            pItem->trackArtistLink=str.remove(str.length()-1,1);
            ui->plainTextEdit->appendPlainText(str);
            //qDebug()<<"trackArtistLink: "<<str<<"\n";
            //-------------
            if (it.hasNext())
            {
                match=it.next();
                ItemStr=match.captured();
                match=RE1.match(ItemStr);
                str=match.captured();
                pItem->trackName=str.remove(QRegularExpression("[<>]"));
                //qDebug()<<"trackName: "<<str<<"\n";
                //-------------
                match=RE2.match(ItemStr);
                str=match.captured();
                str.remove(0,6);
                pItem->trackLink=str.remove(str.length()-1,1);
                ui->plainTextEdit->appendPlainText(str);
                //qDebug()<<"trackLink: "<<str<<"\n";
            }
        }
        QVectorIterator<MusicItem*> iterator(items);
        while (iterator.hasNext())
        {
            MusicItem* itm=iterator.next();
            QListWidgetItem* item=new QListWidgetItem();
            item->setWhatsThis(itm->trackLink);//QString("<a href=http://www.zaycev.net"+itm->trackLink+">скачать</a>"));
            item->setData(Qt::DisplayRole,QString(itm->trackArtist+" - "+itm->trackName));
            ui->listWidget->addItem(item);
        }
        //--------XQuery(not working)---------
        //        QXmlQuery qry;
        //        qry.bindVariable("inputDocument",f);
        //        QFile xq("query.xq");
        //        QString strQuery;
        //        if(xq.open(QIODevice::ReadOnly |QIODevice::Text))
        //        {
        //            qDebug()<<"открыли "<<xq.fileName();
        //            qry.setQuery(&xq,QUrl::fromLocalFile(xq.fileName()));
        //            if (!qry.isValid())
        //            {
        //                qDebug()<<"Неправильный запрос";
        //                f->close();
        //                xq.close();
        //                return result;
        //            }
        //            if(!qry.evaluateTo(&result))
        //            {
        //                qDebug()<<"Can't evaluate";
        //                f->close();
        //                xq.close();
        //                return result;
        //            }
        //            //qDebug()<<strout;
        //            xq.close();
        //            f->close();
        //            return result;
        //        }
        //        else
        //        {
        //            f->close();
        //            return result;
        //        }
        f->close();
    }
}

void MainWindow::readyRead()
{
    QByteArray bytes;
    if (!page.open(QIODevice::WriteOnly|QIODevice::Append))
    {
    }
    bytes=reply->readAll();
    page.write(bytes);
    page.close();
}

void MainWindow::onFinished()
{
    //----------------
    parse(&page);
    //----------------
    //    request->setUrl(QUrl("http://cdndl.zaycev.net/819580/6495607/eldzhey_-_minimal_%28zaycev.net%29.mp3"));
    //    reply=man->get(*request);
    //    connect(reply,SIGNAL(finished()),this,SLOT(onDownload()));
    // connect(reply,SIGNAL(readyRead()),this,SLOT(readyMp3Read()));

}

void MainWindow::onDownloaded()
{
    ui->statusBar->removeWidget(m_pb);
    QByteArray bytes;
    QFile mp3file(reply->objectName()+QString(".mp3"));
    if (!mp3file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        reply->deleteLater();
        return;
    }
    bytes=reply->readAll();
    mp3file.write(bytes);
    mp3file.close();
    qDebug()<<"download is done";
    reply->deleteLater();

}

void MainWindow::slotDownloadProgress(qint64 received, qint64 total)
{
    if (total>0)
    {
        m_pb->setValue(100*received/total);
    }
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QUrl url(QString("http://zaycev.net")+item->whatsThis());
    //qDebug()<<item->whatsThis();
    QString trackName=(item->data(Qt::DisplayRole)).toString();
    request->setUrl(url);
    reply=man->get(*request);
    QEventLoop loop;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    connect(reply,SIGNAL(finished()),reply,SLOT(deleteLater()));
    loop.exec();
    QString subjstr=reply->readAll();
    ui->plainTextEdit->setPlainText(subjstr);
    QRegularExpression RE1("<a [^<>]*id=\"audiotrack-download-link\"[^<>]*>");
    QRegularExpression RE2("href=\".+?\"");
    QRegularExpressionMatch match=RE1.match(subjstr);
    QString str=match.captured();
    qDebug()<<str;
    match=RE2.match(str);
    str=match.captured();
    if (match.hasMatch())
    {
        str.remove(0,6);
        str.remove(str.length()-1,1);
    }
    else
    {
        QMessageBox m(this);
        m.setWindowTitle("Info");
        m.setIcon(QMessageBox::Information);
        m.setText("Not able to download that song(((!!!");
        m.exec();
        return;
    }
    qDebug()<<str;
    request->setUrl(str);
    reply=man->get(*request);
    reply->setObjectName(trackName);
    ui->statusBar->addWidget(m_pb);
    m_pb->show();
    connect(reply,SIGNAL(finished()),m_pb,SLOT(hide()));
    connect(reply,SIGNAL(finished()),this,SLOT(onDownloaded()));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(slotDownloadProgress(qint64,qint64)));
}
